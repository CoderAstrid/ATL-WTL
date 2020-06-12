// ColPropertySelForm.cpp : Implementation of CColPropertySelForm

#include "stdafx.h"
#include "ColPropertySelForm.h"
#include "LIB/CommonColorLib.h"

// CColPropertySelForm

//. Event which is occurred in selecting the "Use the Windows Dither" Check Box
LRESULT CColPropertySelForm::OnBnClickedChkDithering(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	BOOL bRes = !(m_bUseWindowsDithering);
	m_chkUseWinDit.SetCheck(bRes);
	m_bUseWindowsDithering = bRes;
	return 0;
}

//. Event which is occurred in selecting the "Null color" Check Box
LRESULT CColPropertySelForm::OnBnClickedChkNull(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	BOOL bRes = !(m_bNullColor);
	m_chkNullCol.SetCheck(bRes);
	m_bNullColor = bRes;
	::PostMessage(GetParent().m_hWnd, CPN_SELCHANGE, 0L, 1L);
	return 0;
}
