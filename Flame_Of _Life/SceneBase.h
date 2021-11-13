/*
@brief	�v���v���Z�b�T
*/
#pragma once

struct InputState;

class BackGroundSprite;
class MapCreate;
class Sprite;
class Candle;
class Time;

class SceneBase
{
public:

    /*
    @fn	�R���X�g���N�^
    */
    SceneBase();

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
        // ���̑�
        other,
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
    Sprite* mSprite;
    //�}�b�v����
    MapCreate* mMapCreate;
    // �낤�����̐���
    Candle* mCandle;
    //���Ԃ�UI
    Time* mTime;

    // ���̃V�[���ɑJ�ڂ��邩
    bool mGameSceneFlag;

    //���̃V�[���ɑJ�ڂ��鎞�̑ҋ@����
    int mNextSceneCount;

    //�Q�[���N���A������
    bool mClearFlag;
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