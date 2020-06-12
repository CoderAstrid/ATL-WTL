// CMYK_SEL_Form.cpp : Implementation of CCMYK_SEL_FORM

#include "stdafx.h"
#include "CMYK_SEL_Form.h"


// CCMYK_SEL_FORM

LRESULT CCmykSelForm::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	Destroy();

	return 0;
}

void CCmykSelForm::CreateSlider(void)
{
	RECT rc0;
	CWindow wnd;
	HWND pp;
	//.Calculate the position and size of the Tab Items

	int nID[4] = {4462, 4463, 4464, 4465};
	COLORREF cmyk = RgbToCmyk(*m_pSelColor);
	m_aValue[0] = GetCValue(cmyk);
	m_aValue[1] = GetMValue(cmyk);
	m_aValue[2] = GetYValue(cmyk);
	m_aValue[3] = GetKValue(cmyk);

	for(int i = 0; i < 4; i++){
		m_pSlider[i] = new CColPaletteSelWnd();
		m_pSlider[i]->m_pColor = m_pSelColor;
		m_pSlider[i]->Create(m_hWnd, i, efCMYK_Type, 100, 0);		
		m_pSlider[i]->ModifyStyle(WS_CAPTION , WS_CHILD);		

		wnd = GetDlgItem(nID[i]);
		wnd.GetWindowRect(&rc0);
		ScreenToClient(&rc0);
		m_pSlider[i]->MoveWindow(&rc0);
		m_pSlider[i]->ShowWindow(SW_SHOW);
		
		m_pSlider[i]->SetPos(m_aValue[i]);
	}
}

int* CCmykSelForm::GetColorComponentsBuffer(void)
{
	return m_aValue;
}

void CCmykSelForm::DrawAndSetting(BOOL bFirst /*= FALSE*/)
{
	COLORREF col = CMYK(m_aValue[0], m_aValue[1], m_aValue[2], m_aValue[3]);
	COLORREF rgb = CmykToRgb(col);
	if(rgb != *m_pSelColor){// || bFirst){
		m_pSlider[0]->SetPos(m_aValue[0]);
		SendMessage(m_pSlider[1]->m_hWnd, WM_NOTIFY, 0L, 0L);
		SendMessage(m_pSlider[2]->m_hWnd, WM_NOTIFY, 0L, 0L);
		SendMessage(m_pSlider[3]->m_hWnd, WM_NOTIFY, 0L, 0L);
		m_pSlider[1]->SetPos(m_aValue[1]);
		SendMessage(m_pSlider[2]->m_hWnd, WM_NOTIFY, 0L, 0L);
		SendMessage(m_pSlider[0]->m_hWnd, WM_NOTIFY, 0L, 0L);
		SendMessage(m_pSlider[3]->m_hWnd, WM_NOTIFY, 0L, 0L);
		m_pSlider[2]->SetPos(m_aValue[2]);
		SendMessage(m_pSlider[1]->m_hWnd, WM_NOTIFY, 0L, 0L);
		SendMessage(m_pSlider[0]->m_hWnd, WM_NOTIFY, 0L, 0L);
		SendMessage(m_pSlider[3]->m_hWnd, WM_NOTIFY, 0L, 0L);
		m_pSlider[3]->SetPos(m_aValue[3]);
		SendMessage(m_pSlider[1]->m_hWnd, WM_NOTIFY, 0L, 0L);
		SendMessage(m_pSlider[0]->m_hWnd, WM_NOTIFY, 0L, 0L);
		SendMessage(m_pSlider[2]->m_hWnd, WM_NOTIFY, 0L, 0L);

		SendMessage(GetParent().m_hWnd, CPN_SELCHANGE, 0L, 0L);
		*m_pSelColor = rgb;
	}
}

LRESULT CCmykSelForm::OnShowWindow(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	DrawAndSetting(TRUE);
	SetCMYKText();
	return 0;
}

void CCmykSelForm::SetCMYKText(void)
{
	CString str;
	str.Format(_T("%d"), m_aValue[0]);
	m_ctlEditC.SetWindowText(str);
	str.Format(_T("%d"), m_aValue[1]);
	m_ctlEditM.SetWindowText(str);
	str.Format(_T("%d"), m_aValue[2]);
	m_ctlEditY.SetWindowText(str);
	str.Format(_T("%d"), m_aValue[3]);
	m_ctlEditK.SetWindowText(str);
}
