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
/*******************************************************************************/
/*        Define                                                               */
/*******************************************************************************/
/*******************************************************************************/
/*        Structure                                                             */
/*******************************************************************************/
/*******************************************************************************/
/*        Function                                                              */
/*******************************************************************************/

class CColorMap;
typedef CWindowImpl < CColorMap, CWindow, CWinTraits < WS_CHILD | WS_VISIBLE > > CCustStaic;
class CColorMap : public CCustStaic
{
public:
	DECLARE_WND_SUPERCLASS(NULL, _T("STATIC"))

	CColorMap(void);
	~CColorMap(void);
	BEGIN_MSG_MAP(CColorMap)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
	END_MSG_MAP()
//////////////////////////////////////////////////////////////////////////
//. Windows Message
	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
protected:
	int SS_DrawColorMap(HDC hdc, RECT rt);
private:
	COLORREF m_crResult;
	HDC  m_hDC;
	BOOL m_bMouseDown;
public:
//////////////////////////////////////////////////////////////////////////
//. My Public Functions
	COLORREF GetColor(){ return m_crResult; };
};

#endif //.#if !defined( __Cla_ColorMap_h__ )
//.EOF
