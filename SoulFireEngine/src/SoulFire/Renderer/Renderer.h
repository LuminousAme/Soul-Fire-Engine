//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//Renderer.h - header file for the class that represnets the renderer that can interface with different API 
#pragma once

#include "RenderCommand.h"
#include "Camera.h"
#include "Shader.h"
#include "SoulFire/Compontents/Transform.h"

namespace SoulFire {

	class Renderer {
	public:
		static void Init();

		static void BeginRenderPass(sptr<Camera>& cam);
		static void EndRenderPass();

		static void AddToPass(const sptr<VertexArrayObject>& VAO, const sptr<Shader>& shader, Transform& trans);

		static void NaiveWindowResize(uint32_t width, uint32_t height);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData {
			glm::mat4 VP;
		};

		static SceneData* s_SceneData;
	};
}