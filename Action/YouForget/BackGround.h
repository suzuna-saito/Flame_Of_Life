/*
@brief	�v���v���Z�b�T
*/
#pragma once

class BackGround :public GameObject
{
public:
	/*
	@fn		�R���X�g���N�^
	@param	_pos �|�W�V����
	@param	_size �T�C�Y
	@param	_objectTag �I�u�W�F�N�g�̃^�O
	@param	_sceneTag �V�[���^�O
	*/
	BackGround(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::SceneType _sceneTag, const int _type);

	// �f�X�g���N�^
	~BackGround() {};

	/*
	@fn		���̃A�b�v�f�[�g
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	//void UpdateGameObject(float _deltaTime)override;

private:
	//�Q�[���I�u�W�F�N�g�̃��b�V���|�C���^�ϐ�
	MeshComponent* mMeshComponent;

	const int mType;

};

