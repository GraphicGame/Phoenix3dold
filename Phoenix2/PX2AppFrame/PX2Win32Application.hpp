/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2Win32Application.hpp
*
* �汾		:	1.0 (2011/02/02)
*
* ����		��	more
*
*/

#ifndef PX2WIN32APPLICATION_HPP
#define PX2WIN32APPLICATION_HPP

#include "PX2Application.hpp"
#include <windows.h>

namespace PX2
{

	class Win32Application : public Application
	{
	public:
		Win32Application ();
		virtual ~Win32Application ();

		// ����
		void Run ();

		// ��ʼ/�ս�
		virtual bool Initlize ();
		virtual bool OnInitlize ();
		virtual bool OnTernamate ();
		virtual bool Ternamate ();

		// �߼�����Ⱦ
		virtual void OnIdle ();

	protected:
		// ���ڲ���
		std::string mWindowTitle;
		int mXPosition, mYPosition, mWidth, mHeight;
		Float4 mClearColor;
		bool mAllowResize;

		// ����
		HWND mhWnd;

		// ��Ⱦ���
		Texture::Format mColorFormat;
		Texture::Format mDepthStencilFormat;
		int mNumMultisamples;
		Renderer* mRenderer;
		CameraPtr mCamera;

#ifdef PX2_USE_DX9
		RendererInput mInput;
#endif

		// EventSystem
		EventWorldPtr mEventWorld;
		OISEventAdapterPtr mOISEventAdapter;

		// ResourceManager
		ResourceManager *mResManager;

		// UserInterface
		UIManagerPtr mUIManager;

		// ��Ⱦ���ܺ���
		void ResetTime ();
		void MeasureTime ();
		void UpdateFrameCount ();
		void DrawFrameRate (int x, int y, const Float4& color);

		double mLastTime, mAccumulatedTime, mFrameRate;
		int mFrameCount, mAccumulatedFrameCount, mTimer, mMaxTimer;
	};

}

#endif