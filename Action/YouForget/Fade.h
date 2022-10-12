#pragma once

/*
* フェードイン、フェードアウト用クラス
*/
class Fade : public UIBase
{
public:
	// フェードイン　or フェードアウト
	typedef enum class FadeType :unsigned char
	{
		eIn,	// イン
		eOut	// アウト
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Fade();
	// デストラクタ
	~Fade() {};

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="_deltaTime">最後のフレームを完了するのに要した時間</param>
	void UpdateGameObject(float _deltaTime)override;


private:
	float mFadeSpeed;	// フェードさせるスピード
	bool mFadeFlag;		// フェードイン、フェードアウトの更新処理をするフラグ true: 更新してる

public:	// ゲッター、セッター
	// フェードを更新しているか取得するture:更新している
	bool GetNowFadeFlag() { return mFadeFlag; }
	/// <summary>
	/// フェードインまたはフェードアウトを始める設定をする
	/// </summary>
	/// <param name="_color">色</param>
	/// <param name="_fadeType">フェードインかフェードアウトか</param>
	void SetFade(Vector3 _color, FadeType _fadeType);
};