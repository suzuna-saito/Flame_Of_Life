#include "pch.h"
#include "ItemCount.h"

ItemCount::ItemCount(SceneBase::Scene _sceneTag)
	: GameObject(_sceneTag, Tag::UI, false)
	, MPosition(Vector3::Zero)
{
	// �|�W�V�������Z�b�g
	SetPosition(MPosition);

	// SpriteComponent�̏�����
	sprite = new SpriteComponent(this);
}

ItemCount::~ItemCount()
{
}

void ItemCount::UpdateGameObject(float _deltaTime)
{
	sprite->SetTexture(RENDERER->GetItemCountTexture(Rose::mItemCount));
}
