#pragma once
#include "imgui.h"
#include "panels/log.h"
#include <iostream>
#include <cstdlib>
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h> // Will drag system OpenGL headers


static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

template <typename Derived>
class App
{
  public:
    App()
    {
      // const std::string app_name = "Compositor";
      const char app_name[] = "Compositor";
      // Setup
      glfwSetErrorCallback(glfw_error_callback);
      if (!glfwInit())
          std::exit(1);

      // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
      // GL ES 2.0 + GLSL 100
      const char* glsl_version = "#version 100";
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
      glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
      // GL 3.2 + GLSL 150
      const char* glsl_version = "#version 150";
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
      // GL 3.0 + GLSL 130
      const char* glsl_version = "#version 130";
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
      //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
      //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

      // Create window with graphics context
      window = glfwCreateWindow(1280, 720, app_name, nullptr, nullptr);
      if (window == nullptr)
          std::exit(1);
      glfwMakeContextCurrent(window);
      glfwSwapInterval(1); // Enable vsync

      // setup callbacks
      glfwSetKeyCallback(window, &Derived::KeyCallback);

      // Setup Dear ImGui context
      IMGUI_CHECKVERSION();
      ImGui::CreateContext();
      ImGuiIO& io = ImGui::GetIO(); (void)io;
      io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
      io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
      io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;      // Enable Gamepad Controls

      // Setup Dear ImGui style
      ImGui::StyleColorsDark();

      //ImGui::StyleColorsLight();

      // Setup Platform/Renderer backends
      ImGui_ImplGlfw_InitForOpenGL(window, true);
      ImGui_ImplOpenGL3_Init(glsl_version);

      // Our state
      bool show_demo_window = true;
      bool show_another_window = true;

    }

    ~App()
    {
      // Destructor : Cleanup
      ImGui_ImplOpenGL3_Shutdown();
      ImGui_ImplGlfw_Shutdown();
      ImGui::DestroyContext();

      glfwDestroyWindow(window);
      glfwTerminate();
    }

    void Run()
    {
      // Our initial State
      StartUp();

      // Main Loop
      while(!glfwWindowShouldClose(window))
      {
        glfwPollEvents();



        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Enable docking. This needs to be above all other windows for them to be dockable.
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

        Update();




        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);

      }
    }

    void Update()
    {
      static_cast<Derived*>(this)->Update();
    };

    void StartUp()
    {
      static_cast<Derived*>(this)->StartUp();
    };



    // Clearcolor
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // imgui io
    ImGuiIO io;

  private:
    // Private window pointer
    GLFWwindow* window;



};


