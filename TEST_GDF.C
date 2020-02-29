// =======================================================================
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
// -----------------------------------------------------------------------
#include "pcgdf.h"
// =======================================================================
int main(void)
{
/* request auto detection */
int gdriver = DETECT, gmode, errorcode;
int left, top, right, bottom;
int midx, midy;
/* initialize graphics and local  variables */
initgraph(&gdriver, &gmode, "");

/* read result of initialization */
errorcode = graphresult();
/* an error occurred */
if (errorcode != grOk)
	{
	printf("Graphics error: %s\n", grapherrormsg(errorcode));
	printf("Press any key to halt:");
	getch();
	exit(1);    /* terminate with an error code */
	}

gdf_init();
midx = getmaxx() / 2;
midy = getmaxy() / 2;
setcolor(getmaxcolor());

left = getmaxx() / 2 - 50;
top = getmaxy() / 2 - 50;
right = getmaxx() / 2 + 50;
bottom = getmaxy() / 2 + 50;
/* draw arc */
//arc(midx, midy, stangle, endangle, radius);

gdf_test();
   /* clean up */
   getch();
   closegraph();
   return 0;
}
