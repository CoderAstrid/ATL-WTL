//******************************************************************************
//* File Name	: Cla_ColorMap.h
//* Description	: Color Picker With HLS Color Gradient
//*
//* (c)Copyright 2012 DR TECHNOLOGY CO., LTD. All Rights Reserved.
//* ----------------------------------------------------------------------------
//* History
//* Rev     	Date		Reason		Author
//* Rev.01	 	2012-04-06	 New        Jewel
//								
//******************************************************************************
#if !defined( __Cla_HSV_ColorMap_h__ )
#define __Cla_HSV_ColorMap_h__

#pragma once

/*******************************************************************************/
/*        include                                                               */
/*******************************************************************************/
#include "CommonColorLib.h"
#include "BufferDC.h"
/*******************************************************************************/
/*        Define                                                               */
/*******************************************************************************/
/*******************************************************************************/
/*        Structure                                                             */
/*******************************************************************************/
/*******************************************************************************/
/*        Function                                                              */
/*******************************************************************************/

#pragma once

class CHSVColorMapCtrl : 
	public CWindowImpl < CHSVColorMapCtrl, 
	CWindow, 
	CWinTraits < WS_CHILD | WS_VISIBLE > 
	>
{
	DECLARE_WND_SUPERCLASS(NULL, _T("STATIC"))
public:	
	~CHSVColorMapCtrl(void)
	{
		Destroy();
	}
	void Destroy()
	{
// 		if(m_Buffer != NULL){
// 			m_Buffer->Destroy();
// 			m_Buffer = NULL;
// 		}	
		m_bFirstStart = FALSE;
		DestroyWindow();
	}
	CHSVColorMapCtrl()
	{
		m_hParentWnd = NULL;
		m_hBitmap = NULL;
//		m_bDirty = TRUE;
		m_bMouseDown = FALSE;
		m_crResult = 0x000000;
//		m_Buffer = NULL;
		m_nID = efUnknown_Type;
		m_bFirstStart = FALSE;
	}

	CHSVColorMapCtrl(HWND hParent, int nID)
	{
		m_hParentWnd = hParent;
		m_bMouseDown = FALSE;
		m_crResult = 0x000000;
//		m_Buffer = NULL;
		m_nID = efUnknown_Type;
		m_bFirstStart = FALSE;
	}
protected:
	BOOL m_bMouseDown;
	HBITMAP m_hBitmap;
/*	BOOL m_bDirty;*/
/*	CBufferDC* m_Buffer;*/
	int  m_nID;
	long m_nHue, m_nValue, m_nSaturation;
	COLORREF m_crResult;
	HWND m_hParentWnd;
	int m_nDiam;
	BOOL m_bFirstStart;
protected:
	void DrawHSVColorMap(HDC hdc, RECT rt)
	{
// 		if(m_bDirty){
			PutBitmapMap(hdc, rt);
			DrawAngleHandle(hdc);
			DrawTrianglePosition(hdc);
// 		}else{
// 			m_Buffer->Update();
// 		}		
	}

	void PutBitmapMap(HDC hdc, RECT rt)
	{
		CBufferDC m_Buffer(hdc, rt);
// 		if(m_Buffer != NULL)
// 			m_Buffer->Destroy();
//		m_Buffer = new CBufferDC(hdc, rt);
		
		int cr = m_nDiam;
		int m_h =-1 ;
		int Radius = cr / 4;
		double fPI =3.14159265;
		double h, s = 100.0, v = 100.0;
		COLORREF col; int x, y, x0, y0; double ang;

// 		HDC memDC = CreateCompatibleDC ( hdc );
// 		HBITMAP memBM = CreateCompatibleBitmap ( hdc, cw, ch );
// 		HBITMAP hOld = (HBITMAP)SelectObject ( memDC, memBM );

		HBRUSH hOrg = GetSysColorBrush(15);
		FillRect(m_Buffer.GetHDC(), &rt, hOrg);
		HPEN hPen = CreatePen(PS_NULL, 1, 0);
		HPEN oldPen = (HPEN)SelectObject(m_Buffer.GetHDC(), hPen);
		double aStep = fPI / 180.0 * 2;
		for(h = 0; h < 360; h+=2){
			ang = (double)h * aStep / 2;
			col = HsvToRgb((long)h, (long)s, (long)v);			
			x = Radius + cosf(ang) * (double)Radius;
			y = -sinf(ang) * (double)Radius + 3 * Radius;
			x0 = Radius + cosf(ang + aStep) * (double)Radius;
			y0 = -sinf(ang + aStep) * (double)Radius + 3 * Radius;
			HBRUSH hBrush = CreateSolidBrush(col);
			HBRUSH oldBrush = (HBRUSH)SelectObject(m_Buffer.GetHDC(), hBrush);			
			Pie(m_Buffer.GetHDC(), 0, 2 * Radius, 2 * Radius, 4 * Radius, x, y, x0, y0);
			SelectObject(m_Buffer.GetHDC(), oldBrush);
			DeleteObject(hBrush);
		}
		SelectObject(m_Buffer.GetHDC(), oldPen);
		DeleteObject(hPen);
 		for(int x = 0; x < cr; x++)
 		{			
 			for(int y = 0; y < x; y++)
 			{
 				s = (double)(x - y) * 100.0 / (double)cr;
 				v = (double)(cr - y) * 100.0 /(double)cr;
				if(m_nSaturation == 0) s = 0;
 				col = HsvToRgb(m_nHue, (long)s, (long)v);
 				SetPixel(m_Buffer.GetHDC(), x, y, col);
 			}
 		}
		m_Buffer.Destroy();

		DeleteObject(hOrg);
//		m_bDirty = FALSE;
	}
public:
	BEGIN_MSG_MAP(CHSVColorMapCtrl)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
	END_MSG_MAP()
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
protected:
	BOOL PtInSVTriangle(POINT point);
	int XY2SV(int x, int y, int* s, int* v);
	int SV2XY(int s, int v, int* x, int* y);
public:
	int SetHSV(int h, int s, int v);
	int GetHSV(int* h, int* s, int* v);
protected:
	void UpDateControl(BOOL bDraw = TRUE);
	void DrawAngleHandle(HDC hdc);
	void DrawTrianglePosition(HDC hdc, BOOL bDraw = TRUE);
};

#endif //.#if !defined( __Cla_HSV_ColorMap_h__ )
//.EOF
