/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2ActorSelection.hpp
*
* �汾		:	1.0 (2011/06/06)
*
* ����		��	more
*
*/

#ifndef PX2ACTORSELECTION_HPP
#define PX2ACTORSELECTION_HPP

#include "PX2EditorLibPrerequisites.hpp"

namespace PX2Editor
{

	class ActorSelection : public PX2::Singleton<ActorSelection>
	{
	public:
		ActorSelection ();
		~ActorSelection ();

		void AddActor (PX2::Actor *actor);
		void RemoveActor (PX2::Actor *actor);
		PX2::Actor *GetActor (int i);
		int GetActorQuantity ();
		bool IsActorIn (PX2::Actor *actor);
		void Clear ();

		void Translate (PX2::AVector vec);
		void AddRolate (PX2::AVector vec);
		void AddScale (PX2::AVector vec);

	private:
		std::vector<PX2::ActorPtr> mActors;
	};
}

#endif