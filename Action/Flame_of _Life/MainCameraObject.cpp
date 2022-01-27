/*
@brief	インクルード
*/
#include "pch.h"

/*
@fn	コンストラクタ
*/
MainCameraObject::MainCameraObject()
	: GameObject(SceneBase::Scene::other, Tag::Camera, true)
	, mHasParentObject(false)
	, mOffsetPos(Vector3::Zero)
	, mLerpObject(Vector3::Zero)
{
	SetPosition(Vector3(-100.0f, 0.0f, 0.0f));
	mTag = Tag::Camera;
}

/*
@fn	デストラクタ
*/
MainCameraObject::~MainCameraObject()
{
}

/*
@fn		このクラスはポーズ中に別クラスから更新関数を呼ばれることがある
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void MainCameraObject::UpdateGameObject(float _deltaTime)
{
	Vector3 pos = mOffsetPos + mPosition;
	pos = mLerpObject + mOffsetPos;
	
	mPosition = pos;

	SetPosition(mPosition);
	Matrix4 view = Matrix4::CreateLookAt(mPosition, mLerpObject, Vector3::UnitZ);
	RENDERER->SetViewMatrix(view);
}

/*
@param _offset　見たい座標との差
@param _parentPos　見る座標
*/
void MainCameraObject::SetViewMatrixLerpObject(const Vector3& _offset, const Vector3& _parentPos)
{
	mHasParentObject = true;
	mOffsetPos = _offset;
	mLerpObject = _parentPos;
}

/*
@brief ゲーム中の移動処理
@param	_deltaTime 前のフレームでかかった時間
*/
void MainCameraObject::InGameMovableProcess(float _deltaTime)
{
	//// カメラ半径の補正関数
	//CorrectionRadius();

	//// ポジション計算関数
	//CalculationPosition(_deltaTime);

	//// ビュー行列計算関数
	//CalculationViewMatrix();

	//// プレイヤー側に渡す前方ベクトルを生成
	//mForwardVec = lerpObjectPos - position;
	//// 正規化
	//mForwardVec.Normalize();
	//// Z軸を固定
	//mForwardVec.z = 0.0f;

	//// 当たり判定を行うオブジェクトと当たったポジションを保存
	//tmpHitFlag = hitFlag;

	//// 当たり判定を行う際に利用する変数の初期化
	//hitPosition = Vector3::Zero;
	//hitFlag = false;
}
