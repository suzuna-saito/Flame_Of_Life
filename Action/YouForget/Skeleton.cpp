#include "pch.h"

bool Skeleton::Load(const char* _fileName)
{
	// 解析オブジェクト作成
	rapidjson::Document doc;
	// filenameからテキストファイルとして読み込み、rapidJSONに解析させる
	// ファイルが開けなかったら
	if (!OpenJsonFile(doc, _fileName))
	{
		printf("スケルトンファイルです\n");
		return false;	// falseを返す
	}

	// versionをintで取得する
	int ver = doc["version"].GetInt();
	// メタデータのチェック。バージョンが１じゃなかったら
	if (ver != 1)
	{
		printf("スケルトン %s のフォーマットが不明です", _fileName);
		return false;	// falseを返す
	}

	// bonecount ボーン数の取得
	const rapidjson::Value& bonecount = doc["bonecount"];
	if (!bonecount.IsUint())
	{
		printf("スケルトン %s は骨を持っていません", _fileName);
		return false;	// falseを返す
	}
	// 骨数を代入
	size_t count = bonecount.GetUint();

	// ボーン数がMAX_SKELETON_BONESを超えていた場合 (196本が最大)
	if (count > MAX_SKELETON_BONES)
	{
		printf("スケルトン %s が最大骨数を超えています", _fileName);
		return false;	// falseを返す
	}

	// ボーン配列のキャパシティを骨数に合わせて変更する
	mBones.reserve(count);

	// ボーン配列の取得
	const rapidjson::Value& bones = doc["bones"];
	if (!bones.IsArray())
	{
		printf("スケルトン %s は骨の配列を持っていない", _fileName);
		return false;	// falseを返す
	}

	// ボーン配列のサイズとボーン数が異なる場合はエラーを返す
	if (bones.Size() != count)
	{
		printf("スケルトン %s は、骨の数と骨の数が不一致です", _fileName);
		return false;	// falseを返す
	}

	// ボーンの骨格定義保存用
	Bone temp;

	// ボーン配列数分ループ
	for (rapidjson::SizeType i = 0; i < count; ++i)
	{
		// ボーンが読めるか？
		if (!bones[i].IsObject())
		{
			printf("スケルトン %sの骨格 %d は無効です", _fileName, i);
			return false;	// falseを返す
		}

		// "name" ボーン名
		const rapidjson::Value& name = bones[i]["name"];
		temp.mName = name.GetString();

		// "parent" 親ボーンID
		const rapidjson::Value& parent = bones[i]["parent"];
		temp.mParent = parent.GetInt();

		// "bindpose" バインドポーズ
		const rapidjson::Value& bindpose = bones[i]["bindpose"];
		if (!bindpose.IsObject())
		{
			printf("スケルトン %sの骨格 %d は無効です", _fileName, i);
			return false;	// falseを返す
		}

		// バインドポーズの回転、位置
		const rapidjson::Value& rot = bindpose["rot"];		// 回転
		const rapidjson::Value& trans = bindpose["trans"];	// 位置

		// 回転と位置が配列じゃなかったらエラー返す
		if (!rot.IsArray() || !trans.IsArray())
		{
			printf("スケルトン %sの骨格 %d は無効です", _fileName, i);
			return false;	// falseを返す
		}

		// バインドポーズの回転成分
		temp.mLocalBindPose.mRotation.x = static_cast<float>(rot[0].GetDouble());
		temp.mLocalBindPose.mRotation.y = static_cast<float>(rot[1].GetDouble());
		temp.mLocalBindPose.mRotation.z = static_cast<float>(rot[2].GetDouble());
		temp.mLocalBindPose.mRotation.w = static_cast<float>(rot[3].GetDouble());

		// バインドポーズの移動成分
		temp.mLocalBindPose.mTranslation.x = static_cast<float>(trans[0].GetDouble());
		temp.mLocalBindPose.mTranslation.y = static_cast<float>(trans[1].GetDouble());
		temp.mLocalBindPose.mTranslation.z = static_cast<float>(trans[2].GetDouble());

		// ボーン配列に格納する
		mBones.emplace_back(temp);
	}

	// ここでボーン配列は読みこまれているので、逆バインドポーズ行列を計算する
	ComputeGlobalInvBindPose();

	return true;
}

void Skeleton::ComputeGlobalInvBindPose()
{
	// mGlobalInvIndPoses配列を、ボーン数分確保＆自動的に単位行列で初期化
	mGlobalInvBindPoses.resize(GetNumBones());

	// ステップ１：それぞれのボーンのグローバルバインドポーズを計算
	// root ([0]のこと) のグローバルバインドポーズは、ローカルバインドポーズのことです。
	mGlobalInvBindPoses[0] = mBones[0].mLocalBindPose.ToMatrix();

	// 残りの各ボーンのグローバルバインドポーズは、
	// そのローカルポーズに親のグローバルバインドポーズを掛けたものです。
	for (size_t i = 1; i < mGlobalInvBindPoses.size(); ++i)
	{
		Matrix4 localMat = mBones[i].mLocalBindPose.ToMatrix();						// そのボーンのローカルバインドポーズを行列に変換して locakMatに代入
		mGlobalInvBindPoses[i] = localMat * mGlobalInvBindPoses[mBones[i].mParent];	// localMat * 自分の親のグローバルバインドポーズ行列
	}

	// ステップ２：逆行列にする
	for (size_t i = 0; i < mGlobalInvBindPoses.size(); ++i)
	{
		mGlobalInvBindPoses[i].Invert();
	}
}
