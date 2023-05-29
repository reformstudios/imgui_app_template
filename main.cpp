#include "app.hpp"
#include "panels/toolbar.cpp"
#include "panels/node_graph.cpp"
#include "panels/console.cpp"
#include "panels/log.cpp"
#include "panels/log.h"
#include "panels/viewer.cpp"
#include "panels/properties.cpp"
#include <Windows.h>
#include <GLFW/glfw3native.h>

// Forward Declarations
void ShowExampleAppLog(bool* p_open);

class MyApp : public App<MyApp>
{
  ExampleAppLog log;  // Define the log variable as a member of the class

  public:
    MyApp() = default;
    ~MyApp() = default;

    void StartUp()
    {
      
    }

    void Update()
    {
      {
          static bool dockspaceOpen = true;
          // ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar;
          // window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			    // window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
          // ImGui::SetNextWindowSizeConstraints(ImVec2(0, 0), ImVec2(FLT_MAX, FLT_MAX)); // Allow the window to resize freely
          ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDocking;
          ImGuiDockNodeFlags dockNodeFlags = ImGuiDockNodeFlags_NoDockingInCentralNode;
          
          // Make the ImGui window full size
          ImGui::SetWindowSize(ImGui::GetMainViewport()->Size);
          ImGui::SetNextWindowPos(ImVec2(0, 0));
          ImGui::SetNextWindowSize(ImGui::GetMainViewport()->Size);

          // ImGui::SetNextWindowSizeConstraints(ImVec2(0, 0), ImVec2(FLT_MAX, FLT_MAX));
          ImGui::Begin("RSTools", &dockspaceOpen, ImGuiWindowFlags_NoTitleBar|  ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize); // main_window
          // Get the DockSpace ID
          ImGuiID dockspaceID = ImGui::GetID("MyDockSpace");
          ImGui::DockSpace(dockspaceID, ImVec2(0, 0), ImGuiDockNodeFlags_PassthruCentralNode);

          
          ImGui::End(); // main_window
          update_console();
          update_log();
          update_toolbar();
          update_properties();
          update_node_graph();
          update_viewer();
          
          // Close the GLFW window when the ImGui window is closed
          if (!dockspaceOpen)
          {
              glfwSetWindowShouldClose(window, GLFW_TRUE);
          }
          // Update the key state
          if (g_KeyPressed) {
              ExampleAppLog& log = GetExampleAppLog();
              log.AddLog("Key pressed: %d\n", g_KeyPressedCode);
              g_KeyPressed = false;
              g_KeyPressedCode = -1;
          }

      }

    }

    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
      if (action == GLFW_PRESS) {
          g_KeyPressed = true;
          g_KeyPressedCode = key;
      }
    }

  private:
    static bool g_KeyPressed;
    static int g_KeyPressedCode;
};

int main(int, char**)
{
  MyApp app;
  app.Run();

  return 0;
}

bool MyApp::g_KeyPressed    = false;
int MyApp::g_KeyPressedCode = -1;
