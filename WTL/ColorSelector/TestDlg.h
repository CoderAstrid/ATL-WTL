// TestDlg.h : Declaration of the CTestDlg

#pragma once

#include "resource.h"       // main symbols

#include <atlhost.h>
#include "ColorSelctorDlg.h"

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
		RECT rc;
		GetWindowRect(&rc);
		rc.left += 200;
		rc.top += 200;
		rc.bottom += 200;
		rc.right += 200;
		MoveWindow(&rc);

		return 1;  // Let the system set the focus
	}

	LRESULT OnClickedOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		ShowColorSelectDlg();
		return 0;
	}

	LRESULT OnClickedCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}

	void ShowColorSelectDlg(void)
	{
		CColorSelctorDlg dlg;
		COLORREF col = RGB(255, 0, 0);
		BOOL bUseWin = FALSE, bNullColor = FALSE;
		dlg.m_bUseWindowsDithering = bUseWin;
		dlg.m_bNullColor = bNullColor;
		dlg.m_crColor = col;
		if(dlg.DoModal() == IDOK)
		{
			bUseWin = dlg.m_bUseWindowsDithering;
			bNullColor = dlg.m_bNullColor;
			col = dlg.m_crColor;
		}
	}
};


