#include "pch.h"

CountUp::CountUp(const SceneBase::Scene _sceneTag)
	: GameObject(_sceneTag, Tag::UI)
	, time(0)
{
	// �|�W�V�������Z�b�g
	SetPosition(Vector3(700.0f, 480.0f, 0.0f));
	// SpriteComponent�̏�����
	sprite = new SpriteComponent(this,110);
}

CountUp::~CountUp()
{
}

void CountUp::UpdateGameObject(float _deltaTime)
{
	//sprite->SetTexture(RENDERER->GetTimeTexture(time - 1));
}
