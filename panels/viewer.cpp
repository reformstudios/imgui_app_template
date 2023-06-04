
struct Viewer
{
  void OnStart()
  {
  }

  void OnStop() // override
  {
  }

  void OnFrame() //(float deltaTime) // override
  {
    ImGui::Begin("Viewer");                          // Create a window called "Hello, world!" and append into it.
    ImGui::End();
  }
};