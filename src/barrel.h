#include "main.h"

#ifndef BARREL_H
#define BARREL_H


class Barrel {
public:
    Barrel() {}
    Barrel(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // BARREL_H
