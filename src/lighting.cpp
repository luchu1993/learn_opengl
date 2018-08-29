#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

enum VAO_IDs { Cube, Light, NumVAOs };
enum Shader_IDs { Cube_Shader, Light_Shader, NumShaders };
enum VBO_IDs { ArrayBuffer, NumVBOs };
enum Attrib_Index { vPosition, vNormal };
GLuint VAOs[NumVAOs];
GLuint VBOs[NumVBOs];
GLuint Shaders[NumShaders];

const int ScreenWidth = 800;
const int ScreenHeight = 600;

glm::vec3 CameraPos(0.0f, 0.0f, 5.0f);
glm::vec3 CameraFront(0.0f, 0.0f, -1.0f);
glm::vec3 CameraUp(0.0f, 1.0f, 0.0f);
float CameraSpeed = 5.0f;
glm::vec3 LightPos(10.0f, 10.0f, -10.0f);
glm::vec4 LightColor(1.0f, 1.0f, 1.0f, 1.0f);
glm::vec4 CubeColor(0.5f, 0.6f, 0.6f, 1.0f);
glm::vec3 ObjectPos(0.0f, 0.0f, 0.0f);

void processInput(GLFWwindow* window, float deltaTime);
void framebuffer_resize_callback(GLFWwindow* window, int width, int height);
typedef struct {
    GLuint type;
    const char* file;
} ShaderInfo;

ShaderInfo shader_info[NumShaders][3] =
{
    {
        { GL_VERTEX_SHADER, "shaders/cube.vert" },
        { GL_FRAGMENT_SHADER, "shaders/cube.frag" },
        { GL_NONE, nullptr }
    },
    {
        { GL_VERTEX_SHADER, "shaders/light.vert" },
        { GL_FRAGMENT_SHADER, "shaders/light.frag"},
        { GL_NONE, nullptr }
    }
};

GLuint LoadShaders(const ShaderInfo* shader_info)
{
    GLint success;
    char infoLog[512];
    vector<GLuint> shaders;

    while (shader_info->type != GL_NONE )
    {
        GLuint type = shader_info->type;
        const char* file = shader_info->file;
        // load shader source from file
        ifstream in(file);
        ostringstream tmp;
        tmp << in.rdbuf();
        string code = tmp.str();
        const char* shaderCode = code.c_str();
        in.close();

        // create and compile shader
        GLuint shader = glCreateShader(type);
        glShaderSource(shader, 1, &shaderCode, nullptr);
        glCompileShader(shader);
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            cout << "Compile shader " << file << " error: " << infoLog << endl;
            return 0;
        }
        shaders.push_back(shader);
        ++shader_info;
    }

    // create program
    GLuint program = glCreateProgram();
    for (GLuint shader : shaders)
        glAttachShader(program, shader);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        cout << "Link program error: " << infoLog << endl;
        return 0;
    }

    for (GLuint shader : shaders)
        glDeleteShader(shader);
    
    return program;
}

const GLfloat vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

int main(int argc, char *argv[])
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(ScreenWidth, ScreenHeight, "Learn OpenGL", nullptr, nullptr);
    if (!window)
    {
        cout << "Failed to create glfw window." << endl;
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);
    // load GLAD
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        cout << "Failed to load GLAD loader." << endl;
        return -1;
    }

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);

    glGenVertexArrays(NumVAOs, VAOs);
    glGenBuffers(NumVBOs, VBOs);
    
    glBindVertexArray(VAOs[Cube]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[ArrayBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0 );
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(vNormal);

    glBindVertexArray(VAOs[Light]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[ArrayBuffer]);
    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0 );
    glEnableVertexAttribArray(vPosition);

    // load shaders
    Shaders[Cube] = LoadShaders(shader_info[Cube]);
    Shaders[Light] = LoadShaders(shader_info[Light]);

    float lastTime = 0.0f;
    glm::mat4 model, view, projection;
    while (!glfwWindowShouldClose(window))
    {
        float currentTime = glfwGetTime();
        processInput(window, currentTime - lastTime);
        // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // view, projection matrix
        projection = glm::perspective(glm::radians(45.0f), (float)width/(float)height, 0.1f, 100.0f);
        view = glm::lookAt(CameraPos, CameraPos+CameraFront, CameraUp);

        // Cube
        model = glm::mat4(1.0f);
        model = glm::translate(model, ObjectPos);
        model = glm::rotate(model, glm::radians(currentTime * 10.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        glUseProgram(Shaders[Cube_Shader]);
        glUniformMatrix4fv(glGetUniformLocation(Shaders[Cube_Shader], "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(Shaders[Cube_Shader], "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(Shaders[Cube_Shader], "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        // LightPos, LightColor
        glUniform3fv(glGetUniformLocation(Shaders[Cube_Shader], "LightPos"), 1, glm::value_ptr(LightPos));
        glUniform4fv(glGetUniformLocation(Shaders[Cube_Shader], "LightColor"), 1, glm::value_ptr(LightColor));
        glUniform4fv(glGetUniformLocation(Shaders[Cube_Shader], "ObjectColor"), 1, glm::value_ptr(CubeColor));
        glUniform3fv(glGetUniformLocation(Shaders[Cube_Shader], "ViewPos"), 1, glm::value_ptr(CameraPos));
        glBindVertexArray(VAOs[Cube]);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Light
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.2f));
        model = glm::translate(model, LightPos);
        glUseProgram(Shaders[Light_Shader]);
        glUniformMatrix4fv(glGetUniformLocation(Shaders[Light_Shader], "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(Shaders[Light_Shader], "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(Shaders[Light_Shader], "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        // Light Color
        glUniform4fv(glGetUniformLocation(Shaders[Light_Shader], "LightColor"), 1, glm::value_ptr(LightColor));
        glBindVertexArray(VAOs[Light]);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
        lastTime = currentTime;
    }
    return 0;
}

void processInput(GLFWwindow* window, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    // move camera
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        CameraPos += CameraFront * CameraSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        CameraPos -= CameraFront * CameraSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        CameraPos -= glm::normalize(glm::cross(CameraFront, CameraUp)) * CameraSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        CameraPos += glm::normalize(glm::cross(CameraFront, CameraUp)) * CameraSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        CameraPos += CameraUp * CameraSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        CameraPos -= CameraUp * CameraSpeed * deltaTime;
}

void framebuffer_resize_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}