struct GLFWwindow;

class MouseInput{
public:
    

    MouseInput(GLFWwindow* window);
    void EndFrame();

private:

    //Top-Left corner of the window, for glfw
    struct{
        double X = 0.0, Y = 0.0;
        double prevX = 0.0, prevY = 0.0;
    } m_State;


    static void GLFW_mouse_callback(GLFWwindow* window, double xpos, double ypos);
};