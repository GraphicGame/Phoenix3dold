/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2Particle.hpp
*
* �汾		:	1.0 (2011/12/17)
*
* ����		��	more
*
*/

#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "PX2EffectPrerequisites.hpp"

namespace PX2
{

	class EffectEvent;

	/// ����
	class Particle
	{
	public:
		Particle ();
		~Particle ();

		float		SizeU;
		float		SizeR;
		float		SizeUStep;
		float		SizeRStep;

		float		Life;
		float		Age;
		float		EventTime;

		Float3		Color;
		Float3		ColorStep;
		float		Alpha;
		float		AlphaStep;

		APoint		Pos;
		APoint		PrePos;

		AVector		InitialDVector;
		AVector		InitialUVector;
		AVector		InitialRVector;
		AVector		DVector;
		AVector		UVector;
		AVector		RVector;

		AVector		RotAxis;
		float		RotDegree;		//< ����
		float		RotSpeed;
		float		RotSpeedStep;

		float		Speed;
		float		SpeedStep;
		AVector		SpeedDir;
		AVector		SpeedDirStep;

		std::vector<PX2::Pointer0<PX2::EffectEvent> >::iterator CurEvent; //< ��ǰ����ִ�е��¼�

		bool Update (float elapsedTime);
	};

}

#endif