#pragma once
#include "SF_PCH.h"

namespace SoulFire {
	class  Math {
	public:
		static glm::vec2 PairToVec2(std::pair<float, float> pair) {
			return glm::vec2(pair.first, pair.second);
		}
	};
}