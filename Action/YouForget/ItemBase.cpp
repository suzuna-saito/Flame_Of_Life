#include "pch.h"

// 静的変数の初期化
int ItemBase::mItemCount = 0;
vector<ItemNum> ItemBase::mGetNumber;

ItemBase::ItemBase(const SceneBase::Scene _sceneTag, const Tag& _objectTag)
	: GameObject(_sceneTag, _objectTag)
	, mMeshComponent(0)
	, mSelfBoxCollider(0)
	, mMove(60.0f)
	, mMaxMove(50.0f)
	, mMinMove(0.0f)
	, mUpFlag(true)
	, mCollisionFlag(false)
	, mItemNum(ItemNum::first)
{
	// アイテムが生成されるたびにカウントを取る。
	mItemCount++;
}

// 前置インクリメント
//ItemNum& operator++(ItemNum& rhs)
//{
//	if (rhs == ItemNum::end)
//	{
//		throw std::out_of_range("for outof range Tag& operator ++ (Tag&)");
//	}
//	rhs = ItemNum(static_cast<std::underlying_type<ItemNum>::type>(rhs) + 1);
//
//	return rhs;
//}
