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

	//床マップデータ
	vector<vector<int>> mGroundMapData;

	//プレイヤーマップデータ
	vector<vector<int>> mPlayerMapData;
	//ろうそくマップデータ
	vector<vector<int>> mCandleMapData;
	//スイッチ（球体）マップデータ
	vector<vector<int>> mSwitchMapData;
	//アイテムマップデータ
	vector<vector<int>> mItemMapData;

	//現在のシーン
	SceneBase::Scene mScene;
	//幅のマップデータ
	int	mSizeX;
	//高さのマップデータ
	int	mSizeY;
	//奥行のマップデータ
	int	mSizeZ;

	// 床の高さをずらす
	float mChagePosY;
	float mHardChagePosY;

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
	// スイッチ（球体）のスケール
	const float MSwitchScale;

	/* アイテム関連 */
	// 猫（アイテム）のスケール
	const float MCatScale;
	const float MCharaScale;
	const float MLighterScale;
	const float MChairScale;
	const float MTreeScale;
	const float MSwordScale;
	
	int mItemCount;

	const float MPlayerZPos;
	// 地面に埋まらないためにろうそくに足してあげるポジションｚ軸
	const float MCandleZPos;
	// 地面に埋まらないためにアイテムに足してあげるポジションｚ軸
	const float MItemZPos;
};

