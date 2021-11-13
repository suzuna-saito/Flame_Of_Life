/*
@brief	プリプロセッサ
*/
#pragma once


class MapCreate : public GameObject
{
public:

	/*
	@fn	コンストラクタ
	*/
	MapCreate();

	/*
	@fn	デストラクタ
	*/
	~MapCreate();

	/*
	@fn		jsonファイルをRapidJsonで読み込んでマップデータを各配列に格納する
	@return	ファイルを開けたか(bool型)
	*/
	bool OpenFile();

	/*
	@fn	床を生成する
	*/
	void CreateGround();

	/*
	@fn	プレイヤーを生成する
	*/
	void CreatePlayer();

	/*
	@fn	ろうそくを生成する
	*/
	void CreateCandle();
private:

	bool readTiledJson(vector<vector<int>>& _mapData, const char* _fileName, const char* _layerName);

	int  findLayerIndex(rapidjson::GenericArray<false, rapidjson::Value>& _layer, string& _layerName);

	//床マップデータ
	vector<vector<int>> mGroundMapData;

	//プレイヤーマップデータ
	vector<vector<int>> mPlayerMapData;
	//ろうそくマップデータ
	vector<vector<int>> mCandleMapData;

	// 前のデータ
	int mTmpName;
	// 今のデータ
	int mNowName;

	//現在のシーン
	int mScene;
	//幅のマップデータ
	int	mSizeX;
	//高さのマップデータ
	int	mSizeY;
	//奥行のマップデータ
	int	mSizeZ;

	// 床の高さをずらすカウント
	int mHeightChangeCount;

	//オブジェクトごとの距離
	float mOffsetX;
	float mOffsetY;
	float mOffsetZ;

	float mYAddPos;

	// 床のスケール
	const float MGroundScale;
	// ろうそくのスケール
	const float MCandleScale;
	// プレイヤーのスケール
	const float MPlayerScale;

	// ろうそくの初期ポジションｚ軸
	const float MCandleZPos;
	// プレイヤーの初期ポジションｚ軸
	const float MPlayerZPos;

	bool flag;

	float mAdd;
};

