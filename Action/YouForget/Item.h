#pragma once

/*
@brief �O���錾
*/
class ItemEffectManager;


// �A�C�e��
class Item :public ItemBase
{
public:
	// �R���X�g���N�^
	Item(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag, const int _num);

	/*
	@fn	�f�X�g���N�^
	*/
	~Item() {};

	// �X�V
	void UpdateGameObject(float _deltaTime)override;

private:
	// �G�t�F�N�g
	// �A�C�e���̌��̃G�t�F�N�g
	ItemEffectManager* mItemEffectManager;


	// �A�C�e���i���o�[
	const int ItemNumber;


	/*
	@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
	@param	��������GameObject
	*/
	void OnCollision(const GameObject& _hitObject)override;

	// �A�C�e���̎�ނ�����
	void mItemType();

	// �Q�b�^�[�A�Z�b�^�[
public:
	// �A�C�e�����擾�������ǂ�����������
	bool mGetItemFlag() { return mCollisionFlag; }
};

