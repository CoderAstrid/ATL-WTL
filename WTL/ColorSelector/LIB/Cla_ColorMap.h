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
#if !defined( __Cla_ColorMap_h__ )
#define __Cla_ColorMap_h__

#pragma once

/*******************************************************************************/
/*        include                                                               */
/*******************************************************************************/
#include "CommonColorLib.h"
/*******************************************************************************/
/*        Define                                                               */
/*******************************************************************************/
/*******************************************************************************/
/*        Structure                                                             */
/*******************************************************************************/
/*******************************************************************************/
/*        Function                                                              */
/*******************************************************************************/

class CColorMap : 
	public CWindowImpl < CColorMap, 
						 CWindow, 
						 CWinTraits < WS_CHILD | WS_VISIBLE > 
					   >
{
public:
	DECLARE_WND_SUPERCLASS(NULL, _T("STATIC"))
	
	CColorMap()
	{
		m_hParentWnd = NULL;
		m_bMouseDown = FALSE;
		m_crResult = 0x000000;
		m_nID = efUnknown_Type;
	}

	CColorMap(HWND hParent, EF_COLORMAP_TYPE nID)
	{
		m_hParentWnd = hParent;
		m_bMouseDown = FALSE;
		m_crResult = 0x000000;
		m_nID = efUnknown_Type;
	}

	~CColorMap(void);
	BEGIN_MSG_MAP(CColorMap)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)	
		MESSAGE_HANDLER(WM_MOUSELEAVE, OnMouseLeave)
	END_MSG_MAP()
//////////////////////////////////////////////////////////////////////////
//. Windows Message
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMouseLeave(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
protected:
	int SS_DrawColorMap(HDC hdc, RECT rt);
private:
	COLORREF m_crResult;
	EF_COLORMAP_TYPE  m_nID;
	HWND m_hParentWnd;
	BOOL m_bMouseDown;	
};

class CColorStatic : public CWindowImpl < CColorStatic, CWindow, CWinTraits < WS_CHILD | WS_VISIBLE > >
{
public:
	DECLARE_WND_SUPERCLASS(NULL, _T("STATIC"))

	CColorStatic()
	{
		m_hParentWnd = NULL;
		m_bNullColor = FALSE;
		m_crResult = 0x000000;		
	}

	CColorStatic(HWND hParent, COLORREF crCol, BOOL bColor = FALSE)
	{
		m_hParentWnd = hParent;		
		m_crResult = crCol;
		m_bNullColor = bColor;
	}

	~CColorStatic(void)
	{
	}
	BEGIN_MSG_MAP(CColorMap)		
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
	END_MSG_MAP()

  	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
  	{
  		PAINTSTRUCT ps;
  		RECT rt;	
  		HDC hdc = BeginPaint(&ps);
  		::GetClientRect(m_hWnd, &rt);
  		DrawStatic(hdc, rt); 
  		EndPaint(&ps);
  		::ReleaseDC(m_hWnd, hdc);
  		return 1;
  	}

	void SetColor(COLORREF crCol, BOOL bNullColor = FALSE)
	{
		m_bNullColor = bNullColor;
 		m_crResult = crCol;

		Invalidate();
	}
protected:
	int DrawStatic(HDC hdc, RECT rt)
	{
		if(!m_bNullColor)
		{			
			HBRUSH hBrush = CreateSolidBrush(m_crResult);
			HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			FillRect(hdc, &rt, hBrush);
			SelectObject(hdc, oldBrush);			
			DeleteObject(hBrush);	
		}
		else
		{			
			HBRUSH hb = GetSysColorBrush(15);
			HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, hb);
			FillRect(hdc, &rt, hb);
			SelectObject(hdc, oldBrush);			
			DeleteObject(hb);
		}
		return 0;
	}
private:
	COLORREF m_crResult;	
	HWND m_hParentWnd;
	BOOL m_bNullColor;		
};

#endif //.#if !defined( __Cla_ColorMap_h__ )
//.EOF
