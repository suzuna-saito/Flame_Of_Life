#pragma once

/*
@brief �O���錾
*/
class ItemEffectManager;


// �A�C�e��
class Item :public ItemBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_pos">�|�W�V����</param>
	/// <param name="_size">�T�C�Y</param>
	/// <param name="_objectTag">���g�̃^�O</param>
	/// <param name="_sceneTag">���݂̃V�[��</param>
	/// <param name="_num">���ڂ̃A�C�e����</param>
	Item(const Vector3& _pos, const Vector3& _size, const CollisionTag& _objectTag, const SceneBase::SceneType _sceneTag, const int _num);

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

	// �A�C�e�����܂����݂��Ă��邩�̃t���O true _���݂��� false _���݂��Ȃ�
	bool mItemExistsFlag;

	// �A�C�e���̓����x�������邩�ǂ��� true _������ false _�����Ȃ�
	bool mAlphaDownFlag;
	// �A�C�e�����_�ł��n�߂鎞��
	int mItemFlashingTime;
	// �A�C�e���̂��ꂼ��̐�������
	int mItemExistsTime;

	int MItemExistsOneTime;
	int MItemExistsTwoTime;
	int MItemExistsThreeTime;

	/*
	@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
	@param	��������GameObject
	*/
	void OnCollision(const GameObject& _hitObject)override;

	// �A�C�e���̎�ނ�����
	void mItemType(int _num);

	// �A�C�e���̐������Ԃ̏���
	void mItemExists();

	// �Q�b�^�[�A�Z�b�^�[
public:
	// �A�C�e�������݂��Ă邩�ǂ�����������
	bool mGetItemExistsFlag() { return mItemExistsFlag; }
};

