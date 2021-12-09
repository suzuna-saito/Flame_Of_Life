#include "pch.h"
#include "ItemCount.h"

ItemCount::ItemCount(SceneBase::Scene _sceneTag)
	: GameObject(_sceneTag, Tag::UI, false)
	, MPosition(Vector3::Zero)
{
	// ポジションをセット
	SetPosition(MPosition);

	// SpriteComponentの初期化
	sprite = new SpriteComponent(this);
}

ItemCount::~ItemCount()
{
}

void ItemCount::UpdateGameObject(float _deltaTime)
{
	sprite->SetTexture(RENDERER->GetItemCountTexture(Rose::mItemCount));
}
