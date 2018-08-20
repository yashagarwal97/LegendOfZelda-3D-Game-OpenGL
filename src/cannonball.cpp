#include "cannonball.h"
#include "main.h"

Cannonball::Cannonball(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;

    this->cannon_box.width = 1;
    this->cannon_box.length = 1;
    this->cannon_box.height = 1;
    this->is_launched = false;

    static const GLfloat vertex_buffer_data[] = {
        -0.5f, 0.5f, 0.5f,
        -0.5f,-0.5f,0.5f,
        0.5f,0.5f,0.5f,
        0.5f,0.5f,0.5f,
        -0.5f,-0.5f,0.5f,
        0.5f,-0.5f,0.5f,

        0.5f, -0.5f, 0.5f,
        0.5f,0.5f,-0.5f,
        0.5f,-0.5f,0.5f,
        0.5f,-0.5f,0.5f,
        0.5f,0.5f,-0.5f,
        0.5f,-0.5f,-0.5f,

        0.5f,0.5f,-0.5f,
        0.5f,-0.5f,-0.5f,
        -0.5f,-0.5f,-0.5f,
        -0.5f,-0.5f,-0.5f,
        0.5f,0.5f,-0.5f,
        -0.5f,0.5f,-0.5f,

        -0.5f,0.5f,-0.5f,
        -0.5f,-0.5f,-0.5f,
        -0.5f,0.5f,0.5f,
        -0.5f,-0.5f,-0.5f,
        -0.5f,0.5f,0.5f,
        -0.5f,-0.5f,0.5f,

        -0.5f,0.5f,0.5f,
        -0.5f,0.5f,-0.5f,
        0.5f,0.5f,0.5f,
        -0.5f,0.5f,-0.5f,
        0.5f,0.5f,0.5f,
        0.5f,0.5f,-0.5f,

        -0.5f,-0.5f,0.5f,
        -0.5f,-0.5f,-0.5f,
        0.5f,-0.5f,0.5f,
        -0.5f,-0.5f,-0.5f,
        0.5f,-0.5f,0.5f,
        0.5f,-0.5f,-0.5f
    };

    this->object1 = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data, COLOR_DBLUE, GL_FILL);
}

void Cannonball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
}

void Cannonball::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Cannonball::tick() {
    this->cannon_box.x = position.x;
    this->cannon_box.z = position.z;
    this->cannon_box.y = position.y;
}

void Cannonball::fire(){
    this->cannon_box.z = position.z;
    this->cannon_box.x = position.x;
    this->cannon_box.y = position.y;
    this->is_launched = true;
}
