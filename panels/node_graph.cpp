# include "imgui-node-editor/imgui_node_editor.h"

namespace ed = ax::NodeEditor;

void update_node_graph()
{
  auto& io = ImGui::GetIO();
  ImGui::Begin("Node Graph"); 
  ImGui::Text("FPS: %.2f (%.2gms)", io.Framerate, io.Framerate ? 1000.0f / io.Framerate : 0.0f);                         // Create a window called "Hello, world!" and append into it.
  
  ImGui::End();
}
