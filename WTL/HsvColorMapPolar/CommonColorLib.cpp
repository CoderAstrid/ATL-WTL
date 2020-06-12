#include "StdAfx.h"
#include "CommonColorLib.h"

////////////////////////////////////////////////////////////////////////////////
//.Function	: SS_HslToRgb
//.Description	: Get the RGB Value from HSL Value of Any Color
//:=*===================*===============*=======================================
int										//:Return Value(Always 1)
SS_HslToRgb(
LST_HSLCOLOR		hsl,			//:IN: HSL Color Value
LST_RGBCOLOR*		pRgb			//:OUT: RGB Color Value
){
	double				w_red;
	double				w_green;
	double				w_blue;

	double				w_h				= hsl.h / 360.0;
	double				w_s				= hsl.s / 100.0;
	double				w_l				= hsl.l / 100.0;

	double				w_var1;
	double				w_var2;

	long				w_nRed;
	long				w_nGreen;
	long				w_nBlue;

	int					w_Hr			= 0;
	if ( w_s == 0.0 )
	{
		w_red = w_l;
		w_green = w_l;
		w_blue = w_l;
	}
	else
	{
		if ( w_l < 0.5 )
		{
			w_var2 = w_l * (1.0 + w_s);
		}
		else
		{
			w_var2 = (w_l + w_s) - (w_s * w_l);
		}

		w_var1 = 2.0 * w_l - w_var2;

		w_Hr = SS_hue_2_RGB( w_var1, w_var2, w_h + (1.0 / 3.0) , &w_red);
		w_Hr = SS_hue_2_RGB( w_var1, w_var2, w_h , &w_green);
		w_Hr = SS_hue_2_RGB( w_var1, w_var2, w_h - (1.0 / 3.0) , &w_blue);
	}

	w_nRed = (int)( w_red * 255.0 );
	w_nGreen = (int)( w_green * 255.0 );
	w_nBlue = (int)( w_blue * 255.0 );

	pRgb->r = w_nRed, pRgb->g = w_nGreen; pRgb->b = w_nBlue;
	return 1;
}

////////////////////////////////////////////////////////////////////////////////
//.Function	: SS_hue_2_RGB
//.Description	: Get the HUE Value from 3-Parameters Value of Any Color
//:=*===================*===============*=======================================
int										//.Return Value(Always 1)
SS_hue_2_RGB(
double				v1,				//.IN: 1st Parameter Value
double				v2,				//.IN: 2nd Parameter Value
double				vH,				//.IN: 3rd Parameter Value
double				*pHue			//.OUT: Result Hue Value
){
	if ( vH < 0.0 )
	{
		vH += 1.0;
	}
	if ( vH > 1.0 )
	{
		vH -= 1.0;
	}
	if ( (6.0 * vH) < 1.0 )
	{
		*pHue = v1 + (v2 - v1) * 6.0 * vH;
		goto L_EXIT;
	}
	if ( (2.0 * vH) < 1.0 )
	{
		*pHue = v2;
		goto L_EXIT;
	}
	if ( (3.0 * vH) < 2.0 )
		*pHue = v1 + (v2 - v1) * ((2.0 / 3.0) - vH) * 6.0;	
	else
		*pHue = v1;
L_EXIT:	
	return 1;
}

////////////////////////////////////////////////////////////////////////////////
//.Function	: SS_RgbToHsl
//.Description	: Get the HSL Value from RGB Value of Any Color
//:=*===================*===============*=======================================
int										//.Return Value(Always 1)
SS_RgbToHsl(							
LST_RGBCOLOR		rgb,			//.IN: RGB Value
LST_HSLCOLOR*		pHsl			//.OUT: HSL Value
){
	double				w_varR			= (rgb.r / 255.0); //.Where RGB values = 0 ¡À 255
	double				w_varG			= (rgb.g / 255.0);
	double				w_varB			= (rgb.b / 255.0);

	double				w_varMin;
	double				w_varMax;
	double				w_delMax; //.Delta RGB value

	double				w_h;
	double				w_s;
	double				w_l;
	double				w_delR;
	double				w_delG;
	double				w_delB;

	int					w_Hr;
	w_Hr = SS_getMinimumValue( w_varR, w_varG, w_varB, &w_varMin); //.Min. value of RGB
	w_Hr = SS_getMaximumValue( w_varR, w_varG, w_varB, &w_varMax); //.Max. value of RGB
	w_delMax = w_varMax - w_varMin; //.Delta RGB value
	w_l = (w_varMax + w_varMin) / 2;

	if ( w_delMax == 0 ) //.This is a gray, no chroma...
	{
		w_h = 0; //.HSL results = 0 ¡À 1
		//x s = 0;
		//. UK:
		w_s = 1.0;
	}
	else //.Chromatic data...
	{
		if ( w_l < 0.5 )
		{
			w_s = w_delMax / (w_varMax + w_varMin);
		}
		else
		{
			w_s = w_delMax / (2.0 - w_varMax - w_varMin);
		}

		w_delR = (((w_varMax - w_varR) / 6.0) + (w_delMax / 2.0)) / w_delMax;
		w_delG = (((w_varMax - w_varG) / 6.0) + (w_delMax / 2.0)) / w_delMax;
		w_delB = (((w_varMax - w_varB) / 6.0) + (w_delMax / 2.0)) / w_delMax;

		if ( w_varR == w_varMax )
		{
			w_h = w_delB - w_delG;
		}
		else if ( w_varG == w_varMax )
		{
			w_h = (1.0 / 3.0) + w_delR - w_delB;
		}
		else if (w_varB == w_varMax )
		{
			w_h = (2.0 / 3.0) + w_delG - w_delR;
		}
		else
		{
			//.Uwe Keim.
			w_h = 0.0;
		}

		if (w_h < 0.0 )
		{
			w_h += 1.0;
		}
		if (w_h > 1.0 )
		{
			w_h -= 1.0;
		}
	}


	pHsl->h = w_h * 360.0;
	pHsl->l = w_l * 100.0;
	pHsl->s = w_s * 100.0;
	return 1;
}

////////////////////////////////////////////////////////////////////////////////
//.Function	: SS_getMinimumValue
//.Description	: Get the minimum Value of 3-Values
//:=*===================*===============*=======================================
int										//.Return Value(Always 1)
SS_getMinimumValue(
double				x1,				//.IN:1st Value
double				x2,				//.IN:2nd Value
double				x3,				//.IN:3rd Value
double*				pMin			//.OUT:Minimum Value
){
   double				w_x;
   if(x1 > x2) 
	   w_x = x2;
   else
	   w_x = x1;
   if(w_x > x3)
	   w_x = x3;
   *pMin = w_x;
   return 1;
}

////////////////////////////////////////////////////////////////////////////////
//.Function	: SS_getMaximumValue
//.Description	: Get the maximum Value of 3-Values
//:=*===================*===============*=======================================
int										//.Return Value(Always 1)
SS_getMaximumValue(			
double				x1,				//.IN: 1st Value
double				x2,				//.IN: 2nd Value
double				x3,				//.IN: 3rd Value
double*				pMax			//.OUT: Maximum Value
){
   double				w_x;
   if(x1 > x2) 
	   w_x = x1;
   else
	   w_x = x2;
   if(w_x < x3)
	   w_x = x3;
   *pMax = w_x;
   return 1;
}

////////////////////////////////////////////////////////////////////////////////
//.Function	: SF_GetScreenWorkRect
//.Description	: Get the Rect of Work region of Windows Screen
//:=*===================*===============*=======================================
int										//.Return: always 0
SF_GetScreenWorkRect(
RECT* rcWork						//.OUT: Region Rect
){
	HMONITOR hMonitor;
	MONITORINFO mi;
	RECT ScreenRect, m_WindowRect;
	hMonitor = MonitorFromRect(&m_WindowRect, MONITOR_DEFAULTTONEAREST);
	mi.cbSize = sizeof(mi);
	GetMonitorInfo(hMonitor, &mi);
	ScreenRect = mi.rcWork;

	*rcWork = ScreenRect;
	return 0;
}

int 
SF_GetCMYKColComponent(
	COLORREF			crColor, 
	int*				colValues
){
	int w_c, w_m, w_y, w_k;
	COLORREF cmyk = RgbToCmyk(crColor);
	w_c = GetCValue(cmyk);
	w_m = GetMValue(cmyk);
	w_y = GetYValue(cmyk);
	w_k = GetKValue(cmyk);

	colValues[0] = w_c;
	colValues[1] = w_m;
	colValues[2] = w_y;
	colValues[3] = w_k;
	return 0;
}

int 
SF_GetRGBColComponent(
COLORREF			crColor, 
int*				colValues
){
   int w_r, w_g, w_b;
   w_r = GetRValue(crColor);
   w_g = GetGValue(crColor);
   w_b = GetBValue(crColor);   

   colValues[0] = w_r;
   colValues[1] = w_g;
   colValues[2] = w_b;
   return 0;
}

int 
SF_GetHSVColComponent(
COLORREF			crColor, 
int*				colValues
){
	long w_h, w_s, w_v;
	RgbToHsv((OLE_COLOR)crColor, w_h, w_s, w_v);
	colValues[0] = (int)w_h;
	colValues[1] = (int)w_s;
	colValues[2] = (int)w_v;
	return 0;
}

void RgbToHsv(OLE_COLOR nRgbColor,long&  Hue, long& Saturation, long& Value)
{
	float red = (float)GetRValue(nRgbColor) / 255;
	float green = (float)GetGValue(nRgbColor) / 255;
	float blue = (float)GetBValue(nRgbColor) / 255;

	float fHue, fSaturation, fValue;
	RgbToHsv(red, green, blue, &fHue, &fSaturation, &fValue);
	if(fHue < 0) return;

	Hue = (LONG)fHue;
	Saturation = LONG(fSaturation * 100);
	Value = LONG(fValue * 100);
}

OLE_COLOR HsvToRgb( long Hue, long Saturation, long Value)
{
	float fRed, fGreen, fBlue;
	HsvToRgb((float)Hue, (float)Saturation/100, (float)Value/100,&fRed, &fGreen, &fBlue);

	LONG red = LONG(fRed * 255);
	LONG green = LONG(fGreen * 255);
	LONG blue = LONG(fBlue * 255);

	return RGB(red, green, blue);
}

// h = [0,360], s = [0,1], v = [0,1]
// if s == 0, then h = -1 (undefined)
void RgbToHsv(float red, float green, float blue, 
			  float* hue, float* saturation, float* value)
{
	float nMin, nMax, nDelta;
	nMin = min(red, green);
	nMin = min(nMin, blue); 
	nMax = max(red, green);
	nMax = max(nMax, blue);

	*value = nMax;
	nDelta = nMax - nMin;
	if(nMax != 0)
		*saturation = nDelta / nMax; 
	else {
		*saturation = 0;
		*hue = -1;
		return;
	}

	if(red == nMax)
		*hue = (green - blue) / nDelta;         // between yellow and magenta.
	else if(green == nMax)
		*hue = 2 + (blue - red) / nDelta;     // between cyan and yellow.
	else
		*hue = 4 + (red - green) / nDelta;     // between magenta and cyan.

	*hue *= 60;                           // degrees
	if(*hue < 0) *hue += 360;
}

void HsvToRgb(float hue, float saturation, float value,float *red, float *green, float *blue)
{
	if(saturation == 0) {
		*red = *green = *blue = value;
		return;
	}

	int index;
	float colorValue1, colorValue2, colorValue3, colorValue4;
	hue /= 60;
	index =(int)floor(hue);
	colorValue1 = hue - index; 
	colorValue2 = value * (1 - saturation);
	colorValue3 = value * (1 - saturation * colorValue1);
	colorValue4 = value * (1 - saturation * (1 - colorValue1));

	switch( index ){
		case 0:
			*red = value;
			*green = colorValue4;
			*blue = colorValue2;
			break;
		case 1:
			*red = colorValue3;
			*green = value;
			*blue = colorValue2;
			break;
		case 2:
			*red = colorValue2;
			*green = value;
			*blue = colorValue4;
			break;
		case 3:
			*red = colorValue2;
			*green = colorValue3;
			*blue = value;
			break;
		case 4:
			*red = colorValue4;
			*green = colorValue2;
			*blue = value;
			break;
		default: 
			*red = value;
			*green = colorValue2;
			*blue = colorValue3;
			break;
	}
}

// r, g, b values are between in 0 and 1
void RgbToCmyk(float red, float green, float blue, 
			   float* cyan, float* magenta, float* yellow, float* black)
{
	float c = 1.0 - red;
	float m = 1.0 - green;
	float y = 1.0 - blue;

	float k = (double)min(c, min(m, y));

	if(k == 1.0)
	{
		*cyan = 0.0;
		*magenta = 0.0;
		*yellow = 0.0;
		*black = 1.0;
	}
	else
	{
		*cyan = (c - k) / (1.0 - k);
		*magenta = (m - k) / (1.0 - k);
		*yellow = (y - k) / (1.0 - k);
		*black = k;
	}
}

void CmykToRgb(float cyan, float magenta, float yellow, float black, 
			   float* red, float* green, float* blue)
{
	*red = (1.0 - cyan) * (1.0 - black);
	*green = (1.0 - magenta) * (1.0 - black);
	*blue = (1.0 - yellow) * (1.0 - black);
}

COLORREF RgbToCmyk(COLORREF nRgbColor)
{ 
 	float red = (float)GetRValue(nRgbColor) / 255.0;
 	float green = (float)GetGValue(nRgbColor) / 255.0;
 	float blue = (float)GetBValue(nRgbColor) / 255.0;
 
 	float cyan, magenta, yellow, black;
 	RgbToCmyk(red, green, blue, &cyan, &magenta, &yellow, &black);
 	COLORREF nCmykColor = CMYK((LONG)(cyan*100.0), (LONG)(magenta*100.0), (LONG)(yellow*100.0), (LONG)(black*100.0));
 
 	return nCmykColor;
}

COLORREF CmykToRgb(COLORREF nCmykColor)
{
	float cyan = (float)GetCValue(nCmykColor) / 100.0;
	float magenta = (float)GetMValue(nCmykColor) / 100.0;
	float yellow = (float)GetYValue(nCmykColor) / 100.0;
	float black = (float)GetKValue(nCmykColor) / 100.0;

	float red, green, blue;
	CmykToRgb(cyan, magenta, yellow, black, &red, &green, &blue);
	COLORREF nRgbColor = RGB((LONG)(red*255.0), (LONG)(green*255.0), (LONG)(blue*255.0));

	return nRgbColor;
}

double GetDegreeAngle(int x, int y)
{
	double al = atan2((double)y, (double)x);
// 	if(x < 0){
// 		al = al + 3.14159265;
// 	}
	if(al < 0)
		al += 3.14159265 * 2;
	al = al * 180 / 3.14159265;
	return al;
}