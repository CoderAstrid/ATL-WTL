// TestDlg.cpp : Implementation of CTestDlg

#include "stdafx.h"
#include "TestDlg.h"


// CTestDlg

LRESULT CTestDlg::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	if(m_pctlColorMap != NULL){
		m_pctlColorMap->Destroy();		
	}

	return 0;
}
