/*
*
* �ļ�����	��	PX2Controlledable.hpp
*
*/

#ifndef PX2CONTROLLEDOBJECT_HPP
#define PX2CONTROLLEDOBJECT_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2Controller.hpp"

namespace PX2
{
	
	/// ����������
	/**
	* �Ӵ�������������а󶨿������Ĺ��ܡ�
	*/
	class Controlledable : public Object
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(Controlledable);

	protected:
		Controlledable ();
	public:
		virtual ~Controlledable ();

		// ���ʿ��ƶ���Ŀ�����
		int GetNumControllers () const;
		inline Controller* GetController (int i) const;
		void AttachController (Controller* controller);
		void DetachController (Controller* controller);
		void DetachAllControllers ();
		bool UpdateControllers (double applicationTime);

	private:
		// �����������Ŀ���������
		enum { CO_GROW_BY = 4 };
		int mNumControllers, mCapacity;
		ControllerPtr* mControllers;
	};

	PX2_REGISTER_STREAM(Controlledable);
	typedef Pointer0<Controlledable> ControlledablePtr;
#include "PX2Controlledable.inl"

}

#endif