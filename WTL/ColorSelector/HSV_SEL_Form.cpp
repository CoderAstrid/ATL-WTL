// HSV_Sel_Form.cpp : Implementation of CHsvSelForm

#include "stdafx.h"
#include "HSV_SEL_Form.h"


// CHsvSelForm

LRESULT CHsvSelForm::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	Destroy();

	return 0;
}


void CHsvSelForm::CreateSlider(void)
{
	RECT rc0;
	CWindow wnd;
	HWND pp;
	//.Calculate the position and size of the Tab Items

	int nID[3] = {4462, 4463, 4464};
	int nMv[3] = {360, 100, 100};
	long h, s, v;
	RgbToHsv(*m_pSelColor, h, s, v);
	m_aValue[0] = h;
	m_aValue[1] = s;
	m_aValue[2] = v;
	for(int i = 0; i < 3; i++){
		m_pSlider[i] = new CColPaletteSelWnd();
		m_pSlider[i]->m_pColor = m_pSelColor;
		m_pSlider[i]->Create(m_hWnd, i, efHSV_Type, nMv[i], 0);		
		m_pSlider[i]->ModifyStyle(WS_CAPTION , WS_CHILD);		

		wnd = GetDlgItem(nID[i]);
		wnd.GetWindowRect(&rc0);
		ScreenToClient(&rc0);
		m_pSlider[i]->MoveWindow(&rc0);
		m_pSlider[i]->ShowWindow(SW_SHOW);
		
		m_pSlider[i]->SetPos(m_aValue[i]);
	}
}

int* CHsvSelForm::GetColorComponentsBuffer(void)
{
	return m_aValue;
}

void CHsvSelForm::DrawAndSetting(BOOL bFirst /*= FALSE*/)
{
	COLORREF col;
	col = HsvToRgb(m_aValue[0], m_aValue[1], m_aValue[2]);
	if(col != *m_pSelColor || bFirst){
		m_pSlider[0]->SetPos(m_aValue[0]);
		SendMessage(m_pSlider[1]->m_hWnd, WM_NOTIFY, 0L, 0L);
		SendMessage(m_pSlider[2]->m_hWnd, WM_NOTIFY, 0L, 0L);
		m_pSlider[1]->SetPos(m_aValue[1]);
		SendMessage(m_pSlider[2]->m_hWnd, WM_NOTIFY, 0L, 0L);
		SendMessage(m_pSlider[0]->m_hWnd, WM_NOTIFY, 0L, 0L);
		m_pSlider[2]->SetPos(m_aValue[2]);
		SendMessage(m_pSlider[1]->m_hWnd, WM_NOTIFY, 0L, 0L);
		SendMessage(m_pSlider[0]->m_hWnd, WM_NOTIFY, 0L, 0L);

		SendMessage(GetParent().m_hWnd, CPN_SELCHANGE, 0L, 0L);
		*m_pSelColor = col;
	}
}

LRESULT CHsvSelForm::OnShowWindow(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	DrawAndSetting(TRUE);
	SetHSVText();
	return 0;
}

void CHsvSelForm::SetHSVText(void)
{
	CString str;
	str.Format(_T("%d"), m_aValue[0]);
	m_ctlEditH.SetWindowText(str);
	str.Format(_T("%d"), m_aValue[1]);
	m_ctlEditS.SetWindowText(str);
	str.Format(_T("%d"), m_aValue[2]);
	m_ctlEditV.SetWindowText(str);
}
