/*
@file	SphereCollider.h
@brief	���̓����蔻����s���R���|�[�l���g
*/

/*
@brief	�v���v���Z�b�T
*/
#pragma once


class SphereCollider final : public ColliderComponent
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_owner �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^
	@param	_tag �A�^�b�`����Q�[���I�u�W�F�N�g�̓����蔻��̃^�O
	@param	_func ���̃I�u�W�F�N�g�Ɠ����������ɌĂ΂��֐��|�C���^(GetOnCollisionFunc���Ă�)
	@param	_updateOrder �R���|�[�l���g�̍X�V���ԁi���l���������قǑ����X�V�����j
	@param	_collisionOrder �����蔻�莞�ɁA�߂荞�݂��瓮���������̗D��x�����߂鐔�l
	*/
	SphereCollider(GameObject* _owner, GameObject::ObjTag _tag, OnCollisionFunc _func, int _updateOrder = 200, int _collisionOrder = 100);

	/*
	@fn	�f�X�g���N�^
	*/
	virtual ~SphereCollider();

	/*
	@fn	Transform�̃��[���h�ϊ�
	*/
	void OnUpdateWorldTransform() override;

	/*
	@fn		�q�b�g�����I�u�W�F�N�g����ȏ゠�����ꍇ�A�ǂ̃I�u�W�F�N�g�Ɖ����߂������邩
			�^�O�Œ��ׂ���ɂ܂�Transform�̃��[���h�ϊ�������
	@detail �q�b�g�����I�u�W�F�N�g��̊Ԃɂ����ꍇ�A��������������A���蔲������̂�
			�����h�����߂ɂ�����xTransform�̃��[���h�ϊ�������
	*/
	void Refresh() override;

private:

	//�I�u�W�F�N�g�ɐݒ肷��p�̋��i���S���I�u�W�F�N�g�̒��S�ɂ���j
	Sphere mObjectSphere;
	//�����蔻�肷��Ƃ��Ɏg�����i���S�����[���h���W�̒��S�ɂ���j
	Sphere mWorldSphere;

public: //�Q�b�^�[�Z�b�^�[

	/*
	@fn		�����蔻�莞�Ɏg�����[���h��Ԃł�Sphere���擾����
	@return ���S�����[���h���W�ɍ��킹��Sphere�̍\����(Sphere�^)
	*/
	Sphere GetWorldSphere() const { return mWorldSphere; }

	/*
	@fn		�����蔻��Ɏg��Sphere�̐ݒ�
	@param	_sphere �I�u�W�F�N�g�̑傫���ɍ��킹��Sphere�̍\����
	*/
	void SetObjectSphere(const Sphere& _sphere) { mObjectSphere = _sphere; }
};

