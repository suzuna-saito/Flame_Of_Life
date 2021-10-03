/*
@brief	�v���v���Z�b�T
*/
#pragma once


class SandEffect :public ParticleEffectBase
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_pos ���ڂ���̍��W
	@param	_vel ���ڂ���̑��x
	@param	_objectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
	@param	_sceneTag �V�[���̃^�O
	*/
	SandEffect(Vector3 _pos, Vector3 _vel, SceneBase::Scene _sceneTag, const Tag& _objectTag);

	/*
	@fn	�f�X�g���N�^
	*/
	~SandEffect() {};

	/*
	@fn		���ڂ���̃A�b�v�f�[�g
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime)override;

private:
};

