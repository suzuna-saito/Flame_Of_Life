/*
@file	PhysicsWorld.h
@brief	当たり判定を行う
*/

/*
@brief	プリプロセッサ
*/
#pragma once


#define PHYSICS PhysicsWorld::GetInstance()

class GameObject;
class BoxCollider;
class SphereCollider;
class ColliderComponent;


typedef std::function<void(GameObject&)> OnCollisionFunc;
typedef std::map<ColliderComponent*, std::function<void(GameObject&)>> OnCollisionMap;

class PhysicsWorld
{
public:

	/*
	@fn	インスタンスを作成する
	*/
	static void CreateInstance();

	/*
	@fn	インスタンスを削除する
	*/
	static void DeleteInstance();

	/*
	@fn	当たり判定
	*/
	void HitCheck();

	/*
	@fn		矩形の当たり判定
	@brief	矩形の当たり判定がどのオブジェクトと当たったかタグで調べる
	@param _box BoxColliderクラスのポインタ
	*/
	void HitCheck(BoxCollider* _box);

	/*
	@fn		球の当たり判定
	@brief	球の当たり判定がどのオブジェクトと当たったかタグで調べる
	@param _sphere SphereColliderクラスのポインタ
	*/
	void HitCheck(SphereCollider* _sphere);

	/*
	@fn		矩形の当たり判定を追加
	@param	_box　追加するBoxColliderクラスのポインタ
	*/
	void AddBox(BoxCollider* _box, OnCollisionFunc _func);

	/*
	@fn		矩形の当たり判定を削除
	@param	_box　削除するBoxColliderクラスのポインタ
	*/
	void RemoveBox(BoxCollider* _box);

	/*
	@fn		球の当たり判定を追加
	@param	_sphere　追加するSphereColliderクラスのポインタ
	*/
	void AddSphere(SphereCollider* _sphere, OnCollisionFunc _func);

	/*
	@fn		球の当たり判定を削除
	@param	_sphere　削除するSphereColliderクラスのポインタ
	*/
	void RemoveSphere(SphereCollider* _sphere);

private:

	/*
	@fn	コンストラクタの隠蔽
	*/
	PhysicsWorld();

	//自分のインスタンス
	static PhysicsWorld* mPhysics;

	/*
	@fn	矩形と矩形の当たり判定
	*/
	void BoxAndBox();

	/*
	@fn	球と球の当たり判定
	*/
	void SphereAndSphere();

	/*
	@fn	球と矩形の当たり判定
	*/
	void SphereAndBox();

	//矩形の当たり判定を全て格納するための可変長コンテナ
	std::vector<BoxCollider*> mBoxes;

	//床の矩形当たり判定を全て格納するための可変長コンテナ
	std::vector<BoxCollider*> mGroundBoxes;

	//球の当たり判定を全て格納するための可変長コンテナ
	std::vector<SphereCollider*> mSpheres;

	OnCollisionMap mCollisionFunction;

public://ゲッターセッター

	/*
	@return PhysicsWorldクラスのインスタンス(PhysicsWorld型)
	*/
	static PhysicsWorld* GetInstance() { return mPhysics; }
};

/*
@fn 衝突したことが確定したとき、めり込みを戻す関数
@param _movableBox 移動物体
@param _fixedBox 移動しない物体
@param _calcFixVec 移動物体の補正差分ベクトル
*/
void CalcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox, Vector3& _calcFixVec);