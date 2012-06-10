/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2TransformController.hpp
*
* �汾		:	1.0 (2011/02/01)
*
* ����		��	more
*
*/

#ifndef PX2TRANSFORMCONTROLLER_HPP
#define PX2TRANSFORMCONTROLLER_HPP

#include "PX2GraphicsPrerequisites.hpp"
#include "PX2Controller.hpp"
#include "PX2Transform.hpp"

namespace PX2
{

	class PX2_GRAPHICS_ENTRY TransformController : public Controller
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(TransformController);

	public:
		TransformController (const Transform& localTransform);
		virtual ~TransformController ();

		// ��Ա����
		inline void SetTransform (const Transform& localTransform);
		inline const Transform& GetTransform () const;

		// ��������
		/**
		* �ԡ����롱Ϊ��λ������֪ʶ�򵥵Ľ�mLocalTransform������mObject��
		* LocalTransform�С�
		*/
		virtual bool Update (double applicationTime);

	protected:
		Transform mLocalTransform;
	};

	PX2_REGISTER_STREAM(TransformController);
	typedef Pointer0<TransformController> TransformControllerPtr;
#include "PX2TransformController.inl"

}

#endif
