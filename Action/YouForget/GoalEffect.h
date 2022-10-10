#pragma once

/*
* �S�[���ꏊ�ɕ`�悷��G�t�F�N�g
*/
class GoalEffect : public ParticleEffectBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_owner">�A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^</param>
	GoalEffect(class GameObject* _owner);
	// �f�X�g���N�^
	~GoalEffect() {};

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="_deltaTime">�Ō�̃t���[������������̂ɗv��������</param>
	void UpdateGameObject(float _deltaTime)override;

private:
	const float MAddAngleY;	// ��]�l�̑����l
	const float MMInAlpha;	// ���l�̍Œ�l
	float mAddScale;		// �X�P�[���̒ǉ��l
	float mAddAlpha;		// �A���t�@�l�̌����l
};