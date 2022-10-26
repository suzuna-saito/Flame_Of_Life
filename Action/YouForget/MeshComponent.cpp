#include "pch.h"

MeshComponent::MeshComponent(GameObject* _owner, bool _skelton)
	: Component(_owner)
	, mMesh(nullptr)
	, mVisible(true)
	, mSkeltonFlag(_skelton)
{
	// レンダラーにポインターを送る
	RENDERER->AddMeshComponent(this);
}

MeshComponent::~MeshComponent()
{
	// レンダラーからポインタを削除する
	RENDERER->RemoveMeshComponent(this);
}

void MeshComponent::Draw(Shader* _shader)
{
	// オブジェクトが更新終了状態じゃなければ
	if (mOwner->GetState() != State::Dead)
	{
		// uWorldTransformを設定
		_shader->SetMatrixUniform("uWorldTransform",
			mOwner->GetWorldTransform());
		// uSpecPowerを設定
		_shader->SetFloatUniform("uSpecPower", mMesh->GetSpecPower());

		// アタッチしたオブジェクトの値をセット
		_shader->SetFloatUniform("uAlpha", mOwner->GetAlpha());		// α値
		_shader->SetVectorUniform("uColor", mOwner->GetColor());	// 乗算色

		// メッシュに定義されているテクスチャをセット
		SetTextureToShader(_shader);

		// argMeshの頂点配列をactiveに設定
		VertexArray* va = mMesh->GetVertexArray();
		va->SetActive();
		// 描画
		glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
	}
}

// @@@
void MeshComponent::SetTextureToShader(Shader* _shader)
{
	// メッシュテクスチャセット
	int texID, stageCount = 0;
	texID = mMesh->GetTextureID(TextureStage::DiffuseMap); // ディフューズ
	{
		glActiveTexture(GL_TEXTURE0 + stageCount);
		glBindTexture(GL_TEXTURE_2D, texID);
		_shader->SetIntUniform("uDiffuseMap", stageCount);
		stageCount++;
	}
	texID = mMesh->GetTextureID(TextureStage::NormalMap); // 法線マップ
	{
		glActiveTexture(GL_TEXTURE0 + stageCount);
		glBindTexture(GL_TEXTURE_2D, texID);
		_shader->SetIntUniform("uNormalMap", stageCount);
		stageCount++;
	}
	texID = mMesh->GetTextureID(TextureStage::SpecularMap); // スペキュラーマップ
	{
		glActiveTexture(GL_TEXTURE0 + stageCount);
		glBindTexture(GL_TEXTURE_2D, texID);
		_shader->SetIntUniform("uSpecularMap", stageCount);
		stageCount++;
	}
	texID = mMesh->GetTextureID(TextureStage::EmissiveMap); // 自己放射マップ
	{
		glActiveTexture(GL_TEXTURE0 + stageCount);
		glBindTexture(GL_TEXTURE_2D, texID);
		_shader->SetIntUniform("uEmissiveMap", stageCount);
		stageCount++;
	}
}