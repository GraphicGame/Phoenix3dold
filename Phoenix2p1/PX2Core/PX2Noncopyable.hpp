/*
* Phoenix 3D ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2Noncopyable.hpp
*
* �汾		:	1.0 (2011/01/30)
*
* ����		��	more
*
*/

#ifndef PX2NONCOPYABLE_HPP
#define PX2NONCOPYABLE_HPP

namespace PX2
{

	/// �Ӵ���������Ķ��󽫲��ɱ�����
	class Noncopyable
	{
	protected:
		Noncopyable () {}
		~Noncopyable () {}

	private:
		Noncopyable (const Noncopyable &);
		Noncopyable &operator = (const Noncopyable &);
	};

}

#endif