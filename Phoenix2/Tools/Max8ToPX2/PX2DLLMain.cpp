/*
*
* �ļ�����	��	PX2DLLMain.cpp
*
*/

#include "PX2Max9ClassDesc.hpp"

static int sControlsInit = FALSE;
static PX2::GraphicsRoot *sRoot = 0;
static PX2::ResourceManager *sResMan = 0;
//----------------------------------------------------------------------------
BOOL WINAPI DllMain (HINSTANCE instance, ULONG dwReason, LPVOID)
{
	// �������������ʱ����Windows DLL������
	if (!sControlsInit) 
	{
		sControlsInit = true;

		// Max��ʼ��
		InitCustomControls(instance); // max ���ÿؼ�
		InitCommonControls(); // windows�ؼ�
	}

	switch (dwReason) 
	{
	case DLL_PROCESS_ATTACH:
		PX2Max8ClassDesc::msInstance = instance;

#ifdef PX2_USE_MEMORY
		PX2::Memory::Initialize();
#endif

		InitCustomControls(instance);
		InitCommonControls();

		sRoot = new0 PX2::GraphicsRoot();
		sRoot->Initlize();

		sResMan = new0 PX2::ResourceManager();
		break;
	case DLL_PROCESS_DETACH:
		sRoot->Terminate();
		delete0(sRoot);

		delete0(sResMan);
#ifdef PX2_USE_MEMORY
		PX2::Memory::Terminate("Max9ToTd_MemoryReport.txt");
#endif
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	}

	return TRUE;
}
//----------------------------------------------------------------------------
__declspec(dllexport) const TCHAR* LibDescription ()
{
	// �����������һ���ַ����������DLL���û����û�����DLL����ͨ���˻�á�
	return "Phoenix2 3DMax Plugin";
}
//----------------------------------------------------------------------------
__declspec(dllexport) int LibNumberClasses ()
{
	// �������������DLL������ĸ�����
	return 1;
}
//----------------------------------------------------------------------------
__declspec(dllexport) ClassDesc* LibClassDesc (int i)
{
	// �������������������������
	(void)i;
	return &PX2Max8ClassDesc::TheClassDesc;
}
//----------------------------------------------------------------------------
__declspec(dllexport) ULONG LibVersion ()
{
	// ��������һ��Ԥ����ĳ�����ʶMaxϵͳ����İ汾�š������ϵͳ����ʱ����
	// ��ȷ��DLL��
	return VERSION_3DSMAX;
}
//----------------------------------------------------------------------------