// =======================================================================
// LabWork n. 3.0 (C, CPP)
// <skip>
// <skip>
// -----------------------------------------------------------------------
// Image movements.
// Used library: <none>
// -----------------------------------------------------------------------
// File: lab03.c
// -----------------------------------------------------------------------
//     Compiler: Borland C++ 3.1
//  Application: Dos16 console
// -----------------------------------------------------------------------
// Made date: 25/  X.1999
// Last edit: 25/  X.1999
//     Build: 1
// =======================================================================
#include <math.h>               // sin, cos
#include <time.h>               // time
#include <conio.h>              // getch
#include <stdio.h>
#include <stdlib.h>             // random
#include <process.h>            // exit
#include <graphics.h>
// =======================================================================
// Macros ... DO NOT CHANGE !!!
// -----------------------------------------------------------------------
#define scrWD   (getmaxx()+1)   // screen width
#define scrHG   (getmaxy()+1)   // screen height
#define ddX     scrWD/2         // X center
#define ddY     scrHG/2         // Y center
#define sky(_M) drawstars(0,0,scrWD,scrHG,_M)
#define XCORR   45              // x pos. correction
// -----------------------------------------------------------------------
#define planeWD 105             // WD & HG of air plane
#define planeHG 90
// -----------------------------------------------------------------------
#define MAXSPEED        2
#define MINSPEED        .3
#define MAXANGLE        360
#define MAXK            20
#define MIMK            .005
// =======================================================================
// Constants ... USER CHANGEABLE
// =======================================================================
// Key codes
// -----------------------------------------------------------------------
#define kESC     0x1b            // ESC code
#define kUP              72
#define kDOWN            80
#define kLEFT            75
#define kRIGHT           77
// -----------------------------------------------------------------------
// Design constants
// -----------------------------------------------------------------------
#define MAXSTARS        1000
#define pSTARS          (planeWD*planeHG*MAXSTARS)/(scrWD*scrHG)
// -----------------------------------------------------------------------
// Start position of the plane
// -----------------------------------------------------------------------
#define startX  10
#define startY  10
#define startA  45      // Angle
// -----------------------------------------------------------------------
// Vertex line structure
// -----------------------------------------------------------------------
typedef struct
        {
        int a,b;        // x1, y1
        int c,d;        // x2, y2
        int color;
        int mirX, mirY; // make mirror
        int last;       // flag of last elem. in list
        } vline;
// -----------------------------------------------------------------------
// Constants ... changeable
// -----------------------------------------------------------------------
//#include "pcmath.c"
// =======================================================================
// Exhaust of plane
// =======================================================================
vline exhaust[5]=
{
{5,     0,      15,     0,      RED,0,0,NULL}, // -
{5,     2,      15,     0,      RED,1,0,NULL}, // * /
{5,     5,      15,     5,      RED,1,0,NULL}, // * -
{7,     7,      15,     5,      RED,1,0,NULL}, // * /
{7,     3,      15,     5,      RED,1,0,!NULL},// * \
};
// =======================================================================
// Airplane
// =======================================================================
vline plane[47]={
// body of plane
{20,    -8,     20,     8,      YELLOW,0,0,NULL},
{80,    -8,     80,     8,      YELLOW,0,0,NULL},
{20,    8,      80,     8,      YELLOW,1,0,NULL},       // *
// wing
{35,    8,      35,     38,     YELLOW,1,0,NULL},       // *
{75,    8,      50,     38,     YELLOW,1,0,NULL},       // *
{35,    38,     50,     38,     YELLOW,1,0,NULL},       // *
{33,    39,     53,     39,     YELLOW,1,0,NULL},       // *
{33,    40,     55,     40,     YELLOW,1,0,NULL},       // *
{33,    41,     53,     41,     YELLOW,1,0,NULL},       // *
// steering wheel of height
{37,    10,     37,     35,     YELLOW,1,0,NULL},       // *
{35,    10,     37,     10,     YELLOW,1,0,NULL},       // *
{35,    35,     37,     35,     YELLOW,1,0,NULL},       // *
// backwing
{20,    8,      20,     23,     YELLOW,1,0,NULL},       // *
{30,    8,      25,     23,     YELLOW,1,0,NULL},       // *
{20,    23,     25,     23,     YELLOW,1,0,NULL},       // *
{18,    24,     27,     24,     YELLOW,1,0,NULL},       // *
// steering wheel of tumbling
{25,    0,      45,     0,      YELLOW,0,0,NULL},
{25,    -3,     25,     3,      YELLOW,0,0,NULL},
{25,    3,      45,     0,      YELLOW,1,0,NULL},       // *
// nozzles
{18,    -2,     18,     2,      YELLOW,0,0,NULL},
{18,    4,      18,     7,      YELLOW,1,0,NULL},       // *
{18,    2,      20,     2,      YELLOW,1,0,NULL},       // *
{18,    4,      20,     4,      YELLOW,1,0,NULL},       // *
{18,    7,      20,     7,      YELLOW,1,0,NULL},       // *
// booth of pilot
{65,    1,      75,     1,      YELLOW,0,0,NULL},
{65,    -3,     65,     3,      YELLOW,0,0,NULL},
{75,    -3,     75,     3,      YELLOW,0,0,NULL},
{65,    1,      75,     1,      YELLOW,1,0,NULL},       // *
{65,    3,      75,     3,      YELLOW,1,0,NULL},       // *
{62,    0,      65,     3,      YELLOW,1,0,NULL},       // *
{75,    3,      78,     0,      YELLOW,1,0,NULL},       // *
// beak of plane
{80,    -9,     95,     -9,     YELLOW,0,0,NULL},
{94,    -10,    95,     -10,    YELLOW,0,0,NULL},
{100,   -3,     100,    3,      YELLOW,0,0,NULL},
{80,    8,      100,    3,      YELLOW,1,0,NULL},       // *
{100,   2,      105,    0,      YELLOW,1,0,NULL},       // *
// fuel cans
{65,    6,      75,     6,      YELLOW,1,0,NULL},       // *
{65,    6,      65,     8,      YELLOW,1,0,NULL},       // *
{75,    6,      75,     8,      YELLOW,1,0,NULL},       // *
// on-board number
{48,    13,     50,     15,     YELLOW,1,0,NULL},       // * 1
{43,    15,     50,     15,     YELLOW,1,0,NULL},       // * 1
{44,    17,     49,     17,     YELLOW,1,0,NULL},       // * 0
{44,    20,     49,     20,     YELLOW,1,0,NULL},       // * 0
{43,    18,     43,     19,     YELLOW,1,0,NULL},       // * 0
{50,    18,     50,     19,     YELLOW,1,0,NULL},       // * 0
{48,    22,     50,     24,     YELLOW,1,0,NULL},       // * 1
{43,    24,     50,     24,     YELLOW,1,0,!NULL},      // * 1
};
// -----------------------------------------------------------------------
int opengraph(void)
{
int gdriver=DETECT, gmode, errorcode;
initgraph(&gdriver, &gmode, "."); errorcode=graphresult();
if (errorcode!=grOk)
        {printf("Graphics error: %s\n",grapherrormsg(errorcode));exit(1);}
return(0);
}
// =======================================================================
void drawstars(int x, int y, int wd, int hg, int maxstars)
{
// -----------------------------------------------------------------------
// Description: Draws stars on black sky
//   Parametrs: maxstars        - max quantity of stars
//      Return: <none>
// -----------------------------------------------------------------------
int i;
randomize();
for (i=0; i<maxstars; i++)
        {
        putpixel (x+random(wd-1), y+random(hg-1), BLACK+8*random(2));
        putpixel (x+random(wd-1), y+random(hg-1), LIGHTGRAY+8*random(2));
        }
}
// =======================================================================
void drawvline(float cx,float cy,int angle,float k,vline* object,int c)
{
// -----------------------------------------------------------------------
// Description: Draws given vector object
//   Parametrs: cx, cy  - image position
//              angle   - rotation angle [0; 360]
//              k       - scaling ratio
//              object  - given vector-line object
//              c       - color flag, if equal to 0 then image erases
//      Return: <none>
// -----------------------------------------------------------------------
int i=0;
float nx1, ny1, nx2, ny2;
float cs=cos(M_PI*angle/180), sn=sin(M_PI*angle/180);
//float cs=_pccos_deg(angle), sn=_pcsin_deg(angle);
setcolor(BLACK);
// -----------------------------------------------------------------------
do
        {
        // ---------------------------------------------------------------
        if (!c) setcolor(object[i].color);
        // ---------------------------------------------------------------
        nx1=object[i].a*cs-object[i].b*sn;
        ny1=object[i].b*cs+object[i].a*sn;
        nx2=object[i].c*cs-object[i].d*sn;
        ny2=object[i].d*cs+object[i].c*sn;
        line(cx+nx1*k, cy+ny1*k, cx+nx2*k, cy+ny2*k);
        // ---------------------------------------------------------------
        if (object[i].mirX)
                {
                nx1=object[i].a*cs-(-object[i].b)*sn;
                ny1=-object[i].b*cs+object[i].a*sn;
                nx2=object[i].c*cs-(-object[i].d)*sn;
                ny2=-object[i].d*cs+object[i].c*sn;
                line(cx+nx1*k, cy+ny1*k, cx+nx2*k, cy+ny2*k);
                }
        } while (!object[i++].last);
}
// =======================================================================
int main()
{
// -----------------------------------------------------------------------
int work=1, chng=0;
int angle, oldangle;
float x, y;
float oldx, oldy, oldk;
float speed, k;
// -----------------------------------------------------------------------
printf ("\n"
        "LabWork n. 3.0\n"
        "MazaFaka strike eagle ver. 1.0\n\n"
        "Use cursor key to control MazaFaka. Space - fire.\n... ");
getch();
// -----------------------------------------------------------------------
opengraph(); sky(1000); setwritemode(XOR_PUT);
// -----------------------------------------------------------------------
oldx=x=startX; oldy=y=startY; oldangle=angle=startA;
oldk=k=2; speed=MINSPEED;
// -----------------------------------------------------------------------
drawvline(x, y, angle, k, plane, 0);
drawvline(x, y, angle, k, exhaust, 0);
// -----------------------------------------------------------------------
do
{
// -----------------------------------------------------------------------
if (kbhit())
        {
        // ---------------------------------------------------------------
        int ch=getch();
        chng=0;
        switch (ch)
                {
                case kESC: work=0; break;
                case NULL:
                        ch=getch();
                        switch (ch)
                                {
			case kUP: chng=1;speed+=1;break;
			case kDOWN: chng=1;speed-=1;break;
			case kLEFT: chng=1;oldangle=angle;angle-=4;break;
			case kRIGHT:chng=1;oldangle=angle;angle+=4;break;
                                }
                        break;
                case '+': chng=1; oldk=k; k+=.05; break;
                case '-': chng=1; oldk=k; k-=.05; break;
                case '~': getch(); break;
                default: break;
                }
        // ---------------------------------------------------------------
        if (chng)
                {
                if (speed<MINSPEED) { speed=MINSPEED; chng=0; }
                if (speed>MAXSPEED) { speed=MAXSPEED; chng=0; }
                }
        // ---------------------------------------------------------------
        if (chng)
                {
                // -------------------------------------------------------
                if (angle>=MAXANGLE) angle=0;
                if (angle<0) angle=MAXANGLE-1;
                // -------------------------------------------------------
                drawvline(oldx, oldy, oldangle, oldk, plane, NULL);
                drawvline(oldx, oldy, oldangle, oldk, exhaust, NULL);
                drawvline(x, y, angle, k, plane, NULL);
                drawvline(x, y, angle, k, exhaust, NULL);
                // -------------------------------------------------------
                oldk=k; oldangle=angle;
                // -------------------------------------------------------
                }
        // ---------------------------------------------------------------
        }
// -----------------------------------------------------------------------
if (speed>0)
        {
        // -------------------------------------------------------
        oldx=x; oldy=y;
        // -------------------------------------------------------
	//x+=speed*_pccos_deg(angle);
	//y+=speed*_pcsin_deg(angle);
	x+=speed*cos(M_PI*angle/180);
	y+=speed*sin(M_PI*angle/180);
	// -------------------------------------------------------
	if (x<-planeWD*k)               x=scrWD+planeWD*k-1;
	if (y<-planeHG*k/2)             y=scrHG+planeHG*k/2-1;
	if (x>scrWD+planeWD*k)          x=-planeWD*k;
	if (y>scrHG+planeHG*k/2)        y=-planeHG*k/2;
	// -------------------------------------------------------
	drawvline(oldx, oldy, angle, k, plane, NULL);
	drawvline(oldx, oldy, angle, k, exhaust, NULL);
	drawvline(x, y, angle, k, plane, NULL);
	drawvline(x, y, angle, k, exhaust, NULL);
	// -------------------------------------------------------
	oldx=x; oldy=y;
	// -------------------------------------------------------
	}
// -----------------------------------------------------------------------
} while (work);
closegraph();
printf ("Thanx 4 mazafaking ...\n");
return (0);
}
// =======================================================================
