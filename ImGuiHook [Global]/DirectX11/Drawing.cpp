#include "include.h"
void DrawLine(Vector2 pos1, Vector2 pos2, ImColor color, int thickness) {
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(pos1.x, pos1.y), ImVec2(pos2.x, pos2.y), color, thickness + 2);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(pos1.x, pos1.y), ImVec2(pos2.x, pos2.y), color, thickness);
}
void DrawRect(Vector2 pos, float heigth, float width, int thickness, ImColor color) {
	DrawLine({ pos.x - width / 2,pos.y }, { pos.x + width / 2,pos.y }, color, thickness);
	DrawLine({ pos.x - width / 2,pos.y }, { pos.x - width / 2,pos.y - heigth}, color, thickness);
	DrawLine({ pos.x - width / 2,pos.y - heigth }, { pos.x + width / 2,pos.y - heigth}, color, thickness);
	DrawLine({ pos.x + width / 2,pos.y - heigth }, { pos.x + width / 2,pos.y }, color, thickness);
}
void DrawChar(Vector2 pos, const char* text, ImColor color, float divide) {
	ImGui::GetBackgroundDrawList()->AddText(ImVec2(pos.x - ImGui::CalcTextSize(text).x / 2, pos.y - ImGui::CalcTextSize(text).y / divide), color, text);
}
void Draw3dBoxes(int index, ImColor color, int thickness) {
	Vector3 pos = ents[index]->Pos;
	Vector3 pos1 = ents[index]->Pos;
	Vector3 pos2 = ents[index]->Pos;
	Vector3 pos3 = ents[index]->Pos;
	Vector3 pos4 = ents[index]->Pos;
	Vector3 pos5 = ents[index]->Pos;
	Vector3 pos6 = ents[index]->Pos;
	Vector3 pos7 = ents[index]->Pos;

	pos.x -= 15.0f;
	pos.y -= 15.0f;
	pos1.x -= 15.0f;
	pos1.y += 15.0f;
	pos2.x += 15.0f;
	pos2.y += 15.0f;
	pos3.x += 15.0f;
	pos3.y -= 15.0f;

	pos4.x -= 15.0f;
	pos4.y -= 15.0f;
	pos4.z += 64.0f;
	pos5.x -= 15.0f;
	pos5.y += 15.0f;
	pos5.z += 64.0f;
	pos6.x += 15.0f;
	pos6.y += 15.0f;
	pos6.z += 64.0f;
	pos7.x += 15.0f;
	pos7.y -= 15.0f;
	pos7.z += 64.0f;

	Vector2 posscreen = PosToScreen(pos);
	Vector2 posscreen1 = PosToScreen(pos1);
	Vector2 posscreen2 = PosToScreen(pos2);
	Vector2 posscreen3 = PosToScreen(pos3);
	Vector2 posscreen4 = PosToScreen(pos4);
	Vector2 posscreen5 = PosToScreen(pos5);
	Vector2 posscreen6 = PosToScreen(pos6);
	Vector2 posscreen7 = PosToScreen(pos7);

	DrawLine(posscreen, posscreen1, color, thickness);
	DrawLine(posscreen1, posscreen2, color, thickness);
	DrawLine(posscreen2, posscreen3, color, thickness);
	DrawLine(posscreen3, posscreen, color, thickness);

	DrawLine(posscreen, posscreen4, color, thickness);
	DrawLine(posscreen1, posscreen5, color, thickness);
	DrawLine(posscreen2, posscreen6, color, thickness);
	DrawLine(posscreen3, posscreen7, color, thickness);

	DrawLine(posscreen4, posscreen5, color, thickness);
	DrawLine(posscreen5, posscreen6, color, thickness);
	DrawLine(posscreen6, posscreen7, color, thickness);
	DrawLine(posscreen7, posscreen4, color, thickness);
}