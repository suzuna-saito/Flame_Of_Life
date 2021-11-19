/*
@brief	インクルード
*/
#include "pch.h"

//ゲームオブジェクトのID、カウント用の初期化
int GameObject::mGameObjectId = 0;
//メインカメラの初期化　生成はGameObjectManager生成時に行われる
MainCameraObject* GameObject::mMainCamera = nullptr;
//ゲームオブジェクトの更新を止めるイベント状態の初期化
PauzingEvent GameObject::mPauzingEvent = PauzingEvent::NoneEvent;

/*
@param	ゲームクラスのポインタ
*/
GameObject::GameObject(SceneBase::Scene _sceneTag, const Tag& _objectTag, bool _reUseGameObject)
	: mState(Active)
	, mWorldTransform()
	, mPosition(Vector3::Zero)
	, mVelocity(Vector3::Zero)
	, mAabb(Vector3::Zero, Vector3::Zero)
	, mScale(Vector3(1.0f, 1.0f, 1.0f))
	, mDirection(Vector3::Zero)
	, mRotation(Quaternion::Identity)
	, mMyObjectId(mGameObjectId)
	, mTag(_objectTag)
	, mSceneTag(_sceneTag)
	, mMoveSpeed(8.0f)
	, MGravity(10.0f)
	, mReUseObject(_reUseGameObject)
	, mRecomputeWorldTransform(true)
	, mHitFlag(false)
	, mRespawnFlag(false)
	, mAlpha(1.0f)
	, mColor(Vector3(1.0f,1.0f,1.0f))
{
	mGameObjectId++;
	//GameObjectManagerにポインタを渡す
	GAME_OBJECT_MANAGER->AddGameObject(this);
}

GameObject::~GameObject()
{
	//GameObjectManagerからポインタを削除する
	GAME_OBJECT_MANAGER->RemoveGameObject(this);
	while (!mComponents.empty())
	{
		delete mComponents.back();
	}

}

/*
@brief	フレーム毎の処理
@param	最後のフレームを完了するのに要した時間
*/
void GameObject::Update(float _deltaTime)
{
	//更新停止のイベント中でないか(ポーズ画面など)
	if (mPauzingEvent == PauzingEvent::NoneEvent)
	{
		if (mState != Dead)
		{
			//Transformのワールド変換
			ComputeWorldTransform();
			//ゲームオブジェクトの更新
			UpdateGameObject(_deltaTime);
			//このゲームオブジェクトに付属するコンポーネントの更新
			UpdateComponents(_deltaTime);
			//Transformのワールド変換
			ComputeWorldTransform();
		}
	}
	//ポーズ画面のときコンポーネントを更新させない(アニメーションなども止めるため)
	else if (mPauzingEvent == PauzingEvent::PausingEvent)
	{
		PausingUpdateGameObject();
	}
	else
	{
		PausingUpdateGameObject();
		UpdateComponents(_deltaTime);
	}
}

/*
@brief	アタッチされてるコンポーネントのアップデート
@param	最後のフレームを完了するのに要した時間
*/
void GameObject::UpdateComponents(float _deltaTime)
{
	if (mState != Dead)
	{
		for (auto itr : mComponents)
		{
			itr->Update(_deltaTime);
		}
	}
}
/*
@brief	ゲームオブジェクトのアップデート
@param	最後のフレームを完了するのに要した時間
*/
void GameObject::UpdateGameObject(float _deltaTime)
{
}
/*
@fn ゲームオブジェクトが静止中に更新されるアップデート関数
@brief pauzingUpdateがtrueのときだけ呼ばれる更新関数
*/
void GameObject::PausingUpdateGameObject()
{
}

/*
@fn 入力状態を受け取りGameObjectとComponentの入力更新関数を呼び出す
*/
void GameObject::ProcessInput(const InputState& _keyState)
{
	if (mState == Active)
	{
		//コンポーネントの入力関数にコントローラーの入力状態を
		for (auto comp : mComponents)
		{
			comp->ProcessInput(_keyState);
		}
		//ゲームオブジェクトの入力関数にコントローラーの入力状態を
		GameObjectInput(_keyState);
	}
}

/*
@fn 入力を引数で受け取る更新関数
@brief 基本的にここで入力情報を変数に保存しUpdateGameObjectで更新を行う
*/
void GameObject::GameObjectInput(const InputState& _keyState)
{
}

/*
@brief	コンポーネントを追加する
@param	追加するコンポーネントのポインタ
*/
void GameObject::AddComponent(Component* _component)
{
	int order = _component->GetUpdateOder();
	auto itr = mComponents.begin();
	for (;
		itr != mComponents.end();
		++itr)
	{
		if (order < (*itr)->GetUpdateOder())
		{
			break;
		}
	}
	mComponents.insert(itr, _component);
}

/*
@brief	コンポーネントを削除する
@param	削除するコンポーネントのポインタ
*/
void GameObject::RemoveComponent(Component* _component)
{
	auto itr = std::find(mComponents.begin(), mComponents.end(), _component);
	if (itr != mComponents.end())
	{
		mComponents.erase(itr);
	}
}
/*
@fn 現在の仕様上行うことができない処理を外部から強引に行うための関数
@exsample ゲームオブジェクト全体の更新が停止中に対象のゲームオブジェクトを更新する
*/
void GameObject::ExceptionUpdate()
{
	ComputeWorldTransform();

	UpdateGameObject(0.016f);
	UpdateComponents(0.016f);

	ComputeWorldTransform();
}


/*
@brief	Transformのワールド変換
*/
void GameObject::ComputeWorldTransform()
{
	//ワールド変換が必要かどうか？
	//もし必要だったらワールド変換を行う
	if (mRecomputeWorldTransform)
	{
		//objectの
		//変換が必要フラグを降ろす
		mRecomputeWorldTransform = false;
		//スケールのワールド変換
		mWorldTransform = Matrix4::CreateScale(mScale);
		//回転のワールド変換（クウォータニオン）
		mWorldTransform *= Matrix4::CreateFromQuaternion(mRotation);
		//平行移動の更新
		mWorldTransform *= Matrix4::CreateTranslation(mPosition);

		//object（owner）が持っているcomponentによる座標変換系
		for (auto itr : mComponents)
		{
			itr->OnUpdateWorldTransform();
		}
	}
}

void GameObject::FixCollision(const AABB& _myAABB, const AABB& _pairAABB, const Tag& _pairTag)
{
	Vector3 ment = Vector3(0, 0, 0);
	CalcCollisionFixVec(_myAABB, _pairAABB, ment);
	SetPosition(GetPosition() + (ment));
}

void GameObject::CreateMainCamera()
{
	mMainCamera = new MainCameraObject();
}

void GameObject::CalcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox, Vector3& _calcFixVec)
{
	_calcFixVec = Vector3(0, 0, 0);
	float dx1 = _fixedBox.m_min.x - _movableBox.m_max.x;
	float dx2 = _fixedBox.m_max.x - _movableBox.m_min.x;
	float dy1 = _fixedBox.m_min.y - _movableBox.m_max.y;
	float dy2 = _fixedBox.m_max.y - _movableBox.m_min.y;
	float dz1 = _fixedBox.m_min.z - _movableBox.m_max.z;
	float dz2 = _fixedBox.m_max.z - _movableBox.m_min.z;

	// dx, dy, dz には それぞれ1,2のうち絶対値が小さい方をセットする
	float dx = (Math::Abs(dx1) < Math::Abs(dx2)) ? dx1 : dx2;
	float dy = (Math::Abs(dy1) < Math::Abs(dy2)) ? dy1 : dy2;
	float dz = (Math::Abs(dz1) < Math::Abs(dz2)) ? dz1 : dz2;

	// x, y, zのうち最も差が小さい軸で位置を調整
	if (Math::Abs(dx) <= Math::Abs(dy) && Math::Abs(dx) <= Math::Abs(dz))
	{
		_calcFixVec.x = dx;
	}
	else if (Math::Abs(dy) <= Math::Abs(dx) && Math::Abs(dy) <= Math::Abs(dz))
	{
		_calcFixVec.y = dy;
	}
	else
	{
		_calcFixVec.z = dz;
	}
}

/*
@fn		前方ベクトルの向きに回転する
@param	_forward 向かせたい前方方向ベクトル
*/
void GameObject::RotateToNewForward(const Vector3& _forward)
{
	// X軸ベクトル(1,0,0)とforwardの間の角度を求める
	float dot = Vector3::Dot(Vector3::UnitX, _forward);
	float angle = Math::Acos(dot);
	//printf("%f\n", angle);
	// 下向きだった場合
	if (dot > 0.9999f)
	{
		SetRotation(Quaternion::Identity);
	}
	// 上向きだった場合
	else if (dot < -0.9999f)
	{
		SetRotation(Quaternion(Vector3::UnitZ, Math::Pi));
	}
	else
	{
		// 軸ベクトルとforwardとの外積から回転軸をもとめ、回転させる
		Vector3 axis = Vector3::Cross(Vector3::UnitX, _forward);
		axis.Normalize();
		SetRotation(Quaternion(axis, angle));
	}
}
