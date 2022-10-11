#pragma once

/*
* パズルの基盤、ピースを描画するクラス
*/
class PuzzleUI : public UIBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_fileName">画像ファイルの名前</param>
	PuzzleUI(const string _fileName,const UIType _type);
	// デストラクタ
	~PuzzleUI() {};

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="_deltaTime">最後のフレームを完了するのに要した時間</param>
	void UpdateGameObject(float _deltaTime)override;

private:
	UIType mType;	// ピースか基盤か判別用
};