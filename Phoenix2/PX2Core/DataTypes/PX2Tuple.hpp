/*
* Phoenix 3D ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2Tuple.hpp
*
* �汾		:	1.0 (2011/01/29)
*
* ����		��	more
*
*/

#ifndef PX2TUPLE_HPP
#define PX2TUPLE_HPP

#include "PX2CorePrerequisites.hpp"

namespace PX2
{

	/// Ԫ����
	/**
	* TYPE��ԭʼ�������ݻ������������ݣ���Ҫ������ĳ�Ա
	* TYPE::TYPE ()
	* TYPE::TYPE (const TYPE&);
	* TYPE& TYPE::operator= (const TYPE&)
	*/
	template <int DIMENSION, typename TYPE>
	class Tuple
	{
	public:
		Tuple ();
		Tuple (const Tuple& tuple);
		~Tuple ();

		inline operator const TYPE* () const;
		inline operator TYPE* ();
		inline const TYPE& operator[] (int i) const;
		inline TYPE& operator[] (int i);

		Tuple& operator= (const Tuple& tuple);

		bool operator== (const Tuple& tuple) const;
		bool operator!= (const Tuple& tuple) const;
		bool operator<  (const Tuple& tuple) const;
		bool operator<= (const Tuple& tuple) const;
		bool operator>  (const Tuple& tuple) const;
		bool operator>= (const Tuple& tuple) const;

	protected:
		TYPE mTuple[DIMENSION];
	};

#include "PX2Tuple.inl"

}

#endif