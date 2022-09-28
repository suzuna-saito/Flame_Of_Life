/*
@file	BoxCollider.h
@brief	�{�b�N�X�̓����蔻����s���R���|�[�l���g
*/

/*
@brief	�v���v���Z�b�T
*/
#pragma once

class BoxCollider final : public ColliderComponent
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_owner �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^
	@param	_tag �A�^�b�`����Q�[���I�u�W�F�N�g�̓����蔻��̃^�O
	@param	_func ���̃I�u�W�F�N�g�Ɠ����������ɌĂ΂��֐��|�C���^(GetOnCollisionFunc���Ă�)
	@param	_updateOrder �R���|�[�l���g�̍X�V���ԁi���l���������قǑ����X�V�����
	@param	_collisionOrder �����蔻�莞�ɁA�߂荞�݂��瓮���������̗D��x�����߂鐔�l
	*/
	BoxCollider(class GameObject* _owner, ColliderTag _tag, OnCollisionFunc _func, int _updateOrder = 200, int _collisionOrder = 100);

	/*
	@fn	�f�X�g���N�^
	*/
	virtual ~BoxCollider();

	/*
	@fn	Transform�̃��[���h�ϊ�
	*/
	void OnUpdateWorldTransform() override;

	/*
	@fn	�q�b�g�����I�u�W�F�N�g����ȏ゠�����ꍇ�A�ǂ̃I�u�W�F�N�g�Ɖ����߂������邩
			�^�O�Œ��ׂ���ɂ܂�Transform�̃��[���h�ϊ�������
	@brief �q�b�g�����I�u�W�F�N�g��̊Ԃɂ����ꍇ�A��������������A���蔲������̂�
			�����h�����߂ɂ�����xTransform�̃��[���h�ϊ�������
	*/
	void Refresh() override;

private:

	//�I�u�W�F�N�g�ɐݒ肷��p�̃{�b�N�X�i���S���I�u�W�F�N�g�̒��S�ɂ���j
	AABB mObjectBox;
	//�����蔻�肷��Ƃ��Ɏg���{�b�N�X�i���S�����[���h���W�̒��S�ɂ���j
	AABB mWorldBox;
	//��]�����邩
	bool mShouldRotate;

public: //�Q�b�^�[�Z�b�^�[

	/*
	@fn		�����蔻�莞�Ɏg�����[���h��Ԃł�AABB���擾����
	@return ���S�����[���h���W�ɍ��킹��AABB�̍\����(AABB�^)
	*/
	AABB GetWorldBox() const { return mWorldBox; }

	/*
	@fn		�����蔻��Ɏg��AABB�̐ݒ�
	@param	_box �I�u�W�F�N�g�̑傫���ɍ��킹��AABB�̍\����
	*/
	void SetObjectBox(const AABB& _box) { mObjectBox = _box; }
};