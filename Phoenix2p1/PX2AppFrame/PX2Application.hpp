/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2Application.hpp
*
* �汾		:	1.0 (2012/04/15)
*
* ����		��	more
*
*/

#ifndef PX2APPLICATION_HPP
#define PX2APPLICATION_HPP

#include "PX2Core.hpp"
#include "PX2Mathematics.hpp"
#include "PX2Graphics.hpp"
#include "PX2Renderers.hpp"

namespace PX2
{

	class Application
	{
	protected:
		Application ();
	public:
		virtual ~Application ();

		// App
		static Application* msApplication;

		// system use
		bool Initlize ();
		bool Ternamate ();

		// you overwrite these
		virtual bool OnInitlize ();
		virtual bool OnTernamate ();
		virtual bool OnEnterForeground();
		virtual bool OnEnterBackground();

		// Enteries
		typedef bool (*AppInitlizeFun)();
		static AppInitlizeFun msAppInitlizeFun;
		typedef bool (*AppTernamateFun)();
		static AppTernamateFun msAppTernamateFun;
		typedef int (*EntryPoint)(int numArguments, char** arguments);
		static EntryPoint msEntry;

		virtual int Main (int numArguments, char** arguments);

	protected:
		// ��Ⱦ���ܺ���
		void ResetTime ();
		void MeasureTime ();
		void UpdateFrameCount ();
		void DrawFrameRate (int x, int y, const Float4& color);
		
		// ��Ⱦ���
		Texture::Format mColorFormat;
		Texture::Format mDepthStencilFormat;
		int mNumMultisamples;
		Float4 mClearColor;
		Renderer* mRenderer;
		CameraPtr mCamera;

		GraphicsRoot *mRoot;

		double mLastTime, mAccumulatedTime, mFrameRate;
		int mFrameCount, mAccumulatedFrameCount, mTimer, mMaxTimer;
	};

}

#endif