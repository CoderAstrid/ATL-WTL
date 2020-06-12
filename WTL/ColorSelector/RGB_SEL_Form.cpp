// RGB_SEL_Form.cpp : Implementation of CRrgSelForm

#include "stdafx.h"
#include "RGB_SEL_Form.h"


// CRrgSelForm

LRESULT CRrgSelForm::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	Destroy();

	return 0;
}

void CRrgSelForm::CreateSlider(void)
{
	RECT rc0;
	CWindow wnd;
	HWND pp;
	//.Calculate the position and size of the Tab Items
	
	int nID[3] = {4462, 4463, 4464};
	m_aValue[0] = GetRValue(*m_pSelColor);
	m_aValue[1] = GetGValue(*m_pSelColor);
	m_aValue[2] = GetBValue(*m_pSelColor);

	for(int i = 0; i < 3; i++){
		m_pSlider[i] = new CColPaletteSelWnd();
		m_pSlider[i]->m_pColor = m_pSelColor;
		m_pSlider[i]->Create(m_hWnd, i, efRGB_Type, 255, 0);		
		m_pSlider[i]->ModifyStyle(WS_CAPTION , WS_CHILD);		

		wnd = GetDlgItem(nID[i]);
		wnd.GetWindowRect(&rc0);
		ScreenToClient(&rc0);
		m_pSlider[i]->MoveWindow(&rc0);
		m_pSlider[i]->ShowWindow(SW_SHOW);
		
		m_pSlider[i]->SetPos(m_aValue[i]);
	}
}

int* CRrgSelForm::GetColorComponentsBuffer(void)
{
	return m_aValue;
}

void CRrgSelForm::DrawAndSetting(BOOL bFirst /*= FALSE*/)
{
	COLORREF col = RGB(m_aValue[0], m_aValue[1], m_aValue[2]);
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

LRESULT CRrgSelForm::OnShowWindow(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	DrawAndSetting(TRUE);
	SetRGBText();
	return 0;
}

void CRrgSelForm::SetRGBText(void)
{
	CString str;
	str.Format(_T("%d"), m_aValue[0]);
	m_ctlEditR.SetWindowText(str);
	str.Format(_T("%d"), m_aValue[1]);
	m_ctlEditG.SetWindowText(str);
	str.Format(_T("%d"), m_aValue[2]);
	m_ctlEditB.SetWindowText(str);
}


LRESULT CRrgSelForm::OnKeyDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// TODO: Add your message handler code here and/or call default

	return 0;
}
