/*
*
* �ļ�����	��	PX2Controller.hpp
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
		Controlledable* GetControlledable () const;
		double GetApplicationTime () const;

		// �������£�applicationTime���Ժ��������㵥λ��
		virtual bool Update (double applicationTime);
		bool IsTimeInited ();
		void Reset ();
		double GetElapsedTime (); //< ���֡����ʱ�䣬��Update���ú����
		double GetRunTime ();

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
		virtual void SetControlledable (Controlledable* object);

	protected:
		/// ��Ӧ�ó����ʱ��ת�����������ĵ�ǰʱ�䡣�������ڸ����Լ���ʱ���
		/// �õ��˺�����
		double GetControlTime (double applicationTime);

		/// ʹ��һ������ָ��ָ�򱻿��ƵĶ�����������controller��mObject֮��
		/// smartָ���ѭ������
		Controlledable* mObject;

		/// �Ժ�������λ��Ӧ�ó����¼�
		double mApplicationTime;
		double mLastApplicationTime;

		bool mIsTimeInited;
		double mInitedApplicationIime;
	};

	PX2_REGISTER_STREAM(Controller);
	typedef Pointer0<Controller> ControllerPtr;
#include "PX2Controller.inl"

}

#endif