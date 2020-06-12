#include "StdAfx.h"
#include "HSVColorMapCtrl.h"

LRESULT CHSVColorMapCtrl::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	
	
	return 0;
}

LRESULT CHSVColorMapCtrl::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// TODO: Add your message handler code here and/or call default

	return 0;
}

LRESULT CHSVColorMapCtrl::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	m_bMouseDown = TRUE;
	::SetCapture(m_hWnd);

	return 0;
}

LRESULT CHSVColorMapCtrl::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if(m_bMouseDown){
		POINT p2;
		p2.x = LOWORD(lParam);
		p2.y = HIWORD(lParam);

		HDC hdc = ::GetDC(m_hWnd);
		::LPtoDP(hdc, &p2, 1);
		if(PtInSVTriangle(p2)){
			int s, v;
			XY2SV(p2.x, p2.y, &s, &v);
			m_nSaturation = s;
			m_nValue = v;
			UpDateControl();
		}
		else
		{
			double h = GetDegreeAngle(p2.x - m_nDiam / 4, m_nDiam * 3 / 4 -  p2.y);
			m_nHue = h;
			UpDateControl();
		}
	}
	m_bMouseDown = FALSE;
	::ReleaseCapture();
		
	return 0;
}

LRESULT CHSVColorMapCtrl::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HWND hWnd = ::GetCapture();
	if(m_bMouseDown && hWnd == m_hWnd){
		POINT p2;
		p2.x = LOWORD(lParam);
		p2.y = HIWORD(lParam);

		HDC hdc = ::GetDC(m_hWnd);
		::LPtoDP(hdc, &p2, 1);
		if(PtInSVTriangle(p2)){
			int s, v;
			XY2SV(p2.x, p2.y, &s, &v);
			m_nSaturation = s;
			m_nValue = v;
			UpDateControl(FALSE);
		}
		else
		{
			double h = GetDegreeAngle(p2.x - m_nDiam / 4, m_nDiam * 3 / 4 -  p2.y);
			m_nHue = h;
			UpDateControl();
		}
	}

	return 0;
}

LRESULT CHSVColorMapCtrl::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
 	if(!m_bFirstStart){
 		RECT rc;
 		GetClientRect(&rc);
 		int w, h;
 		h = rc.bottom - rc.top;
 		w = rc.right - rc.left;
 		m_nDiam = min(w,h);
 		m_bFirstStart = TRUE;
 	}
 	PAINTSTRUCT ps;
 	RECT rt;	
 	HDC hdc = BeginPaint(&ps);
 	//m_hDC = ::GetDC(m_hWnd);
 
 	::GetClientRect(m_hWnd, &rt);
 	DrawHSVColorMap(hdc, rt); 
 	EndPaint(&ps);
 	::ReleaseDC(m_hWnd, hdc);

	return 0;
}

BOOL CHSVColorMapCtrl::PtInSVTriangle(POINT point)
{
	RECT rc;
	int cw, ch, cr, x, y;
	
	x = point.x; y = point.y;	
	return (x < m_nDiam && x > y);
}

int CHSVColorMapCtrl::XY2SV(int x, int y, int* s, int* v)
{
	*s = (x - y) * 100 / m_nDiam;
	*v = (m_nDiam - y) * 100 / m_nDiam;
	if(*s < 0) *s = 0;
	if(*s > 100) *s = 100;
	if(*v < 0) *v = 0;
	if(*v > 100) *v = 100;
	return 0;
}

int CHSVColorMapCtrl::SV2XY(int s, int v, int* x, int* y)
{
	*y = (100 - v) * m_nDiam / 100;
	*x = (s + 100 - v) * m_nDiam / 100;

	return 0;
}

int CHSVColorMapCtrl::SetHSV(int h, int s, int v)
{
	m_nHue = (h < 0 ? 0: (h > 360 ? 360 : h));
	m_nSaturation = (s < 0 ? 0: (s > 100 ? 100 : s));
	m_nValue = (v < 0 ? 0: (v > 100 ? 100 : v));
	UpDateControl();
	return 0;
}


int CHSVColorMapCtrl::GetHSV(int* h, int* s, int* v)
{
	*h = m_nHue;
	*s = m_nSaturation;
	*v = m_nValue;
	return 0;
}

void CHSVColorMapCtrl::UpDateControl(BOOL bDraw /* = TRUE*/)
{
	HDC hdc = GetDC();
	RECT rc;
	if(m_nSaturation == 0 || m_nValue == 0)
	{
		m_nSaturation = 0;
	}
	GetClientRect(&rc);
	PutBitmapMap(hdc, rc);
	DrawAngleHandle(hdc);
	DrawTrianglePosition(hdc, bDraw);
	ReleaseDC(hdc);
}

void CHSVColorMapCtrl::DrawAngleHandle(HDC hdc)
{
	int cr = m_nDiam / 4;
	int x, y;
	double angle = 3.14159265 * m_nHue / 180.0;
	x = cosf(angle) * cr + cr;
	y = -sin(angle) * cr + 3 * cr;
	HPEN hPen = CreatePen(PS_SOLID, 1, 0);
	HPEN hOld = (HPEN)SelectObject(hdc, hPen);
	MoveToEx(hdc, cr , 3 * cr, (LPPOINT)NULL);
	LineTo(hdc, x, y);
	SelectObject(hdc, hOld);
	DeleteObject(hPen);
}

void CHSVColorMapCtrl::DrawTrianglePosition(HDC hdc, BOOL bDraw /* = TRUE*/)
{
	if(!bDraw) return;
	int x, y;
	SV2XY(m_nSaturation, m_nValue, &x, &y);
	HPEN hPen = CreatePen(PS_SOLID, 2, 0);
	//HBRUSH hBrush = CreateSolidBrush(0);
	HPEN oldPen = (HPEN)SelectObject(hdc, hPen);
	MoveToEx(hdc, x-4, y-4,(LPPOINT)NULL);
	LineTo(hdc, x-4, y + 4);
	LineTo(hdc, x+4, y+4);
	LineTo(hdc, x+4, y -4);
	LineTo(hdc, x-4, y-4);
	//Rectangle(hdc, x - 4, y - 4, x + 4, y + 4);
	SelectObject(hdc, oldPen);
	DeleteObject(hPen);
	//y += m_nDiam / 4;
}
