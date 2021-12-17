#include "pch.h"

// 静的変数の初期化
int ItemBase::mItemCount = 0;
vector<itemNames> ItemBase::mGetNames;

ItemBase::ItemBase(const SceneBase::Scene _sceneTag, const Tag& _objectTag)
	: GameObject(_sceneTag, _objectTag)
	, mMeshComponent(0)
	, mSelfBoxCollider(0)
	, mCollisionFlag(false)
{
	// アイテムが生成されるたびにカウントを取る。
	mItemCount++;
}

// 前置インクリメント
//itemNames& operator++(itemNames& rhs)
//{
//	if (rhs == itemNames::end)
//	{
//		throw std::out_of_range("for outof range Tag& operator ++ (Tag&)");
//	}
//	rhs = itemNames(static_cast<std::underlying_type<itemNames>::type>(rhs) + 1);
//
//	return rhs;
//}
