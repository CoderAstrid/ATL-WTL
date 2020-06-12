//////////////////////////////////////
// Memory Bitmap DC
// Author:	HKG 
// Date:	June 8,2006 
#pragma once
#include "Windows.h"
class CBufferDC
{
public:
	CBufferDC(HDC hDC, const RECT rcClient)	: m_bmOld(NULL)
	{
		m_dcMain = hDC ;
		m_dcThis = CreateCompatibleDC(m_dcMain);

// 		HRGN hRgn = CreateRectRgn(rcClient.left, rcClient.top, rcClient.right, rcClient.bottom);		
// 		ExtSelectClipRgn(m_dcThis, hRgn, RGN_AND);

		m_bmBuffer = CreateCompatibleBitmap(m_dcMain, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top);

		m_bmOld = (HBITMAP)SelectObject(m_dcThis, m_bmBuffer);

		//	FillSolidRect(&rcClient, GetSysColor(COLOR_MENU));
		HBRUSH hBrush = CreateSolidBrush(0xFFFFFF);
		HBRUSH hOld = (HBRUSH)SelectObject(m_dcThis, hBrush);
		FillRect(m_dcThis, &rcClient, hBrush);
		SelectObject(m_dcThis, hOld);
		DeleteObject(hBrush);
//		DeleteObject(hRgn);

		m_rcClient = rcClient;
		m_bDestroyed = FALSE;
	}
	void Update()
	{
		BitBlt(m_dcMain, 0, 0, m_rcClient.right - m_rcClient.left, m_rcClient.bottom - m_rcClient.top, m_dcThis, 0 ,0 , SRCCOPY);
	}
	void Destroy()
	{
		if(m_bDestroyed) return;
		BitBlt(m_dcMain, 0, 0, m_rcClient.right - m_rcClient.left, m_rcClient.bottom - m_rcClient.top, m_dcThis, 0 ,0 , SRCCOPY);
		SelectObject(m_dcThis, m_bmOld);
		DeleteObject(m_bmBuffer);
		DeleteDC(m_dcThis);
		m_bDestroyed = TRUE;
	}
	~CBufferDC()	
	{
		Destroy();
	}
	HDC GetHDC()
	{
		return m_dcThis;
	}
private:
	HDC		 m_dcMain;
	HDC		 m_dcThis;
	HBITMAP  m_bmBuffer;
	HBITMAP  m_bmOld;
	RECT	 m_rcClient;	
	BOOL     m_bDestroyed;
};
