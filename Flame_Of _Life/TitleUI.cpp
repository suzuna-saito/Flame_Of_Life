/*
@brief	インクルード
*/
#include "pch.h"

TitleUI::TitleUI()
	: GameObject(SceneBase::Scene::title, Tag::UI)
{

	spriteComponent = new SpriteComponent(this);
	spriteComponent->SetTexture(RENDERER->GetTexture("Assets/UI/Title.png"));
	spriteComponent->SetVisible(true);
}
