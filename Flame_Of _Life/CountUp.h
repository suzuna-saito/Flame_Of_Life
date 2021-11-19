#pragma once

// クラスの前方宣言
class SpriteComponent;
class Texture;
class Font;

/*
@file CountUp.h
@brief カウントダウンフォントの表示を行う
*/
class CountUp: public GameObject
{
public:

    /*
    @brief	コンストラクタ
    @param	カウントする時間
    @param	現在のシーン
    */
    CountUp(SceneBase::Scene _sceneTag);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~CountUp();

    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;


private:
    // カウントを開始するかのフラグ変数
    static bool countStartFlag;

    // SpriteComponent変数
    SpriteComponent* sprite;
    // フレームカウント
    int frameCount;
    // 計測する時間
    int time;

    // 時間を1進めるタイミングを比較する定数
    const int AddTimeCount;

public://ゲッターセッター

    /*
    @fn countStartFlagのsetter関数
    @brief	countStartFlagに値をセット
    @param	_countStartFlag カウントを開始するかのフラグ
    */
    static void SetCountStartFlag(bool _countStartFlag) { countStartFlag = _countStartFlag; }

    /*
    @fn countStartFlagのgetter関数
    @brief	countStartFlagを取得
    @return	カウントを開始するかのフラグ
    */
    static bool GetCountStartFlag() { return countStartFlag; }

};