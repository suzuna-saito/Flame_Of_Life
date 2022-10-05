/*
@brief	プリプロセッサ
*/
#include "pch.h"

//現在のシーンの初期化
SceneBase::SceneType SceneBase::mIsScene = SceneType::eInit;

/*
@fn	コンストラクタ
*/
SceneBase::SceneBase()
	: mFullPicture(nullptr)
	, mMapCreate(nullptr)
	, mClearFlag(false)
	, mGameSceneFlag(false)
	, mReturnTitleFlag(false)
	, mNextSceneCount(0)
	, mThisSpriteAlpha(1.0f)
{
	//環境光
	const Vector3 AmbientLight = Vector3(0.4f, 0.4f, 0.4f);

	// ライトを設定(設定しないと何も映らない)
	RENDERER->SetAmbientLight(Vector3(0.8f, 0.8f, 0.8f));
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.m_direction = Vector3(0.0f, 0.0f, 0.0f);
	dir.m_diffuseColor = Vector3(1.0f, 1.0f, 1.0f);
	//dir.m_diffuseColor = Vector3(0.5f, 0.5f, 0.8f);
	dir.m_specColor = Vector3(0.8f, 0.8f, 0.8f);
}
