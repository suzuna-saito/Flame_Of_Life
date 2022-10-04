/*
@brief	プリプロセッサ
*/
#pragma once

struct InputState;

class BackGroundSprite;
class MapCreate;
class Sprite;
class Candle;

class SceneBase
{
public:

    /*
    @fn	コンストラクタ
    */
    SceneBase();

    /*
    @fn	デストラクタ
    */
    virtual ~SceneBase() {};

    /*
    @fn	現在のシーン時に毎フレーム更新処理をする
    */
    virtual SceneBase* update() = 0;

    /*
    @fn	現在のシーン時に毎フレーム入力処理をする
    */
    virtual void Input(const InputState& state) {};

    // シーンの種類
    enum class SceneType :unsigned char
    {
        eInit,          // 初期状態
        eTitle,         // タイトル
        eTutorial,      // チュートリアル
        eFirst,         // Firstステージ
        eSecond,        // Secondステージ
        eThird,         // Thirdステージ
        eFirstResult,   // Firstリザルト
        eSecondResult,  // Secondリザルト
        eThirdResult,   // Thirdリザルト
        eGameClear,     // ゲームクリア
        eGameOver,      // ゲームオーバー
    };

protected:

    //背景
    Sprite* mSprite;
    //マップ生成
    MapCreate* mMapCreate;

    // 次のシーンに遷移するか
    bool mGameSceneFlag;

    // タイトルシーンに遷移するか
    bool mReturnTitleFlag;

    //ゲームクリアしたか
    bool mClearFlag;

    //次のシーンに遷移する時の待機時間
    int mNextSceneCount;

    // 説明画像のα値
    float mThisSpriteAlpha;
private:

    //現在のシーン
    static SceneType mIsScene;

public://ゲッターセッター

    /*
    @return 現在のシーン(int型)
    */
    static SceneType GetScene() { return mIsScene; };

    /*
    @param _isScene 現在のシーン
    */
    virtual void SetScene(SceneType _isScene) { mIsScene = _isScene; };
};