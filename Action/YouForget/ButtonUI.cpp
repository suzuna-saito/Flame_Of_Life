#include "pch.h"

ButtonUI::ButtonUI(const Vector2& _Pos, const Tag& _ObjectTag, const SceneBase::SceneType _SceneTag)
	:UIBase(_Pos, "Assets/UI/Button.png", _SceneTag, _ObjectTag)
{
	mUI = new UIComponent(this,0);
	mUI->SetTexture(RENDERER->GetTexture("Assets/UI/Button.png"));

	mPosition = Vector3(_Pos.x, _Pos.y, 0.0f);
}

void ButtonUI::UpdateGameObject(float _deltaTime)
{
}
