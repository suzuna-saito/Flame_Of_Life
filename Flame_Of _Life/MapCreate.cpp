/*
@brief	インクルード
*/
#include "pch.h"

/*
@fn	コンストラクタ
*/
MapCreate::MapCreate() 
	:GameObject(SceneBase::other, Tag::Other)
	, MGroundScale(6.0f)
	, MCandleScale(4.0f)
	, MPlayerScale(5.0f)
	, MCandleZPos(60.0f)
	, MOffsetX(160.0f)
	, MOffsetY(-220.0f)
{
	mSizeX = 0;
	mSizeY = 0;
	mSizeZ = 0;
}

/*
@fn	デストラクタ
*/
MapCreate::~MapCreate()
{
	mGroundMapData.clear();
	mGroundMapData2.clear();
	mGroundMapData3.clear();
	mPlayerMapData.clear();
	mCandleMapData.clear();
}

/*
@fn		jsonファイルをRapidJsonで読み込んでマップデータを各配列に格納する
@return	ファイルを開けたか(bool型)
*/
bool MapCreate::OpenFile()
{
	mScene = SceneBase::GetScene();

	//-----------------------------------------------
	//----------------tutorial-----------------------
	//-----------------------------------------------

	if (mScene == SceneBase::tutorial)
	{
		//床データの読み込み
		if (!readTiledJson(mGroundMapData, "Assets/Config/test.json", "Ground"))
		{
			printf("don't have Layer/Ground\n");
			return true;
		}

		mSizeX = mGroundMapData[0].size();
		mSizeY = mGroundMapData[0].size();
		//mSizeZ = mGroundMapData.size();

		//プレイヤーデータの読み込み
		if (!readTiledJson(mPlayerMapData, "Assets/Config/test.json", "Player"))
		{
			printf("don't have Layer/player\n");
			return true;
		}

		//ろうそくデータの読み込み
		if (!readTiledJson(mCandleMapData, "Assets/Config/test.json", "Candle"))
		{
			printf("don't have Layer/Candle\n");
			return true;
		}

	}

	//-----------------------------------------------
	//----------------stage0l------------------------
	//-----------------------------------------------
	if (mScene == SceneBase::stage01)
	{
		//床データの読み込み
		if (!readTiledJson(mGroundMapData, "Assets/Config/map.json", "Ground"))
		{
			printf("don't have Layer/Ground\n");
			return true;
		}
		if (!readTiledJson(mGroundMapData2, "Assets/Config/map.json", "Ground2"))
		{
			printf("don't have Layer/Ground2\n");
			return true;
		}
		if (!readTiledJson(mGroundMapData3, "Assets/Config/map.json", "Ground3"))
		{
			printf("don't have Layer/Ground3\n");
			return true;
		}

		mSizeX = mGroundMapData[0].size();
		mSizeY = mGroundMapData[0].size();
		//mSizeZ = mGroundMapData.size();

		//プレイヤーデータの読み込み
		if (!readTiledJson(mPlayerMapData, "Assets/Config/map.json", "Player"))
		{
			printf("don't have Layer/player\n");
			return true;
		}

		//ろうそくデータの読み込み
		if (!readTiledJson(mCandleMapData, "Assets/Config/map.json", "Candle"))
		{
			printf("don't have Layer/Candle\n");
			return true;
		}

	}


	return false;
}

/*
@fn	床を生成する
*/
void MapCreate::CreateGround()
{
	for (float iz = 0; iz < mSizeY; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mGroundMapData[(int)iz][(int)ix];
			const Vector3 objectPos = Vector3(-MOffsetX * ix, MOffsetY * iz, 0.0f);
			const Vector3 objectSize = Vector3(MGroundScale, MGroundScale, MGroundScale);

			switch (mScene)
			{
			case SceneBase::tutorial:

				switch (name)
				{
				case(1):
					new Ground(objectPos, objectSize, ground, SceneBase::tutorial);
					break;
				}
				break;

			case SceneBase::stage01:

				switch (name)
				{
				case(1):
					new Ground(objectPos, objectSize, ground, SceneBase::stage01);
					break;
				case(3):
					new Ground(objectPos+Vector3(0.0f,0.0f,3.0f), objectSize, ground, SceneBase::stage01);
					break;
				case(4):
					new Ground(objectPos/* + Vector3(0.0f, 0.0f, 10.0f)*/, objectSize, ground, SceneBase::stage01);
					break;
				case(5):
					new Ground(objectPos/* + Vector3(0.0f, 0.0f, 15.0f)*/, objectSize, ground, SceneBase::stage01);
					break;
				case(6):
					new Ground(objectPos/* + Vector3(0.0f, 0.0f, 20.0f)*/, objectSize, ground, SceneBase::stage01);
					break;
				case(7):
					new Ground(objectPos /*+ Vector3(0.0f, 0.0f, 25.0f)*/, objectSize, ground, SceneBase::stage01);
					break;
				}

				break;
			}
		}
	}
}


/*
@fn	プレイヤーを生成する
*/
void MapCreate::CreatePlayer()
{
	for (float iz = 0; iz < mSizeY; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mPlayerMapData[(int)iz][(int)ix];
			Vector3 objectPos = Vector3(-MOffsetX * ix, MOffsetY * iz, MCandleZPos);
			Vector3 objectSize = Vector3(MPlayerScale, MPlayerScale, MPlayerScale);

			switch (mScene)
			{
			case SceneBase::tutorial:

				switch (name)
				{
				case(2):
					new Player(objectPos, objectSize, player, SceneBase::tutorial);
					break;
				}
				break;

			case SceneBase::stage01:

				switch (name)
				{
				case(2):
					new Player(objectPos, objectSize, player, SceneBase::stage01);
					break;
				}
				break;
			}
		}
	}

}

/*
@fn	ろうそくを生成する
*/
void MapCreate::CreateCandle()
{
	for (float iz = 0; iz < mSizeY; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mCandleMapData[(int)iz][(int)ix];
			Vector3 objectPos = Vector3(-MOffsetX * ix, MOffsetY * iz, MCandleZPos);
			Vector3 objectSize = Vector3(MCandleScale, MCandleScale, MCandleScale);

			switch (mScene)
			{
			case SceneBase::tutorial:

				switch (name)
				{
				case(3):
					new Candle(objectPos, objectSize, candle, SceneBase::tutorial);
					break;
				}
				break;
			}
		}
	}

}


bool MapCreate::readTiledJson(std::vector<std::vector<int>>& _mapData, const char* _fileName, const char* _layerName)
{
	//RapidJsonドキュメントとして開けるか？
	rapidjson::Document doc;
	if (!openJsonFile(doc, _fileName))
	{
		return false;
	}

	//開いたdocumentのtypeはmapか？
	if (!IsExistMemberAndValue(doc, "type", "map"))
	{
		return false;
	}
	//開いたdocumentにlayerはあるか？
	if (!IsExistArrayName(doc, "layers"))
	{
		return false;
	}
	//layer数を取得
	auto layer = doc["layers"].GetArray();
	int layerSize = layer.Size();

	//layer名から該当layerの添え字を調べる
	std::string layerNameString(_layerName);
	int layerIndex = findLayerIndex(layer, layerNameString);
	if (layerIndex < 0)
	{
		return false;
	}

	//layer内にデータはあるか？
	rapidjson::Value::ConstMemberIterator itr = layer[layerIndex].FindMember("data");
	if (itr == layer[layerIndex].MemberEnd())
	{
		printf("レイヤー名:%sにマップデータがありません\n", _layerName);
		return false;
	}

	//レイヤーよりrapidjson配列作成
	const rapidjson::Value& rapidArrayData = layer[layerIndex]["data"].GetArray();
	int width, height;
	width = layer[layerIndex]["width"].GetInt();
	height = layer[layerIndex]["height"].GetInt();

	//ユーザー配列確保　行方向、列方向の順番にサイズ確保
	_mapData.resize(height);
	for (auto& mapIter : _mapData)
	{
		mapIter.resize(width);
	}

	//ユーザー配列（2次元）にデータをコピー
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			//なぜかIDが+1ずれているので補正する
			_mapData[y][x] = rapidArrayData[y * width + x].GetInt();
		}
	}
	return true;
}

int MapCreate::findLayerIndex(rapidjson::GenericArray<false, rapidjson::Value>& _layer, std::string& _layerName)
{
	int layerSize = _layer.Size();
	int i;
	std::string layerNameString(_layerName);
	for (i = 0; i < layerSize; i++)
	{
		std::string currentLayerName = _layer[i]["name"].GetString();
		printf("%s\n", currentLayerName.c_str());
		if (layerNameString == currentLayerName)
		{
			break;
		}
	}
	if (i == layerSize)
	{
		return -1;
	}
	return i;
}
