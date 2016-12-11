#include <math.h>
/* Gregorian calendar adopted 15 Oct 1582 */
#define IGREG (15+31L*(10+12L*1582))
/* returns the Julian Day Number which begins at noon
   of the calendar date specified by integers 
   (month mm, day id, year iyyy)
   positive is AD, negative is BC
Note: the year after 1 BC was 1 AD */
long julday(int mm, int id, int iyyy)
{
  long jul;
  int ja, jy, jm;
  void nrerror();

  if (iyyy == 0)
    nrerror("JULDAY: there is no year zero.");
  if (iyyy < 0)
    ++iyyy;
  if (mm > 2) {
    jy = iyyy;
    jm = mm+13;
  } else {
    jy = iyyy-1;
    jm = mm+13;
  }
  jul = (long)(floor(365.25*jy)+floor(30.6001*jm)+id+1720995);

  /* test whether to change to Gregorian Calendar */
  if (id+31L*(mm+12L*iyyy) >= IGREG) {
    ja = 0.01*jy;
    jul += 2-ja+(int)(0.25*ja);
  }
  return jul;
}

