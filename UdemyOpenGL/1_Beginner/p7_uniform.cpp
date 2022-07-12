#include "../utils.h"


extern void CreateTriangle(GLuint* pVAO, GLuint* pVBO);


int p7_uniform()
{
    INIT_WINDOW(1120, 630, "Triangle");

    GLuint VAO, VBO;
    CreateTriangle(&VAO, &VBO);
    GLuint program = CompileShadersProgram("shaders/p7_vshader.glsl", "shaders/p5_fshader.glsl");

    // Get location of uniform variable
    GLint uniOffsetX = glGetUniformLocation(program, "offsetX");
    bool direction = true;
    float offsetX = 0.f;
    float maxOffsetX = 0.5f;
    float speed = 1.f;


    double lastFrameTime = glfwGetTime();
    // Loop until window closed
    while (!glfwWindowShouldClose(mainWindow))
    {
        double now = glfwGetTime();
        double dt = now - lastFrameTime;
        lastFrameTime = now;
        // Get + Handle user input events
        glfwPollEvents();

        if (direction)
        {
            offsetX += speed * (float)dt;
            if (offsetX >= maxOffsetX)
            {
                offsetX = maxOffsetX;
                direction = !direction;
            }
        }
        else
        {
            offsetX -= speed * (float)dt;
            if (offsetX <= -maxOffsetX)
            {
                offsetX = -maxOffsetX;
                direction = !direction;
            }
        }

        // Clear window
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);

        glUniform1f(uniOffsetX, offsetX);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glUseProgram(0);

        glfwSwapBuffers(mainWindow);
    }

    return 0;
}
