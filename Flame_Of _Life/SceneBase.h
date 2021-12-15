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
    enum class Scene:unsigned char
    {
        // ���̑�
        other,
        // �^�C�g��
        title,
        // �`���[�g���A��
        tutorial,
        // Easy�X�e�[�W
        easy,
        // Normal�X�e�[�W
        normal,
        // Hard�X�e�[�W
        hard,
        // ���U���g
        result,
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
    //���Ԃ�UI
    Time* mTime;

    // ���̃V�[���ɑJ�ڂ��邩
    bool mGameSceneFlag;

    //�Q�[���N���A������
    bool mClearFlag;

    //���̃V�[���ɑJ�ڂ��鎞�̑ҋ@����
    int mNextSceneCount;
private:

    //���݂̃V�[��
    static Scene mIsScene;

public://�Q�b�^�[�Z�b�^�[

    /*
    @return ���݂̃V�[��(int�^)
    */
    static Scene GetScene() { return mIsScene; };

    /*
    @param _isScene ���݂̃V�[��
    */
    virtual void SetScene(Scene _isScene) { mIsScene = _isScene; };
};