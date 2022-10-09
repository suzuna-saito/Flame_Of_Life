/*
@brief �v���v���Z�b�T
*/
#pragma once

/*
@brief �O���錾
*/
class CircledShadow;

class CircledShadowManager : public GameObject
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_ObjectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
	@param	_SceneTag �V�[���̃^�O
	@param _ItemPtr �v���C���[�̃|�C���^
	*/
	CircledShadowManager(const Tag& _ObjectTag, const SceneBase::SceneType _SceneTag, Player* _PlayerPtr);

	/*
	@fn	�f�X�g���N�^
	*/
	~CircledShadowManager() {};

	/*
	@fn		�G�t�F�N�g�}�l�[�W���[�̃A�b�v�f�[�g
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime)override;

private:
	//�Q�[���I�u�W�F�N�g�N���X�̃|�C���^
	GameObject* mOwner;
	//�p�[�e�B�N���̏��
	ParticleEffectBase::ParticleState mState;
	//�V�[���̃^�O
	SceneBase::SceneType mSceneTag;
	//�A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
	Tag				 mTag;
	//�v���C���[�̉e�G�t�F�N�g
	CircledShadow* mCircledShadowEffect;
	//�A�C�e���̃|�C���^
	Player* mPlayer;
	//�p�x
	float			 mAngle;
};

