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

	bool readTiledJson(std::vector<std::vector<int>>& _mapData, const char* _fileName, const char* _layerName);

	int  findLayerIndex(rapidjson::GenericArray<false, rapidjson::Value>& _layer, std::string& _layerName);

	//床マップデータ
	std::vector<std::vector<int>> mGroundMapData;
	std::vector<std::vector<int>> mGroundMapData2;
	std::vector<std::vector<int>> mGroundMapData3;
	//プレイヤーマップデータ
	std::vector<std::vector<int>> mPlayerMapData;
	//ろうそくマップデータ
	std::vector<std::vector<int>> mCandleMapData;

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
	const float MOffsetX;
	const float MOffsetY;
	float mOffsetZ;

	// 床のスケール
	const float MGroundScale;
	// ろうそくのスケール
	const float MCandleScale;
	// プレイヤーのスケール
	const float MPlayerScale;

	// ろうそくの初期ポジションｚ軸
	const float MCandleAddZPos;

	// プレイヤーの初期ポジションｚ軸
	const float MPlayerAddZPos;
};

