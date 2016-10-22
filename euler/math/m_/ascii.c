#include <stdio.h>

char *str[256]={
	"nul","soh","stx","etx","eot","enq","ack","bel",
	"bs ","ht ","nl ","vt ","np ","cr ","so ","si ",
	"dle","dc1","dc2","dc3","dc4","nak","syn","etb",
	"can","em ","sub","esc","fs ","gs ","rs ","us ",
	"sp "," ! "," \" "," # "," $ "," % "," & "," ' ",
	" ( "," ) "," * "," + "," , "," - "," . "," / ",
	" 0 "," 1 "," 2 "," 3 "," 4 "," 5 "," 6 "," 7 ",
	" 8 "," 9 "," : "," ; "," < "," = "," > "," ? ",
	" @ "," A "," B "," C "," D "," E "," F "," G ",
	" H "," I "," J "," K "," L "," M "," N "," O ",
	" P "," Q "," R "," S "," T "," U "," V "," W ",
	" X "," Y "," Z "," [ "," \\ "," ] "," ^ "," _ ",
	" ` "," a "," b "," c "," d "," e "," f "," g ",
	" h "," i "," j "," k "," l "," m "," n "," o ",
	" p "," q "," r "," s "," t "," u "," v "," w ",
	" x "," y "," z "," { "," | "," } "," ~ ","del",
	"x80","x81","x82","x83","x84","x85","x86","x87",
	"x88","x89","x8a","x8b","x8c","x8d","x8e","x8f",
	"x90","x91","x92","x93","x94","x95","x96","x97",
	"x98","x99","x9a","x9b","x9c","x9d","x9e","x9f",
	"xa0"," ¡ "," ¢ "," £ "," ¤ "," ¥ "," ¦ "," § ",
	" ¨ "," © "," ª "," « "," ¬ "," - "," ® "," ¯ ",
	" ° "," ± "," ² "," ³ "," ´ "," µ "," ¶ "," · ",
	" ¸ "," ¹ "," º "," » "," ¼ "," ½ "," ¾ "," ¿ ",
	" À "," Á "," Â "," Ã "," Ä "," Å "," Æ "," Ç ",
	" È "," É "," Ê "," Ë "," Ì "," Í "," Î "," Ï ",
	" Ð "," Ñ "," Ò "," Ó "," Ô "," Õ "," Ö "," × ",
	" Ø "," Ù "," Ú "," Û "," Ü "," Ý "," Þ "," ß ",
	" à "," á "," â "," ã "," ä "," å "," æ "," ç ",
	" è "," é "," ê "," ë "," ì "," í "," î "," ï ",
	" ð "," ñ "," ò "," ó "," ô "," õ "," ö "," ÷ ",
	" ø "," ù "," ú "," û "," ü "," ý "," þ "," ÿ "
};

int
main(void)
{
  int j=-1;
  for (int i=0; i<256; ++i) {
    if (i%8==0)
      printf("\n\t%2d\t", ++j);
    printf("%s ", str[i]);
  }
  printf("\n");
	return(0);
}

