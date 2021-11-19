#pragma once

// �N���X�̑O���錾
class SpriteComponent;
class Texture;
class Font;

/*
@file CountUp.h
@brief �J�E���g�_�E���t�H���g�̕\�����s��
*/
class CountUp: public GameObject
{
public:

    /*
    @brief	�R���X�g���N�^
    @param	�J�E���g���鎞��
    @param	���݂̃V�[��
    */
    CountUp(SceneBase::Scene _sceneTag);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~CountUp();

    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;


private:
    // �J�E���g���J�n���邩�̃t���O�ϐ�
    static bool countStartFlag;

    // SpriteComponent�ϐ�
    SpriteComponent* sprite;
    // �t���[���J�E���g
    int frameCount;
    // �v�����鎞��
    int time;

    // ���Ԃ�1�i�߂�^�C�~���O���r����萔
    const int AddTimeCount;

public://�Q�b�^�[�Z�b�^�[

    /*
    @fn countStartFlag��setter�֐�
    @brief	countStartFlag�ɒl���Z�b�g
    @param	_countStartFlag �J�E���g���J�n���邩�̃t���O
    */
    static void SetCountStartFlag(bool _countStartFlag) { countStartFlag = _countStartFlag; }

    /*
    @fn countStartFlag��getter�֐�
    @brief	countStartFlag���擾
    @return	�J�E���g���J�n���邩�̃t���O
    */
    static bool GetCountStartFlag() { return countStartFlag; }

};