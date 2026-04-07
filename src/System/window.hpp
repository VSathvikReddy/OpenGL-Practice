#include <cstdint>

struct GLFWwindow;


struct WindowProperties{
    uint32_t width = 0;
    uint32_t height = 0;
    const char* title = "Default Name";
};

//Glew and Glfw Wrapper
class Window{
public:
    Window(const WindowProperties& properties);
    ~Window();

    GLFWwindow* GetNativeWindow() const;
private:
    GLFWwindow* m_Window;
    WindowProperties m_Properties;


    //Function called in case of error
    static void GLFW_error_callback(int error, const char* description);
    static void GLFW_framebuffer_size_callback(GLFWwindow* window, int width, int height);   
};