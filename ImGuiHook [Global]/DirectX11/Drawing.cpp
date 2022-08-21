#include "include.h"
void DrawLine(Vector2 pos1, Vector2 pos2, ImColor color, int thickness) {
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(pos1.x, pos1.y), ImVec2(pos2.x, pos2.y), color, thickness + 2);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(pos1.x, pos1.y), ImVec2(pos2.x, pos2.y), color, thickness);
}