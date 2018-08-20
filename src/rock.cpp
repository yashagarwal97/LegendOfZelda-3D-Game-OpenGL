#include "rock.h"
#include "main.h"

Rock::Rock(float x, float y,float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 1;
    this->rock_box.x=this->position.x;
    this->rock_box.y=this->position.y;
    this->rock_box.z=this->position.z;
    this->rock_box.height=2;
    this->rock_box.width=2;
    this->rock_box.length=2;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -1.0f,-1.0f,-1.0f, // triangle 1 : begin
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // triangle 1 : end

        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,

        1.0f,-1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,

        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,

        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,

        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,

        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,

        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,

        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,

        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,

        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,

        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f
    };

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
}

void Rock::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Rock::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Rock::tick() {
    //this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

