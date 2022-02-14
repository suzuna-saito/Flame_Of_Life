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

    /*
    @enum シーンの種類
    */
    enum class Scene:unsigned char
    {
        // その他
        other,
        // タイトル
        title,
        // チュートリアル
        tutorial,
        // Firstステージ
        first,
        // Secondステージ
        second,
        // Thirdステージ
        third,
        // Firstリザルト
        firstResult,
        // Secondリザルト
        secondResult,
        // Thirdリザルト
        thirdResult,
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

    // 次のシーンに遷移するか
    bool mGameSceneFlag;

    //ゲームクリアしたか
    bool mClearFlag;

    //次のシーンに遷移する時の待機時間
    int mNextSceneCount;
private:

    //現在のシーン
    static Scene mIsScene;

public://ゲッターセッター

    /*
    @return 現在のシーン(int型)
    */
    static Scene GetScene() { return mIsScene; };

    /*
    @param _isScene 現在のシーン
    */
    virtual void SetScene(Scene _isScene) { mIsScene = _isScene; };
};