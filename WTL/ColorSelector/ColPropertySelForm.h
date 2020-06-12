// ColPropertySelForm.h : Declaration of the CColPropertySelForm

#pragma once

#include "resource.h"       // main symbols

#include <atlhost.h>


// CColPropertySelForm

class CColPropertySelForm : 
	public CAxDialogImpl<CColPropertySelForm>
{
public:
	CColPropertySelForm()
	{
		IDD = IDD_COLPROPERTYSELFORM;
		m_bUseWindowsDithering = FALSE;
		m_bNullColor = FALSE;
	}
	CColPropertySelForm(UINT nID)
	{
		IDD = nID;
		m_bUseWindowsDithering = FALSE;
		m_bNullColor = FALSE;
	}

	~CColPropertySelForm()
	{
	}

	UINT IDD;
	BOOL m_bUseWindowsDithering;
	BOOL m_bNullColor;
	CButton m_chkUseWinDit;
	CButton m_chkNullCol;
BEGIN_MSG_MAP(CColPropertySelForm)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_HANDLER(IDOK, BN_CLICKED, OnClickedOK)
	COMMAND_HANDLER(IDCANCEL, BN_CLICKED, OnClickedCancel)
	COMMAND_HANDLER(IDC_CHK_DITHER, BN_CLICKED, OnBnClickedChkDithering)
	COMMAND_HANDLER(IDC_CHK_NULL, BN_CLICKED, OnBnClickedChkNull)
	CHAIN_MSG_MAP(CAxDialogImpl<CColPropertySelForm>)
END_MSG_MAP()

// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CAxDialogImpl<CColPropertySelForm>::OnInitDialog(uMsg, wParam, lParam, bHandled);
		bHandled = TRUE;
		m_chkUseWinDit= GetDlgItem(IDC_CHK_DITHER);
		m_chkNullCol = GetDlgItem(IDC_CHK_NULL);

		m_chkUseWinDit.SetCheck(m_bUseWindowsDithering);
		m_chkNullCol.SetCheck(m_bNullColor);
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
	LRESULT OnBnClickedChkDithering(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedChkNull(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};


