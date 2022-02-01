#pragma once

// �N���X�̑O���錾
class SpriteComponent;

/*
@file CountUp.h
@brief �J�E���g�_�E���t�H���g�̕\�����s��
*/
class ItemCount : public GameObject
{
public:

    /*
    @brief	�R���X�g���N�^
    @param	�J�E���g���鎞��
    @param	���݂̃V�[��
    */
    ItemCount(SceneBase::Scene _sceneTag);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~ItemCount();

    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;


private:
    // SpriteComponent�ϐ�
    SpriteComponent* sprite;

    // �\��������|�W�V����
    const Vector3 MPosition;

public://�Q�b�^�[�Z�b�^�[
};