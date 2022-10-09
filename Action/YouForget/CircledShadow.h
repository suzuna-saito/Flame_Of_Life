#pragma once

/*
* オブジェクトの丸影エフェクト
*/
class CircledShadow : public ParticleEffectBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_Pos 影エフェクトの生成場所
	@param	_Vel 影エフェクトの速度
	@param	_ObjectTag アタッチしたゲームオブジェクトのタグ
	@param	_SceneTag シーンのタグ
	*/
	CircledShadow(class GameObject* _owner);

	/*
	@fn	デストラクタ
	*/
	~CircledShadow() {};

	/*
	@fn		影エフェクトのアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:
	class GameObject* mOwner;	// アタッチしたオブジェクトのポインタ
	
	const float MBaseZPos;		// 丸影のｚポジション(基盤)
	const float MMaxScale;		// 最大スケール値
};

