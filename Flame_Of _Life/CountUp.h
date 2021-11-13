#pragma once
/*
@brief カウントアップの表示
*/
class CountUp :public GameObject
{
public:
	/*
	@brief コンストラクタ
	*/
	CountUp(const SceneBase::Scene _sceneTag);

	/*
	@brief デストラクタ
	*/
	~CountUp();

	/*
	@brief 更新処理を行う
	*/
	void UpdateGameObject(float _deltaTime)override;

private:
	// SpriteComponent変数
	SpriteComponent* sprite;

	// 計測する時間
	int time;
};

