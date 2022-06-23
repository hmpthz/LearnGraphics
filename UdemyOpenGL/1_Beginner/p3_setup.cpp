#include "../utils.h"
using std::cout;
using std::cerr;


// Reset viewport everytime when window size is changed
void frameBufferSize_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int initWindow(
    int width, int height, const char* title,
    GLFWwindow** pMainWindow, int* pBufferWidth, int* pBufferHeight
)
{
    // Initialise GLFW
    if (!glfwInit())
    {
        cout << "GLFW initialisation failed!";
        glfwTerminate();
        return 1;
    }

    // Setup GLFW window properties
    // OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    // Core Profile = No Backwards Compatibility
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Allow Forward Compatbility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create the window
    *pMainWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);
    auto mainWindow = *pMainWindow;
    if (!mainWindow)
    {
        cout << "GLFW window creation failed!";
        glfwTerminate();
        return 1;
    }

    // Get Buffer Size information
    glfwGetFramebufferSize(mainWindow, pBufferWidth, pBufferHeight);

    // Set context for GLEW to use
    glfwMakeContextCurrent(mainWindow);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "GLAD initialisation failed!";
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }

    glfwSetFramebufferSizeCallback(mainWindow, frameBufferSize_callback);
    return 0;
}

int p3_setup()
{
    INIT_WINDOW(1120, 630, "Test Window");

    // Loop until window closed
    while (!glfwWindowShouldClose(mainWindow))
    {
        // Get + Handle user input events
        glfwPollEvents();

        // Clear window
        glClearColor(.0f, .0f, .2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(mainWindow);
    }

    return 0;
}