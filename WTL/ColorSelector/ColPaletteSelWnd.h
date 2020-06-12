// ColPaletteSelWnd.h : Declaration of the CColPaletteSelWnd

#pragma once

#include "resource.h"       // main symbols

#include <atlhost.h>
#include "atlcontrols.h"
using namespace ATLControls;
#include "LIB/CommonColorLib.h"
// CColPaletteSelWnd

// class CColPaletteSelWnd : 
// 	public CAxDialogImpl<CColPaletteSelWnd>
class CColPaletteSelWnd : 
	public CAxDialogImpl<CColPaletteSelWnd>
{
public:
	CColPaletteSelWnd()
	{
		IDD = IDD = IDD_COLPALETTESELWND;
		m_nID = 0;
		m_nMin = 0;
		m_nMax = 100;
		m_nStep = 1;
		m_nPos = 0;
		m_hParent = NULL;
	}

	CColPaletteSelWnd(UINT ID)
	{
		IDD = ID;
		m_nID = 0;
		m_nMin = 0;
		m_nMax = 100;
		m_nStep = 1;
		m_nPos = 0;
		m_hParent = NULL;
		m_pColor = NULL;
	}

	UINT IDD;
	COLORREF* m_pColor;
	HWND Create(HWND hWndParent, int nID, EF_COLORMAP_TYPE efColorType,
				int nMax = 100,  int nMin = 0, 
				int nPos = 0, int nStep = 1, LPARAM dwInitParam = NULL)
	{
		m_nID = nID;
		m_eColorMapType = efColorType;
		m_nMin = nMin;
		m_nMax = nMax;
		m_nStep = nStep;
		m_nPos = nPos;
		m_hParent = hWndParent;
		m_bDrawing = FALSE;
		return CAxDialogImpl<CColPaletteSelWnd>::Create(hWndParent, dwInitParam);
	}
BEGIN_MSG_MAP(CColPaletteSelWnd)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_HANDLER(IDOK, BN_CLICKED, OnClickedOK)
	COMMAND_HANDLER(IDCANCEL, BN_CLICKED, OnClickedCancel)	
	MESSAGE_HANDLER(WM_HSCROLL, OnHScroll)
	MESSAGE_HANDLER(WM_NOTIFY, OnChangedPalette)
	MESSAGE_HANDLER(WM_SHOWWINDOW, OnShowWindow)
	CHAIN_MSG_MAP(CAxDialogImpl<CColPaletteSelWnd>)
END_MSG_MAP()

// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnChangedPalette(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		DrawStatic();
		return 0;
	}
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CAxDialogImpl<CColPaletteSelWnd>::OnInitDialog(uMsg, wParam, lParam, bHandled);
		bHandled = TRUE;
		m_Slider = GetDlgItem(4459);
		m_Slider.SetRangeMin(m_nMin);
		m_Slider.SetRangeMax(m_nMax);
		m_Slider.SetTicFreq(1);
		m_Slider.SetPageSize(10);
		m_Slider.SetPos(m_nPos);
		m_ctlStatic = GetDlgItem(4458);
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
	LRESULT OnHScroll(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
private:
	CTrackBarCtrl m_Slider;
	int m_nPos;
	int m_nMin;
	int m_nMax;
	int m_nStep;
	int m_nID;
	HWND m_hParent;
	CStatic m_ctlStatic;
	EF_COLORMAP_TYPE m_eColorMapType;
	BOOL m_bDrawing;
	void DrawStatic();
public:
	void SetPos(int nPos);
	LRESULT OnShowWindow(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
};


