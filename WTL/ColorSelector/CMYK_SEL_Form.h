// CMYK_SEL_Form.h : Declaration of the CCmykSelForm

#pragma once

#include "resource.h"       // main symbols

#include <atlhost.h>
#include "LIB/Cla_ColorMap.h"
#include "ColPaletteSelWnd.h"
// CRrgSelForm

class CCmykSelForm : 
	public CAxDialogImpl<CCmykSelForm>
{
public:
	CCmykSelForm()
	{
		IDD = IDD_CMYK_SEL_Form;		
		Initialize();
	}

	CCmykSelForm(UINT nID)
	{
		IDD = nID;
		Initialize();
	}
	~CCmykSelForm()
	{
		
	}

	void Initialize()
	{
		for(int i = 0; i < 4; i++)
			m_pSlider[i] = NULL;
		m_pctlColorMap = NULL;
	}

	void Destroy()
	{
		for(int i = 0; i < 4; i++)
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

BEGIN_MSG_MAP(CCmykSelForm)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_HANDLER(IDOK, BN_CLICKED, OnClickedOK)
	COMMAND_HANDLER(IDCANCEL, BN_CLICKED, OnClickedCancel)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
//	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_SHOWWINDOW, OnShowWindow)
	COMMAND_HANDLER(4470, EN_CHANGE, OnCEditChanged)
	COMMAND_HANDLER(4471, EN_CHANGE, OnMEditChanged)
	COMMAND_HANDLER(4472, EN_CHANGE, OnYEditChanged)
	COMMAND_HANDLER(4473, EN_CHANGE, OnKEditChanged)
	MESSAGE_HANDLER(WM_NOTIFY, OnColorChanged)
	CHAIN_MSG_MAP(CAxDialogImpl<CCmykSelForm>)
END_MSG_MAP()

// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnCEditChanged(WORD, WORD, HWND, BOOL)
	{
		int nValue = 0;		
		
		BSTR bstr = NULL;
		m_ctlEditC.GetWindowText(&bstr);
		CString str = bstr;
		
		nValue = _wtoi(str);
		if(nValue < 0) nValue = 0;
		if(nValue >100) nValue = 100;
		if(nValue != m_aValue[0]){
			m_aValue[0] = nValue;
			
		}
		SysFreeString(bstr);
		DrawAndSetting();
		return 0;
	}
	LRESULT OnMEditChanged(WORD, WORD, HWND, BOOL)
	{
 		int nValue = 0;				
 		BSTR pstr = NULL;
 		m_ctlEditM.GetWindowText(&pstr);
 		CString str = pstr;
 
 		nValue = _wtoi(str);		
 		if(nValue < 0) nValue = 0;
 		if(nValue >100) nValue = 100;
 		if(nValue != m_aValue[1]){
 			m_aValue[1] = nValue; 			
 		}	

		SysFreeString(pstr);
		DrawAndSetting();
		return 0;
	}
	LRESULT OnYEditChanged(WORD, WORD, HWND, BOOL)
	{
		int nValue = 0;				
 		BSTR bstr = NULL;
 		m_ctlEditY.GetWindowText(&bstr);
 
 		CString str = bstr;
 
 		nValue = _wtoi(str);
		if(nValue < 0) nValue = 0;
		if(nValue >100) nValue = 100;
		if(nValue != m_aValue[2]){
			m_aValue[2] = nValue;			
		}
		SysFreeString(bstr);
		DrawAndSetting();
		return 0;
	}
	LRESULT OnKEditChanged(WORD, WORD, HWND, BOOL)
	{
		int nValue = 0;				
		BSTR bstr = NULL;
		m_ctlEditK.GetWindowText(&bstr);

		CString str = bstr;

		nValue = _wtoi(str);
		if(nValue < 0) nValue = 0;
		if(nValue >100) nValue = 100;
		if(nValue != m_aValue[3]){
			m_aValue[3] = nValue;			
		}
		SysFreeString(bstr);
		DrawAndSetting();
		return 0;
	}
	LRESULT OnColorChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LONG nSlide = HIWORD(wParam);
		int nID = LOWORD(wParam);

		if(nSlide == 0xFF){//. Message from ColorMap
			COLORREF col = (COLORREF)lParam;
			EF_COLORMAP_TYPE colMapType = (EF_COLORMAP_TYPE)nID;
			if(col != CLR_INVALID){
				COLORREF cmyk = RgbToCmyk(col);
				m_aValue[0] = GetCValue(cmyk);
				m_aValue[1] = GetMValue(cmyk);
				m_aValue[2] = GetYValue(cmyk);
				m_aValue[3] = GetKValue(cmyk);
			}
		}else{//. Message form 4 slides
			m_aValue[nID] = (LONG)lParam;
			if(m_aValue[nID] < 0) m_aValue[nID] = 0;
			if(m_aValue[nID] > 100) m_aValue[nID] = 100;
		}
		SetCMYKText();
		DrawAndSetting();
		return 0;
	}
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CAxDialogImpl<CCmykSelForm>::OnInitDialog(uMsg, wParam, lParam, bHandled);
		bHandled = TRUE;
		
		m_pctlColorMap = new CColorMap(m_hWnd, efCMYK_Type);
		m_pctlColorMap->SubclassWindow(GetDlgItem(IDC_MAP));
		m_ctlEditC = GetDlgItem(4470);
		m_ctlEditM = GetDlgItem(4471);
		m_ctlEditY = GetDlgItem(4472);
		m_ctlEditK = GetDlgItem(4473);
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
	
	CColPaletteSelWnd* m_pSlider[4];
	int m_aValue[4];
	CEdit		m_ctlEditC;
	CEdit		m_ctlEditM;
	CEdit		m_ctlEditY;
	CEdit		m_ctlEditK;
	
	void CreateSlider(void);
public:
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	
	int* GetColorComponentsBuffer(void);
private:
	void DrawAndSetting(BOOL bFirst = FALSE);
public:
	CColorMap*   m_pctlColorMap;
	LRESULT OnShowWindow(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	COLORREF *m_pSelColor;
	void SetCMYKText(void);
};


