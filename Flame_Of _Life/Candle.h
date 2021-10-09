/*
@brief	�v���v���Z�b�T
*/
#pragma once

class Candle :public GameObject
{
public:
	// �R���X�g���N�^
	Candle(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag);

	// �f�X�g���N�^
	~Candle() {};


private:
	//�Q�[���I�u�W�F�N�g�̃��b�V���|�C���^�ϐ�
	MeshComponent* mMeshComponent;

	// �l�p�̒n�ʂ̓����蔻��𐶐�
	BoxCollider* mSelfBoxCollider;

	// �낤�����̉΂������ǂ���
	bool mFireFlag;
	// �낤�����̉΂�`�悵�Ă��邩�ǂ���
	bool mDrawFireFlag;

public: // �Z�b�^�[�A�Q�b�^�[
	bool SetFireFlag(bool _flag) { mFireFlag = _flag; }
};

