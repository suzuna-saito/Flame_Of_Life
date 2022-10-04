#pragma once

/*
* UI関連の基底クラス
*/
class UIBase : public GameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_pos">UIの生成場所（スクリーン座標）</param>
	/// <param name="_uiFileName">画像へのアドレス</param>
	/// <param name="_sceneTag">生成した時のシーン</param>
	/// <param name="_objectTag">アタッチしたゲームオブジェクトのタグ</param>
	/// <param name="_scale">画像の拡大サイズ</param>
	UIBase(const Vector2& _pos, const string& _uiFileName, SceneBase::SceneType _sceneTypeTag, const Tag& _objectTag, const float& _scale = 1);
	// デストラクタ
	~UIBase() {};

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="_deltaTime">最後のフレームを完了するのに要した時間</param>
	void UpdateGameObject(float _deltaTime)override;

protected:
	//UIの描画クラス
	UIComponent* mUI;
};
