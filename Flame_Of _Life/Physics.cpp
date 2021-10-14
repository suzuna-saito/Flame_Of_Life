#include "pch.h"

// PhysicsWorldコンストラクタ
Physics::Physics()
	: mBoolDebugMode(false)
{
	printf("PysicsWorld 作成\n");
	InitBoxVertices();
	InitSquareVertices();
	InitLineVertices();

	mLineShader = new Shader();
	mLineShader->Load("shaders/LineWorld.vert", "shaders/Line.frag");

	// 当たり判定ボックスのライン配列
	mLineColors.emplace_back(Color::White);
	mLineColors.emplace_back(Color::Red);
	mLineColors.emplace_back(Color::Green);
	mLineColors.emplace_back(Color::Blue);
	mLineColors.emplace_back(Color::Yellow);
	mLineColors.emplace_back(Color::LightYellow);
	mLineColors.emplace_back(Color::LightBlue);
	mLineColors.emplace_back(Color::LightPink);
	mLineColors.emplace_back(Color::LightGreen);
}

// デストラクタ
Physics::~Physics()
{
	printf("PysicsWorld 破棄\n");
	delete mLineShader;
}

// BoxColliderの追加
void Physics::AddCollider(ColliderComponent* collider)
{
	ColliderTag t = collider->GetTag();
	mColliders[t].emplace_back(collider);
}

// boxColliderの削除
void Physics::RemoveCollider(ColliderComponent* collider)
{
	Tag t = collider->GetOwner()->GetTag();
	// タグから検索して削除
	std::vector<ColliderComponent*>::iterator iter = std::find(mColliders[t].begin(), mColliders[t].end(), collider);
	if (iter != mColliders[t].end())
	{
		mColliders[t].erase(iter);
		return;
	}
}


void Physics::Collision()
{
	// 片方だけリアクションを返す当たり判定テスト
	for (auto reactionPair : mOneSideReactions)
	{
		OneReactionMatch(reactionPair);
	}

	// 両方リアクションを返す当たり判定セット
	for (auto reactionPair : mDualReactions)
	{
		DualReactionMatch(reactionPair);
	}

	// 自分と同じリストの当たり判定セット
	for (auto t : mSelfReactions)
	{
		SelfReactionMatch(t);
	}

}

void Physics::DebugShowBox()
{
	// デバッグモードか？
	if (!mBoolDebugMode)
	{
		return;
	}

	// AABB描画準備
	Matrix4 scale, trans, world, view, proj, viewProj;
	view = RENDERER->GetViewMatrix();
	proj = RENDERER->GetProjectionMatrix();
	viewProj = view * proj;
	mLineShader->SetActive();
	mLineShader->SetMatrixUniform("uViewProj", viewProj);

	// 当たり判定ボックス描画 tag毎に色を変えてすべてのリスト表示
	int colorCount = 0;
	size_t colorNum = mLineColors.size();
	for (auto t = Tag::Begin; t != Tag::End; ++t)
	{
		DrawCollisions(mColliders[t], mLineColors[colorCount % colorNum]);
		colorCount++;
	}
}

// ボックス描画用頂点定義
void Physics::InitBoxVertices()
{
	// ボックス頂点リスト
	float vertices[] = {
		0.0f, 0.0f, 0.0f,  // min
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f,  // max
		0.0f, 1.0f, 1.0f,
	};
	// ボックスのラインリスト
	unsigned int lineList[] = {
		0,1,
		1,2,
		2,3,
		3,0,
		4,5,
		5,6,
		6,7,
		7,4,
		0,4,
		1,5,
		2,6,
		3,7,
	};
	unsigned int vbo, ebo;
	glGenVertexArrays(1, &mBoxVAO);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glBindVertexArray(mBoxVAO);
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(lineList), lineList, GL_STATIC_DRAW);
	}
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

}

void Physics::InitSquareVertices()
{
	// ボックス頂点リスト
	float vertices[] = {  // 奥下→奥上→手前上→手前下
		0.0f, 0.5f,-0.5f,
		0.0f, 0.5f, 0.5f,
		0.0f,-0.5f, 0.5f,
		0.0f,-0.5f,-0.5f,
		0.0f, 0.0f, 0.0f, // 法線表示
	   -1.0f, 0.0f, 0.0f,
	};
	// ボックスのラインリスト
	unsigned int lineList[] = {
		0,1,
		1,2,
		2,3,
		3,0,
		4,5
	};

	// 頂点配列 mSquareVAOの設定
	unsigned int vbo, ebo;
	glGenVertexArrays(1, &mSquareVAO);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glBindVertexArray(mSquareVAO);
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(lineList), lineList, GL_STATIC_DRAW);
	}
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void Physics::InitLineVertices()
{
	// ライン頂点リスト
	float vertices[] =
	{
		0.0f,0.0f,0.0f,
		1.0f,0.0f,0.0f,
	};
	// ラインリスト
	unsigned int lineList[] =
	{
		0,1
	};
	// 頂点配列 mLineVAOの設定
	unsigned int vbo, ebo;
	glGenVertexArrays(1, &mLineVAO);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glBindVertexArray(mLineVAO);
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(lineList), lineList, GL_STATIC_DRAW);
	}
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

}

// 衝突ボックスの描画
void Physics::DrawCollisions(std::vector<class ColliderComponent*>& collisions, const Vector3& color)
{
	Matrix4 scaleMat, posMat, rotMat, worldMat, slopeRot;
	Vector3 scale, pos;

	mLineShader->SetVectorUniform("uColor", color);
	for (auto item : collisions)
	{
		// Boxだった場合の描画
		if (item->GetColliderType() == ColliderTypeEnum::Box)
		{
			AABB box;
			Vector3 min, max;
			box = dynamic_cast<BoxCollider*>(item)->GetWorldBox();

			// ボックスのスケールと位置を取得
			min = box.mMin;
			max = box.mMax;
			scale = max - min;
			pos = min;

			scaleMat = Matrix4::CreateScale(scale);
			posMat = Matrix4::CreateTranslation(pos);

			worldMat = scaleMat * posMat;
			mLineShader->SetMatrixUniform("uWorld", worldMat);

			glBindVertexArray(mBoxVAO);
			glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);
		}


	}
}

void Physics::SetOneSideReactionCollisionPair(Tag noReactionType, Tag reactionType)
{
	collidePairs cp;
	cp.pair1 = noReactionType;
	cp.pair2 = reactionType;

	mOneSideReactions.emplace_back(cp);
}


void Physics::ClearOneSidePair()
{
	mOneSideReactions.clear();
}

void Physics::ClearDualPair()
{
	mDualReactions.clear();
}

void Physics::ClearSelfPair()
{
	mSelfReactions.clear();
}


//// 自分と同じ当たり判定グループの総組み合わせを行う
//void Physics::SelfReactionMatch(Tag type)
//{
//	size_t size = mColliders[type].size();
//
//	for (int i = 0; i < size; i++)
//	{
//		//自分自身の当たり判定は行わず、総当たりチェック
//		for (int j = i + 1; j < size; j++)
//		{
//			if (mColliders[type][i]->CollisionDetection(mColliders[type][j]))
//			{
//				Actor* obj1 = mColliders[type][i]->GetOwner();
//				obj1->OnCollisionEnter(mColliders[type][i], mColliders[type][j]);
//			}
//		}
//	}
//}
