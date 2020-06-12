//******************************************************************************
//* File Name	: Cla_ColorMap.cpp
//* Description	: Color Picker With HLS Color Gradient
//*
//* (c)Copyright 2012 DR TECHNOLOGY CO., LTD. All Rights Reserved.
//* ----------------------------------------------------------------------------
//* History
//* Rev     	Date		Reason		Author
//* Rev.01	 	2012-04-06  New         Jewel
//								
//******************************************************************************

/*******************************************************************************/
/*        include                                                               */
/*******************************************************************************/
#include "StdAfx.h"
#include "Cla_ColorMap.h"
#include <math.h>
/*******************************************************************************/
/*        Define                                                               */
/*******************************************************************************/
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
/*******************************************************************************/
/*        Function                                                              */
/*******************************************************************************/
int SS_hue_2_RGB(double v1, double v2, double vH, double* pHue);
int SS_HslToRgb(LST_HSLCOLOR hsl, LST_RGBCOLOR* pRgb);
int SS_getMinimumValue(double x1, double x2, double x3, double* pMin);
int SS_getMaximumValue(double x1, double x2, double x3, double* pMax);
int SS_RgbToHsl(LST_RGBCOLOR rgb, LST_HSLCOLOR* pHsl);

CColorMap::CColorMap(void)
{
	m_bMouseDown = FALSE;
	m_crResult = 0x000000;
}

CColorMap::~CColorMap(void)
{
}

////////////////////////////////////////////////////////////////////////////////
//.Function	: SS_DrawColorMap
//.Description	: Draw the HLS Color Map Rectangle
//:=*===================*===============*=======================================
int										//.Return: Always 1 
CColorMap::SS_DrawColorMap(			
	HDC					hdc,			//.IN: HDC which Draw
	RECT				rt				//.IN: RECT which Draw
){
	int					w_ch			= rt.bottom - rt.top;		
	int					w_cw			= rt.right - rt.left;
	int					w_Hr;
	LST_RGBCOLOR		w_rgb;
	LST_HSLCOLOR		w_hsl;
	for(int y = 0; y < w_ch; ++y)
	{
		for(int x = 0; x < w_cw; ++x)
		{
			w_hsl.h		= 360.0 * (double)x / (double)w_cw;
			w_hsl.l		= 100.0 * (double)(w_ch - y)/(double)w_ch;
			w_hsl.s		= 100.0;			
			
			w_Hr = SS_HslToRgb(w_hsl, &w_rgb);
			COLORREF col = RGB(w_rgb.r, w_rgb.g, w_rgb.b);
			SetPixel(hdc, x + rt.left, y + rt.top, col);
		}
	}
	return 1;
}

LRESULT CColorMap::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// TODO: Add your message handler code here and/or call default

	return 0;
}

LRESULT CColorMap::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// TODO: Add your message handler code here and/or call default

	return 0;
}



LRESULT CColorMap::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
 	if (m_bMouseDown)
 	{
 			m_bMouseDown = FALSE;
 	}

	::SetCapture(m_hWnd);
	m_bMouseDown = TRUE;

	return 0;
}

LRESULT CColorMap::OnLButtonUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{	
	if(m_bMouseDown)
		::ReleaseCapture();
	m_bMouseDown = FALSE;
	return 0;
}

LRESULT CColorMap::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HWND hWND = ::GetCapture();
 	if ((m_bMouseDown) &&(hWND == m_hWnd))
 	{
		::ReleaseCapture();
 		POINT p2;
 		p2.x = LOWORD(lParam);
 		p2.y = HIWORD(lParam);
 
 		
 		//HWND mouse_wnd = ::WindowFromPoint(p2);
		HDC hdc = ::GetDC(m_hWnd);
		::LPtoDP(hdc, &p2, 1);		
		m_crResult = GetPixel(hdc, p2.x, p2.y);
		
		::ReleaseDC(m_hWnd,hdc);
		if(m_crResult == CLR_INVALID)
			p2.x += 0;
		::SendMessage(m_hWnd, WM_CTLCOLOREDIT, 0L, 0L);
 	}
 	return 0;
}

//:=*===================*===============*=======================================
LRESULT CColorMap::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	PAINTSTRUCT ps;
	RECT rt;	
	HDC hdc = BeginPaint(&ps);
	//m_hDC = ::GetDC(m_hWnd);
	
	::GetClientRect(m_hWnd, &rt);
	SS_DrawColorMap(hdc, rt); 
	EndPaint(&ps);
	::ReleaseDC(m_hWnd, hdc);
	return 0;
}

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
	double				w_varR			= (rgb.r / 255.0); //.Where RGB values = 0 �� 255
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
		w_h = 0; //.HSL results = 0 �� 1
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