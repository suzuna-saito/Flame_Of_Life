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
	map<itemNames, string> mItemDescription;

	// 描画する説明
	vector<string> mDescription;

	// 一回だけしてほしい処理
	bool mFirstFlag;
	bool mDraw;
	bool mBackDraw;

	// いったん仮
	int mCount;
	int mNum;

	Sprite* mNowDescription;
	Sprite* mBackDescription;
	//vector<itemNames> test;
};
