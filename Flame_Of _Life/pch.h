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

// コリジョン
#include "Collision.h"

// コンポーネント
#include "Component.h"
#include "MeshComponent.h"
#include "ParticleComponent.h"
#include "SpriteComponent.h"
#include "SkeletalMeshComponent.h"

// レンダラー
#include "Shader.h"
#include "VertexArray.h"
#include "Texture.h"
#include "Mesh.h"
#include "Renderer.h"
#include "SceneBase.h"

// ゲームオブジェクト
#include "GameObject.h"
#include "GameObjectManager.h"
/* カメラ */
#include "MainCameraObject.h"
/* 床 */
#include "Ground.h"

/* ろうそく */
#include "Candle.h"
/* ろうそくについてるオブジェクト */
#include "FireObject.h"
/* プレイヤー */
#include "Player.h"

// ジャンプ
#include "Jump.h"


// パーティクルエフェクト
#include "ParticleEffectBase.h"
#include "EffectManager.h"
#include "SandEffect.h"

// UI
#include "UIBase.h"
/* タイム */
#include "CountUp.h"
#include "Time.h"
/* スプライト*/
#include "Sprite.h"

// シーン
#include "SceneBase.h"
#include "Title.h"
#include "Tutorial.h"
#include "Stage01.h"

// コリジョン *
#include "PhysicsWorld.h"
#include "ColliderComponent.h"
#include "SphereCollider.h"
#include "BoxCollider.h"

// RapidJson
#include "RapidJsonHelper.h"

// マップ
#include "MapCreate.h"

// Game
#include "Game.h"


#endif //PCH_H