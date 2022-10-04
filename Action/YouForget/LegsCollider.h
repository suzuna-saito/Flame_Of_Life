/*
@brief	�v���v���Z�b�T
*/
#pragma once

class LegsCollider :public GameObject
{
public:

	/*
	@fn		�R���X�g���N�^
	*/
	LegsCollider(Player* _owner, const Tag& _objectTag, const SceneBase::SceneType _sceneTag);

	/*
	@fn	�f�X�g���N�^
	*/
	~LegsCollider() {};

	/*
	@fn	�X�V
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	//�v���C���[�̑��������蔻��𐶐�
	BoxCollider* mLegsBoxCollider;

	Player* mOwner;
	/*
	@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�(��������p)
	@param	��������GameObject
	*/
	void OnCollision(const GameObject& _hitObject)override;


	// �ݒu����
	bool mIsGround;

public://�Q�b�^�[�Z�b�^�[

	/*
	@return	�n�ʂƂ̓����蔻��
	*/
	const bool GetIsGround() const { return mIsGround; }

	void SetIsGround(bool _groundFlag) { mIsGround = _groundFlag; }
};


