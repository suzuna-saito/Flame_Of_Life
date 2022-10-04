#pragma once

/*
@brief �v���v���Z�b�T
*/
#pragma once

class FallEffect : public ParticleEffectBase
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_Pos �f�X�G�t�F�N�g�̐����ꏊ
	@param	_Vel �N���A�G�t�F�N�g�̑��x
	@param	_ObjectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
	@param	_SceneTag �V�[���̃^�O
	*/
	FallEffect(const Vector3 _Pos, const Vector3 _Vel, const Tag& _ObjectTag, const SceneBase::SceneType _SceneTag);

	/*
	@fn	�f�X�g���N�^
	*/
	~FallEffect() {};

	/*
	@fn		�f�X�G�t�F�N�g�̃A�b�v�f�[�g
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime)override;

private:
	//�A���t�@�l�̍팸�l
	const float MAlphaReductionVal;
	//�X�P�[���̒ǉ��l
	const float MScaleAddVal;
};

