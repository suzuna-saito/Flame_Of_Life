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
#include <SDL_mixer.h>
#include <SDL_mouse.h>
#include <SDL_scancode.h>
#include <SDL_ttf.h>
#include <time.h>
#include <unordered_map>
#include <vector>
#include <Windows.h>

// System @ �C���v�b�g�V�X�e��
#include "Math.h"
#include "FPS.h"
#include "RapidJsonHelper.h"
#include "InputSystem.h"

// Animation
#include "Animation.h"
#include "BoneTransform.h"
#include "MatrixPalette.h"
#include "Skeleton.h"

// Scene
#include "SceneBase.h"
#include "Collision.h"

// GameObject @ �S��
#include "GameObject.h"
#include "GameObjectManager.h"
#include "MainCameraObject.h"
#include "Ground.h"
#include "Player.h"
#include "LegsCollider.h"

// Component @ �S��
#include "Component.h"
#include "MeshComponent.h"//
#include "ParticleComponent.h"//
#include "SkeletalMeshComponent.h"
#include "UIComponent.h"//
/* Collision */ // @ �S��
#include "Collision.h"
#include "ColliderComponent.h"
#include "PhysicsWorld.h"
#include "BoxCollider.h"
#include "SphereCollider.h"

// Renderer@ �e�N�X�`���ȊO
#include "Renderer.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"


// �W�����v @�R���|�[�l���g���H
#include "Jump.h"

// Scene
#include "Title.h"
#include "FirstStage.h"

// ParticleEffect
#include "ParticleEffectBase.h"

// UI
#include "UIBase.h"
#include "Fade.h"

// Map @ �S��
#include "MapCreate.h"

// Game
#include "Game.h"

#endif //PCH_H