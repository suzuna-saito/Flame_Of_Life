#pragma once

class ItemBase;

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
	map<itemNames, const char*> mItemDescription;

	// 描画する説明
	vector<const char*> mDescription;

	// イテレーター
	decltype(mItemDescription)::iterator it;

	bool mFirstFlag;

	//vector<itemNames> test;
};
