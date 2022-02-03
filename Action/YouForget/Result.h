#pragma once

class Sprite;

class Result :public SceneBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_nowScene 現在のシーン
	*/
	Result(const Scene& _nowScene);

	/*
	@fn	デストラクタ
	*/
	~Result();

	/*
	@fn	タイトルシーン時に毎フレーム更新処理をする
	*/
	SceneBase* update() override;

	/*
	@fn	タイトルシーン時に毎フレーム入力処理をする
	*/
	void Input(const InputState& _inputState)override;

private:
	// マップで取得したアイテムと説明を関連付ける
	map<ItemNum, string> mItemDescription;

	// 描画する画像
	vector<string> mDescription;
	// 表示した画像をvectorに保存し、デストラクタでまとめて消す
	vector <Sprite*> mDeleteDescription;

	// 次の画像を表示するか
	bool mNextFlag;
	// 最後の画像を表示し終わったか
	bool mEndFlag;
	// 表示処理をするかどうか
	bool mDraw;

	// 出す画像のナンバー
	unsigned int mNum ;

	// 今表示している画像
	Sprite* mNowDescription;
	// 後ろの画像
	Sprite* mBackDescription;

	// どのアイテムを取っているか検索する
	void mSearch();
};
