#include "gift.h"
#include "main.h"

Gift::Gift(float x, float y,float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 1;
    gift_flag=0;
//    bounding_box_t gift_box;
    this->gift_box.x=this->position.x;
    this->gift_box.y=this->position.y;
    this->gift_box.z=this->position.z;
    this->gift_box.height=4;
    this->gift_box.width=4;
    this->gift_box.length=0.1;


    static GLfloat g_vertex_buffer_data[9000000];
      int n=8,top=0;
      for(int i=0;i<n;i++)
      {
          g_vertex_buffer_data[top++]=2.0*cos((2*3.1416/n)*i);
          g_vertex_buffer_data[top++]=2.0*sin((2*3.1416/n)*i);
          g_vertex_buffer_data[top++]=0;

          g_vertex_buffer_data[top++]=2.0*cos((2*3.1416/n)*(i+1));
          g_vertex_buffer_data[top++]=2.0*sin((2*3.1416/n)*(i+1));
          g_vertex_buffer_data[top++]=0;

          g_vertex_buffer_data[top++]=0;
          g_vertex_buffer_data[top++]=0;
          g_vertex_buffer_data[top++]=0;

      }


    this->object = create3DObject(GL_TRIANGLES, n*3, g_vertex_buffer_data, color, GL_FILL);
}

void Gift::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Gift::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Gift::tick() {
    //this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

/*
bounding_box_t Gifts::bounding_box() {
    float x = this->position.x, y = this->position.y, z = this->position.z;
    //float w = this->radius, h = this->radius;
    bounding_box_t bbox = { x, y, z, 0.1, 8, 7 };
    return bbox;
}
*/

