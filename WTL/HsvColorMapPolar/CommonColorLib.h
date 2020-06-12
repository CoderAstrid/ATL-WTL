#pragma once

#include <math.h>
/*******************************************************************************/
/*        Define                                                               */
/*******************************************************************************/

//.Color Picker Notify Message Macros
#define CPN_SELCHANGE        0x8000	/* Color Picker Selection change */
#define CPN_DROPDOWN         0x8001	/* Color Picker drop down */
#define CPN_CLOSEUP          0x8002	/* Color Picker close up */
#define CPN_SELENDOK         0x8003	/* Color Picker end OK */
#define CPN_SELENDCANCEL     0x8004	/* Color Picker end (cancelled) */
//#define WM_USER + 0x123
//
/*******************************************************************************/
/*        Structure                                                             */
/*******************************************************************************/
//. RGB Color Structure
typedef struct LST_RGBCOLOR
{
	long r;
	long g;
	long b;	
}LST_RGBCOLOR, *LST_LPRGBCOLOR;

//. HSL Color Structure
typedef struct LST_HSLCOLOR
{
	double h;
	double s;
	double l;	
}LST_HSLCOLOR, *LST_LPHSLCOLOR;

enum EF_COLORMAP_TYPE
{
	efUnknown_Type = 0,
	efCMYK_Type = 1,
	efHSV_Type = 2,
	efRGB_Type = 3
};
/*******************************************************************************/
/*        Function                                                              */
/*******************************************************************************/
int SS_hue_2_RGB(double v1, double v2, double vH, double* pHue);
int SS_HslToRgb(LST_HSLCOLOR hsl, LST_RGBCOLOR* pRgb);
int SS_getMinimumValue(double x1, double x2, double x3, double* pMin);
int SS_getMaximumValue(double x1, double x2, double x3, double* pMax);
int SS_RgbToHsl(LST_RGBCOLOR rgb, LST_HSLCOLOR* pHsl);

int SF_GetScreenWorkRect(RECT* rcWork);
int SF_GetHSVColComponent(COLORREF crColor, int* colValues);
int SF_GetRGBColComponent(COLORREF crColor, int* colValues);
int SF_GetCMYKColComponent(COLORREF crColor, int* colValues);
void HsvToRgb(float hue, float saturation, float value,float *red, float *green, float *blue);
void RgbToHsv(float red, float green, float blue, float* hue, float* saturation, float* value);
COLORREF HsvToRgb( long Hue, long Saturation, long Value);
void RgbToHsv(COLORREF nRgbColor,long&  Hue, long& Saturation, long& Value);
void RgbToCmyk(float red, float green, float blue, 
			   float* cyan, float* magenta, float* yellow, float* black);
void CmykToRgb(float cyan, float magenta, float yellow, float black, 
			   float* red, float* green, float* blue);

COLORREF CmykToRgb(COLORREF nCmykColor);
COLORREF RgbToCmyk(COLORREF nRgbColor);
double GetDegreeAngle(int x, int y);