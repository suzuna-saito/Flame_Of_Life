/*
@file	SkeletalMeshComponent.h
@brief	スケルトンデータの描画とアニメーション
*/

/*
@brief	プリプロセッサ
*/
#pragma once


class SkeletalMeshComponent : public MeshComponent
{
public:
	/*
	@fn		コンストラクタ
	@param	_owner アタッチするゲームオブジェクトのポインタ
	*/
	SkeletalMeshComponent(class GameObject* _owner);

	/*
	@fn		フレーム毎の処理
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void Update(float _deltaTime) override;

	/*
	@fn		描画処理
	@param	_shader 使用するシェーダークラスのポインタ
	*/
	void Draw(class Shader* _shader) override;

	/*
	@fn		アニメーションの再生
	@param	_anim アニメーションデータクラス
	@param	_playRate アニメーションの再生速度
	@return	アニメーションの残り時間(float型)
	*/
	float PlayAnimation(const class Animation* _anim, float _playRate = 1.0f);
protected:
	/*
	@fn 行列パレットの計算
	*/
	void ComputeMatrixPalette();

	// 行列パレット
	MatrixPalette mPalette;
	// スケルトンデータ
	const class Skeleton* mSkeleton;
	// アニメーションデータ
	const class Animation* mAnimation;
	// アニメーションの再生速度
	float mAnimPlayRate;
	// アニメーション時間
	float mAnimTime;
	//スケルトンデータに乗算する色
	Vector3 mColor;
	
private:
	//テクスチャサイズ
	size_t mTextureIndex;

public://ゲッターセッター
	/*
	@param _skeleton スケルトンデータ
	*/
	void SetSkeleton(const class Skeleton* _skeleton) { mSkeleton = _skeleton; }
	/*
	@param _color スケルトンデータに乗算する色
	*/
	void SetColor(const Vector3& _color) { mColor = _color; }
};
