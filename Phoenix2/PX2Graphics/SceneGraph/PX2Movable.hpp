/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2Movable.hpp
*
* �汾		:	1.0 (2011/02/01)
*
* ����		��	more
*
*/

#ifndef PX2SPATIAL_HPP
#define PX2SPATIAL_HPP

#include "PX2GraphicsPrerequisites.hpp"
#include "PX2Controlledable.hpp"
#include "PX2Bound.hpp"
#include "PX2Transform.hpp"

namespace PX2
{

	class Culler;
	
	/// �ռ伸������
	/**
	* ������Ҫ�ռ�����֧�ֵ����Ͷ��Ӵ���������ͬʱ֧�ֽ�ͷ��ü����ܡ��ռ�����
	* �������ռ�任����Χ�С�
	*/
	class Movable : public Controlledable
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(Movable);

	protected:
		Movable ();
	public:
		virtual ~Movable ();

		/// ���غ�����任
		/**
		* ��ĳЩ����£���Ҳ����Ҫֱ����������任�����World�������ˣ�
		* WorldIsCurrent��ʶҲ��ñ�����Ϊtrue��
		*/
		Transform LocalTransform;
		Transform WorldTransform;
		bool WorldTransformIsCurrent;

		/// �����Χ�з���
		/**
		* ��ĳЩ����£���Ҳ����Ҫֱ�����������Χ�С����WorldBound��ֱ������
		* ��WorldBoundIsCurrentӦ�ñ�����Ϊtrue��
		*/
		Bound WorldBound;
		bool WorldBoundIsCurrent;

		/// �ü�����
		enum CullingMode
		{
			/// ͨ���Ƚϰ�Χ�кͲü��棬��������Ŀɼ��ԡ�
			CULL_DYNAMIC,

			/// ǿ�����屻�ü��������һ��Node���ü��ˣ���Node�µ������ӽڵ�Ҳ
			/// ���ü���	
			CULL_ALWAYS,

			/// ��Զ���ü����塣���һ��Node�����ü�����Node�µ������ӽڵ�Ҳ��
			/// ���ü���
			CULL_NEVER
		};

		CullingMode Culling;

		/// ���¼���״̬�Ϳ�����
		/**
		* �������¸��³����任�����ϸ��������Χ�С�
		*/
		void Update (double applicationTime = -Mathd::MAX_REAL,
			bool initiator = true);

		/// ��ø���
		inline Movable* GetParent ();

		// �ҽ�
		/*
		* ���ڵ㱻���ص�������ʱ�����ش˺�������ʵ���Լ���Ҫ�Ĳ�����ͨ������
		* ���ڵ��Attach��Detach�����������������Ĭ�Ϻ�����Ϊ�ա�
		*/
		virtual void OnAttach ();
		virtual void OnDetach (); 

	protected:
		// ����״̬����
		virtual void UpdateWorldData (double applicationTime);
		virtual void UpdateWorldBound () = 0;
		void PropagateBoundToRoot ();

public_internal:
		// �����ü�
		void OnGetVisibleSet (Culler& culler, bool noCull);
		virtual void GetVisibleSet (Culler& culler, bool noCull) = 0;

		// ���ø��ڵ㣬�ڵ���attach/detach��ʱ����ô˺�����
		inline void SetParent (Movable* parent);

	protected:
		Movable* mParent;
	};

	PX2_REGISTER_STREAM(Movable);
	typedef Pointer0<Movable> MovablePtr;
#include "PX2Movable.inl"

}

#endif