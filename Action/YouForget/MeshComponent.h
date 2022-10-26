#pragma once

/*
* ���b�V���f�[�^�̊Ǘ��ƕ`����s��
*/
class MeshComponent : public Component
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_owner">�A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^</param>
	/// <param name="_skelton">�X�P���g���f�[�^��p���邩(�f�t�H��false(�p���Ȃ�))</param>
	MeshComponent(class GameObject* _owner, bool _skelton = false);

	// �f�X�g���N�^
	~MeshComponent();

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="_shadere">�g�p����V�F�[�_�[�N���X�̃|�C���^</param>
	virtual void Draw(class Shader* _shader);

protected:
	/// <summary>
	/// �e�N�X�`�����X�e�[�W���ƂɃZ�b�g
	/// </summary>
	/// <param name="_shader">�g�p����V�F�[�_�[�N���X�̃|�C���^</param>
	void SetTextureToShader(class Shader* _shader);

	class Mesh* mMesh;	// ���b�V���f�[�^�N���X�ւ̃|�C���^

	bool mVisible;		// �`������邩�ǂ���
	bool mSkeltonFlag;	// �X�P���g���f�[�^��p���邩

public: //�Q�b�^�[�Z�b�^�[
	// �`������邩�ǂ������擾 true:�`�悷��
	bool GetVisible() const { return mVisible; }

	// �X�P���g���f�[�^��p���邩�擾 true:�p���Ȃ�
	bool GetIsSkeltal()const { return mSkeltonFlag; }

	/// <summary>
	/// �`������邩�ǂ�����ݒ�
	/// </summary>
	/// <param name="_visible">�`�悷�邩�ǂ��� true:�`�悷��</param>
	void SetVisible(bool _visible) { mVisible = _visible; }
	
	/// <summary>
	/// ���b�V���R���|�[�l���g���g��Mesh�̐ݒ�
	/// </summary>
	/// <param name="_mesh">�ݒ肷��Mesh�N���X�̃|�C���^</param>
	void SetMesh(class Mesh* _mesh) { mMesh = _mesh; }
};