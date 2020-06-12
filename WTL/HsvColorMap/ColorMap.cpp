// ColorMap.cpp : Implementation of WinMain


#include "stdafx.h"
#include "resource.h"
#include "ColorMap_i.h"
#include "Cla_TestDlg.h"

class CColorMapModule : public CAtlExeModuleT< CColorMapModule >
{
public :
	DECLARE_LIBID(LIBID_ColorMapLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_COLORMAP, "{AE255880-5774-4160-B7DA-4B2382161A6A}")
};

CColorMapModule _AtlModule;



//
extern "C" int WINAPI _tWinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, 
                                LPTSTR /*lpCmdLine*/, int nShowCmd)
{
	CTestDlg dlg;
	dlg.DoModal();
    return _AtlModule.WinMain(nShowCmd);
}

