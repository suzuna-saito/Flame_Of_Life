/*
@brief	インクルード
*/
#include "pch.h"

/*
@param	_pos UIの生成場所(スクリーン座標)
@param	_uiFileName 画像へのアドレス
@param	_objectTag アタッチしたゲームオブジェクトのタグ
@param	_sceneTag シーンのタグ
@param	_scale 画像の拡大サイズ
*/
UIBase::UIBase(const Vector2& _pos, const std::string& _uiFileName, SceneBase::Scene _sceneTag, const Tag& _objectTag, const float& _scale)
	: GameObject(_sceneTag, _objectTag)
{

}

/*
@fn 派生クラスの更新関数を呼び座標に移動量を足し続ける
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void UIBase::UpdateGameObject(float _deltaTime)
{

}