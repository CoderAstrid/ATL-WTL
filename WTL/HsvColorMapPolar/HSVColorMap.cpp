// HSVColorMap.cpp : Implementation of WinMain


#include "stdafx.h"
#include "resource.h"
#include "HSVColorMap_i.h"
#include "TestDlg.h"

class CHSVColorMapModule : public CAtlExeModuleT< CHSVColorMapModule >
{
public :
	DECLARE_LIBID(LIBID_HSVColorMapLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_HSVCOLORMAP, "{2B1857AB-2A9D-473E-8B72-C8AFDEF5931D}")
	HRESULT PreMessageLoop(int nShowCmd)
	{
		CTestDlg dlg;
		dlg.DoModal();
		return S_FALSE;
	}
};

CHSVColorMapModule _AtlModule;



//
extern "C" int WINAPI _tWinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, 
                                LPTSTR /*lpCmdLine*/, int nShowCmd)
{
    return _AtlModule.WinMain(nShowCmd);
}

