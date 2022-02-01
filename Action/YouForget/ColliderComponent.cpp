/*
@file	ColliderComponent.h
@brief	�����蔻����s���R���|�[�l���g�̋K��N���X
*/

/*
@brief	�C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_owner �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^
@param	_tag �A�^�b�`����Q�[���I�u�W�F�N�g�̓����蔻��̃^�O
@param	_updateOrder �R���|�[�l���g�̍X�V���ԁi���l���������قǑ����X�V�����j
@param  _collisionOrder �����蔻�莞�ɁA�߂荞�݂��瓮���������̗D��x�����߂鐔�l
*/
ColliderComponent::ColliderComponent(GameObject* _owner, ColliderTag _tag, int _updateOrder, int _collisionOrder)
	: Component(_owner, _updateOrder)
	, mTriggerFlag(false)
	, mCollisionOrder(_collisionOrder)
	, mTag(_tag)
{
}

ColliderTag& operator++(ColliderTag& rhs)
{
	if (rhs == ColliderTag::end)
	{
		throw std::out_of_range("for outof range Tag& operator ++ (Tag&)");
	}
	rhs = ColliderTag(static_cast<std::underlying_type<ColliderTag>::type>(rhs) + 1);

	return rhs;
}
