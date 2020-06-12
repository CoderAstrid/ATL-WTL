// ColorSelector.cpp : Implementation of WinMain


#include "stdafx.h"
#include "resource.h"
#include "ColorSelector_i.h"
#include "TestDlg.h"
#define _CRTDBG_MAP_ALLOC
#include "crtdbg.h"

class CColorSelectorModule : public CAtlExeModuleT< CColorSelectorModule >
{
public :
	DECLARE_LIBID(LIBID_ColorSelectorLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_COLORSELECTOR, "{35C98A63-420E-4786-9360-B1E27DD44055}")
	HRESULT PreMessageLoop(int nShowCmd)
	{
		CTestDlg dlg;
		dlg.DoModal();
		return S_FALSE;
	}
};

CColorSelectorModule _AtlModule;



//
extern "C" int WINAPI _tWinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, 
                                LPTSTR /*lpCmdLine*/, int nShowCmd)
{
	int DbgFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	DbgFlag |= _CRTDBG_LEAK_CHECK_DF;
	DbgFlag |= _CRTDBG_ALLOC_MEM_DF;
	_CrtSetDbgFlag(DbgFlag);

    return _AtlModule.WinMain(nShowCmd);
}

