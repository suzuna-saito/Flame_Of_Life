/*
@brief	�v���v���Z�b�T
*/
#pragma once

class Ground :public GameObject
{
public:
	// �R���X�g���N�^
	Ground(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag);

	// �f�X�g���N�^
	~Ground() {};

private:
	//�Q�[���I�u�W�F�N�g�̃��b�V���|�C���^�ϐ�
	MeshComponent* mMeshComponent;

	// �l�p�̒n�ʂ̓����蔻��𐶐�
	BoxCollider* mSelfBoxCollider;
};

