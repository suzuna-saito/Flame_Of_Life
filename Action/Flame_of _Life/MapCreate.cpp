/*
@brief	インクルード
*/
#include "pch.h"

/*
@fn	コンストラクタ
*/
MapCreate::MapCreate()
	:GameObject(SceneBase::Scene::other, Tag::Other)
	, MGroundScale(10.0f)
	, MCandleScale(6.0f)
	, MPlayerScale(0.06f)
	, MCatScale(4.0f)
	, MCharaScale(6.0f)
	, MLighterScale(2.0f)
	, MChairScale(0.7f)
	, MTreeScale(0.5f)
	, MSwordScale(2.0f)
	, MPlayerZPos(100.0f)
	, MCandleZPos(90.0f)
	, MItemZPos(110.0f)
	, mOffsetX(265.0f)
	, mOffsetY(-380.0f)
	, mOffsetZ(0.0f)
	, mChagePosY(100.0f)
	, mHardChagePosY(90.0f)
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

	if (mScene == SceneBase::Scene::tutorial)
	{
		//床データの読み込み
		if (!readTiledJson(mGroundMapData, "Assets/Config/choice.json", "Ground"))
		{
			printf("don't have Layer/Ground\n");
			return true;
		}

		mSizeX = mGroundMapData[0].size();
		mSizeY = mGroundMapData[0].size();
		//mSizeZ = mGroundMapData.size();

		//プレイヤーデータの読み込み
		if (!readTiledJson(mPlayerMapData, "Assets/Config/choice.json", "Player"))
		{
			printf("don't have Layer/player\n");
			return true;
		}

		//ろうそくデータの読み込み
		if (!readTiledJson(mCandleMapData, "Assets/Config/choice.json", "Candle"))
		{
			printf("don't have Layer/Candle\n");
			return true;
		}

	}

	//-----------------------------------------------
	//----------------EasyStage----------------------
	//-----------------------------------------------
	if (mScene == SceneBase::Scene::easy)
	{
		//床データの読み込み
		if (!readTiledJson(mGroundMapData, "Assets/Config/easy.json", "Ground"))
		{
			printf("don't have Layer/Ground\n");
			return true;
		}
		

		mSizeX = mGroundMapData[0].size();
		mSizeY = mGroundMapData.size();
		//mSizeZ = mGroundMapData.size();


		//プレイヤーデータの読み込み
		if (!readTiledJson(mPlayerMapData, "Assets/Config/easy.json", "Player"))
		{
			printf("don't have Layer/player\n");
			return true;
		}

		//ろうそくデータの読み込み
		if (!readTiledJson(mCandleMapData, "Assets/Config/easy.json", "Candle"))
		{
			printf("don't have Layer/Candle\n");
			return true;
		}

	}


	//-----------------------------------------------
	//----------------NormalStage--------------------
	//-----------------------------------------------
	if (mScene == SceneBase::Scene::normal)
	{
		//床データの読み込み
		if (!readTiledJson(mGroundMapData, "Assets/Config/normal.json", "Ground"))
		{
			printf("don't have Layer/Ground\n");
			return true;
		}


		mSizeX = mGroundMapData[0].size();
		mSizeY = mGroundMapData.size();
		//mSizeZ = mGroundMapData.size();


		//プレイヤーデータの読み込み
		if (!readTiledJson(mPlayerMapData, "Assets/Config/normal.json", "Player"))
		{
			printf("don't have Layer/player\n");
			return true;
		}

		//ろうそくデータの読み込み
		if (!readTiledJson(mCandleMapData, "Assets/Config/normal.json", "Candle"))
		{
			printf("don't have Layer/Candle\n");
			return true;
		}

	}

	//-----------------------------------------------
	//----------------HardStage----------------------
	//-----------------------------------------------
	if (mScene == SceneBase::Scene::hard)
	{
		//床データの読み込み
		if (!readTiledJson(mGroundMapData, "Assets/Config/hard01.json", "Ground"))
		{
			printf("don't have Layer/Ground\n");
			return true;
		}


		mSizeX = mGroundMapData[0].size();
		mSizeY = mGroundMapData.size();
		//mSizeZ = mGroundMapData.size();


		//プレイヤーデータの読み込み
		if (!readTiledJson(mPlayerMapData, "Assets/Config/hard01.json", "Player"))
		{
			printf("don't have Layer/player\n");
			return true;
		}

		//ろうそくデータの読み込み
		if (!readTiledJson(mCandleMapData, "Assets/Config/hard01.json", "Candle"))
		{
			printf("don't have Layer/Candle\n");
			return true;
		}

		//アイテムデータの読み込み
		if (!readTiledJson(mItemMapData, "Assets/Config/hard01.json", "Item"))
		{
			printf("don't have Layer/Item\n");
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

			Vector3 objectPos = Vector3(-mOffsetX * ix, mOffsetY * iz, mOffsetZ);
			const Vector3 objectSize = Vector3(MGroundScale, MGroundScale, MGroundScale);

			switch (mScene)
			{
			case SceneBase::Scene::tutorial:

				switch (name)
				{
				case(1):
					new Ground(objectPos, objectSize, Tag::ground, SceneBase::Scene::tutorial, Ground::groundTag::notAlpha);
					break;
				}
				break;

			case SceneBase::Scene::easy:

				switch (name)
				{
				case(1):
					new Ground(objectPos, objectSize, Tag::ground, SceneBase::Scene::easy, Ground::groundTag::notAlpha);
					break;
				default:
					new Ground(objectPos, objectSize, Tag::ground, SceneBase::Scene::easy, Ground::groundTag::RGBalpha);
					break;
				}
				break;

			case SceneBase::Scene::normal:

				switch (name)
				{
				case(1):
					new Ground(objectPos, objectSize, Tag::ground, SceneBase::Scene::normal, Ground::groundTag::notAlpha);
					break;
				default:
					new Ground(objectPos, objectSize, Tag::ground, SceneBase::Scene::normal, Ground::groundTag::RGBalpha);
					break;
				}
				break;

			case SceneBase::Scene::hard:

				switch (name)
				{
				case(0):
					break;
				case(1):
					new Ground(objectPos, objectSize, Tag::ground, SceneBase::Scene::hard, Ground::groundTag::notAlpha);
					break;
				case(36):
					new Ground(objectPos, objectSize, Tag::ground, SceneBase::Scene::hard, Ground::groundTag::alpha);
					break;
				default:
					new Ground(objectPos, objectSize, Tag::ground, SceneBase::Scene::hard, Ground::groundTag::RGBalpha);
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
			Vector3 objectPos = Vector3(-mOffsetX * ix, mOffsetY * iz, MPlayerZPos);
			Vector3 objectSize = Vector3(MPlayerScale, MPlayerScale, MPlayerScale);

			switch (mScene)
			{
			case SceneBase::Scene::tutorial:

				switch (name)
				{
				case(2):
					new Player(objectPos, objectSize, Tag::player, SceneBase::Scene::tutorial);
					break;
				}
				break;

			case SceneBase::Scene::easy:

				switch (name)
				{
				case(2):
					new Player(objectPos, objectSize, Tag::player, SceneBase::Scene::easy);
					break;
				}
				break;

			case SceneBase::Scene::normal:

				switch (name)
				{
				case(2):
					new Player(objectPos, objectSize, Tag::player, SceneBase::Scene::normal);
					break;
				}
				break;

			case SceneBase::Scene::hard:

				switch (name)
				{
				case(2):
					new Player(objectPos, objectSize, Tag::player, SceneBase::Scene::hard);
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
			Vector3 objectPos = Vector3(-mOffsetX * ix, mOffsetY * iz, MCandleZPos);
			Vector3 objectSize = Vector3(MCandleScale, MCandleScale, MCandleScale);

			switch (mScene)
			{
			case SceneBase::Scene::tutorial:

				switch (name)
				{
				case(3):
					new Candle(objectPos, objectSize, Tag::candle, SceneBase::Scene::tutorial);
					break;
				}
				break;

			case SceneBase::Scene::easy:

				switch (name)
				{
				case(3):
					new Candle(objectPos, objectSize, Tag::candle, SceneBase::Scene::easy);
					break;
				}
				break;

			case SceneBase::Scene::normal:

				switch (name)
				{
				case(3):
					new Candle(objectPos, objectSize, Tag::candle, SceneBase::Scene::normal);
					break;
				}
				break;

			case SceneBase::Scene::hard:

				switch (name)
				{
				case(3):
					new Candle(objectPos, objectSize, Tag::candle, SceneBase::Scene::hard);
					break;
				}
				break;
			}
		}
	}

}

/*
@fn	アイテムを生成する
*/
void MapCreate::CreateItem()
{
	for (float iz = 0; iz < mSizeY; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mItemMapData[(int)iz][(int)ix];
			Vector3 objectPos = Vector3(-mOffsetX * ix, mOffsetY * iz, MItemZPos);
			Vector3 objectSize = Vector3::Zero;

			switch (mScene)
			{
			case SceneBase::Scene::hard:

				switch (name)
				{
				case(18):  // いす
					objectSize = Vector3(MChairScale, MChairScale, MChairScale);
					new ItemChair(objectPos, objectSize, Tag::item, SceneBase::Scene::hard);
					break;
				case(19):  // ライト @@@
					objectPos = Vector3(-mOffsetX * ix, mOffsetY * iz, MItemZPos+200.0f);
					objectSize = Vector3(MLighterScale, MLighterScale, MLighterScale);
					new ItemLighter(objectPos, objectSize, Tag::item, SceneBase::Scene::hard);
					break;
				case(20):  // ミニキャラ
					objectSize = Vector3(MCharaScale, MCharaScale, MCharaScale);
					new ItemChara(objectPos, objectSize, Tag::item, SceneBase::Scene::hard);
					break;
				case(21):  // 木
					objectSize = Vector3(MTreeScale, MTreeScale, MTreeScale);
					new ItemTree(objectPos, objectSize, Tag::item, SceneBase::Scene::hard);
					break;
				case(22):  // 剣
					objectSize = Vector3(MSwordScale, MSwordScale, MSwordScale);
					new ItemSword(objectPos, objectSize, Tag::item, SceneBase::Scene::hard);
					break;
				case(23):  // 猫
					objectSize = Vector3(MCatScale, MCatScale, MCatScale);
					new ItemCat(objectPos, objectSize, Tag::item, SceneBase::Scene::hard);
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
