/*
@brief	�v���v���Z�b�T
*/
#pragma once

struct InputState;

class BackGroundSprite;
class MapCreate;
class Sprite;
class Candle;

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

    // �V�[���̎��
    enum class SceneType :unsigned char
    {
        eInit,          // �������
        eTitle,         // �^�C�g��
        eTutorial,      // �`���[�g���A��
        eFirst,         // First�X�e�[�W
        eSecond,        // Second�X�e�[�W
        eThird,         // Third�X�e�[�W
        eFirstResult,   // First���U���g
        eSecondResult,  // Second���U���g
        eThirdResult,   // Third���U���g
        eGameClear,     // �Q�[���N���A
        eGameOver,      // �Q�[���I�[�o�[
    };

protected:

    //�w�i
    Sprite* mSprite;
    //�}�b�v����
    MapCreate* mMapCreate;

    // ���̃V�[���ɑJ�ڂ��邩
    bool mGameSceneFlag;

    // �^�C�g���V�[���ɑJ�ڂ��邩
    bool mReturnTitleFlag;

    //�Q�[���N���A������
    bool mClearFlag;

    //���̃V�[���ɑJ�ڂ��鎞�̑ҋ@����
    int mNextSceneCount;

    // �����摜�̃��l
    float mThisSpriteAlpha;
private:

    //���݂̃V�[��
    static SceneType mIsScene;

public://�Q�b�^�[�Z�b�^�[

    /*
    @return ���݂̃V�[��(int�^)
    */
    static SceneType GetScene() { return mIsScene; };

    /*
    @param _isScene ���݂̃V�[��
    */
    virtual void SetScene(SceneType _isScene) { mIsScene = _isScene; };
};