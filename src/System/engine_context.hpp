class KeyboardInput;
class MouseInput;
class Window;

class EngineContext{
public:
    KeyboardInput* keyboard;
    MouseInput* mouse;
    Window* window;

    float deltaTime = 0.0f;


    EngineContext(Window* window);
    ~EngineContext();
};
