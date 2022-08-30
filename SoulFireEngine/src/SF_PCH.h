//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//SF_PCH.h - precompile header
#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include "SoulFire/Core/Logger.h"

//math
#include "GLM/glm.hpp"
#include "glm/common.hpp"
#include <GLM/gtc/type_ptr.hpp>
#include <GLM/gtc/matrix_transform.hpp>
//allow use of experimental glm features
#define GLM_ENABLE_EXPERIMENTAL
#include "GLM/gtx/quaternion.hpp"
#include "GLM/gtx/transform.hpp"

#ifdef SF_PLATFORM_WINDOWS
	#include <Windows.h>
#endif

