#include <stdio.h>
#include <math.h>

#include "nrutil.c"
#include "flmoon.c"
#include "julday.c"

#define ZON -5.0    /* time zone -5 is Eastern Standard Time */
#define IYBEG 1900  /* the range of dates to be searched */
#define IYEND 2000

int main(void) /* Program BADLUK */
{
  int ic, icon, idwk, im, iyyy, n;
  float timzon = ZON/24.0, frac;
  long jd, jday;
  void flmoon();
  long julday();

  printf("\nFull moons on Friday the 13th from %5d to %5d\n", IYBEG,IYEND);
  /* loop over each year and month, is the 13th a Friday ? */
  for (iyyy=IYBEG; iyyy<=IYEND; ++iyyy) {
    for (im=1; im<=12; ++im) {
      jday = julday(im, 13, iyyy);
      idwk = (int) ((jday+1) % 7);
      if (idwk == 5) {
        /* n is the first approximation of how many full moons have occurred
         * since 1900
         * up<->down until 13th was/was not a full moon
         * icon is the direction of adjustment */
        n = 12.37*(iyyy-1900+(im-0.5)/12.0);
        icon = 0;

        for (;;) { 
          /* get date of full moon n */
          flmoon(n, 2, &jd, &frac);
          /* convert to hours in correct time zone */
          frac = 24.0*(frac+timzon);

          /* convert from Julian Days (beginning:noon) to
           * civil days (beginning:midnight) */
          if (frac < 0.0) {
            --jd;
            frac += 24.0;
          }
          if (frac > 12.0) {
            ++jd;
            frac -= 12.0;
          } else
            frac += 12.0;
          if (jd == jday) { /* target day hit? */
            printf("\n%2d/13/%4d\n", im,iyyy);
            printf("%s %5.1f %s\n", "Full moon",frac,
                " hrs after midnight (EST)");
            break;
          } else { /* did not hit */
            ic = (jday >= jd ? 1 : -1);
            if (ic == (-icon))
              break;
            icon = ic;
            n += ic;
          }
        }
      }
    }
  }
}

