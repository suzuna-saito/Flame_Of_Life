#pragma once

class Time :public UIBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_pos プレイヤーの体力UIの生成場所(スクリーン座標)
	@param	_objectTag アタッチしたゲームオブジェクトのタグ
	@param	_sceneTag シーンのタグ
	*/
	Time(const Vector2& _pos, const Tag& _objectTag, SceneBase::Scene _sceneTag);

	/*
	@fn	デストラクタ
	*/
	~Time() {};

	/*
	@fn		プレイヤーの体力UIのアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

};