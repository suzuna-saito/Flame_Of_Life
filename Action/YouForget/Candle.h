#pragma once

/*
* �S�[���I�u�W�F�N�g�̏���
*/
class Candle :public GameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_pos">�|�W�V����</param>
	/// <param name="_size">�T�C�Y</param>
	/// <param name="_objectTag">���g�̃^�O</param>
	/// <param name="_sceneTag">���݂̃V�[���^�O</param>
	Candle(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::SceneType _sceneTag);
	// �f�X�g���N�^
	~Candle() {};

	/// <summary>
	/// �S�[���I�u�W�F�N�g�̍X�V����
	/// </summary>
	/// <param name="_deltaTime">�Ō�̃t���[������������̂ɗv��������</param>
	void UpdateGameObject(float _deltaTime)override;

	static bool mGoalFlag;          // �S�[���������ǂ���

private:
	MeshComponent* mMeshComponent;  //�Q�[���I�u�W�F�N�g�̃��b�V���|�C���^�ϐ�
	BoxCollider* mSelfBoxCollider;  // �����蔻��(�l�p)

	/// <summary>
	/// �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
	/// </summary>
	/// <param name="_hitObject">Hit�����Ώۂ̃Q�[���I�u�W�F�N�g�̃A�h���X</param>
	void OnCollision(const GameObject& _hitObject)override;

	bool mDrawFireFlag;    // �낤�����̉΂�`�悵�Ă��邩�ǂ���

public: // �Z�b�^�[�A�Q�b�^�[
};

