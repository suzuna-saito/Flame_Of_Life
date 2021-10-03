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

	void CreateGround();

	/*
	@fn	プレイヤーを生成する
	*/
	void CreatePlayer();


private:

	bool readTiledJson(std::vector<std::vector<int>>& _mapData, const char* _fileName, const char* _layerName);

	int  findLayerIndex(rapidjson::GenericArray<false, rapidjson::Value>& _layer, std::string& _layerName);

	//床マップデータ
	std::vector<std::vector<int>> mGroundMapData;
	//プレイヤーマップデータ
	std::vector<std::vector<int>> mPlayerMapData;

	//現在のシーン
	int mScene;
	//幅のマップデータ
	int	mSizeX;
	//高さのマップデータ
	int	mSizeY;
	//奥行のマップデータ
	int	mSizeZ;

	//オブジェクトごとの距離
	float mOffset;
};

