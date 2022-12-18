//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//ImGuiFields.h - header file that has a variety of functions to more easily create ImGui fields
#pragma once

namespace SoulFire {
	class ImGuiFields {
	public:
		static void Seperator();

		static void Space(float space);

		static void Text(const std::string& text);

		static bool Checkbox(const std::string& label, bool* item, float columnWidth = 100.0f, const std::string& id = "");
		static bool Checkbox(const std::string& id, const std::string& label, bool* item, float columnWidth = 100.0f);

		static bool LeftAlignedButton(const std::string& label, glm::vec2 size = glm::vec2(20.0f, 20.0f));
		static bool RightAlignedButton(const std::string& label, glm::vec2 size = glm::vec2(20.0f, 20.0f));
		static bool CentreAlignedButton(const std::string& label, glm::vec2 size = glm::vec2(20.0f, 20.0f));

		static bool ShortTextField(const std::string& label, std::string& text, float columnWidth = 100.0f, const std::string& id = "");
		static bool ShortTextField(const std::string& id, const std::string& label, std::string& text, float columnWidth = 100.0f);

		static bool FloatField(const std::string& label, float* value, float resetVal = 0.0f, float columnWidth = 100.0f, const std::string& id = "");
		static bool FloatField(const std::string& id, const std::string& label, float* value, float resetVal = 0.0f, float columnWidth = 100.0f);

		static bool Vec2Field(const std::string& label, glm::vec2& values, float resetVal = 0.0f, float columnWidth = 100.0f, const std::string& id = "");
		static bool Vec2Field(const std::string& id, const std::string& label, glm::vec2& values, float resetVal = 0.0f, float columnWidth = 100.0f);

		static bool Vec3Field(const std::string& label, glm::vec3& values, float resetVal = 0.0f, float columnWidth = 100.0f, const std::string& id = "");
		static bool Vec3Field(const std::string& id, const std::string& label, glm::vec3& values, float resetVal = 0.0f, float columnWidth = 100.0f);

		static bool Vec4Field(const std::string& label, glm::vec4& values, float resetVal = 0.0f, float columnWidth = 100.0f, const std::string& id = "");
		static bool Vec4Field(const std::string& id, const std::string& label, glm::vec4& values, float resetVal = 0.0f, float columnWidth = 100.0f);

		static bool Color3Field(const std::string& label, glm::vec3& color, float columnWidth = 100.0f, const std::string& id = "");
		static bool Color3Field(const std::string& id, const std::string& label, glm::vec3& color, float columnWidth = 100.0f);

		static bool Color4Field(const std::string& label, glm::vec4& color, float columnWidth = 100.0f, const std::string& id = "");
		static bool Color4Field(const std::string& id, const std::string& label, glm::vec4& color, float columnWidth = 100.0f);

		static bool Dropdown(const std::string& label, const std::vector<std::string>& options, uint32_t& currentIndex, float columnWidth = 100.0f, const std::string& id = "");
		static bool Dropdown(const std::string& id, const std::string& label, const std::vector<std::string>& options, uint32_t& currentIndex, float columnWidth = 100.0f);
	private:
		static void PushID(const std::string& label, const std::string& id);
	};
}