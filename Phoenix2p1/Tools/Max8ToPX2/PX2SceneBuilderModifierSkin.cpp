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

	// 1. ���max��Ƥ��Ϣ�еĹ�������Ӧ����Phoenix�Ĺ����ڵ��б�
	// 2. ���maxNodeӰ���Phoenix����
	// 3. ���max��ÿ��������Ӱ���Phoenix�����еĶ�������������Բ�����Ƥ��Ϣ
	//	  Ӱ�������
	// 4. ����Phoenix mesh����Ƥ��Ϣ������SkinControl��AttachController��
	//    Phoenix mesh�ϡ�
	
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
		PX2::Node *node = PX2::StaticCast<PX2::Node>(mScene->GetObjectByName(
			boneNode->GetName()));
		bones[b] = node;
	}

	// 1

	// ���maxNode�������Phoenix mesh
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

		// Phoenix������max�����е�����
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
			// Phoenix���񲻱��κι���Ӱ�죬������һ������
			continue;
		}

		// 4

		PX2::Node **theBones = new1<PX2::Node*>(bQuantity);
		float **weight = new2<float>(bQuantity, vertexNumEqualInMax);
		memset(weight[0],0,bQuantity*vertexNumEqualInMax*sizeof(float));
		PX2::APoint **offset = new2<PX2::APoint>(bQuantity, vertexNumEqualInMax);
		memset(offset[0],0,bQuantity*vertexNumEqualInMax*sizeof(PX2::APoint));

		// ����max������Phoenix������Ӧ������(k)
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
				float wit = skinData->GetBoneWeight(v, j); // ��j��������Ӱ��Ȩ��
				weight[i][k] = wit;

				Float3 &position = vba.Position<Float3>(i);
				APoint point = bones[k]->WorldTransform.Inverse() 
					* (mesh->WorldTransform * APoint(position));
				offset[i][k] = Float3(point.X(), point.Y(), point.Z()); // ������Ӱ������е�λ��
			}
		}

		PX2::SkinController *skinCtrl = new0 PX2::SkinController
			(vertexNumEqualInMax, bQuantity);
		for (int i=0; i<bQuantity; i++)
		{
			skinCtrl->GetBones()[i] = theBones[i];
		}
		for (int i=0; i<vertexNumEqualInMax; i++)
		{
			for (int j=0; j<bQuantity; j++)
			{
				float wgt = weight[i][j];
				APoint oft = offset[i][j];
				skinCtrl->GetWeights()[i][j] = wgt;
				skinCtrl->GetOffsets()[i][j] = oft; 
			}
		}
		
		skinCtrl->Repeat = Controller::RT_WRAP;
		skinCtrl->MinTime = 0.0f;
		skinCtrl->MaxTime = TicksToSec(mTimeEnd - mTimeStart);

		mesh->AttachController(skinCtrl);

		delete1(theBones);
		delete2(weight);
		delete2(offset);
	}

	if (needDel)
	{
		delete0(triObj);
	}

	delete1(bones);
	delete1(vertNumInfuseByBone);
}
//----------------------------------------------------------------------------