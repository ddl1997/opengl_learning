#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include<vector>

using namespace std;

//窗口大小调整回调函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

//输入控制
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

vector<float> processClearColor(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        return { 0.5f, 0.25f, 0.25f, 1.0f };
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        return { 0.25f, 0.5f, 0.25f, 1.0f };
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        return { 0.25f, 0.25f, 0.5f, 1.0f };
    else
        return { };
} 

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    vector<float> color = { 0.8f, 0.8f, 0.8f, 1.0f };
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        //清空屏幕
        /*auto temp = processClearColor(window);
        if (!temp.empty()) color = temp;
        glClearColor(color[0],color[1], color[2], color[3]);*/
        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

	return 0;
}