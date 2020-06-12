// HSV_Sel_Form.h : Declaration of the CHsvSelForm

#pragma once

#include "resource.h"       // main symbols

#include <atlhost.h>
#include "LIB/Cla_ColorMap.h"
#include "ColPaletteSelWnd.h"
// CRrgSelForm

class CHsvSelForm : 
	public CAxDialogImpl<CHsvSelForm>
{
public:
	CHsvSelForm()
	{
		IDD = IDD_HSV_Sel_Form;
		Initialize();
	}
	CHsvSelForm(UINT nID)
	{
		IDD = nID;
		
		Initialize();
	}
	~CHsvSelForm()
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

BEGIN_MSG_MAP(CHsvSelForm)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_HANDLER(IDOK, BN_CLICKED, OnClickedOK)
	COMMAND_HANDLER(IDCANCEL, BN_CLICKED, OnClickedCancel)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
//	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_SHOWWINDOW, OnShowWindow)
	COMMAND_HANDLER(4470, EN_CHANGE, OnHEditChanged)
	COMMAND_HANDLER(4471, EN_CHANGE, OnSEditChanged)
	COMMAND_HANDLER(4472, EN_CHANGE, OnVEditChanged)
	
	MESSAGE_HANDLER(WM_NOTIFY, OnColorChanged)
	CHAIN_MSG_MAP(CAxDialogImpl<CHsvSelForm>)
END_MSG_MAP()

// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnHEditChanged(WORD, WORD, HWND, BOOL)
	{
		int nValue = 0;		
		
		BSTR bstr = NULL;
		m_ctlEditH.GetWindowText(&bstr);
		CString str = bstr;
		
		nValue = _wtoi(str);
		if(nValue < 0) nValue = 0;
		if(nValue >360) nValue = 360;
		if(nValue != m_aValue[0]){
			m_aValue[0] = nValue;
			
		}
		SysFreeString(bstr);
		DrawAndSetting();
		return 0;
	}
	LRESULT OnSEditChanged(WORD, WORD, HWND, BOOL)
	{
 		int nValue = 0;				
 		BSTR pstr = NULL;
 		m_ctlEditS.GetWindowText(&pstr);
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
	LRESULT OnVEditChanged(WORD, WORD, HWND, BOOL)
	{
		int nValue = 0;				
 		BSTR bstr = NULL;
 		m_ctlEditV.GetWindowText(&bstr);
 
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
	LRESULT OnColorChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LONG nSlide = HIWORD(wParam);
		int nID = LOWORD(wParam);
		long nMaxV[3] = {360, 100, 100};
		if(nSlide == 0xFF){
			COLORREF col = (COLORREF)lParam;
			
			EF_COLORMAP_TYPE colMapType = (EF_COLORMAP_TYPE)nID;
			if(col != CLR_INVALID){
				long h, s, v;				
				RgbToHsv(col, h, s, v);
				m_aValue[0] = h;
				m_aValue[1] = s;
				m_aValue[2] = v;
			}
		}else{
			m_aValue[nID] = (LONG)lParam;
			if(m_aValue[nID] < 0) m_aValue[nID] = 0;
			if(m_aValue[nID] > nMaxV[nID]) m_aValue[nID] = nMaxV[nID];
		}
		SetHSVText();
		DrawAndSetting();
		return 0;
	}

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CAxDialogImpl<CHsvSelForm>::OnInitDialog(uMsg, wParam, lParam, bHandled);
		bHandled = TRUE;
		m_pctlColorMap = new CColorMap(m_hWnd, efHSV_Type);
		m_pctlColorMap->SubclassWindow(GetDlgItem(4478));
		m_ctlEditH = GetDlgItem(4470);
		m_ctlEditS = GetDlgItem(4471);
		m_ctlEditV = GetDlgItem(4472);
		CreateSlider();
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
	CEdit		m_ctlEditH;
	CEdit		m_ctlEditS;
	CEdit		m_ctlEditV;
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
	void SetHSVText(void);
};


