#include "../utils.h"
#include <fstream>


void CreateTriangle(GLuint *pVAO, GLuint *pVBO)
{
    GLfloat vertices[] = {
        -1.f, -1.f, 0.f,
        1.f, -1.f, 0.f,
        0.f, 1.f, 0.f
    };

    glGenVertexArrays(1, pVAO);
    glBindVertexArray(*pVAO);

    glGenBuffers(1, pVBO);
    glBindBuffer(GL_ARRAY_BUFFER, *pVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void AddShader(std::string& shaderCode, GLenum shaderType, int program)
{
    GLuint shader = glCreateShader(shaderType);

    const GLchar* theCode[1];
    theCode[0] = shaderCode.c_str();

    GLint codeLength[1];
    codeLength[0] = shaderCode.size();

    glShaderSource(shader, 1, theCode, codeLength);
    glCompileShader(shader);

    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(shader, 1024, NULL, eLog);
        cerr << std::format("Error compiling the {} shader: '{}'\n", shaderType, eLog);
        return;
    }

    glAttachShader(program, shader);
}

int CompileShadersProgram(const char* vShader, const char* fShader)
{
    std::string vShaderCode = LoadFile(vShader);
    std::string fShaderCode = LoadFile(fShader);

    GLuint program = glCreateProgram();

    if (!program)
    {
        cout << "Failed to create shader program\n";
        return 0;
    }

    AddShader(vShaderCode, GL_VERTEX_SHADER, program);
    AddShader(fShaderCode, GL_FRAGMENT_SHADER, program);

    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(program, sizeof(eLog), NULL, eLog);
        cout << std::format("Error linking program: '{}'\n", eLog);
        return 0;
    }

    glValidateProgram(program);
    glGetProgramiv(program, GL_VALIDATE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(program, sizeof(eLog), NULL, eLog);
        cout << std::format("Error validating program: '%s'\n", eLog);
        return 0;
    }
    return program;
}

int p5_triangle()
{
    INIT_WINDOW(1120, 630, "Triangle");

    GLuint VAO, VBO;
    CreateTriangle(&VAO, &VBO);
    GLuint program = CompileShadersProgram("shaders/p5_vshader.glsl", "shaders/p5_fshader.glsl");

    // Loop until window closed
    while (!glfwWindowShouldClose(mainWindow))
    {
        // Get + Handle user input events
        glfwPollEvents();

        // Clear window
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glUseProgram(0);

        glfwSwapBuffers(mainWindow);
    }

    return 0;
}

std::string LoadFile(const char* filename)
{
    std::ifstream fin(filename);
    return std::string(std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>());
}
