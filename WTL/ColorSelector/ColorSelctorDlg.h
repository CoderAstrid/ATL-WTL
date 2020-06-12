// ColorSelctorDlg.h : Declaration of the CColorSelctorDlg

#pragma once

#include "resource.h"       // main symbols

#include <atlhost.h>
#include "CMYK_SEL_Form.h"
#include "HSV_SEL_Form.h"
#include "RGB_SEL_Form.h"
#include "ColPropertySelForm.h"

#include "LIB/Cla_ColorMap.h"

class CColorSelctorDlg : 
	public CAxDialogImpl<CColorSelctorDlg>
{
public:
	CColorSelctorDlg()
	{
		IDD = IDD_COLORSELCTORDLG;
		m_pDlg1 = NULL;
		m_pDlg2 = NULL;
		m_pDlg3 = NULL;
		m_pDlg4 = NULL;
		m_pPropertyTab = NULL;
		m_pColorTab = NULL;
		m_hTabHwnd = NULL;
		m_nCurForm = 0;
		m_pctlSelColor = NULL;
		m_pctlColor = NULL;
	}

	CColorSelctorDlg(UINT nID)
	{
		IDD = nID;
		m_pDlg1 = NULL;
		m_pDlg2 = NULL;
		m_pDlg3 = NULL;
		m_pDlg4 = NULL;
		m_pPropertyTab = NULL;
		m_pColorTab = NULL;
		m_hTabHwnd = NULL;
		m_nCurForm = 0;
	}
	~CColorSelctorDlg()
	{
	}

	UINT IDD;
	COLORREF		m_crColor;	
	BOOL			m_bNullColor;
	BOOL			m_bUseWindowsDithering;
BEGIN_MSG_MAP(CColorSelctorDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_HANDLER(IDOK, BN_CLICKED, OnClickedOK)
	COMMAND_HANDLER(IDCANCEL, BN_CLICKED, OnClickedCancel)	
	COMMAND_HANDLER(IDC_ADVANCED_BTN, BN_CLICKED, OnBnClickedAdvancedBtn)
	NOTIFY_HANDLER(IDC_CLRSPACE_TAB, TCN_SELCHANGE, OnTcnSelchangeClrspaceTab)
	COMMAND_HANDLER(IDC_COLSPC_COMBO, CBN_SELCHANGE, OnCbnSelchangeColspcCombo)
	MESSAGE_HANDLER(CPN_SELCHANGE, OnSelColorChanged)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	CHAIN_MSG_MAP(CAxDialogImpl<CColorSelctorDlg>)
END_MSG_MAP()

 	LRESULT OnSelColorChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
 	{
		int msgId = (int)lParam;
		if(msgId == 1){
			m_bNullColor = m_pDlg4->m_bNullColor;
			m_bUseWindowsDithering = m_pDlg4->m_bUseWindowsDithering;
		}
		m_pctlSelColor->SetColor(m_selColor, m_bNullColor);
		
 		return 0;
 	}
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CAxDialogImpl<CColorSelctorDlg>::OnInitDialog(uMsg, wParam, lParam, bHandled);
		bHandled = TRUE;
		
		CreateControls();
		CreateTabCtrl();
		return 1;  // Let the system set the focus
	}

	LRESULT OnClickedOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		m_bUseWindowsDithering = m_pDlg4->m_bUseWindowsDithering;
		m_bNullColor = m_pDlg4->m_bNullColor;
		m_crColor = m_selColor;

		EndDialog(wID);
		return 0;
	}

	LRESULT OnClickedCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}	
	LRESULT OnBnClickedAdvancedBtn(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnTcnSelchangeClrspaceTab(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/);
	LRESULT OnCbnSelchangeColspcCombo(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
private:
	TCITEM*  m_pColorTab;
	TCITEM*  m_pPropertyTab;	

	CCmykSelForm* m_pDlg1;	
	CHsvSelForm* m_pDlg2;
	CRrgSelForm* m_pDlg3;
	CColPropertySelForm* m_pDlg4;

	HWND m_hTabHwnd;
	CComboBox  m_ctrlCombo;
	int		m_nCurForm;	
	COLORREF		m_selColor;
	CColorStatic*		m_pctlSelColor;
	CColorStatic*		m_pctlColor;
public:
	void CreateTabCtrl(void);	
	int CreateControls(void);
	int SetFormInTab(int index);
private:
	int DestroyAllWindow(void);
public:
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
};


