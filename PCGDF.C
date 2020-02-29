// =======================================================================
// Graphics Drawer Files function library ver. 1.0 (C, CPP)
// Troy computing, Inc.
// Copyright (c) 1994-2000
// -----------------------------------------------------------------------
// GDF Vector graphics support library.
// Used library: unitypes.h, memc.h
// -----------------------------------------------------------------------
// File: pcgdf.c
// -----------------------------------------------------------------------
//     Compiler: Borland C++ 3.1
//  Application: DOS16 console, Win32 GUI
// -----------------------------------------------------------------------
// Made date: 07/ IX.2000
// Last edit: 10/ IX.2000
//     Build: 1
// =======================================================================
#ifdef __MSDOS__
#include <graphics.h>
#endif
// -----------------------------------------------------------------------
#include <math.h>		// M_PI
// -----------------------------------------------------------------------
#include "memc.h"
#include "unitypes.h"
// -----------------------------------------------------------------------
#include "pcgdf.h"
#include "pcmath.h"
// =======================================================================
#define rad2deg(_r_)    ((float)(180*(_r_))/M_PI)
// =======================================================================
// Control structure
// =======================================================================
struct tag_gdf_control
	{
	// ---------------------------------------------------------------
	// 1. General
	// ---------------------------------------------------------------
	int16 color;
	int16 writemode;
	// ---------------------------------------------------------------
	// 2. linesettingstype
	// ---------------------------------------------------------------
	int16 linestyle;
	int16 upattern;
	int16 thickness;
	// ---------------------------------------------------------------
	// 3. fillsettingstype
	// ---------------------------------------------------------------
	int16 fillpattern;	// current fill pattern
	int16 fillcolor;	// current fill color
	// ---------------------------------------------------------------
	// 4. Special settings
	// ---------------------------------------------------------------
	int16 mirX;		// make mirror copy via OX
	int16 mirY;		// make mirror copy via OY
	int16 mirXY;		// make mirror copy via XOY
	int16 scrCX;		// X center of screen
	int16 scrCY;		// Y center of screen
	int16 enfill;		// Enable filling
	// ---------------------------------------------------------------
	} gdf_control={
	0, 0,			// 1. General
	0, 0, 1,		// 2. linesettingstype
	1, 15,			// 3. fillsettingstype
	0, 0, 0,		// 4. Special settings
	0, 0, 0};
// =======================================================================
// Pixel struct
// =======================================================================
typedef struct tag_pixel2d
	{
	int16 x, y;
	} pixel2d;
// =======================================================================
// Private function
// -----------------------------------------------------------------------
// Hardware depended functions (HDF)
// =======================================================================
void gdf_update (void)
{
// -----------------------------------------------------------------------
// Description: Updates graphics parametrs
//   Parametrs: <none>
//      Return: <none>
// -----------------------------------------------------------------------
#ifdef __MSDOS__
setcolor(gdf_control.color);
setwritemode(gdf_control.writemode);
setlinestyle(gdf_control.linestyle, gdf_control.upattern,
	gdf_control.thickness);
setfillstyle(gdf_control.fillpattern, gdf_control.fillcolor);
#elif _Windows
#endif
// -----------------------------------------------------------------------
}
// =======================================================================
void gdf_init (void)
{
// -----------------------------------------------------------------------
// Description: Reinits graphics parametrs
//   Parametrs: <none>
//      Return: <none>
// -----------------------------------------------------------------------
gdf_update();
// -----------------------------------------------------------------------
gdf_control.mirX=0; gdf_control.mirY=0; gdf_control.mirXY=0;
gdf_control.scrCX=0; gdf_control.scrCY=0; gdf_control.enfill=0;
// -----------------------------------------------------------------------
}
// =======================================================================
pixel2d gdf_pixtransform(int16 x, int16 y, int16 angle, float k)
{
// -----------------------------------------------------------------------
// Description: Scales & rotates pixel coordinates
//   Parametrs: x, y	- pixel coordinates
//		angle	- rotation angle
//		k	- scaling ratio
//      Return: scaled & rotated structure
// -----------------------------------------------------------------------
//float cs=cos(M_PI*angle/180), sn=sin(M_PI*angle/180);
float cs=_pccos_deg(angle), sn=_pcsin_deg(angle);
pixel2d npix;
// -----------------------------------------------------------------------
npix.x=gdf_control.scrCX+((float)x*cs-y*sn)*k;
npix.y=gdf_control.scrCY+((float)y*cs+x*sn)*k;
// -----------------------------------------------------------------------
return (npix);
}
// =======================================================================
void gdf_setcolor (int16 c)
{
// -----------------------------------------------------------------------
// Description: Sets output color
//   Parametrs: c	- color
//      Return: <none>
// -----------------------------------------------------------------------
gdf_control.color=c;
#ifdef __MSDOS__
setcolor(c);
#elif _Windows
#endif
}
// =======================================================================
void gdf_setfillcolor (int16 c)
{
// -----------------------------------------------------------------------
// Description: Sets fill color
//   Parametrs: c	- new fill color
//      Return: <none>
// -----------------------------------------------------------------------
gdf_control.fillcolor=c;
#ifdef __MSDOS__
setfillstyle(gdf_control.fillpattern, c);
#elif _Windows
#endif
}
// =======================================================================
void gdf_setfillpattern (int16 p)
{
// -----------------------------------------------------------------------
// Description: Sets fill pattern
//   Parametrs: c	- new fill pattern number
//      Return: <none>
// -----------------------------------------------------------------------
gdf_control.fillpattern=p;
#ifdef __MSDOS__
setfillstyle(p, gdf_control.fillcolor);
#elif _Windows
#endif
}
// =======================================================================
void gdf_sub_putpixel (int16 x, int16 y, int16 c)
{
// -----------------------------------------------------------------------
// Description: Draws unscalable pixel
//   Parametrs: x, y	- coordiantes
//              c       - color flag
//      Return: <none>
// -----------------------------------------------------------------------
#ifdef __MSDOS__
putpixel(x, y, c);
#elif _Windows
PutPixel(x, y, c);
#endif
}
// =======================================================================
void gdf_moveto (int16 x, int16 y)
{
// -----------------------------------------------------------------------
// Description: Moves graphics pointer to given coordinates
//   Parametrs: x, y	- coordinates
//      Return: <none>
// -----------------------------------------------------------------------
#ifdef __MSDOS__
moveto(x, y);
#elif _Windows
MoveTo(x, y);
#endif
}
// =======================================================================
void gdf_lineto (int16 x, int16 y, int16 c)
{
// -----------------------------------------------------------------------
// Description: Draws line to given coordinates
//   Parametrs: x, y	- coordinates
//      Return: <none>
// -----------------------------------------------------------------------
gdf_setcolor(c);
#ifdef __MSDOS__
lineto(x, y);
#elif _Windows
LineTo(x, y);
#endif
}
// =======================================================================
void gdf_linerel (int16 dx, int16 dy, int16 c)
{
// -----------------------------------------------------------------------
// Description: Draws relative line
//   Parametrs: dx, dy	- addictions
//      Return: <none>
// -----------------------------------------------------------------------
gdf_setcolor(c);
#ifdef __MSDOS__
linerel(dx, dy);
#elif _Windows
LineRel(dx, dy);
#endif
}
// =======================================================================
void gdf_sub_fillpoly (int16 n, int16* points, int16 angle, float k,
	int16 c, int16 fc)
{
// -----------------------------------------------------------------------
// Description: Draws & fills a polygon
//   Parametrs: n	- quantity of points
//		points	- ptr to a sequence of (numpoints x 2) integers
//              angle   - rotation angle [0; 360]
//              k       - scaling ratio
//		c	- color
//		fc	- fill color (or '-1' to skip filling)
//      Return: <none>
// -----------------------------------------------------------------------
int i, *ptrpoint;
pixel2d npix;
// -----------------------------------------------------------------------
if ((ptrpoint=newm(int, n+1))==NULL) return;
for (i=0; i<n; i++)
	{
	npix=gdf_pixtransform(points[i*2+0], points[i*2+1], -angle, k);
	ptrpoint[i*2+0]=npix.x;
	ptrpoint[i*2+1]=npix.y;
	}
// -----------------------------------------------------------------------
if (fc!=-1)
	{ ptrpoint[n*2+0]=ptrpoint[0];
	ptrpoint[n*2+1]=ptrpoint[1]; }
// -----------------------------------------------------------------------
gdf_setcolor(c); if (fc!=-1) gdf_setfillcolor(fc);
// -----------------------------------------------------------------------
#ifdef __MSDOS__
if (fc!=-1) fillpoly(n, ptrpoint); drawpoly(n, ptrpoint);
#elif _Windows
#endif
// -----------------------------------------------------------------------
deletem(ptrpoint);
// -----------------------------------------------------------------------
}
// =======================================================================
void gdf_ellipse (int16 x, int16 y, int16 stangle, int16 endangle,
	int16 xradius, int16 yradius, int16 c)
{
// -----------------------------------------------------------------------
// Description: Draws unscalable ellipse
//   Parametrs: x, y	- Center of ellipse
//		xradius	- Horizontal axis
//		yradius	- Vertical axis
//		stangle	- Starting angle
//		endangle	- Ending angle
//      Return: <none>
// -----------------------------------------------------------------------
gdf_setcolor(c);
#ifdef __MSDOS__
ellipse (x, y, stangle, endangle, xradius, yradius);
#elif _Windows
Ellipse (x, y, stangle, endangle, xradius, yradius);
#endif
}
// =======================================================================
void gdf_fillellipse (int16 x, int16 y, int16 stangle, int16 endangle,
		int16 xradius, int16 yradius, int16 c)
{
// -----------------------------------------------------------------------
// Description: Draws and fills unscalable ellipse
//   Parametrs: x, y	- Center of ellipse
//		xradius	- Horizontal axis
//		yradius	- Vertical axis
//		stangle	- Starting angle
//		endangle - Ending angle
//      Return: <none>
// -----------------------------------------------------------------------
gdf_setfillcolor(c);
#ifdef __MSDOS__
//fillellipse (x, y, xradius, yradius);
sector (x, y, stangle, endangle, xradius, yradius);
#elif _Windows
Ellipse (x, y, xradius, yradius);
#endif
}
// =======================================================================
void gdf_sector (int16 x, int16 y, int16 stangle, int16 endangle,
	int16 xradius, int16 yradius, int16 c)
{
// -----------------------------------------------------------------------
// Description: Draws and fills unscalable sector
//   Parametrs: x, y	- Center of ellipse
//		xradius	- Horizontal axis
//		yradius	- Vertical axis
//		stangle	- Starting angle
//		endangle - Ending angle
//      Return: <none>
// -----------------------------------------------------------------------
gdf_setcolor(c);
#ifdef __MSDOS__
sector (x, y, stangle, endangle, xradius, yradius);
#elif _Windows
Ellipse (x, y, stangle, endangle, xradius, yradius);
#endif
}
// =======================================================================
void gdf_arc(int x1, int y1, int x2, int y2, int r, int c)
{
c=x1&x2&y1&y2&r&c;
}
// =======================================================================
// Private function
// -----------------------------------------------------------------------
// Hardware independed functions (HIF)
// =======================================================================
void gdf_putpixel(int16 x, int16 y, float k, int16 c)
{
// -----------------------------------------------------------------------
// Description: Draws scalable pixel
//   Parametrs: x, y	- coordiantes
//              k       - scaling ratio
//              c       - color flag
//      Return: <none>
// -----------------------------------------------------------------------
if (k<1.5)
	gdf_sub_putpixel(x, y, c);
else if (k>=1.5 && k<2.5)
	{
	gdf_sub_putpixel(x, y, c);
	gdf_sub_putpixel(x-1, y, c); gdf_sub_putpixel(x+1, y, c);
	gdf_sub_putpixel(x, y-1, c); gdf_sub_putpixel(x, y+1, c);
	}
else
	{ gdf_sub_putpixel(x, y, c);
	/*gdf_fillcircle(x, y, 1, k, c, c); */}
}
// =======================================================================
void gdf_sub_line (int16 x1, int16 y1, int16 x2, int16 y2, int16 c)
{
// -----------------------------------------------------------------------
// Description: Draws unscalable HIF line
//   Parametrs: x1, y1  - coordinates of start of line
//		x2, y2  - coordinates of end of line
//              c       - color flag
//      Return: <none>
// -----------------------------------------------------------------------
gdf_moveto(x1, y1); gdf_lineto(x2, y2, c);
}
// =======================================================================
void gdf_line (int16 x1, int16 y1, int16 x2, int16 y2, int16 angle,
	float k, int16 c)
{
// -----------------------------------------------------------------------
// Description: Draws scalable line
//   Parametrs: x1, y1  - coordinates of start of line
//		x2, y2  - coordinates of end of line
//              angle   - rotation angle [0; 360]
//              k       - scaling ratio
//              c       - color flag
//      Return: <none>
// -----------------------------------------------------------------------
int16 cx, cy;
float nx1, ny1, nx2, ny2;
//float cs=cos(M_PI*angle/-180), sn=sin(M_PI*angle/-180);
float cs=_pccos_deg(-angle), sn=_pcsin_deg(-angle);
// -----------------------------------------------------------------------
nx1=x1*cs-y1*sn; ny1=y1*cs+x1*sn;
nx2=x2*cs-y2*sn; ny2=y2*cs+x2*sn;
// -----------------------------------------------------------------------
cx=gdf_control.scrCX; cy=gdf_control.scrCY;
// -----------------------------------------------------------------------
gdf_sub_line(cx+nx1*k, cy+ny1*k, cx+nx2*k, cy+ny2*k, c);
// -----------------------------------------------------------------------
if (gdf_control.mirX)
	{ nx1=x1*cs-(-y1)*sn; ny1=(-y1)*cs+x1*sn;
	nx2=x2*cs-(-y2)*sn; ny2=-y2*cs+x2*sn;
	gdf_sub_line(cx+nx1*k, cy+ny1*k, cx+nx2*k, cy+ny2*k, c);}
// -----------------------------------------------------------------------
if (gdf_control.mirY)
	{ nx1=-x1*cs-y1*sn; ny1=y1*cs+(-x1)*sn;
	nx2=-x2*cs-y2*sn; ny2=y2*cs+(-x2)*sn;
	gdf_sub_line(cx+nx1*k, cy+ny1*k, cx+nx2*k, cy+ny2*k, c); }
// -----------------------------------------------------------------------
if (gdf_control.mirXY)
	{ nx1=-x1*cs-(-y1)*sn; ny1=-y1*cs+(-x1)*sn;
	nx2=-x2*cs-(-y2)*sn; ny2=-y2*cs+(-x2)*sn;
	gdf_sub_line(cx+nx1*k, cy+ny1*k, cx+nx2*k, cy+ny2*k, c); }
// -----------------------------------------------------------------------
}
// =======================================================================
#define gdf_drawpoly(_n_,_points_,_angle_,_k_,_c_) \
	gdf_sub_fillpoly(_n_,_points_,_angle_,_k_,_c_,-1);
// -----------------------------------------------------------------------
// Description: Draws a polygon using the current line style and color.
//   Parametrs: n	- quantity of points
//		points	- ptr to a sequence of (numpoints x 2) integers
//              angle   - rotation angle [0; 360]
//              k       - scaling ratio
//		c	- color
//      Return: <none>
// -----------------------------------------------------------------------
// =======================================================================
#define gdf_fillpoly(_n_,_points_,_angle_,_k_,_c_,_fc_) \
	gdf_sub_fillpoly(_n_,_points_,_angle_,_k_,_c_,_fc_);
// -----------------------------------------------------------------------
// Description: Draws & fill a polygon
//   Parametrs: n	- quantity of points
//		points	- ptr to a sequence of (numpoints x 2) integers
//              angle   - rotation angle [0; 360]
//              k       - scaling ratio
//		c	- color
//		fc	- fill color
//      Return: <none>
// -----------------------------------------------------------------------
// =======================================================================
// Figures
// =======================================================================
void gdf_sub_rect (int16 x1, int16 y1, int16 x2, int16 y2, int16 angle,
	float k, int16 c, int16 fc)
{
// -----------------------------------------------------------------------
// Description: Draws scalable rectangle
//   Parametrs: x1, y1  - coordinates of lower left corner
//		x2, y2  - coordinates of upper right corner
//              angle   - rotation angle [0; 360]
//              k       - scaling ratio
//              c       - color flag
//		fc	- fill color
//      Return: <none>
// -----------------------------------------------------------------------
int rect[10];
rect[0]=x1; rect[1]=y1; rect[2]=x2; rect[3]=y1;
rect[4]=x2; rect[5]=y2; rect[6]=x1; rect[7]=y2;
rect[8]=x1; rect[9]=y1;
gdf_sub_fillpoly(5, rect, angle, k, c, fc);
// -----------------------------------------------------------------------
}
// =======================================================================
#define gdf_rect(_x1_,_y1_,_x2_,_y2_,_angle_,_k_,_c_)\
	gdf_sub_rect(_x1_,_y1_,_x2_,_y2_,_angle_,_k_,_c_,-1)
#define gdf_fillrect(_x1_,_y1_,_x2_,_y2_,_angle_,_k_,_c_,_fc_)\
	gdf_sub_rect(_x1_,_y1_,_x2_,_y2_,_angle_,_k_,_c_,_fc_)
#define gdf_bar(_x1_,_y1_,_x2_,_y2_,_angle_,_k_,_c_,_fc_)\
	gdf_sub_rect(_x1_,_y1_,_x2_,_y2_,_angle_,_k_,_c_,_fc_)
// =======================================================================
void gdf_sub_tri (int16 x1, int16 y1, int16 x2, int16 y2,
	int16 x3, int16 y3, int16 angle, float k, int16 c, int16 fc)
{
// -----------------------------------------------------------------------
// Description: Draws scalable triangle
//   Parametrs: x1,y1,x2,y2,x3,y3	- coordinates of corners
//              angle   - rotation angle [0; 360]
//              k       - scaling ratio
//              c       - color flag
//		fc	- fill color
//      Return: <none>
// -----------------------------------------------------------------------
int tri[8];
tri[0]=x1; tri[1]=y1; tri[2]=x2; tri[3]=y2;
tri[4]=x3; tri[5]=y3; tri[6]=x1; tri[7]=y1;
gdf_sub_fillpoly(4, tri, angle, k, c, fc);
// -----------------------------------------------------------------------
}
// =======================================================================
#define gdf_tri(_x1_,_y1_,_x2_,_y2_,_x3_,_y3_,_angle_,_k_,_c_)\
	gdf_sub_tri(_x1_,_y1_,_x2_,_y2_,_x3_,_y3_,_angle_,_k_,_c_,-1)
#define gdf_filltri(_x1_,_y1_,_x2_,_y2_,_x3_,_y3_,_angle_,_k_,_c_,_fc_)\
	gdf_sub_tri(_x1_,_y1_,_x2_,_y2_,_x3_,_y3_,_angle_,_k_,_c_,_fc_)
// =======================================================================
void gdf_sub_circle(int16 x, int16 y, int16 r, float k, int16 c, int16 fc)
{
// -----------------------------------------------------------------------
// Description: Draws scalable circle
//   Parametrs: x, y	- Center of circle
//		r	- radius
//              k       - scaling ratio
//              c       - color flag
//		fc	- fill color
//      Return: <none>
// -----------------------------------------------------------------------
if (fc!=-1) gdf_fillellipse (x, y, 0, 360, r*k, r*k, fc);
gdf_ellipse (x, y, 0, 360, r*k, r*k, c);
}
// =======================================================================
#define gdf_circle(_x_,_y_,_r_,_k_,_c_)\
	gdf_sub_circle(_x_,_y_,_r_,_k_,_c_,-1)
#define gdf_fillcircle(_x_,_y_,_r_,_k_,_c_,_fc_)\
	gdf_sub_circle(_x_,_y_,_r_,_k_,_c_,_fc_)
// =======================================================================
// Public functions ... PCGDF
// =======================================================================
void gdf_put (int px, int py, int16 angle, float k, int16* obj)
{
// -----------------------------------------------------------------------
int i=0;
int16 j, n, x, y, x1, y1, x2, y2, x3, y3, sa, ea, r, rx, ry, c, fc;
int16* poly;
// -----------------------------------------------------------------------
gdf_control.scrCX=px;
gdf_control.scrCY=py;
// -----------------------------------------------------------------------
do
{
// -----------------------------------------------------------------------
switch (obj[i])
	{
	// ---------------------------------------------------------------
	// Main graphics primitives
	// ---------------------------------------------------------------
	case gdfCC: 	break;
	case gdfPTR:	x=obj[i+1]; y=obj[i+2];
			gdf_moveto(x, y); i+=3; break;
	case gdfPIX:	x=obj[i+1]; y=obj[i+2]; c=obj[i+3];
			gdf_putpixel(x, y, k, c); i+=4; break;
	case gdfLNT:	x=obj[i+1]; y=obj[i+2]; c=obj[i+3];
			gdf_lineto(x, y, c); i+=4; break;
	case gdfLNR:	x=obj[i+1]; y=obj[i+2]; c=obj[i+3];
			gdf_linerel(x, y, c); i+=4; break;
	// ---------------------------------------------------------------
	case gdfLN:	x1=obj[i+1]; y1=obj[i+2];
			x2=obj[i+3]; y2=obj[i+4]; c=obj[i+5];
			gdf_line(x1, y1, x2, y2, angle, k, c); i+=6;
			break;
	// ---------------------------------------------------------------
	case gdfLNC:	i+=7; break;
	// ---------------------------------------------------------------
	case gdfPOLY:	n=obj[i+1]; c=obj[i+2+n*2];
			if ((poly=newm(int16, n*2))==NULL)
				{i=i+3+n*2; break;}
			for (j=0; j<n; j++)
				{ poly[j*2+0]=obj[i+2+j*2+0];
				poly[j*2+1]=obj[i+2+j*2+1]; }
			gdf_drawpoly(n, poly, angle, k, c); i=i+3+n*2;
			deletem(poly); break;
	// ---------------------------------------------------------------
	case gdfPOLYFL:	n=obj[i+1]; c=obj[i+2+n*2]; fc=obj[i+2+n*2+1];
			if ((poly=newm(int16, n*2))==NULL)
				{i=i+4+n*2; break;}
			for (j=0; j<n; j++)
				{ poly[j*2+0]=obj[i+2+j*2+0];
				poly[j*2+1]=obj[i+2+j*2+1]; }
			gdf_fillpoly(n, poly, angle, k, c, fc); i=i+4+n*2;
			deletem(poly); break;
	// ---------------------------------------------------------------
	case gdfELL:	x=obj[i+1]; y=obj[i+2]; sa=obj[i+3]; ea=obj[i+4];
			rx=obj[i+5]; ry=obj[i+5]; c=obj[i+7];
			gdf_ellipse(x, y, sa, ea, rx, ry, c); i+=8; break;
	// ---------------------------------------------------------------
	case gdfELLFL:	x=obj[i+1]; y=obj[i+2]; sa=obj[i+3]; ea=obj[i+4];
			rx=obj[i+5]; ry=obj[i+5]; c=obj[i+7]; fc=obj[i+8];
			gdf_fillellipse(x, y, sa, ea, rx, ry, c); i+=9;
			break;
	// ---------------------------------------------------------------
	// Figures
	// ---------------------------------------------------------------
	case gdfRECT:	x1=obj[i+1]; y1=obj[i+2];
			x2=obj[i+3]; y2=obj[i+4]; c=obj[i+5];
			gdf_rect(x1, y1, x2, y2, angle, k, c); i+=6;
			break;
	// ---------------------------------------------------------------
	case gdfRECTFL:	x1=obj[i+1]; y1=obj[i+2];
			x2=obj[i+3]; y2=obj[i+4]; c=obj[i+5]; fc=obj[i+6];
			gdf_bar(x1, y1, x2, y2, angle, k, c, fc); i+=7;
			break;
	// ---------------------------------------------------------------
	case gdfTRI:	x1=obj[i+1]; y1=obj[i+2];
			x2=obj[i+3]; y2=obj[i+4];
			x3=obj[i+5]; y3=obj[i+6]; c=obj[i+7];
			gdf_tri(x1, y1, x2, y2, x3, y3,angle, k, c); i+=8;
			break;
	// ---------------------------------------------------------------
	case gdfTRIFL:	x1=obj[i+1]; y1=obj[i+2];
			x2=obj[i+3]; y2=obj[i+4];
			x3=obj[i+5]; y3=obj[i+6]; c=obj[i+7]; fc=obj[i+8];
			gdf_filltri(x1, y1, x2, y2, x3, y3,angle, k, c, fc);
			i+=9; break;
	// ---------------------------------------------------------------
	case gdfCIRC:	x=obj[i+1]; y=obj[i+2];
			r=obj[i+3]; c=obj[i+4];
			gdf_circle(x, y, r, k, c); i+=5;
			break;
	// ---------------------------------------------------------------
	case gdfCIRCFL:	x=obj[i+1]; y=obj[i+2];
			r=obj[i+3]; c=obj[i+4]; fc=obj[i+5];
			gdf_fillcircle(x, y, r, k, c, fc); i+=6;
			break;
	// ---------------------------------------------------------------
	default: break;
	}
// -----------------------------------------------------------------------
} while(obj[i]!=NULL && i<32767);
}
// =======================================================================
// Test functions ... PCGDF
// =======================================================================
#include <time.h>
void drawstars(int x, int y, int wd, int hg, int maxstars)
{
// -----------------------------------------------------------------------
// Description: Draws stars on black sky
//   Parametrs: maxstars        - max quantity of stars
//      Return: <none>
// -----------------------------------------------------------------------
int i;
// -----------------------------------------------------------------------
randomize();
for (i=0; i<maxstars; i++)
	{ gdf_putpixel (x+random(wd-1), y+random(hg-1),
		random(2)+1, BLACK+8*random(2));
	gdf_putpixel (x+random(wd-1), y+random(hg-1),
		random(2)+1, LIGHTGRAY+8*random(2)); }
// -----------------------------------------------------------------------
}
// =======================================================================
int16 plane[]=
	{
	// body
	gdfRECTFL, -45, 10, 45, -10, 8, 7,
	// rockets - left
	gdfRECTFL, -5,-60,22,-57,8,7, gdfTRIFL, 22,-60,25,-58,22,-57,12,4,
	gdfRECTFL, -5,-50,22,-47,8,7, gdfTRIFL, 22,-50,25,-48,22,-47,12,4,
	gdfRECTFL, -5,-40,22,-37,8,7, gdfTRIFL, 22,-40,25,-38,22,-37,12,4,
	// rockets - right
	gdfRECTFL, -5,60,22,57,8,7, gdfTRIFL, 22,60,25,58,22,57,12,4,
	gdfRECTFL, -5,50,22,47,8,7, gdfTRIFL, 22,50,25,48,22,47,12,4,
	gdfRECTFL, -5,40,22,37,8,7, gdfTRIFL, 22,40,25,38,22,37,12,4,
	// forward
	gdfPOLYFL, 5, 45, -10, 67, -5, 67, 5, 45, 10, 45, -10, 8, 7,
	gdfTRIFL, 67, -3, 75, 0, 67, 3, 8, 7,
	// wings
	gdfPOLYFL, 4, 0, -10, 0, -70, 15, -70, 25, -10, 8, 7,
	gdfPOLYFL, 4, 0, 10, 0, 70, 15, 70, 25, 10, 8, 7,
	// rul'
	gdfRECT, 0,-55,5,-15,8,
	gdfRECT, 0,55,5,15,8,
	// stabiliser
	gdfPOLYFL, 6, -2,-70, -2,-75, 15,-75, 19,-72, 15,-70, -2,-70, 8, 7,
	gdfPOLYFL, 6, -2,70, -2,75, 15,75, 19,72, 15,70, -2,70, 8, 7,
	// zakryliky
	gdfPOLYFL, 4, -45,-10, -45,-30, -35,-30, -30,-10, 8, 7,
	gdfPOLYFL, 4, -45,10, -45,30, -35,30, -30,10, 8, 7,
	// rul' 2
	gdfRECT, -45,-25,-43,-12,8,
	gdfRECT, -45,25,-43,12,8,
	// sopla
	gdfRECTFL, -45,-2,-47,-8,8,7,
	gdfRECTFL, -45,2,-47,8,8,7,
	// back wing
	gdfTRI, -40,-2,-20,0,-40, 2, 8,
	gdfLN, -40,0,-20,0,8,
	// baki
	gdfRECT, 20,-7,35,-10,8,
	gdfRECT, 20,7,35,10,8,
	// kabina (fonar')
	gdfRECT, 20,-3,35,3,8,
	gdfTRI, 35,-3,37,0,35, 3, 8,
	gdfTRI, 20,-3,18,0,20, 3, 8,
	// onboard number
	gdfPOLY, 3, 10,-40, 15,-37, 10,-35, 8,
	gdfLN, 12,-39,12,-36,8,
	gdfLN, 12,-33,12,-31,8,
	gdfPOLY, 3, 13,-29, 15,-27, 10,-27, 8,
	gdfRECT, 10,-25,15,-22,8,
	// onboard name
	gdfPOLY, 4,10,22,10,20,15,20,15,22,8,
	gdfPOLY, 4,10,27,10,25,15,25,15,27,8,
	gdfPOLY, 4,10,32,10,30,15,30,15,32,8,
	gdfLN, 10,35,15,35,8,
	gdfRECT, 15,35,12,37,8,
	0};
// =======================================================================
void gdf_test(void)
{
// -----------------------------------------------------------------------
int i;
int16 scrCX=320, scrCY=240;
// -----------------------------------------------------------------------
#ifdef __MSDOS__
{
float j;
int16 x, y;
scrCX=getmaxx()/2; scrCY=getmaxy()/2;
gdf_sub_line(scrCX, 0, scrCX, 480, 14);
gdf_sub_line(0, scrCY, 640, scrCY, 14);
for (j=scrCX*2; j>-scrCX*2; j-=.1)
	{
	x=j/2+scrCX;
	y=-_pcsin_deg(j)*200+scrCY;
	gdf_lineto (x, y, 15);
	}
for (j=-scrCX*2; j<scrCX*2; j+=.1)
	{
	x=j/2+scrCX;
	y=-_pccos_deg(j)*200+scrCY;
	gdf_lineto (x, y, 13);
	}
//getch();
}
#endif
drawstars(0, 0, scrCX*2, scrCY*2, 500);
//setwritemode(XOR_PUT);
//gdf_control.fillpattern=10; gdf_update();
/*gdf_control.mirX=1;
gdf_control.mirY=1;
gdf_control.mirXY=1;*/
//*
gdf_control.scrCX=scrCX;
gdf_control.scrCY=scrCY;
//gdf_rect(-100, -100, 150, 100, 30, 1, 5);
gdf_rect(-100, -100, 150, 100, 5, 1, 5);
gdf_fillrect(-100, -100, 150, 100, 45, 1, 11,5);
//getch();
// -----------------------------------------------------------------------
for (i=0; i<4*180; i+=2)
	{
	//gdf_rect(left,top,250,bottom, i, 1, i%16);
	//gdf_rect(100, 100, 120, 130, i, 1, i%16);
	gdf_put(scrCX, scrCY, i, 2, plane);
	}//*/
// -----------------------------------------------------------------------
gdf_tri(10,10,20,20,0,20, 4,10,14);
gdf_filltri(10,10,20,20,0,20, 180,10,14,2);
gdf_put(320, 240, 10, 3, plane);
}
// =======================================================================
