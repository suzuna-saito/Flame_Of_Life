/*
@brief	インクルード
*/
#include "pch.h"
/*
@fn		コンストラクタ
@param	_nowScene 現在のシーン
*/
TitleScene::TitleScene(const Scene& _nowScene)
	: mGameSceneFlag(false)
{
	// ライトを設定(設定しないと何も映らない)
	RENDERER->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.m_direction = Vector3(1.0f, 0.7f, -0.7f);
	//dir.diffuseColor = Vector3(1.0f, 1.0f, 1.0f);
	dir.m_diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.m_specColor = Vector3(0.8f, 0.8f, 0.8f);

	SetScene(_nowScene);

	new TitleUI();

	mNextSceneCount = 0;
}

/*
@fn	デストラクタ
*/
TitleScene::~TitleScene()
{
	GAME_OBJECT_MANAGER->RemoveGameObjects(title);
}

void TitleScene::Input(const InputState& _inputState)
{
	if (_inputState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_START) == 1 ||
		_inputState.m_keyboard.GetKeyValue(SDL_SCANCODE_SPACE) == 1)
	{
		mGameSceneFlag = true;
	}
}

/*
@fn	現在のシーン時に毎フレーム更新処理をする
*/
SceneBase* TitleScene::update()
{

	if (mGameSceneFlag)
	{
		//return new GameScene(tutorial);
	}

	return this;
}