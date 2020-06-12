// ColPaletteSelWnd.cpp : Implementation of CColPaletteSelWnd

#include "stdafx.h"
#include "ColPaletteSelWnd.h"


// CColPaletteSelWnd


LRESULT CColPaletteSelWnd::OnHScroll(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HWND slideWnd = (HWND)lParam;
	ATLASSERT(::IsWindow(slideWnd));
	
	int nPos = ::SendMessage(slideWnd, TBM_GETPOS, 0, 0L);

	if(slideWnd == GetDlgItem(4459)) 
		m_nPos = nPos;	
	WPARAM wP = MAKEWPARAM(m_nID, m_eColorMapType);	
	::SendMessage(m_hParent, WM_NOTIFY, wP, (LPARAM)nPos);	

	return 0;
}

void CColPaletteSelWnd::SetPos(int nPos)
{
	m_nPos = nPos;
	m_Slider.SetPos(nPos);
}

void CColPaletteSelWnd::DrawStatic()
{
	RECT rc; int cw, ch, x;
	//if(m_bDrawing) return;
	//m_bDrawing = TRUE;
	HDC hdc = m_ctlStatic.GetDC();
	
	m_ctlStatic.GetClientRect(&rc);
	cw = rc.right - rc.left;
	ch = rc.bottom - rc.top;

	HDC memDC = ::CreateCompatibleDC ( hdc );	
	HBITMAP memBM = CreateCompatibleBitmap ( hdc, cw, ch);	
	HBITMAP oldBmp = (HBITMAP)SelectObject ( memDC, memBM );
	
	COLORREF crColor = *m_pColor;
	if(m_eColorMapType == efRGB_Type){
		int nR = GetRValue(crColor);
		int nG = GetGValue(crColor);
		int nB = GetBValue(crColor);
		COLORREF col; int i;
		for(int x = 0; x < cw; x++){
			i = (double)255.0 * (double)x / cw;
			if(m_nID == 0){
				col = RGB(i, nG, nB);
			}else if(m_nID == 1){
				col = RGB(nR, i, nB);
			}else if(m_nID == 2){
				col = RGB(nR, nG, i);
			}
			HPEN hPen = CreatePen(PS_SOLID, 1, col);
			HPEN oldPen = (HPEN)SelectObject(memDC, hPen);
			MoveToEx(memDC, x, 0, (LPPOINT)NULL);
			LineTo(memDC, x, ch);
			SelectObject(memDC, oldPen);
			DeleteObject(hPen);
		}
	}else if(m_eColorMapType == efCMYK_Type){
		COLORREF cmyk = RgbToCmyk(crColor);
		int nC = GetCValue(cmyk);
		int nM = GetMValue(cmyk);
		int nY = GetYValue(cmyk);
		int nK = GetKValue(cmyk);		
		COLORREF col; int i;
		for(int x = 0; x < cw; x++){
			i = (int)(100.0 * (double)x / (double)cw);
			COLORREF newCMYK;
			if(m_nID == 0){
				newCMYK = CMYK(i, nM, nY, nK);
			}else if(m_nID == 1){
				newCMYK = CMYK(nC, i, nY, nK);
			}else if(m_nID == 2){
				newCMYK = CMYK(nC, nM, i, nK);
			}else if(m_nID == 3){
				newCMYK = CMYK(nC, nM, nY, i);
			}
			col = CmykToRgb(newCMYK);
			HPEN hPen = CreatePen(PS_SOLID, 1, col);
			HPEN oldPen = (HPEN)SelectObject(memDC, hPen);
			MoveToEx(memDC, x, 0, (LPPOINT)NULL);
			LineTo(memDC, x, ch);
			SelectObject(memDC, oldPen);
			DeleteObject(hPen);
		}
	}else if(m_eColorMapType == efHSV_Type){		
		long h, s, v; int nMv[3] = {360, 100, 100};
		RgbToHsv(crColor, h, s, v);
		COLORREF col; int i;
		for(int x = 0; x < cw; x++){
			i = (int)(nMv[m_nID] * (double)x / (double)cw);
			if(m_nID == 0){
				col = HsvToRgb(i,s, v);
			}else if(m_nID == 1){
				col = HsvToRgb(h,i, v);
			}else if(m_nID == 2){
				col = HsvToRgb(h,s, i);
			}
			
			HPEN hPen = CreatePen(PS_SOLID, 1, col);
			HPEN oldPen = (HPEN)SelectObject(memDC, hPen);
			MoveToEx(memDC, x, 0, (LPPOINT)NULL);
			LineTo(memDC, x, ch);
			SelectObject(memDC, oldPen);
			DeleteObject(hPen);
		}
	}else{

	}
	BitBlt(hdc, 0, 0, cw, ch, memDC, 0, 0, SRCCOPY);	
	SelectObject(memDC, oldBmp);
	//m_ctlStatic.SetBitmap(memBM);
	DeleteObject(memBM);	
	DeleteDC(memDC);
	m_ctlStatic.ReleaseDC(hdc);
	//m_bDrawing = FALSE;
}


LRESULT CColPaletteSelWnd::OnShowWindow(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	DrawStatic();

	return 0;
}
