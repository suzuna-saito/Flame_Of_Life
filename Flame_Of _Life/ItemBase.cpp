#include "pch.h"

// �ÓI�ϐ��̏�����
int ItemBase::mItemCount = 0;

ItemBase::ItemBase(const SceneBase::Scene _sceneTag, const Tag& _objectTag)
	: GameObject(_sceneTag, _objectTag)
	, mCollisionFlag(false)
{
	// �A�C�e������������邽�тɃJ�E���g�����B
	mItemCount++;
}
