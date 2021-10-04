#ifndef PCH_H
#define PCH_H

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

// インプットシステム
#include "InputSystem.h"

// アニメーション
#include "MatrixPalette.h"
#include "BoneTransform.h"
#include "Skeleton.h"
#include "Animation.h"

// コンポーネント
#include "Component.h"
#include "MeshComponent.h"
#include "ParticleComponent.h"
#include "SkeletalMeshComponent.h"
#include "SpriteComponent.h"
/* コリジョン */
#include "ColliderComponent.h"
#include "Collision.h"
#include "PhysicsWorld.h"
#include "BoxCollider.h"
#include "SphereCollider.h"

// シーン
#include "SceneBase.h"
#include "TitleScene.h"

// ゲームオブジェクト
#include "GameObject.h"
#include "GameObjectManager.h"
/* カメラ */
#include "MainCameraObject.h"


// マップ
#include "MapCreate.h"

// パーティクルエフェクト
#include "ParticleEffectBase.h"
#include "EffectManager.h"
#include "SandEffect.h"

// RapidJson
#include "RapidJsonHelper.h"

// レンダラー
#include "Mesh.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"

// UI
#include "UIBase.h"
#include "TitleUI.h"

// Others
#include "Game.h"

#endif //PCH_H