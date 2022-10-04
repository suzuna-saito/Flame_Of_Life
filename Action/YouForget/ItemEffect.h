#pragma once

/*
@brief �v���v���Z�b�T
*/
#pragma once

/*
@brief �O���錾
*/
class Item;

class ItemEffect : public ParticleEffectBase
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_Pos �A�C�e���G�t�F�N�g�̐����ꏊ
	@param	_Vel �A�C�e���G�t�F�N�g�̑��x
	@param	_ObjectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
	@param	_SceneTag �V�[���̃^�O
	*/
	ItemEffect(const Vector3 _Pos, const Vector3 _Vel, const Tag& _ObjectTag, const SceneBase::SceneType _SceneTag, Item* _ItemPtr);

	/*
	@fn	�f�X�g���N�^
	*/
	~ItemEffect() {};

	/*
	@fn		�A�C�e���G�t�F�N�g�̃A�b�v�f�[�g
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime)override;

	bool mItemVisible;
	
	//�A�C�e���̃|�C���^
	Item* mItem;

public:
	void SetItemEffectPos(Vector3 _pos) { mPosition = _pos; }

	bool GetItemVisible() { return mItemVisible; }
};

