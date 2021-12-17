/*
�v���v���Z�b�T
*/
#pragma once

class MeshComponent;
class SamplePlayer;

class FireObject :public GameObject
{
public:

	// �R���X�g���N�^
	FireObject(Candle* _owner, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag);

	/*
	@fn	�f�X�g���N�^
	*/
	~FireObject() {};

	// �X�V
	void UpdateGameObject(float _deltaTime)override;

private:

	//�Q�[���I�u�W�F�N�g�̃��b�V���|�C���^�ϐ�
	MeshComponent* mMeshComponent;

	Candle* mOwner;

	const float MAddPos;
public://�Q�b�^�[�Z�b�^�[

};

