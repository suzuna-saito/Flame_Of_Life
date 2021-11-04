/*
@file	SkeletalMeshComponent.h
@brief	スケルトンデータの描画とアニメーション
*/

/*
@brief	インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_owner アタッチするゲームオブジェクトのポインタ
*/
SkeletalMeshComponent::SkeletalMeshComponent(GameObject* _owner)
	: MeshComponent(_owner, true)
	, mSkeleton(nullptr)
	, mAnimation(nullptr)
	, mColor(Vector3::Zero)
	, mAnimPlayRate(0.0f)
	, mAnimTime(0.0f)
{
}

/*
@fn		描画処理
@param	_shader 使用するシェーダークラスのポインタ
*/
void SkeletalMeshComponent::Draw(Shader* _shader)
{
	//親オブジェクトが未更新状態でないか
	if (mOwner->GetState() != State::Dead)
	{
		if (mMesh)
		{
			//ワールド変換をセット
			_shader->SetMatrixUniform("uWorldTransform",
				mOwner->GetWorldTransform());
			// 行列パレットをセット    
			_shader->SetMatrixUniforms("uMatrixPalette", &mPalette.mEntry[0],
				MAX_SKELETON_BONES);
			//スペキュラー強度をセット
			_shader->SetFloatUniform("uSpecPower", 100);

			// プレイヤーの色変更
			_shader->SetVectorUniform("uColor", Vector3(0.8f, 0.1f, 0.5f));
			//  テクスチャをセット 
			Texture* t = mMesh->GetTexture(mTextureIndex);
			if (t)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, t->GetTextureID());
				_shader->SetIntUniform("uMeshTexture", 0);
			}
			//メッシュの頂点配列をアクティブに
			VertexArray* va = mMesh->GetVertexArray();
			va->SetActive();
			//描画
			glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
		}
	}
}

/*
@fn		フレーム毎の処理
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void SkeletalMeshComponent::Update(float _deltaTime)
{
	if (mAnimation && mSkeleton)
	{
		mAnimTime += _deltaTime * mAnimPlayRate;
		//  アニメを巻き戻して再生
		while (mAnimTime > mAnimation->GetDuration())
		{
			mAnimTime -= mAnimation->GetDuration();
		}

		// 行列パレットの再計算
		ComputeMatrixPalette();
	}

}

/*
@fn		アニメーションの再生
@param	_anim アニメーションデータクラス
@param	_playRate アニメーションの再生速度
@return	アニメーションの残り時間
*/
float SkeletalMeshComponent::PlayAnimation(const Animation* _anim, float _playRate)
{
	mAnimation = _anim;
	mAnimTime = 0.0f;
	mAnimPlayRate = _playRate;

	if (!mAnimation)
	{
		return 0.0f;
	}

	ComputeMatrixPalette();

	return mAnimation->GetDuration();
}

/*
@fn 行列パレットの計算
*/
void SkeletalMeshComponent::ComputeMatrixPalette()
{
	// グローバル逆バインド行列配列の取得
	const std::vector<Matrix4>& globalInvBindPoses = mSkeleton->GetGlobalInvBindPoses();
	// 現在のポーズ行列
	std::vector<Matrix4> currentPoses;
	// アニメ時刻時点のグローバルポーズの取得
	mAnimation->GetGlobalPoseAtTime(currentPoses, mSkeleton, mAnimTime);
	// それぞれのボーンの行列パレットのセット                                    
	for (size_t i = 0; i < mSkeleton->GetNumBones(); i++)
	{
		//行列パレット[i] = グローバル逆バインド行列[i]　×　現在のポーズ行列[i]  (iはボーンID)         
		mPalette.mEntry[i] = globalInvBindPoses[i] * currentPoses[i];
	}
}
