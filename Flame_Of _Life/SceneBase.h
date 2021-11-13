/*
@brief	プリプロセッサ
*/
#pragma once

struct InputState;

class BackGroundSprite;
class MapCreate;
class Sprite;
class Candle;
class Time;

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

    /*
    @enum シーンの種類
    */
    enum Scene
    {
        // その他
        other,
        // タイトル
        title,
        // チュートリアル
        tutorial,
        // ステージ1
        stage01,
        // ゲームクリア
        gameClear,
        // ゲームオーバー
        gameOver,
        // コンティニュー 
        Continue
    };

protected:

    //背景
    Sprite* mSprite;
    //マップ生成
    MapCreate* mMapCreate;
    // ろうそくの生成
    Candle* mCandle;
    //時間のUI
    Time* mTime;

    // 次のシーンに遷移するか
    bool mGameSceneFlag;

    //次のシーンに遷移する時の待機時間
    int mNextSceneCount;

    //ゲームクリアしたか
    bool mClearFlag;
private:

    //現在のシーン
    static int   mIsScene;

public://ゲッターセッター

    /*
    @return 現在のシーン(int型)
    */
    static int  GetScene() { return mIsScene; };

    /*
    @param _isScene 現在のシーン
    */
    virtual void SetScene(int _isScene) { mIsScene = _isScene; };
};