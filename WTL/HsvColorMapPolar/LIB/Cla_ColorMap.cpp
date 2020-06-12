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
#include ".\Cla_ColorMap.h"

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

	HDC memDC = CreateCompatibleDC ( hdc );
	HBITMAP memBM = CreateCompatibleBitmap ( hdc, w_cw, w_ch );
	HBITMAP hOld = (HBITMAP)SelectObject ( memDC, memBM );

	for(int y = 0; y < w_ch; ++y)
	{
		for(int x = 0; x < w_cw; ++x)
		{
			w_hsl.h		= 360.0 * (double)x / (double)w_cw;
			w_hsl.s		= 100.0 * (double)(w_ch - y)/(double)w_ch;
			w_hsl.l		= 50;			
			
			w_Hr = SS_HslToRgb(w_hsl, &w_rgb);
			COLORREF col = RGB(w_rgb.r, w_rgb.g, w_rgb.b);
			SetPixel(memDC, x + rt.left, y + rt.top, col);
		}
	}

	BitBlt(hdc, 0, 0, w_cw, w_ch, memDC, 0, 0, SRCCOPY);
	SelectObject(memDC, hOld);
	DeleteObject(memBM);
	DeleteDC(memDC);

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
	::SetCapture(m_hWnd);
	m_bMouseDown = TRUE;

	return 0;
}

LRESULT CColorMap::OnMouseLeave(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}
LRESULT CColorMap::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{	
	if(m_bMouseDown){
		HWND hWND = ::GetCapture();
		::ReleaseCapture();		
		if (hWND == m_hWnd)
		{			
			POINT p2;
			p2.x = LOWORD(lParam);
			p2.y = HIWORD(lParam);
			
			HDC hdc = ::GetDC(m_hWnd);
			::LPtoDP(hdc, &p2, 1);		
			m_crResult = GetPixel(hdc, p2.x, p2.y);

			::ReleaseDC(m_hWnd,hdc);
			WPARAM wParam = MAKEWPARAM(m_nID, 0xFF);
			if(m_crResult != CLR_INVALID)
				::SendMessage(m_hParentWnd, WM_NOTIFY, wParam, m_crResult);
		}
	}
	m_bMouseDown = FALSE;
	return 0;
}

LRESULT CColorMap::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HWND hWND = ::GetCapture();
 	if ((m_bMouseDown) &&(hWND == m_hWnd))
 	{
		//::ReleaseCapture();
 		POINT p2;
 		p2.x = LOWORD(lParam);
 		p2.y = HIWORD(lParam);
 
 		HDC hdc = ::GetDC(m_hWnd);
		::LPtoDP(hdc, &p2, 1);		
		m_crResult = GetPixel(hdc, p2.x, p2.y);
		
		//::ReleaseDC(m_hWnd,hdc);
		WPARAM wParam = MAKEWPARAM(m_nID, 0xFF);
		if(m_crResult != CLR_INVALID)
			::SendMessage(m_hParentWnd, WM_NOTIFY, wParam, m_crResult);

// 		TRACKMOUSEEVENT t = 
// 		{
// 			sizeof(TRACKMOUSEEVENT),
// 			TME_LEAVE,
// 			m_hWnd,
// 			0
// 		};
// 		if (::_TrackMouseEvent(&t))
// 		{
// 			//m_bTracking = true;
// 			Invalidate();
// 		}

 	}
 	return 0;
}

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
