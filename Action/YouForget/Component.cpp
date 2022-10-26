/*
@file	Component.h
@brief	�S�ẴR���|�[�l���g�̊Ǘ����s��
*/

/*
@brief	�C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_owner �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^
@param	_updateOrder �R���|�[�l���g�̍X�V���ԁi���l���������قǑ����X�V�����
*/
Component::Component(GameObject* _owner, int _updateOrder)
	: mOwner(_owner)
	, mUpdateOrder(_updateOrder)
{
	mOwner->AddComponent(this);
}

/*
@fn	�f�X�g���N�^
*/
Component::~Component()
{
	mOwner->RemoveComponent(this);
}