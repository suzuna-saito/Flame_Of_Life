#ifndef PCH_H
#define PCH_H

// �O���ˑ�--------------------------
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


// �R���|�[�l���g -------------------
#include "Component.h"
// ----------------------------------

// �R���W���� -----------------------
#include "Collision.h"
#include "ColliderComponent.h"
// ----------------------------------

// �Q�[���I�u�W�F�N�g ---------------
#include "GameObject.h"
// ----------------------------------

// �����_���[ -----------------------
#include "Renderer.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
// ----------------------------------

// �V�[��----------------------------
#include "SceneBase.h"
//-----------------------------------

#endif //PCH_H