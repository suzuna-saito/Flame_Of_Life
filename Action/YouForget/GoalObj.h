#pragma once

/*
* �S�[���I�u�W�F�N�g�̏���
*/
class GoalObj :public GameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_pos">�|�W�V����</param>
	GoalObj(const Vector3 _pos);
	// �f�X�g���N�^
	~GoalObj() {};

	static bool mGoalFlag;	// �S�[���������ǂ��� true:����

private:
	/// <summary>
	/// �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
	/// </summary>
	/// <param name="_hitObject">Hit�����Ώۂ̃Q�[���I�u�W�F�N�g�̃A�h���X</param>
	void OnCollision(const GameObject& _hitObject)override;

	class BoxCollider* mSelfBoxCollider;	// �����蔻��(�l�p)
};