#include "main.h"

#ifndef CANNONBALL_H
#define CANNONBALL_H


class Cannonball {
public:
    Cannonball() {}
    Cannonball(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void fire();
    void tick();
    void set_position(float x, float y, float z);
    bool is_launched;
    bounding_box_t cannon_box;
private:
    VAO *object1;
};

#endif // CANNONBALL_H
