#pragma once

// クラスの前方宣言
class SpriteComponent;

/*
@file CountUp.h
@brief カウントダウンフォントの表示を行う
*/
class ItemCount : public GameObject
{
public:

    /*
    @brief	コンストラクタ
    @param	カウントする時間
    @param	現在のシーン
    */
    ItemCount(SceneBase::Scene _sceneTag);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~ItemCount();

    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;


private:
    // SpriteComponent変数
    SpriteComponent* sprite;

    // 表示させるポジション
    const Vector3 MPosition;

public://ゲッターセッター
};