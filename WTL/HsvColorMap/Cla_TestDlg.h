// Cla_TestDlg.h : Declaration of the CTestDlg

#pragma once

#include "resource.h"       // main symbols

#include <atlhost.h>
#include "Cla_ColorMap.h"

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

	enum { IDD = IDD_CTESTDLG };

BEGIN_MSG_MAP(CTestDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_HANDLER(IDOK, BN_CLICKED, OnClickedOK)
	COMMAND_HANDLER(IDCANCEL, BN_CLICKED, OnClickedCancel)
	MESSAGE_HANDLER(WM_CTLCOLOREDIT, OnCtlColorEdit)
	CHAIN_MSG_MAP(CAxDialogImpl<CTestDlg>)
	REFLECT_NOTIFICATIONS()
END_MSG_MAP()

// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CAxDialogImpl<CTestDlg>::OnInitDialog(uMsg, wParam, lParam, bHandled);
		bHandled = TRUE;
		m_ctrlColorMap.SubclassWindow(GetDlgItem(IDC_COLOR_MAP));
		
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
	CColorMap m_ctrlColorMap;	//. My Custom Color Map Control
	LRESULT OnCtlColorEdit(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
};


