#include "pch.h"

bool Skeleton::Load(const char* _fileName)
{
	// ��̓I�u�W�F�N�g�쐬
	rapidjson::Document doc;
	// filename����e�L�X�g�t�@�C���Ƃ��ēǂݍ��݁ArapidJSON�ɉ�͂�����
	// �t�@�C�����J���Ȃ�������
	if (!OpenJsonFile(doc, _fileName))
	{
		printf("�X�P���g���t�@�C���ł�\n");
		return false;	// false��Ԃ�
	}

	// version��int�Ŏ擾����
	int ver = doc["version"].GetInt();
	// ���^�f�[�^�̃`�F�b�N�B�o�[�W�������P����Ȃ�������
	if (ver != 1)
	{
		printf("�X�P���g�� %s �̃t�H�[�}�b�g���s���ł�", _fileName);
		return false;	// false��Ԃ�
	}

	// bonecount �{�[�����̎擾
	const rapidjson::Value& bonecount = doc["bonecount"];
	if (!bonecount.IsUint())
	{
		printf("�X�P���g�� %s �͍��������Ă��܂���", _fileName);
		return false;	// false��Ԃ�
	}
	// ��������
	size_t count = bonecount.GetUint();

	// �{�[������MAX_SKELETON_BONES�𒴂��Ă����ꍇ (196�{���ő�)
	if (count > MAX_SKELETON_BONES)
	{
		printf("�X�P���g�� %s ���ő卜���𒴂��Ă��܂�", _fileName);
		return false;	// false��Ԃ�
	}

	// �{�[���z��̃L���p�V�e�B�������ɍ��킹�ĕύX����
	mBones.reserve(count);

	// �{�[���z��̎擾
	const rapidjson::Value& bones = doc["bones"];
	if (!bones.IsArray())
	{
		printf("�X�P���g�� %s �͍��̔z��������Ă��Ȃ�", _fileName);
		return false;	// false��Ԃ�
	}

	// �{�[���z��̃T�C�Y�ƃ{�[�������قȂ�ꍇ�̓G���[��Ԃ�
	if (bones.Size() != count)
	{
		printf("�X�P���g�� %s �́A���̐��ƍ��̐����s��v�ł�", _fileName);
		return false;	// false��Ԃ�
	}

	// �{�[���̍��i��`�ۑ��p
	Bone temp;

	// �{�[���z�񐔕����[�v
	for (rapidjson::SizeType i = 0; i < count; ++i)
	{
		// �{�[�����ǂ߂邩�H
		if (!bones[i].IsObject())
		{
			printf("�X�P���g�� %s�̍��i %d �͖����ł�", _fileName, i);
			return false;	// false��Ԃ�
		}

		// "name" �{�[����
		const rapidjson::Value& name = bones[i]["name"];
		temp.mName = name.GetString();

		// "parent" �e�{�[��ID
		const rapidjson::Value& parent = bones[i]["parent"];
		temp.mParent = parent.GetInt();

		// "bindpose" �o�C���h�|�[�Y
		const rapidjson::Value& bindpose = bones[i]["bindpose"];
		if (!bindpose.IsObject())
		{
			printf("�X�P���g�� %s�̍��i %d �͖����ł�", _fileName, i);
			return false;	// false��Ԃ�
		}

		// �o�C���h�|�[�Y�̉�]�A�ʒu
		const rapidjson::Value& rot = bindpose["rot"];		// ��]
		const rapidjson::Value& trans = bindpose["trans"];	// �ʒu

		// ��]�ƈʒu���z�񂶂�Ȃ�������G���[�Ԃ�
		if (!rot.IsArray() || !trans.IsArray())
		{
			printf("�X�P���g�� %s�̍��i %d �͖����ł�", _fileName, i);
			return false;	// false��Ԃ�
		}

		// �o�C���h�|�[�Y�̉�]����
		temp.mLocalBindPose.mRotation.x = static_cast<float>(rot[0].GetDouble());
		temp.mLocalBindPose.mRotation.y = static_cast<float>(rot[1].GetDouble());
		temp.mLocalBindPose.mRotation.z = static_cast<float>(rot[2].GetDouble());
		temp.mLocalBindPose.mRotation.w = static_cast<float>(rot[3].GetDouble());

		// �o�C���h�|�[�Y�̈ړ�����
		temp.mLocalBindPose.mTranslation.x = static_cast<float>(trans[0].GetDouble());
		temp.mLocalBindPose.mTranslation.y = static_cast<float>(trans[1].GetDouble());
		temp.mLocalBindPose.mTranslation.z = static_cast<float>(trans[2].GetDouble());

		// �{�[���z��Ɋi�[����
		mBones.emplace_back(temp);
	}

	// �����Ń{�[���z��͓ǂ݂��܂�Ă���̂ŁA�t�o�C���h�|�[�Y�s����v�Z����
	ComputeGlobalInvBindPose();

	return true;
}

void Skeleton::ComputeGlobalInvBindPose()
{
	// mGlobalInvIndPoses�z����A�{�[�������m�ہ������I�ɒP�ʍs��ŏ�����
	mGlobalInvBindPoses.resize(GetNumBones());

	// �X�e�b�v�P�F���ꂼ��̃{�[���̃O���[�o���o�C���h�|�[�Y���v�Z
	// root ([0]�̂���) �̃O���[�o���o�C���h�|�[�Y�́A���[�J���o�C���h�|�[�Y�̂��Ƃł��B
	mGlobalInvBindPoses[0] = mBones[0].mLocalBindPose.ToMatrix();

	// �c��̊e�{�[���̃O���[�o���o�C���h�|�[�Y�́A
	// ���̃��[�J���|�[�Y�ɐe�̃O���[�o���o�C���h�|�[�Y���|�������̂ł��B
	for (size_t i = 1; i < mGlobalInvBindPoses.size(); ++i)
	{
		Matrix4 localMat = mBones[i].mLocalBindPose.ToMatrix();						// ���̃{�[���̃��[�J���o�C���h�|�[�Y���s��ɕϊ����� locakMat�ɑ��
		mGlobalInvBindPoses[i] = localMat * mGlobalInvBindPoses[mBones[i].mParent];	// localMat * �����̐e�̃O���[�o���o�C���h�|�[�Y�s��
	}

	// �X�e�b�v�Q�F�t�s��ɂ���
	for (size_t i = 0; i < mGlobalInvBindPoses.size(); ++i)
	{
		mGlobalInvBindPoses[i].Invert();
	}
}
