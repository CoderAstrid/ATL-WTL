// RGB_SEL_Form.h : Declaration of the CRrgSelForm

#pragma once

#include "resource.h"       // main symbols

#include <atlhost.h>
#include "LIB/Cla_ColorMap.h"
#include "ColPaletteSelWnd.h"
// CRrgSelForm

class CRrgSelForm : 
	public CAxDialogImpl<CRrgSelForm>
{
public:
	CRrgSelForm()
	{
		IDD = IDD_RGB_SEL_Form;		
		Initialize();
	}

	CRrgSelForm(UINT nID)
	{
		IDD = nID;
		
		Initialize();
	}
	~CRrgSelForm()
	{
		
	}

	void Initialize()
	{
		for(int i = 0; i < 3; i++)
			m_pSlider[i] = NULL;
		m_pctlColorMap = NULL;
	}

	void Destroy()
	{
		for(int i = 0; i < 3; i++)
		{
			if(m_pSlider[i] != NULL){
				m_pSlider[i]->DestroyWindow();
				delete m_pSlider[i];
				m_pSlider[i] = NULL;
			}
		}

		if(m_pctlColorMap != NULL)
		{
			m_pctlColorMap->DestroyWindow();
			delete m_pctlColorMap;
			m_pctlColorMap = NULL;
		}
	}
	UINT IDD;

BEGIN_MSG_MAP(CRrgSelForm)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_HANDLER(IDOK, BN_CLICKED, OnClickedOK)
	COMMAND_HANDLER(IDCANCEL, BN_CLICKED, OnClickedCancel)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
//	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_SHOWWINDOW, OnShowWindow)
	COMMAND_HANDLER(4470, EN_CHANGE, OnREditChanged)
	COMMAND_HANDLER(4471, EN_CHANGE, OnGEditChanged)
	COMMAND_HANDLER(4472, EN_CHANGE, OnBEditChanged)	
	MESSAGE_HANDLER(WM_NOTIFY, OnColorChanged)
	MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
	CHAIN_MSG_MAP(CAxDialogImpl<CRrgSelForm>)
	//MESSAGE_HANDLER(WM_CTLCOLOREDIT, OnColorScrolled)		
END_MSG_MAP()

// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnREditChanged(WORD, WORD, HWND, BOOL)
	{
		int nValue = 0;		
		
		BSTR bstr = NULL;
		m_ctlEditR.GetWindowText(&bstr);
		CString str = bstr;
		
		nValue = _wtoi(str);
		if(nValue < 0) nValue = 0;
		if(nValue >255) nValue = 255;
		if(nValue != m_aValue[0]){
			m_aValue[0] = nValue;
			
		}
		SysFreeString(bstr);
		DrawAndSetting();
		return 0;
	}
	LRESULT OnGEditChanged(WORD, WORD, HWND, BOOL)
	{
 		int nValue = 0;				
 		BSTR pstr = NULL;
 		m_ctlEditG.GetWindowText(&pstr);
 		CString str = pstr;
 
 		nValue = _wtoi(str);		
 		if(nValue < 0) nValue = 0;
 		if(nValue >255) nValue = 255;
 		if(nValue != m_aValue[1]){
 			m_aValue[1] = nValue; 			
 		}	

		SysFreeString(pstr);
		DrawAndSetting();
		return 0;
	}
	LRESULT OnBEditChanged(WORD, WORD, HWND, BOOL)
	{
		int nValue = 0;				
 		BSTR bstr = NULL;
 		m_ctlEditB.GetWindowText(&bstr);
 
 		CString str = bstr;
 
 		nValue = _wtoi(str);
		if(nValue < 0) nValue = 0;
		if(nValue >255) nValue = 255;
		if(nValue != m_aValue[2]){
			m_aValue[2] = nValue;			
		}
		SysFreeString(bstr);
		DrawAndSetting();
		return 0;
	}
	LRESULT OnColorChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LONG nSlide = HIWORD(wParam);
		int nID = LOWORD(wParam);

		if(nSlide == 0xFF){
			COLORREF col = (COLORREF)lParam;
			EF_COLORMAP_TYPE colMapType = (EF_COLORMAP_TYPE)nID;
			if(col != CLR_INVALID){
				m_aValue[0] = GetRValue(col);
				m_aValue[1] = GetGValue(col);
				m_aValue[2] = GetBValue(col);
			}
		}else{
			m_aValue[nID] = (LONG)lParam;
			if(m_aValue[nID] < 0) m_aValue[nID] = 0;
			if(m_aValue[nID] > 0xff) m_aValue[nID] = 0xff;
		}
		SetRGBText();
		DrawAndSetting();
		return 0;
	}
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CAxDialogImpl<CRrgSelForm>::OnInitDialog(uMsg, wParam, lParam, bHandled);
		bHandled = TRUE;
		m_pctlColorMap = new CColorMap(m_hWnd, efRGB_Type);
		m_pctlColorMap->SubclassWindow(GetDlgItem(4478));
		m_ctlEditR = GetDlgItem(4470);
		m_ctlEditG = GetDlgItem(4471);
		m_ctlEditB = GetDlgItem(4472);
		CreateSlider();
//		m_ctlColorMap.m_hParentWnd = m_hWnd;
// 		RECT rc;
// 		SF_GetScreenWorkRect(&rc);
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
private:
	
	CColPaletteSelWnd* m_pSlider[3];
	int m_aValue[4];
	CEdit		m_ctlEditR;
	CEdit		m_ctlEditG;
	CEdit		m_ctlEditB;
	void CreateSlider(void);
public:
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	
	int* GetColorComponentsBuffer(void);
private:
	void DrawAndSetting(BOOL bFirst = FALSE);
public:
	CColorMap*   m_pctlColorMap;
//	LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnShowWindow(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	COLORREF *m_pSelColor;
	void SetRGBText(void);	
	LRESULT OnKeyDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
};


