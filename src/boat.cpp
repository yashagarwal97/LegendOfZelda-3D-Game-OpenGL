#include "boat.h"
#include "main.h"

Boat::Boat(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 1;
    this->boat_box.height=1;
    this->boat_box.width=2;
    this->boat_box.length=4;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data1[] = {
        -1.0f,1.0f,-1.0f, // triangle 1 : begin
        -1.0f,1.0f, 1.0f,
        -1.0f, 0.0f, -1.0f, // triangle 1 : end
        -1.0f,0.0f,1.0f, // triangle 1 : begin
        -1.0f,1.0f, 1.0f,
        -1.0f, 0.0f, -1.0f, // triangle 1 : end

        1.0f,0.0f,1.0f, // triangle 1 : begin
        1.0f,1.0f, 1.0f,
        0.0f, 0.0f, 2.0f, // triangle 1 : end
        0.0f,1.0f,2.0f, // triangle 1 : begin
        1.0f,1.0f, 1.0f,
        0.0f, 0.0f, 2.0f, // triangle 1 : end

        0.0f,0.0f,-2.0f, // triangle 1 : begin
        0.0f,1.0f, -2.0f,
        1.0f, 0.0f, -1.0f, // triangle 1 : end
        1.0f,1.0f,-1.0f, // triangle 1 : begin
         0.0f,1.0f, -2.0f,
        1.0f, 0.0f, -1.0f, // triangle 1 : end


        -1.0f,0.0f,1.0f, // triangle 1 : begin
        -1.0f,1.0f, 1.0f,
        0.0f, 0.0f, 2.0f, // triangle 1 : end
        0.0f,1.0f,2.0f, // triangle 1 : begin
        -1.0f,1.0f, 1.0f,
        0.0f, 0.0f, 2.0f, // triangle 1 : end

        1.0f,1.0f,-1.0f, // triangle 1 : begin
        1.0f,1.0f, 1.0f,
        1.0f, 0.0f, -1.0f, // triangle 1 : end
        1.0f,0.0f,1.0f, // triangle 1 : begin
        1.0f,1.0f, 1.0f,
        1.0f, 0.0f, -1.0f, // triangle 1 : end


        0.0f,0.0f,-2.0f, // triangle 1 : begin
        0.0f,1.0f, -2.0f,
        -1.0f, 0.0f, -1.0f, // triangle 1 : end
        -1.0f,1.0f,-1.0f, // triangle 1 : begin
        0.0f,1.0f, -2.0f,
        -1.0f, 0.0f, -1.0f, // triangle 1 : end



    };
    static const GLfloat vertex_buffer_data2[] = {
         0.0f,0.0f,0.0f, // triangle 1 : begin
         0.0f,5.0f, 0.0f,
        1.0f, 2.5f, 1.0f, // triangle 1 : end
   };

    static const GLfloat vertex_buffer_data3[] = {
        -1.0f,0.0f,1.0f, // triangle 1 : begin
        1.0f,0.0f, 1.0f,
        0.0f, 0.0f, 2.0f, // triangle 1 : end
        -1.0f,0.0f,-1.0f, // triangle 1 : begin
        1.0f,0.0f, 1.0f,
        -1.0f, 0.0f, 1.0f, // triangle 1 : end

         0.0f,0.0f,-2.0f, // triangle 1 : begin
         1.0f,0.0f, -1.0f,
        -1.0f, 0.0f, -1.0f, // triangle 1 : end
        1.0f,0.0f,-1.0f, // triangle 1 : begin
        1.0f,0.0f, 1.0f,
        -1.0f, 0.0f, -1.0f, // triangle 1 : end

    };

    this->object[0] = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data1, color, GL_FILL);
    this->object[1] = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data3, COLOR_ORANGE, GL_FILL);
    this->object[2] = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data2, COLOR_YELLOW, GL_FILL);
}

void Boat::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[0]);
    draw3DObject(this->object[1]);
    draw3DObject(this->object[2]);
}

void Boat::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Boat::tick() {
    this->boat_box.x=this->position.x;
    this->boat_box.y=this->position.y;
    this->boat_box.z=this->position.z;
    speed2 = speed2 + accel;
    //this->rotation += speed;
    // this->position.x -= speed;
    this->position.y += speed2;
    if(this->position.y<0)
    {
        this->position.y=0;
        this->accel=0;
        this->speed2=0;
    }

}




