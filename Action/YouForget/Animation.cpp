#include "pch.h"

Animation::Animation()
	: mNumBones(0)
	, mNumFrames(0)
	, mDuration(0.0f)
	, mFrameDuration(0.0f)
{
}

bool Animation::Load(const char* _fileName)
{
	// ��̓I�u�W�F�N�g�쐬
	rapidjson::Document doc;
	// filename����e�L�X�g�t�@�C���Ƃ��ēǂݍ��݁ArapidJSON�ɉ�͂�����
	// �t�@�C�����J���Ȃ�������
	if (!OpenJsonFile(doc, _fileName))
	{
		printf("�A�j���[�V�����t�@�C���ł�\n");
		return false;	// false��Ԃ�
	}

	// version��int�Ŏ擾����
	int ver = doc["version"].GetInt();
	// ���^�f�[�^�̃`�F�b�N�B�o�[�W�������P����Ȃ�������
	if (ver != 1)
	{
		printf("�A�j���[�V���� %s �̃t�H�[�}�b�g���s���ł�", _fileName);
		return false;	// false��Ԃ�
	}

	// sequece���ǂݍ��߂邩�H
	const rapidjson::Value& sequence = doc["sequence"];
	// �I�u�W�F�N�g�ϐ���\���Ă��Ȃ�������
	if (!sequence.IsObject())
	{
		printf("�A�j���[�V���� %s �̓V�[�P���X�������܂���", _fileName);
		return false;	// false��Ԃ�
	}

	// frames,length,bonecount,�͂��邩�H
	const rapidjson::Value& frames = sequence["frames"];
	const rapidjson::Value& length = sequence["length"];
	const rapidjson::Value& bonecount = sequence["bonecount"];
	// �Ȃ�������
	if (!frames.IsUint() || !length.IsDouble() || !bonecount.IsUint())
	{
		printf("�V�[�P���X %s �̓t���[���A�����A�܂��̓{�[�����������ł�", _fileName);
		return false;	// false��Ԃ�
	}

	// �t���[�����A�A�j���[�V�������ԁA�{�[�����A�t���[���Ԃ̎��Ԃ��擾
	mNumFrames = frames.GetUint();						// �t���[����
	mDuration = static_cast<float>(length.GetDouble());	// �A�j���[�V��������
	mNumBones = bonecount.GetUint();					// �{�[����
	mFrameDuration = mDuration / (mNumFrames - 1);		// �t���[���Ԃ̎���(�A�j���[�V�����̍Đ�����/(�t���[���� - 1))

	// �g���b�N�z����m��
	mTracks.resize(mNumBones);
	// �g���b�N�z�񂪎擾�ł��邩�H
	const rapidjson::Value& tracks = sequence["tracks"];
	// �z�񂪎擾�ł��Ȃ����
	if (!tracks.IsArray())
	{
		printf("�V�[�P���X %s �Ƀg���b�N�z�񂪂���܂���", _fileName);
		return false;	// false��Ԃ�
	}

	// �g���b�N�������[�v
	for (rapidjson::SizeType i = 0; i < tracks.Size(); ++i)
	{
		// tracs[i]���I�u�W�F�N�g����Ȃ�������
		if (!tracks[i].IsObject())
		{
			printf("�A�j���[�V���� %s�B�g���b�N�v�f %d �͖����ł�", _fileName, i);
			return false;	// false��Ԃ�
		}

		// tracks[i]�̒��� "bone"��uint�œǂݍ��݁B�{�[���ԍ����擾
		size_t boneIndex = tracks[i]["bone"].GetUint();

		// tracks[i]�̒��� "transforms"���擾�ł��邩�H
		const rapidjson::Value& transforms = tracks[i]["transforms"];
		// transforms���z�񂶂�Ȃ�������
		if (!transforms.IsArray())
		{
			printf("�A�j���[�V���� %s�B�g���b�N�v�f %d �Ƀg�����X�t�H�[��������܂���", _fileName, i);
			return false;	// false��Ԃ�
		}

		// transforms�̃T�C�Y���A�j���[�V�����̃t���[������菬����������
		if (transforms.Size() < mNumFrames)
		{
			printf("�A�j���[�V���� %s�B�g���b�N�v�f %d �͗\�z��菭�Ȃ��t���[�����ł�", _fileName, i);
			return false;	// false��Ԃ�
		}

		// transforms�̃T�C�Y�����[�v�B�{�[���ԍ�boneIndex�̕ϊ����Ƃ��Ď�荞��
		for (rapidjson::SizeType j = 0; j < transforms.Size(); ++j)
		{
			// ���[�e�[�V����(quaternion)��trans(���s�ړ�����)��ǂݍ���
			const rapidjson::Value& rot = transforms[j]["rot"];
			const rapidjson::Value& trans = transforms[j]["trans"];
			// ���[�e�[�V�������z�񂶂�Ȃ�������A�܂���transforms���z�񂶂�Ȃ�������
			if (!rot.IsArray() || !trans.IsArray())
			{
				printf("���[�e�[�V����(quaternion)�A�܂���trans(���s�ړ�����)���ǂݍ��߂܂���ł���");
				return false;	// false��Ԃ�
			}

			BoneTransform temp; // BoneTransform �c ���f���̃{�[���ϊ�
			// temp.mRotation�Ɂ@quaternion�Ƃ��ăR�s�[�A
			temp.mRotation.x = static_cast<float>(rot[0].GetDouble());
			temp.mRotation.y = static_cast<float>(rot[1].GetDouble());
			temp.mRotation.z = static_cast<float>(rot[2].GetDouble());
			temp.mRotation.w = static_cast<float>(rot[3].GetDouble());

			// temp.mTranslation�ɕ��s�ړ������Ƃ��ăR�s�[
			temp.mTranslation.x = static_cast<float>(trans[0].GetDouble());
			temp.mTranslation.y = static_cast<float>(trans[1].GetDouble());
			temp.mTranslation.z = static_cast<float>(trans[2].GetDouble());

			// �{�[���ԍ�boneIndex�̎p���f�[�^�Ƃ��āAmTracks�z��ɓ����B
			mTracks[boneIndex].emplace_back(temp);
		}
	}

	return true;
}

const void Animation::GetGlobalPoseAtTime(vector<Matrix4>& _outPoses, const Skeleton* _inSkeleton, float _inTime) const
{
	// �A�j���[�V�����̂��߂̃{�[�����ƒl������Ă�����
	if (_outPoses.size() != mNumBones)
	{
		_outPoses.resize(mNumBones);	// �|�[�Y�}�g���b�N�X�z����m��
	}

	// @@@
	// ���݂̃t���[���Ǝ��̃t���[���������o���B
	// �����inTime�� [0�`AnimDuration] �̊Ԃɂ��邱�Ƃ�O��Ƃ��Ă��܂��B
	size_t frame = static_cast<size_t>(_inTime / mFrameDuration);	// �t���[�� = �w�莞�� / �A�j���[�V�����̃t���[���Ԃ̎���
	size_t nextFrame = frame + 1;
	// �t���[���Ǝ��̃t���[���̊Ԃ̏����l���v�Z���܂��B
	float pct = _inTime / mFrameDuration - frame;					// pct = �w�莞�� / �A�j���[�V�����̃t���[���Ԃ̎��� - frame

	// �A�j���[�V�����̃t���[������nextFrame�����傫�����
	if (mNumFrames <= nextFrame)
	{
		--nextFrame;	// nextFrame�����炷
	}

	// �|�[�Y���Z�b�g�A�b�v
	if (mTracks[0].size() > 0)
	{
		// ���݂̃t���[���̃|�[�Y�Ǝ��̃t���[���̊Ԃ��Ԃ���
		BoneTransform interp = BoneTransform::Interpolate(mTracks[0][frame],
			mTracks[0][nextFrame], pct);
		_outPoses[0] = interp.ToMatrix();
	}
	else
	{
		_outPoses[0] = Matrix4::Identity;
	}

	// �{�[���z��
	const vector<Skeleton::Bone>& bones = _inSkeleton->GetBones();
	// �c��̃|�[�Y��ݒ肵�܂�
	for (size_t bone = 1; bone < mNumBones; ++bone)
	{
		Matrix4 localMat;	// �f�t�H���g�͒P�ʍs��
		if (mTracks[bone].size() > 0)
		{
			// [bone][frame]�̃{�[���p����[bone][nextframe]�������_�ȉ���pct�ŕ�Ԃ����p����interp�ɎZ�o
			BoneTransform interp = BoneTransform::Interpolate(mTracks[bone][frame],
				mTracks[bone][nextFrame], pct);

			// interp���s��ɕϊ�����localMat�ɑ������
			localMat = interp.ToMatrix();
		}

		// �o�̓|�[�Y�s��[bone] = ���[�J���|�[�Y�s�� * �o�̓|�[�Y�s��[�ebone]
		_outPoses[bone] = localMat * _outPoses[bones[bone].mParent];
	}
}
