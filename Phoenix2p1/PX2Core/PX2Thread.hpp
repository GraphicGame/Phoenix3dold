/*
* Phoenix 3D ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2Thread.hpp
*
* �汾		:	1.0 (2011/01/30)
*
* ����		��	more
*
*/

#ifndef PX2THREAD_HPP
#define PX2THREAD_HPP

#include "PX2CorePre.hpp"
#include "PX2ThreadType.hpp"

namespace PX2
{

	class Thread
	{
	public:
		Thread (void* function, void* userData, unsigned int processorNumber = 0,
			unsigned int stackSize = 0);

		~Thread ();

		/// �ָ�
		void Resume ();

		/// ����
		void Suspend ();

	private:
		ThreadType mThread;
		unsigned int mThreadID;
		void* mFunction;
		void* mUserData;
		unsigned int mProcessorNumber;
		unsigned int mStackSize;
	};

}

#endif
