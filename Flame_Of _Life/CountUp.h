#pragma once
/*
@brief �J�E���g�A�b�v�̕\��
*/
class CountUp :public GameObject
{
public:
	/*
	@brief �R���X�g���N�^
	*/
	CountUp(const SceneBase::Scene _sceneTag);

	/*
	@brief �f�X�g���N�^
	*/
	~CountUp();

	/*
	@brief �X�V�������s��
	*/
	void UpdateGameObject(float _deltaTime)override;

private:
	// SpriteComponent�ϐ�
	SpriteComponent* sprite;

	// �v�����鎞��
	int time;
};

