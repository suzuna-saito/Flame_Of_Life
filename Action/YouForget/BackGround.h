#pragma once

class BackGround :public GameObject
{
public:
	// �w�i�ɂ���΂߂��Ă��鏰�̎��
	enum class BackGroundType :unsigned char
	{
		eBGtypeOne,	// 1
		eBGtypeTwo,	// 2
	};

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_pos">�|�W�V����</param>
	/// <param name="_type">�w�i�ɂ���΂߂��Ă��鏰�̎��</param>
	BackGround(const Vector3 _pos, const BackGroundType _type);
	// �f�X�g���N�^
	~BackGround() {};

private:
	//�Q�[���I�u�W�F�N�g�̃��b�V���|�C���^�ϐ�
	class MeshComponent* mMeshComponent;
};