/*
@brief インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_Pos ボタン画像の生成場所(スクリーン座標)
@param	_ObjectTag アタッチしたゲームオブジェクトのタグ
@param	_SceneTag シーンのタグ
*/
ButtonUI::ButtonUI(const Vector2& _Pos, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag)
	:UIBase(_Pos, "Assets/UI/Button.png", _SceneTag, _ObjectTag)
{
	mUI = new UIComponent(this,0);
	mUI->SetTexture(RENDERER->GetTexture("Assets/UI/Button.png"));

	mPosition = Vector3(_Pos.x, _Pos.y, 0.0f);
}

/*
@fn		ボタン画像のアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void ButtonUI::UpdateGameObject(float _deltaTime)
{
}
