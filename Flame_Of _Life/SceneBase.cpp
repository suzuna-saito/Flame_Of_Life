/*
@brief	プリプロセッサ
*/
#include "pch.h"

//現在のシーンの初期化
int SceneBase::mIsScene = 0;

/*
@fn	コンストラクタ
*/
SceneBase::SceneBase()
	:/* mSprite(nullptr)
	, */mMapCreate(nullptr)
	, mClearFlag(false)
	, mNextSceneCount(false)
{
}
