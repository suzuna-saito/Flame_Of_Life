#include "pch.h"

// 静的変数の初期化
int ItemBase::mItemCount = 0;

ItemBase::ItemBase(const SceneBase::Scene _sceneTag, const Tag& _objectTag)
	: GameObject(_sceneTag, _objectTag)
	, mCollisionFlag(false)
{
	// アイテムが生成されるたびにカウントを取る。
	mItemCount++;
}
