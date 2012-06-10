/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2UIManager.hpp
*
* �汾		:	1.0 (2011/02/23)
*
* ����		��	more
*
*/

#ifndef PX2UIMANAGER_HPP
#define PX2UIMANATER_HPP

#include "PX2UIPrerequisites.hpp"
#include "PX2Singleton.hpp"
#include "PX2VertexFormat.hpp"
#include "PX2Camera.hpp"
#include "PX2UIFrame.hpp"
#include "PX2UIMaterial.hpp"
#include "PX2EventHandler.hpp"
#include "PX2Help.hpp"

namespace PX2
{

	class UIManager : public Singleton<UIManager>, public EventHandler
	{
	public:
		UIManager (EventWorld *eventWorld);
		UIManager (EventWorld *eventWorld, float width, float height);
		~UIManager ();

		// ��Ϣ����
		EventWorld *GetEventWorld ();

		// ID
		int GetNextID ();

		// �����ʽ
		VertexFormat *GetUIVertexFromat ();

		// ���
		Camera *GetUICamera ();

		// UI����
		UIMaterial *GetUIMaterial ();

		// App ����
		float GetWndWidth ();
		float GetWndHeight ();

		UIFrame *CreateAddAddUIFrame (const std::string &name, bool isForwardUI=true);
		void AddUIFrame (UIFrame *group, bool isForwardUI=true);
		bool RemoveUIFrame (const int ID);
		bool RemoveUIFrame (const std::string &name);
		void RemoveAllGroups ();

		UIFrame *GetUIFrame (const int ID);
		UIFrame *GetUIFrame (const std::string &name);

		// �¼�
		virtual void DoExecute (Event *event);

		/// ��ÿɼ���
		/**
		* �򵥵Ľ�����Ԫ�صļ���ͼ�μӵ��ɼ����С�
		*/
		VisibleSet &GetVisibleSet();

		/// ����������Ŀɼ�����ͼ��
		void DrawSorted (Renderer *renderer);

		// ����
		/**
		* �򵥵ر�������Ԫ�ؽ��л��ơ�
		*/
		void Draw (Renderer *renderer);

	private:
		UIManager ();

		EventWorldPtr mEventWorld;
		int mNextID;
		float mWndWidth;
		float mWndHeight;
		VertexFormatPtr mVFormat;
		CameraPtr mCamera;
		UIMaterialPtr mUIMaterial;

		VisibleSet mSet;

		std::vector<UIFramePtr> mForwardUIFrames;
		std::vector<UIFramePtr> mBackgroundUIFrames;
	};

	typedef Pointer0<UIManager> UIManagerPtr;

}

#endif