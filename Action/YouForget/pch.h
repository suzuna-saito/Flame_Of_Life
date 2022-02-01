#ifndef PCH_H
#define PCH_H

using namespace std;

// �O���ˑ�
#include <algorithm>
#include <array>
#include <cstring>
#include <cstdint>
#include <cmath>
#include <document.h>
#include <fstream>
#include <functional>
#include <filereadstream.h>
#include <glew.h>
#include <limits>
#include <limits.h>
#include <memory.h>
#include <map>
#include <set>
#include <stdio.h>
#include <string>
#include <sstream>
#include <SDL.h>
#include <SDL_gamecontroller.h>
#include <SDL_image.h>
#include <SDL_log.h>
#include <SDL_mouse.h>
#include <SDL_scancode.h>
#include <SDL_ttf.h>
#include <time.h>
#include <unordered_map>
#include <vector>
#include <Windows.h>

// Math
#include "Math.h"

// FPS
#include "FPS.h"

// �C���v�b�g�V�X�e��
#include "InputSystem.h"

// �A�j���[�V����
#include "MatrixPalette.h"
#include "BoneTransform.h"
#include "Skeleton.h"
#include "Animation.h"

// �R���W����
#include "Collision.h"

// �R���|�[�l���g
#include "Component.h"
#include "MeshComponent.h"
#include "ParticleComponent.h"
#include "SpriteComponent.h"
#include "SkeletalMeshComponent.h"

// �����_���[
#include "Shader.h"
#include "VertexArray.h"
#include "Texture.h"
#include "Mesh.h"
#include "Renderer.h"
#include "SceneBase.h"
/* TTF */
#include "Font.h"

// �Q�[���I�u�W�F�N�g
#include "GameObject.h"
#include "GameObjectManager.h"
/* �J���� */
#include "MainCameraObject.h"
/* �� */
#include "Ground.h"
/* �w�i */
#include "BackGround.h"
/* �X�C�b�` */
#include "Switch.h"
#include "SwitchCollider.h"
/* �낤���� */
#include "Candle.h"
/* �낤�����ɂ��Ă�I�u�W�F�N�g */
#include "FireObject.h"
/* �v���C���[ */
#include "Player.h"
#include "LegsCollider.h"
/* �A�C�e�� */
#include "ItemBase.h"
#include "Item.h"

// �W�����v
#include "Jump.h"

// �p�[�e�B�N���G�t�F�N�g
#include "ParticleEffectBase.h"
#include "EffectManager.h"
#include "SandEffect.h"
/* �v���C���[�����������̃G�t�F�N�g */
#include "FallEffectManager.h"
#include "FallEffect.h"
/* �A�C�e���̌��ɂ���G�t�F�N�g */
#include "ItemEffectManager.h"
#include "ItemEffect.h"

// UI
#include "UIBase.h"
/* �X�v���C�g*/
#include "Sprite.h"
/* �A�C�e���̐� */
#include "ItemCount.h"

// �V�[��
#include "SceneBase.h"
#include "Title.h"
#include "Tutorial.h"
#include "FirstStage.h"
#include "SecondStage.h"
#include "ThirdStage.h"
#include "Result.h"

// �R���W���� *
#include "PhysicsWorld.h"
#include "ColliderComponent.h"
#include "SphereCollider.h"
#include "BoxCollider.h"

// RapidJson
#include "RapidJsonHelper.h"

// �}�b�v
#include "MapCreate.h"

// Game
#include "Game.h"


#endif //PCH_H