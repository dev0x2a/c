/*
 * v1.6
 * Star-Empires, author D. Bolton (C)2011 http://cplus.about.com
 * This is from the series of Programming in C by David Bolton
 * Article url:  http://cplus.about.com/od/learningc/ss/programming-games-in-c-tutorial-one.htm
 * Last updated: 27 Jan 2013
 * 
 * Changes:
 * 1.6 27-jan-2013 added 0 to first return in checkmessages
 */

#include <time.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h> /* needed for _getch() */
#include <math.h>
#include <Windows.h>

/* #define CC386 //comment out if not compiling with CC386 */

/* data structures  */
struct fleet {
	int from;
	int to;
	int turns;
	int numships;
	int owner; /* (o or 1) */
};

struct system {
	int x,y;
	int numships;
	int owner;
};

/* defines a message type */
typedef char message[120];

/* game data */
#define WIDTH 80
#define HEIGHT 50
#define MAXLEN 4
#define MAXFLEETS 100
#define MAXSYSTEMS 10
#define FIGHTMARKER 999
#define SECSPERTURN 5
#define MSGLINE 25
#define CMDLINE 45

struct system galaxy[MAXSYSTEMS];
struct fleet fleets[MAXFLEETS];
char layout[5][5];
message messagebuffer;
message messages[100];
message spaces;
int msgindex;
int msghead,msgtail;
int GameOver;
int Turn;
clock_t lasttick;

/* returns a number between 1 and max */
int Random(int max) {
	return (rand() % max) + 1;
}

/* returns the index in the galaxy for the sysm at x,y */
int getsystem(int x,int y) {
	int i;
	for (i=0;i<10;i++)
		if (galaxy[i].x==x && galaxy[i].y==y){
			return i;
		}
	return -1; /* should never get here! */
}

/* returns a + for systems owned by the player, - for enemy and u for unowned */
char owner(int x,int y) {
	int i= getsystem(x,y);
	if (i != -1)
	  {
		if (galaxy[i].owner==0)
			return '+';
		else
			if (galaxy[i].owner==1)
			return '-';
			else
			return 'u';
		}
	return ' '; /* should never get here! */
}

/* moves the cursor to x,y x- across, y = down */

#ifndef CC386
void gotoxy( short x, short y ) 

{ 
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE) ; 
    COORD position = { x, y } ; 
     
    SetConsoleCursorPosition( hStdout, position ) ; 
}  

/* comment this function out with CC386 */
COORD GetConsoleSize() 
{ 
    HANDLE hnd = GetStdHandle(STD_OUTPUT_HANDLE) ; 
    return GetLargestConsoleWindowSize(hnd); 
}  

/* comment this function out with CC386 */
COORD SetScreenSize(short x,short y) {
	COORD result; 
	HANDLE hnd;
	result.X=0;
	result.Y=0;
    hnd= GetStdHandle(STD_OUTPUT_HANDLE) ; 
    SetConsoleDisplayMode( hnd,CONSOLE_WINDOWED_MODE,&result);
    return result;
}
#endif


/* clears the screen area */
void ClrScr() {
	COORD c;
	DWORD NumWr;
	HANDLE hnd = GetStdHandle(STD_OUTPUT_HANDLE) ;
	c.X=0;
	c.Y=0;
     
    FillConsoleOutputCharacter(hnd,' ',WIDTH*HEIGHT,c,&NumWr);
	/* FillConsoleOutputAttribute(hnd,0x88,4000,c,&NumWr);  for setting color*/
}

/* returns distance as int. Values are always in the range 1-6 */
int distance(int x,int y) {
   int distsqr= (x*x) + (y*y);
   return (int)(sqrt((float)distsqr)+0.5);
}

/* This initialises a single system */
void InitSystem(int systemindex,int x,int y,int shipnums,int owner) {
		galaxy[systemindex].x=x;		
		galaxy[systemindex].y=y;
		galaxy[systemindex].numships = shipnums;
		galaxy[systemindex].owner = owner;
		layout[x][y]=(char)(systemindex+48);
}

/* Generates a random layout of systems (apart from systems 0 and 9 which are always fixed.
This also sets up the number of ships at aeach system */
void GenMapSystems() {
	int i,x,y;

	for (x=0;x<5;x++)
	for (y=0;y<5;y++) {
		layout[x][y]=' ';
	}

	InitSystem(0,0,0,50,0);
	InitSystem(9,4,4,50,9);

	/* Find an empty space for remaining 8 systems*/
	for (i=1;i<=8;i++) {
		do {
			x= Random(5)-1;
			y= Random(5)-1;
		}
		while (layout[x][y] !=' ');
	   InitSystem(i,x,y,15,-1);
	}

}

/* Boxes off the area for messages to appear in */
void DisplayMessageArea(){
gotoxy(0,MSGLINE);printf(   "============================= Messages =============================");
gotoxy(0,MSGLINE+18);printf("====================================================================");
}

/* return 1 if one second passed since last lasttick */
int onesecpassed() {
	clock_t tick = clock();
	if (tick-lasttick > CLOCKS_PER_SEC)
		{
			lasttick = tick;
			return 1;
	}
	else
		return 0;
}

void DisplayMap() {
int x,y;
gotoxy(0,5);printf("Map\n\r");
for (y=0;y<5;y++) {
	printf("   ");
	for (x=0;x<5;x++) {
		if (layout[x][y]==' ')
			printf(" .  ");
		else
			printf(" %c%c ",layout[x][y],owner(x,y));
	}
	
	printf("\n\r");
   }
}

void DisplayDistances() {
int x,y,sx,sy,sx2,sy2;
gotoxy(0,12);printf("System Distances\n\r");
printf("  To   1  2  3  4  5  6  7  8  9\n\r");
printf("     ----------------------------\n\r");
for (y=0;y<9;y++) {
	printf("      ");
	sx = galaxy[y].x;
	sy = galaxy[y].y;
	for (x=1;x<10;x++) {
	    if (x>y)
		{
			sx2 = galaxy[x].x;
			sy2 = galaxy[x].y;
			printf(" %c ",(char)(distance(sx-sx2,sy-sy2)+'0'));
		 }
		else
			printf("   ");
	}
	printf("| %2d\n\r",y);
   }
}

/* messages go in a 100 x 100 message buffer array with msgtail and msghead
messages are added using the tail and displayed from the msghead */
void SendaMessage(char * text) {
  sprintf(messages[msgtail],"%i %s",Turn,text);
  msgtail++;
  if (msgtail == 100)
	  msgtail=0;
}

/* writes a message with a single int parameter */
void SendaMessage2(char * msgtext,int x) {
  char buffer[100];
  sprintf(buffer,"%s %i",msgtext,x);
  SendaMessage(buffer);
}

/* initializes all the game data in one place */
void InitData() {
	int i;
	for (i=0;i< MAXFLEETS;i++)
		fleets[i].numships=0;
	for(i=0;i<sizeof(message);i++)
		spaces[i]=' ';
	spaces[sizeof(message)-1]='\0';
	msgindex=0;
	msghead=0;
	msgtail=0;
	GameOver=0;
	srand((int)time(NULL));
	Turn=1;
	lasttick = clock();
}

/* totals up how many player's ships are on the way to the specified system */
int shipsSent(int tosystem) {
	int i,total;
	total=0;
	for (i=0;i<MAXFLEETS;i++)
		if (fleets[i].to==tosystem && fleets[i].numships >0 && fleets[i].owner==0)
			total+= fleets[i].numships;
	return total;
}

/* calculates the soones arrival time of any fleet at a system */
int turnstogo(int tosystem) {
	int i,ttg;
	ttg = 99;
	for (i=0;i<MAXFLEETS;i++)
	{
		if (fleets[i].to==tosystem && fleets[i].numships >0 && fleets[i].owner==0)
			{
				if (fleets[i].turns<ttg)
					ttg= fleets[i].turns;
				else
					if (fleets[i].turns= FIGHTMARKER)
						ttg = 0;
		}
	}
	return ttg;
}

void DisplayFleets() {
	int i,owner,ttg;
	char text[20];
	gotoxy(45,13);printf("System(Own) Ships Sent(Turns)");
	for (i=0;i<MAXSYSTEMS;i++) {
	  gotoxy(45,14+i);
	  owner = galaxy[i].owner;
	  if (owner==-1 )
		strcpy(text,"u");
	  else
		  _snprintf(text,5,"%i",owner);
	  printf("%2i (%3s)    %3i   %3i",i,text,galaxy[i].numships,shipsSent(i));
	  ttg = turnstogo(i);
	  if (ttg!= 99)
		  printf("(%i)  ",ttg); 
	  else
		  printf("     ");
	}
}

/* clears line# in the display */
void clr(int line) {
	int i;
	gotoxy(0,line);
	for (i=0;i<WIDTH;i++)
	{
		printf(" ");
	}
}

/* wait for numms (millisecs) */
void waitms(int numms) {
	clock_t until;
	until = clock()+(numms*1000/CLOCKS_PER_SEC);	/* 1,2,3...		*/
	while (clock() < until) {
		if (_kbhit())
			break;
	}
}

/* displays the turn number and adds 1 to it */
void ShowTurn() {
	gotoxy(45,5);	
	SendaMessage2("Turn ",Turn);
	printf("Turn %d",Turn++);

}

/* handles input chars 0-9, backspace and return */
int GetInput() {
	char * back ="\b \b";
	char buffer[MAXLEN+1]; /* max 4 digits */
	char key;
	int result=0;
	int buflen=0;
	int hitreturn=0;
	buffer[0]='\0';
	do {
		key=_getch();
		if (key==27)
			return -1;
		buflen=strlen(buffer);
		if ((buflen < MAXLEN && key >='0' && key <='9') || 
			(buflen >0 && (key== 8 || key==13)))
		{
			  if (key ==13)
				  hitreturn=1;
			  else
				if (key==8)
				{
					buffer[--buflen]='\0';
					printf("%s",back);
					
				}
				else
				{
					buffer[buflen++]=key;
					buffer[buflen]='\0';				
					printf("%c",key);
				}
		}
	}
     while (!hitreturn);
  return atoi(buffer);
}

/* Every time this is called, it checks if one second passed and if not 
it returns. It's called from the keyboard input loop when no key is pressed. 
The message display is 15 lines of messages that scroll up.
Messages are written into a 100 line buffer using msgtail as the index 
into the 100 lines to write the message. Then msghead follows msgtail and is where 
messages are displayed from. The tricky bits are
1). Making sure both msgtail wrap round (at 100 they become 0) and
2). When less than 15 lines of messages, write spaces (only happens at start)
*/

int CheckMessages() {
	int i,nummsgs,numbl,j,line;
	if (!onesecpassed())
		return 0;
    line = MSGLINE+1;
	nummsgs=0;
	if (msghead != msgtail) {
		if (msghead < msgtail)
			nummsgs =  (msgtail - msghead);
		else
			nummsgs = (msgtail+100-msghead);
	}
	else
	  return 0; /* no messages */
	if (nummsgs < 15) {
		numbl = 15-nummsgs;
		for(i=0;i<numbl;i++){
			gotoxy(0,line+i);
			printf("%66s",spaces);
		}
		j=msghead;
		for (i=numbl;i<16;i++)
		{			
			gotoxy(0,line+i);
			printf("%66s",spaces);			
			gotoxy(0,line+i);
			printf(messages[j++]);
		}

	}
	else
	{		/* don't move msghead until all message space is full */
		j=msghead++;
		if (msghead >=100)
			msghead =0; /* wraps around */
		for (i=0;i<16;i++)
		{						
			gotoxy(0,line+i);
			printf(spaces);	
			gotoxy(0,line+i);
			printf(messages[j++]);
		}
	}
	return 1; /* Messages scrolled */ 
}


void CheckGameOver() {
	int i,countpl,countenemy,checkfleets;
	checkfleets=0;
	countpl=0;
	countenemy=0;
	for (i=0;i<MAXSYSTEMS;i++)
		if (galaxy[i].owner==0)
			countpl++;
		else
		if (galaxy[i].owner==9)
			countenemy++;
	if (countpl==MAXSYSTEMS)
		{
			SendaMessage("You have captured ten systems");
			checkfleets=1;
	}
	else
	if (countenemy==MAXSYSTEMS)
		{
			SendaMessage("Enemy has captured ten systems");
			checkfleets=1;
	}
	
	if (countpl==0) {
			SendaMessage("You have lost all your systems");
			checkfleets=1;	
	}
	
	if (countenemy==0) {
			SendaMessage("Enemy has lost all their systems");
			checkfleets=1;	
	}	

	if (checkfleets) { /* Check if any fleets in flight, if none, game over! */
		checkfleets=0;
		for (i=0;i<MAXFLEETS;i++)
			if (fleets[i].turns >0 && fleets[i].numships >0)
				checkfleets++;
		if (checkfleets==0)
		{
			if (countpl==MAXSYSTEMS || countenemy==0)
				{
					SendaMessage("You have Won!");
					GameOver-=1;
			}
			else
				if (countenemy == MAXSYSTEMS || countpl ==0) {
				    SendaMessage("The Enemey player has won. Tough luck");
					GameOver=1;
				}
		}

	}
}

/* find empty slot (any where  fleet.numships == 0) and put details there */

int AddFleet(int player,int numships,int source,int target) {
	int sx,sy,tx,ty,fi,fleetindex;
	fi =-1;
	for (fleetindex=0;fleetindex<MAXFLEETS;fleetindex++)
		if (fleets[fleetindex].numships == 0)
		{
			fi = fleetindex;
			break;
		}
	if (fi==-1) {
	   SendaMessage("No spare fleets, try in a turn or two");
		return 0;
	}
	
	sx = galaxy[source].x;
	sy = galaxy[source].y;
	tx = galaxy[target].x;
	ty = galaxy[target].y;
	fleets[fi].from=source;
	fleets[fi].to=target;
	fleets[fi].turns = distance(sx-tx,sy-ty);
	fleets[fi].owner=player;
	fleets[fi].numships = numships;

	galaxy[source].numships -= numships;
	return 1;
}

/* transfers any ship fleets that have arrived at a friendly system and add them to 
system defences */
void MoveFleetToOrbit(int atsystem) {

	int i,playernum;
	playernum= galaxy[atsystem].owner;
	for (i=0;i< MAXFLEETS;i++) {
		if (fleets[i].to==atsystem && fleets[i].owner==playernum && fleets[i].numships>0)
		{
			galaxy[atsystem].numships += fleets[i].numships;
			fleets[i].turns=0;
			fleets[i].numships=0;
			fleets[i].to=0;
		}
	}
}

/* called once per turn */ 
int MoveFleets() {
	int i=0;
	int destination;
	int numfights =0;
	for (i=0;i<MAXFLEETS;i++) {
		if (fleets[i].numships >0) {
			{
				fleets[i].turns--;
				if (fleets[i].turns==0) { /* arrived */
					destination = fleets[i].to;
					if (galaxy[destination].owner== fleets[i].owner) 
					{  /* we own system so reinforce it */
						MoveFleetToOrbit(destination);
					}
					else
					{/* fight, fight, fight! */
						fleets[i].turns= FIGHTMARKER; /* special marker for fights, do fights later */					
						numfights++;
					}
				}
			}
		}
	}
	return numfights;
}

/* forces playernum (0 or 9) to retreat to system they came from */
void retreat(int playernum,int asystem) {
	int i,temp,from,xf,yf,xt,yt;
	for (i=0;i< MAXFLEETS;i++) {
		if (fleets[i].numships >0 && fleets[i].turns== FIGHTMARKER && 
			fleets[i].to==asystem && fleets[i].owner==playernum) {
			if (fleets[i].numships >0) {
				temp = fleets[i].to;
				from=fleets[i].from;
				fleets[i].to=from;
				fleets[i].from = temp;
				xt = galaxy[temp].x;
				yt = galaxy[temp].y;
				xf = galaxy[from].x;
				yf = galaxy[from].y;
				fleets[i].turns=distance(xt-xf,yt-yf);
			}
		}
	}
}

/* This removes one ship at a time from all fleets in battles at a system for one player */
void RemoveCasualties(int playernum,int casualties,int atsystem) {
	int i,f0,f9,fs,totalships;
	message tempmsg;
	f0=0;
	f9=0;
	fs=0;
	while (casualties>0) {
		totalships =0;
		for (i=0;i<MAXFLEETS;i++) {
			if (fleets[i].turns= FIGHTMARKER && fleets[i].to==atsystem && 
				fleets[i].owner==playernum && fleets[i].numships >0)
					{
						--casualties;
						--fleets[i].numships;
						if (fleets[i].numships<=0)
						{							
							if (playernum==0) {
								sprintf(tempmsg,"Fleet %i lost, attacking system %i",i,
									fleets[i].to);
								SendaMessage(tempmsg);
							}
							fleets[i].to=0;
						    fleets[i].turns=0;		
							fleets[i].numships=0;

						}
						totalships += fleets[i].numships;
					}
			}	/* for */	
		if (totalships==0)
			break;
	}
}

int doOneonOne(int fleet0,int fleet9,int atsystem) {
int p0,p9,cas0,cas9,tcas0,tcas9,f0,f9,factor,i;
  p0=50;
  p9=50;
  if (fleet0>fleet9) 
	{
		factor = fleet0/fleet9;
		if (factor >= 2) p0 +=10;
		if (factor >= 3) p0 +=10;
		if (factor >= 4) p0 +=10;    
    }
  else
  {
		factor = fleet9/fleet0;
		if (factor >= 2) p9 +=10;
		if (factor >= 3) p9 +=10;
		if (factor >= 4) p9 +=10;    
  }
  tcas0=0;
  tcas9=0;
  f0=fleet0;
  f9=fleet9;
  while (fleet0 >0 && tcas0*100/f0 <50 && fleet9 >0 && tcas9*100/f9 < 50) 
  {
	cas9 =0;
	for (i=0;i<fleet0;i++) 
		if (Random(100)<= p0)
			cas9++;
	cas0 =0;
	for (i=0;i<fleet9;i++) 
		if (Random(100)<= p9)
			cas0++;
    tcas0 += cas0;
	tcas9 += cas9;
	fleet0 -=cas0;
	fleet9 -=cas9;
	if (fleet0<0) fleet0=0;
	if (fleet9<0) fleet9 =0;
  }	
  RemoveCasualties(0,tcas0,atsystem);
  RemoveCasualties(9,tcas9,atsystem);
  if (tcas0*100/f0>50)
	  return 9; /* - means 0 won 9 lost */
  else
	  return  0; /* + means 9 won 0 lost */
}

/* NumShips - add up all ships at a system for a player */
int GetNumShips(int playernum,int atsystem) {
	int i,numships;
	numships=0;
	for (i=0;i<MAXFLEETS;i++) 
		if (fleets[i].turns= FIGHTMARKER && fleets[i].to==atsystem && 
				fleets[i].owner==playernum )
				numships += fleets[i].numships;
    return numships;
}

/* */
void SendHomeFleets(int playernum,int atsystem) {
	int i,tx,ty,hx,hy,home;
	message tempmsg;
	for (i=0;i<MAXFLEETS;i++) 
		if (fleets[i].turns= FIGHTMARKER && fleets[i].to==atsystem && 
			fleets[i].owner==playernum && fleets[i].numships>0)
		{		
			
			home=fleets[i].from;
			tx=galaxy[atsystem].x;
			ty=galaxy[atsystem].y;			
			hx=galaxy[home].x;
			hy=galaxy[home].y;
			fleets[i].to= home;
			fleets[i].from= atsystem;
			fleets[i].turns= distance(tx-hx,ty-hy);
			sprintf(tempmsg,"  Fleet %i lost against system %i.  %i ships back to System %i",i,
				atsystem,fleets[i].numships,home);
			SendaMessage(tempmsg);
		}
}

/* This handles a fight at a system between a player (0 or 9)
and the system fletp = nums of ships */
int AttackSystem(int playernum,int fleetp, int atsystem) {
	int pp,ps,casp,cass,tcass,tcasp,factor,i,fleetsys;
	message tempmsg;
  pp=50; /* Prob% of player's ships destroying system  ships */
  ps=60; /* Prob% of system's ships destroying player's ship */
  fleetsys= galaxy[atsystem].numships;
  if (fleetsys >0 && fleetp>fleetsys)  /* work out odds improvement */
	{
		factor = fleetp/fleetsys;
		if (factor >= 2) pp +=10; /* 2:10 + 10% */
		if (factor >= 3) pp +=10; /* 3:1  + 10% */
		if (factor >= 4) pp +=10; /* 4:1  + 10% */   
    }
  else
  {
		factor = fleetsys/fleetp;
		if (factor >= 2) ps +=10;
		if (factor >= 3) ps +=10;
		if (factor >= 4) ps +=10;    
  }
  tcasp=0; /* total cas of player */
  tcass=0; /* total cas of system */

  /* fight continues while players fleet is not destroyed (fleetp != 0)
   and players fleet has less than 50% casualties and system ships not destroyed */
  while (fleetp > 0 && (tcasp*100/fleetp <50) && (fleetsys >0)) 
  {
	cass =0;
	for (i=0;i<fleetp;i++) 
		if (Random(100)<= pp)
			cass++; /* how many system ships desytoyed this round */
	casp =0;
	for (i=0;i<fleetsys;i++) 
		if (Random(100)<= ps) /* how many players ships desytoyed this round */
			casp++;
    tcasp += casp; /* add this rounds casulaties to total (player)*/
	tcass += cass; /* add this rounds casulaties to total (player)*/
	fleetp -= casp; /* deduct casualties from players ships */ 
	fleetsys -= cass; /*  deduct casualties from systems ships */ 
	if (fleetp<0) /* if negative make zero */
		fleetp=0;
	if (fleetsys<0) /* if negative make zero */
		fleetsys=0;
  }	
  RemoveCasualties(playernum,tcasp,atsystem); /* remove players casualties from all fleets at syste, */
  galaxy[atsystem].numships -= tcass;    /* remove system casulaties */
  if (galaxy[atsystem].numships<0)   /* if negative make zero */
	  galaxy[atsystem].numships =0;   
  if (galaxy[atsystem].numships==0) /* system captured if no ships left */
  {
	  galaxy[atsystem].owner= playernum;
	  MoveFleetToOrbit(atsystem);  /* disband fleets, now system ships  */
	  CheckGameOver();
	  if (playernum==0) 
		  {
			  SendaMessage2("You captured system ",atsystem);
			  return 0;
	  }
	  else
	  {
		  SendaMessage2("Enemy captured system ",atsystem);
		  return 9;
	  }
  }
  {
	  if (playernum==0) 
		  SendaMessage2("Enemy failed to capture system ",atsystem);
	   else
		  SendaMessage2("Enemy failed to capture system ",atsystem);
	  sprintf(tempmsg,"System %i lost %i ships",atsystem,tcass);
	  SendaMessage(tempmsg);
	  SendHomeFleets(playernum,atsystem);
  }
  return -1;
}

/*
Possible three way fight if player and enemy fleets arrive on same turn.
if fleet0 and fleet9 have ships then they fight, winner then attack the system
if only one of fleet0 or Fleet9 present then they fight fleet system
*/

int fight(int fleet0,int fleet9,int atsystem) {
	int lostpl;
	if (fleet0 >0 && fleet9 >0) {
		lostpl=doOneonOne(fleet0,fleet9,atsystem); /* winner is 0 or 9 */
		retreat(lostpl,atsystem);		
		SendaMessage2("You fought the enemy at system ",atsystem);
		if (lostpl==0)
			{
				fleet0=0;
				SendaMessage("   You lost ");
				fleet9 = GetNumShips(9,atsystem);
		}
		else
			{
				fleet9=0;
				SendaMessage("   You won");
				fleet0 = GetNumShips(0,atsystem);
		}
	}
  if (fleet0 >0)
	 return AttackSystem(0,fleet0,atsystem);
  else
	 return AttackSystem(9,fleet9,atsystem);
}

/* handles all fights and reinforcements, between player 0 and enemy 9 */
void DoFights() {
	int i,f0,f9;
	f0=0;
	f9=0;
	for (i=0;i<MAXSYSTEMS;i++) {
		f0= GetNumShips(0,i);
		f9= GetNumShips(9,i);
		if (f0 >0 || f9>0)
			fight(f0,f9,i);
	}
}

/* index of nearest galaxy not owned by player 9*/
int findNearestSystem(int atsystem) {
	int dist,sdist,ni,sx,sy,nsx,nsy,i;
	sx=galaxy[atsystem].x;	
	sy=galaxy[atsystem].y;
	sdist = 99;
	ni=-1;
	for (i=0;i< MAXSYSTEMS;i++) {
		if (galaxy[i].owner != 9) 
		{
			nsx= galaxy[i].x;			
			nsy= galaxy[i].y;
			dist = distance(sx-nsx,sy-nsy);
			if (dist < sdist) {
				sdist = dist;
				ni = i;
			}
		}
	}
	return ni;
}

/* Simple AI. Send half from any system over 30 strong to nearest system */
void EnemyOrders() {
	int i,numships,target;
	for (i=0;i<MAXSYSTEMS;i++)
		if (galaxy[i].owner==9 && galaxy[i].numships > 30) {
			target = findNearestSystem(i);
			if (target != -1)
			{
				numships = galaxy[i].numships/2;
				galaxy[i].numships -= numships;
				AddFleet(9,numships,i,target);
				SendaMessage2("Enemy launched fleet to system ",target);
			}
		}
}
/* adds new ships at each system. Unowned systesm are capped at 250, owned at 999 
This is called once per turn */
void BuildFleets() {
	int i,numshipsbuilt;
	for (i=0;i<MAXSYSTEMS;i++)
	{
		numshipsbuilt = galaxy[i].numships/10;	
		if (numshipsbuilt==0)  /* always build 1 ship */
			numshipsbuilt=1;
		if (numshipsbuilt > 15)
			numshipsbuilt=15;
		galaxy[i].numships += numshipsbuilt;
		if (galaxy[i].numships > 999)
		{
			galaxy[i].numships=999; /* maximum cap */
		}
		if (galaxy[i].owner==-1 && galaxy[i].numships > 250)
		{
			galaxy[i].numships=250; /* maximum cap */
		}
	}
}

/* display a message for a second then remove it */
void DisplayTimedMessage(char * msg,int line) {
	gotoxy(0,line);
	printf(msg);
    waitms(1000); /* waits 1000 ms, ie 1 sec */
	clr(line);
}

/* if a/A was pressed, this assembles fleets at all systems and sends them to the target,
  it builds up each fleet one ship at a time so we don't try get them all from one system*/
void BuildFleetsAtAllSystems(int numships,int target) {
	int anyleft,i;
	int fleetsize[MAXSYSTEMS];

	for (i=0;i<MAXSYSTEMS;i++)
		fleetsize[i]=0;
	while (numships>0 ) {
		anyleft =0;
		for (i=0;i<MAXSYSTEMS;i++) {
			if (galaxy[i].owner==0 && galaxy[i].numships >0)
			{
				fleetsize[i]++;
				galaxy[i].numships--;
				anyleft += galaxy[i].numships;	
				numships--;
			}
		}
		if (anyleft==0)
			break;
	}
	for(i=0;i<MAXSYSTEMS;i++) 
		if (fleetsize[i]>0) {
			galaxy[i].numships= fleetsize[i]; /* needed as AddFleet deducts ships */
			AddFleet(0,fleetsize[i],i,target);
		}

}

/* processes the command presed which is 0-9 or a/A */
void Process_Command(char c) {
	char t;
	int source,target,numships;
	gotoxy(0,CMDLINE+1);printf("Target System: Press 0-9: ");
	t=_getch();
	printf("%c",t);
	if (t >='0' && t <='9' && t != c) {
		if (c=='a' || c=='A')
			source =99;
		else
			source = (int)(c-'0');
		target = (int)(t-'0');
		if (source !=99 && galaxy[source].owner!=0) {
			sprintf(messagebuffer,"You don't own system %i",source);
			DisplayTimedMessage(messagebuffer,CMDLINE+2);
			clr(CMDLINE+1);
			return;		
		}
		gotoxy(0,CMDLINE+2);printf("How Many Ships:");numships=GetInput();
		if (numships >-1 )
		  {
			  if (source != 99 && numships > galaxy[source].numships)
			  {
				  sprintf(messagebuffer,"Can't send %i ships. Order reduced to %i.",numships,galaxy[source].numships);
				  DisplayTimedMessage(messagebuffer,CMDLINE+3);
				  numships= galaxy[source].numships;
			  }
			  if (source == 99) {
				BuildFleetsAtAllSystems(numships,target);
			  }
			  else
			  {
			    sprintf(messagebuffer,"Move %d from %d to %d",numships,source,target);
    		    DisplayTimedMessage(messagebuffer,CMDLINE+3);
			    AddFleet(0,numships,source,target);
			  }
		}
		clr(CMDLINE+1);
		clr(CMDLINE+2);
	}
	
}

/* This waits for SECSPERTURN seconds for input, 
and returns if no command in that time. While waiting, if the key isn't pressed
it calls CheckMessage() to pump the message queue */
void GetandProcessOrders() {
	clock_t timeinsecs;
	char c;
	timeinsecs = clock()+(SECSPERTURN*CLOCKS_PER_SEC);	/* 5 Seconds initially but change SECSPERTURN */
	gotoxy(0,CMDLINE);printf("Move Command: Press 0-9 or A(ll):");
	while (clock() < timeinsecs) {

		if (_kbhit())  /* Key pressed */
		{
			c = _getch();
			if (c=='\0')
				c=_getch();
			if (c==27)	{
					GameOver=1;
					return;
			}
			
			if ((c>='0' && c <='9') || (c=='a' || c=='A')) {
				{
					
					Process_Command(c);
					gotoxy(0,CMDLINE);printf("Move Command: Press 0-9 or A(ll): ");
				}
			}
			else
			{
				printf("%c",7);
			}
		}
		else
			CheckMessages();
	}
}

/* The main game code with game loop */
int main(int argc, char * argv[])
{
#ifndef CC386
	COORD scrSize;	
	scrSize=SetScreenSize(WIDTH,HEIGHT);	
#endif
	ClrScr();
	InitData();
	GenMapSystems();	
	DisplayDistances();
	DisplayMessageArea();
	ShowTurn();
	gotoxy(0,49);
	while (!GameOver) {	/* game loop */		
		DisplayMap();
		DisplayFleets();		
		GetandProcessOrders();
		EnemyOrders();
		if (MoveFleets())
			DoFights();

		BuildFleets();		
		ShowTurn();
	};
	SendaMessage("Game Over - Closing down...");
	/* Give game a chance to display all messages */
	while (CheckMessages()==1) {
		waitms(500);
	}
	waitms(3*1000);
	return 0;
};
  1.6 27-jan-2013 added 0 to first return in checkmessages
*/

#include <time.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h> /* needed for _getch() */
#include <math.h>
#include <Windows.h>

/* #define CC386 /* comment out if not compiling with CC386 */

/* data structures  */
struct fleet {
	int from;
	int to;
	int turns;
	int numships;
	int owner; /* (o or 1) */
};

struct system {
	int x,y;
	int numships;
	int owner;
};

/* defines a message type */
typedef char message[120];

/* game data */
#define WIDTH 80
#define HEIGHT 50
#define MAXLEN 4
#define MAXFLEETS 100
#define MAXSYSTEMS 10
#define FIGHTMARKER 999
#define SECSPERTURN 5
#define MSGLINE 25
#define CMDLINE 45

struct system galaxy[MAXSYSTEMS];
struct fleet fleets[MAXFLEETS];
char layout[5][5];
message messagebuffer;
message messages[100];
message spaces;
int msgindex;
int msghead,msgtail;
int GameOver;
int Turn;
clock_t lasttick;

/* returns a number between 1 and max */
int Random(int max) {
	return (rand() % max) + 1;
}

/* returns the index in the galaxy for the sysm at x,y */
int getsystem(int x,int y) {
	int i;
	for (i=0;i<10;i++)
		if (galaxy[i].x==x && galaxy[i].y==y){
			return i;
		}
	return -1; /* should never get here! */
}

/* returns a + for systems owned by the player, - for enemy and u for unowned */
char owner(int x,int y) {
	int i= getsystem(x,y);
	if (i != -1)
	  {
		if (galaxy[i].owner==0)
			return '+';
		else
			if (galaxy[i].owner==1)
			return '-';
			else
			return 'u';
		}
	return ' '; /* should never get here! */
}

/* moves the cursor to x,y x- across, y = down */

#ifndef CC386
void gotoxy( short x, short y ) 

{ 
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE) ; 
    COORD position = { x, y } ; 
     
    SetConsoleCursorPosition( hStdout, position ) ; 
}  

/* comment this function out with CC386 */
COORD GetConsoleSize() 
{ 
    HANDLE hnd = GetStdHandle(STD_OUTPUT_HANDLE) ; 
    return GetLargestConsoleWindowSize(hnd); 
}  

/* comment this function out with CC386 */
COORD SetScreenSize(short x,short y) {
	COORD result; 
	HANDLE hnd;
	result.X=0;
	result.Y=0;
    hnd= GetStdHandle(STD_OUTPUT_HANDLE) ; 
    SetConsoleDisplayMode( hnd,CONSOLE_WINDOWED_MODE,&result);
    return result;
}
#endif


/* clears the screen area */
void ClrScr() {
	COORD c;
	DWORD NumWr;
	HANDLE hnd = GetStdHandle(STD_OUTPUT_HANDLE) ;
	c.X=0;
	c.Y=0;
     
    FillConsoleOutputCharacter(hnd,' ',WIDTH*HEIGHT,c,&NumWr);
	/* FillConsoleOutputAttribute(hnd,0x88,4000,c,&NumWr);  for setting color*/
}

/* returns distance as int. Values are always in the range 1-6 */
int distance(int x,int y) {
   int distsqr= (x*x) + (y*y);
   return (int)(sqrt((float)distsqr)+0.5);
}

/* This initialises a single system */
void InitSystem(int systemindex,int x,int y,int shipnums,int owner) {
		galaxy[systemindex].x=x;		
		galaxy[systemindex].y=y;
		galaxy[systemindex].numships = shipnums;
		galaxy[systemindex].owner = owner;
		layout[x][y]=(char)(systemindex+48);
}

/* Generates a random layout of systems (apart from systems 0 and 9 which are always fixed.
This also sets up the number of ships at aeach system */
void GenMapSystems() {
	int i,x,y;

	for (x=0;x<5;x++)
	for (y=0;y<5;y++) {
		layout[x][y]=' ';
	}

	InitSystem(0,0,0,50,0);
	InitSystem(9,4,4,50,9);

	/* Find an empty space for remaining 8 systems*/
	for (i=1;i<=8;i++) {
		do {
			x= Random(5)-1;
			y= Random(5)-1;
		}
		while (layout[x][y] !=' ');
	   InitSystem(i,x,y,15,-1);
	}

}

/* Boxes off the area for messages to appear in */
void DisplayMessageArea(){
gotoxy(0,MSGLINE);printf(   "============================= Messages =============================");
gotoxy(0,MSGLINE+18);printf("====================================================================");
}

/* return 1 if one second passed since last lasttick */
int onesecpassed() {
	clock_t tick = clock();
	if (tick-lasttick > CLOCKS_PER_SEC)
		{
			lasttick = tick;
			return 1;
	}
	else
		return 0;
}

void DisplayMap() {
int x,y;
gotoxy(0,5);printf("Map\n\r");
for (y=0;y<5;y++) {
	printf("   ");
	for (x=0;x<5;x++) {
		if (layout[x][y]==' ')
			printf(" .  ");
		else
			printf(" %c%c ",layout[x][y],owner(x,y));
	}
	
	printf("\n\r");
   }
}

void DisplayDistances() {
int x,y,sx,sy,sx2,sy2;
gotoxy(0,12);printf("System Distances\n\r");
printf("  To   1  2  3  4  5  6  7  8  9\n\r");
printf("     ----------------------------\n\r");
for (y=0;y<9;y++) {
	printf("      ");
	sx = galaxy[y].x;
	sy = galaxy[y].y;
	for (x=1;x<10;x++) {
	    if (x>y)
		{
			sx2 = galaxy[x].x;
			sy2 = galaxy[x].y;
			printf(" %c ",(char)(distance(sx-sx2,sy-sy2)+'0'));
		 }
		else
			printf("   ");
	}
	printf("| %2d\n\r",y);
   }
}

/* messages go in a 100 x 100 message buffer array with msgtail and msghead
messages are added using the tail and displayed from the msghead */
void SendaMessage(char * text) {
  sprintf(messages[msgtail],"%i %s",Turn,text);
  msgtail++;
  if (msgtail == 100)
	  msgtail=0;
}

/* writes a message with a single int parameter */
void SendaMessage2(char * msgtext,int x) {
  char buffer[100];
  sprintf(buffer,"%s %i",msgtext,x);
  SendaMessage(buffer);
}

/* initializes all the game data in one place */
void InitData() {
	int i;
	for (i=0;i< MAXFLEETS;i++)
		fleets[i].numships=0;
	for(i=0;i<sizeof(message);i++)
		spaces[i]=' ';
	spaces[sizeof(message)-1]='\0';
	msgindex=0;
	msghead=0;
	msgtail=0;
	GameOver=0;
	srand((int)time(NULL));
	Turn=1;
	lasttick = clock();
}

/* totals up how many player's ships are on the way to the specified system */
int shipsSent(int tosystem) {
	int i,total;
	total=0;
	for (i=0;i<MAXFLEETS;i++)
		if (fleets[i].to==tosystem && fleets[i].numships >0 && fleets[i].owner==0)
			total+= fleets[i].numships;
	return total;
}

/* calculates the soones arrival time of any fleet at a system */
int turnstogo(int tosystem) {
	int i,ttg;
	ttg = 99;
	for (i=0;i<MAXFLEETS;i++)
	{
		if (fleets[i].to==tosystem && fleets[i].numships >0 && fleets[i].owner==0)
			{
				if (fleets[i].turns<ttg)
					ttg= fleets[i].turns;
				else
					if (fleets[i].turns= FIGHTMARKER)
						ttg = 0;
		}
	}
	return ttg;
}

void DisplayFleets() {
	int i,owner,ttg;
	char text[20];
	gotoxy(45,13);printf("System(Own) Ships Sent(Turns)");
	for (i=0;i<MAXSYSTEMS;i++) {
	  gotoxy(45,14+i);
	  owner = galaxy[i].owner;
	  if (owner==-1 )
		strcpy(text,"u");
	  else
		  _snprintf(text,5,"%i",owner);
	  printf("%2i (%3s)    %3i   %3i",i,text,galaxy[i].numships,shipsSent(i));
	  ttg = turnstogo(i);
	  if (ttg!= 99)
		  printf("(%i)  ",ttg); 
	  else
		  printf("     ");
	}
}

/* clears line# in the display */
void clr(int line) {
	int i;
	gotoxy(0,line);
	for (i=0;i<WIDTH;i++)
	{
		printf(" ");
	}
}

/* wait for numms (millisecs) */
void waitms(int numms) {
	clock_t until;
	until = clock()+(numms*1000/CLOCKS_PER_SEC);	/* 1,2,3...		*/
	while (clock() < until) {
		if (_kbhit())
			break;
	}
}

/* displays the turn number and adds 1 to it */
void ShowTurn() {
	gotoxy(45,5);	
	SendaMessage2("Turn ",Turn);
	printf("Turn %d",Turn++);

}

/* handles input chars 0-9, backspace and return */
int GetInput() {
	char * back ="\b \b";
	char buffer[MAXLEN+1]; /* max 4 digits */
	char key;
	int result=0;
	int buflen=0;
	int hitreturn=0;
	buffer[0]='\0';
	do {
		key=_getch();
		if (key==27)
			return -1;
		buflen=strlen(buffer);
		if ((buflen < MAXLEN && key >='0' && key <='9') || 
			(buflen >0 && (key== 8 || key==13)))
		{
			  if (key ==13)
				  hitreturn=1;
			  else
				if (key==8)
				{
					buffer[--buflen]='\0';
					printf("%s",back);
					
				}
				else
				{
					buffer[buflen++]=key;
					buffer[buflen]='\0';				
					printf("%c",key);
				}
		}
	}
     while (!hitreturn);
  return atoi(buffer);
}

/* Every time this is called, it checks if one second passed and if not 
it returns. It's called from the keyboard input loop when no key is pressed. 
The message display is 15 lines of messages that scroll up.
Messages are written into a 100 line buffer using msgtail as the index 
into the 100 lines to write the message. Then msghead follows msgtail and is where 
messages are displayed from. The tricky bits are
1). Making sure both msgtail wrap round (at 100 they become 0) and
2). When less than 15 lines of messages, write spaces (only happens at start)
*/

int CheckMessages() {
	int i,nummsgs,numbl,j,line;
	if (!onesecpassed())
		return 0;
    line = MSGLINE+1;
	nummsgs=0;
	if (msghead != msgtail) {
		if (msghead < msgtail)
			nummsgs =  (msgtail - msghead);
		else
			nummsgs = (msgtail+100-msghead);
	}
	else
	  return 0; /* no messages */
	if (nummsgs < 15) {
		numbl = 15-nummsgs;
		for(i=0;i<numbl;i++){
			gotoxy(0,line+i);
			printf("%66s",spaces);
		}
		j=msghead;
		for (i=numbl;i<16;i++)
		{			
			gotoxy(0,line+i);
			printf("%66s",spaces);			
			gotoxy(0,line+i);
			printf(messages[j++]);
		}

	}
	else
	{		/* don't move msghead until all message space is full */
		j=msghead++;
		if (msghead >=100)
			msghead =0; /* wraps around */
		for (i=0;i<16;i++)
		{						
			gotoxy(0,line+i);
			printf(spaces);	
			gotoxy(0,line+i);
			printf(messages[j++]);
		}
	}
	return 1; /* Messages scrolled */ 
}


void CheckGameOver() {
	int i,countpl,countenemy,checkfleets;
	checkfleets=0;
	countpl=0;
	countenemy=0;
	for (i=0;i<MAXSYSTEMS;i++)
		if (galaxy[i].owner==0)
			countpl++;
		else
		if (galaxy[i].owner==9)
			countenemy++;
	if (countpl==MAXSYSTEMS)
		{
			SendaMessage("You have captured ten systems");
			checkfleets=1;
	}
	else
	if (countenemy==MAXSYSTEMS)
		{
			SendaMessage("Enemy has captured ten systems");
			checkfleets=1;
	}
	
	if (countpl==0) {
			SendaMessage("You have lost all your systems");
			checkfleets=1;	
	}
	
	if (countenemy==0) {
			SendaMessage("Enemy has lost all their systems");
			checkfleets=1;	
	}	

	if (checkfleets) { /* Check if any fleets in flight, if none, game over! */
		checkfleets=0;
		for (i=0;i<MAXFLEETS;i++)
			if (fleets[i].turns >0 && fleets[i].numships >0)
				checkfleets++;
		if (checkfleets==0)
		{
			if (countpl==MAXSYSTEMS || countenemy==0)
				{
					SendaMessage("You have Won!");
					GameOver-=1;
			}
			else
				if (countenemy == MAXSYSTEMS || countpl ==0) {
				    SendaMessage("The Enemey player has won. Tough luck");
					GameOver=1;
				}
		}

	}
}

/* find empty slot (any where  fleet.numships == 0) and put details there */

int AddFleet(int player,int numships,int source,int target) {
	int sx,sy,tx,ty,fi,fleetindex;
	fi =-1;
	for (fleetindex=0;fleetindex<MAXFLEETS;fleetindex++)
		if (fleets[fleetindex].numships == 0)
		{
			fi = fleetindex;
			break;
		}
	if (fi==-1) {
	   SendaMessage("No spare fleets, try in a turn or two");
		return 0;
	}
	
	sx = galaxy[source].x;
	sy = galaxy[source].y;
	tx = galaxy[target].x;
	ty = galaxy[target].y;
	fleets[fi].from=source;
	fleets[fi].to=target;
	fleets[fi].turns = distance(sx-tx,sy-ty);
	fleets[fi].owner=player;
	fleets[fi].numships = numships;

	galaxy[source].numships -= numships;
	return 1;
}

/* transfers any ship fleets that have arrived at a friendly system and add them to 
system defences */
void MoveFleetToOrbit(int atsystem) {

	int i,playernum;
	playernum= galaxy[atsystem].owner;
	for (i=0;i< MAXFLEETS;i++) {
		if (fleets[i].to==atsystem && fleets[i].owner==playernum && fleets[i].numships>0)
		{
			galaxy[atsystem].numships += fleets[i].numships;
			fleets[i].turns=0;
			fleets[i].numships=0;
			fleets[i].to=0;
		}
	}
}

/* called once per turn */ 
int MoveFleets() {
	int i=0;
	int destination;
	int numfights =0;
	for (i=0;i<MAXFLEETS;i++) {
		if (fleets[i].numships >0) {
			{
				fleets[i].turns--;
				if (fleets[i].turns==0) { /* arrived */
					destination = fleets[i].to;
					if (galaxy[destination].owner== fleets[i].owner) 
					{  /* we own system so reinforce it */
						MoveFleetToOrbit(destination);
					}
					else
					{/* fight, fight, fight! */
						fleets[i].turns= FIGHTMARKER; /* special marker for fights, do fights later */					
						numfights++;
					}
				}
			}
		}
	}
	return numfights;
}

/* forces playernum (0 or 9) to retreat to system they came from */
void retreat(int playernum,int asystem) {
	int i,temp,from,xf,yf,xt,yt;
	for (i=0;i< MAXFLEETS;i++) {
		if (fleets[i].numships >0 && fleets[i].turns== FIGHTMARKER && 
			fleets[i].to==asystem && fleets[i].owner==playernum) {
			if (fleets[i].numships >0) {
				temp = fleets[i].to;
				from=fleets[i].from;
				fleets[i].to=from;
				fleets[i].from = temp;
				xt = galaxy[temp].x;
				yt = galaxy[temp].y;
				xf = galaxy[from].x;
				yf = galaxy[from].y;
				fleets[i].turns=distance(xt-xf,yt-yf);
			}
		}
	}
}

/* This removes one ship at a time from all fleets in battles at a system for one player */
void RemoveCasualties(int playernum,int casualties,int atsystem) {
	int i,f0,f9,fs,totalships;
	message tempmsg;
	f0=0;
	f9=0;
	fs=0;
	while (casualties>0) {
		totalships =0;
		for (i=0;i<MAXFLEETS;i++) {
			if (fleets[i].turns= FIGHTMARKER && fleets[i].to==atsystem && 
				fleets[i].owner==playernum && fleets[i].numships >0)
					{
						--casualties;
						--fleets[i].numships;
						if (fleets[i].numships<=0)
						{							
							if (playernum==0) {
								sprintf(tempmsg,"Fleet %i lost, attacking system %i",i,
									fleets[i].to);
								SendaMessage(tempmsg);
							}
							fleets[i].to=0;
						    fleets[i].turns=0;		
							fleets[i].numships=0;

						}
						totalships += fleets[i].numships;
					}
			}	/* for */	
		if (totalships==0)
			break;
	}
}

int doOneonOne(int fleet0,int fleet9,int atsystem) {
int p0,p9,cas0,cas9,tcas0,tcas9,f0,f9,factor,i;
  p0=50;
  p9=50;
  if (fleet0>fleet9) 
	{
		factor = fleet0/fleet9;
		if (factor >= 2) p0 +=10;
		if (factor >= 3) p0 +=10;
		if (factor >= 4) p0 +=10;    
    }
  else
  {
		factor = fleet9/fleet0;
		if (factor >= 2) p9 +=10;
		if (factor >= 3) p9 +=10;
		if (factor >= 4) p9 +=10;    
  }
  tcas0=0;
  tcas9=0;
  f0=fleet0;
  f9=fleet9;
  while (fleet0 >0 && tcas0*100/f0 <50 && fleet9 >0 && tcas9*100/f9 < 50) 
  {
	cas9 =0;
	for (i=0;i<fleet0;i++) 
		if (Random(100)<= p0)
			cas9++;
	cas0 =0;
	for (i=0;i<fleet9;i++) 
		if (Random(100)<= p9)
			cas0++;
    tcas0 += cas0;
	tcas9 += cas9;
	fleet0 -=cas0;
	fleet9 -=cas9;
	if (fleet0<0) fleet0=0;
	if (fleet9<0) fleet9 =0;
  }	
  RemoveCasualties(0,tcas0,atsystem);
  RemoveCasualties(9,tcas9,atsystem);
  if (tcas0*100/f0>50)
	  return 9; /* - means 0 won 9 lost */
  else
	  return  0; /* + means 9 won 0 lost */
}

/* NumShips - add up all ships at a system for a player */
int GetNumShips(int playernum,int atsystem) {
	int i,numships;
	numships=0;
	for (i=0;i<MAXFLEETS;i++) 
		if (fleets[i].turns= FIGHTMARKER && fleets[i].to==atsystem && 
				fleets[i].owner==playernum )
				numships += fleets[i].numships;
    return numships;
}

/* */
void SendHomeFleets(int playernum,int atsystem) {
	int i,tx,ty,hx,hy,home;
	message tempmsg;
	for (i=0;i<MAXFLEETS;i++) 
		if (fleets[i].turns= FIGHTMARKER && fleets[i].to==atsystem && 
			fleets[i].owner==playernum && fleets[i].numships>0)
		{		
			
			home=fleets[i].from;
			tx=galaxy[atsystem].x;
			ty=galaxy[atsystem].y;			
			hx=galaxy[home].x;
			hy=galaxy[home].y;
			fleets[i].to= home;
			fleets[i].from= atsystem;
			fleets[i].turns= distance(tx-hx,ty-hy);
			sprintf(tempmsg,"  Fleet %i lost against system %i.  %i ships back to System %i",i,
				atsystem,fleets[i].numships,home);
			SendaMessage(tempmsg);
		}
}

/* This handles a fight at a system between a player (0 or 9)
and the system fletp = nums of ships */
int AttackSystem(int playernum,int fleetp, int atsystem) {
	int pp,ps,casp,cass,tcass,tcasp,factor,i,fleetsys;
	message tempmsg;
  pp=50; /* Prob% of player's ships destroying system  ships */
  ps=60; /* Prob% of system's ships destroying player's ship */
  fleetsys= galaxy[atsystem].numships;
  if (fleetsys >0 && fleetp>fleetsys)  /* work out odds improvement */
	{
		factor = fleetp/fleetsys;
		if (factor >= 2) pp +=10; /* 2:10 + 10% */
		if (factor >= 3) pp +=10; /* 3:1  + 10% */
		if (factor >= 4) pp +=10; /* 4:1  + 10% */   
    }
  else
  {
		factor = fleetsys/fleetp;
		if (factor >= 2) ps +=10;
		if (factor >= 3) ps +=10;
		if (factor >= 4) ps +=10;    
  }
  tcasp=0; /* total cas of player */
  tcass=0; /* total cas of system */

  /* fight continues while players fleet is not destroyed (fleetp != 0)
   and players fleet has less than 50% casualties and system ships not destroyed */
  while (fleetp > 0 && (tcasp*100/fleetp <50) && (fleetsys >0)) 
  {
	cass =0;
	for (i=0;i<fleetp;i++) 
		if (Random(100)<= pp)
			cass++; /* how many system ships desytoyed this round */
	casp =0;
	for (i=0;i<fleetsys;i++) 
		if (Random(100)<= ps) /* how many players ships desytoyed this round */
			casp++;
    tcasp += casp; /* add this rounds casulaties to total (player)*/
	tcass += cass; /* add this rounds casulaties to total (player)*/
	fleetp -= casp; /* deduct casualties from players ships */ 
	fleetsys -= cass; /*  deduct casualties from systems ships */ 
	if (fleetp<0) /* if negative make zero */
		fleetp=0;
	if (fleetsys<0) /* if negative make zero */
		fleetsys=0;
  }	
  RemoveCasualties(playernum,tcasp,atsystem); /* remove players casualties from all fleets at syste, */
  galaxy[atsystem].numships -= tcass;    /* remove system casulaties */
  if (galaxy[atsystem].numships<0)   /* if negative make zero */
	  galaxy[atsystem].numships =0;   
  if (galaxy[atsystem].numships==0) /* system captured if no ships left */
  {
	  galaxy[atsystem].owner= playernum;
	  MoveFleetToOrbit(atsystem);  /* disband fleets, now system ships  */
	  CheckGameOver();
	  if (playernum==0) 
		  {
			  SendaMessage2("You captured system ",atsystem);
			  return 0;
	  }
	  else
	  {
		  SendaMessage2("Enemy captured system ",atsystem);
		  return 9;
	  }
  }
  {
	  if (playernum==0) 
		  SendaMessage2("Enemy failed to capture system ",atsystem);
	   else
		  SendaMessage2("Enemy failed to capture system ",atsystem);
	  sprintf(tempmsg,"System %i lost %i ships",atsystem,tcass);
	  SendaMessage(tempmsg);
	  SendHomeFleets(playernum,atsystem);
  }
  return -1;
}

/*
Possible three way fight if player and enemy fleets arrive on same turn.
if fleet0 and fleet9 have ships then they fight, winner then attack the system
if only one of fleet0 or Fleet9 present then they fight fleet system
*/

int fight(int fleet0,int fleet9,int atsystem) {
	int lostpl;
	if (fleet0 >0 && fleet9 >0) {
		lostpl=doOneonOne(fleet0,fleet9,atsystem); /* winner is 0 or 9 */
		retreat(lostpl,atsystem);		
		SendaMessage2("You fought the enemy at system ",atsystem);
		if (lostpl==0)
			{
				fleet0=0;
				SendaMessage("   You lost ");
				fleet9 = GetNumShips(9,atsystem);
		}
		else
			{
				fleet9=0;
				SendaMessage("   You won");
				fleet0 = GetNumShips(0,atsystem);
		}
	}
  if (fleet0 >0)
	 return AttackSystem(0,fleet0,atsystem);
  else
	 return AttackSystem(9,fleet9,atsystem);
}

/* handles all fights and reinforcements, between player 0 and enemy 9 */
void DoFights() {
	int i,f0,f9;
	f0=0;
	f9=0;
	for (i=0;i<MAXSYSTEMS;i++) {
		f0= GetNumShips(0,i);
		f9= GetNumShips(9,i);
		if (f0 >0 || f9>0)
			fight(f0,f9,i);
	}
}

/* index of nearest galaxy not owned by player 9*/
int findNearestSystem(int atsystem) {
	int dist,sdist,ni,sx,sy,nsx,nsy,i;
	sx=galaxy[atsystem].x;	
	sy=galaxy[atsystem].y;
	sdist = 99;
	ni=-1;
	for (i=0;i< MAXSYSTEMS;i++) {
		if (galaxy[i].owner != 9) 
		{
			nsx= galaxy[i].x;			
			nsy= galaxy[i].y;
			dist = distance(sx-nsx,sy-nsy);
			if (dist < sdist) {
				sdist = dist;
				ni = i;
			}
		}
	}
	return ni;
}

/* Simple AI. Send half from any system over 30 strong to nearest system */
void EnemyOrders() {
	int i,numships,target;
	for (i=0;i<MAXSYSTEMS;i++)
		if (galaxy[i].owner==9 && galaxy[i].numships > 30) {
			target = findNearestSystem(i);
			if (target != -1)
			{
				numships = galaxy[i].numships/2;
				galaxy[i].numships -= numships;
				AddFleet(9,numships,i,target);
				SendaMessage2("Enemy launched fleet to system ",target);
			}
		}
}
/* adds new ships at each system. Unowned systesm are capped at 250, owned at 999 
This is called once per turn */
void BuildFleets() {
	int i,numshipsbuilt;
	for (i=0;i<MAXSYSTEMS;i++)
	{
		numshipsbuilt = galaxy[i].numships/10;	
		if (numshipsbuilt==0)  /* always build 1 ship */
			numshipsbuilt=1;
		if (numshipsbuilt > 15)
			numshipsbuilt=15;
		galaxy[i].numships += numshipsbuilt;
		if (galaxy[i].numships > 999)
		{
			galaxy[i].numships=999; /* maximum cap */
		}
		if (galaxy[i].owner==-1 && galaxy[i].numships > 250)
		{
			galaxy[i].numships=250; /* maximum cap */
		}
	}
}

/* display a message for a second then remove it */
void DisplayTimedMessage(char * msg,int line) {
	gotoxy(0,line);
	printf(msg);
    waitms(1000); /* waits 1000 ms, ie 1 sec */
	clr(line);
}

/* if a/A was pressed, this assembles fleets at all systems and sends them to the target,
  it builds up each fleet one ship at a time so we don't try get them all from one system*/
void BuildFleetsAtAllSystems(int numships,int target) {
	int anyleft,i;
	int fleetsize[MAXSYSTEMS];

	for (i=0;i<MAXSYSTEMS;i++)
		fleetsize[i]=0;
	while (numships>0 ) {
		anyleft =0;
		for (i=0;i<MAXSYSTEMS;i++) {
			if (galaxy[i].owner==0 && galaxy[i].numships >0)
			{
				fleetsize[i]++;
				galaxy[i].numships--;
				anyleft += galaxy[i].numships;	
				numships--;
			}
		}
		if (anyleft==0)
			break;
	}
	for(i=0;i<MAXSYSTEMS;i++) 
		if (fleetsize[i]>0) {
			galaxy[i].numships= fleetsize[i]; /* needed as AddFleet deducts ships */
			AddFleet(0,fleetsize[i],i,target);
		}

}

/* processes the command presed which is 0-9 or a/A */
void Process_Command(char c) {
	char t;
	int source,target,numships;
	gotoxy(0,CMDLINE+1);printf("Target System: Press 0-9: ");
	t=_getch();
	printf("%c",t);
	if (t >='0' && t <='9' && t != c) {
		if (c=='a' || c=='A')
			source =99;
		else
			source = (int)(c-'0');
		target = (int)(t-'0');
		if (source !=99 && galaxy[source].owner!=0) {
			sprintf(messagebuffer,"You don't own system %i",source);
			DisplayTimedMessage(messagebuffer,CMDLINE+2);
			clr(CMDLINE+1);
			return;		
		}
		gotoxy(0,CMDLINE+2);printf("How Many Ships:");numships=GetInput();
		if (numships >-1 )
		  {
			  if (source != 99 && numships > galaxy[source].numships)
			  {
				  sprintf(messagebuffer,"Can't send %i ships. Order reduced to %i.",numships,galaxy[source].numships);
				  DisplayTimedMessage(messagebuffer,CMDLINE+3);
				  numships= galaxy[source].numships;
			  }
			  if (source == 99) {
				BuildFleetsAtAllSystems(numships,target);
			  }
			  else
			  {
			    sprintf(messagebuffer,"Move %d from %d to %d",numships,source,target);
    		    DisplayTimedMessage(messagebuffer,CMDLINE+3);
			    AddFleet(0,numships,source,target);
			  }
		}
		clr(CMDLINE+1);
		clr(CMDLINE+2);
	}
	
}

/* This waits for SECSPERTURN seconds for input, 
and returns if no command in that time. While waiting, if the key isn't pressed
it calls CheckMessage() to pump the message queue */
void GetandProcessOrders() {
	clock_t timeinsecs;
	char c;
	timeinsecs = clock()+(SECSPERTURN*CLOCKS_PER_SEC);	/* 5 Seconds initially but change SECSPERTURN */
	gotoxy(0,CMDLINE);printf("Move Command: Press 0-9 or A(ll):");
	while (clock() < timeinsecs) {

		if (_kbhit())  /* Key pressed */
		{
			c = _getch();
			if (c=='\0')
				c=_getch();
			if (c==27)	{
					GameOver=1;
					return;
			}
			
			if ((c>='0' && c <='9') || (c=='a' || c=='A')) {
				{
					
					Process_Command(c);
					gotoxy(0,CMDLINE);printf("Move Command: Press 0-9 or A(ll): ");
				}
			}
			else
			{
				printf("%c",7);
			}
		}
		else
			CheckMessages();
	}
}

/* The main game code with game loop */
int main(int argc, char * argv[])
{
#ifndef CC386
	COORD scrSize;	
	scrSize=SetScreenSize(WIDTH,HEIGHT);	
#endif
	ClrScr();
	InitData();
	GenMapSystems();	
	DisplayDistances();
	DisplayMessageArea();
	ShowTurn();
	gotoxy(0,49);
	while (!GameOver) {	/* game loop */		
		DisplayMap();
		DisplayFleets();		
		GetandProcessOrders();
		EnemyOrders();
		if (MoveFleets())
			DoFights();

		BuildFleets();		
		ShowTurn();
	};
	SendaMessage("Game Over - Closing down...");
	/* Give game a chance to display all messages */
	while (CheckMessages()==1) {
		waitms(500);
	}
	waitms(3*1000);
	return 0;
};
