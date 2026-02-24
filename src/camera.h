#ifndef CAMERA_H
#define CAMERA_h

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using Mat4f = glm::mat4;
using Vec3f = glm::vec3;

class  Camera{
private:
    // camera Attributes
    Vec3f Position;
    Vec3f Front = {0.0f,0.0f,-1.0f};
    Vec3f Up;
    Vec3f Right;
    Vec3f WorldUp = {0.0f,1.0f,0.0f};
    // euler Angles
    float Yaw = 0.0f ;
    float Pitch = 0.0f;
    // camera options
    float MovementSpeed = 0.05f;
    float MouseSensitivity;
    float Zoom;
public:
     Camera(glm::vec3 position);
    ~ Camera();
};




#endif