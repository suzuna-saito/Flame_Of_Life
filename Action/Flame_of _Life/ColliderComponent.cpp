/*
@file	ColliderComponent.h
@brief	当たり判定を行うコンポーネントの規定クラス
*/

/*
@brief	インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_owner アタッチするゲームオブジェクトのポインタ
@param	_tag アタッチするゲームオブジェクトの当たり判定のタグ
@param	_updateOrder コンポーネントの更新順番（数値が小さいほど早く更新される）
@param  _collisionOrder 当たり判定時に、めり込みから動かす処理の優先度を決める数値
*/
ColliderComponent::ColliderComponent(GameObject* _owner, ColliderTag _tag, int _updateOrder, int _collisionOrder)
	: Component(_owner, _updateOrder)
	, mTriggerFlag(false)
	, mCollisionOrder(_collisionOrder)
	, mTag(_tag)
{
}

ColliderTag& operator++(ColliderTag& rhs)
{
	if (rhs == ColliderTag::end)
	{
		throw std::out_of_range("for outof range Tag& operator ++ (Tag&)");
	}
	rhs = ColliderTag(static_cast<std::underlying_type<ColliderTag>::type>(rhs) + 1);

	return rhs;
}
