#pragma once

/*
* �I�u�W�F�N�g�̊ۉe�G�t�F�N�g
*/
class CircledShadow : public ParticleEffectBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_owner">�A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^</param>
	/// <param name="_color">�ۉe�̐F</param>
	CircledShadow(class GameObject* _owner, const Vector3 _color);
	// �f�X�g���N�^
	~CircledShadow() {};

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="_deltaTime">�Ō�̃t���[������������̂ɗv��������</param>
	void UpdateGameObject(float _deltaTime)override;

private:	
	const float MBaseZPos;		// �ۉe�̂��|�W�V����(���)
	const float MMaxScale;		// �ő�X�P�[���l
	const float MInitOwnerAlpha;// �A�^�b�`�����I�u�W�F�N�g�̌��X�̓����x
	const float MMaxAlpha;		// �ő僿�l
	const float MAddAlpha;		// ���l�̑����l
	const float MSubAlpha;		// ���l�̌����l
};