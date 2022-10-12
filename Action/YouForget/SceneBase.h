#pragma once

/*
* �V�[���̊��N���X
*/
class SceneBase
{
public:
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
        eLastResult,    // �Ō�̃��U���g
    };

    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="_nowScene">���݂̃V�[���^�C�v</param>
    SceneBase(const SceneType& _sceneType);
    // �f�X�g���N�^
    virtual ~SceneBase() {};

    /// <summary>
    /// ���͏���
    /// </summary>
    /// <param name="_inputState">���͏��</param>
    virtual void Input(const InputState& _state) {};

    /// <summary>
    /// �X�V����
    /// </summary>
    /// <returns>���̃V�[���̃^�C�v</returns>
    virtual SceneType update() = 0;

    static SceneType mIsSceneType;      // ���݂̃V�[���^�C�v
    static bool mClearEndFlag;	        // �G���h�̕���t���O(true:�N���A)

protected:
    class Fade* mFade;                  // �t�F�[�h�C���A�t�F�[�h�A�E�g
    class FullPicture* mFullPicture;    // 1920�~1080�T�C�Y�̉摜UI
    class MapCreate* mMapCreate;        // �}�b�v

    bool mGameSceneFlag;                // ���̃V�[���ɑJ�ڂ��邩(true:����)
    bool mReturnTitleFlag;              // �^�C�g���V�[���ɑJ�ڂ��邩(true:����)
};