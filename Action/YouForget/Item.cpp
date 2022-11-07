#include "pch.h"

// 静的メンバ変数の初期化
vector<Item::PieceNum> Item::mGetNumber;	// 収集したピースの格納

Item::Item(const Vector3 _pos, const int _num)
	: GameObject(ObjTag::ePuzzle)
	, mItemExistsTime(0)
	, mItemFlashingTime(200)
	, mItemExistsFlag(true)
	, MMaxPos(_pos.z + 70.0f)
	, MMinPos(_pos.z)
	, mPosMove(70.0f)
	, mAlphaMove(0.05f)
{
	// Component基底クラスは自動で管理クラスに追加され自動で解放される
	mMeshComponent = new MeshComponent(this);
	// Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Item/Puzzle.gpmesh"));

	//当たり判定
	mSelfBoxCollider = new BoxCollider(this, mTag, GetOnCollisionFunc());
	AABB box = { Vector3(3.0f,-3.0f,-3.0f),Vector3(-3.0f,4.0f,3.0f) };
	mSelfBoxCollider->SetObjectBox(box);

	//回転処理                        ↓回転する値
	float radianZ = Math::ToRadians(90.0f);					// Z軸回転
	Quaternion rot = this->GetRotation();
	Quaternion incZ(Vector3::UnitZ, radianZ);
	Quaternion target = Quaternion::Concatenate(rot, incZ);
	SetRotation(target);

	float radianY = Math::ToRadians(-80.0f * (int)_num);	// Y軸回転
	rot = this->GetRotation();
	Quaternion incY(Vector3::UnitY, radianY);
	target = Quaternion::Concatenate(rot, incY);
	SetRotation(target);

	float radianX = Math::ToRadians(-40.0f);				// X軸回転
	rot = this->GetRotation();
	Quaternion incX(Vector3::UnitX, radianX);
	target = Quaternion::Concatenate(rot, incX);
	SetRotation(target);

	//GameObjectメンバ変数の初期化
	SetScale(Vector3(18.0f, 18.0f, 18.0f));	// スケール
	SetPosition(_pos);						// ポジション
	mColor = Vector3(0.68f, 0.85f, 1.2f);	// 色

	// アイテムの丸影エフェクトを生成
	new CircledShadow(this, Color::LightBlue);

	// パズルピースのナンバー、生存時間を設定
	SetPieceInfo(_num);
}

void Item::SetPieceInfo(int _num)
{
	// 生成されたときのシーンによってパズルピースの生存時間を変える
	int MItemExistsOneTime = 0;
	int MItemExistsTwoTime = 0;
	int MItemExistsThreeTime = 0;

	if (SceneBase::mIsSceneType == SceneBase::SceneType::eFirst)
	{
		MItemExistsOneTime = 2000;		// 一番奥のピース
		MItemExistsTwoTime = 1700;		// 真ん中のピース
		MItemExistsThreeTime = 1000;	// 一番近くのピース
	}
	else if (SceneBase::mIsSceneType == SceneBase::SceneType::eSecond)
	{
		MItemExistsOneTime = 2700;
		MItemExistsTwoTime = 800;
		MItemExistsThreeTime = 600;
	}
	else if(SceneBase::mIsSceneType == SceneBase::SceneType::eThird)
	{
		MItemExistsOneTime = 4800;
		MItemExistsTwoTime = 3600;
		MItemExistsThreeTime = 1600;
	}

	// 生成が何番目かを保存、生存時間を代入
	if (_num == (int)PieceNum::one)
	{
		mItemNum = PieceNum::one;
		mItemExistsTime = MItemExistsOneTime;
	}
	else if (_num == (int)PieceNum::two)
	{
		mItemNum = PieceNum::two;
		mItemExistsTime = MItemExistsTwoTime;
	}
	else
	{
		mItemNum = PieceNum::three;
		mItemExistsTime = MItemExistsThreeTime;
	}
}

void Item::UpdateGameObject(float _deltaTime)
{
	// パズルピースの生存時間の計算
	PieceExists();

	// 生存フラグがfalseだったら
	if (!mItemExistsFlag)
	{
		// 描画をやめる
		mMeshComponent->SetVisible(false);

		// ステートを更新停止状態にする
		SetState(State::Paused);
	}
	// まだピースが生存している時にプレイヤーと当たったら
	else if (mCollisionFlag)
	{
		// 取得したアイテムをデータ構造に格納する
		mGetNumber.push_back(mItemNum);

		// アイテムが存在してないとする
		mItemExistsFlag = false;
	}
	else
	{
		// パズルピースを上下させる
		mPosition.z += mPosMove * _deltaTime;

		// ポジションが設定した最大値以上または、最小値いかになったら
		if (mPosition.z >= MMaxPos || mPosition.z <= MMinPos)
		{
			// 移動値の符号を反転させる
			mPosMove *= -1;
		}

		// ポジションを更新
		SetPosition(mPosition);
	}
}

void Item::OnCollision(const GameObject& _hitObject)
{
	// プレイヤーが操作可能状態の時にピースに当たったら
	if (Player::mOperable)
	{
		// 当たったのでフラグを上げる
		mCollisionFlag = true;
	}
}

void Item::PieceExists()
{
	// アイテムの生存時間を引いてく
	mItemExistsTime--;

	// 残りの生存時間が200よりも小さくなったら
	if (mItemExistsTime <= mItemFlashingTime)
	{
		// 点滅させる
		mAlpha += mAlphaMove;

		// α値が1以上、または0以下だったら
		if (mAlpha >= 1.0f || mAlpha <= 0.0f)
		{
			// α値の変化値の符号を変更
			mAlphaMove *= -1;
		}
	}

	// 残りの生存時間が0よりも小さくなったら、かつ、α値が0以下になったら
	if (mItemExistsTime <= 0 && mAlpha <= 0.0f)
	{
		// 生存フラグをfalseにする
		mItemExistsFlag = false;
	}
}