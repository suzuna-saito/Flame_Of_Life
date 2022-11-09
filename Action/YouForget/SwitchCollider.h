/*
@brief	プリプロセッサ
*/
#pragma once

class SwitchCollider :public GameObject
{
public:

	/*
	@fn		コンストラクタ
	*/
	SwitchCollider(Switch* _owner, const ObjTag& _objectTag, const SceneBase::SceneType _sceneTag,const Switch::switchColor _switchColor);

	/*
	@fn	デストラクタ
	*/
	~SwitchCollider() {};

	/*
	@fn	更新
	*/
	void UpdateGameObject(float _deltaTime)override;

	// スイッチと連携している床の色
	static Ground::GroundColor mLinkageColor;

private:
	Ground::GroundColor mSwitchColor;

	//スイッチ中心の判定を生成
	BoxCollider* mSwitchBoxCollider;

	Switch* mOwner;

	/*
	@fn 当たり判定が行われHitした際に呼ばれる関数(足元判定用)
	@param	当たったGameObject
	*/
	void OnCollision(const GameObject& _hitObject)override;

public://ゲッターセッター
};


