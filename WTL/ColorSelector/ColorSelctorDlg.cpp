// ColorSelctorDlg.cpp : Implementation of CColorSelctorDlg

#include "stdafx.h"
#include "ColorSelctorDlg.h"
// CColorSelctorDlg


LRESULT CColorSelctorDlg::OnBnClickedAdvancedBtn(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your control notification handler code here

	return 0;
}

LRESULT CColorSelctorDlg::OnTcnSelchangeClrspaceTab(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/)
{
	int nCur = TabCtrl_GetCurSel(m_hTabHwnd);
	int index = m_nCurForm;
	if(nCur == 0){
		int i = m_ctrlCombo.GetCurSel();
		if(i < 0) i = 0;
		index = i;

	}else if(nCur == 1){
		index = 4;		
	}
	if(index != m_nCurForm){
		SetFormInTab(index);
		m_nCurForm = index;
	}
	m_nCurForm = index;

	return 0;
}

LRESULT CColorSelctorDlg::OnCbnSelchangeColspcCombo(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	int nCur = TabCtrl_GetCurSel(m_hTabHwnd);
	int index = m_nCurForm;

	int i = m_ctrlCombo.GetCurSel();
	if(i < 0) i = 0;
	index = i;		
	
	if(index != m_nCurForm){
		SetFormInTab(index);
		m_nCurForm = index;
	}
	m_nCurForm = index;

	return 0;
}

void CColorSelctorDlg::CreateTabCtrl(void)
{
	RECT rc0, rc, rc1;
	CWindow wnd0, wnd;
	HWND pp;
	int  w, h, cx, cy;
	int* colValues;
	
//.Calculate the position and size of the Tab Items
	wnd = GetDlgItem(IDC_CLRSPACE_TAB);	
	wnd.GetWindowRect(&rc0);
	wnd0 = GetDlgItem(IDC_PAN_GRP);	
	wnd0.GetWindowRect(&rc);	
		
	w = (rc.right - rc.left); h = (rc.bottom - rc.top);
	cx = rc.left - rc0.left; cy = rc.top - rc0.top;
	rc1.left = cx; rc1.top = cy; 
	rc1.right = cx + w; rc1.bottom = cy + h;
//. CMYK Tab Create	
	m_hTabHwnd = wnd.m_hWnd;
	m_pColorTab = new TCITEM;
	m_pColorTab->mask = TCIF_TEXT | TCIF_IMAGE;
	m_pColorTab->iImage = -1;
	m_pColorTab->pszText = _T("CMYK");

	m_pDlg1 = new CCmykSelForm;
	m_pDlg1->m_pSelColor = &m_selColor;
	m_pDlg1->Create(m_hWnd);
	colValues = m_pDlg1->GetColorComponentsBuffer();
	SF_GetCMYKColComponent(m_selColor, colValues);	
	
	m_pDlg1->ModifyStyle(WS_CAPTION , WS_CHILD);
	m_pDlg1->MoveWindow(&rc1);

	m_pColorTab->lParam = (LPARAM)m_pDlg1->m_hWnd;
	TabCtrl_InsertItem(m_hTabHwnd, 0, m_pColorTab);
//.HSV Dlg Create
	m_pDlg2 = new CHsvSelForm;
	m_pDlg2->m_pSelColor = &m_selColor;
 	m_pDlg2->Create(m_hWnd);
	colValues = m_pDlg2->GetColorComponentsBuffer();
	SF_GetHSVColComponent(m_selColor, colValues);	
	m_pDlg2->ModifyStyle(WS_CAPTION , WS_CHILD);
	m_pDlg2->MoveWindow(&rc1);
	
//.RGB Dlg Create
	m_pDlg3 = new CRrgSelForm;
	m_pDlg3->m_pSelColor = &m_selColor;
	m_pDlg3->Create(m_hWnd);
	colValues = m_pDlg3->GetColorComponentsBuffer();
	SF_GetRGBColComponent(m_selColor, colValues);	
	m_pDlg3->ModifyStyle(WS_CAPTION , WS_CHILD);
	m_pDlg3->MoveWindow(&rc1);
//.Properties Tab Create
	m_pPropertyTab = new TCITEM;
	m_pPropertyTab->mask = TCIF_TEXT | TCIF_IMAGE;
	m_pPropertyTab->iImage = -1;
	m_pPropertyTab->pszText = _T("Properties");

	m_pDlg4 = new CColPropertySelForm;
	m_pDlg4->m_bNullColor = m_bNullColor;
	m_pDlg4->m_bUseWindowsDithering = m_bUseWindowsDithering;

	m_pDlg4->Create(m_hWnd);	
	m_pDlg4->ModifyStyle(WS_CAPTION , WS_CHILD);
	m_pDlg4->MoveWindow(&rc1);

	m_pPropertyTab->lParam = (LPARAM)m_pDlg4->m_hWnd;
	TabCtrl_InsertItem(m_hTabHwnd, 1, m_pPropertyTab);
//.UI Default Setting
	TabCtrl_SetCurSel(m_hTabHwnd, 0);
	m_pDlg1->ShowWindow(SW_SHOW);
	Invalidate();
}

int CColorSelctorDlg::DestroyAllWindow(void)
{
	CWindow wnd = GetDlgItem(IDC_CLRSPACE_TAB);
	TabCtrl_DeleteAllItems(wnd.m_hWnd);
	delete m_pPropertyTab;
	delete m_pColorTab;
	
	m_pDlg1->DestroyWindow();
	delete m_pDlg1;
	m_pDlg2->DestroyWindow();
	delete m_pDlg2;
	m_pDlg3->DestroyWindow();
	delete m_pDlg3;
	m_pDlg4->DestroyWindow();
	delete m_pDlg4;

	//m_pDlg1->DestroyWindow();
	//m_pDlg2->DestroyWindow();
	//m_pDlg3->DestroyWindow();
	//m_pDlg4->DestroyWindow();
	
 	if(m_pctlColor != NULL){
		m_pctlColor->DestroyWindow();
		delete m_pctlColor;
 		//m_pctlColor->DestroyWindow();
 		m_pctlColor = NULL;
 	}
	if(m_pctlSelColor != NULL){
		m_pctlSelColor->DestroyWindow();
		delete m_pctlSelColor;
		//m_pctlSelColor->DestroyWindow();
		m_pctlSelColor = NULL;
	}
	return 0;
}

int CColorSelctorDlg::CreateControls(void)
{
	m_selColor = m_crColor;
	m_ctrlCombo = GetDlgItem(IDC_COLSPC_COMBO);
	
	m_ctrlCombo.ResetContent();

	m_ctrlCombo.AddString(_T("CMYK"));
	m_ctrlCombo.AddString(_T("HSV"));
	m_ctrlCombo.AddString(_T("RGB"));
	m_ctrlCombo.SetCurSel(0);

	m_pctlSelColor = new CColorStatic(m_hWnd, m_selColor);
	m_pctlSelColor->SubclassWindow(GetDlgItem(IDC_CURCOL_STATIC));	
	
	m_pctlColor = new CColorStatic(m_hWnd, m_crColor, m_bNullColor);	
	m_pctlColor->SubclassWindow(GetDlgItem(IDC_PREVCOL_STATIC));
	
	return 0;
}

int CColorSelctorDlg::SetFormInTab(int index)
{
	CString sTitle;
	COLORREF col = m_selColor;
	int* pValue;
	switch(index)
	{
	case 0:
		m_pColorTab->pszText = _T("CMYK");
		m_pColorTab->lParam = (LPARAM)m_pDlg1->m_hWnd;
		TabCtrl_SetItem(m_hTabHwnd, 0, m_pColorTab);

		TabCtrl_SetCurSel(m_hTabHwnd, 0);
		pValue = m_pDlg1->GetColorComponentsBuffer();
		SF_GetCMYKColComponent(col, pValue);

		m_pDlg1->ShowWindow(SW_SHOW);
		m_pDlg2->ShowWindow(SW_HIDE);
		m_pDlg3->ShowWindow(SW_HIDE);
		m_pDlg4->ShowWindow(SW_HIDE);		
		break;
	case 1:
		m_pColorTab->pszText = _T("HSV");
		m_pColorTab->lParam = (LPARAM)m_pDlg2->m_hWnd;
		TabCtrl_SetItem(m_hTabHwnd, 0, m_pColorTab);

		TabCtrl_SetCurSel(m_hTabHwnd, 0);
		pValue = m_pDlg2->GetColorComponentsBuffer();
		SF_GetHSVColComponent(col, pValue);

		m_pDlg1->ShowWindow(SW_HIDE);
		m_pDlg2->ShowWindow(SW_SHOW);
		m_pDlg3->ShowWindow(SW_HIDE);
		m_pDlg4->ShowWindow(SW_HIDE);
		
		break;
	case 2:
		m_pColorTab->pszText = _T("RGB");
		m_pColorTab->lParam = (LPARAM)m_pDlg3->m_hWnd;
		TabCtrl_SetItem(m_hTabHwnd, 0, m_pColorTab);

		TabCtrl_SetCurSel(m_hTabHwnd, 0);
		pValue = m_pDlg3->GetColorComponentsBuffer();
		SF_GetRGBColComponent(col, pValue);

		m_pDlg1->ShowWindow(SW_HIDE);
		m_pDlg2->ShowWindow(SW_HIDE);
		m_pDlg3->ShowWindow(SW_SHOW);
		m_pDlg4->ShowWindow(SW_HIDE);
		
		break;
	case 4:
		m_pColorTab->pszText = _T("Properties");
		m_pColorTab->lParam = (LPARAM)m_pDlg4->m_hWnd;
		TabCtrl_SetItem(m_hTabHwnd, 1, m_pPropertyTab);

		TabCtrl_SetCurSel(m_hTabHwnd, 1);
		m_pDlg1->ShowWindow(SW_HIDE);
		m_pDlg2->ShowWindow(SW_HIDE);
		m_pDlg3->ShowWindow(SW_HIDE);
		m_pDlg4->ShowWindow(SW_SHOW);
		break;
	}

	return 0;
}
// 
// LRESULT CColorSelctorDlg::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
// {
// 	DestroyAllWindow();
// 
// 	return 0;
// }

LRESULT CColorSelctorDlg::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	DestroyAllWindow();

	return 0;
}
