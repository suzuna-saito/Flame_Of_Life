#ifndef PCH_H
#define PCH_H

using namespace std;

// 外部依存
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

// System @ インプットシステム
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

// GameObject @ 全部
#include "GameObject.h"
#include "GameObjectManager.h"
#include "MainCameraObject.h"
#include "Ground.h"
#include "Player.h"
#include "LegsCollider.h"

// Component @ 全部
#include "Component.h"
#include "MeshComponent.h"//
#include "ParticleComponent.h"//
#include "SkeletalMeshComponent.h"
#include "UIComponent.h"//
/* Collision */ // @ 全部
#include "Collision.h"
#include "ColliderComponent.h"
#include "PhysicsWorld.h"
#include "BoxCollider.h"
#include "SphereCollider.h"

// Renderer@ テクスチャ以外
#include "Renderer.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"


// ジャンプ @コンポーネントか？
#include "Jump.h"

// Scene
#include "Title.h"
#include "FirstStage.h"

// ParticleEffect
#include "ParticleEffectBase.h"

// UI
#include "UIBase.h"
#include "Fade.h"

// Map @ 全部
#include "MapCreate.h"

// Game
#include "Game.h"

#endif //PCH_H