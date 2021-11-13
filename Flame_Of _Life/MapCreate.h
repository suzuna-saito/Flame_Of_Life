/*
@brief	�v���v���Z�b�T
*/
#pragma once


class MapCreate : public GameObject
{
public:

	/*
	@fn	�R���X�g���N�^
	*/
	MapCreate();

	/*
	@fn	�f�X�g���N�^
	*/
	~MapCreate();

	/*
	@fn		json�t�@�C����RapidJson�œǂݍ���Ń}�b�v�f�[�^���e�z��Ɋi�[����
	@return	�t�@�C�����J������(bool�^)
	*/
	bool OpenFile();

	/*
	@fn	���𐶐�����
	*/
	void CreateGround();

	/*
	@fn	�v���C���[�𐶐�����
	*/
	void CreatePlayer();

	/*
	@fn	�낤�����𐶐�����
	*/
	void CreateCandle();
private:

	bool readTiledJson(vector<vector<int>>& _mapData, const char* _fileName, const char* _layerName);

	int  findLayerIndex(rapidjson::GenericArray<false, rapidjson::Value>& _layer, string& _layerName);

	//���}�b�v�f�[�^
	vector<vector<int>> mGroundMapData;

	//�v���C���[�}�b�v�f�[�^
	vector<vector<int>> mPlayerMapData;
	//�낤�����}�b�v�f�[�^
	vector<vector<int>> mCandleMapData;

	// �O�̃f�[�^
	int mTmpName;
	// ���̃f�[�^
	int mNowName;

	//���݂̃V�[��
	int mScene;
	//���̃}�b�v�f�[�^
	int	mSizeX;
	//�����̃}�b�v�f�[�^
	int	mSizeY;
	//���s�̃}�b�v�f�[�^
	int	mSizeZ;

	// ���̍��������炷�J�E���g
	int mHeightChangeCount;

	//�I�u�W�F�N�g���Ƃ̋���
	float mOffsetX;
	float mOffsetY;
	float mOffsetZ;

	float mYAddPos;

	// ���̃X�P�[��
	const float MGroundScale;
	// �낤�����̃X�P�[��
	const float MCandleScale;
	// �v���C���[�̃X�P�[��
	const float MPlayerScale;

	// �낤�����̏����|�W�V��������
	const float MCandleZPos;
	// �v���C���[�̏����|�W�V��������
	const float MPlayerZPos;

	bool flag;

	float mAdd;
};

