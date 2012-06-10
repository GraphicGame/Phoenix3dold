/*
* Turandot 3D ��Ϸ���� Version 1.0
*
* Copyright (C) 2009-2011 http://www.Turandot3d.org/
*
* �ļ�����	��	Path.hpp
*
* �汾		:	1.0 (2011/07/24)
*
* ����		��	���
*
*/

#ifndef PATH_HPP
#define PATH_HPP

namespace Td
{

	class Path 
	{
	public:
		Path ();
		Path (int numWayPoints, AVector minPos, AVector maxPos,
			bool loop = true);

		std::list<APoint> CreateRandomPath (int numWayPoints, AVector minPos,
			AVector maxPos);

		void AddPoint (APoint point);
		APoint GetCurrentWayPoint () const { return *mCurWayPoint; }
		void SetNextWayPoint ();
		void Clear ();
		std::list<APoint> GetPoints ();

		bool IsFinished () { return mCurWayPoint == mWayPoints.end(); }

		void EnableLoop () { mLoop = true; }
		void DisableLoop () { mLoop = false; }

	protected:
		std::list<APoint> mWayPoints;
		std::list<APoint>::iterator mCurWayPoint;
		bool mLoop;
	};

}

#endif