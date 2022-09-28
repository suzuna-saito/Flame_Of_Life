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

// Animation @ �X�P���g��
#include "Animation.h"
#include "BoneTransform.h"
#include "MatrixPalette.h"
#include "Skeleton.h"

// Component @ �S��
#include "Component.h"
#include "MeshComponent.h"
#include "ParticleComponent.h"
#include "SkeletalMeshComponent.h"
#include "SpriteComponent.h"
#include "UIComponent.h"
/* Collision */ // @ �S��
#include "Collision.h"
#include "ColliderComponent.h"
#include "PhysicsWorld.h"
#include "BoxCollider.h"
#include "SphereCollider.h"

// Renderer
#include "Renderer.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"

// �V�[�� @ �I����ĂȂ�
#include "SceneBase.h"

// GameObject @ �S��
#include "GameObject.h"
#include "GameObjectManager.h"
#include "BackGround.h"
#include "MainCameraObject.h"
#include "GoalObj.h"
#include "Candle.h"
#include "FireObject.h"
#include "Ground.h"
#include "Player.h"
#include "LegsCollider.h"
#include "Switch.h"
#include "SwitchCollider.h"
#include "ItemBase.h"
#include "Item.h"

// �W�����v @�R���|�[�l���g���H
#include "Jump.h"

// �V�[�� @ �S��
#include "Title.h"
#include "FirstStage.h"
#include "SecondStage.h"
#include "ThirdStage.h"
#include "ResultBase.h"
#include "FirstResult.h"
#include "SecondResult.h"
#include "ThirdResult.h"
#include "Result.h"

// ParticleEffect @ �S��
#include "ParticleEffectBase.h"
#include "EffectManager.h"
#include "FallEffect.h"
#include "FallEffectManager.h"
#include "ItemEffect.h"
#include "ItemEffectManager.h"
#include "CircledShadow.h"
#include "CircledShadowManager.h"
#include "GoalEffect.h"
#include "GoalEffectManager.h"

// UI @ �S��
#include "UIBase.h"
#include "ButtonUI.h"
#include "Sprite.h"

// Map @ �S��
#include "MapCreate.h"

// Game @ �S��
#include "Game.h"


#endif //PCH_H