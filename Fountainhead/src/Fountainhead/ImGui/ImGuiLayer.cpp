#include "fhpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
//#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
//#define IMGUI_IMPL_OPENGL_LOADER_GLAD
//#include "examples/imgui_impl_glfw.cpp"
//#include "examples/imgui_impl_opengl3.cpp"
#include "ImGuiBuild.cpp"

#include "Fountainhead/Application.h"

//临时包含的头文件
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Fountainhead {

    ImGuiLayer::ImGuiLayer()
        : Layer("ImGuiLayer")//调用基类的构造函数，特定的渲染调试的层
    {
    }

    ImGuiLayer::~ImGuiLayer()
    {
    }

    void ImGuiLayer::OnAttach()
    {
        ////ImGui标准设置流程
        //ImGui::CreateContext();//创建ImGui上下文
        //ImGui::StyleColorsDark();
        //
        //ImGuiIO& io = ImGui::GetIO();
        //io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;//鼠标指针
        //io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;//鼠标坐标

        ////临时使用ImGui按键映射按键码，我们最终会使用自己的按键码
        //io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
        //io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
        //io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
        //io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
        //io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
        //io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
        //io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
        //io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
        //io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
        //io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
        //io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
        //io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
        //io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
        //io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
        //io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
        //io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
        //io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
        //io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
        //io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
        //io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
        //io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

        ////初始化
        //ImGui_ImplOpenGL3_Init("#version 410");

        //设置ImGui上下文
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
        //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
        //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

        //设置ImGui风格
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();

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

    void ImGuiLayer::OnDetach()
    {
        //销毁上下文
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::Begin()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiLayer::End()
    {
        ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::Get();
        io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

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

    void ImGuiLayer::OnImGuiRender()
    {
        static bool show = true;
        ImGui::ShowDemoWindow(&show);
    }

    //void ImGuiLayer::OnUpdate()
    //{
    //    ImGuiIO& io = ImGui::GetIO();
    //    Application& app = Application::Get();//获取App单例，获取窗口的宽高进行设置
    //    io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

    //    float time = (float)glfwGetTime();//设置DeltaTime
    //    io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
    //    m_Time = time;

    //    ImGui_ImplOpenGL3_NewFrame();
    //    ImGui::NewFrame();


    //    static bool show = true;
    //    ImGui::ShowDemoWindow(&show);//显示ImGui演示窗口

    //    ImGui::Render();
    //    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    //}

    //void ImGuiLayer::OnEvent(Event& event)
    //{
    //    //当事件进入到这个ImGui Layer时，我们需要检查事件类型，然后转发给下面对应的函数
    //    EventDispatcher dispatcher(event);
    //    dispatcher.Dispatch<MouseButtonPressedEvent>(FH_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
    //    dispatcher.Dispatch<MouseButtonReleasedEvent>(FH_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
    //    dispatcher.Dispatch<MouseMovedEvent>(FH_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
    //    dispatcher.Dispatch<MouseScrolledEvent>(FH_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
    //    dispatcher.Dispatch<KeyPressedEvent>(FH_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
    //    dispatcher.Dispatch<KeyReleasedEvent>(FH_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
    //    dispatcher.Dispatch<KeyTypedEvent>(FH_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
    //    dispatcher.Dispatch<WindowResizeEvent>(FH_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
    //}

    //bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
    //{
    //    ImGuiIO& io = ImGui::GetIO();
    //    io.MouseDown[e.GetMouseButton()] = true;

    //    return false;//这里返回false是因为希望由其他层处理鼠标点击事件，因此我们不想要这个Layer消耗每一个鼠标事件
    //}

    //bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
    //{
    //    ImGuiIO& io = ImGui::GetIO();
    //    io.MouseDown[e.GetMouseButton()] = false;

    //    return false;
    //}

    //bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
    //{
    //    ImGuiIO& io = ImGui::GetIO();
    //    io.MousePos = ImVec2(e.GetX(), e.GetY());

    //    return false;
    //}

    //bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
    //{
    //    ImGuiIO& io = ImGui::GetIO();
    //    io.MouseWheelH += e.GetXOffset();
    //    io.MouseWheel += e.GetYOffset();

    //    return false;
    //}

    //bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
    //{
    //    ImGuiIO& io = ImGui::GetIO();
    //    io.KeysDown[e.GetKeyCode()] = true;

    //    io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
    //    io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
    //    io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
    //    io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

    //    return false;
    //}

    //bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
    //{
    //    ImGuiIO& io = ImGui::GetIO();
    //    io.KeysDown[e.GetKeyCode()] = false;

    //    return false;
    //}

    //bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
    //{
    //    ImGuiIO& io = ImGui::GetIO();
    //    int keycode = e.GetKeyCode();
    //    if (keycode > 0 && keycode < 0x10000)
    //        io.AddInputCharacter((unsigned short)keycode);

    //    return false;
    //}

    //bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
    //{
    //    ImGuiIO& io = ImGui::GetIO();
    //    io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
    //    io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
    //    glViewport(0, 0, e.GetWidth(), e.GetHeight());

    //    return false;
    //}

}