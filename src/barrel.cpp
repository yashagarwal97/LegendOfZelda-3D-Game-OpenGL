#include "barrel.h"
#include "main.h"

Barrel::Barrel(float x, float y, color_t color) {
    this->position = glm::vec3(x, 0, y);
    this->rotation = 0;
    speed = 1;

    static const GLfloat vertex_buffer_data[] = {
        0.0f,1.2f,0.0f, // triangle 1 : begin
        1.2f,0.0f, 0.0f,
        -0.8f, 0.0f, -0.8f, // triangle 1 : end

        0.0f, 1.2f,0.0f, // triangle 2 : begin
        1.2f,0.0f,0.0f,
        -0.8f, 0.0f,0.8f, // triangle 2 : end

        -0.8f, 0.0f,0.8f, // triangle 3 : begin
        -0.8f,0.0f,-0.8f,
        0.0f, 1.2f,0.0f, // triangle 3 : end

    };

    this->object = create3DObject(GL_TRIANGLES, 3*3, vertex_buffer_data, color, GL_FILL);
}

void Barrel::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Barrel::set_position(float x, float y) {
    this->position = glm::vec3(x, 0, y);
}

void Barrel::tick() {
    //this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}
