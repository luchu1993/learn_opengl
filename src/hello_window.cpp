#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

bool wireFrame = false;

static void framebuffer_resize_callback(GLuint width, GLuint height)
{
    glViewport(0, 0, width, height);
}

static void key_callback(GLFWwindow* window, int key, int scancodes, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE)
    {
        glfwSetWindowShouldClose(window, true);
    } 
    else if (key == GLFW_KEY_Q && action == GLFW_PRESS) 
    {
        glPolygonMode(GL_FRONT_AND_BACK, wireFrame ? GL_FILL : GL_LINE);
        wireFrame = !wireFrame;
    } 
}

typedef struct {
    GLuint type;
    const char* file;
} ShaderInfo;

ShaderInfo shader_info[] =
{
    { GL_VERTEX_SHADER, "shaders/triangles.vert" },
    { GL_FRAGMENT_SHADER, "shaders/triangles.frag" },
    { GL_NONE, nullptr }
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

GLuint LoadTexture(const char* image)
{
    GLuint texture = 0;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    int width, height, nChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(image, &width, &height, &nChannels, 0);
    if (data) {
        if (nChannels == 4)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        else
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);    
    } else {
        cout << "Failed to load texture" << endl;
    }
    stbi_image_free(data);

    return texture;
}

enum VAO_IDs { Triangle, NumVAOs };
enum Buffer_IDs { ArrayBuffer, IndexBuffer, NumBuffers };
enum Texture_IDs { Container, Face, NumTextures };

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
GLuint Textures[NumTextures];

enum { vPosition, vColor, vTexCoord };

const GLfloat vertices[] = {
    // vPosition  // vColor         // vTexCoord
    -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
};

const GLuint indices[] = {
    0, 1, 2,
    0, 2, 3
};

int main(int argc, char* argv[])
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create glfw window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Learn OpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        cout << "Can't create glfw window!" << endl;
        return -1;
    }
    glfwMakeContextCurrent(window);

    if ( !gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    GLFWframebuffersizefun(framebuffer_resize_callback);
    glfwSetKeyCallback(window, key_callback);
    glViewport(0, 0, 800, 600);

    GLint max_combined_texture_image_uints = 0;
    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &max_combined_texture_image_uints);
    cout << max_combined_texture_image_uints << endl;

    // create Vertex Array Object
    glGenVertexArrays(NumVAOs, VAOs);
    glBindVertexArray(VAOs[Triangle]);
    // create Vertex Buffer Object
    glGenBuffers(NumBuffers, Buffers);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // create Element Buffer Object
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffers[IndexBuffer]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // create Texture Object
    Textures[Container] = LoadTexture("images/container.jpg");
    Textures[Face] = LoadTexture("images/face.png");

    // use shader program
    GLuint program = LoadShaders(shader_info);
    glUseProgram(program);
    glUniform1i(glGetUniformLocation(program, "sampler0"), 0);
    glUniform1i(glGetUniformLocation(program, "sampler1"), 1);

    // pipeline assamble
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 7*sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_FALSE, 7*sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(vColor);
    glVertexAttribPointer(vTexCoord, 2, GL_FLOAT, GL_FALSE, 7*sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));
    glEnableVertexAttribArray(vTexCoord);

    // active texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Textures[Container]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, Textures[Face]);

    

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAOs[Triangle]);
        float time = (float) glfwGetTime();
        glm::mat4 trans(1.0f);
        trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));
        trans = glm::rotate(trans, glm::radians(time * 10), glm::vec3(0.0f, 0.0f, 1.0f));
        GLuint location = glGetUniformLocation(program, "transform");
        glUniformMatrix4fv(location, 1, false, glm::value_ptr(trans));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(NumVAOs, VAOs);
    glDeleteBuffers(NumBuffers, Buffers);
    glDeleteTextures(NumTextures, Textures);

    glfwTerminate();
    return 0;
}