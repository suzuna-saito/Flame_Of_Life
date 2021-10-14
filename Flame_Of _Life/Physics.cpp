#include "pch.h"

// PhysicsWorld�R���X�g���N�^
Physics::Physics()
	: mBoolDebugMode(false)
{
	printf("PysicsWorld �쐬\n");
	InitBoxVertices();
	InitSquareVertices();
	InitLineVertices();

	mLineShader = new Shader();
	mLineShader->Load("shaders/LineWorld.vert", "shaders/Line.frag");

	// �����蔻��{�b�N�X�̃��C���z��
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

// �f�X�g���N�^
Physics::~Physics()
{
	printf("PysicsWorld �j��\n");
	delete mLineShader;
}

// BoxCollider�̒ǉ�
void Physics::AddCollider(ColliderComponent* collider)
{
	ColliderTag t = collider->GetTag();
	mColliders[t].emplace_back(collider);
}

// boxCollider�̍폜
void Physics::RemoveCollider(ColliderComponent* collider)
{
	Tag t = collider->GetOwner()->GetTag();
	// �^�O���猟�����č폜
	std::vector<ColliderComponent*>::iterator iter = std::find(mColliders[t].begin(), mColliders[t].end(), collider);
	if (iter != mColliders[t].end())
	{
		mColliders[t].erase(iter);
		return;
	}
}


void Physics::Collision()
{
	// �Е��������A�N�V������Ԃ������蔻��e�X�g
	for (auto reactionPair : mOneSideReactions)
	{
		OneReactionMatch(reactionPair);
	}

	// �������A�N�V������Ԃ������蔻��Z�b�g
	for (auto reactionPair : mDualReactions)
	{
		DualReactionMatch(reactionPair);
	}

	// �����Ɠ������X�g�̓����蔻��Z�b�g
	for (auto t : mSelfReactions)
	{
		SelfReactionMatch(t);
	}

}

void Physics::DebugShowBox()
{
	// �f�o�b�O���[�h���H
	if (!mBoolDebugMode)
	{
		return;
	}

	// AABB�`�揀��
	Matrix4 scale, trans, world, view, proj, viewProj;
	view = RENDERER->GetViewMatrix();
	proj = RENDERER->GetProjectionMatrix();
	viewProj = view * proj;
	mLineShader->SetActive();
	mLineShader->SetMatrixUniform("uViewProj", viewProj);

	// �����蔻��{�b�N�X�`�� tag���ɐF��ς��Ă��ׂẴ��X�g�\��
	int colorCount = 0;
	size_t colorNum = mLineColors.size();
	for (auto t = Tag::Begin; t != Tag::End; ++t)
	{
		DrawCollisions(mColliders[t], mLineColors[colorCount % colorNum]);
		colorCount++;
	}
}

// �{�b�N�X�`��p���_��`
void Physics::InitBoxVertices()
{
	// �{�b�N�X���_���X�g
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
	// �{�b�N�X�̃��C�����X�g
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
	// �{�b�N�X���_���X�g
	float vertices[] = {  // ���������と��O�と��O��
		0.0f, 0.5f,-0.5f,
		0.0f, 0.5f, 0.5f,
		0.0f,-0.5f, 0.5f,
		0.0f,-0.5f,-0.5f,
		0.0f, 0.0f, 0.0f, // �@���\��
	   -1.0f, 0.0f, 0.0f,
	};
	// �{�b�N�X�̃��C�����X�g
	unsigned int lineList[] = {
		0,1,
		1,2,
		2,3,
		3,0,
		4,5
	};

	// ���_�z�� mSquareVAO�̐ݒ�
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
	// ���C�����_���X�g
	float vertices[] =
	{
		0.0f,0.0f,0.0f,
		1.0f,0.0f,0.0f,
	};
	// ���C�����X�g
	unsigned int lineList[] =
	{
		0,1
	};
	// ���_�z�� mLineVAO�̐ݒ�
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

// �Փ˃{�b�N�X�̕`��
void Physics::DrawCollisions(std::vector<class ColliderComponent*>& collisions, const Vector3& color)
{
	Matrix4 scaleMat, posMat, rotMat, worldMat, slopeRot;
	Vector3 scale, pos;

	mLineShader->SetVectorUniform("uColor", color);
	for (auto item : collisions)
	{
		// Box�������ꍇ�̕`��
		if (item->GetColliderType() == ColliderTypeEnum::Box)
		{
			AABB box;
			Vector3 min, max;
			box = dynamic_cast<BoxCollider*>(item)->GetWorldBox();

			// �{�b�N�X�̃X�P�[���ƈʒu���擾
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


//// �����Ɠ��������蔻��O���[�v�̑��g�ݍ��킹���s��
//void Physics::SelfReactionMatch(Tag type)
//{
//	size_t size = mColliders[type].size();
//
//	for (int i = 0; i < size; i++)
//	{
//		//�������g�̓����蔻��͍s�킸�A��������`�F�b�N
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
