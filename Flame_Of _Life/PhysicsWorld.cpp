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

}

void PhysicsWorld::HitCheck(SphereCollider* _sphere)
{
	//�R���C�_�[�̐e�I�u�W�F�N�g��Active����Ȃ���ΏI������
	if (_sphere->GetOwner()->GetState() != State::Active)
	{
		return;
	}

	//�v���C���[�������Ɠ���������
	if (_sphere->GetTag() == ColliderTag::playerTag)
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

	//for (auto itr : mSpheres)
	//{
	//	if (itr == _sphere)
	//	{
	//		continue;
	//	}
	//	//�R���C�_�[�̐e�I�u�W�F�N�g��Active����Ȃ���ΏI������
	//	if (itr->GetOwner()->GetState() != State::Active)
	//	{
	//		continue;
	//	}
	//	bool hit = Intersect(itr->GetWorldSphere(), _sphere->GetWorldSphere());
	//	if (hit)
	//	{
	//		OnCollisionFunc func = mCollisionFunction.at(_sphere);
	//		func(*(itr->GetOwner()));
	//		func = mCollisionFunction.at(itr);
	//		func(*(_sphere->GetOwner()));
	//		/*_sphere->Refresh();*/
	//	}
	//}
	//for (auto itr : mBoxes)
	//{
	//	//�R���C�_�[�̐e�I�u�W�F�N�g��Active����Ȃ���ΏI������
	//	if (itr->GetOwner()->GetState() != State::Active)
	//	{
	//		continue;
	//	}
	//	bool hit = Intersect(_sphere->GetWorldSphere(),itr->GetWorldBox());
	//	if (hit)
	//	{
	//		OnCollisionFunc func = mCollisionFunction.at(_sphere);
	//		func(*(itr->GetOwner()));
	//		func = mCollisionFunction.at(itr);
	//		func(*(_sphere->GetOwner()));
	//		/*_sphere->Refresh();*/
	//	}
	//}
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

void PhysicsWorld::SphereAndSphere()
{
	for (size_t i = 0; i < mSpheres.size(); i++)
	{
		if (mSpheres[i]->GetOwner()->GetState() != Active)
		{
			continue;
		}
		for (size_t j = i + 1; j < mSpheres.size(); j++)
		{
			if (mSpheres[j]->GetOwner()->GetState() != Active)
			{
				continue;
			}
			bool hit = Intersect(mSpheres[i]->GetWorldSphere(), mSpheres[j]->GetWorldSphere());

			if (hit)
			{
				SphereCollider* sphereA = mSpheres[i];
				SphereCollider* sphereB = mSpheres[j];

				//sphereA->GetOwner()->OnCollision(*(sphereB->GetOwner()));
				//sphereB->GetOwner()->OnCollision(*(sphereA->GetOwner()));
			}
		}
	}
}

void PhysicsWorld::BoxAndBox()
{
	for (size_t i = 0; i < mBoxes.size(); i++)
	{
		if (mBoxes[i]->GetOwner()->GetState() != Active)
		{
			continue;
		}
		for (size_t j = i + 1; j < mBoxes.size(); j++)
		{
			if (mBoxes[j]->GetOwner()->GetState() != Active)
			{
				continue;
			}
			bool hit = Intersect(mBoxes[i]->GetWorldBox(), mBoxes[j]->GetWorldBox());

			if (hit)
			{
				BoxCollider* boxA = mBoxes[i];
				BoxCollider* boxB = mBoxes[j];

				//boxA->GetOwner()->OnCollision(*(boxB->GetOwner()));
				//boxB->GetOwner()->OnCollision(*(boxA->GetOwner()));
			}
		}
	}
}

void PhysicsWorld::SphereAndBox()
{
	for (size_t i = 0; i < mSpheres.size(); i++)
	{
		if (mSpheres[i]->GetOwner()->GetState() != Active)
		{
			continue;
		}
		for (size_t j = 0; j < mBoxes.size(); j++)
		{
			if (mBoxes[j]->GetOwner()->GetState() != Active)
			{
				continue;
			}
			bool hit = Intersect(mSpheres[i]->GetWorldSphere(), mBoxes[j]->GetWorldBox());

			if (hit)
			{
				//spheres[i]->GetOwner()->OnCollision(*(boxes[j]->GetOwner()));
				//boxes[j]->GetOwner()->OnCollision(*(spheres[i]->GetOwner()));
			}
		}
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
