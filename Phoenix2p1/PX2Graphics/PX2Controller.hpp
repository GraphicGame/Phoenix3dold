/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2Controller.hpp
*
* �汾		:	1.0 (2011/02/01)
*
* ����		��	more
*
*/

#ifndef PX2CONTROLLER_HPP
#define PX2CONTROLLER_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2Object.hpp"

namespace PX2
{

	class Controlledable;

	class Controller : public Object
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(Controller);

	protected:
		Controller ();
	public:
		virtual ~Controller ();

		// ��Ա����
		inline Controlledable* GetObject () const;
		inline void SetApplicationTime (double applicationTime);
		inline double GetApplicationTime () const;

		// �������£�applicationTime���Ժ��������㵥λ��
		virtual bool Update (double applicationTime);

		/// ������������
		enum RepeatType
		{
			RT_CLAMP,
			RT_WRAP,
			RT_CYCLE
		};
		
		// ��Ա����
		RepeatType Repeat;  //< default = RT_CLAMP
		double MinTime;     //< default = 0
		double MaxTime;     //< default = 0
		double Phase;       //< default = 0
		double Frequency;   //< default = 1
		bool Active;        //< default = true

public_internal:
		/// ���ñ����ƵĶ���
		virtual void SetObject (Controlledable* object);

	protected:
		/// ��Ӧ�ó����ʱ��ת�����������ĵ�ǰʱ�䡣�������ڸ����Լ���ʱ���
		/// �õ��˺�����
		double GetControlTime (double applicationTime);

		/// ʹ��һ������ָ��ָ�򱻿��ƵĶ�����������controller��mObject֮��
		/// smartָ���ѭ������
		Controlledable* mObject;

		/// �Ժ�������λ��Ӧ�ó����¼�
		double mApplicationTime;
	};

	PX2_REGISTER_STREAM(Controller);
	typedef Pointer0<Controller> ControllerPtr;
#include "PX2Controller.inl"

}

#endif