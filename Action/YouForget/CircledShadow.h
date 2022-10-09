#pragma once

/*
* �I�u�W�F�N�g�̊ۉe�G�t�F�N�g
*/
class CircledShadow : public ParticleEffectBase
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_Pos �e�G�t�F�N�g�̐����ꏊ
	@param	_Vel �e�G�t�F�N�g�̑��x
	@param	_ObjectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
	@param	_SceneTag �V�[���̃^�O
	*/
	CircledShadow(class GameObject* _owner);

	/*
	@fn	�f�X�g���N�^
	*/
	~CircledShadow() {};

	/*
	@fn		�e�G�t�F�N�g�̃A�b�v�f�[�g
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime)override;

private:
	class GameObject* mOwner;	// �A�^�b�`�����I�u�W�F�N�g�̃|�C���^
	
	const float MBaseZPos;		// �ۉe�̂��|�W�V����(���)
	const float MMaxScale;		// �ő�X�P�[���l
};

