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
