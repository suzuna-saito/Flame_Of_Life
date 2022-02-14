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
	@fn	背景を生成する
	*/
	void CreateBackGround();

	/*
	@fn	プレイヤーを生成する
	*/
	void CreatePlayer();

	/*
	@fn	ろうそくを生成する
	*/
	void CreateCandle();

	/*
	@fn	スイッチ（球体）を生成する
	*/
	void CreateSwitch();

	/*
	@fn	アイテムを生成する
	*/
	void CreateItem();
private:

	bool readTiledJson(vector<vector<int>>& _mapData, const char* _fileName, const char* _layerName);

	int  findLayerIndex(rapidjson::GenericArray<false, rapidjson::Value>& _layer, string& _layerName);

	// 背景のマップデータ
	vector<vector<int>> mBackGroundMapData;
	//床マップデータ
	vector<vector<int>> mGroundMapData;

	//プレイヤーマップデータ
	vector<vector<int>> mPlayerMapData;
	//ろうそくマップデータ
	vector<vector<int>> mCandleMapData;
	//スイッチマップデータ
	vector<vector<int>> mSwitchMapData;
	//アイテムマップデータ
	vector<vector<int>> mItemMapData;

	//現在のシーン
	SceneBase::Scene mScene;
	//幅のマップデータ
	int	mSizeX;
	//奥行のマップデータ
	int	mSizeY;
	//高さのマップデータ
	int	mSizeZ;

	// 背景用の床の高さ
	const float MBackGroundPosZ;
	const float MBackGroundInsidePosZ;

	//オブジェクトごとの距離
	float mOffsetX;
	float mOffsetY;
	float mOffsetZ;

	// 床のスケール
	const float MGroundScale;
	// ろうそくのスケール
	const float MCandleScale;
	// プレイヤーのスケール
	const float MPlayerScale;
	// スイッチのスケール
	const float MSphereScale;
	//アイテム（パズル）のスケール
	const float MItemScale;

	// 地面に埋まらないためにプレイヤーに足してあげるポジションｚ軸
	const float MPlayerZPos;
	// 地面に埋まらないためにろうそくに足してあげるポジションｚ軸
	const float MCandleZPos;
	// 地面に埋まらないためにアイテムに足してあげるポジションｚ軸
	const float MItemZPos;
};

