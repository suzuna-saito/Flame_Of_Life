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
        eGameClear,     // �Q�[���N���A
        eGameOver,      // �Q�[���I�[�o�[
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
    /// <returns>���̃V�[���̃|�C���^</returns>
    virtual SceneBase* update() = 0;

    static SceneType mIsScene;          // ���݂̃V�[���^�C�v

protected:
    class FullPicture* mFullPicture;    // 1920�~1080�T�C�Y�̉摜UI
    class MapCreate* mMapCreate;        // �}�b�v

    bool mGameSceneFlag;                // ���̃V�[���ɑJ�ڂ��邩(true:����)
    bool mReturnTitleFlag;              // �^�C�g���V�[���ɑJ�ڂ��邩(true:����)
};