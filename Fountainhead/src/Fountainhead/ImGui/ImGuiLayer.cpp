#include "fhpch.h"
#include "Fountainhead/ImGui/ImGuiLayer.h"

#include <imgui.h>
#include "ImGuiBuild.cpp"

#include "Fountainhead/Core/Application.h"

//��ʱ������ͷ�ļ�
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Fountainhead {
    // ���캯�����û��� Layer �Ĺ��캯������Ϊ�ò�ָ�������֡�
    ImGuiLayer::ImGuiLayer()
        : Layer("ImGuiLayer")
    {
    }
    // ��������ĿǰΪ�գ��������� OnDetach ����ɡ�
    ImGuiLayer::~ImGuiLayer()
    {
    }
    // ��ʼ�� ImGui������ ImGui �����ģ����û������ܣ�����̵�����ͣ���Ͷ��ӿ�֧�֣������ý����񣬲��󶨵� GLFW �� OpenGL��
    void ImGuiLayer::OnAttach()
    {
        FH_PROFILE_FUNCTION();

        //����ImGui������
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // ������̿���
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // ������ͣ��
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // ���ö��ӿ�/ƽ̨����

        //����ImGui���
        ImGui::StyleColorsDark();

        //�����ӿں����ǵ���WindowRounding/WindowBg��ʹƽ̨���ڿ������볣�洰����ͬ��
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
    // �������� ImGui �����Դ�������ر� ImGui �� GLFW �� OpenGL �İ󶨣������� ImGui �����ġ�
    void ImGuiLayer::OnDetach()
    {
        FH_PROFILE_FUNCTION();

        //����������
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
    // ��װ�� ImGui ��Ⱦ֡�Ŀ�ʼ�ͽ������̡�
    // ׼���µ� ImGui ֡��
    void ImGuiLayer::Begin()
    {
        FH_PROFILE_FUNCTION();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        static bool show = true;
        ImGui::ShowDemoWindow(&show);
    }
    // ��Ⱦ ImGui ��ͼ���ݵ���Ļ����������ӿ���Ⱦ��
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