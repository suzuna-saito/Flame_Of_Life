#include "pch.h"
#include "Time.h"

Time::Time(const Vector2& _pos, const Tag& _objectTag, SceneBase::Scene _sceneTag)
	:UIBase(_pos, "Assets/heart02.png", _sceneTag, _objectTag)
{
}

void Time::UpdateGameObject(float _deltaTime)
{
}
