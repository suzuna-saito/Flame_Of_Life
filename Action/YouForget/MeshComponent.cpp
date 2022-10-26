#include "pch.h"

MeshComponent::MeshComponent(GameObject* _owner, bool _skelton)
	: Component(_owner)
	, mMesh(nullptr)
	, mVisible(true)
	, mSkeltonFlag(_skelton)
{
	// �����_���[�Ƀ|�C���^�[�𑗂�
	RENDERER->AddMeshComponent(this);
}

MeshComponent::~MeshComponent()
{
	// �����_���[����|�C���^���폜����
	RENDERER->RemoveMeshComponent(this);
}

void MeshComponent::Draw(Shader* _shader)
{
	// �I�u�W�F�N�g���X�V�I����Ԃ���Ȃ����
	if (mOwner->GetState() != State::Dead)
	{
		// uWorldTransform��ݒ�
		_shader->SetMatrixUniform("uWorldTransform",
			mOwner->GetWorldTransform());
		// uSpecPower��ݒ�
		_shader->SetFloatUniform("uSpecPower", mMesh->GetSpecPower());

		// �A�^�b�`�����I�u�W�F�N�g�̒l���Z�b�g
		_shader->SetFloatUniform("uAlpha", mOwner->GetAlpha());		// ���l
		_shader->SetVectorUniform("uColor", mOwner->GetColor());	// ��Z�F

		// ���b�V���ɒ�`����Ă���e�N�X�`�����Z�b�g
		SetTextureToShader(_shader);

		// argMesh�̒��_�z���active�ɐݒ�
		VertexArray* va = mMesh->GetVertexArray();
		va->SetActive();
		// �`��
		glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
	}
}

// @@@
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