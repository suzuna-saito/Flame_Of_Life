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
#include <stdio.h>
#include <string>
#include <sstream>
#include <SDL.h>
#include <SDL_scancode.h>
#include <SDL_gamecontroller.h>
#include <SDL_mouse.h>
#include <SDL_log.h>
#include <SDL_image.h>
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

// �Q�[���I�u�W�F�N�g
#include "GameObject.h"
#include "GameObjectManager.h"
/* �J���� */
#include "MainCameraObject.h"
/* �� */
#include "Ground.h"

/* �낤���� */
#include "Candle.h"
/* �낤�����ɂ��Ă�I�u�W�F�N�g */
#include "FireObject.h"
/* �v���C���[ */
#include "Player.h"

// �W�����v
#include "Jump.h"


// �p�[�e�B�N���G�t�F�N�g
#include "ParticleEffectBase.h"
#include "EffectManager.h"
#include "SandEffect.h"

// UI
#include "UIBase.h"
/* �^�C�� */
#include "CountUp.h"
#include "Time.h"
/* �X�v���C�g*/
#include "Sprite.h"

// �V�[��
#include "SceneBase.h"
#include "Title.h"
#include "Tutorial.h"
#include "Stage01.h"

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