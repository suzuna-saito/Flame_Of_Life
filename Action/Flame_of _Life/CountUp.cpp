//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "pch.h"

// 静的メンバーの初期化
bool CountUp::countStartFlag = false;

/*
@brief	コンストラクタ
@param	カウントする時間
@param	現在のシーン
*/
CountUp::CountUp(SceneBase::Scene _sceneTag)
	: GameObject(_sceneTag, Tag::UI, false)
	, AddTimeCount(60)
	, time(0)
	, MMaxTime(999)
	, MPosition(Vector3(-700.0f, 450.0f, 0.0f))
{
	// ポジションをセット
	SetPosition(MPosition);

	// SpriteComponentの初期化
	sprite = new SpriteComponent(this);
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
CountUp::~CountUp()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void CountUp::UpdateGameObject(float _deltaTime)
{
	// ゲームスタートしたらカウント開始
	if (countStartFlag == true && frameCount != MMaxTime)
	{
		// フレームカウントを数える
		frameCount++;
		// カウントが60になったら
		if (frameCount >= AddTimeCount)
		{
			// timeを増やす
			time += 1;
			frameCount = 0;
		}
	}

	//@@@
	// textureを先に作ってvector配列に格納している都合上0を描画するときnullにアクセスしてしまうのを回避
	if (time == 0)
	{
		sprite->SetTexture(RENDERER->GetTimeTexture(-1));
	}
	else
	{
		// 白色で描画
		sprite->SetTexture(RENDERER->GetTimeTexture(time - 1));
	}
}