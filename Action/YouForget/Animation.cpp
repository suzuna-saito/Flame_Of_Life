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
	// 解析オブジェクト作成
	rapidjson::Document doc;
	// filenameからテキストファイルとして読み込み、rapidJSONに解析させる
	// ファイルが開けなかったら
	if (!OpenJsonFile(doc, _fileName))
	{
		printf("アニメーションファイルです\n");
		return false;	// falseを返す
	}

	// versionをintで取得する
	int ver = doc["version"].GetInt();
	// メタデータのチェック。バージョンが１じゃなかったら
	if (ver != 1)
	{
		printf("アニメーション %s のフォーマットが不明です", _fileName);
		return false;	// falseを返す
	}

	// sequece情報読み込めるか？
	const rapidjson::Value& sequence = doc["sequence"];
	// オブジェクト変数を表していなかったら
	if (!sequence.IsObject())
	{
		printf("アニメーション %s はシーケンスを持ちません", _fileName);
		return false;	// falseを返す
	}

	// frames,length,bonecount,はあるか？
	const rapidjson::Value& frames = sequence["frames"];
	const rapidjson::Value& length = sequence["length"];
	const rapidjson::Value& bonecount = sequence["bonecount"];
	// なかったら
	if (!frames.IsUint() || !length.IsDouble() || !bonecount.IsUint())
	{
		printf("シーケンス %s はフレーム、長さ、またはボーン数が無効です", _fileName);
		return false;	// falseを返す
	}

	// フレーム数、アニメーション時間、ボーン数、フレーム間の時間を取得
	mNumFrames = frames.GetUint();						// フレーム数
	mDuration = static_cast<float>(length.GetDouble());	// アニメーション時間
	mNumBones = bonecount.GetUint();					// ボーン数
	mFrameDuration = mDuration / (mNumFrames - 1);		// フレーム間の時間(アニメーションの再生時間/(フレーム数 - 1))

	// トラック配列を確保
	mTracks.resize(mNumBones);
	// トラック配列が取得できるか？
	const rapidjson::Value& tracks = sequence["tracks"];
	// 配列が取得できなければ
	if (!tracks.IsArray())
	{
		printf("シーケンス %s にトラック配列がありません", _fileName);
		return false;	// falseを返す
	}

	// トラック数分ループ
	for (rapidjson::SizeType i = 0; i < tracks.Size(); ++i)
	{
		// tracs[i]がオブジェクトじゃなかったら
		if (!tracks[i].IsObject())
		{
			printf("アニメーション %s。トラック要素 %d は無効です", _fileName, i);
			return false;	// falseを返す
		}

		// tracks[i]の中の "bone"をuintで読み込み。ボーン番号を取得
		size_t boneIndex = tracks[i]["bone"].GetUint();

		// tracks[i]の中の "transforms"が取得できるか？
		const rapidjson::Value& transforms = tracks[i]["transforms"];
		// transformsが配列じゃなかったら
		if (!transforms.IsArray())
		{
			printf("アニメーション %s。トラック要素 %d にトランスフォームがありません", _fileName, i);
			return false;	// falseを返す
		}

		// transformsのサイズがアニメーションのフレーム数より小さかったら
		if (transforms.Size() < mNumFrames)
		{
			printf("アニメーション %s。トラック要素 %d は予想より少ないフレーム数です", _fileName, i);
			return false;	// falseを返す
		}

		// transformsのサイズ分ループ。ボーン番号boneIndexの変換情報として取り込む
		for (rapidjson::SizeType j = 0; j < transforms.Size(); ++j)
		{
			// ローテーション(quaternion)とtrans(平行移動成分)を読み込む
			const rapidjson::Value& rot = transforms[j]["rot"];
			const rapidjson::Value& trans = transforms[j]["trans"];
			// ローテーションが配列じゃなかったら、またはtransformsが配列じゃなかったら
			if (!rot.IsArray() || !trans.IsArray())
			{
				printf("ローテーション(quaternion)、またはtrans(平行移動成分)が読み込めませんでした");
				return false;	// falseを返す
			}

			BoneTransform temp; // BoneTransform … モデルのボーン変換
			// temp.mRotationに　quaternionとしてコピー、
			temp.mRotation.x = static_cast<float>(rot[0].GetDouble());
			temp.mRotation.y = static_cast<float>(rot[1].GetDouble());
			temp.mRotation.z = static_cast<float>(rot[2].GetDouble());
			temp.mRotation.w = static_cast<float>(rot[3].GetDouble());

			// temp.mTranslationに平行移動成分としてコピー
			temp.mTranslation.x = static_cast<float>(trans[0].GetDouble());
			temp.mTranslation.y = static_cast<float>(trans[1].GetDouble());
			temp.mTranslation.z = static_cast<float>(trans[2].GetDouble());

			// ボーン番号boneIndexの姿勢データとして、mTracks配列に入れる。
			mTracks[boneIndex].emplace_back(temp);
		}
	}

	return true;
}

const void Animation::GetGlobalPoseAtTime(vector<Matrix4>& _outPoses, const Skeleton* _inSkeleton, float _inTime) const
{
	// アニメーションのためのボーン数と値が違っていたら
	if (_outPoses.size() != mNumBones)
	{
		_outPoses.resize(mNumBones);	// ポーズマトリックス配列を確保
	}

	// @@@
	// 現在のフレームと次のフレームを見つけ出す。
	// これはinTimeが [0～AnimDuration] の間にいることを前提としています。
	size_t frame = static_cast<size_t>(_inTime / mFrameDuration);	// フレーム = 指定時間 / アニメーションのフレーム間の時間
	size_t nextFrame = frame + 1;
	// フレームと次のフレームの間の小数値を計算します。
	float pct = _inTime / mFrameDuration - frame;					// pct = 指定時間 / アニメーションのフレーム間の時間 - frame

	// アニメーションのフレーム数がnextFrameよりも大きければ
	if (mNumFrames <= nextFrame)
	{
		--nextFrame;	// nextFrameを減らす
	}

	// ポーズをセットアップ
	if (mTracks[0].size() > 0)
	{
		// 現在のフレームのポーズと次のフレームの間を補間する
		BoneTransform interp = BoneTransform::Interpolate(mTracks[0][frame],
			mTracks[0][nextFrame], pct);
		_outPoses[0] = interp.ToMatrix();
	}
	else
	{
		_outPoses[0] = Matrix4::Identity;
	}

	// ボーン配列
	const vector<Skeleton::Bone>& bones = _inSkeleton->GetBones();
	// 残りのポーズを設定します
	for (size_t bone = 1; bone < mNumBones; ++bone)
	{
		Matrix4 localMat;	// デフォルトは単位行列
		if (mTracks[bone].size() > 0)
		{
			// [bone][frame]のボーン姿勢と[bone][nextframe]を小数点以下のpctで補間した姿勢をinterpに算出
			BoneTransform interp = BoneTransform::Interpolate(mTracks[bone][frame],
				mTracks[bone][nextFrame], pct);

			// interpを行列に変換してlocalMatに代入する
			localMat = interp.ToMatrix();
		}

		// 出力ポーズ行列[bone] = ローカルポーズ行列 * 出力ポーズ行列[親bone]
		_outPoses[bone] = localMat * _outPoses[bones[bone].mParent];
	}
}
