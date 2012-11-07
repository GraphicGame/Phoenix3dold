/*
* Phoenix 3D ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2ScopedCS.hpp
*
* �汾		:	1.0 (2011/01/30)
*
* ����		��	more
*
*/

#ifndef PX2SCOPEDCS_HPP
#define PX2SCOPEDCS_HPP

#include "PX2CorePre.hpp"
#include "PX2Mutex.hpp"

namespace PX2
{

	/// ����Χ�ࣺScoped critial section
	/**
	* ������һ����Χ�������ľֲ���ʱ���󴴽�һ��mutex�����˳�����ʱ���Զ��ͷ�
	* ���mutex��
	*/
	class ScopedCS
	{
	public:
		ScopedCS (Mutex* mutex);
		~ScopedCS ();

	private:
		Mutex* mMutex;
	};

}

#endif
