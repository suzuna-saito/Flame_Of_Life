#pragma once

// �L�̃I�u�W�F�N�g
class ItemCat :public ItemBase
{
public:
	// �R���X�g���N�^
	ItemCat(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag);

	/*
	@fn	�f�X�g���N�^
	*/
	~ItemCat() {};

	// �X�V
	void UpdateGameObject(float _deltaTime)override;

private:

	/*
	@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
	@param	��������GameObject
	*/
	void OnCollision(const GameObject& _hitObject)override;
};

