#pragma once

/*
* �I�u�W�F�N�g�����������ɕ`�悷��G�t�F�N�g
*/
class FallEffect : public ParticleEffectBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_owner">�A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^</param>
	FallEffect(class GameObject* _owner);
	// �f�X�g���N�^
	~FallEffect() {};

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="_deltaTime">�Ō�̃t���[������������̂ɗv��������</param>
	void UpdateGameObject(float _deltaTime)override;

private:
	const float MBaseScale;	// �X�P�[���l(���)
	const float MAddScale;	// �X�P�[���̒ǉ��l
	const float MSubAlpha;	// �A���t�@�l�̌����l

	bool mTmpVisible;		// �X�V�����̍Ō�ɕ`�悵�Ă������ǂ�����ۑ�
};