//SoulFire engine by Ame Gilham, inspired by The Cherno's Hazel
//SoulFire.h - an include header that allows client side applications to access soul fire featuers
#pragma once

#include "SF_PCH.h"
#include "SoulFire/Core/Application.h"
#include "SoulFire/Core/Logger.h"
#include "SoulFire/Events/Event.h"

#include "SoulFire/Core/Input.h"
#include "SoulFire/Core/InputCodes.h"
#include "SoulFire/Core/OrthographicCameraController.h"

#include "SoulFire/ImGui/ImGuiLayer.h"

#include "SoulFire/Renderer/Renderer.h"
#include "SoulFire/Renderer/Renderer2D.h"
#include "SoulFire/Renderer/RenderCommand.h"

#include "SoulFire/Renderer/Buffer.h"
#include "SoulFire/Renderer/Shader.h"
#include "SoulFire/Renderer/Texture.h"
#include "SoulFire/Renderer/VertexArrayObject.h"

#include "SoulFire/Renderer/Camera.h"

#include "SoulFire/Core/Time.h"

#include "SoulFire/Core/HelperFunctions.h"

namespace SoulFire {
	using namespace RendererEnums;
}