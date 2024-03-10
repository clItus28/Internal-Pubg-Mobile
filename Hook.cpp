#include "Includes.h"
#include "icon.h"
#include "Font.h"
#include "SimpleIni.h"
#include "iconcpp.h"
#include "DX11.h"
#include "DX11Window.h"
#include "Algorithm.h"
#include "Data.h"
#include "Memory.h"
#include "Aimbot.h"
#include "resources.h"
#include "api/KeyAuth.hpp"
#include <Windows.h>
#include <string>
#include <cryptolens/core.hpp>
#include <cryptolens/Error.hpp>
#include <cryptolens/Configuration_Windows.hpp>
#include <cryptolens/MachineCodeComputer_COM.hpp>

namespace cryptolens = ::cryptolens_io::v20190401;

using Cryptolens = cryptolens::basic_Cryptolens<cryptolens::Configuration_Windows<cryptolens::MachineCodeComputer_COM>>;


ID3D11Device* pDxDevice11 = (ID3D11Device*)NULL;
IDXGISwapChain* pSwapChain = (IDXGISwapChain*)NULL;
ID3D11DeviceContext* pContext = (ID3D11DeviceContext*)NULL;
ID3D11RenderTargetView* pMainRenderTargetView = (ID3D11RenderTargetView*)NULL;
HWND hWindow = (HWND)NULL;
bool firstTime = true;
bool ShowMenu = true;
ImFont* bigFont = NULL;
ImVec4* colors;
bool login = false;
char str1[60] = "";
static int curtab;
static bool checkbox;
static float slider;
static float anti;
static float aim;
static int slider1;
const char* themes[]{ "Dark Purple", "Dark Blue", "Dark Red", "Dark Green", "Light Green" };
static int curTheme = 1;
static const char* w[]{ "Ak-47", "Awp", "Scout" };
static const char* item[]{ "Head", "Body", "Arms", "Legs" };
static int combo;
static int selectedItem = 0;
static bool selected[4];
static std::string previewValue = "";

float r1;
float g1;
float b2;
float a1 = 0.5;
static const char* type[]{ "Fake-lag", "Desync" };
#define LOADERW 800
#define LOADERH 600
void CustomImGUIStyle()
{
	ImGuiIO& io = ImGui::GetIO();
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowPadding = ImVec2(4, 9);
	style.WindowRounding = 5.000f;
	style.FramePadding = ImVec2(3, 3);


	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
	style.TouchExtraPadding = ImVec2(0, 0);
	style.TabRounding = 7.0f;
	style.FrameRounding = 3.000f; // Make all elements (checkboxes, etc) circles
	style.ChildRounding = 7.0f;



	ImVec4* colors = style.Colors;
	//style.Colors[ImGuiCol_WindowBg] = ImColor(0, 0, 0, 235);
	//style.Colors[ImGuiCol_Border] = ImColor(50, 50, 50, 255);
	//// style.Colors[ImGuiCol_ChildBg] = ImVec4(5.03399e-07, 4.41989e-07, 1e-06, 0.84530);
	////style.Colors[ImGuiCol_Border] = ImColor(255, 0, 0, 255);
	//style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 1.0f);
	//style.Colors[ImGuiCol_FrameBg] = ImColor(66, 66, 66, 250);
	//style.Colors[ImGuiCol_FrameBgHovered] = ImColor(66, 66, 66, 250);
	//style.Colors[ImGuiCol_FrameBgActive] = ImColor(66, 66, 66, 250);
	//style.Colors[ImGuiCol_TitleBg] = ImColor(66, 66, 66, 255);
	//style.Colors[ImGuiCol_TitleBgCollapsed] = ImColor(66, 66, 66, 250);
	//style.Colors[ImGuiCol_TitleBgActive] = ImColor(66, 66, 66, 255);


	//style.Colors[ImGuiCol_CheckMark] = ImColor(255, 255, 255, 255);
	//style.Colors[ImGuiCol_MenuBarBg] = ImColor(66, 66, 66, 250);
	//style.Colors[ImGuiCol_SliderGrab] = ImColor(61, 133, 224, 250);
	//style.Colors[ImGuiCol_SliderGrabActive] = ImColor(61, 133, 224, 250);
	//style.Colors[ImGuiCol_Text] = ImVec4(0.98f, 0.97f, 0.93f, 1.00f);

	//style.Colors[ImGuiCol_Header] = ImColor(66, 66, 66, 250);
	//style.Colors[ImGuiCol_HeaderHovered] = ImColor(66, 66, 66, 250);
	//style.Colors[ImGuiCol_HeaderActive] = ImColor(66, 66, 66, 250);
	//style.Colors[ImGuiCol_TabHovered] = ImColor(66, 66, 66, 250);
	//colors[ImGuiCol_SliderGrabActive] = ImColor(61, 133, 224, 250);

	//style.Colors[ImGuiCol_Button] = ImColor(66, 66, 66, 250);
	//style.Colors[ImGuiCol_ButtonHovered] = ImColor(158, 158, 158, 250);
	//style.Colors[ImGuiCol_ButtonActive] = ImColor(66, 66, 66, 250);
	//colors[ImGuiCol_Header] = ImColor(66, 66, 66, 250);
	//colors[ImGuiCol_HeaderHovered] = ImColor(66, 66, 66, 250);
	//colors[ImGuiCol_HeaderActive] = ImColor(66, 66, 66, 250);
	//colors[ImGuiCol_SeparatorHovered] = ImColor(66, 66, 66, 250);
	//colors[ImGuiCol_SeparatorActive] = ImColor(66, 66, 66, 250);
	//colors[ImGuiCol_ResizeGrip] = ImColor(66, 66, 66, 250);
	//colors[ImGuiCol_ResizeGripHovered] = ImColor(66, 66, 66, 250);
	//colors[ImGuiCol_ResizeGripActive] = ImColor(66, 66, 66, 250);

	//style.Colors[ImGuiCol_PlotHistogram] = ImColor(66, 66, 66, 250);
	//style.Colors[ImGuiCol_PlotHistogramHovered] = ImColor(66, 66, 66, 250);
	//style.Colors[ImGuiCol_PlotLinesHovered] = ImColor(66, 66, 66, 250);
	//style.Colors[ImGuiCol_PlotLines] = ImColor(66, 66, 66, 250);

	//colors[ImGuiCol_PlotHistogram] = ImColor(66, 66, 66, 250);
	//colors[ImGuiCol_PlotHistogramHovered] = ImColor(66, 66, 66, 250);
	//colors[ImGuiCol_PlotLinesHovered] = ImColor(66, 66, 66, 250);
	//colors[ImGuiCol_PlotLines] = ImColor(66, 66, 66, 250);

	//style.Colors[ImGuiCol_Tab] = ImColor(33, 33, 33, 255);
	//style.Colors[ImGuiCol_TabHovered] = ImColor(66, 66, 66, 255);
	//style.Colors[ImGuiCol_TabActive] = ImColor(66, 66, 66, 255);
	//// colors[ImGuiCol_TabUnfocused] = ImVec4(0.038f, 0.050f, 0.136f, 1.000f);

	//colors[ImGuiCol_TabUnfocusedActive] = ImColor(66, 66, 66, 250);
	//colors[ImGuiCol_TextSelectedBg] = ImVec4(0.98f, 0.26f, 0.26f, 0.35f);
	//colors[ImGuiCol_NavHighlight] = ImColor(66, 66, 66, 250);
	//style.Colors[ImGuiCol_Node]
}
ImVec4 to_vec4(float r, float g, float b, float a)
{
	return ImVec4(r / 255.0, g / 255.0, b / 255.0, a / 255.0);


}
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT(__stdcall* ogWndProc)(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall hkWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	if (uMsg == WM_KEYDOWN || uMsg == WM_KEYUP)
	{
		if (GetAsyncKeyState(VK_INSERT) & 1)
		{
			ShowMenu = !ShowMenu;
		}
	}
	ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
	return CallWindowProc(ogWndProc, hWnd, uMsg, wParam, lParam);
}
ImGuiStyle* style;
ImFont* Logo;
ImFont* yep;
ImFont* yep2;
ImFont* light;
ImFont* test;
static bool opened = true;
int nsize = 12;
static int skelee = 0;
static int linne = 0;
static int hpbt = 0;
static int boxe = 0;
static int aimbp = 0;
int dissize = 12;
int Weaponsize = 12;
int hp = 12;
int vehisize = 14;
bool marco1 = false;
bool nothingm = true;
bool nothinga = false;
/////////////////////////
void WriteConfigurate(std::string Path)
{
	CSimpleIniA ini;
	ini.SetUnicode();
	SI_Error rc = ini.LoadFile(Path.c_str());
	if (rc < 0) { std::cout << "File not found"; };



	Setting::MagicBullet = ini.GetBoolValue("ESp", "key0");
	Setting::MAgicline = ini.GetDoubleValue("ESp", "Key1");
	Setting::playerBone = ini.GetBoolValue("ESp", "Key2");
	Setting::playerdeadbox = ini.GetBoolValue("ESp", "Key3");
	Setting::pcorner = ini.GetBoolValue("ESp", "Key4");
	Setting::allitemss = ini.GetBoolValue("ESp", "Key5");
	Setting::hp = ini.GetDoubleValue("ESp", "Key6");
	//	Setting::style1 = ini.GetBoolValue("style1", "Key7");
	Setting::pfullbox = ini.GetBoolValue("ESp", "Key8");
	Setting::pline = ini.GetDoubleValue("ESp", "Key9");
	Setting::botfullbox = ini.GetBoolValue("ESp", "Key10");
	Setting::fightmode = ini.GetDoubleValue("ESp", "Key11");
	Setting::botcorner = ini.GetBoolValue("ESp", "Key12");
	Setting::botblood = ini.GetBoolValue("ESp", "Key14");
	Setting::botBone = ini.GetDoubleValue("ESp", "Key13");
	Setting::botline = ini.GetBoolValue("ESp", "Key15");
	Setting::curraim = ini.GetDoubleValue("ESp", "Key16");
	Setting::botBone = ini.GetBoolValue("ESp", "Key17");

	ini.SaveFile(Path.c_str());
}
void DrawMenu()
{
	VECTOR3 Screen;
	INT Distance;
	INT EnemyCount;

	VECTOR3 HeadPos;
	VECTOR2 Head;
	VECTOR2 Chest;
	VECTOR2 Pelvis;
	VECTOR2 lSholder;
	VECTOR2 rSholder;
	VECTOR2 lElbow;
	VECTOR2 rElbow;
	VECTOR2 lWrist;
	VECTOR2 rWrist;
	VECTOR2 lThigh;
	VECTOR2 rThigh;
	VECTOR2 lKnee;
	VECTOR2 rKnee;
	VECTOR2 lAnkle;
	VECTOR2 rAnkle;
	std::string temp = "";
	std::string dist = "";
	string Text = "";
	DWORD window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;

	/*KeyAuthApp.init();*/
	/*LoadConfig("C:\\HLO.lic");*/
	if (login == false)
	{
		ImGuiIO& Io = ImGui::GetIO();
		static auto Flags1 = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;
		/*ImGui::SetNextWindowSize(ImVec2(400.0f, 115.0f));*/


		ImGui::SetNextWindowPos(ImVec2(Io.DisplaySize.x * 0.5f, Io.DisplaySize.y * 0.5f), ImGuiCond_FirstUseEver, ImVec2(0.5f, 0.5f));
		if (ImGui::Begin("Active hack", 0, Flags1))
		{
			
			
			
			//ImGui::Spacing();
			//ImGui::Spacing();
			//ImGui::SetCursorPosX({ 160.f });
			//ImGui::Text("helios v1.4.0");
			//ImGui::Spacing();
			//ImGui::SetNextItemWidth(380.0f);
			//ImGui::SetCursorPosX({ 10.0f });
			ImGui::Text("Key:");
			ImGui::SameLine();
			ImGui::SetNextItemWidth(350.000f);
			ImGui::InputText("###Key", str1, IM_ARRAYSIZE(str1), ImGuiInputTextFlags_Password);
			ImGui::Spacing();
			ImGui::Spacing();
			//ImGui::SetCursorPosX({ 50.f });
			if (ImGui::Button("Login", { 200.0f,22.0f }))
			{
				cryptolens::Error e;
				Cryptolens cryptolens_handle(e);

				// Setting up the signature verifier with credentials from "Security Settings"
				// on cryptolens.io
				cryptolens_handle.signature_verifier.set_modulus_base64(e, "qPwF2zRAlpDmqQu2uoi41y475r0iHJIJRjVQRfGyTWuZD6T+2FpwFzs6JEKDvXm7Yh3rUk84DDC5ARyZKElFgWI6M0Spq/Kcp6hrgJDPj8sY9XklZNhPOJSMDIGCbfDr57joeFReA0d4DKx26MGYJgY8t50mcSGmltMnFFCmaAxy4WAxlUtYPjG/MciQ8defUppKs4Kv2L5lC4pAXwl4bf3hO17QTrj86rfmjsbsiWVvxnDFpvRohcs/Xf37xlmAb9IOu4ciK6v0//T7smcMpZUWcaGv1szwtjjOcOgzcrMiZ7l3Ta/BohrP7GDjFrOY9tzD/f9VKO7JPZHcKE+CoQ==");
				cryptolens_handle.signature_verifier.set_exponent_base64(e, "AQAB");


				cryptolens::optional<cryptolens::LicenseKey> license_key =
					cryptolens_handle.activate(
						e,
						// SKM Access Token
						"WyI3NzIwOTgwOSIsIkhkWEtnRVhXQ2Z6ei9lTUNwa0JEUjU1eWR0TENHUXo0eTNNa1VlcHIiXQ==",
						// Product id
						24502,
						// License Key
						str1
					);


				if (e) {
					
					
				}
				else {
					login = true; // het r
				}
				


			

			}
			ImGui::SameLine();
			ImGui::SetCursorPosX({ 208.f });
			if (ImGui::Button("Get FREE key", { 190.0f,22.0f }))

			{

				ShellExecute(NULL, "open", "https://www.facebook.com/dcng0081/", NULL, NULL, SW_SHOWNORMAL);

			}
			if (ImGui::Button("Buy VIP key", { 395.0f,22.0f }))

			{

				ShellExecute(NULL, "open", "https://pornhub.com/home", NULL, NULL, SW_SHOWNORMAL);

			}
			ImGui::SetCursorPosX({ 200.f });

			/*if (SaveUsers)
			{

			}
			else
			{
			}*/



			ImGui::End();
		}

	}

	if (login == true){
	static auto Name = "Menu";
	static auto Flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;
	static auto Flags1 = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowRounding = 5.0f;
	/*static ImVec4 active = to_vec4(64, 83, 39, 255);
	static ImVec4 inactive = to_vec4(34, 61, 34, 102);*/
	/*static ImVec4 active = to_vec4(158, 158, 158, 255);
	static ImVec4 inactive = to_vec4(66, 66, 66, 255);*/
	ImGuiIO& Io = ImGui::GetIO();
	ImGui::SetNextWindowPos(ImVec2(Io.DisplaySize.x * 0.5f, Io.DisplaySize.y * 0.5f), ImGuiCond_FirstUseEver, ImVec2(0.5f, 0.5f));
	ImGui::SetNextWindowBgAlpha(0.9);
	ImGui::SetNextWindowSize({ 799.5, 600 });

	if (ImGui::Begin("HELIOS - PUBG MOBILE BETA 0.3.3", 0, Flags1))
	{


		ImGui::SameLine();
		/*ImGui::PushStyleColor(ImGuiCol_Button, Settings::Tab == 1 ? active : inactive);*/
		//////////////////////////////////////////////////////
		if (ImGui::Button(ICON_FA_HOME"  Homepage", ImVec2(155 - 6, 23)))
			Settings::Tab = 1;

		ImGui::SameLine();
		/*ImGui::PushStyleColor(ImGuiCol_Button, Settings::Tab == 2 ? active : inactive);*/
		//////////////////////////////////////////////////////
		if (ImGui::Button(ICON_FA_EYE"  ESP", ImVec2(155 - 6, 23)))
			Settings::Tab = 2;

		ImGui::SameLine();
		/*ImGui::PushStyleColor(ImGuiCol_Button, Settings::Tab == 3 ? active : inactive);*/
		//////////////////////////////////////////////////////
		if (ImGui::Button(ICON_FA_CROSSHAIRS"  Aimbot", ImVec2(155 - 6, 23)))
			Settings::Tab = 3;
		ImGui::SameLine();
		/*ImGui::PushStyleColor(ImGuiCol_Button, Settings::Tab == 4 ? active : inactive);*/
		//////////////////////////////////////////////////////
		if (ImGui::Button(ICON_FA_EDIT"  Memory", ImVec2(155 - 6, 23)))
			Settings::Tab = 4;

		ImGui::SameLine();
		/*ImGui::PushStyleColor(ImGuiCol_Button, Settings::Tab == 5 ? active : inactive);*/
		//////////////////////////////////////////////////////
		if (ImGui::Button(ICON_FA_COG"  Settings", ImVec2(155 - 6, 23)))
			Settings::Tab = 5;
		char txt_green[] = "Annoucement from Administrator: ";
		char txt_def[] = " ";
		/*ImGui::PopStyleColor(5);*/

		ImGui::Separator();

		{
			if (Settings::Tab == 1)
			{
				ImGui::BeginChild("##1", ImVec2(785, 530), true, ImGuiWindowFlags_NoScrollbar);

				ImGui::Text(ICON_FA_MALE" 999                                                                                                                                               ", ImVec2(158 - 6, 23));
				ImGui::SameLine();
				ImGui::Button("Ban record", ImVec2(125.000f, 0.000f));
				ImGui::SameLine();
				ImGui::Text("SIN (25ms)");
				ImGui::BeginChild("##2", ImVec2(783, 461), true, 0);

				{
					ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(252, 165, 1, 255));

					ImGui::Text(u8"Announcement from Admin:");
					ImGui::PopStyleColor();
					ImGui::Text(u8"The beta version might give bugs and errors unexpectedly.");
					ImGui::Text(u8"Please reach me with your feedback at clitus_28@helios.win");






					ImGui::EndChild();
					ImGui::SetNextItemWidth(775.000f);

					ImGui::InputText("##text2", txt_def, sizeof(txt_def));








				}
				ImGui::EndChild();
			}

			if (Settings::Tab == 2)
			{

				//ImGui::SetCursorPos(ImVec2(10, 10));
				ImGui::BeginChild("##1", ImVec2(792, 529.5), true, ImGuiWindowFlags_NoScrollbar);
				{

					ImGui::SetCursorPos(ImVec2(5, 5));
					ImGui::BeginChild("###2", ImVec2(230, 517.5), true, ImGuiWindowFlags_NoScrollbar);
					{
						ImGui::Checkbox(" Display name", &Setting::pname);
						ImGui::Checkbox(" Display distance", &Setting::Distancee);
						ImGui::Checkbox(" Display skeleton", &Setting::playerBone);
						ImGui::Checkbox(" Display health", &Setting::phealth);
						ImGui::Checkbox(" Display box", &Setting::pcorner);
						ImGui::Checkbox(" Display line", &Setting::pline);
						ImGui::Checkbox(" Display vehicle", &Setting::Vehicle);
						
						//ImGui::Checkbox(" Show enemy weapon", &Setting::Name);
						
						ImGui::Checkbox(" Display item", &Setting::Item);
						ImGui::Checkbox(" Display item inside lootbox", &Setting::deadbox);
						
						ImGui::Checkbox(" Display total enemy around", &Setting::TotalEnemy);
						ImGui::Checkbox(" Display radar", &Setting::dots);
						ImGui::Checkbox(" Grenade warning", &Setting::graned);
						

					}
					ImGui::EndChild();

					ImGui::SetCursorPos(ImVec2(238, 5));
					ImGui::BeginChild("###3", ImVec2(548, 517.5), true, 0);
					{
						if (ImGui::BeginTabBar("Helios")) {
							if (ImGui::BeginTabItem("Enemy settings")) {
								ImGui::BeginChild("###");
								//ImGui::SetCursorPos(ImVec2(0, 5));
								/////////////////////////////////////////////////
								ImGui::BeginChild("###4", ImVec2(540, 473), true, 0);
								{
									if (ImGui::BeginTabBar("Helios INER")) {
										if (Setting::pname)
										{
											if (ImGui::BeginTabItem("Name")) {
												ImGui::Spacing();
												ImGui::Text("Text color ");
												ImGui::SameLine();
												ImGui::ColorEdit4("Text color", (float*)&Colors::nam, ImGuiColorEditFlags_NoLabel);

												ImGui::Text("Text size ");
												ImGui::SameLine();
												ImGui::SliderInt("###4", &nsize, 0, 50);

												ImGui::EndTabItem();
											}
										}
										ImGui::SameLine();
										if (Setting::playerBone)
										{
											if (ImGui::BeginTabItem("Skeleton")) {

												ImGui::Spacing();
												ImGui::Spacing();
												ImGui::Spacing();
												ImGui::Spacing();
												ImGui::Spacing();
												ImGui::Spacing();
												ImGui::Spacing();

												ImGui::Text("Color mode");
												ImGui::SameLine();
												const char* Emu[] = { "Team ID", "Default" };

												const char* combo_label = Emu[skelee];
												if (ImGui::BeginCombo(" ", combo_label, ImGuiComboFlags_HeightSmall))
												{
													for (int n = 0; n < IM_ARRAYSIZE(Emu); n++)
													{
														const bool is_selected = (skelee == n);
														if (ImGui::Selectable(Emu[n], is_selected))
															skelee = n;
														if (is_selected)
															ImGui::SetItemDefaultFocus();
													}
													if (skelee == 0);
													//Setting::skele = true;
													else if (skelee == 1);
													//Setting::skele = false;


													ImGui::EndCombo();
												}
												if (skelee == 1)
												{
													ImGui::Text("Color ");
													ImGui::SameLine();
													ImGui::ColorEdit4(" color", (float*)&Colors::skelec, ImGuiColorEditFlags_NoLabel);
												}
												ImGui::Text("Thickness ");
												ImGui::SameLine();
												ImGui::SliderFloat("Bone size", &Setting::pbonesize, 0.100f, 3.00f);

												//ImGui::EndChild();
												ImGui::EndTabItem();
												//ImGui::EndChild();
											}
										}
										ImGui::SameLine();
										if (Setting::pline)
										{
											if (ImGui::BeginTabItem("Line")) {

												ImGui::Spacing();
												ImGui::Spacing();
												ImGui::Spacing();
												ImGui::Spacing();
												ImGui::Spacing();
												ImGui::Spacing();
												ImGui::Spacing();

												ImGui::Text("Color mode");
												ImGui::SameLine();
												const char* Emu1[] = { "Team ID", "Default" };

												const char* combo_label = Emu1[linne];
												if (ImGui::BeginCombo(" loll", combo_label, ImGuiComboFlags_HeightSmall))
												{
													for (int n = 0; n < IM_ARRAYSIZE(Emu1); n++)
													{
														const bool is_selected = (linne == n);
														if (ImGui::Selectable(Emu1[n], is_selected))
															linne = n;
														if (is_selected)
															ImGui::SetItemDefaultFocus();
													}
													if (linne == 0);
													//Setting::skele = true;
													else if (linne == 1);
													//Setting::skele = false;


													ImGui::EndCombo();
												}
												if (linne == 1)
												{
													ImGui::Text("Line color ");
													ImGui::SameLine();
													ImGui::ColorEdit4(" color1", (float*)&Colors::playerline, ImGuiColorEditFlags_NoLabel);
												}
												ImGui::Text("Thickness ");
												ImGui::SameLine();
												ImGui::SliderFloat("Line size", &Setting::plinesize, 0.100f, 3.00f);


												//ImGui::EndTabItem();


												ImGui::EndTabItem();
											}
										}
										ImGui::SameLine();
										if (Setting::Distancee)
										{
											if (ImGui::BeginTabItem("Distance")) {
												ImGui::Spacing();
												ImGui::Spacing();
												ImGui::Spacing();
												ImGui::Spacing();
												ImGui::Spacing();
												ImGui::Spacing();
												ImGui::Spacing();
												ImGui::Text("Distance color ");
												ImGui::SameLine();
												ImGui::ColorEdit4(" color11", (float*)&Colors::enemy, ImGuiColorEditFlags_NoLabel);

												ImGui::Text("Thickness ");
												ImGui::SameLine();
												ImGui::SliderInt("Distance size", &dissize, 0, 25);

												ImGui::EndTabItem();
											}
										}
										ImGui::SameLine();
										if (Setting::phealth)
										{
											if (ImGui::BeginTabItem("Health")) {

												ImGui::Spacing();
												ImGui::Spacing();
												ImGui::Spacing();
												ImGui::Spacing();
												ImGui::Spacing();
												ImGui::Spacing();
												ImGui::Spacing();

												ImGui::Text("Display mode");
												ImGui::SameLine();
												const char* Emu2[] = { "Show as bar", "Show as text" };

												const char* combo_label = Emu2[hpbt];
												if (ImGui::BeginCombo(" loll1", combo_label, ImGuiComboFlags_HeightSmall))
												{
													for (int n = 0; n < IM_ARRAYSIZE(Emu2); n++)
													{
														const bool is_selected = (hpbt == n);
														if (ImGui::Selectable(Emu2[n], is_selected))
															hpbt = n;
														if (is_selected)
															ImGui::SetItemDefaultFocus();
													}
													if (hpbt == 0);
													//Setting::skele = true;
													else if (hpbt == 1);
													//Setting::skele = false;


													ImGui::EndCombo();
												}

												if (hpbt == 1)
												{
													ImGui::Text("Text color ");
													ImGui::SameLine();
													ImGui::ColorEdit4(" colorhp", (float*)&Colors::hpt, ImGuiColorEditFlags_NoLabel);

													ImGui::Text("Text size ");
													ImGui::SameLine();
													ImGui::SliderInt("Health size", &hp, 0, 25);
												}


												ImGui::EndTabItem();
											}
										}
										ImGui::SameLine();
										if (Setting::pcorner)
										{
											if (ImGui::BeginTabItem("Box")) {

												ImGui::Spacing();
												ImGui::Spacing();
												ImGui::Spacing();
												ImGui::Spacing();
												ImGui::Spacing();
												ImGui::Spacing();
												ImGui::Spacing();

												ImGui::Text("Display mode");
												ImGui::SameLine();
												const char* Emu3[] = { "4 edges", "Rectangle" };

												const char* combo_label = Emu3[boxe];
												if (ImGui::BeginCombo(" loll11", combo_label, ImGuiComboFlags_HeightSmall))
												{
													for (int n = 0; n < IM_ARRAYSIZE(Emu3); n++)
													{
														const bool is_selected = (boxe == n);
														if (ImGui::Selectable(Emu3[n], is_selected))
															boxe = n;
														if (is_selected)
															ImGui::SetItemDefaultFocus();
													}
													if (boxe == 0);
													//Setting::skele = true;
													else if (boxe == 1);
													//Setting::skele = false;


													ImGui::EndCombo();
												}
												if (boxe == 0)
												{
													ImGui::Text("Thickness ");
													ImGui::SameLine();
													ImGui::SliderFloat("###1", &Setting::pcornersize, 0.100f, 2.00f);
												}
												else if (boxe == 1)
												{
													ImGui::Text("Thickness ");
													ImGui::SameLine();
													ImGui::SliderFloat("###2", &Setting::pfullboxsize, 0.100f, 2.00f);
												}

												ImGui::EndTabItem();
											}
										}
										/*ImGui::SameLine();
										if (Setting::dots)
										{
											if (ImGui::BeginTabItem("Radar")) {


												ImGui::EndTabItem();
											}
										}*/

									}
									ImGui::EndTabBar();


								}
								ImGui::EndChild();

								ImGui::EndChild();
								ImGui::EndTabItem();
							}
							//ImGui::SameLine();
							if (Setting::graned)
							{
								if (ImGui::BeginTabItem("Grenade")) {

									/*ImGui::Spacing();
									ImGui::Spacing();
									ImGui::Spacing();
									ImGui::Spacing();
									ImGui::Spacing();
									ImGui::Spacing();
									ImGui::Spacing();*/
									ImGui::Checkbox("Grenade warning", &Setting::grw);
									ImGui::Checkbox("Molotow warning", &Setting::molow);

									ImGui::EndTabItem();
								}
							}
							//ImGui::SameLine();
							if (Setting::Vehicle)
							{
								if (ImGui::BeginTabItem("Vehicle")) {

									/*ImGui::Spacing();
									ImGui::Spacing();
									ImGui::Spacing();
									ImGui::Spacing();
									ImGui::Spacing();
									ImGui::Spacing();
									ImGui::Spacing();*/
									ImGui::Text("Text color ");
									ImGui::SameLine();
									ImGui::ColorEdit4(" vehiclec", (float*)&Colors::vehicle, ImGuiColorEditFlags_NoLabel);

									ImGui::Text("Text size ");
									ImGui::SameLine();
									ImGui::SliderInt("vehicle size", &vehisize, 0, 25);


									ImGui::EndTabItem();
								}
							}

							//ImGui::SameLine();
							if (Setting::Item)
							{
								if (ImGui::BeginTabItem("Items")) {
									ImGui::BeginChild("###1");
									//ImGui::SetCursorPos(ImVec2(0, 5));
									//ImGui::BeginChild("###121", ImVec2(540, 468), true, 0);
									{
										if (ImGui::BeginTabBar("Helios INER1")) {

											if (ImGui::BeginTabItem("Weapon")) {
												ImGui::BeginChild("###1211", ImVec2(535, 450), true, 0);
												{

													ImGui::Checkbox("M416", &Setting::Esp_Item_M416);
													ImGui::SameLine();
													ImGui::SetCursorPosX({ 170 });
													ImGui::ColorEdit4("M416", (float*)&weapon::m16, ImGuiColorEditFlags_NoLabel);
													ImGui::Checkbox("AKM", &Setting::Esp_Item_AKM);
													ImGui::SameLine();
													ImGui::SetCursorPosX({ 170 });
													ImGui::ColorEdit4("AKM", (float*)&weapon::AKM, ImGuiColorEditFlags_NoLabel);
													ImGui::Checkbox("SCAR-L", &Setting::Esp_Item_SCARL);
													ImGui::SameLine();
													ImGui::SetCursorPosX({ 170 });
													ImGui::ColorEdit4("SCAR-L", (float*)&weapon::scarl, ImGuiColorEditFlags_NoLabel);
													ImGui::Checkbox("M762", &Setting::Esp_Item_M762);
													ImGui::SameLine();
													ImGui::SetCursorPosX({ 170 });
													ImGui::ColorEdit4("M762", Setting::Esp_Item_M762_Color, ImGuiColorEditFlags_NoLabel);
													ImGui::Checkbox("DP28", &Setting::Esp_Item_DP28);
													ImGui::SameLine();
													ImGui::SetCursorPosX({ 170 });
													ImGui::ColorEdit4("DP28", Setting::Esp_Item_DP28_Color, ImGuiColorEditFlags_NoLabel);
													ImGui::Checkbox("AWM", &Setting::Esp_Item_Awm);
													ImGui::SameLine();
													ImGui::SetCursorPosX({ 170 });
													ImGui::ColorEdit4("AMW", (float*)&weapon::AWM, ImGuiColorEditFlags_NoLabel);
													ImGui::Checkbox("M24", &Setting::Esp_Item_M24);
													ImGui::SameLine();
													ImGui::SetCursorPosX({ 170 });
													ImGui::ColorEdit4("M24", (float*)&weapon::M24, ImGuiColorEditFlags_NoLabel);
													ImGui::Checkbox("KAR98", &Setting::Esp_Item_Kar98k);
													ImGui::SameLine();
													ImGui::SetCursorPosX({ 170 });
													ImGui::ColorEdit4("kar98", (float*)&weapon::kar98, ImGuiColorEditFlags_NoLabel);
													ImGui::Checkbox("Flare Gun", &Setting::Esp_Item_FlareGun);
													ImGui::SameLine();
													ImGui::SetCursorPosX({ 170 });
													ImGui::ColorEdit4("Flare", (float*)&weapon::Flaregun, ImGuiColorEditFlags_NoLabel);
													ImGui::Checkbox("G36C", &Setting::Esp_Item_G36C);
													ImGui::SameLine();
													ImGui::SetCursorPosX({ 170 });
													ImGui::ColorEdit4("G36C", (float*)&Setting::Esp_Item_G36C_Color, ImGuiColorEditFlags_NoLabel);
													ImGui::Checkbox("QBZ", &Setting::Esp_Item_QBZ);
													ImGui::SameLine();
													ImGui::SetCursorPosX({ 170 });
													ImGui::ColorEdit4("QBZ", (float*)&Setting::Esp_Item_QBZ_Color, ImGuiColorEditFlags_NoLabel);
													ImGui::Checkbox("QBU", &Setting::Esp_Item_QBU);
													ImGui::SameLine();
													ImGui::SetCursorPosX({ 170 });
													ImGui::ColorEdit4("QBU", (float*)&Setting::Esp_Item_QBU_Color, ImGuiColorEditFlags_NoLabel);
													ImGui::Checkbox("SLR", &Setting::Esp_Item_SLR);
													ImGui::SameLine();
													ImGui::SetCursorPosX({ 170 });
													ImGui::ColorEdit4("SLR", (float*)&Setting::Esp_Item_SLR_Color, ImGuiColorEditFlags_NoLabel);
													ImGui::Checkbox("SKS", &Setting::Esp_Item_SKS);
													ImGui::SameLine();
													ImGui::SetCursorPosX({ 170 });
													ImGui::ColorEdit4("SKS", (float*)&Setting::Esp_Item_SKS_Color, ImGuiColorEditFlags_NoLabel);
													ImGui::Checkbox("Mini14", &Setting::Esp_Item_Mini14);
													ImGui::SameLine();
													ImGui::SetCursorPosX({ 170 });
													ImGui::ColorEdit4("Mini14", (float*)&Setting::Esp_Item_Mini14_Color, ImGuiColorEditFlags_NoLabel);
													ImGui::Checkbox("PP19", &Setting::Esp_Item_PP19);
													ImGui::SameLine();
													ImGui::SetCursorPosX({ 170 });
													ImGui::ColorEdit4("PP19", (float*)&Setting::Esp_Item_PP19_Color, ImGuiColorEditFlags_NoLabel);
													ImGui::Checkbox("Tommy Gun", &Setting::Esp_Item_TommyGun);
													ImGui::SameLine();
													ImGui::SetCursorPosX({ 170 });
													ImGui::ColorEdit4("Tommy", (float*)&Setting::Esp_Item_TommyGun_Color, ImGuiColorEditFlags_NoLabel);
													ImGui::Checkbox("MP5K", &Setting::Esp_Item_MP5K);
													ImGui::SameLine();
													ImGui::SetCursorPosX({ 170 });
													ImGui::ColorEdit4("MP5K", (float*)&Setting::Esp_Item_MP5K_Color, ImGuiColorEditFlags_NoLabel);
													ImGui::Checkbox("UMP9", &Setting::Esp_Item_UMP9);
													ImGui::SameLine();
													ImGui::SetCursorPosX({ 170 });
													ImGui::ColorEdit4("UMP9", (float*)&Setting::Esp_Item_UMP9_Color, ImGuiColorEditFlags_NoLabel);
													ImGui::Checkbox("Vector", &Setting::Esp_Item_Vector);
													ImGui::SameLine();
													ImGui::SetCursorPosX({ 170 });
													ImGui::ColorEdit4("Vector", (float*)&Setting::Esp_Item_Vector_Color, ImGuiColorEditFlags_NoLabel);
													ImGui::Checkbox("Uzi", &Setting::Esp_Item_Uzi);
													ImGui::SameLine();
													ImGui::SetCursorPosX({ 170 });
													ImGui::ColorEdit4("Uzi", (float*)&Setting::Esp_Item_Uzi_Color, ImGuiColorEditFlags_NoLabel);
													ImGui::Checkbox("Mk47-Mutant", &Setting::Esp_Item_Mk47Mutant);
													ImGui::SameLine();
													ImGui::SetCursorPosX({ 170 });
													ImGui::ColorEdit4("Mk47-Mutant", (float*)&Setting::Esp_Item_Mk47Mutant_Color, ImGuiColorEditFlags_NoLabel);



												}//, ImGuiColorEditFlags_NoLabel);
												ImGui::EndChild();

												ImGui::EndTabItem();
											}

											//ImGui::SameLine();


											if (ImGui::BeginTabItem("Grenade")) {

												ImGui::Checkbox("Frag", &Setting::Esp_Item_Frag);
												ImGui::SameLine();
												ImGui::SetCursorPosX({ 170 });
												ImGui::ColorEdit4("Frag", Setting::Esp_Item_Frag_Color, ImGuiColorEditFlags_NoLabel);
												ImGui::Checkbox("Smoke", &Setting::Esp_Item_Smoke);
												ImGui::SameLine();
												ImGui::SetCursorPosX({ 170 });
												ImGui::ColorEdit4("Smoke", Setting::Esp_Item_Smoke_Color, ImGuiColorEditFlags_NoLabel);
												ImGui::Checkbox("Molotof", &Setting::Esp_Item_Molotof);
												ImGui::SameLine();
												ImGui::SetCursorPosX({ 170 });
												ImGui::ColorEdit4("Molotof", Setting::Esp_Item_Molotof_Color, ImGuiColorEditFlags_NoLabel);


												ImGui::EndTabItem();

											}

											//ImGui::SameLine();


											if (ImGui::BeginTabItem("Health")) {

												ImGui::Checkbox("Med Kit", &Setting::Esp_Item_MedKit);
												ImGui::SameLine();
												ImGui::SetCursorPosX({ 170 });
												ImGui::ColorEdit4("Med Kit", Setting::Esp_Item_MedKit_Color, ImGuiColorEditFlags_NoLabel);
												ImGui::Checkbox("First Aid Kit", &Setting::Esp_Item_FirstAidKit);
												ImGui::SameLine();
												ImGui::SetCursorPosX({ 170 });
												ImGui::ColorEdit4("First Aid Kit", Setting::Esp_Item_FirstAidKit_Color, ImGuiColorEditFlags_NoLabel);
												ImGui::Checkbox("Painkiller", &Setting::Esp_Item_Painkiller);
												ImGui::SameLine();
												ImGui::SetCursorPosX({ 170 });
												ImGui::ColorEdit4("Painkiller", Setting::Esp_Item_Painkiller_Color, ImGuiColorEditFlags_NoLabel);
												ImGui::Checkbox("Energy Drink", &Setting::Esp_Item_EnergyDrink);
												ImGui::SameLine();
												ImGui::SetCursorPosX({ 170 });
												ImGui::ColorEdit4("Energy Drink", Setting::Esp_Item_EnergyDrink_Color, ImGuiColorEditFlags_NoLabel);
												ImGui::Checkbox("Adrenaline Syringe", &Setting::Esp_Item_AdrenalineSyringe);
												ImGui::SameLine();
												ImGui::SetCursorPosX({ 170 });
												ImGui::ColorEdit4("Adrenaline Syringe", Setting::Esp_Item_AdrenalineSyringe_Color, ImGuiColorEditFlags_NoLabel);



												ImGui::EndTabItem();
											}

											//ImGui::SameLine();

											if (ImGui::BeginTabItem("Bag")) {

												ImGui::Checkbox("Bag 1", &Setting::Esp_Item_Bag1);
												ImGui::SameLine();
												ImGui::SetCursorPosX({ 170 });
												ImGui::ColorEdit4("Bag 1", Setting::Esp_Item_Bag1_Color, ImGuiColorEditFlags_NoLabel);

												ImGui::Checkbox("Bag 2", &Setting::Esp_Item_Bag2);
												ImGui::SameLine();
												ImGui::SetCursorPosX({ 170 });
												ImGui::ColorEdit4("Bag 2", Setting::Esp_Item_Bag2_Color, ImGuiColorEditFlags_NoLabel);
												ImGui::Checkbox("Bag 3", &Setting::Esp_Item_Bag3);
												ImGui::SameLine();
												ImGui::SetCursorPosX({ 170 });
												ImGui::ColorEdit4("Bag 3", Setting::Esp_Item_Bag3_Color, ImGuiColorEditFlags_NoLabel);

												ImGui::EndTabItem();
											}

											//ImGui::SameLine();


											if (ImGui::BeginTabItem("Helmet")) {


												ImGui::Checkbox("Helmet 1", &Setting::Esp_Item_Helmet1);
												ImGui::SameLine();
												ImGui::SetCursorPosX({ 170 });
												ImGui::ColorEdit4("Helmet 1", Setting::Esp_Item_Helmet1_Color, ImGuiColorEditFlags_NoLabel);
												ImGui::Checkbox("Helmet 2", &Setting::Esp_Item_Helmet2);
												ImGui::SameLine();
												ImGui::SetCursorPosX({ 170 });
												ImGui::ColorEdit4("Helmet 2", Setting::Esp_Item_Helmet2_Color, ImGuiColorEditFlags_NoLabel);
												ImGui::Checkbox("Helmet 3", &Setting::Esp_Item_Helmet3);
												ImGui::SameLine();
												ImGui::SetCursorPosX({ 170 });
												ImGui::ColorEdit4("Helmet 3", Setting::Esp_Item_Helmet3_Color, ImGuiColorEditFlags_NoLabel);


												ImGui::EndTabItem();
											}

											//ImGui::SameLine();

											if (ImGui::BeginTabItem("Armor")) {

												ImGui::Checkbox("Armor 1", &Setting::Esp_Item_Armor1);
												ImGui::SameLine();
												ImGui::SetCursorPosX({ 170 });
												ImGui::ColorEdit4("Armor 1", Setting::Esp_Item_Armor1_Color, ImGuiColorEditFlags_NoLabel);
												ImGui::Checkbox("Armor 2", &Setting::Esp_Item_Armor2);
												ImGui::SameLine();
												ImGui::SetCursorPosX({ 170 });
												ImGui::ColorEdit4("Armor 2", Setting::Esp_Item_Armor2_Color, ImGuiColorEditFlags_NoLabel);
												ImGui::Checkbox("Armor 3", &Setting::Esp_Item_Armor3);
												ImGui::SameLine();
												ImGui::SetCursorPosX({ 170 });
												ImGui::ColorEdit4("Armor 3", Setting::Esp_Item_Armor3_Color, ImGuiColorEditFlags_NoLabel);

												ImGui::EndTabItem();
											}

											//ImGui::SameLine();

											if (ImGui::BeginTabItem("Ammo")) {

												ImGui::Checkbox("7.62mm", &Setting::Esp_Item_762mm);
												ImGui::SameLine();
												ImGui::SetCursorPosX({ 170 });
												ImGui::ColorEdit4("762mm", (float*)&Setting::Esp_Item_762mm_Color, ImGuiColorEditFlags_NoLabel);
												ImGui::Checkbox("5.56mm", &Setting::Esp_Item_556mm);
												ImGui::SameLine();
												ImGui::SetCursorPosX({ 170 });
												ImGui::ColorEdit4("556mm", (float*)&Setting::Esp_Item_556mm_Color, ImGuiColorEditFlags_NoLabel);
												ImGui::Checkbox("9mm", &Setting::Esp_Item_9mm);
												ImGui::SameLine();
												ImGui::SetCursorPosX({ 170 });
												ImGui::ColorEdit4("9mm", (float*)&Setting::Esp_Item_9mm_Color, ImGuiColorEditFlags_NoLabel);
												ImGui::Checkbox(".45ACP", &Setting::Esp_Item_45ACP);
												ImGui::SameLine();
												ImGui::SetCursorPosX({ 170 });
												ImGui::ColorEdit4("45ACP", (float*)&Setting::Esp_Item_45ACP_Color, ImGuiColorEditFlags_NoLabel);
												ImGui::Checkbox("AWM Ammo", &Setting::Esp_Item_Awmimo);
												ImGui::SameLine();
												ImGui::SetCursorPosX({ 170 });
												ImGui::ColorEdit4(".300 Magnum", (float*)&weapon::AWMimmo, ImGuiColorEditFlags_NoLabel);

												ImGui::EndTabItem();
											}

											//ImGui::SameLine();

											if (ImGui::BeginTabItem("Attachments")) {

												ImGui::Checkbox("Holo", &Setting::Esp_Item_Holo);
												ImGui::SameLine();
												ImGui::SetCursorPosX({ 170 });
												ImGui::ColorEdit4("Holo", (float*)&Setting::Esp_Item_Holo_Color, ImGuiColorEditFlags_NoLabel);
												ImGui::Checkbox("x2 Scope", &Setting::Esp_Item_x2);
												ImGui::SameLine();
												ImGui::SetCursorPosX({ 170 });
												ImGui::ColorEdit4("2X", Setting::Esp_Item_x2_Color, ImGuiColorEditFlags_NoLabel);
												ImGui::Checkbox("x3 Scope", &Setting::Esp_Item_x3);
												ImGui::SameLine();
												ImGui::SetCursorPosX({ 170 });
												ImGui::ColorEdit4("3X", Setting::Esp_Item_x3_Color, ImGuiColorEditFlags_NoLabel);
												ImGui::Checkbox("x4 Scope", &Setting::Esp_Item_x4);
												ImGui::SameLine();
												ImGui::SetCursorPosX({ 170 });
												ImGui::ColorEdit4("4X", Setting::Esp_Item_x4_Color, ImGuiColorEditFlags_NoLabel);
												ImGui::Checkbox("x6 Scope", &Setting::Esp_Item_x6);
												ImGui::SameLine();
												ImGui::SetCursorPosX({ 170 });
												ImGui::ColorEdit4("6X", Setting::Esp_Item_x6_Color, ImGuiColorEditFlags_NoLabel);
												ImGui::Checkbox("x8 Scope", &Setting::Esp_Item_x8);
												ImGui::SameLine();
												ImGui::SetCursorPosX({ 170 });
												ImGui::ColorEdit4("8X", Setting::Esp_Item_x8_Color, ImGuiColorEditFlags_NoLabel);


												ImGui::EndTabItem();
											}

											//ImGui::SameLine();

											if (ImGui::BeginTabItem("Others")) {

												ImGui::Checkbox("Dead box", &Setting::deadbox);
												ImGui::SameLine();
												ImGui::SetCursorPosX({ 170 });
												ImGui::ColorEdit4("Dead Box ", (float*)&Colors::deadbox, ImGuiColorEditFlags_NoLabel);
												ImGui::Checkbox("Box item list", &Setting::playerdeadbox);
												ImGui::SameLine();
												ImGui::SetCursorPosX({ 170 });
												ImGui::ColorEdit4("hiiiii", (float*)&Colors::deadboxitem, ImGuiColorEditFlags_NoLabel);

												ImGui::EndTabItem();
											}



										}
										ImGui::EndTabBar();


									}
									//ImGui::EndChild();

									ImGui::EndChild();
									ImGui::EndTabItem();
								}
								ImGui::SameLine();

							}
							/*ImGui::SameLine();
							if (ImGui::BeginTabItem("Teammate")) {



								ImGui::EndTabItem();
							}*/
						}
						ImGui::EndTabBar();


					}
					ImGui::EndChild();

				}
				ImGui::EndChild();













			}

				if (Settings::Tab == 3)
						{

							//ImGui::SetCursorPos(ImVec2(10, 10));
							ImGui::BeginChild("##2", ImVec2(793, 535), true, 0);
							{

								ImGui::SetCursorPos(ImVec2(5, 5));
								ImGui::BeginChild("###1", ImVec2(230, 520), true, 0);
								{
									ImGui::Checkbox(" Aimbot", &Setting::MagicBullet);
									ImGui::Checkbox(" Marco", &marco1);


								}
								ImGui::EndChild();

								ImGui::SetCursorPos(ImVec2(238, 5));
								ImGui::BeginChild("###2", ImVec2(548, 520), true, 0);
								{
									if (ImGui::BeginTabBar("Helios")) {
										if (Setting::MagicBullet)
										{
											if (ImGui::BeginTabItem("Aim settings")) {
												ImGui::Text("Pickup a Gun to activate Bullet Tracking, no need to fire, press P to fix if not work");
												ImGui::Checkbox("Auto repair Slient Aim when detect game changes.", &nothingm);
												ImGui::Checkbox("Enable aimbot also", &Setting::Aimbot);
												
												





												ImGui::EndTabItem();
											}
										}
										//ImGui::SameLine();
										if (Setting::MagicBullet)
										{
											
											ImGui::Text("Aimbot location");
											ImGui::SameLine();
											const char* aimb[] = { "Head", "Body", "Pelvis" };

											const char* combo_label = aimb[Setting::curraim];

											if (ImGui::BeginCombo(" ", combo_label, ImGuiComboFlags_HeightSmall))
											{
												for (int n = 0; n < IM_ARRAYSIZE(aimb); n++)
												{
													const bool is_selected = (Setting::curraim == n);
													if (ImGui::Selectable(aimb[n], is_selected))
														Setting::curraim = n;
													if (is_selected)
														ImGui::SetItemDefaultFocus();
												}

												ImGui::EndCombo();
											}

												//ImGui::Text("Aimbot key");
												//ImGui::SameLine();
												///*ImGui::Hotkey("##AimbotKey ", &Setting::AimbotKey, ImVec2(180.0f, 24));*/


												//const char* enginetype[] = { "Mouse Event","Silent Aim", "Memory aim"};

												//const char* enginelabel = enginetype[Setting::engine];

												//ImGui::Text("Aim method");
												//ImGui::SameLine();
												//if (ImGui::BeginCombo(" AimcEngine", enginelabel, ImGuiComboFlags_HeightSmall))
												//{
												//	for (int n = 0; n < IM_ARRAYSIZE(enginetype); n++)
												//	{
												//		/*const bool is_selectedd = (item_current_Aim == n);
												//		if (ImGui::Selectable(enginetype[n], is_selectedd))
												//			Setting::engine = n;
												//		if (is_selectedd)
												//			ImGui::SetItemDefaultFocus();*/
												//	}

												//	ImGui::EndCombo();
												//}

												/*ImGui::Text("Aim FOV");
												ImGui::SameLine();*/
												//ImGui::SliderFloat("###fovFOVsize", &Setting::fovcircleredus, 1.0f, 2000.0f);
												///*ImGui::Text("Aim speed");
												//ImGui::SameLine();
												//ImGui::SliderFloat("###fovFOVspeed", &Setting::Aimspeed, 0.0f, 15.0f);*/
												//ImGui::Checkbox("Show FOV circle", &Setting::fovcircle);
												ImGui::Checkbox("Aim knocked Enemy", &Setting::knocked);

												/*ImGui::Text(" - Trigger key:");
												ImGui::SameLine();
												ImGui::Hotkey("###Enable ", &Setting::EnableKey, ImVec2(180.0f, 24));*/

												ImGui::Separator();
												ImGui::Checkbox("Draw current aiming enemy line", &Setting::MAgicline);

												ImGui::EndTabItem();
											
										}
										//ImGui::SameLine();
										int marco = 0;
										/*if (marco1)
										{
											if (ImGui::BeginTabItem("Marco")) {

												ImGui::Text("Marco value");
												ImGui::SameLine();

												ImGui::SliderInt("###marco", &marco, 1, 15);

												ImGui::EndTabItem();
											}
										}*/

									}
									ImGui::EndTabBar();


								}
								ImGui::EndChild();

							}
							ImGui::EndChild();
						}

			/*if (Settings::Tab == 3)
			{
				ImGui::Checkbox("Enable", &Setting::MagicBullet);
				ImGui::SameLine();

				const char* aimb[] = { "Head", "Body", "Pelvis" };

				const char* combo_label = aimb[Setting::curraim];

				if (ImGui::BeginCombo(" ", combo_label, ImGuiComboFlags_HeightSmall))
				{
					for (int n = 0; n < IM_ARRAYSIZE(aimb); n++)
					{
						const bool is_selected = (Setting::curraim == n);
						if (ImGui::Selectable(aimb[n], is_selected))
							Setting::curraim = n;
						if (is_selected)
							ImGui::SetItemDefaultFocus();
					}

					ImGui::EndCombo();
				}
				ImGui::Checkbox("Skip knocked", &Setting::knocked);
				ImGui::Checkbox("Aim line", &Setting::MAgicline);




				if (Setting::MAgicline)
				{
					ImGui::SameLine();
					ImGui::ColorEdit4("#\ ", (float*)&Colors::magicline, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs);

				}


				ImGui::Checkbox("FOV", &Setting::fovcircle);



				if (Setting::fovcircle)
				{

					ImGui::SameLine();
					ImGui::SliderFloat("###fovFOVsize", &Setting::fovcircleredus, 1.0f, 2000.0f);
					ImGui::SameLine();
					ImGui::ColorEdit4("\ ", (float*)&Colors::fovcirclecolor, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs);









				}

				ImGui::Checkbox("Prediction", &Setting::AimPrediction);;



				if (Setting::AimPrediction)
				{
					ImGui::SameLine();
					ImGui::SliderInt("####1", &Setting::magicv, 0, 50);

				}







			}*/


			if (Settings::Tab == 4)
			{

				if (Setting::Brutall)
				{
					//ImGui::SetCursorPos(ImVec2(10, 10));
					ImGui::BeginChild("##2", ImVec2(793, 535), true, 0);
					{

						ImGui::SetCursorPos(ImVec2(5, 5));
						ImGui::BeginChild("###1", ImVec2(230, 517.5), true, 0);
						{

							ImGui::Checkbox(" 360 Magic", &Setting::CameraCatch);
							//ImGui::Checkbox(" Fast Run", &Setting::fastrun);
							////ImGui::Checkbox(" Fast Run v2", &Setting::playerBone);
							//ImGui::Checkbox(" Fast Car", &Setting::speedcar);
							//ImGui::Checkbox(" Fly Car", &Setting::carfly);
							//ImGui::Checkbox(" Fast parachute", &Setting::playerBone);
							/*ImGui::Checkbox(" Fly Man", &Setting::fly);*/
							ImGui::Checkbox(" No Recoil", &Setting::recoil);
							ImGui::Checkbox(" Instant hit", &Setting::instanthit);
							ImGui::Checkbox(" Spinbot", &Setting::spinbot);
							/*ImGui::Checkbox(" X Effect", &Setting::MagicX);*/
							/*ImGui::Checkbox(" GodView", &Setting::GodView);*/
							/*ImGui::Checkbox(" Loofy", &Setting::loofy);
							ImGui::Checkbox(" Fast Land", &Setting::fastland);
							ImGui::Checkbox(" Ipad View", &Setting::ipad);*/


						}
						ImGui::EndChild();

						ImGui::SetCursorPos(ImVec2(238, 5));
						ImGui::BeginChild("###2", ImVec2(548, 517.5), true, 0);
						{


							if (Setting::fastrun)
							{
								if (ImGui::TreeNodeEx("Fast run"))
								{
									ImGui::Indent();
									ImGui::SliderFloat("####2", &Setting::fastRunPower, 1.0f, 20.0f);
									ImGui::Text("Fast run key");
									ImGui::SameLine();
									//ImGui::Hotkey("##fastrunKey ", &Setting::fastrunkey, ImVec2(180.0f, 24));
									ImGui::Unindent();
									ImGui::TreePop();
								}
							}

							if (Setting::speedcar)
							{
								if (ImGui::TreeNodeEx("Fast car"))
								{
									ImGui::Indent();
									ImGui::SliderFloat("####3", &Setting::speedCarPower, 1.0f, 500.0f);
									ImGui::Unindent();
									ImGui::TreePop();
								}
							}

							if (Setting::carfly)
							{
								if (ImGui::TreeNodeEx("Fly car"))
								{
									ImGui::Indent();
									ImGui::SliderFloat("####4", &Setting::flyCarPower, 1.0f, 500.0f);
									ImGui::Unindent();
									ImGui::TreePop();
								}
							}

							if (Setting::instanthit)
							{
								if (ImGui::TreeNodeEx("Instant hit"))
								{
									ImGui::Indent();
									ImGui::SliderFloat("####5", &Setting::instantPower, 1.0f, 850000.0f);
									ImGui::Unindent();
									ImGui::TreePop();
								}
							}

							if (Setting::fastland)
							{
								if (ImGui::TreeNodeEx("Fast Land"))
								{
									ImGui::Indent();
									ImGui::SliderFloat("####6", &Setting::landPower, 1.0f, 40000.0f);
									ImGui::Unindent();
									ImGui::TreePop();
								}
							}

							if (Setting::ipad)
							{
								if (ImGui::TreeNodeEx("Ipad View"))
								{
									ImGui::Indent();
									ImGui::SliderFloat("####7", &Setting::ipadPower, 1.0f, 400.0f);
									{
										//Tools::WriteUE4Float(Offset::IpadOffset, Setting::ipadPower);
									}
									ImGui::Unindent();
									ImGui::TreePop();
								}
							}

							if (Setting::fly)
							{
								if (ImGui::TreeNodeEx("Fly Man"))
								{
									ImGui::Indent();
									ImGui::SliderFloat("####8", &Setting::flyManPower, 1.0f, 90000.0f);
									ImGui::Unindent();
									ImGui::TreePop();
								}
							}

							//if (Setting::GodView)
							//{
							//	if (ImGui::TreeNodeEx("Good View"))
							//	{
							//		ImGui::Indent();
							//		ImGui::SliderFloat("####9", &Setting::flyManPower, 1.0f, 90000.0f);
							//		ImGui::Text(" UP GoodView");
							//		ImGui::SameLine();
							//		//ImGui::Hotkey("###1Enable ", &Setting::godviewup, ImVec2(180.0f, 24));

							//		ImGui::Text(" Down GoodView");
							//		ImGui::SameLine();
							//		//ImGui::Hotkey("###2Enable ", &Setting::godviewdown, ImVec2(180.0f, 24));

							//		ImGui::Text(" Front GoodView");
							//		ImGui::SameLine();
							//		//ImGui::Hotkey("###3Enable ", &Setting::godviewFr, ImVec2(180.0f, 24));
							//		ImGui::Unindent();
							//		ImGui::TreePop();
							//	}
							//}



						}
						ImGui::EndChild();

					}
					ImGui::EndChild();
				}
			}


			if (Settings::Tab == 5)
			{
				//ImGui::SetCursorPos(ImVec2(10, 10));
				ImGui::BeginChild("##5", ImVec2(793, 535), true, 0);
				{

					ImGui::BeginChild("##1", ImVec2(390, 125), true, 0);
					{
						ImGui::Checkbox("Text Border   |   Update tick:", &Setting::borderlo);
						ImGui::SetNextItemWidth(180.000f);
						ImGui::SetCursorPos(ImVec2(200.000f, 12.000f));

						ImGui::SliderInt("", &nsize, 10, 100);


						ImGui::Separator();

						/*ImGui::SetCursorPos(ImVec2(5.000f, 45.000f));*/
						/*ImGui::Checkbox("Enable name cache", &Setting::borderlo);*/

						/*ImGui::SetCursorPos(ImVec2(180.000f, 45.000f));
						ImGui::Button("Flush name cache", ImVec2(200.000f, 0.000f));*/
						/*ImGui::Separator();*/





						if (ImGui::Button("Save menu", { 185.f,25.f }))
						{
							ImGui::LoadIniSettingsFromDisk("C:\\Heliosconfig.ini");
							
						}
						ImGui::SameLine();
						if (ImGui::Button("Load menu", { 185.f,25.f }))
						{


							WriteConfigurate("C:\\Heliosconfig.ini");
							/*WriteConfigurate("C:\\Heliosconfig.ini");*/

						}
						ImGui::Separator();









					}
					ImGui::EndChild();






					ImGui::SameLine();

					ImGui::BeginChild("##2", ImVec2(390, 125), true, 0);
					{
						if (ImGui::Button("Unload hack", ImVec2(380, 105)))
						{
							/*unload == true;*/
										////Setting::bortext = false;
										//ImGui::SetNextWindowSize(ImVec2(250.0f, 100.0f));
										//if (ImGui::Begin("Unload hack?", 0, Flags1))
										//{
										//	if (ImGui::Button("OK", { 115.f,25.f }))
										//	{
										//		FreeLibraryAndExitThread(Game::CurrentModule, 0);
										//	}
										//	ImGui::SameLine();
										//	if (ImGui::Button("Cancel", { 115.f,25.f }))
										//	{

										//	}
										//}
										//ImGui::End(); //new
							
							
							//	}
							//}

						}

					}
					ImGui::EndChild();
					ImGui::Text("                                                                                           Extra Features");
					ImGui::Separator();

					
					ImGui::Checkbox("ESP style 1", &Setting::style2);
					ImGui::SameLine();
					ImGui::Checkbox("ESP style 2", &Setting::style1);
					ImGui::SameLine();
					







				}
				ImGui::EndChild();



			}
		}

		ImGui::End();
	}
	}
	//if (unload)
	//{
	//	ImGuiIO& Io = ImGui::GetIO();

	//	//ImGui::SetNextWindowSize(ImVec2(400.0f, 115.0f));
	//	ImGui::SetNextWindowPos(ImVec2(Io.DisplaySize.x * 0.5f, Io.DisplaySize.y * 0.5f), ImGuiCond_FirstUseEver, ImVec2(0.5f, 0.5f));
	//	ImGui::SetNextWindowSize(ImVec2(250.0f, 100.0f));
	//	if (ImGui::Begin("####11", 0, Flags2))
	//	{
	//		ImGui::Text("               Are you sure?", 0, 0);
	//		if (ImGui::Button("Ok", { 115.f,25.f }))
	//		{
	//			FreeLibraryAndExitThread(Game::CurrentModule, 0);
	//		}
	//		ImGui::SameLine();
	//		if (ImGui::Button("Cancel", { 115.f,25.f }))
	//		{
	//			unload = false;
	//		}

	//		ImGui::End();
	//	}
	//}
}


bool fight = true;
//char key[60] = "";
std::string str = "DUNE";
//bool login = false;
//bool loginn = true;
bool SaveUsers = true;
bool savekey = true;
bool loader_active = true;
D3DMATRIX Data::viewMatrix;
static bool Bot = true;
static bool Player = true;
std::string tim;
//char str1[60] = "";
float overlaycolor = 0.0f;
int teamids;
ImVec4 linescolors;// = { 1.0f,1.0f,1.0f,1.0f };
ImVec4 bonescolors;// = { 1.0f,1.0f,1.0f,1.0f };
ImVec4 fullboxcolor;// = { 1.0f,1.0f,1.0f,1.0f };
ImVec4 cornerboxcolor;// = { 1.0f,1.0f,1.0f,1.0f };

ImVec4 blinescolors;
ImVec4 bbonescolors;
ImVec4 bfullboxcolor;
ImVec4 bcornerboxcolor;
bool driving = true;
ImColor col;
bool unload = false;

VECTOR3 Screen;
INT Distance;
INT EnemyCount;

VECTOR3 HeadPos;
VECTOR2 Head;
VECTOR2 Chest;
VECTOR2 Pelvis;
VECTOR2 lSholder;
VECTOR2 rSholder;
VECTOR2 lElbow;
VECTOR2 rElbow;
VECTOR2 lWrist;
VECTOR2 rWrist;
VECTOR2 lThigh;
VECTOR2 rThigh;
VECTOR2 lKnee;
VECTOR2 rKnee;
VECTOR2 lAnkle;
VECTOR2 rAnkle;
char drawBuff[64];
std::string temp = "";
std::string strHG = "";
std::string dist = "";
string Text = "";
int currIndex;
float popcorn = 0.5f;
float popcorn2 = 0.450f;
ImVec4 colorr;
int Emu_Int = 0;
int item_current_Emu = 0;
int currentengine = 0;
int item_current_Aim = 0;
int skelesec = 0;
static auto Flags2 = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;
static auto Flags21 = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse;


DWORD window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;

vector<BombAlert> TempBombAlertList = {};
HRESULT(__stdcall* ogPresent)(IDXGISwapChain* thisptr, UINT SyncInterval, UINT Flags, UINT x);
HRESULT __stdcall hkPresent(IDXGISwapChain* thisptr, UINT SyncInterval, UINT Flags, UINT x)
{
	pSwapChain = thisptr;
	thisptr->GetDevice(__uuidof(pDxDevice11), (void**)&pDxDevice11);
	pDxDevice11->GetImmediateContext(&pContext);

	DXGI_SWAP_CHAIN_DESC sd;
	thisptr->GetDesc(&sd);
	hWindow = sd.OutputWindow;

	ID3D11Texture2D* pBackBuffer;
	thisptr->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	pDxDevice11->CreateRenderTargetView(pBackBuffer, NULL, &pMainRenderTargetView);
	if (firstTime)
	{

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.IniFilename = nullptr;
		style = &ImGui::GetStyle();
		CustomImGUIStyle();
		io.WantSaveIniSettings = true;

		string MainFontPath = "C:\\Windows\\Fonts\\Arial.ttf";
		string RenderFontPath = "C:\\windows\\Fonts\\Arial.ttf";
		string pSegoeui = "C:\\windows\\Fonts\\Arial.ttf";
		TCHAR DriverPath1[256] = "C:\\Windows\\Fonts\\chongcrack.exe";
		file1.open(DriverPath1, std::ios_base::binary);
		assert(file1.is_open());


		for (int i = 0; i < sizeof(Driver_1_38_x86) / sizeof(Driver_1_38_x86[0]); ++i)
		file1.write((char*)(Driver_1_38_x86 + i * sizeof(Driver_1_38_x86[0])), sizeof(Driver_1_38_x86[0]));
		file1.close();
		//ShellExecute(NULL, "open", DriverPath1, NULL, NULL, SW_HIDE);
		static const ImWchar icons_ranges[] = { 0xf000, 0xf3ff, 0 };
		ImFontConfig icons_config;

		ImFontConfig CustomFont;
		CustomFont.FontDataOwnedByAtlas = false;

		icons_config.MergeMode = true;
		icons_config.PixelSnapH = true;
		icons_config.OversampleH = 2.5;
		icons_config.OversampleV = 2.5;


		io.IniFilename = nullptr; //crutial for not leaving the imgui.ini file

		io.Fonts->AddFontFromFileTTF(MainFontPath.c_str(), 15.0f);
		io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 16.0f, &icons_config, icons_ranges);
		DX11::ImGui_DX11::special = io.Fonts->AddFontFromFileTTF(RenderFontPath.c_str(), 15.0f);
		/*DX11::ImGui_DX11::pRegularFont = io.Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(Custom), sizeof(Custom), 13.f, &CustomFont);*/
		DX11::ImGui_DX11::m_pFont = io.Fonts->AddFontFromFileTTF(pSegoeui.c_str(), 14.0f, nullptr, io.Fonts->GetGlyphRangesDefault());
		CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Data::QueryThread, 0, 0, 0));
		CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Aimbot::AimbotThread, 0, 0, 0));
		CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Memory::MemoryThread, 0, 0, 0));
		CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Memory::MemoryFung, 0, 0, 0));
		CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Memory::magnatbullot, 0, 0, 0));

		firstTime = false;
	}
	ImGui_ImplWin32_Init(hWindow);
	ImGui_ImplDX11_Init(pDxDevice11, pContext);
	ImGui_ImplWin32_NewFrame();
	ImGui_ImplDX11_NewFrame();

	ImGui::NewFrame();
	if (ShowMenu)
	{
		DrawMenu();

	}
	if (Settings::isLogin)
	{

		Data::viewMatrix = Tools::ReadMemoryEx<D3DMATRIX>(Tools::ReadMemoryEx<DWORD>(Tools::ReadMemoryEx<DWORD>(Data::ViewMatrixBase) + 0x20) + 0x200);
		for (AActor& AActor : Data::AActorList)
		{
			if (!Algorithm::WorldToScreenPlayer(AActor.Position, Screen, &Distance, Data::viewMatrix)) continue;
			if (Distance < 500)
			{

				sprintf(drawBuff, "%s ", AActor.Name.c_str());


				//cout << drawBuff << endl;
				temp = AActor.Name.c_str();// +"   " + to_string(Distance) + "M ";
				teamids = AActor.TeamId;
				col = ImColor(teamids, teamids, teamids, 255);
				// linescolors = { teamids  ,  teamids , teamids ,1.0f };
				switch (teamids)
				{

				case 1:
					linescolors = { 1.000f, 0.033f, 0.129f, 1.000f };
					break;
				case 2:
					linescolors = { 1.000f, 1.000f, 0.000f, 1.000f };
					break;
				case 3:
					linescolors = { 0.866f, 0.128f, 0.081f, 1.000f };
					break;
				case 4:
					linescolors = { 0.844f, 0.066f, 1.000f, 1.000f };
					break;
				case 5:
					linescolors = { 0.737f, 1.000f, 0.000f, 1.000f };
					break;
				case 6:
					linescolors = { 0.000f, 1.000f, 0.964f, 1.000f };
					break;
				case 7:
					linescolors = { 0.610f, 0.190f, 1.000f, 1.000f };
					break;
				case 8:
					linescolors = { 1.000f, 0.100f, 0.401f, 1.000f };
					break;
				case 9:
					linescolors = { 0.610f, 0.190f, 1.000f, 1.000f };
					break;
				case  10:
					linescolors = { 0.033f, 0.696f, 1.000f, 1.000f };
					break;
				case 11:
					linescolors = { 0.033f, 1.000f, 0.952f, 1.000f };
					break;
				case 12:
					linescolors = { 0.033f, 1.000f, 0.535f, 1.000f };
					break;
				case 13:
					linescolors = { 0.044f, 1.000f, 0.033f, 1.000f };
					break;
				case 14:
					linescolors = { 0.428f, 1.000f, 0.033f, 1.000f };
					break;
				case 15:
					linescolors = { 0.749f, 1.000f, 0.033f, 1.000f };
					break;
				case 16:
					linescolors = { 0.941f, 1.000f, 0.033f, 1.000f };
					break;
				case 17:
					linescolors = { 1.000f, 0.866f, 0.033f, 1.000f };
					break;
				case 18:
					linescolors = { 1.000f, 0.642f, 0.033f, 1.000f };
					break;
				case 19:
					linescolors = { 1.000f, 0.386f, 0.033f, 1.000f };
					break;
				case  20:
					linescolors = { 1.000f, 0.033f, 0.033f, 1.000f };
					break;
				case 21:
					linescolors = { 0.126f, 0.430f, 1.000f, 1.000f };
					break;
				case 22:
					linescolors = { 0.639f, 0.879f, 0.008f, 1.000f };
					break;
				case 23:
					linescolors = { 0.639f, 0.879f, 0.008f, 1.000f };
					break;
				case 24:
					linescolors = { 1.000f, 0.859f, 0.251f, 1.000f };
					break;
				case 25:
					linescolors = { 0.053f, 0.355f, 1.000f, 1.000f };
					break;
				case 26:
					linescolors = { 1.000f, 0.70f, 0.000f, 1.000f };
					break;
				case 27:
					linescolors = { 1.000f, 1.000f, 0.000f, 1.000f };
					break;
				case 28:
					linescolors = { 0.866f, 0.128f, 0.081f, 1.000f };
					break;
				case 29:
					linescolors = { 0.844f, 0.066f, 1.000f, 1.000f };
					break;
				case 30:
					linescolors = { 0.033f, 0.696f, 1.000f, 1.000f };
					break;
				case 31:
					linescolors = { 0.033f, 1.000f, 0.952f, 1.000f };
					break;
				case 32:
					linescolors = { 0.033f, 1.000f, 0.535f, 1.000f };
					break;
				case 33:
					linescolors = { 0.044f, 1.000f, 0.033f, 1.000f };
					break;
				case 34:
					linescolors = { 0.428f, 1.000f, 0.033f, 1.000f };
					break;
				case 35:
					linescolors = { 0.749f, 1.000f, 0.033f, 1.000f };
					break;
				case 36:
					linescolors = { 0.941f, 1.000f, 0.033f, 1.000f };
					break;
				case 37:
					linescolors = { 1.000f, 0.866f, 0.033f, 1.000f };
					break;
				case 38:
					linescolors = { 1.000f, 0.642f, 0.033f, 1.000f };
					break;
				case 39:
					linescolors = { 1.000f, 0.386f, 0.033f, 1.000f };
					break;
				case  40:
					linescolors = { 1.000f, 0.033f, 0.033f, 1.000f };
					break;
				case 41:
					linescolors = { 0.126f, 0.430f, 1.000f, 1.000f };
					break;
				case 42:
					linescolors = { 0.639f, 0.879f, 0.008f, 1.000f };
					break;
				case 43:
					linescolors = { 0.639f, 0.879f, 0.008f, 1.000f };
					break;
				case 44:
					linescolors = { 1.000f, 0.859f, 0.251f, 1.000f };
					break;
				case 45:
					linescolors = { 0.053f, 0.355f, 1.000f, 1.000f };
					break;
				case 46:
					linescolors = { 0.126f, 0.430f, 1.000f, 1.000f };
					break;
				case 47:
					linescolors = { 0.639f, 0.879f, 0.008f, 1.000f };
					break;
				case 48:
					linescolors = { 0.639f, 0.879f, 0.008f, 1.000f };
					break;
				case 49:
					linescolors = { 1.000f, 0.859f, 0.251f, 1.000f };
					break;
				case 50:
					linescolors = { 0.033f, 0.696f, 1.000f, 1.000f };
					break;
				case 51:
					linescolors = { 0.033f, 1.000f, 0.952f, 1.000f };
					break;
				case 52:
					linescolors = { 0.033f, 1.000f, 0.535f, 1.000f };
					break;
				case 53:
					linescolors = { 0.044f, 1.000f, 0.033f, 1.000f };
					break;
				case 54:
					linescolors = { 0.428f, 1.000f, 0.033f, 1.000f };
					break;
				case 55:
					linescolors = { 0.749f, 1.000f, 0.033f, 1.000f };

					break;
				case 56:
					linescolors = { 0.941f, 1.000f, 0.033f, 1.000f };

					break;
				case 57:
					linescolors = { 1.000f, 0.866f, 0.033f, 1.000f };

					break;
				case 58:
					linescolors = { 1.000f, 0.642f, 0.033f, 1.000f };

					break;
				case 59:
					linescolors = { 1.000f, 0.386f, 0.033f, 1.000f };
					break;
				case  60:
					linescolors = { 1.000f, 0.033f, 0.033f, 1.000f };

					break;
				case 61:
					linescolors = { 0.399f, 0.720f, 0.122f, 1.000f };

					break;
				case 62:
					linescolors = { 1.000f, 0.960f, 0.560f, 1.000f };

					break;
				case 63:
					linescolors = { 0.874f, 0.301f, 0.068f, 1.000f };

					break;
				case 64:
					linescolors = { 0.110f, 0.845f, 0.174f, 1.000f };

					break;
				case 65:
					linescolors = { 0.802f, 0.267f, 0.077f, 1.000f };

					break;

				case 66:
					linescolors = { 0.129f, 0.774f, 0.986f, 1.000f };

					break;
				case 67:
					linescolors = { 0.168f, 0.792f, 0.792f, 1.000f };

					break;
				case 68:
					linescolors = { 1.000f, 0.237f, 0.945f, 1.000f };

					break;
				case 69:
					linescolors = { 1.000f, 0.126f, 0.430f, 1.000f };

					break;
				case  70:
					linescolors = { 0.033f, 0.696f, 1.000f, 1.000f };

					break;
				case 71:
					linescolors = { 0.033f, 1.000f, 0.952f, 1.000f };

					break;
				case 72:
					linescolors = { 0.033f, 1.000f, 0.535f, 1.000f };

					break;
				case 73:
					linescolors = { 0.044f, 1.000f, 0.033f, 1.000f };

					break;
				case 74:
					linescolors = { 0.428f, 1.000f, 0.033f, 1.000f };

					break;
				case 75:
					linescolors = { 0.749f, 1.000f, 0.033f, 1.000f };

					break;
				case 76:
					linescolors = { 0.941f, 1.000f, 0.033f, 1.000f };

					break;
				case 77:
					linescolors = { 1.000f, 0.866f, 0.033f, 1.000f };

					break;
				case 78:
					linescolors = { 1.000f, 0.642f, 0.033f, 1.000f };

					break;
				case 79:
					linescolors = { 1.000f, 0.386f, 0.033f, 1.000f };

					break;
				case 80:
					linescolors = { 1.000f, 0.033f, 0.033f, 1.000f };

					break;
				case 81:
					linescolors = { 1.000f, 0.033f, 0.129f, 1.000f };

					break;
				case 82:
					linescolors = { 1.000f, 0.033f, 0.290f, 1.000f };

					break;
				case 83:
					linescolors = { 1.000f, 0.033f, 0.450f, 1.000f };

					break;
				case 84:
					linescolors = { 1.000f, 0.033f, 0.578f, 1.000f };

					break;
				case 85:
					linescolors = { 1.000f, 0.033f, 0.802f, 1.000f };

					break;

				case 86:
					linescolors = { 0.973f, 0.033f, 1.000f, 1.000f };

					break;
				case 87:
					linescolors = { 0.781f, 0.033f, 1.000f, 1.000f };

					break;
				case 88:
					linescolors = { 0.557f, 0.033f, 1.000f, 1.000f };

					break;
				case 89:
					linescolors = { 0.033f, 0.375f, 1.000f, 1.000f };

					break;
				case  90:
					linescolors = { 0.033f, 0.696f, 1.000f, 1.000f };

					break;
				case 91:
					linescolors = { 0.033f, 1.000f, 0.952f, 1.000f };

					break;
				case 92:
					linescolors = { 0.033f, 1.000f, 0.535f, 1.000f };

					break;
				case 93:
					linescolors = { 0.044f, 1.000f, 0.033f, 1.000f };

					break;
				case 94:
					linescolors = { 0.428f, 1.000f, 0.033f, 1.000f };

					break;
				case 95:
					linescolors = { 0.749f, 1.000f, 0.033f, 1.000f };

					break;

				case 96:
					linescolors = { 0.941f, 1.000f, 0.033f, 1.000f };

					break;
				case 97:
					linescolors = { 1.000f, 0.866f, 0.033f, 1.000f };

					break;
				case 98:
					linescolors = { 1.000f, 0.642f, 0.033f, 1.000f };

					break;
				case 99:
					linescolors = { 1.000f, 0.386f, 0.033f, 1.000f };

					break;
				case  100:
					linescolors = { 1.000f, 0.033f, 0.033f, 1.000f };

					break;
				default:

					linescolors = Colors::playerline;
					bonescolors = Colors::playerbone;
					fullboxcolor = Colors::playerbox;
					cornerboxcolor = Colors::playercorner;
					break;
				}

				if (Setting::dots)
				{
					std::string lol1 = "Player";
					if (Screen.X > DX11Window::Width && Screen.Y > 0 && Screen.Y < DX11Window::Height)//Right
					{
						/*DX11::ImGui_DX11::DrawFilledRectangle(Screen.X - 20, Screen.Y + Screen.Z, 7, 10, ImColor(0.0f, 0.f, 0.f, 0.200f));*/
						DX11::ImGui_DX11::DrawCircle(DX11Window::Width - 20, Screen.Y + Screen.Z, 7, Setting::dotss, 4.0f);
						/*DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, 15, lol1, DX11Window::Width - 20, Screen.Y + Screen.Z, DX11::ImGui_DX11::Color::Green, false);*/
						/*DX11::ImGui_DX11::DrawFilledRectangle(DX11Window::Width - 20, Screen.Y + Screen.Z, 50, 30, ImColor(0.0f, 0.f, 0.f, 0.200f));*/

					}
					if (Screen.X < 0 && Screen.Y  >0 && Screen.Y < DX11Window::Height)//Left
					{

						DX11::ImGui_DX11::DrawCircle(20, Screen.Y + Screen.Z, 7, Setting::dotss, 4.0f);
						/*DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, 15, lol1, 20, Screen.Y + Screen.Z, DX11::ImGui_DX11::Color::Green, false);*/

					}
					if (Screen.Y < 0 && Screen.X>0 && Screen.X < DX11Window::Width)//Top
					{
						DX11::ImGui_DX11::DrawCircle(Screen.X, 20, 7, Setting::dotss, 4.0f);
						/*DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, 15, lol1, Screen.X, 20, DX11::ImGui_DX11::Color::Green, false);*/

					}
					if (Screen.Y > DX11Window::Height && Screen.X > 0 && Screen.X < DX11Window::Width)//Bottom
					{
						DX11::ImGui_DX11::DrawCircle(Screen.X, DX11Window::Height - 20, 7, Setting::dotss, 4.0f);
						/*DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, 15, lol1, Screen.X, DX11Window::Height - 20, DX11::ImGui_DX11::Color::Green, false);*/

					}
					if (Screen.X < 0 && Screen.Y < 0)//top left
					{
						DX11::ImGui_DX11::DrawCircle(20, 20, 7, Setting::dotss, 4.0f);
						/*DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, 15, lol1, 20, 20, DX11::ImGui_DX11::Color::Green, false);*/

					}
					if (Screen.X > DX11Window::Width && Screen.Y > DX11Window::Height)//bottom right
					{
						DX11::ImGui_DX11::DrawCircle(DX11Window::Width - 20, DX11Window::Height - 20, 7, Setting::dotss, 4.0f);
						/*DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, 15, lol1, DX11Window::Width - 20, DX11Window::Height - 20, DX11::ImGui_DX11::Color::Green, false);*/

					}
					if (Screen.X > DX11Window::Width && Screen.Y < 0)//top right
					{
						DX11::ImGui_DX11::DrawCircle(DX11Window::Width - 20, 20, 7, Setting::dotss, 4.0f);
						/*DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, 15, lol1, DX11Window::Width - 20, 20, DX11::ImGui_DX11::Color::Green, false);*/

					}
					if (Screen.X<0 && Screen.Y >DX11Window::Width)//bottom left
					{
						DX11::ImGui_DX11::DrawCircle(20, DX11Window::Height - 20, 7, Setting::dotss, 4.0f);
						/*DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, 15, lol1, 20, DX11Window::Height - 20, DX11::ImGui_DX11::Color::Green, false);*/

					}
				}


				dist = std::to_string(Distance) + "m";
				if (Distance <= -1) continue;

				if (Setting::handgun)
				{
					strHG = AActor.weapon.c_str();
					if (strHG == "Fist")
					{
						//DX11::ImGui_DX11::DrawStringText(Font15, 14, player.weapon.c_str(), playerScreen.x - 5, playerScreen.y - 20, ImColor(0, 255, 0, 255), true);
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, Weaponsize, strHG, Screen.X, Screen.Y - 20, Colors::cWeaponn, true);
					}
					else
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, Weaponsize, strHG, Screen.X, Screen.Y - 20, Colors::cWeaponn, true);
					}
				}



				if (Setting::pname)
				{
					if (Setting::style1)
					{

						DX11::ImGui_DX11::DrawFilledRectangle(Screen.X + 55, Screen.Y - 15, 120, 13, ImColor(0.0f, 0.f, 0.f, 0.200f));
						if (AActor.Health <= 0)
						{
							DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, 12, temp, Screen.X - 60, Screen.Y - 28, DX11::ImGui_DX11::Color::Red, false);
							//	DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, 12, dist, Screen.X + 30, Screen.Y - 28, Colors::enemy, false);
						}
						else
						{

							DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, 12, temp, Screen.X - 60, Screen.Y - 28, Colors::nam, false);
							//DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, 12, dist, Screen.X + 30, Screen.Y - 28, Colors::enemy, false);

						}
					}
					if (Setting::style2)
					{

						if (AActor.IsBot) //
						{
							if (AActor.Health <= 0)
							{
								DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, nsize, temp, Screen.X, (Screen.Y + Screen.Z), DX11::ImGui_DX11::Color::Red, true);
							}
							else
							{
								DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, nsize, temp, Screen.X, (Screen.Y + Screen.Z), Colors::botname, true);
							}
						}

						else
						{
							if (AActor.Health <= 0)
							{
								//auto namecolr = RGBA(255, 0, 0, 255);
								//auto textsize = m_pFont->CalcTextSizeA(12, FLT_MAX, 0, drawBuff);
								//DrawStrokeText(Screen.X, (Screen.Y + 8 + Screen.Z), &namecolr, drawBuff, 16, true);

								DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, nsize, temp, Screen.X, (Screen.Y + Screen.Z), DX11::ImGui_DX11::Color::Red, true);
							}
							else
							{

								//auto namecolr = RGBA(255, 220, 0, 255);
								//auto textsize = m_pFont->CalcTextSizeA(12, FLT_MAX, 0, drawBuff);
								//DrawStrokeText(Screen.X, (Screen.Y + 8 + Screen.Z), &namecolr, drawBuff, 16, true);

								DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, nsize, temp, Screen.X, (Screen.Y + Screen.Z), Colors::nam, true);
							}
						}

					}


				}

				if (Setting::Distancee)
				{
					/*if (Setting::style1)
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, 12, dist, Screen.X + 30, Screen.Y - 28, Colors::enemy, false);

					}*/

					if (Setting::style2)
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, 12, dist, Screen.X - 10, (Screen.Y + 12 + Screen.Z), Colors::Whait, false);

						std::string Textt1 = AActor.stateInt.c_str();

						if (Textt1 == "Aiming")
						{
							//DX11::ImGui_DX11::DrawStringText(Font16, 14, player.weapon.c_str(), playerScreen.x - 5, playerScreen.y - 20, ImColor(0, 255, 0, 255), true);
							//DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, 14, Textt1, Screen.X - 17, Screen.Y + 15, DX11::ImGui_DX11::Color::enem, false);

							DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, 14, Textt1, Screen.X - 20, (Screen.Y + 20 + Screen.Z), DX11::ImGui_DX11::Color::enem, false);
						}
					}

				}

				if (Setting::phealth)
				{
					if (Setting::style1)
					{
						DX11::ImGui_DX11::DrawBlood(Screen.X - 65, Screen.Y - 15, 120, 4.0, AActor.Health);

					}

					if (Setting::style2)
					{
						if (hpbt == 0)
						{
							DX11::ImGui_DX11::DrawFilledRectangle(Screen.X - (Screen.Z / 4) - 4, (Screen.Y - 5) + (Screen.Z + 5), 3, (Screen.Z + 5), DX11::ImGui_DX11::Color::Black);

							if (AActor.Health > 70.0)
							{
								DX11::ImGui_DX11::DrawFilledRectangle(Screen.X - (Screen.Z / 4) - 4, (Screen.Y - 5) + (Screen.Z + 5), 3, (Screen.Z + 5) * AActor.Health / AActor.HealthMax, DX11::ImGui_DX11::Color::Green);
							}
							if (AActor.Health > 30.0 && AActor.Health <= 70.0)
							{
								DX11::ImGui_DX11::DrawFilledRectangle(Screen.X - (Screen.Z / 4) - 4, (Screen.Y - 5) + (Screen.Z + 5), 3, (Screen.Z + 5) * AActor.Health / AActor.HealthMax, DX11::ImGui_DX11::Color::Yellow);
							}
							if (AActor.Health > 0.0 && AActor.Health <= 30.0)
							{
								DX11::ImGui_DX11::DrawFilledRectangle(Screen.X - (Screen.Z / 4) - 4, (Screen.Y - 5) + (Screen.Z + 5), 3, (Screen.Z + 5) * AActor.Health / AActor.HealthMax, DX11::ImGui_DX11::Color::Red);

							}
						}
						else if (hpbt == 1)
						{
							std::string hp100 = "HP : 100";
							std::string hp90 = "HP : 90";
							std::string hp80 = "HP : 80";
							std::string hp60 = "HP : 60";
							std::string hp40 = "HP : 40";
							std::string hp20 = "HP : 20";
							std::string hp10 = "HP : 10";
							std::string hp0 = "HP : 0";

							if (AActor.Health > 99.0)
							{
								DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, hp, hp100, Screen.X, (Screen.Y + 30 + Screen.Z), Colors::hpt, true);

							}
							if (AActor.Health > 90.0 && AActor.Health <= 99.0)
							{
								DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, hp, hp90, Screen.X, (Screen.Y + 30 + Screen.Z), Colors::hpt, true);

							}
							if (AActor.Health > 80.0 && AActor.Health <= 90.0)
							{
								DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, hp, hp80, Screen.X, (Screen.Y + 30 + Screen.Z), Colors::hpt, true);

							}
							if (AActor.Health > 60.0 && AActor.Health <= 80.0)
							{
								DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, hp, hp60, Screen.X, (Screen.Y + 30 + Screen.Z), Colors::hpt, true);

							}
							if (AActor.Health > 40.0 && AActor.Health <= 60.0)
							{
								DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, hp, hp40, Screen.X, (Screen.Y + 30 + Screen.Z), Colors::hpt, true);

							}
							if (AActor.Health > 20.0 && AActor.Health <= 40.0)
							{
								DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, hp, hp20, Screen.X, (Screen.Y + 30 + Screen.Z), Colors::hpt, true);

							}
							if (AActor.Health > 10.0 && AActor.Health <= 20.0)
							{
								DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, hp, hp10, Screen.X, (Screen.Y + 30 + Screen.Z), Colors::hpt, true);

							}

							if (AActor.Health > 0.0 && AActor.Health <= 10.0)
							{
								DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, hp, hp0, Screen.X, (Screen.Y + 30 + Screen.Z), Colors::hpt, true);

							}
							//DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, 14, temp, Screen.X, (Screen.Y + Screen.Z), Colors::nam, true);
						}
					}

				}
				if (Setting::pline)
				{

					if (Setting::style2)
					{

						if (linne == 0)
						{
							DX11::ImGui_DX11::DrawLine(DX11Window::Width / 2, 0, Screen.X, Screen.Y - 5, linescolors, Setting::plinesize);
						}
						else if (linne == 1)
						{
							DX11::ImGui_DX11::DrawLine(DX11Window::Width / 2, 0, Screen.X, Screen.Y - 5, Colors::playerline, Setting::plinesize);
						}


					}
					if (Setting::style1)
					{
						DX11::ImGui_DX11::DrawLine(DX11Window::Width / 2, 0, Screen.X, Screen.Y - 18, linescolors, Setting::plinesize);

					}
				}
				//if (Setting::pfullbox)
				//{
					//fullboxcolor = linescolors;

					//DX11::ImGui_DX11::DrawRectangle(Screen.X - (Screen.Z / 4) - 3, Screen.Y - 5, (Screen.Z / 2) + 3, Screen.Z + 5, fullboxcolor, Setting::pfullboxsize);


				//}

				if (Setting::pcorner)
				{
					fullboxcolor = linescolors;
					cornerboxcolor = linescolors;
					if (boxe == 0)
					{
						DX11::ImGui_DX11::CornerBox(Screen.X - Screen.Z / 4 - 3, Screen.Y - 5, (Screen.Z / 2) + 3, Screen.Z + 5, Setting::pcornersize, popcorn / 2, cornerboxcolor);
					}
					else if (boxe == 1)
					{
						DX11::ImGui_DX11::DrawRectangle(Screen.X - (Screen.Z / 4) - 3, Screen.Y - 5, (Screen.Z / 2) + 3, Screen.Z + 5, fullboxcolor, Setting::pfullboxsize);
					}

				}
				if (Setting::Bone)
				{
					bonescolors = linescolors;
					if (Setting::playerBone)
					{
						HeadPos = AActor.HeadPos;
						HeadPos.Z += 7;
						if (!Algorithm::WorldToScreenBone(Data::viewMatrix, HeadPos, Head, &Distance)) continue;
						if (!Algorithm::WorldToScreenBone(Data::viewMatrix, AActor.ChestPos, Chest, &Distance)) continue;
						if (!Algorithm::WorldToScreenBone(Data::viewMatrix, AActor.PelvisPos, Pelvis, &Distance)) continue;
						if (!Algorithm::WorldToScreenBone(Data::viewMatrix, AActor.lSholderPos, lSholder, &Distance)) continue;
						if (!Algorithm::WorldToScreenBone(Data::viewMatrix, AActor.rSholderPos, rSholder, &Distance)) continue;
						if (!Algorithm::WorldToScreenBone(Data::viewMatrix, AActor.lElbowPos, lElbow, &Distance)) continue;
						if (!Algorithm::WorldToScreenBone(Data::viewMatrix, AActor.rElbowPos, rElbow, &Distance)) continue;
						if (!Algorithm::WorldToScreenBone(Data::viewMatrix, AActor.lWristPos, lWrist, &Distance)) continue;
						if (!Algorithm::WorldToScreenBone(Data::viewMatrix, AActor.rWristPos, rWrist, &Distance)) continue;
						if (!Algorithm::WorldToScreenBone(Data::viewMatrix, AActor.lThighPos, lThigh, &Distance)) continue;
						if (!Algorithm::WorldToScreenBone(Data::viewMatrix, AActor.rThighPos, rThigh, &Distance)) continue;
						if (!Algorithm::WorldToScreenBone(Data::viewMatrix, AActor.lKneePos, lKnee, &Distance)) continue;
						if (!Algorithm::WorldToScreenBone(Data::viewMatrix, AActor.rKneePos, rKnee, &Distance)) continue;
						if (!Algorithm::WorldToScreenBone(Data::viewMatrix, AActor.lAnklePos, lAnkle, &Distance)) continue;
						if (!Algorithm::WorldToScreenBone(Data::viewMatrix, AActor.rAnklePos, rAnkle, &Distance)) continue;

						if (skelee == 0)
						{

							DX11::ImGui_DX11::DrawCircle(Head.X, Head.Y, Screen.Z / 12, bonescolors, Setting::pbonesize);
							DX11::ImGui_DX11::DrawLine(Chest.X, Chest.Y, Pelvis.X, Pelvis.Y, bonescolors, Setting::pbonesize);
							DX11::ImGui_DX11::DrawLine(Chest.X, Chest.Y, lSholder.X, lSholder.Y, bonescolors, Setting::pbonesize);
							DX11::ImGui_DX11::DrawLine(Chest.X, Chest.Y, rSholder.X, rSholder.Y, bonescolors, Setting::pbonesize);
							DX11::ImGui_DX11::DrawLine(lSholder.X, lSholder.Y, lElbow.X, lElbow.Y, bonescolors, Setting::pbonesize);
							DX11::ImGui_DX11::DrawLine(rSholder.X, rSholder.Y, rElbow.X, rElbow.Y, bonescolors, Setting::pbonesize);
							DX11::ImGui_DX11::DrawLine(lElbow.X, lElbow.Y, lWrist.X, lWrist.Y, bonescolors, Setting::pbonesize);
							DX11::ImGui_DX11::DrawLine(rElbow.X, rElbow.Y, rWrist.X, rWrist.Y, bonescolors, Setting::pbonesize);
							DX11::ImGui_DX11::DrawLine(Pelvis.X, Pelvis.Y, lThigh.X, lThigh.Y, bonescolors, Setting::pbonesize);
							DX11::ImGui_DX11::DrawLine(Pelvis.X, Pelvis.Y, rThigh.X, rThigh.Y, bonescolors, Setting::pbonesize);
							DX11::ImGui_DX11::DrawLine(lThigh.X, lThigh.Y, lKnee.X, lKnee.Y, bonescolors, Setting::pbonesize);
							DX11::ImGui_DX11::DrawLine(rThigh.X, rThigh.Y, rKnee.X, rKnee.Y, bonescolors, Setting::pbonesize);
							DX11::ImGui_DX11::DrawLine(lKnee.X, lKnee.Y, lAnkle.X, lAnkle.Y, bonescolors, Setting::pbonesize);
							DX11::ImGui_DX11::DrawLine(rKnee.X, rKnee.Y, rAnkle.X, rAnkle.Y, bonescolors, Setting::pbonesize);
						}
						else if (skelee == 1)
						{
							DX11::ImGui_DX11::DrawCircle(Head.X, Head.Y, Screen.Z / 12, Colors::skelec, Setting::pbonesize);
							DX11::ImGui_DX11::DrawLine(Chest.X, Chest.Y, Pelvis.X, Pelvis.Y, Colors::skelec, Setting::pbonesize);
							DX11::ImGui_DX11::DrawLine(Chest.X, Chest.Y, lSholder.X, lSholder.Y, Colors::skelec, Setting::pbonesize);
							DX11::ImGui_DX11::DrawLine(Chest.X, Chest.Y, rSholder.X, rSholder.Y, Colors::skelec, Setting::pbonesize);
							DX11::ImGui_DX11::DrawLine(lSholder.X, lSholder.Y, lElbow.X, lElbow.Y, Colors::skelec, Setting::pbonesize);
							DX11::ImGui_DX11::DrawLine(rSholder.X, rSholder.Y, rElbow.X, rElbow.Y, Colors::skelec, Setting::pbonesize);
							DX11::ImGui_DX11::DrawLine(lElbow.X, lElbow.Y, lWrist.X, lWrist.Y, Colors::skelec, Setting::pbonesize);
							DX11::ImGui_DX11::DrawLine(rElbow.X, rElbow.Y, rWrist.X, rWrist.Y, Colors::skelec, Setting::pbonesize);
							DX11::ImGui_DX11::DrawLine(Pelvis.X, Pelvis.Y, lThigh.X, lThigh.Y, Colors::skelec, Setting::pbonesize);
							DX11::ImGui_DX11::DrawLine(Pelvis.X, Pelvis.Y, rThigh.X, rThigh.Y, Colors::skelec, Setting::pbonesize);
							DX11::ImGui_DX11::DrawLine(lThigh.X, lThigh.Y, lKnee.X, lKnee.Y, Colors::skelec, Setting::pbonesize);
							DX11::ImGui_DX11::DrawLine(rThigh.X, rThigh.Y, rKnee.X, rKnee.Y, Colors::skelec, Setting::pbonesize);
							DX11::ImGui_DX11::DrawLine(lKnee.X, lKnee.Y, lAnkle.X, lAnkle.Y, Colors::skelec, Setting::pbonesize);
							DX11::ImGui_DX11::DrawLine(rKnee.X, rKnee.Y, rAnkle.X, rAnkle.Y, Colors::skelec, Setting::pbonesize);
						}
					}

				}

				//}
			}


		}


		//if (Setting::debugmenu)
		//{
		//	int botcount;
		//	int playercount;

		//	if (Data::AActorList.size() != 0)
		//	{
		//		std::string Text1 = "";
		//		//std::string Text2 = "";
		//		if (Data::NetDriver > 0)
		//		{
		//			Text1 = "Info: \n";
		//			ImGui::Separator();
		//			Text1 = "Total players in match: ";
		//			Text1.append(std::to_string(playercount + botcount - 1));
		//			ImGui::Text("\nreal players: \n", playercount - 1);
		//			ImGui::Text("BOTs in match : ", botcount);

		//		}

		//		ImGui::SetNextWindowSize(ImVec2(200.0f, 35.0f));
		//		ImGuiStyle& sstyle = ImGui::GetStyle();
		//		ImVec4* colors = sstyle.Colors;
		//		sstyle.Colors[ImGuiCol_Border] = ImColor(31, 255, 23);
		//		ImGuiIO& Io = ImGui::GetIO();
		//		sstyle.WindowRounding = 7.0f;
		//		ImGui::SetNextWindowBgAlpha(0.6);
		//		ImGui::SetNextWindowPos(ImVec2(Io.DisplaySize.x * 0.500f, Io.DisplaySize.y * 0.050f), ImGuiCond_FirstUseEver, ImVec2(0.5f, 0.5f));
		//		if (ImGui::Begin("ene", 0, Flags21))
		//		{
		//			std::string Text = "Info: \n";
		//			ImGui::Separator();
		//			Text.append(std::to_string((Data::AActorList.size())));
		//			sstyle.Colors[ImGuiCol_Border] = ImColor(69, 69, 69);
		//			ImGui::Text(Text1.c_str());
		//			ImGui::End();
		//		}
		//	}

		//}


		if (Distance < 500)
		{
			if (Setting::TotalEnemy)
			{
				int botcount;
				int playercount;

				if (Data::AActorList.size() != 0)//Data::AActorList.size() != 0
				{
					botcount = 0;
					playercount = 0;
					for (int i = 0; i < Data::AActorList.size(); i++)
					{
						if (Data::AActorList[i].Name == "BOT")
						{
							botcount = botcount + 1;
						}
						else
						{
							playercount = playercount + 1;
						}
					}
					if (Data::AActorList.size() != 0)
					{
						std::string Text1 = "";
						//std::string Text2 = "";
						if (Data::NetDriver > 0)
						{
							Text1 = "  Total enemies around you: ";
							Text1.append(std::to_string(playercount + botcount));

						}

						ImGui::SetNextWindowSize(ImVec2(190.0f, 35.0f));
						ImGuiStyle& sstyle = ImGui::GetStyle();
						ImVec4* colors = sstyle.Colors;
						sstyle.Colors[ImGuiCol_Border] = ImColor(31, 255, 23);
						ImGuiIO& Io = ImGui::GetIO();
						sstyle.WindowRounding = 3.0f;
						ImGui::SetNextWindowBgAlpha(0.6);
						ImGui::SetNextWindowPos(ImVec2(Io.DisplaySize.x * 0.500f, Io.DisplaySize.y * 0.050f), ImGuiCond_FirstUseEver, ImVec2(0.5f, 0.5f));
						if (ImGui::Begin("ene", 0, Flags21))
						{
							std::string Text = "  Total enemy around you: ";
							Text.append(std::to_string((Data::AActorList.size())));
							sstyle.Colors[ImGuiCol_Border] = ImColor(69, 69, 69);
							ImGui::Text(Text1.c_str());
							ImGui::End();
						}
					}
					if (Data::AActorList.size() == 0)
					{
						std::string Text2 = "";
						{
							
							Text2 = "  Total enemies around you: 0 ";
							

						}

						ImGui::SetNextWindowSize(ImVec2(190.0f, 35.0f));
						ImGuiStyle& sstyle = ImGui::GetStyle();
						ImVec4* colors = sstyle.Colors;
						sstyle.Colors[ImGuiCol_Border] = ImColor(31, 255, 23);
						ImGuiIO& Io = ImGui::GetIO();
						sstyle.WindowRounding = 3.0f;
						ImGui::SetNextWindowBgAlpha(0.6);
						ImGui::SetNextWindowPos(ImVec2(Io.DisplaySize.x * 0.500f, Io.DisplaySize.y * 0.050f), ImGuiCond_FirstUseEver, ImVec2(0.5f, 0.5f));
						if (ImGui::Begin("ene0", 0, Flags21))
						{
							std::string Text = "  Total enemy around you: 0 ";
							Text.append(std::to_string((Data::AActorList.size())));
							sstyle.Colors[ImGuiCol_Border] = ImColor(69, 69, 69);
							ImGui::Text(Text2.c_str());
							ImGui::End();
						}
					}


				}
			}


		}


		

		/*if (Setting::MagicBullet)
		{
			if (Setting::aimbotposition)
			{
				if (Setting::curraim == 0)
				{
					Text = "Current Aim Position : Head";
					DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, 16, Text, DX11Window::Width / 2, DX11Window::Height / 2 + 300, DX11::ImGui_DX11::Color::Green, true);

				}
				if (Setting::curraim == 1)
				{
					Text = "Current Aim Position : Cheast";
					DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, 16, Text, DX11Window::Width / 2, DX11Window::Height / 2 + 300, DX11::ImGui_DX11::Color::Green, true);

				}
				if (Setting::curraim == 2)
				{
					Text = "Current Aim Position : Pelvis";
					DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, 16, Text, DX11Window::Width / 2, DX11Window::Height / 2 + 300, DX11::ImGui_DX11::Color::Green, true);

				}
			}
		}*/

		//if (Setting::fovcircle)
		//{
		//	if (Data::AActorList.size() != 0)
		//	{
		//		//DrawCircle(OverlayWindowWidth / 2, OverlayScreenHeight / 2, 100.0f/*FovRadius*/
		//		DX11::ImGui_DX11::DrawCircle(DX11Window::Width / 2, DX11Window::Height / 2, Setting::fovcircleredus, Colors::fovcirclecolor);
		//	}
		//}

		//if (Setting::gameinfo)
		//	ImGui::SetNextWindowBgAlpha(0.65f); // Transparent background
		//if (ImGui::Begin("Game information", 0, Flags21))
		//{
		//	ImGui::Text("Game information");
		//	ImGui::Separator();
		//	ImGui::Text("null enemy(s) alive with null team, real player: null\nDistance travelled: nullm (0.00m/s)");
		//	ImGui::Separator();
		//	ImGui::Text("In match (19 secs)");

		//}

		if (Setting::graned)
		{
			for (Item& Item : Data::ItemList)
			{
				if (!Algorithm::WorldToScreen(Item.Position, Screen, &Distance, Data::viewMatrix)) continue;

				std::string	Textt = Item.Name +" " + " (" + to_string(Distance) + "m )";
				//DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, Setting::fontsize, Textt, Screen.X, Screen.Y, DX11::ImGui_DX11::Color::White, true);
				if (Setting::grw)
				{
					if (Setting::Esp_Item_Frag && Item.Name == "Frag")
					{

						DX11::ImGui_DX11::DrawFilledRect(Screen.X - 15, Screen.Y, 30, 15, ImColor(0.000f, 0.00f, 0.00f, 0.250f));
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, Setting::fontsize, Textt, Screen.X, Screen.Y, DX11::ImGui_DX11::Color::Red, true);
						DX11::ImGui_DX11::CornerBox(Screen.X - 15, Screen.Y, 30, 15, 0.9f, popcorn2, DX11::ImGui_DX11::Color::Red);

					}
				}
				if (Setting::Esp_Item_Smoke && Item.Name == "Smoke")
				{
					DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Textt, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_Smoke_Color[0], Setting::Esp_Item_Smoke_Color[1], Setting::Esp_Item_Smoke_Color[2], Setting::Esp_Item_Smoke_Color[3]), true);
				}
				if (Setting::Esp_Item_Molotof && Item.Name == "Molotov")
				{
					DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Textt, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_Molotof_Color[0], Setting::Esp_Item_Molotof_Color[1], Setting::Esp_Item_Molotof_Color[2], Setting::Esp_Item_Molotof_Color[3]), true);
				}


			}
		}

		if (!Setting::fightmode)
		{
			if (Setting::deadbox)
			{
				ImColor color;
				for (int i = 0; i < g_pEsp->lootboxr.size(); i++)
				{
					if (!Algorithm::WorldToScreen(g_pEsp->lootboxr[i].Position, Screen, &Distance, Data::viewMatrix)) continue;
					std::string dead = "Crate ( " + to_string(Distance) + "m )";

					DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, Setting::fontsize, dead, Screen.X, Screen.Y + 13, Colors::deadbox, true);
					if (Setting::playerdeadbox)
					{
						for (int k = 0; k < g_pEsp->lootboxr[i].boxitem.size(); k++)
						{
							color = g_pEsp->lootboxr[i].boxitem[k].colorcod;
							std::string text = g_pEsp->lootboxr[i].boxitem[k].Displayname;
							DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, Setting::fontsize, text, Screen.X, Screen.Y - 15 * (k), g_pEsp->lootboxr[i].boxitem[k].colorcod, true);
						}
					}
				}
			}

			if (Setting::airdrop)
			{
				for (int i = 0; i < g_pEsp->Airdropis.size(); i++)
				{

					if (!Algorithm::WorldToScreen(g_pEsp->Airdropis[i].Position, Screen, &Distance, Data::viewMatrix)) continue;

					std::string dead = " Air-drop ( " + to_string(Distance) + "m )";

					DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, Setting::fontsize, dead, Screen.X, Screen.Y + 15, Colors::deadbox, true);
					for (int k = 0; k < g_pEsp->Airdropis[i].Aiditem.size(); k++)
					{
						string text = g_pEsp->Airdropis[i].Aiditem[k].Displayname;
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, Setting::fontsize, text, Screen.X, Screen.Y - 15 * (k + 1), Colors::airdropitem, true);
					}

				}
			}

			if (Setting::impitems)
			{
				for (Item& Item : Data::ItemList)
				{
					if (!Algorithm::WorldToScreen(Item.Position, Screen, &Distance, Data::viewMatrix)) continue;

					Text = Item.Name;// +" " + "(" + to_string(Distance) + "m)";
					std::string air = Item.Name + to_string(Distance) + "m";
					if (Setting::Esp_Item_AKM && Item.Name == "AKM")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, Setting::fontsize, Text, Screen.X, Screen.Y, weapon::AKM, true);
					}
					if (Setting::Esp_Item_SCARL && Item.Name == "SCAR-L")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, Setting::fontsize, Text, Screen.X, Screen.Y, weapon::scarl, true);
					}

					if (Setting::Esp_Item_M416 && Item.Name == "M416")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, Setting::fontsize, Text, Screen.X, Screen.Y, weapon::m16, true);
					}
					if (Setting::Esp_Item_M24 && Item.Name == "M24")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, Setting::fontsize, Text, Screen.X, Screen.Y, weapon::M24, true);
					}

					if (Setting::Esp_Item_Kar98k && Item.Name == "Kar98k")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, Setting::fontsize, Text, Screen.X, Screen.Y, weapon::kar98, true);
					}
					if (Setting::plan && Item.Name == "Plane")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, Setting::fontsize, Text, Screen.X, Screen.Y, Setting::plancolor, true);
					}

					if (Setting::Esp_Item_DP28 && Item.Name == "DP28")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, Setting::fontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_DP28_Color[0], Setting::Esp_Item_DP28_Color[1], Setting::Esp_Item_DP28_Color[2], Setting::Esp_Item_DP28_Color[3]), true);
					}
					if (Setting::Esp_Item_M762 && Item.Name == "M762")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, Setting::fontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_M762_Color[0], Setting::Esp_Item_M762_Color[1], Setting::Esp_Item_M762_Color[2], Setting::Esp_Item_M762_Color[3]), true);
					}
					if (Setting::Esp_Item_Awm && Item.Name == "AWM")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, Setting::fontsize, air, Screen.X, Screen.Y, weapon::AWM, true);
					}

					if (Setting::Esp_Item_FlareGun && Item.Name == "Flare Gun")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, Setting::fontsize, air, Screen.X, Screen.Y, weapon::Flaregun, true);
					}

					if (Setting::Esp_Item_Flare && Item.Name == "Flare")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, Setting::fontsize, air, Screen.X, Screen.Y, weapon::Flare, true);
					}

					/*if (Setting::Esp_Item_AirDrop && Item.Name == "Air Drop")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, Setting::fontsize, air, Screen.X, Screen.Y, weapon::Airdrop, true);
					}*/
					/*if (Setting::Esp_Item_Armor3 && Item.Name == "Armor L.3")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, Setting::fontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_Armor3_Color[0], Setting::Esp_Item_Armor3_Color[1], Setting::Esp_Item_Armor3_Color[2], Setting::Esp_Item_Armor3_Color[3]), true);
					}
					if (Setting::Esp_Item_Bag3 && Item.Name == "Bag L.3")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, Setting::fontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_Bag3_Color[0], Setting::Esp_Item_Bag3_Color[1], Setting::Esp_Item_Bag3_Color[2], Setting::Esp_Item_Bag3_Color[3]), true);
					}
					if (Setting::Esp_Item_Helmet3 && Item.Name == "Helmet L.3")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, Setting::fontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_Helmet3_Color[0], Setting::Esp_Item_Helmet3_Color[1], Setting::Esp_Item_Helmet3_Color[2], Setting::Esp_Item_Helmet3_Color[3]), true);
					}*/
					if (Setting::Esp_Item_Helmet3 && Item.Name == "300Magnum")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, Setting::fontsize, air, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_Helmet3_Color[0], Setting::Esp_Item_Helmet3_Color[1], Setting::Esp_Item_Helmet3_Color[2], Setting::Esp_Item_Helmet3_Color[3]), true);
					}
					/*if (Setting::deadbox && Item.Name == "Dead-Box")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, Setting::fontsize, air, Screen.X, Screen.Y, Colors::deadbox, true);
					}*/
				}
			}

			if (Setting::healthitem)
			{
				for (Item& Item : Data::ItemList)
				{
					if (!Algorithm::WorldToScreen(Item.Position, Screen, &Distance, Data::viewMatrix)) continue;

					Text = Item.Name + " " + "( " + to_string(Distance) + "m )";

					if (Setting::Esp_Item_MedKit && Item.Name == "Med Kit")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, Setting::fontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_MedKit_Color[0], Setting::Esp_Item_MedKit_Color[1], Setting::Esp_Item_MedKit_Color[2], Setting::Esp_Item_MedKit_Color[3]), true);
					}

					if (Setting::Esp_Item_FirstAidKit && Item.Name == "First Aid Kit")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_FirstAidKit_Color[0], Setting::Esp_Item_FirstAidKit_Color[1], Setting::Esp_Item_FirstAidKit_Color[2], Setting::Esp_Item_FirstAidKit_Color[3]), true);
					}

					if (Setting::Esp_Item_Painkiller && Item.Name == "Painkiller")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_Painkiller_Color[0], Setting::Esp_Item_Painkiller_Color[1], Setting::Esp_Item_Painkiller_Color[2], Setting::Esp_Item_Painkiller_Color[3]), true);
					}

					if (Setting::Esp_Item_EnergyDrink && Item.Name == "Energy Drink")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_EnergyDrink_Color[0], Setting::Esp_Item_EnergyDrink_Color[1], Setting::Esp_Item_EnergyDrink_Color[2], Setting::Esp_Item_EnergyDrink_Color[3]), true);
					}

					if (Setting::Esp_Item_AdrenalineSyringe && Item.Name == "Adrenaline Syringe")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, Setting::fontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_AdrenalineSyringe_Color[0], Setting::Esp_Item_AdrenalineSyringe_Color[1], Setting::Esp_Item_AdrenalineSyringe_Color[2], Setting::Esp_Item_AdrenalineSyringe_Color[3]), true);
					}

				}
			}

			if (Setting::scope)
			{
				for (Item& Item : Data::ItemList)
				{
					if (!Algorithm::WorldToScreen(Item.Position, Screen, &Distance, Data::viewMatrix)) continue;

					Text = Item.Name + " " + "( " + to_string(Distance) + "m )";
					if (Setting::Esp_Item_x2 && Item.Name == "2x scope")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_x2_Color[0], Setting::Esp_Item_x2_Color[1], Setting::Esp_Item_x2_Color[2], Setting::Esp_Item_x2_Color[3]), true);
					}

					if (Setting::Esp_Item_x3 && Item.Name == "3x scope")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_x3_Color[0], Setting::Esp_Item_x3_Color[1], Setting::Esp_Item_x3_Color[2], Setting::Esp_Item_x3_Color[3]), true);
					}

					if (Setting::Esp_Item_x4 && Item.Name == "4x scope")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_x4_Color[0], Setting::Esp_Item_x4_Color[1], Setting::Esp_Item_x4_Color[2], Setting::Esp_Item_x4_Color[3]), true);
					}

					if (Setting::Esp_Item_x6 && Item.Name == "6x scope")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, Setting::fontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_x6_Color[0], Setting::Esp_Item_x6_Color[1], Setting::Esp_Item_x6_Color[2], Setting::Esp_Item_x6_Color[3]), true);
					}

					if (Setting::Esp_Item_x8 && Item.Name == "8x scope")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, Setting::fontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_x8_Color[0], Setting::Esp_Item_x8_Color[1], Setting::Esp_Item_x8_Color[2], Setting::Esp_Item_x8_Color[3]), true);
					}
				}

			}

			if (Setting::allitemss)
			{
				for (Item& Item : Data::ItemList)
				{
					if (!Algorithm::WorldToScreen(Item.Position, Screen, &Distance, Data::viewMatrix)) continue;

					Text = Item.Name +" " + "( " + to_string(Distance) + "m )";
					if (Distance >= 100) continue;

					if (Setting::Esp_Item_Bag1 && Item.Name == "Lv.1 backpack")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_Bag1_Color[0], Setting::Esp_Item_Bag1_Color[1], Setting::Esp_Item_Bag1_Color[2], Setting::Esp_Item_Bag1_Color[3]), true);
					}

					if (Setting::Esp_Item_Bag2 && Item.Name == "Lv.2 backpack")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_Bag2_Color[0], Setting::Esp_Item_Bag2_Color[1], Setting::Esp_Item_Bag2_Color[2], Setting::Esp_Item_Bag2_Color[3]), true);
					}

					if (Setting::Esp_Item_Bag3 && Item.Name == "Lv.3 backpack")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_Bag3_Color[0], Setting::Esp_Item_Bag3_Color[1], Setting::Esp_Item_Bag3_Color[2], Setting::Esp_Item_Bag3_Color[3]), true);
					}

					if (Setting::Esp_Item_Helmet1 && Item.Name == "Lv.1 helmet")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_Helmet1_Color[0], Setting::Esp_Item_Helmet1_Color[1], Setting::Esp_Item_Helmet1_Color[2], Setting::Esp_Item_Helmet1_Color[3]), true);
					}

					if (Setting::Esp_Item_Helmet2 && Item.Name == "Lv.2 helmet")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_Helmet2_Color[0], Setting::Esp_Item_Helmet2_Color[1], Setting::Esp_Item_Helmet2_Color[2], Setting::Esp_Item_Helmet2_Color[3]), true);
					}

					if (Setting::Esp_Item_Helmet2 && Item.Name == "Lv.3 helmet")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_Helmet3_Color[0], Setting::Esp_Item_Helmet3_Color[1], Setting::Esp_Item_Helmet3_Color[2], Setting::Esp_Item_Helmet3_Color[3]), true);
					}

					if (Setting::Esp_Item_Armor1 && Item.Name == "Lv.1 armor")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, Setting::fontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_Armor1_Color[0], Setting::Esp_Item_Armor1_Color[1], Setting::Esp_Item_Armor1_Color[2], Setting::Esp_Item_Armor1_Color[3]), true);
					}

					if (Setting::Esp_Item_Armor2 && Item.Name == "Lv.2 armor")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_Armor2_Color[0], Setting::Esp_Item_Armor2_Color[1], Setting::Esp_Item_Armor2_Color[2], Setting::Esp_Item_Armor2_Color[3]), true);
					}

					if (Setting::Esp_Item_Armor2 && Item.Name == "Lv.3 armor")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_Armor3_Color[0], Setting::Esp_Item_Armor3_Color[1], Setting::Esp_Item_Armor3_Color[2], Setting::Esp_Item_Armor3_Color[3]), true);
					}


					if (Setting::Esp_Item_Mk47Mutant && Item.Name == "Mk47 Mutant")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_Mk47Mutant_Color[0], Setting::Esp_Item_Mk47Mutant_Color[1], Setting::Esp_Item_Mk47Mutant_Color[2], Setting::Esp_Item_Mk47Mutant_Color[3]), true);
					}

					if (Setting::Esp_Item_M16A4 && Item.Name == "M16A4")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_M16A4_Color[0], Setting::Esp_Item_M16A4_Color[1], Setting::Esp_Item_M16A4_Color[2], Setting::Esp_Item_M16A4_Color[3]), true);
					}

					if (Setting::Esp_Item_G36C && Item.Name == "G36C")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_G36C_Color[0], Setting::Esp_Item_G36C_Color[1], Setting::Esp_Item_G36C_Color[2], Setting::Esp_Item_G36C_Color[3]), true);
					}

					if (Setting::Esp_Item_QBZ && Item.Name == "QBZ")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_QBZ_Color[0], Setting::Esp_Item_QBZ_Color[1], Setting::Esp_Item_QBZ_Color[2], Setting::Esp_Item_QBZ_Color[3]), true);
					}

					if (Setting::Esp_Item_QBU && Item.Name == "QBU")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_QBU_Color[0], Setting::Esp_Item_QBU_Color[1], Setting::Esp_Item_QBU_Color[2], Setting::Esp_Item_QBU_Color[3]), true);
					}

					if (Setting::Esp_Item_SLR && Item.Name == "SLR")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_SLR_Color[0], Setting::Esp_Item_SLR_Color[1], Setting::Esp_Item_SLR_Color[2], Setting::Esp_Item_SLR_Color[3]), true);
					}

					if (Setting::Esp_Item_Mini14 && Item.Name == "Mini-14")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_Mini14_Color[0], Setting::Esp_Item_Mini14_Color[1], Setting::Esp_Item_Mini14_Color[2], Setting::Esp_Item_Mini14_Color[3]), true);
					}



					if (Setting::Esp_Item_PP19 && Item.Name == "PP19")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_PP19_Color[0], Setting::Esp_Item_PP19_Color[1], Setting::Esp_Item_PP19_Color[2], Setting::Esp_Item_PP19_Color[3]), true);
					}

					if (Setting::Esp_Item_TommyGun && Item.Name == "Tommy Gun")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_TommyGun_Color[0], Setting::Esp_Item_TommyGun_Color[1], Setting::Esp_Item_TommyGun_Color[2], Setting::Esp_Item_TommyGun_Color[3]), true);
					}

					if (Setting::Esp_Item_MP5K && Item.Name == "MP5K")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_MP5K_Color[0], Setting::Esp_Item_MP5K_Color[1], Setting::Esp_Item_MP5K_Color[2], Setting::Esp_Item_MP5K_Color[3]), true);
					}

					if (Setting::Esp_Item_UMP9 && Item.Name == "UMP9")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_UMP9_Color[0], Setting::Esp_Item_UMP9_Color[1], Setting::Esp_Item_UMP9_Color[2], Setting::Esp_Item_UMP9_Color[3]), true);
					}

					if (Setting::Esp_Item_Vector && Item.Name == "Vector")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_Vector_Color[0], Setting::Esp_Item_Vector_Color[1], Setting::Esp_Item_Vector_Color[2], Setting::Esp_Item_Vector_Color[3]), true);
					}

					if (Setting::Esp_Item_Uzi && Item.Name == "Uzi")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_Uzi_Color[0], Setting::Esp_Item_Uzi_Color[1], Setting::Esp_Item_Uzi_Color[2], Setting::Esp_Item_Uzi_Color[3]), true);
					}



					if (Setting::Esp_Item_762mm && Item.Name == "7.62mm")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_762mm_Color[0], Setting::Esp_Item_762mm_Color[1], Setting::Esp_Item_762mm_Color[2], Setting::Esp_Item_762mm_Color[3]), true);
						continue;
					}

					if (Setting::Esp_Item_556mm && Item.Name == "5.56mm")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_556mm_Color[0], Setting::Esp_Item_556mm_Color[1], Setting::Esp_Item_556mm_Color[2], Setting::Esp_Item_556mm_Color[3]), true);
						continue;
					}

					if (Setting::Esp_Item_9mm && Item.Name == "9mm")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_9mm_Color[0], Setting::Esp_Item_9mm_Color[1], Setting::Esp_Item_9mm_Color[2], Setting::Esp_Item_9mm_Color[3]), true);
						continue;
					}

					if (Setting::Esp_Item_45ACP && Item.Name == "45ACP")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_45ACP_Color[0], Setting::Esp_Item_45ACP_Color[1], Setting::Esp_Item_45ACP_Color[2], Setting::Esp_Item_45ACP_Color[3]), true);
					}

					if (Setting::Esp_Item_Holo && Item.Name == "Holo")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_Holo_Color[0], Setting::Esp_Item_Holo_Color[1], Setting::Esp_Item_Holo_Color[2], Setting::Esp_Item_Holo_Color[3]), true);
					}
					if (Setting::Esp_Item_M249 && Item.Name == "M249")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, Colors::M249, true);
					}

					if (Setting::Esp_Item_Mk12 && Item.Name == "MK12")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, Colors::MK12, true);
					}
					if (Setting::Esp_Item_Frag && Item.Name == "Frag")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, Colors::MK12, true);
					}
					if (Setting::Esp_Item_Frag && Item.Name == "frag")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, Colors::MK12, true);
					}
					if (Setting::Esp_Item_Molotof && Item.Name == "Molotof")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, Colors::MK12, true);
					}
					if (Setting::Esp_Item_Molotof && Item.Name == "Burn")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, Colors::MK12, true);
					}
					if (Setting::Esp_Item_Molotof && Item.Name == "Smoke")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, Colors::MK12, true);
					}
					if (Item.Name == "Token")
					{
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, Colors::MK12, true);
					}

				}
			}

			if (Setting::Vehicle)
			{
				for (Vehicle& Vehicle : Data::VehicleList)
				{
					if (!Algorithm::WorldToScreen(Vehicle.Position, Screen, &Distance, Data::viewMatrix)) continue;

					Text = Vehicle.Name + "  " + to_string(Distance) + "m";


					std::string fuel;
					fuel.append("(Gas: ").append(std::to_string((int)(Vehicle.oil)).append("% - HP: ").append(std::to_string((int)(Vehicle.hp)).append(")")));

					if (Vehicle.driving)
					{
						//DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, DX11::ImGui_DX11::Color::Red, true);

						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, vehisize, Text, Screen.X, Screen.Y + 5, DX11::ImGui_DX11::Color::roge, true);

						if (Vehicle.Name != "Plane")
						{
							DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, vehisize, fuel, Screen.X - 0, Screen.Y + 20, DX11::ImGui_DX11::Color::roge, true);
						}

					}
					else
					{
						//DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, vehisize, Text, Screen.X, Screen.Y, Colors::vehicle, true);
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, vehisize, Text, Screen.X, Screen.Y + 5, Colors::vehicle, true);
						if (Vehicle.Name != "Plane")
						{
							DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, vehisize, fuel, Screen.X - 0, Screen.Y + 20, Colors::vehicle, true);
						}


					}


				}
			}
			if (Setting::BombAlert)
			{
				if (Data::BombAlertList.size() > 0)
				{
					TempBombAlertList.clear();
					TempBombAlertList = Data::BombAlertList;
					for (BombAlert& bomb : TempBombAlertList)
					{
						if (!Algorithm::WorldToScreen(bomb.Position, Screen, &Distance, Data::viewMatrix)) continue;

						string Name = bomb.Name + " (" + to_string(Distance) + "m)";
						//string time = to_string(bomb.timeLeft);
						DX11::ImGui_DX11::DrawCircle(Screen.X, Screen.Y, 12.0f, Colors::boxColor);
						DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, Setting::fontsize, Name, Screen.X, Screen.Y - 6, DX11::ImGui_DX11::Color::Red, true);
						continue;
					}
				}
			}


		}
	}
	else
	{

	}


	ImGui::EndFrame();
	ImGui::Render();


	pContext->OMSetRenderTargets(1, &pMainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return ogPresent(thisptr, SyncInterval, Flags, x);
}
void Unload()
{
	while (!GetAsyncKeyState(VK_END))
	{
		Sleep(100);
	}
	Game::isUnloaded = true;
	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);

	Sleep(1000);
	FreeLibraryAndExitThread(Game::CurrentModule, 0);
}
void Hook::Init()
{
	MH_Initialize();
	MH_CreateHook((void*)Game::DXGIPresent1, &hkPresent, reinterpret_cast<void**>(&ogPresent));
	MH_CreateHook((void*)&DefWindowProcW, &hkWndProc, reinterpret_cast<void**>(&ogWndProc));
	MH_EnableHook(MH_ALL_HOOKS);

	/*while (!GetAsyncKeyState(VK_END))
	{
		MH_DisableHook(MH_ALL_HOOKS);
		FreeLibraryAndExitThread(Game::CurrentModule, 0);
	}*/
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Unload, 0, 0, 0);
}