/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2GraphicsRoot.hpp
*
* �汾		:	1.0 (2012/04/15)
*
* ����		��	more
*
*/

#ifndef PX2GRAPHICSROOT_HPP
#define PX2GRAPHICSROOT_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2Camera.hpp"
#include "PX2Light.hpp"
#include "PX2Singleton.hpp"

namespace PX2
{

	class GraphicsRoot : public Singleton<GraphicsRoot>
	{
	public:
		GraphicsRoot ();
		~GraphicsRoot ();

		bool Initlize ();
		bool Terminate ();

		void AddLight (Light *light);
		void RemoveLight (Light *light);
		void ClearAllLights ();
		int GetNumLights ();
		Light *GetLight (int index);

	private:
		PX2::CameraPtr mCamera;
		std::vector<LightPtr> mAllLights; // ������ڳ����е����еƹ�
		static std::string PX2Path;
	};

}

#endif