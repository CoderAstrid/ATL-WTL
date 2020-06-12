// TestDlg.h : Declaration of the CTestDlg

#pragma once

#include "resource.h"       // main symbols

#include <atlhost.h>
#include "HSVColorMapCtrl.h"

// CTestDlg

class CTestDlg : 
	public CAxDialogImpl<CTestDlg>
{
public:
	CTestDlg()
	{
	}

	~CTestDlg()
	{
		
	}

	enum { IDD = IDD_TESTDLG };

BEGIN_MSG_MAP(CTestDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_HANDLER(IDOK, BN_CLICKED, OnClickedOK)
	COMMAND_HANDLER(IDCANCEL, BN_CLICKED, OnClickedCancel)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	CHAIN_MSG_MAP(CAxDialogImpl<CTestDlg>)
END_MSG_MAP()

// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CAxDialogImpl<CTestDlg>::OnInitDialog(uMsg, wParam, lParam, bHandled);
		bHandled = TRUE;
		m_pctlColorMap = new CHSVColorMapCtrl(m_hWnd, 0);
		m_pctlColorMap->SubclassWindow(GetDlgItem(IDC_HSV_MAP));
		return 1;  // Let the system set the focus
	}

	LRESULT OnClickedOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}

	LRESULT OnClickedCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
protected: 
	CHSVColorMapCtrl* m_pctlColorMap;
public:
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
};


