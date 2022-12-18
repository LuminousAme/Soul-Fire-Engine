//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//ImGuiFields.cpp - soure file that has a variety of functions to more easily create ImGui fields

#include "SF_PCH.h"
#include "ImGuiFields.h"
#include "imgui.h"
#include "imgui_internal.h"

namespace SoulFire {
	static uint32_t id = 1000;

	void ImGuiFields::Seperator()
	{
		ImGui::Separator();
	}

	void ImGuiFields::Space(float space)
	{
		ImGui::Dummy(ImVec2(0.0f, space));
	}

	void ImGuiFields::Text(const std::string& text)
	{
		ImGui::Text(text.c_str());
	}

	bool ImGuiFields::Checkbox(const std::string& label, bool* item, float columnWidth, const std::string& id)
	{
		bool changed = false;
		PushID(label, id);

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();
		changed = ImGui::Checkbox("##B", item);
		ImGui::Columns(1);

		ImGui::PopID();
		return changed;
	}

	bool ImGuiFields::Checkbox(const std::string& id, const std::string& label, bool* item, float columnWidth)
	{
		return Checkbox(label, item, columnWidth, id);
	}

	bool ImGuiFields::LeftAlignedButton(const std::string& label, glm::vec2 size)
	{
		bool pressed = false;
		ImGui::SameLine(5.0f);
		pressed = ImGui::Button(label.c_str());
		return pressed;
	}

	bool ImGuiFields::RightAlignedButton(const std::string& label, glm::vec2 size)
	{
		bool pressed = false;
		ImGui::SameLine(ImGui::GetWindowWidth() - (size.x + 5.0f));
		pressed = ImGui::Button(label.c_str());
		return pressed;
	}

	bool ImGuiFields::CentreAlignedButton(const std::string& label, glm::vec2 size)
	{
		bool pressed = false;
		ImGui::SameLine((ImGui::GetWindowWidth() / 2.0f) - (0.5f * (size.x + 2.5f)));
		pressed = ImGui::Button(label.c_str());
		return pressed;
	}

	bool ImGuiFields::ShortTextField(const std::string& label, std::string& text, float columnWidth, const std::string& id)
	{
		bool changed = false;
		PushID(label, id);
		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		char buffer[256];
		memset(buffer, 0, sizeof(buffer));
		strcpy_s(buffer, sizeof(buffer), text.c_str());
		if (ImGui::InputText("##S", buffer, sizeof(buffer))) {
			text = std::string(buffer);
			changed = true;
		}
		ImGui::Columns(1);
		ImGui::PopID();
		return changed;
	}

	bool ImGuiFields::ShortTextField(const std::string& id, const std::string& label, std::string& text, float columnWidth)
	{
		return ShortTextField(label, text, columnWidth, id);
	}

	bool ImGuiFields::FloatField(const std::string& label, float* value, float resetVal, float columnWidth, const std::string& id)
	{
		bool changed = false;
		PushID(label, id);

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(1, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0.0f, 0.0f });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		if (ImGui::Button("R", buttonSize)) {
			*value = resetVal;
			changed = true;
		}

		ImGui::PopStyleColor(3);
		ImGui::SameLine();

		if (ImGui::DragFloat("##R", value, 0.1f)) changed = true;
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();
		ImGui::Columns(1);

		ImGui::PopID();
		return changed;
	}

	bool ImGuiFields::FloatField(const std::string& id, const std::string& label, float* value, float resetVal, float columnWidth)
	{
		return FloatField(label, value, resetVal, columnWidth, id);
	}

	bool ImGuiFields::Vec2Field(const std::string& label, glm::vec2& values, float resetVal, float columnWidth, const std::string& id)
	{
		float changed = false;
		PushID(label, id);

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(2, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0.0f, 0.0f });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		if (ImGui::Button("X", buttonSize)) {
			values.x = resetVal;
			changed = true;
		}

		ImGui::PopStyleColor(3);
		ImGui::SameLine();

		if (ImGui::DragFloat("##X", &values.x, 0.1f)) changed = true;
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::Dummy(ImVec2(5.0f, 0));
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.3f, 1.0f });
		if (ImGui::Button("Y", buttonSize)) {
			values.y = resetVal;
			changed = true;
		}
		ImGui::PopStyleColor(3);
		ImGui::SameLine();

		if (ImGui::DragFloat("##Y", &values.y, 0.1f)) changed = true;
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();
		ImGui::Columns(1);

		ImGui::PopID();
		return changed;
	}

	bool ImGuiFields::Vec2Field(const std::string& id, const std::string& label, glm::vec2& values, float resetVal, float columnWidth)
	{
		return Vec2Field(label, values, resetVal, columnWidth, id);
	}

	bool ImGuiFields::Vec3Field(const std::string& label, glm::vec3& values, float resetVal, float columnWidth, const std::string& id)
	{
		bool changed = false;
		PushID(label, id);

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0.0f, 0.0f });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		if (ImGui::Button("X", buttonSize)) {
			values.x = resetVal;
			changed = true;
		}
		ImGui::PopStyleColor(3);
		ImGui::SameLine();


		if (ImGui::DragFloat("##X", &values.x, 0.1f)) changed = true;
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::Dummy(ImVec2(5.0f, 0));
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.3f, 1.0f });
		if (ImGui::Button("Y", buttonSize)) {
			values.y = resetVal;
			changed = true;
		}
		ImGui::PopStyleColor(3);
		ImGui::SameLine();

		if (ImGui::DragFloat("##Y", &values.y, 0.1f)) changed = true;
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::Dummy(ImVec2(5.0f, 0));
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		if (ImGui::Button("Z", buttonSize)) {
			values.z = resetVal;
			changed = true;
		}
		ImGui::PopStyleColor(3);
		ImGui::SameLine();

		if (ImGui::DragFloat("##Z", &values.z, 0.1f)) changed = true;
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();
		ImGui::Columns(1);

		ImGui::PopID();
		return changed;
	}

	bool ImGuiFields::Vec3Field(const std::string& id, const std::string& label, glm::vec3& values, float resetVal, float columnWidth)
	{
		return Vec3Field(label, values, resetVal, columnWidth, id);
	}

	bool ImGuiFields::Vec4Field(const std::string& label, glm::vec4& values, float resetVal, float columnWidth, const std::string& id)
	{
		bool changed = false;
		PushID(label, id);

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(4, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0.0f, 0.0f });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		if (ImGui::Button("X", buttonSize)) {
			values.x = resetVal;
			changed = true;
		}

		ImGui::PopStyleColor(3);
		ImGui::SameLine();

		if (ImGui::DragFloat("##X", &values.x, 0.1f)) changed = true;
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::Dummy(ImVec2(5.0f, 0));
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.3f, 1.0f });
		if (ImGui::Button("Y", buttonSize)) {
			values.y = resetVal;
			changed = true;
		}
		ImGui::PopStyleColor(3);
		ImGui::SameLine();

		if (ImGui::DragFloat("##Y", &values.y, 0.1f)) changed = true;
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::Dummy(ImVec2(5.0f, 0));
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		if (ImGui::Button("Z", buttonSize)) {
			values.z = resetVal;
			changed = true;
		}
		ImGui::PopStyleColor(3);
		ImGui::SameLine();

		if (ImGui::DragFloat("##Z", &values.z, 0.1f)) changed = true;
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::Dummy(ImVec2(5.0f, 0));
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.2f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.3f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.2f, 0.8f, 1.0f });
		if (ImGui::Button("W", buttonSize)) {
			values.w = resetVal;
			changed = true;
		}
		ImGui::PopStyleColor(3);
		ImGui::SameLine();

		if (ImGui::DragFloat("##W", &values.w, 0.1f)) changed;
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();
		ImGui::Columns(1);

		ImGui::PopID();
		return changed;
	}

	bool ImGuiFields::Vec4Field(const std::string& id, const std::string& label, glm::vec4& values, float resetVal, float columnWidth)
	{
		return Vec4Field(label, values, resetVal, columnWidth, id);
	}

	bool ImGuiFields::Color3Field(const std::string& label, glm::vec3& color, float columnWidth, const std::string& id)
	{
		bool changed = false;
		PushID(label, id);
		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();
		changed = ImGui::ColorEdit3("", glm::value_ptr(color));
		ImGui::Columns(1);
		ImGui::PopID();
		return changed;
	}

	bool ImGuiFields::Color3Field(const std::string& id, const std::string& label, glm::vec3& color, float columnWidth)
	{
		return Color3Field(label, color, columnWidth, id);
	}

	bool ImGuiFields::Color4Field(const std::string& label, glm::vec4& color, float columnWidth, const std::string& id)
	{
		bool changed = false;
		PushID(label, id);
		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();
		changed = ImGui::ColorEdit4("", glm::value_ptr(color));
		ImGui::Columns(1);
		ImGui::PopID();
		return changed;
	}

	bool ImGuiFields::Color4Field(const std::string& id, const std::string& label, glm::vec4& color, float columnWidth)
	{
		return Color4Field(label, color, columnWidth, id);
	}

	bool ImGuiFields::Dropdown(const std::string& label, const std::vector<std::string>& options, uint32_t& currentIndex, float columnWidth, const std::string& id)
	{
		bool changed = false;
		PushID(label, id);

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());

		ImGui::NextColumn();
		if (ImGui::BeginCombo("##S", options[currentIndex].c_str())) {
			for (uint32_t i = 0; i < options.size(); i++) {
				bool isSelected = currentIndex == i;
				if (ImGui::Selectable(options[i].c_str(), isSelected)) {
					currentIndex = i;
					changed = true;
				}

				if (isSelected) ImGui::SetItemDefaultFocus(); //shows the current selected in the base box
			}

			ImGui::EndCombo();
		}

		ImGui::Columns(1);
		ImGui::PopID();
		return changed;
	}

	bool ImGuiFields::Dropdown(const std::string& id, const std::string& label, const std::vector<std::string>& options, uint32_t& currentIndex, float columnWidth)
	{
		return Dropdown(label, options, currentIndex, columnWidth, id);
	}

	void ImGuiFields::PushID(const std::string& label, const std::string& id)
	{
		if (id == "")
			ImGui::PushID(label.c_str());
		else
			ImGui::PushID(id.c_str());
	}
}