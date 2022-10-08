#pragma once

/*
* シーンの基底クラス
*/
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

    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="_nowScene">現在のシーンタイプ</param>
    SceneBase(const SceneType& _sceneType);
    // デストラクタ
    virtual ~SceneBase() {};

    /// <summary>
    /// 入力処理
    /// </summary>
    /// <param name="_inputState">入力状態</param>
    virtual void Input(const InputState& _state) {};

    /// <summary>
    /// 更新処理
    /// </summary>
    /// <returns>次のシーンのポインタ</returns>
    virtual SceneBase* update() = 0;

    static SceneType mIsScene;          // 現在のシーンタイプ

protected:
    class FullPicture* mFullPicture;    // 1920×1080サイズの画像UI
    class MapCreate* mMapCreate;        // マップ

    bool mGameSceneFlag;                // 次のシーンに遷移するか(true:する)
    bool mReturnTitleFlag;              // タイトルシーンに遷移するか(true:する)
};