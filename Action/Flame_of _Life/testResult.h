#pragma once

class Sprite;

class testResult :public SceneBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_nowScene 現在のシーン
	*/
	testResult(const Scene& _nowScene);

	/*
	@fn	デストラクタ
	*/
	~testResult();

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

	// 次の説明を表示するか
	bool mNextFlag;
	// 最後の説明を表示し終わったか
	bool mEndFlag;
	// 一回だけしてほしい処理
	bool mDraw;

	// 出す説明のナンバー
	int mNum;

	Sprite* mNowDescription;

	vector <Sprite*> mDeleteDescription;
	Sprite* mNowDescriptionOne;
	Sprite* mNowDescriptionTwo;
	Sprite* mNowDescriptionThree;
	Sprite* mBackDescription;

	// どのアイテムを取っているか検索する
	void mInit();
};
