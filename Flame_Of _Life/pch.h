#ifndef PCH_H
#define PCH_H

// 外部依存--------------------------
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
// ----------------------------------


#include "Game.h"
#include "Windows.h"

#include "FPS.h"
#include "InputSystem.h"
#include "Math.h"
#include "RapidJsonHelper.h"


// アニメーション -------------------
#include "Animation.h"
#include "BoneTransform.h"
#include "MatrixPalette.h"
#include "Skeleton.h"
// ----------------------------------


// コンポーネント -------------------
#include "Component.h"
#include "MeshComponent.h"
#include "ParticleComponent.h"
#include "SkeletalMeshComponent.h"
#include "SpriteComponent.h"
/* コリジョン */
#include "BoxCollider.h"
#include "ColliderComponent.h"
#include "Collision.h"
#include "PhysicsWorld.h"
#include "SphereCollider.h"
// ----------------------------------


// ゲームオブジェクト ---------------
#include "GameObject.h"
#include "GameObjectManager.h"
/* カメラ */
#include "MainCameraObject.h"

// ----------------------------------


// レンダラー -----------------------
#include "Mesh.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
// ----------------------------------


// シーン----------------------------
#include "SceneBase.h"
//-----------------------------------

#endif //PCH_H