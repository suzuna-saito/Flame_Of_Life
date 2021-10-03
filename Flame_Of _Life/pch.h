#ifndef PCH_H
#define PCH_H

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

// �A�j���[�V����
#include "Animation.h"
#include "BoneTransform.h"
#include "MatrixPalette.h"
#include "Skeleton.h"

// �R���|�[�l���g
#include "Component.h"
#include "MeshComponent.h"
#include "ParticleComponent.h"
#include "SkeletalMeshComponent.h"
#include "SpriteComponent.h"
/* �R���W���� */
#include "BoxCollider.h"
#include "ColliderComponent.h"
#include "Collision.h"
#include "PhysicsWorld.h"
#include "SphereCollider.h"

// FPS
#include "FPS.h"

// �Q�[���I�u�W�F�N�g
#include "GameObject.h"
#include "GameObjectManager.h"
/* �J���� */
#include "MainCameraObject.h"

// �C���v�b�g�V�X�e��
#include "InputSystem.h"

// Math
#include "Math.h"

// �}�b�v
#include "MapCreate.h"

// �p�[�e�B�N���G�t�F�N�g
#include "ParticleEffectBase.h"
#include "EffectManager.h"
#include "SandEffect.h"

// RapidJson
#include "RapidJsonHelper.h"

// �����_���[
#include "Mesh.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"

// �V�[��
#include "SceneBase.h"
#include "TitleScene.h"

// UI
#include "UIBase.h"
#include "TitleUI.h"

// Others
#include "Game.h"


#endif //PCH_H