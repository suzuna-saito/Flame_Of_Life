/*
@brief	プリプロセッサ
*/
#pragma once

class BackGroundSprite;
class MapCreate;
class Candle;

class SceneBase
{
public:
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

    /*
    @fn	コンストラクタ
    */
    SceneBase(const SceneType& _sceneType);

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

    //現在のシーン
    static SceneType mIsScene;

protected:

    //背景
    class FullPicture* mFullPicture;
    //マップ生成
    class MapCreate* mMapCreate;

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

   

public://ゲッターセッター
};