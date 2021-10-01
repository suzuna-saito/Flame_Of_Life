/*
@brief	�v���v���Z�b�T
*/
#pragma once

struct InputState;

class BackGroundSprite;
class MapCreate;
//class SamplePlayer;
//class Ground;

class SceneBase
{
public:

    /*
    @fn	�R���X�g���N�^
    */
    SceneBase() {};

    /*
    @fn	�f�X�g���N�^
    */
    virtual ~SceneBase() {};

    /*
    @fn	���݂̃V�[�����ɖ��t���[���X�V����������
    */
    virtual SceneBase* update() = 0;

    /*
    @fn	���݂̃V�[�����ɖ��t���[�����͏���������
    */
    virtual void Input(const InputState& state) {};

    /*
    @enum �V�[���̎��
    */
    enum Scene
    {
        // �^�C�g��
        title,
        // �`���[�g���A��
        tutorial,
        // �X�e�[�W1
        stage01,
        // �Q�[���N���A
        gameClear,
        // �Q�[���I�[�o�[
        gameOver,
        // �R���e�B�j���[ 
        Continue
    };

protected:

    //�w�i
    BackGroundSprite* mSprite;
    //�}�b�v����
    MapCreate* mMapCreate;
    ////�v���C���[�̃|�C���^
    //SamplePlayer* mPlayer;
    //// �����ɍ�������̃|�C���^
    //Ground* mGround;

    //�Q�[���N���A������
    bool mClearFlag;
    //���̃V�[���ɑJ�ڂ��鎞�̑ҋ@����
    int mNextSceneCount;

private:

    //���݂̃V�[��
    static int   mIsScene;

public://�Q�b�^�[�Z�b�^�[

    /*
    @return ���݂̃V�[��(int�^)
    */
    static int  GetScene() { return mIsScene; };

    /*
    @param _isScene ���݂̃V�[��
    */
    virtual void SetScene(int _isScene) { mIsScene = _isScene; };
};