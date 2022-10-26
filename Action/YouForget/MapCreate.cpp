/*
@brief	インクルード
*/
#include "pch.h"

/*
@fn	コンストラクタ
*/
MapCreate::MapCreate(const SceneBase::SceneType& _sceneType)
	: GameObject()
	, mScene()
	, MGroundScale(10.0f)
	, MCandleScale(6.0f)
	, MPlayerScale(0.06f)
	, MSphereScale(5.0f)
	, MItemScale(18.0f)
	, MBackGroundPosZ(-850.0f)
	, MBackGroundInsidePosZ(-1200.0f)
	, MPlayerZPos(150.0f)
	, MCandleZPos(90.0f)
	, MItemZPos(200.0f)
	, mOffsetX(265.0f)
	, mOffsetY(-380.0f)
	, mOffsetZ(0.0f)
	, mSizeX(0)
	, mSizeY(0)
	, mSizeZ(0)
{
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
	mScene = SceneBase::mIsSceneType;

	// 現在のシーンによって読み込むファイル名を変える
	const char *filename = nullptr;
	switch (mScene)
	{
	//----------------tutorial-----------------------
	case SceneBase::SceneType::eTutorial:
		filename = "Assets/Config/tutorial.json";
		break;
	//----------------FirstStage---------------------
	case SceneBase::SceneType::eFirst:
		filename = "Assets/Config/first.json";
		break;
	//----------------SecondStage--------------------
	case SceneBase::SceneType::eSecond:
		filename = "Assets/Config/easy.json";
		break;
	//----------------ThirdStage---------------------
	case SceneBase::SceneType::eThird:
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
	if (mScene != SceneBase::SceneType::eTutorial)
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
@fn	背景を生成する
*/
void MapCreate::CreateBackGround()
{
	for (float iz = 0; iz < mSizeY; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mBackGroundMapData[(int)iz][(int)ix];
			
			const Vector3 objectPos = Vector3(-mOffsetX * ix, mOffsetY * iz, MBackGroundPosZ);
			const Vector3 objectPos02 = Vector3(-mOffsetX * ix, mOffsetY * iz, MBackGroundInsidePosZ);
			const Vector3 objectSize = Vector3(MGroundScale, MGroundScale, MGroundScale);

			if (name == 35)
			{
				new BackGround(objectPos, BackGround::BackGroundType::eBGtypeOne);
			}
			else if (name == 36)
			{
				new BackGround(objectPos02, BackGround::BackGroundType::eBGtypeTwo);
			}
		}
	}
}


/*
@fn	床を生成する
*/
void MapCreate::CreateGround()
{
	/* 乱数の種を初期化 */
	srand((unsigned)time(NULL));

	// 床の種類の数をステージによって設定
	if (mScene == SceneBase::SceneType::eTutorial ||
		mScene == SceneBase::SceneType::eFirst)
	{
		// 床の種類が1つ
		Ground::mTypeNum = 1;
	}
	else if (mScene == SceneBase::SceneType::eSecond ||
		mScene == SceneBase::SceneType::eThird)
	{
		// 床の種類が2つ
		Ground::mTypeNum = 2;
	}

	for (float iz = 0; iz < mSizeY; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mGroundMapData[(int)iz][(int)ix];

			const Vector3 objectPos = Vector3(-mOffsetX * ix, mOffsetY * iz, mOffsetZ);
			const Vector3 objectSize = Vector3(MGroundScale, MGroundScale, MGroundScale);

			if (name == 1)
			{
				new Ground(objectPos, objectSize, ObjTag::eGround, SceneBase::mIsSceneType, Ground::groundTag::notAlpha);
			}
			else if (name == 4)
			{
				new Ground(objectPos, objectSize, ObjTag::eGround, SceneBase::mIsSceneType, Ground::groundTag::RGBalpha);
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

			const Vector3 objectPos = Vector3(-mOffsetX * ix, mOffsetY * iz, MPlayerZPos);
			const Vector3 objectSize = Vector3(MPlayerScale, MPlayerScale, MPlayerScale);

			if (name == 2)
			{
				new Player(objectPos, objectSize, ObjTag::ePlayer, SceneBase::mIsSceneType);
			}
		}
	}
}

void MapCreate::CreateCandle()
{
	for (float iz = 0; iz < mSizeY; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mCandleMapData[(int)iz][(int)ix];

			const Vector3 objectPos = Vector3(-mOffsetX * ix, mOffsetY * iz, MCandleZPos+450.0f);

			if (name == 3)
			{
				new GoalObj(objectPos);
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

			const Vector3 objectPos = Vector3(-mOffsetX * ix, mOffsetY * iz, 0.0f);

			if (name == 18)
			{
				new Switch(objectPos,Switch::switchColor::red);
			}
			else if (name == 24)
			{
				new Switch(objectPos,Switch::switchColor::green);
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

			const Vector3 objectPos = Vector3(-mOffsetX * ix, mOffsetY * iz, MItemZPos);
			const Vector3 objectSize = Vector3(MItemScale, MItemScale, MItemScale);

			if (name == 7)
			{
				new Item(objectPos, objectSize, ObjTag::ePuzzle, SceneBase::mIsSceneType, ItemNumber);
				ItemNumber++;
			}
		}
	}

}

bool MapCreate::readTiledJson(std::vector<std::vector<int>>& _mapData, const char* _fileName, const char* _layerName)
{
	//RapidJsonドキュメントとして開けるか？
	rapidjson::Document doc;
	if (!OpenJsonFile(doc, _fileName))
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
