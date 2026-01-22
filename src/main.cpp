#include <cstddef>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <ostream>

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "\n"
    "void main() {\n"
    "    FragColor = vec4(0.0f, 1.0f, 0.0f, 0.0f);\n"
    "}\0";

const char *vertexShaderSource = "#version 330 core\n" // Dynamically complied at runtime barebones vertex shader
    "layout (location = 0) in vec3 aPos;\n"
    "void main() {\n"
    "\tgl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

int WINDOWWIDTH = 800;
int WINDOWHEIGHT = 600;


void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);


int main() {
    
    glfwInit(); // Starts library allowing functions
    
    // Telling GLFW to use OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Disable backwards compatiblity
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Needed on mac for some reason

    GLFWwindow* window = glfwCreateWindow(WINDOWWIDTH, WINDOWHEIGHT, "OpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to load GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    float vertices[] = { // Vertice data
        -.5f, -.5f, 0.f,
        .5f, -.5f, 0.f,
        0.f, .5f, 0.f
    };
    unsigned int VBO;
    glGenBuffers(1, &VBO); // assign 1 ID (size 1, not num) to Vertice Buffer Object ptr
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // Stateful binding, when utlizing GL_ARRAY_BUFFER will affect VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Assign vertice data to buffer
    
    unsigned int vertexShader; 
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // Load in one vertex shader from string pointer 
    glCompileShader(vertexShader);

    // Logging
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) { // If fail log to buffer
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAIL" << infoLog << std::endl;
    }

    

    glViewport(0, 0, WINDOWWIDTH, WINDOWHEIGHT);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // Callback for when resizing

    while (!glfwWindowShouldClose(window)) {
        processInput(window); // Check inputs (keypress, joystick)

        // Render logic in middle
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Check and call events then swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}