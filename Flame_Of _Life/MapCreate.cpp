/*
@brief	�C���N���[�h
*/
#include "pch.h"

/*
@fn	�R���X�g���N�^
*/
MapCreate::MapCreate()
	:GameObject(SceneBase::other, Tag::Other)
	, MGroundScale(10.0f)
	, MCandleScale(6.0f)
	, MPlayerScale(0.06f)
	, MCandleZPos(90.0f)
	, mOffsetX(265.0f)
	, mOffsetY(-380.0f)
	, mOffsetZ(0.0f)
	, mHeightChangeCount(0)
	, mTmpName(1)
	, flag(false)
	, mAdd(0.0f)
{
	mSizeX = 0;
	mSizeY = 0;
	mSizeZ = 0;
}

/*
@fn	�f�X�g���N�^
*/
MapCreate::~MapCreate()
{
	mGroundMapData.clear();
	
	mPlayerMapData.clear();
	mCandleMapData.clear();
}

/*
@fn		json�t�@�C����RapidJson�œǂݍ���Ń}�b�v�f�[�^���e�z��Ɋi�[����
@return	�t�@�C�����J������(bool�^)
*/
bool MapCreate::OpenFile()
{
	mScene = SceneBase::GetScene();

	//-----------------------------------------------
	//----------------tutorial-----------------------
	//-----------------------------------------------

	if (mScene == SceneBase::tutorial)
	{
		//���f�[�^�̓ǂݍ���
		if (!readTiledJson(mGroundMapData, "Assets/Config/choice.json", "Ground"))
		{
			printf("don't have Layer/Ground\n");
			return true;
		}

		mSizeX = mGroundMapData[0].size();
		mSizeY = mGroundMapData[0].size();
		//mSizeZ = mGroundMapData.size();

		//�v���C���[�f�[�^�̓ǂݍ���
		if (!readTiledJson(mPlayerMapData, "Assets/Config/choice.json", "Player"))
		{
			printf("don't have Layer/player\n");
			return true;
		}

		//�낤�����f�[�^�̓ǂݍ���
		if (!readTiledJson(mCandleMapData, "Assets/Config/choice.json", "Candle"))
		{
			printf("don't have Layer/Candle\n");
			return true;
		}

	}

	//-----------------------------------------------
	//----------------stage0l------------------------
	//-----------------------------------------------
	if (mScene == SceneBase::easy)
	{
		//���f�[�^�̓ǂݍ���
		if (!readTiledJson(mGroundMapData, "Assets/Config/easy.json", "Ground"))
		{
			printf("don't have Layer/Ground\n");
			return true;
		}
		

		mSizeX = mGroundMapData[0].size();
		mSizeY = mGroundMapData.size();
		//mSizeZ = mGroundMapData.size();


		//�v���C���[�f�[�^�̓ǂݍ���
		if (!readTiledJson(mPlayerMapData, "Assets/Config/easy.json", "Player"))
		{
			printf("don't have Layer/player\n");
			return true;
		}

		//�낤�����f�[�^�̓ǂݍ���
		if (!readTiledJson(mCandleMapData, "Assets/Config/easy.json", "Candle"))
		{
			printf("don't have Layer/Candle\n");
			return true;
		}

	}


	return false;
}

/*
@fn	���𐶐�����
*/
void MapCreate::CreateGround()
{
	for (float iz = 0; iz < mSizeY; iz++)
	{
		/*if (flag)
		{
			mOffsetY -= 10.0f;
			flag = false;
		}*/

		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mGroundMapData[(int)iz][(int)ix];

			if (mTmpName != name)
			{
				mOffsetZ -= 100.0f;
				flag = true;
				mTmpName = name;
			}

			Vector3 objectPos = Vector3(-mOffsetX * ix, mOffsetY * iz, mOffsetZ);
			const Vector3 objectSize = Vector3(MGroundScale, MGroundScale, MGroundScale);

			switch (mScene)
			{
			case SceneBase::tutorial:

				switch (name)
				{
				case(1):
					new Ground(objectPos, objectSize, ground, SceneBase::tutorial, false);
					break;
				}
				break;

			case SceneBase::easy:

				switch (name)
				{
				case(1):
					new Ground(objectPos, objectSize, ground, SceneBase::easy, false);
					break;
				default:
					new Ground(objectPos, objectSize, ground, SceneBase::easy, true);
					break;
				}

				break;
			}
		}
	}
}

/*
@fn	�v���C���[�𐶐�����
*/
void MapCreate::CreatePlayer()
{
	for (float iz = 0; iz < mSizeY; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mPlayerMapData[(int)iz][(int)ix];
			Vector3 objectPos = Vector3(-mOffsetX * ix, mOffsetY * iz, mOffsetZ);
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

			case SceneBase::easy:

				switch (name)
				{
				case(2):
					new Player(objectPos, objectSize, player, SceneBase::easy);
					break;
				}
				break;
			}
		}
	}

}

/*
@fn	�낤�����𐶐�����
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
			case SceneBase::tutorial:

				switch (name)
				{
				case(3):
					new Candle(objectPos, objectSize, candle, SceneBase::tutorial);
					break;
				}
				break;

			case SceneBase::easy:

				switch (name)
				{
				case(3):
					new Candle(objectPos, objectSize, candle, SceneBase::easy);
					break;
				}
				break;
			}
		}
	}

}


bool MapCreate::readTiledJson(std::vector<std::vector<int>>& _mapData, const char* _fileName, const char* _layerName)
{
	//RapidJson�h�L�������g�Ƃ��ĊJ���邩�H
	rapidjson::Document doc;
	if (!openJsonFile(doc, _fileName))
	{
		return false;
	}

	//�J����document��type��map���H
	if (!IsExistMemberAndValue(doc, "type", "map"))
	{
		return false;
	}
	//�J����document��layer�͂��邩�H
	if (!IsExistArrayName(doc, "layers"))
	{
		return false;
	}
	//layer�����擾
	auto layer = doc["layers"].GetArray();
	int layerSize = layer.Size();

	//layer������Y��layer�̓Y�����𒲂ׂ�
	std::string layerNameString(_layerName);
	int layerIndex = findLayerIndex(layer, layerNameString);
	if (layerIndex < 0)
	{
		return false;
	}

	//layer���Ƀf�[�^�͂��邩�H
	rapidjson::Value::ConstMemberIterator itr = layer[layerIndex].FindMember("data");
	if (itr == layer[layerIndex].MemberEnd())
	{
		printf("���C���[��:%s�Ƀ}�b�v�f�[�^������܂���\n", _layerName);
		return false;
	}

	//���C���[���rapidjson�z��쐬
	const rapidjson::Value& rapidArrayData = layer[layerIndex]["data"].GetArray();
	int width, height;
	width = layer[layerIndex]["width"].GetInt();
	height = layer[layerIndex]["height"].GetInt();

	//���[�U�[�z��m�ہ@�s�����A������̏��ԂɃT�C�Y�m��
	_mapData.resize(height);
	for (auto& mapIter : _mapData)
	{
		mapIter.resize(width);
	}

	//���[�U�[�z��i2�����j�Ƀf�[�^���R�s�[
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			//�Ȃ���ID��+1����Ă���̂ŕ␳����
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
