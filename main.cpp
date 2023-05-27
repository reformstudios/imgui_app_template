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

      // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
      {
          static float f = 0.0f;
          static int counter = 0;
          ExampleAppLog& log = GetExampleAppLog();


          update_toolbar();
          update_properties();
          update_node_graph();
          update_viewer();
          update_console();
          update_log();



          // log.AddLog("yipee!\n");
      }

    }

  private:
    bool show_demo_window = true;
    bool show_another_window = true;
};

int main(int, char**)
{
  MyApp app;
  app.Run();

  return 0;
}
