#include "pch.h"

// 静的メンバ変数の初期化
vector<PuzzlePiece::PieceNum> PuzzlePiece::mGetNumber;	// 収集したピースの格納

PuzzlePiece::PuzzlePiece(const Vector3 _pos, const int _num)
	: GameObject(ObjTag::ePuzzle)
	, mPieceNum()
	, MMaxPos(_pos.z + 70.0f)
	, MMinPos(_pos.z)
	, mAlphaMove(0.05f)
	, mPosMove(70.0f)
	, mPieceExistsTime(0)
	, mPieceFlashingTime(200)
	, mPieceExistsFlag(true)
{
	// MeshComponentを生成することで自動で管理クラスに追加され自動で解放される
	mMeshComponent = new MeshComponent(this);
	// Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Item/Puzzle.gpmesh"));

	// 当たり判定
	mSelfBoxCollider = new BoxCollider(this, mTag, GetOnCollisionFunc());
	AABB box = { Vector3(-3.0f,-3.0f,-3.0f),Vector3(3.0f,4.0f,3.0f) };
	mSelfBoxCollider->SetObjectBox(box);

	// 回転処理						↓回転する値
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

	// GameObjectメンバ変数の初期化
	SetScale(Vector3(18.0f, 18.0f, 18.0f));	// スケール
	SetPosition(_pos);						// ポジション
	mColor = Vector3(0.68f, 0.85f, 1.2f);	// 色

	// パズルピースの丸影エフェクトを生成
	new CircledShadow(this, Color::LightBlue);

	// パズルピースのナンバー、生存時間を設定
	SetPieceInfo(_num);
}

void PuzzlePiece::SetPieceInfo(int _num)
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
	else if (SceneBase::mIsSceneType == SceneBase::SceneType::eThird)
	{
		MItemExistsOneTime = 4800;
		MItemExistsTwoTime = 3600;
		MItemExistsThreeTime = 1600;
	}

	// 生成が何番目かを保存、生存時間を代入
	if (_num == (int)PieceNum::eOne)
	{
		mPieceNum = PieceNum::eOne;
		mPieceExistsTime = MItemExistsOneTime;
	}
	else if (_num == (int)PieceNum::eTwo)
	{
		mPieceNum = PieceNum::eTwo;
		mPieceExistsTime = MItemExistsTwoTime;
	}
	else
	{
		mPieceNum = PieceNum::eThree;
		mPieceExistsTime = MItemExistsThreeTime;
	}
}

void PuzzlePiece::UpdateGameObject(float _deltaTime)
{
	// パズルピースの生存時間の計算
	PieceExists();

	// 生存フラグがfalseだったら
	if (!mPieceExistsFlag)
	{
		// 描画をやめる
		mMeshComponent->SetVisible(false);

		// ステートを更新停止状態にする
		SetState(State::Paused);

		return;
	}

	// プレイヤーと当たったら
	if (mCollisionFlag)
	{
		// 取得したパズルピースをデータ構造に格納する
		mGetNumber.push_back(mPieceNum);

		// パズルピースが存在してないとする
		mPieceExistsFlag = false;
	}
	else
	{
		// パズルピースを上下させる
		mPosition.z += mPosMove * _deltaTime;

		// ポジションが設定した最大値以上または、最小値以下になったら
		if (mPosition.z >= MMaxPos || mPosition.z <= MMinPos)
		{
			// 移動値の符号を反転させる
			mPosMove *= -1;
		}

		// ポジションを更新
		SetPosition(mPosition);
	}
}

void PuzzlePiece::OnCollision(const GameObject& _hitObject)
{
	// プレイヤーが操作可能状態の時にピースに当たったら
	if (Player::mOperable)
	{
		// 当たったのでフラグを上げる
		mCollisionFlag = true;
	}
}

void PuzzlePiece::PieceExists()
{
	// パズルピースの生存時間を引いてく
	--mPieceExistsTime;

	// 残りの生存時間が0よりも小さくなったら、かつ、α値が0以下になったら
	if (mPieceExistsTime <= 0 && mAlpha <= 0.0f)
	{
		// 生存フラグをfalseにする
		mPieceExistsFlag = false;
		return;
	}

	// 残りの生存時間が設定した値よりも小さくなったら、点滅させる
	if (mPieceExistsTime <= mPieceFlashingTime)
	{
		mAlpha += mAlphaMove;

		// α値が1以上、または0以下だったら
		if (mAlpha >= 1.0f || mAlpha <= 0.0f)
		{
			// α値の変化値の符号を変更
			mAlphaMove *= -1;
		}
	}
}