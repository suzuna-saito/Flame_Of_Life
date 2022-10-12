#include "pch.h"

// 静的メンバ変数の初期化
SceneBase::SceneType SceneBase::mIsSceneType = SceneType::eInit;	// 現在のシーンタイプ

SceneBase::SceneBase(const SceneType& _sceneType)
	: mFullPicture(nullptr)
	, mMapCreate(nullptr)
	, mGameSceneFlag(false)
	, mReturnTitleFlag(false)
{
	// ライトを設定(設定しないと何も映らない)
	RENDERER->SetAmbientLight(Vector3(1.0f, 1.0f, 1.0f));	// 光の色
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.m_direction = Vector3::Zero;						// 方向
	dir.m_diffuseColor = Vector3(1.0f, 1.0f, 1.0f);			// 拡散反射色
	dir.m_specColor = Vector3(1.0f, 1.0f, 1.0f);			// 鏡面反射色

	// シーンタイプの更新
	mIsSceneType = _sceneType;
	//// シーンがeLastResultでクリアフラグがたっていた時だけ
	//if (mIsSceneType == SceneType::eLastResult && ResultBase::mClearEndFlag)
	//{
	//	// 白いフェードインをさせる
	//	mFade->SetFade(Color::White, Fade::FadeType::eIn);
	//}
	//else
	//{
	//	// 黒いフェードインをさせる
	//	mFade->SetFade(Color::Black, Fade::FadeType::eIn);
	//}
}