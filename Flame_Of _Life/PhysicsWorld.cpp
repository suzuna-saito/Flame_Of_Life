/*
@file	PhysicsWorld.h
@brief	�����蔻����s��
*/

/*
@brief	�C���N���[�h
*/
#include "pch.h"

//�����̃C���X�^���X�̏�����
PhysicsWorld* PhysicsWorld::mPhysics = nullptr;

PhysicsWorld::PhysicsWorld()
{
	InitBoxVertices();
	InitSquareVertices();
	InitLineVertices();

	mLineShader = new Shader();
	mLineShader->Load("shaders/LineWorld.vert", "shaders/Line.frag");
}

void PhysicsWorld::CreateInstance()
{
	if (mPhysics == nullptr)
	{
		mPhysics = new PhysicsWorld();
	}
}

void PhysicsWorld::DeleteInstance()
{
	if (mPhysics != nullptr)
	{
		delete mPhysics;
		mPhysics = nullptr;
	}
}

void PhysicsWorld::HitCheck()
{
	SphereAndSphere();
	BoxAndBox();
	SphereAndBox();
}

void PhysicsWorld::HitCheck(BoxCollider* _box)
{
	//�R���C�_�[�̐e�I�u�W�F�N�g��Active����Ȃ���ΏI������
	if (_box->GetOwner()->GetState() != State::Active)
	{
		return;
	}

	if (_box->GetTag() == ColliderTag::playerTag)
	{
		for (auto itr : mBoxes)
		{
			if (itr == _box)
			{
				continue;
			}

			//�R���C�_�[�̐e�I�u�W�F�N�g��Active����Ȃ���ΏI������
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			
			bool hit = Intersect(itr->GetWorldBox(), _box->GetWorldBox());

			if (hit)
			{
				OnCollisionFunc func = mCollisionFunction.at(_box);
				func((*(itr->GetOwner())));
				func = mCollisionFunction.at(itr);
				func(*(_box->GetOwner()));
				_box->Refresh();
			}

		}

		for (auto itr : mSpheres)
		{
			//�R���C�_�[�̐e�I�u�W�F�N�g��Active����Ȃ���ΏI������
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			bool hit = Intersect(itr->GetWorldSphere(), _box->GetWorldBox());
			if (hit)
			{
				OnCollisionFunc func = mCollisionFunction.at(_box);
				func(*(itr->GetOwner()));
				func = mCollisionFunction.at(itr);
				func(*(_box->GetOwner()));
				_box->Refresh();
			}
		}
	}

	if (_box->GetTag() == ColliderTag::playerLegsTag)
	{
		for (auto itr : mBoxes)
		{
			if (itr == _box)
			{
				continue;
			}

			if (itr->GetTag() != ColliderTag::groundTag)
			{
				continue;
			}

			//�R���C�_�[�̐e�I�u�W�F�N�g��Active����Ȃ���ΏI������
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}

			bool hit = Intersect(itr->GetWorldBox(), _box->GetWorldBox());

			if (hit)
			{
				OnCollisionFunc func = mCollisionFunction.at(_box);
				func((*(itr->GetOwner())));
				func = mCollisionFunction.at(itr);
				func(*(_box->GetOwner()));
				_box->Refresh();
			}

		}
	}

}

void PhysicsWorld::HitCheck(SphereCollider* _sphere)
{
	//�R���C�_�[�̐e�I�u�W�F�N�g��Active����Ȃ���ΏI������
	if (_sphere->GetOwner()->GetState() != State::Active)
	{
		return;
	}

	//�v���C���[�������Ɠ���������
	if (_sphere->GetTag() == ColliderTag::playerLegsTag)
	{
		//��
		for (auto itr : mBoxes)
		{
			//�R���C�_�[�̐e�I�u�W�F�N�g��Active����Ȃ���ΏI������ 
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			bool hit = Intersect(_sphere->GetWorldSphere(), itr->GetWorldBox());
			if (hit)
			{
				OnCollisionFunc func = mCollisionFunction.at(_sphere);
				func(*(itr->GetOwner()));
				func = mCollisionFunction.at(itr);
				func(*(_sphere->GetOwner()));
				_sphere->Refresh();
			}
		}
	}

}

void PhysicsWorld::AddBox(BoxCollider* _box, OnCollisionFunc _func)
{
	mBoxes.emplace_back(_box);
	//�R���C�_�[�̃|�C���^�Ɛe�I�u�W�F�N�g�̓����蔻�莞�֐��|�C���^
	mCollisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
}

void PhysicsWorld::RemoveBox(BoxCollider* _box)
{
	auto iter = std::find(mBoxes.begin(), mBoxes.end(), _box);
	if (iter != mBoxes.end())
	{
		std::iter_swap(iter, mBoxes.end() - 1);
		mBoxes.pop_back();
	}
	mCollisionFunction.erase(_box);
}

void PhysicsWorld::AddSphere(SphereCollider* _sphere, OnCollisionFunc _func)
{
	mSpheres.emplace_back(_sphere);
	//�R���C�_�[�̃|�C���^�Ɛe�I�u�W�F�N�g�̓����蔻�莞�֐��|�C���^
	mCollisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_sphere), _func));
}

void PhysicsWorld::RemoveSphere(SphereCollider* _sphere)
{
	auto iter = std::find(mSpheres.begin(), mSpheres.end(), _sphere);
	if (iter != mSpheres.end())
	{
		std::iter_swap(iter, mSpheres.end() - 1);
		mSpheres.pop_back();
	}
	mCollisionFunction.erase(_sphere);
}

void PhysicsWorld::DebugShowBox()
{
	// �f�o�b�O���[�h���H
	if (!mBoolDebugMode)
	{
		return;
	}

	// AABB�`�揀��
	Matrix4 scale, trans, world, view, proj, viewProj;
	view = RENDERER->GetViewMatrix();
	proj = RENDERER->GetProjectionMatrix();
	viewProj = view * proj;
	mLineShader->SetActive();
	mLineShader->SetMatrixUniform("uViewProj", viewProj);

	DrawCollisions(mBoxes, Color::Green);
}

void PhysicsWorld::SphereAndSphere()
{
	for (size_t i = 0; i < mSpheres.size(); i++)
	{
		if (mSpheres[i]->GetOwner()->GetState() != State::Active)
		{
			continue;
		}
		for (size_t j = i + 1; j < mSpheres.size(); j++)
		{
			if (mSpheres[j]->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			bool hit = Intersect(mSpheres[i]->GetWorldSphere(), mSpheres[j]->GetWorldSphere());

			if (hit)
			{
				SphereCollider* sphereA = mSpheres[i];
				SphereCollider* sphereB = mSpheres[j];

			}
		}
	}
}

void PhysicsWorld::BoxAndBox()
{
	for (size_t i = 0; i < mBoxes.size(); i++)
	{
		if (mBoxes[i]->GetOwner()->GetState() != State::Active)
		{
			continue;
		}
		for (size_t j = i + 1; j < mBoxes.size(); j++)
		{
			if (mBoxes[j]->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			bool hit = Intersect(mBoxes[i]->GetWorldBox(), mBoxes[j]->GetWorldBox());

			if (hit)
			{
				BoxCollider* boxA = mBoxes[i];
				BoxCollider* boxB = mBoxes[j];
			}
		}
	}
}

void PhysicsWorld::SphereAndBox()
{
	for (size_t i = 0; i < mSpheres.size(); i++)
	{
		if (mSpheres[i]->GetOwner()->GetState() != State::Active)
		{
			continue;
		}
		for (size_t j = 0; j < mBoxes.size(); j++)
		{
			if (mBoxes[j]->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			bool hit = Intersect(mSpheres[i]->GetWorldSphere(), mBoxes[j]->GetWorldBox());

		}
	}
}

void PhysicsWorld::InitBoxVertices()
{
	// �{�b�N�X���_���X�g
	float vertices[] = {
		0.0f, 0.0f, 0.0f,  // min
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f,  // max
		0.0f, 1.0f, 1.0f,
	};
	// �{�b�N�X�̃��C�����X�g
	unsigned int lineList[] = {
		0,1,
		1,2,
		2,3,
		3,0,
		4,5,
		5,6,
		6,7,
		7,4,
		0,4,
		1,5,
		2,6,
		3,7,
	};
	unsigned int vbo, ebo;
	glGenVertexArrays(1, &mBoxVAO);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glBindVertexArray(mBoxVAO);
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(lineList), lineList, GL_STATIC_DRAW);
	}
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void PhysicsWorld::InitSquareVertices()
{
	// �{�b�N�X���_���X�g
	float vertices[] = {  // ���������と��O�と��O��
		0.0f, 0.5f,-0.5f,
		0.0f, 0.5f, 0.5f,
		0.0f,-0.5f, 0.5f,
		0.0f,-0.5f,-0.5f,
		0.0f, 0.0f, 0.0f, // �@���\��
	   -1.0f, 0.0f, 0.0f,
	};
	// �{�b�N�X�̃��C�����X�g
	unsigned int lineList[] = {
		0,1,
		1,2,
		2,3,
		3,0,
		4,5
	};

	// ���_�z�� mSquareVAO�̐ݒ�
	unsigned int vbo, ebo;
	glGenVertexArrays(1, &mSquareVAO);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glBindVertexArray(mSquareVAO);
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(lineList), lineList, GL_STATIC_DRAW);
	}
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void PhysicsWorld::InitLineVertices()
{
	// ���C�����_���X�g
	float vertices[] =
	{
		0.0f,0.0f,0.0f,
		1.0f,0.0f,0.0f,
	};
	// ���C�����X�g
	unsigned int lineList[] =
	{
		0,1
	};
	// ���_�z�� mLineVAO�̐ݒ�
	unsigned int vbo, ebo;
	glGenVertexArrays(1, &mLineVAO);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glBindVertexArray(mLineVAO);
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(lineList), lineList, GL_STATIC_DRAW);
	}
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

}

// �Փ˃{�b�N�X�̕`��   // obj , color
void PhysicsWorld::DrawCollisions(std::vector<class BoxCollider*>& boxes, const Vector3& color)
{
	Matrix4 scaleMat, posMat, rotMat, worldMat, slopeRot;
	Vector3 scale, pos;

	mLineShader->SetVectorUniform("uColor", color);
	for (auto item : boxes)
	{
		//// Box�������ꍇ�̕`��
		//if (item->GetColliderType() == ColliderTypeEnum::Box)
		//{
			AABB box = AABB(Vector3::Zero, Vector3::Zero);
			Vector3 min, max;
			// ���̃I�u�W�F�̑傫���H
			box = item->GetWorldBox();

			// �{�b�N�X�̃X�P�[���ƈʒu���擾
			min = box.m_min;
			max = box.m_max;
			scale = max - min;
			pos = min;

			// scaleMat = �}�g���b�N�X4
			// scale��pos��matrix4�ɕϊ�
			scaleMat = Matrix4::CreateScale(scale);
			posMat = Matrix4::CreateTranslation(pos);

			worldMat = scaleMat * posMat;
			mLineShader->SetMatrixUniform("uWorld", worldMat);

			glBindVertexArray(mBoxVAO);
			glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);
		//}
		//// Wall�������ꍇ�̕`�� 
		//if (item->GetColliderType() == ColliderTypeEnum::Wall ||
		//	item->GetColliderType() == ColliderTypeEnum::Slope)
		//{
		//	WallCollider* wallcol;
		//	Wall walldata;

		//	Vector3 scale; // �`��X�P�[�����O�W��
		//	Vector3 pos; // �`��ʒu
		//	Vector3 normal; // �ǖ@��

		//	// WallCollider�ƕǃf�[�^�擾
		//	wallcol = dynamic_cast<WallCollider*>(item);
		//	walldata = wallcol->GetWall();
		//	normal = walldata.mNormal;
		//	// 4�_�̒��_�����߂�
		//	for (int i = 0; i < 4; i++)
		//	{
		//		pos += walldata.mWallVertex[i];
		//	}
		//	pos = pos * 0.25f;

		//	// �s��
		//	scaleMat = Matrix4::CreateScale(walldata.mScale);
		//	rotMat = Matrix4::CreateRotationZ(walldata.mZRotate);
		//	posMat = Matrix4::CreateTranslation(pos);
		//	slopeRot = Matrix4::CreateRotationY(walldata.mSlopeAngle);

		//	worldMat = scaleMat * slopeRot * rotMat * posMat;
		//	mLineShader->SetMatrixUniform("uWorld", worldMat);

		//	glBindVertexArray(mSquareVAO);
		//	glDrawElements(GL_LINES, 10, GL_UNSIGNED_INT, 0);
		//}
		//// LINE�������ꍇ
		//if (item->GetColliderType() == ColliderTypeEnum::Line)
		//{
		//	LineCollider* linecol;
		//	Line line;

		//	linecol = dynamic_cast<LineCollider*>(item);

		//	Vector3 scale;  // �`��X�P�[�����O�W��
		//	Vector3 pos;    // �`��ʒu
		//	line = linecol->GetLine();

		//	// �����x�N�g���Ɛ��K�����������x�N�g�����߂�
		//	Vector3 lineVec = line.mLineEnd - line.mLineStart;;
		//	Vector3 lineDir = lineVec;
		//	lineDir.Normalize();

		//	//����������X�P�[�����O�s��쐬
		//	float len = lineVec.Length();
		//	Matrix4 scaleMat = Matrix4::CreateScale(len, 0, 0);

		//	// ���������]���Ɖ�]�p�����߃N�I�[�^�j�I���쐬
		//	Vector3 rotAxis;
		//	rotAxis = Vector3::Cross(lineDir, Vector3(1, 0, 0));
		//	float rotAngle = -1.0f * acosf(Vector3::Dot(rotAxis, lineDir));

		//	// �N�I�[�^�j�I����������̕����ɉ�]����s����쐬
		//	Quaternion q(rotAxis, rotAngle);
		//	Matrix4 rotMat = Matrix4::CreateFromQuaternion(q);

		//	// ���s�ړ�����
		//	Matrix4 posMat = Matrix4::CreateTranslation(line.mLineStart);


		//	worldMat = scaleMat * rotMat * posMat;
		//	mLineShader->SetMatrixUniform("uWorld", worldMat);

		//	//�`��
		//	glBindVertexArray(mLineVAO);
		//	glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, 0);
		//}
	}
}

/*
@fn �Փ˂������Ƃ��m�肵���Ƃ��A�߂荞�݂�߂��֐�
@param _movableBox �ړ�����
@param _fixedBox �ړ����Ȃ�����
@param _calcFixVec �ړ����̂̕␳�����x�N�g��
*/
void CalcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox, Vector3& _calcFixVec)
{
	_calcFixVec = Vector3(0, 0, 0);
	float dx1 = _fixedBox.m_min.x - _movableBox.m_max.x;
	float dx2 = _fixedBox.m_max.x - _movableBox.m_min.x;
	float dy1 = _fixedBox.m_min.y - _movableBox.m_max.y;
	float dy2 = _fixedBox.m_max.y - _movableBox.m_min.y;
	float dz1 = _fixedBox.m_min.z - _movableBox.m_max.z;
	float dz2 = _fixedBox.m_max.z - _movableBox.m_min.z;

	// dx, dy, dz �ɂ� ���ꂼ��1,2�̂�����Βl�������������Z�b�g����
	float dx = (Math::Abs(dx1) < Math::Abs(dx2)) ? dx1 : dx2;
	float dy = (Math::Abs(dy1) < Math::Abs(dy2)) ? dy1 : dy2;
	float dz = (Math::Abs(dz1) < Math::Abs(dz2)) ? dz1 : dz2;

	// x, y, z�̂����ł��������������ňʒu�𒲐�
	if (Math::Abs(dx) <= Math::Abs(dy) && Math::Abs(dx) <= Math::Abs(dz))
	{
		_calcFixVec.x = dx;
	}
	else if (Math::Abs(dy) <= Math::Abs(dx) && Math::Abs(dy) <= Math::Abs(dz))
	{
		_calcFixVec.y = dy;
	}
	else
	{
		_calcFixVec.z = dz;
	}

}
