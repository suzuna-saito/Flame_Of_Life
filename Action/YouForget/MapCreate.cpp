/*
@brief	インクルード
*/
#include "pch.h"

/*
@fn	コンストラクタ
*/
MapCreate::MapCreate()
	:GameObject(SceneBase::Scene::other, Tag::Other)
	, mScene()
	, MGroundScale(10.0f)
	, MCandleScale(6.0f)
	, MPlayerScale(0.06f)
	, MSphereScale(5.0f)
	, MCatScale(4.0f)
	, MCharaScale(6.0f)
	, MLighterScale(2.0f)
	, MChairScale(0.7f)
	, MTreeScale(0.5f)
	, MSwordScale(10.0f)
	, MItemScale(18.0f)
	, MPlayerZPos(200.0f)
	, MCandleZPos(90.0f)
	, MItemZPos(200.0f)
	, mOffsetX(265.0f)
	, mOffsetY(-380.0f)
	, mOffsetZ(0.0f)
	, mChagePosY(100.0f)
	, mHardChagePosY(90.0f)
	, mItemNum(0)
	, count(0)
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
	mBackGroundMapData.clear();
	mGroundMapData.clear();
	mPlayerMapData.clear();
	mCandleMapData.clear();
	mSwitchMapData.clear();
	mItemMapData.clear();
}

/*
@fn		jsonファイルをRapidJsonで読み込んでマップデータを各配列に格納する
@return	ファイルを開けたか(bool型)
*/
bool MapCreate::OpenFile()
{
	mScene = SceneBase::GetScene();

	// 現在のシーンによって読み込むファイル名を変える
	const char *filename = nullptr;
	switch (mScene)
	{
	//----------------tutorial-----------------------
	case SceneBase::Scene::tutorial:
		filename = "Assets/Config/tutorial.json";
		break;
	//----------------FirstStage---------------------
	case SceneBase::Scene::first:
		filename = "Assets/Config/first.json";
		break;
	//----------------SecondStage--------------------
	case SceneBase::Scene::second:
		filename = "Assets/Config/easy.json";
		break;
	//----------------ThirdStage---------------------
	case SceneBase::Scene::third:
		filename = "Assets/Config/second.json";
		break;
	default:
		break;
	}

	//背景データの読み込み
	if (!readTiledJson(mBackGroundMapData, filename, "BackGround"))
	{
		printf("don't have Layer/BackGround\n");
		return true;
	}

	mSizeX = mBackGroundMapData[0].size();
	mSizeY = mBackGroundMapData.size();

	//床データの読み込み
	if (!readTiledJson(mGroundMapData, filename, "Ground"))
	{
		printf("don't have Layer/Ground\n");
		return true;
	}

	//プレイヤーデータの読み込み
	if (!readTiledJson(mPlayerMapData, filename, "Player"))
	{
		printf("don't have Layer/player\n");
		return true;
	}

	//ろうそくデータの読み込み
	if (!readTiledJson(mCandleMapData, filename, "Candle"))
	{
		printf("don't have Layer/Candle\n");
		return true;
	}

	//スイッチデータの読み込み
	if (!readTiledJson(mSwitchMapData, filename, "Switch"))
	{
		printf("don't have Layer/Switch\n");
		return true;
	}

	// チュートリアルシーンにはアイテムがないので、チュートリアル以外だったら
	if (mScene != SceneBase::Scene::tutorial)
	{
		//アイテムデータの読み込み
		if (!readTiledJson(mItemMapData, filename, "Item"))
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
	/* 乱数の種を初期化 */
	srand((unsigned)time(NULL));

	//if(mScene == )

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
				// 床の種類の数を設定 @@@ マジックナンバー
				Ground::mTypeNum = 1;

				switch (name)
				{
				case(0):
					break;
				case(1):
					new Ground(objectPos, objectSize, Tag::ground, SceneBase::Scene::tutorial, Ground::groundTag::notAlpha);
					break;
				default:
					new Ground(objectPos, objectSize, Tag::ground, SceneBase::Scene::tutorial, Ground::groundTag::RGBalpha);
					break;
				}
				break;

			case SceneBase::Scene::first:
				Ground::mTypeNum = 1;

				switch (name)
				{
				case(0):
					break;
				case(1):
					new Ground(objectPos, objectSize, Tag::ground, SceneBase::Scene::first, Ground::groundTag::notAlpha);
					break;
				default:
					new Ground(objectPos, objectSize, Tag::ground, SceneBase::Scene::first, Ground::groundTag::RGBalpha);
					break;
				}
				break;

			case SceneBase::Scene::second:
				Ground::mTypeNum = 2;

				switch (name)
				{
				case(0):
					break;
				case(1):
					new Ground(objectPos, objectSize, Tag::ground, SceneBase::Scene::second, Ground::groundTag::notAlpha);
					break;
				default:
					new Ground(objectPos, objectSize, Tag::ground, SceneBase::Scene::second, Ground::groundTag::RGBalpha);
					break;
				}
				break;

			case SceneBase::Scene::third :
				Ground::mTypeNum = 2;

				switch (name)
				{
				case(0):
					break;
				case(1):
					new Ground(objectPos, objectSize, Tag::ground, SceneBase::Scene::third, Ground::groundTag::notAlpha);
					break;
				default:
					new Ground(objectPos, objectSize, Tag::ground, SceneBase::Scene::third, Ground::groundTag::RGBalpha);
					break;
				}
				break;
			}
		}
	}
}

/*
@fn	背景を生成する
*/
void MapCreate::CreateBackGround()
{
	for (float iz = 0; iz < mSizeY; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mBackGroundMapData[(int)iz][(int)ix];
			// @@@ マジックナンバー直せ
			Vector3 objectPos = Vector3(-mOffsetX * ix, mOffsetY * iz, -850.0f);
			Vector3 objectPos02 = Vector3(-mOffsetX * ix, mOffsetY * iz, -1200.0f);
			Vector3 objectSize = Vector3(MGroundScale, MGroundScale, MGroundScale);
			
			if (name == 35)
			{
				new BackGround(objectPos, objectSize, Tag::Other, SceneBase::GetScene(), name);
			}
			else if (name == 36)
			{
				new BackGround(objectPos02, objectSize, Tag::Other, SceneBase::GetScene(), name);
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

			if (name == 2)
			{
				new Player(objectPos, objectSize, Tag::player, SceneBase::GetScene());
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

			if (name == 3)
			{
				new Candle(objectPos, objectSize, Tag::candle, SceneBase::GetScene());
			}

		}
	}

}
/*
@fn	スイッチを生成する
*/
void MapCreate::CreateSwitch()
{
	for (float iz = 0; iz < mSizeY; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mSwitchMapData[(int)iz][(int)ix];
			Vector3 objectPos = Vector3(-mOffsetX * ix, mOffsetY * iz, 0.0f);
			Vector3 objectSize = Vector3(MGroundScale, MGroundScale, MGroundScale);

			if (name == 18)
			{
				new Switch(objectPos, objectSize, Tag::Switch, SceneBase::GetScene(), Switch::switchColor::red);
			}
			else if (name == 24)
			{
				new Switch(objectPos, objectSize, Tag::Switch, SceneBase::GetScene(), Switch::switchColor::green);
			}

		}
	}

}

/*
@fn	アイテムを生成する
*/
void MapCreate::CreateItem()
{
	int ItemNumber = 0;
	for (float iz = 0; iz < mSizeY; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mItemMapData[(int)iz][(int)ix];
			Vector3 objectPos = Vector3(-mOffsetX * ix, mOffsetY * iz, MItemZPos);
			Vector3 objectSize = Vector3(MItemScale, MItemScale, MItemScale);

			if (name == 7)
			{
				new Item(objectPos, objectSize, Tag::item, SceneBase::GetScene(), ItemNumber);
				ItemNumber++;
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
