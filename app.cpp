// Part of ImGui Bundle - MIT License - Copyright (c) 2022-2023 Pascal Thomet - https://github.com/pthom/imgui_bundle
#include "immapp/immapp.h"
#include "implot/implot.h"
#include "imgui_md_wrapper.h"

#include "panels/toolbar.cpp"
#include "panels/node_graph.cpp"
#include "panels/console.cpp"
#include "panels/log.cpp"
#include "panels/log.h"
#include "panels/viewer.cpp"
#include "panels/properties.cpp"

#include <cmath>

struct App
    //: public Application
{
    // Struct to hold basic information about connection between
    // pins. Note that connection (aka. link) has its own ID.
    // This is useful later with dealing with selections, deletion
    // or other operations.
    struct LinkInfo
    {
        ed::LinkId Id;
        ed::PinId  InputId;
        ed::PinId  OutputId;
    };

    void OnStart() //override
    {
        m_Viewer.OnStart();
        m_NodeEditor.OnStart();
    }

    void OnStop() // override
    {
        m_Viewer.OnStop();
        m_NodeEditor.OnStop();
    }

    
    void OnFrame() //(float deltaTime) // override
    {
        // Setup Windowsize and dockspace.
        static bool dockspaceOpen = true;
        ImGui::SetWindowSize(ImGui::GetMainViewport()->Size);
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImGui::GetMainViewport()->Size);
        ImGui::Begin("RSTools", &dockspaceOpen, ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize); // main_window
        ImGuiID dockspaceID = ImGui::GetID("RSToolsDockSpace");
        ImGui::DockSpace(dockspaceID, ImVec2(0, 0), ImGuiDockNodeFlags_PassthruCentralNode);

        // Update panels
        update_console();
        update_log();
        update_toolbar();
        update_properties();
        // update_viewer();
        m_NodeEditor.OnFrame();
        m_Viewer.OnFrame();

        // End Dockspace
        ImGui::End(); // Dockspace
        ImGui::End(); // RSTools main_window
    }

    NodeEditor           m_NodeEditor;              // Declare nodeEditor Class.
    Viewer               m_Viewer;                  // Declare nodeEditor Class.
};

int main(int , char *[])
{
    App app;
    HelloImGui::RunnerParams runnerParams;
    runnerParams.callbacks.ShowGui = [&] { app.OnFrame(); };
    runnerParams.callbacks.PostInit = [&] { app.OnStart(); };
    runnerParams.callbacks.BeforeExit = [&] { app.OnStop(); };
    runnerParams.appWindowParams.windowTitle = "Re:Comp";
    runnerParams.appWindowParams.windowGeometry.size = {1200, 800};
    HelloImGui::Run(runnerParams);
    return 0;
}
