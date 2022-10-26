/*
@file	Component.h
@brief	�S�ẴR���|�[�l���g�̊Ǘ����s��
*/

/*
@brief	�v���v���Z�b�T
*/
#pragma once


class GameObject;

class Component
{
public:
	/*
	@fn		�R���X�g���N�^
	@param	_owner �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^
	@param	_updateOrder �R���|�[�l���g�̍X�V���ԁi���l���������قǑ����X�V�����
	*/
	Component(GameObject* _owner, int _updateOrder = 100);

	/*
	@fn	�f�X�g���N�^
	*/
	virtual ~Component();

	/*
	@fn		�t���[�����̏���
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	virtual void Update(float _deltaTime) {};

	/*
	@fn		���͏���
	@param	_state InputState�\����
	*/
	virtual void ProcessInput(const struct InputState& _state) {}

	/*
	@fn	Transform�̃��[���h�ϊ�
	*/
	virtual void OnUpdateWorldTransform() {}

	/*
	@fn		�q�b�g�����I�u�W�F�N�g����ȏ゠�����ꍇ�A�ǂ̃I�u�W�F�N�g�Ɖ����߂������邩
			�^�O�Œ��ׂ���ɂ܂�Transform�̃��[���h�ϊ�������
	@detail �q�b�g�����I�u�W�F�N�g��̊Ԃɂ����ꍇ�A��������������A���蔲������̂�
			�����h�����߂ɂ�����xTransform�̃��[���h�ϊ�������
	*/
	virtual void Refresh() {}

protected:
	//�A�^�b�`���Ă���Q�[���I�u�W�F�N�g�̃|�C���^
	GameObject* mOwner;
	// �R���|�[�l���g�̍X�V���ԁi���l���������قǑ����X�V�����j
	int mUpdateOrder;

public: //�Q�b�^�[�Z�b�^�[

	/*
	@return �X�V����(int�^)
	*/
	int GetUpdateOder() { return mUpdateOrder; }

	/*
	@return �A�^�b�`���Ă���Q�[���I�u�W�F�N�g�ւ̃|�C���^(GameObject�^)
	*/
	GameObject* GetOwner() { return mOwner; }
};

