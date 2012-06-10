/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2EffectEdit.hpp
*
* �汾		:	1.0 (2011/08/02)
*
* ����		��	more
*
*/

#ifndef PX2EFFECTEDIT_HPP
#define PX2EFFECTEDIT_HPP

#include "PX2EditorLibPrerequisites.hpp"

namespace PX2Editor
{

	class EffectEdit
	{
	public:
		EffectEdit ();
		~EffectEdit ();

		void SetEditEffectNode (PX2::EffectNode *node);
		PX2::EffectNode *GetEditEffectNode ();

		void SetEditEffect (PX2::Movable *obj);
		PX2::Movable *GetEditEffect ();

		// ��ǰ׼�������¼���ʱ��
		/**
		* �����ȡ��ʱ��С��0������������¼�
		*/
		void SetInsertingTime (float insertingTime);
		float GetInsertingTime ();

	private:
		PX2::EffectNodePtr mEffectNode;
		PX2::MovablePtr mEffect;
		float mInsertingTime; // ��ǰ׼������ؼ�֡��ʱ��
	};
}

#endif