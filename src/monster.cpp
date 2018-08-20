#include "monster.h"
#include "main.h"

Monster::Monster(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 0.2;
    this->monster_box.width = 2.8;
    this->monster_box.height = 3.0;
    this->monster_box.length = 2.8;
    double rand1,rand2;
    rand2= rand()%2;
    rand1 = ((rand()%4)+1)*0.1;
    if(rand2>0)
        speed2=rand1;
    else
        speed2=-rand1;


    static const GLfloat vertex_buffer_data[] = {
            -1.4f, 1.4f, 1.4f,  //red face start
            -1.4f,-1.4f,1.4f,
            1.4f,1.4f,1.4f,
            1.4f,1.4f,1.4f,
            -1.4f,-1.4f,1.4f,
            1.4f,-1.4f,1.4f,       //red face end


            1.4f, -1.4f, 1.4f,
            1.4f,1.4f,-1.4f,
            1.4f,-1.4f,1.4f,
            1.4f,-1.4f,1.4f,
            1.4f,1.4f,-1.4f,
            1.4f,-1.4f,-1.4f,

            1.4f,1.4f,-1.4f,
            1.4f,-1.4f,-1.4f,
            -1.4f,-1.4f,-1.4f,
            -1.4f,-1.4f,-1.4f,
            1.4f,1.4f,-1.4f,
            -1.4f,1.4f,-1.4f,

            -1.4f,1.4f,-1.4f,
            -1.4f,-1.4f,-1.4f,
            -1.4f,1.4f,1.4f,
            -1.4f,-1.4f,-1.4f,
            -1.4f,1.4f,1.4f,
            -1.4f,-1.4f,1.4f,

            -1.4f,1.4f,1.4f,
            -1.4f,1.4f,-1.4f,
            1.4f,1.4f,1.4f,
            -1.4f,1.4f,-1.4f,
            1.4f,1.4f,1.4f,
            1.4f,1.4f,-1.4f,

            -1.4f,-1.4f,1.4f,
            -1.4f,-1.4f,-1.4f,
            1.4f,-1.4f,1.4f,
            -1.4f,-1.4f,-1.4f,
            1.4f,-1.4f,1.4f,
            1.4f,-1.4f,-1.4f,

            0.0f, 5.0f, 0.0f,
            -1.4f, 1.4f, -1.4f,
            1.4f, 1.4f, -1.4f,

            0.0f, 5.0f, 0.0f,
            1.4f, 1.4f, 1.4f,
            1.4f, 1.4f, -1.4f,

            0.0f, 5.0f, 0.0f,
            -1.4f, 1.4f, 1.4f,
            1.4f, 1.4f, 1.4f,

            0.0f, 5.0f, 0.0f,
            -1.4f, 1.4f, 1.4f,
            -1.4f, 1.4f, -1.4f,

            //eyes start
            0.4f, 0.6f, 1.4f,
            1.2f, 1.0f, 1.4f,
            0.8f, 0.0f, 1.4f,

            -0.4f, 0.6f, 1.4f,
            -1.2f, 1.0f, 1.4f,
            -0.8f, 0.0f, 1.4f,
            //eyes end

            //smile_start
            0.8f, -0.3f, 1.4f,
            0.0f, -0.6f, 1.4f,
            0.0f, -1.1f, 1.4f,

            -0.8f, -0.3f, 1.4f,
            0.0f, -0.6f, 1.4f,
            0.0f, -1.1f, 1.4f
            //smile_end

        };

    this->object1 = create3DObject(GL_TRIANGLES, 48, vertex_buffer_data, color, GL_FILL);
       this->object2 = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data + 144, COLOR_BLACK, GL_FILL);


   // this->object = create3DObject(GL_TRIANGLES, n*3, g_vertex_buffer_data, color, GL_FILL);
}

void Monster::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
}

void Monster::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Monster::tick() {
    //this->rotation += speed;

    this->monster_box.x = this->position.x;
    this->monster_box.y = this->position.y;
    this->monster_box.z = this->position.z;

    this->position.z -= speed;
    this->position.x -= speed2;
    // this->position.y -= speed;
}


