/*
@brief	インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_nowScene 現在のシーン
*/
GameScene::GameScene(const Scene& _nowScene)
{
	// ライトを設定(設定しないと何も映らない)
	RENDERER->SetAmbientLight(Vector3(0.8f, 0.8f, 0.8f));
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.m_direction = Vector3(0.0f, 0.0f, 0.0f);
	//dir.diffuseColor = Vector3(1.0f, 1.0f, 1.0f);
	dir.m_diffuseColor = Vector3(0.5f, 0.5f, 0.8f);
	dir.m_specColor = Vector3(0.8f, 0.8f, 0.8f);

	SetScene(_nowScene);

	mMapCreate = new MapCreate();

	if (!mMapCreate->OpenFile())
	{
		// 床の生成
		mMapCreate->CreateGround();
		// プレイヤーの生成
		mMapCreate->CreatePlayer();
	}

}

/*
@fn	デストラクタ
*/
GameScene::~GameScene()
{
	GAME_OBJECT_MANAGER->RemoveGameObjects(tutorial);
}

/*
@fn	現在のシーン時に毎フレーム更新処理をする
*/
SceneBase* GameScene::update()
{
	return this;
}