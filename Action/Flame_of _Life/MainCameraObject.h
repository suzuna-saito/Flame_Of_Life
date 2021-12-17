/*
@file MainCameraObject.h
@brief ���C���J�����BGameObject�̐ÓI�I�u�W�F�N�g �J�����ƏՓ˂��Ă��Ȃ��I�u�W�F�N�g�͍X�V���ꎞ�I�ɒ�~����
*/

/*
@brief	�v���v���Z�b�T
*/
#pragma once


class MainCameraObject :public GameObject
{
public:

	/*
	@fn	�R���X�g���N�^
	*/
	MainCameraObject();

	/*
	@fn	�f�X�g���N�^
	*/
	~MainCameraObject();

	/*
	@fn		���̃N���X�̓|�[�Y���ɕʃN���X����X�V�֐����Ă΂�邱�Ƃ�����
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime = 1.0f)override;

private:

	//�e�I�u�W�F�N�g�Ƃ̍�
	Vector3 mOffsetPos;
	//�Ǐ]��̃I�u�W�F�N�g���W
	Vector3 mLerpObject;
	//�Ǐ]��̃I�u�W�F�N�g���������Ă��邩
	bool mHasParentObject;

public://�Q�b�^�[�Z�b�^�[

	/*
	@param _offset ���������W�Ƃ̍�
	@param _parentPos ������W
	*/
	void SetViewMatrixLerpObject(const Vector3& _offset, const Vector3& _parentPos);

};

