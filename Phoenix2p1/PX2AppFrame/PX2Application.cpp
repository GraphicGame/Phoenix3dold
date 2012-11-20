/*
*
* �ļ�����	��	PX2Win32Application.cpp
*
*/

#include "PX2Application.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
#if defined(_WIN32) || defined(WIN32)
LRESULT CALLBACK MsWindowEventHandler (HWND handle, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	switch (message) 
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		break;
	}

	return DefWindowProc(handle, message, wParam, lParam);
}
#endif
//----------------------------------------------------------------------------
Application::Application ()
	:
mWindowTitle("Application"),
	mXPosition(0),
	mYPosition(0),
	mWidth(800),
	mHeight(600),
	mAllowResize(true)
{
}
//----------------------------------------------------------------------------
Application::~Application ()
{
}
//----------------------------------------------------------------------------
int Application::Entry (int numArguments, char** arguments)
{
	Application* theApp = (Application*)msApplication;
	return theApp->Main(numArguments, arguments);
}
//----------------------------------------------------------------------------
#if defined(_WIN32) || defined(WIN32)
int Application::Main (int numArguments, char** arguments)
{
	PX2_UNUSED(numArguments);
	PX2_UNUSED(arguments);

	Initlize ();

	// Ԥ�������ɫ
	mRenderer->ClearBuffers();

	// ��ʾ����
	ShowWindow(mhWnd, SW_SHOWNORMAL);
	UpdateWindow(mhWnd);

	// ��Ϣѭ��
	bool applicationRunning = true;
	while (applicationRunning)
	{
		MSG msg;
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				applicationRunning = false;
				continue;
			}

			HACCEL accel = 0;
			if (!TranslateAccelerator(mhWnd, accel, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

		}
		else
		{
			OnIdle();
		}
	}

	Ternamate ();

	return 0;
}
#endif
//----------------------------------------------------------------------------
#if defined __ANDROID__
int Application::Main (int numArguments, char** arguments)
{
	return 0;
}
#endif
//----------------------------------------------------------------------------
#if defined(_WIN32) || defined(WIN32)
bool Application::OnInitlize ()
{
	ApplicationBase::OnInitlize();

	// === ������Ⱦ���� ===

	// ע�ᴰ����
	static char sWindowClass[] = "Phoenix2 ApplicationBase";
	WNDCLASS wc;
	wc.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc   = MsWindowEventHandler;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = 0;
	wc.hIcon         = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor       = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszClassName = sWindowClass;
	wc.lpszMenuName  = 0;
	RegisterClass(&wc);

	DWORD dwStyle;
	if (mAllowResize)
	{
		dwStyle = WS_OVERLAPPEDWINDOW;
	}
	else
	{
		dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
	}

	// �����ض��ͻ�����С�Ĵ��ڴ�С
	RECT rect = { 0, 0, mWidth-1, mHeight-1 };
	AdjustWindowRect(&rect, dwStyle, FALSE);

	// ��������
	mhWnd = CreateWindow(sWindowClass, mWindowTitle.c_str(),
		dwStyle, mXPosition, mYPosition,
		rect.right - rect.left + 1, rect.bottom - rect.top + 1, 0, 0, 0, 0);

	// === ��Ⱦ�� ===

#ifdef PX2_USE_DX9
	// ������Ⱦ��
	mInput.mWindowHandle = mhWnd;
	mInput.mDriver = Direct3DCreate9(D3D_SDK_VERSION);
	assertion(mInput.mDriver != 0, "Failed to create Direct3D9\n");
	mRenderer = new0 Renderer(mInput, mWidth, mHeight,
		mColorFormat, mDepthStencilFormat, mNumMultisamples);
#endif

#ifdef PX2_USE_OPENGLES2
	mInput.mWindowHandle = mhWnd;
	mInput.mRendererDC = GetDC(mhWnd);
	mRenderer = new0 Renderer(mInput, mWidth, mHeight,
		mColorFormat, mDepthStencilFormat, mNumMultisamples);
#endif

	mRenderer->SetClearColor(mClearColor);

	mCamera = new0 Camera();
	mRenderer->SetCamera(mCamera);

	return true;
}
#endif
//----------------------------------------------------------------------------
#ifdef __ANDROID__
bool Application::OnInitlize ()
{
	ApplicationBase::OnInitlize();

#ifdef PX2_USE_OPENGLES2
	mRenderer = new0 Renderer(mInput, mWidth, mHeight,
		mColorFormat, mDepthStencilFormat, mNumMultisamples);
#endif

	mRenderer->SetClearColor(mClearColor);

	mCamera = new0 Camera();
	mRenderer->SetCamera(mCamera);

	return true;
}
#endif
//----------------------------------------------------------------------------
#if defined(_WIN32) || defined(WIN32)
bool Application::OnTernamate()
{
	ApplicationBase::OnTernamate();

	mCamera = 0;

	delete0(mRenderer);
#ifdef PX2_USE_DX9
	mInput.mDriver->Release();
#endif

	return true;
}
#endif
//----------------------------------------------------------------------------
#ifdef __ANDROID__
bool Application::OnTernamate()
{
	ApplicationBase::OnTernamate();

	mCamera = 0;

	delete0(mRenderer);

	return true;
}
#endif
//----------------------------------------------------------------------------