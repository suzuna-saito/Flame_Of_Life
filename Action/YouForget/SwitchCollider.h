/*
@brief	�v���v���Z�b�T
*/
#pragma once

class SwitchCollider :public GameObject
{
public:

	/*
	@fn		�R���X�g���N�^
	*/
	SwitchCollider(Switch* _owner, const ObjTag& _objectTag, const SceneBase::SceneType _sceneTag,const Switch::switchColor _switchColor);

	/*
	@fn	�f�X�g���N�^
	*/
	~SwitchCollider() {};

	/*
	@fn	�X�V
	*/
	void UpdateGameObject(float _deltaTime)override;

	// �X�C�b�`�ƘA�g���Ă��鏰�̐F
	static Ground::GroundColor mLinkageColor;

private:
	Ground::GroundColor mSwitchColor;

	//�X�C�b�`���S�̔���𐶐�
	BoxCollider* mSwitchBoxCollider;

	Switch* mOwner;

	/*
	@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�(��������p)
	@param	��������GameObject
	*/
	void OnCollision(const GameObject& _hitObject)override;

public://�Q�b�^�[�Z�b�^�[
};


