//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//Renderer.cpp - source file for the class that represnets the renderer that can interface with different API 
#include "SF_PCH.h"
#include "Renderer.h"

namespace SoulFire {

	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData();

	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::BeginRenderPass(sptr<Camera>& cam)
	{
		s_SceneData->VP = cam->GetVP();
	}

	void Renderer::EndRenderPass()
	{
	}

	void Renderer::AddToPass(const sptr<VertexArrayObject>& VAO, const sptr<Shader>& shader, Transform& trans)
	{
		shader->Bind();
		shader->SetUniformMatrix("u_ViewProjection", s_SceneData->VP);
		shader->SetUniformMatrix("u_Model", trans.GetTransform());
		RenderCommand::Draw(VAO);
		shader->UnBind();
	}
}