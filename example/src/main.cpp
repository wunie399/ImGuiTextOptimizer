//
// Created by 洋葱落日 on 2025/6/1.
//
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <stdio.h>
#include <GLFW/glfw3.h>
#include <random>
#include <string>

#include "YC.h"
#include "font.h"
// GLFW 错误回调函数
static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int main(int, char**)
{
    // 设置错误回调并初始化 GLFW
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // 配置 OpenGL 版本等（这里使用 OpenGL 3.0 及以上）
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    // 创建窗口
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui Example", NULL, NULL);
    if (window == NULL)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // 开启垂直同步

    // 创建 ImGui 上下文
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();

    // Setup Dear ImGui font
    io.Fonts->AddFontFromMemoryTTF((void *)Yclr_data, Yclr_size, 15.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());


    // 初始化平台与渲染器后端
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // 主循环
    while (!glfwWindowShouldClose(window))
    {
        // 处理事件
        glfwPollEvents();
        // 启动 ImGui 新一帧
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 创建一个简单窗口
        ImGui::Begin("洋葱落日 - 防重叠脚本 / Onion Sunset - Anti-overlap Script");
        
        // 定义变量 
        static int current_lang = 0;
        static int yc_v = 0;  // 防重叠脚本版本 0：1.0  1：2.1
        static int yc_a = 0;  // 防重叠脚本模式 0：2d  1：3d 
        static int edge_length = 60; // 边长
        static int text_amount = 0; // 文本量
        static bool Anti_overlapping = false; // 防重叠脚本开关

        static std::vector<Point> points;

        const char* langs[] = { "中文", "English" };
        ImGui::Combo("语言 / Language", &current_lang, langs, IM_ARRAYSIZE(langs));
        // 定义文本表
        const char* label_hello[] = { "作用:优化/解决ImGui大量文本渲染所出现的文本重叠！", "Purpose: Optimize/solve the text overlap caused by ImGui's large text rendering!" };
        const char* label_yc[]   = { "防重叠脚本版本", "Anti-overlap script version" };
        const char* label_yc_a[] = { "防重叠脚本模式", "Anti-overlap script mode" };
        const char* label_yc_v[] = { "1.0", "2.1" };
        const char* label_yc_a_2d[] = { "2D", "3D" };
        const char* label_edge_length[] = { "边长", "Edge Length" };
        const char* label_text_amount[] = { "文本量", "Text Amount" };
        const char* label_Anti_overlapping[] = { "防重叠脚本开关", "Anti-overlap script switch" };
        
        ImGui::Text("%s", label_hello[current_lang]);
        // 显示防重叠脚本版本
        ImGui::Combo(label_yc[current_lang], &yc_v, label_yc_v, IM_ARRAYSIZE(label_yc_v));
        // 显示防重叠脚本模式
        ImGui::Combo(label_yc_a[current_lang], &yc_a, label_yc_a_2d, IM_ARRAYSIZE(label_yc_a_2d));
        // 红色的文本 内容：注意：脚本版本2.1下的3D模式和脚本版本1.0下的3D模式没有区别！   2.1下的2D模式会有更高的占用   
        if (yc_v == 1) {
            ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "%s", current_lang == 0 ? "注意：脚本版本2.1下的3D模式和脚本版本1.0下的3D模式没有区别！   2.1下的2D模式会有更高的占用" : "Note: There is no difference between the 3D mode of script version 2.1 and the 3D mode of script version 1.0! The 2D mode under 2.1 will have higher usage");
        } 
        // 显示边长
        ImGui::SliderInt(label_edge_length[current_lang], &edge_length, 10, 5000, "%d", ImGuiSliderFlags_AlwaysClamp);
        // 显示文本量
        ImGui::SliderInt(label_text_amount[current_lang], &text_amount, 0, 2000, "%d", ImGuiSliderFlags_AlwaysClamp);
        // 显示防重叠脚本开关
        ImGui::Checkbox(label_Anti_overlapping[current_lang], &Anti_overlapping);
         // 显示帧率
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
        
        // 渲染文本 ImGui::GetBackgroundDrawList()
        ImGui::GetBackgroundDrawList()->AddText(ImVec2(10, 10), IM_COL32(255, 255, 255, 255), "This is a sample text rendered by ImGui.");
        // 渲染 无填充的红色边框的正方形在窗口中间 边长 edge_length
        ImGui::GetBackgroundDrawList()->AddRect(ImVec2((1280 - edge_length) / 2, (720 - edge_length) / 2), 
                                                 ImVec2((1280 + edge_length) / 2, (720 + edge_length) / 2), 
                                                 IM_COL32(255, 0, 0, 255), 0.0f, ImDrawFlags_None, 1.0f);
        // 固定种子在正方形内渲染文本量个数的文本 文本内容随机生成，位置随机，可以重叠    如果 Anti_overlapping 为 true，则使用防重叠脚本 用法 主要参考YC.h std::vector<Point> points; addToEnd(points, x, y, m, true, YC_V1); // 用1.0算法 addToEnd(points, x, y, m, true, YC_V2, 30, 15); // 用2.1算法，指定宽高用ImGui自带函数算出
        // 固定随机种子
        std::mt19937 rng(42);
        std::uniform_real_distribution<float> dist_x((1280 - edge_length) / 2.0f, (1280 + edge_length) / 2.0f);
        std::uniform_real_distribution<float> dist_y((720 - edge_length) / 2.0f, (720 + edge_length) / 2.0f);
        std::uniform_real_distribution<float> dist_m(0.0f, 100.0f);
        



        /***********************************主要实例***********************************/
        // 根据 yc_v 和 yc_a 的值选择防重叠脚本版本和模式
        points.clear();
        for (int i = 0; i < text_amount; ++i) {
            // 生成随机位置和文本内容
            float x = dist_x(rng);
            float y = dist_y(rng);
            float m = yc_a == 0 ? 0.0f : dist_m(rng);
            char buf[64];
            if (yc_a == 0) {
                snprintf(buf, sizeof(buf), "Text%d", i);
            } else {
                snprintf(buf, sizeof(buf), "Text%d m=%.1f", i, m);
            }
            ImVec2 text_size = ImGui::CalcTextSize(buf);
            if (Anti_overlapping) {
                if (yc_v == 0) { // 1.0
                    addToEnd(points, x, y, m, yc_a == 0, YC_V1);
                } else { // 2.1
                    addToEnd(points, x, y, m, yc_a == 0, YC_V2, text_size.x, text_size.y);
                }
                readLastPoint(points, x, y);
            } 
            // 渲染文本
            ImGui::GetBackgroundDrawList()->AddText(ImVec2(x, y), IM_COL32(255, 255, 0, 255), buf);
        }
        /***********************************主要实例***********************************/

        // 渲染
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // 清理资源
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext(ImGui::GetCurrentContext());
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
