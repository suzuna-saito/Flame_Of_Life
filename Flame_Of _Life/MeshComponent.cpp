/*
@file	MeshComponent.h
@brief	���b�V���f�[�^�̊Ǘ��ƕ`����s��
*/

/*
@brief	�C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_owner �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^
@param _skelton �X�P���g���f�[�^��p���邩�B
@sa SkeletalMeshComponent.h
*/
MeshComponent::MeshComponent(GameObject* _owner, bool _skelton)
	: Component(_owner)
	, mMesh(nullptr)
	, mTextureIndex(0)
	, mVisible(true)
	, mSkeltonFlag(_skelton)
{
	//�����_���[�Ƀ|�C���^�[�𑗂�
	RENDERER->AddMeshComponent(this);
}

/*
@fn		�f�X�g���N�^
*/
MeshComponent::~MeshComponent()
{
	//�����_���[����|�C���^���폜����
	RENDERER->RemoveMeshComponent(this);
}

/*
@fn		�`�揈��
@param	_shader �g�p����V�F�[�_�[�N���X�̃|�C���^
*/
void MeshComponent::Draw(Shader* _shader)
{
	if (mOwner->GetState() != State::Dead)
	{
		if (mMesh)
		{
			// Set the world transform
			_shader->SetMatrixUniform("uWorldTransform",
				mOwner->GetWorldTransform());
			// Set specular power
			_shader->SetFloatUniform("uSpecPower", mMesh->GetSpecPower());

			// Set the active texture

			// ���b�V���ɒ�`����Ă���e�N�X�`�����Z�b�g
			SetTextureToShader(_shader);

			// Set the argMesh's vertex array as active
			VertexArray* va = mMesh->GetVertexArray();
			va->SetActive();
			// Draw
			glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
		}
	}
}

/*
@fn		�e�N�X�`�����X�e�[�W���ƂɃZ�b�g
@brief	�f�B�t���[�Y�}�b�v	stage00
		�@���}�b�v			stage01
		�X�y�L�����[�}�b�v	stage02
		���ȕ��˃}�b�v		stage03
@param	_shader �g�p����V�F�[�_�[�N���X�̃|�C���^
*/
void MeshComponent::SetTextureToShader(Shader* _shader)
{
	// ���b�V���e�N�X�`���Z�b�g
	int texID, stageCount = 0;
	texID = mMesh->GetTextureID(TextureStage::DiffuseMap); // �f�B�t���[�Y
	{
		glActiveTexture(GL_TEXTURE0 + stageCount);
		glBindTexture(GL_TEXTURE_2D, texID);
		_shader->SetIntUniform("uDiffuseMap", stageCount);
		stageCount++;
	}
	texID = mMesh->GetTextureID(TextureStage::NormalMap); // �@���}�b�v
	{
		glActiveTexture(GL_TEXTURE0 + stageCount);
		glBindTexture(GL_TEXTURE_2D, texID);
		_shader->SetIntUniform("uNormalMap", stageCount);
		stageCount++;
	}
	texID = mMesh->GetTextureID(TextureStage::SpecularMap); // �X�y�L�����[�}�b�v
	{
		glActiveTexture(GL_TEXTURE0 + stageCount);
		glBindTexture(GL_TEXTURE_2D, texID);
		_shader->SetIntUniform("uSpecularMap", stageCount);
		stageCount++;
	}
	texID = mMesh->GetTextureID(TextureStage::EmissiveMap); // ���ȕ��˃}�b�v
	{
		glActiveTexture(GL_TEXTURE0 + stageCount);
		glBindTexture(GL_TEXTURE_2D, texID);
		_shader->SetIntUniform("uEmissiveMap", stageCount);
		stageCount++;
	}
}
