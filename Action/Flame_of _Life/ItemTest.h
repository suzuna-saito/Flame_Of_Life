#pragma once

// �A�C�e��
class ItemTest :public ItemBase
{
public:
	// �R���X�g���N�^
	ItemTest(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag, const int _num);

	/*
	@fn	�f�X�g���N�^
	*/
	~ItemTest() {};

	// �X�V
	void UpdateGameObject(float _deltaTime)override;

private:
	// �A�C�e���i���o�[
	const int ItemNumber;

	/*
	@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
	@param	��������GameObject
	*/
	void OnCollision(const GameObject& _hitObject)override;

	// �A�C�e���̎�ނ�����
	void mItemType();

};

