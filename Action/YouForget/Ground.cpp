/*
@brief	インクルード
*/
#include "pch.h"

// 静的メンバ変数の初期化
int Ground::mTypeNum = 0;

Ground::Ground(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag, const groundTag& _tag)
	:GameObject(_sceneTag, _objectTag)
	, mAlphaNum(0)
	, MAlphaAddSpeed(4.5f)
	, MAlphaSubSpeed(0.7f)
	, MAlphaMax(1.2f)
	, mGroundTag(_tag)
	, mAlphaColorTag(alphaColor::red)
{
	//GameObjectメンバ変数の初期化
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	//Component基底クラスは自動で管理クラスに追加され自動で解放される
	mMeshComponent = new MeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Books/Book_1.gpmesh"));

	//地面の当たり判定
	mSelfBoxCollider = new BoxCollider(this, ColliderTag::groundTag, GetOnCollisionFunc());
	AABB box = { Vector3(-14.5f,-21.5f,0.0f),Vector3(14.5f,20.0f,9.0f) };
	mSelfBoxCollider->SetObjectBox(box);

	// 床の色などを設定する
	if (mGroundTag == groundTag::RGBalpha)
	{
		mInit();
	}

	// 透明度
	if (mGroundTag == groundTag::RGBalpha)
	{
		mAlpha = 0.0f;
	}
}

void Ground::UpdateGameObject(float _deltaTime)
{
	mAabb = mSelfBoxCollider->GetWorldBox();

	// スイッチを押していたらかつ、今踏んでるスイッチの色と床の色が一緒だったら
	if (Switch::mSwitchFlag && mGroundTag == groundTag::RGBalpha &&
		mAlphaColorTag == SwitchCollider::mLinkageColor)
	{
		// 少しずつ透明度をあげる
		if (mAlpha <= MAlphaMax)
		{
			mAlpha += MAlphaAddSpeed* _deltaTime;
		}
	}
	else if(mGroundTag != groundTag::notAlpha)
	{
		// 少しずつ透明度を下げる
		if (mAlpha >= 0.0f)
		{
			mAlpha -= MAlphaSubSpeed * _deltaTime;
		}
	}

	if (!Player::mOperable && mAlpha <= 1.0f)
	{
		mAlpha += MAlphaAddSpeed * _deltaTime;
	}
}

void Ground::OnCollision(const GameObject& _hitObject)
{
}

// 床の色、α値の変わるタイミングを設定する
void Ground::mInit()
{

	// ランダムでmAlphaNamを設定
	mAlphaNum = rand() % mTypeNum;

	switch (mAlphaNum)
	{
	case (int)alphaColor::red:
		mColor = Color::Red;
		// 何色の床なのかを設定
		mAlphaColorTag = alphaColor::red;
		break;
	case (int)alphaColor::green:
		mColor = Color::Green;
		// 何色の床なのかを設定
		mAlphaColorTag = alphaColor::green;
		break;
	case (int)alphaColor::yellow:
		mColor = Color::Yellow;
		break;
	}
}
