#include "app.hpp"
#include "panels/toolbar.cpp"
#include "panels/node_graph.cpp"
#include "panels/console.cpp"
#include "panels/log.cpp"
#include "panels/log.h"
#include "panels/viewer.cpp"
#include "panels/properties.cpp"

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
        static float f = 0.0f;
        static int counter = 0;

        update_toolbar();
        update_properties();
        update_node_graph();
        update_viewer();
        update_console();
        update_log();

        // Callbacks

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
