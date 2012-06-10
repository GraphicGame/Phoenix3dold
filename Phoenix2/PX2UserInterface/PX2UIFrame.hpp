/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2UIFrame.hpp
*
* �汾		:	1.0 (2011/02/23)
*
* ����		��	more
*
*/

#ifndef PX2UICONTAINER_HPP
#define PX2UICONTAINER_HPP

#include "PX2UIPrerequisites.hpp"
#include "PX2UIElement.hpp"

namespace PX2
{

	class UIFrame : public UIElement
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;

	public:
		UIFrame (UIFrame *parentContainer, int ID, std::string name,
			float deltaX=0.0f, float deltaY=0.0f,
			float width=800.0f, float height=600.0f,
			bool visible=true);
		virtual ~UIFrame ();

		// ��λ
		virtual void SetPosition (float offsetParentX, float offsetParentY);
		virtual void Move (float deltaX, float deltaY);

		// �ؼ����
		UIElement* GetElement (const std::string name) const;
		UIElement* GetElement (int ID) const;

		UIElement *CreateAndAddElement (UIElement::UIType type);
		void AddElement (UIElement *element);
		bool RemoveElement (int ID);
		bool RemoveElement (const std::string &name);
		void RemoveAllElements ();

		// �¼�
		virtual void OnEvent (Event *event);

		virtual void GetVisibleSet (VisibleSet &set);

		virtual void Draw (Renderer *renderer);

	private:
		void SortInOrder ();
		std::vector<UIElementPtr> mElements;
	};

	typedef Pointer0<UIFrame> UIFramePtr;
}

#endif