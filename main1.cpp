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

    float vertices[] = {
        0.5f, 0.5f, 0.0f,   // 右上角
        0.5f, -0.5f, 0.0f,  // 右下角
        -0.5f, -0.5f, 0.0f, // 左下角
        -0.5f, 0.5f, 0.0f   // 左上角
    };

    unsigned int indices[][3] = { // 注意索引从0开始! 
        { 0, 1, 3 }, // 第一个三角形
        { 1, 2, 3 }  // 第二个三角形
    };

    //顶点着色器
    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    
    ////片段着色器1
    //const char* fragmentShaderSourceOrange = "#version 330 core\n"
    //    "out vec4 FragColor;\n"
    //    "void main()\n"
    //    "{\n"
    //    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    //    "}\0";
    //unsigned int fragmentShaderOrange;
    //fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);
    //glShaderSource(fragmentShaderOrange, 1, &fragmentShaderSourceOrange, NULL);
    //glCompileShader(fragmentShaderOrange);

    ////片段着色器2
    //const char* fragmentShaderSourceYellow = "#version 330 core\n"
    //    "out vec4 FragColor;\n"
    //    "void main()\n"
    //    "{\n"
    //    "   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
    //    "}\0";
    //unsigned int fragmentShaderYellow;
    //fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
    //glShaderSource(fragmentShaderYellow, 1, &fragmentShaderSourceYellow, NULL);
    //glCompileShader(fragmentShaderYellow);

    ////着色器程序1
    //unsigned int shaderProgramOrange;
    //shaderProgramOrange = glCreateProgram();
    //glAttachShader(shaderProgramOrange, vertexShader);
    //glAttachShader(shaderProgramOrange, fragmentShaderOrange);
    //glLinkProgram(shaderProgramOrange);
    //glDeleteShader(vertexShader);
    //glDeleteShader(fragmentShaderOrange);

    ////着色器程序2
    //unsigned int shaderProgramYellow;
    //shaderProgramYellow = glCreateProgram();
    //glAttachShader(shaderProgramYellow, vertexShader);
    //glAttachShader(shaderProgramYellow, fragmentShaderYellow);
    //glLinkProgram(shaderProgramYellow);
    //glDeleteShader(vertexShader);
    //glDeleteShader(fragmentShaderYellow);
   

    //片段着色器
    const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "uniform vec4 _color;\n"
        "void main()\n"
        "{\n"
        "   FragColor = _color;\n"
        "}\0";
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    //着色器程序
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    unsigned int EBOs[2];
    glGenBuffers(2, EBOs);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]), indices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[1]), indices[1], GL_STATIC_DRAW);

    //链接顶点属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    vector<float> color = { 0.8f, 0.8f, 0.8f, 1.0f };
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        //清空屏幕
        /*auto temp = processClearColor(window);
        if (!temp.empty()) color = temp;
        glClearColor(color[0],color[1], color[2], color[3]);*/
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        float timeValue = glfwGetTime();
        float redValue = (sin(timeValue) / 2.0f) + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "_color");
        glUniform4f(vertexColorLocation, redValue, 0.0f, 0.0f, 1.0f); //更新一个uniform之前你必须先使用程序（调用glUseProgram)，因为它是在当前激活的着色器程序中设置uniform的。

        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[0]);
        //glUseProgram(shaderProgramOrange);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        /*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[1]);
        glUseProgram(shaderProgramYellow);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);*/
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(2, EBOs);
    /*glDeleteProgram(shaderProgramOrange);
    glDeleteProgram(shaderProgramYellow);*/
    glfwTerminate();

	return 0;
}