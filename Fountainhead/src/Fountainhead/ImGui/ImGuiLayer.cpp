#include "fhpch.h"
#include "Fountainhead/ImGui/ImGuiLayer.h"

#include <imgui.h>
#include "ImGuiBuild.cpp"

#include "Fountainhead/Core/Application.h"

//临时包含的头文件
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Fountainhead {
    // 构造函数调用基类 Layer 的构造函数，并为该层指定了名字。
    ImGuiLayer::ImGuiLayer()
        : Layer("ImGuiLayer")
    {
    }
    // 析构函数目前为空，清理工作在 OnDetach 中完成。
    ImGuiLayer::~ImGuiLayer()
    {
    }
    // 初始化 ImGui，创建 ImGui 上下文，配置基础功能（如键盘导航、停靠和多视口支持），设置界面风格，并绑定到 GLFW 和 OpenGL。
    void ImGuiLayer::OnAttach()
    {
        FH_PROFILE_FUNCTION();

        //设置ImGui上下文
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // 允许键盘控制
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // 允许窗口停靠
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // 启用多视口/平台窗口

        //设置ImGui风格
        ImGui::StyleColorsDark();

        //启用视口后，我们调整WindowRounding/WindowBg，使平台窗口看起来与常规窗口相同。
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        Application& app = Application::Get();
        GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

        // Setup Platform/Renderer bindings
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 410");
    }
    // 负责清理 ImGui 相关资源，包括关闭 ImGui 与 GLFW 和 OpenGL 的绑定，并销毁 ImGui 上下文。
    void ImGuiLayer::OnDetach()
    {
        FH_PROFILE_FUNCTION();

        //销毁上下文
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
    // 封装了 ImGui 渲染帧的开始和结束过程。
    // 准备新的 ImGui 帧。
    void ImGuiLayer::Begin()
    {
        FH_PROFILE_FUNCTION();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        static bool show = true;
        ImGui::ShowDemoWindow(&show);
    }
    // 渲染 ImGui 绘图数据到屏幕，并处理多视口渲染。
    void ImGuiLayer::End()
    {
        FH_PROFILE_FUNCTION();

        ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::Get();
        io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }

}