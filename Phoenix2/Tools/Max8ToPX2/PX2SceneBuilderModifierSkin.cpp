/*
*
* �ļ�����	��	PX2SceneBuilderSkinModifier.cpp
*
*/

#include "PX2SceneBuilder.hpp"
using namespace PX2;

void SceneBuilder::ProcessSkin(INode *node, Modifier *skinMod)
{
	// ����Ƥ�������������Max�����񱻰��ղ���ϸ�֣�ÿһ��������Ҫ�Լ�����Ƥ
	// ��Ϣ����������Ƥ��Ϣ�е�offset���ڶ�����ʼʱ�����㣬�ǹ���������任��
	//
	// node:
	//		ָ����Ƥ�޸���ָ���Max�еĽڵ㡣
	// skinMod:
	//		ָ����Ƥ�޸���

	// 1. ���max��Ƥ��Ϣ�еĹ�������Ӧ����turandot�Ĺ����ڵ��б�
	// 2. ���maxNodeӰ���turandot����
	// 3. ���max��ÿ��������Ӱ���turandot�����еĶ�������������Բ�����Ƥ��Ϣ
	//	  Ӱ�������
	// 4. ����turandot mesh����Ƥ��Ϣ������SkinControl��AttachController��
	//    turandot mesh�ϡ�

	// 1

	bool needDel;
	TriObject *triObj = GetTriObject(node, &needDel);
	Mesh *maxMesh = &triObj->GetMesh();

	// MaxƤ���������ӿ�
	ISkin *skin = (ISkin*)skinMod->GetInterface(I_SKIN);
	ISkinContextData *skinData = skin->GetContextInterface(node);

	// max Skin Bones -> Phoenix2 Skin Bones
	int b, allBoneQuantity = skin->GetNumBones();
	PX2::Node **bones = new1<PX2::Node*>(allBoneQuantity);
	for (b=0; b<allBoneQuantity; b++)
	{
		INode *boneNode = skin->GetBone(b);
		bones[b] = PX2::StaticCast<PX2::Node>(mScene->GetObjectByName(boneNode
			->GetName()));
	}

	// 1

	// ���maxNode�������turandot mesh
	std::vector<PX2::TriMesh*> meshes;
	PX2::Object *object = mScene->GetObjectByName(node->GetName());
	if (object->IsExactly(PX2::TriMesh::TYPE))
	{
		meshes.push_back(PX2::StaticCast<PX2::TriMesh>(object));
	}
	else
	{
		PX2::Node *node = PX2::StaticCast<PX2::Node>(object);
		const char *nName = node->GetName().c_str();
		for (int c=0; c<node->GetNumChildren(); c++)
		{
			PX2::Movable *child = node->GetChild(c);
			const char *cName = child->GetName().c_str();
			if (strncmp(cName, nName, strlen(cName)) == 0)
			{
				meshes.push_back(PX2::StaticCast<PX2::TriMesh>(child));
			}
		}
	}

	// ΪPhoenix2��ÿ����������ص�Ƥ��������

	int *vertNumInfuseByBone = new1<int>(allBoneQuantity);
	for (int m=0; m<(int)meshes.size(); m++)
	{
		PX2::TriMesh *mesh = meshes[m];

		// turandot������max�����е�����
		PX2::VertexBuffer *vb = mesh->GetVertexBuffer();
		int tdMeshVertexNum = vb->GetNumElements();
		std::vector<int> VIArray;
		int v, i, j, k;

		PX2::VertexBufferAccessor vba(mesh->GetVertexFormat(), vb);

		// 3

		for (int v=0; v<tdMeshVertexNum; ++v)
		{
			Float3 &position = vba.Position<Float3>(v);
			for (i=0; i<maxMesh->getNumVerts(); i++)
			{
				if (position[0] == maxMesh->verts[i].x
					&& position[1] == maxMesh->verts[i].y 
					&& position[2] == maxMesh->verts[i].z)
				{
					VIArray.push_back(i);
					break;
				}
			}
		}

		// ȷ��ÿ��������Ӱ��Ķ�������
		int vertexNumEqualInMax = (int)VIArray.size();
		memset(vertNumInfuseByBone, 0, sizeof(int)*allBoneQuantity);
		for (i=0; i<vertexNumEqualInMax; i++)
		{
			v = VIArray[i];
			for (j=0; j<skinData->GetNumAssignedBones(v); j++)
			{
				b = skinData->GetAssignedBone(v, j);
				vertNumInfuseByBone[b]++;
			}
		}

		// ���Max�������Ǳ����ղ��ʷָ�ģ�����һЩ�����Ե�ǰPhoenix2����û��
		// Ӱ��
		int bQuantity = 0; // Ӱ�쵱ǰPhoenix2����Ĺ�������
		for (b=0; b<allBoneQuantity; b++)
		{
			if (vertNumInfuseByBone[b] > 0)
				bQuantity++;
		}

		if (bQuantity == 0)
		{
			// Truandot���񲻱��κι���Ӱ�죬������һ������
			continue;
		}

		// 4

		PX2::Node **theBones = new1<PX2::Node*>(bQuantity);
		float **weight = new2<float>(bQuantity, vertexNumEqualInMax);
		PX2::APoint **offset = new2<PX2::APoint>(bQuantity, vertexNumEqualInMax);

		std::vector<int> bIArray(allBoneQuantity);
		for (b=0, k=0; b<allBoneQuantity; b++)
		{
			if (vertNumInfuseByBone[b] > 0)
			{
				theBones[k] = bones[b];
				bIArray[b] = k;
				k++;
			}
		}

		// �������㣬���㶥��Ȩ�غ�offset
		for (i=0; i<vertexNumEqualInMax; i++)
		{
			v = VIArray[i];
			for (j=0; j<skinData->GetNumAssignedBones(v); j++)
			{ // ����Ӱ���Max����Ĺ���
				b = skinData->GetAssignedBone(v, j);
				k = bIArray[b];
				weight[i][k] = skinData->GetBoneWeight(v, j); // ��j��������Ӱ��
															  // Ȩ��
				Float3 &position = vba.Position<Float3>(i);
				APoint point = bones[k]->WorldTransform.Inverse() 
					* (mesh->WorldTransform * APoint(position));
				offset[i][k] = Float3(point.X(), point.Y(), point.Z());
			}
		}

		PX2::SkinController *skinController = new0 PX2::SkinController
			(tdMeshVertexNum, bQuantity);
		
		
		skinController->MinTime = 0.0f;
		skinController->MaxTime = TicksToSec(mTimeEnd - mTimeStart);

		mesh->AttachController(skinController);
	}

	if (needDel)
	{
		delete0(triObj);
	}

	delete1(bones);
	delete1(vertNumInfuseByBone);
}
//----------------------------------------------------------------------------