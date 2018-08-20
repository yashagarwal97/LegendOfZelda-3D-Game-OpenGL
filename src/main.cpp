#include "main.h"
#include "timer.h"
#include "ball.h"
#include "barrel.h"
#include "boat.h"
#include "rock.h"
#include "sea.h"
#include "gift.h"
#include "cannonball.h"
#include "monster.h"
#include<string.h>
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball1;
Boat boat1;
Sea sea1;
Rock rock[1000];
Monster monster[1000];
Cannonball cannonball;
Barrel barrel[500];
Gift gift[500];

int wind_frame=0;
int wind_flag=0;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 90;
float tar1,tar2,tar3;
float eye1,eye2,eye3;
int health=100,points=0;
int cannon_flag=0;

bool set_tower_view = false;
int view=0;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
//    glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 4, 5*sin(camera_rotation_angle*M_PI/180.0f) );
//     glm::vec3 eye (boat1.position.x-5*cos(camera_rotation_angle*M_PI/180.0f) ,5, boat1.position.z-5*sin(camera_rotation_angle*M_PI/180.0f));
     glm::vec3 eye (eye1,eye2,eye3);
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
//    glm::vec3 target (0, 0, 0);
//     glm::vec3 target (boat1.position.x ,0, boat1.position.z);
     glm::vec3 target (tar1,tar2,tar3);

    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    sea1.draw(VP);
    boat1.draw(VP);

    for(int i=0;i<300;i++)
    {
        barrel[i].draw(VP);
        gift[i].draw(VP);
    }
    for(int i=0;i<300;i++)
    {
        rock[i].draw(VP);
    }
    for(int i=0;i<400;i++)
    {
        monster[i].draw(VP);
    }
    if(cannon_flag==1)
    cannonball.draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up  = glfwGetKey(window, GLFW_KEY_UP);
    int down  = glfwGetKey(window, GLFW_KEY_DOWN);
    int spacebar  = glfwGetKey(window, GLFW_KEY_SPACE);
    int fire  = glfwGetKey(window, GLFW_KEY_F);
    if(fire)
    {
        cannon_flag=1;
    }
    if(spacebar)
    {
        boat1.speed2=0.4;
        boat1.accel=-0.06;
        boat1.tick();
    }
    if (left) {
        // Do something
        //boat1.position.z+=0.5;
        boat1.rotation+=0.5;
        cannonball.rotation += 0.5;
        camera_rotation_angle-=0.5;
    }
    if (right) {
        // Do something
        //boat1.position.z-=0.5;
        boat1.rotation-=0.5;
        cannonball.rotation -= 0.5;
        camera_rotation_angle+=0.5;
    }
    if (up) {
        // Do something
        boat1.position.z+=0.5*cos(boat1.rotation*M_PI/180.0f);
        boat1.position.x+=0.5*sin(boat1.rotation*M_PI/180.0f);

        cannonball.position.z+=0.5*cos(boat1.rotation*M_PI/180.0f);
        cannonball.position.x+=0.5*sin(boat1.rotation*M_PI/180.0f);
    }
    if (down) {
        // Do something
        boat1.position.z-=0.5*cos(boat1.rotation*M_PI/180.0f);
        boat1.position.x-=0.5*sin(boat1.rotation*M_PI/180.0f);

        cannonball.position.z-=0.5*cos(boat1.rotation*M_PI/180.0f);
        cannonball.position.x-=0.5*sin(boat1.rotation*M_PI/180.0f);
    }
}

void tick_elements() {
    boat1.tick();


    if(wind_frame>=600 && wind_frame<=800)
       {
           wind_flag=1;

           //magnet[0].draw(VP);
           //magnet[1].draw(VP);
       }
    else if(wind_frame>800 && wind_frame<=1400)
    {
        wind_flag=0;
    }
    else if(wind_frame>1400 && wind_frame<=1600)
    {
        wind_flag=2;
    }
    else if(wind_frame>1600)
       {
           wind_flag=0;
           wind_frame=-600;
       }
    if(wind_flag==1)
    {
        boat1.rotation+=0.05;
//        printf("flag1 = %lf\n",boat1.rotation);
    }
    else if(wind_flag==2)
    {
        boat1.rotation-=0.1;
//        printf("flag2 = %lf\n",boat1.rotation);
    }


    if(cannon_flag)
    {
        if(abs(boat1.position.x - cannonball.position.x)>=25 ||
                abs(boat1.position.z - cannonball.position.z)>=25)
        {
            cannon_flag=0;
            cannonball.position.x = boat1.position.x;
            cannonball.position.z = boat1.position.z;
        }

        cannonball.position.z+=1.5*cos(boat1.rotation*M_PI/180.0f);
        cannonball.position.x+=1.5*sin(boat1.rotation*M_PI/180.0f);

        cannonball.fire();
    }
    //int gift_flag=0;
    for(int i=0;i<400;i++)
    {
        monster[i].tick();
        if(detect_collision(cannonball.cannon_box,monster[i].monster_box))
        {
            monster[i].position.x=50000;
            points+=25;
        }

        if(detect_collision(boat1.boat_box,monster[i].monster_box))
        {
            health-=10;
            monster[i].position.x=50000;
        }
    }

    for(int i=0;i<300;i++)
    {
        if(detect_collision(gift[i].gift_box,boat1.boat_box) && gift[i].gift_flag==0)
        {
            gift[i].gift_flag=1;
            points+=10;
            gift[i].position.y=1000;
        }
    }

    for(int i=0;i<300;i++)
    {
        if(detect_collision(rock[i].rock_box,boat1.boat_box))
        {
            boat1.position.x-=0.5;
           // printf("\n\n\nhahahaah\n\n\n");
            boat1.position.z-=0.5;
            health-=5;
        }
    }
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    int rand1,rand2;
    ball1 = Ball(0, 0, COLOR_RED);
    boat1 = Boat(0, 0, 0, COLOR_VIOLET);
    sea1 = Sea(0, 0, COLOR_BLACK);
    cannonball = Cannonball(boat1.position.x,boat1.position.y,boat1.position.z);

    for(int i=0;i<300;i++)
    {
        rand1=rand()%1000-500;
        rand2=rand()%1000-500;
        barrel[i] = Barrel(rand1,rand2,COLOR_YELLOW);
        gift[i] = Gift(rand1,10.0,rand2,COLOR_RED);
    }

    for(int i=0;i<300;i++)
    {
        rand1=rand()%1000-500;
        rand2=rand()%1000-500;
        rock[i] = Rock(rand1,0,rand2,COLOR_BROWN);
    }
    for(int i=0;i<400;i++)
    {
        rand1=rand()%1000-500;
        rand2=rand()%1000-500;
        monster[i] = Monster(rand1,0,rand2,COLOR_ORANGE);
    }
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            wind_frame++;
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            char s1[30],s2[30],s3[30];
                       char output[300]="";
                         sprintf(s1,"%d",health);
                         sprintf(s2,"%d",points);
                        // sprintf(s3,"%d",ball[1].level);
                         strcat(output,"Health: ");
                         strcat(output,s1);
                         strcat(output,"   Score: ");
                         strcat(output,s2);
                        // strcat(output,"   Level: ");
                        // strcat(output,s3);
           glfwSetWindowTitle(window,output);
           if(health<=0)
               quit(window);

            tick_elements();
            tick_input(window);
            apply_view();
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

void viewchange()
{
    view++;
    if(view==5)
        view=0;
}

void apply_view()
{

    switch(view)
    {
    //follow-cam view
    case 0:
        eye1 = boat1.position.x-5*cos(camera_rotation_angle*M_PI/180.0f);
        eye2 = 5;
        eye3 = boat1.position.z-5*sin(camera_rotation_angle*M_PI/180.0f);
        // glm::vec3 eye (boat1.position.x-5*cos(camera_rotation_angle*M_PI/180.0f) ,5, boat1.position.z-5*sin(camera_rotation_angle*M_PI/180.0f));
        // glm::vec3 target (boat1.position.x ,0, boat1.position.z);
         tar1 = boat1.position.x+cos(camera_rotation_angle*M_PI/180.0f);
         tar2 = 5;
         tar3 = boat1.position.z+sin(camera_rotation_angle*M_PI/180.0f);
         set_tower_view =  false;
        break;
    // top view
    case 1:
        eye1 = boat1.position.x;
        eye2 = 15;
        eye3 = boat1.position.z;
        tar1 = 1+boat1.position.x;
        tar2 = boat1.position.y;
        tar3 = boat1.position.z;
        set_tower_view =  false;
        break;
    // tower view
    case 2:
        if(!set_tower_view){
            set_tower_view = true;
            eye1 = 10+boat1.position.x;
            eye2 = 10;
            eye3 = boat1.position.z;

        }

        tar1 = boat1.position.x;
        tar2 = boat1.position.y;
        tar3 = boat1.position.z;
        break;
    // boat view
    case 3:
        set_tower_view = false;
        eye1 = boat1.position.x-1*cos(camera_rotation_angle*M_PI/180.0f);
        eye2 = 2;
        eye3 = boat1.position.z-1*sin(camera_rotation_angle*M_PI/180.0f);
        // glm::vec3 eye (boat1.position.x-5*cos(camera_rotation_angle*M_PI/180.0f) ,5, boat1.position.z-5*sin(camera_rotation_angle*M_PI/180.0f));
        // glm::vec3 target (boat1.position.x ,0, boat1.position.z);
         tar1 = boat1.position.x;
         tar2 = 2;
         tar3 = boat1.position.z;
        break;
   // helicopter view
   case 4:
        eye2=30;
        break;
    default:
        eye1 = boat1.position.x-5*cos(camera_rotation_angle*M_PI/180.0f);
        eye2 = 5;
        eye3 = boat1.position.z-5*sin(camera_rotation_angle*M_PI/180.0f);
        // glm::vec3 eye (boat1.position.x-5*cos(camera_rotation_angle*M_PI/180.0f) ,5, boat1.position.z-5*sin(camera_rotation_angle*M_PI/180.0f));
        // glm::vec3 target (boat1.position.x ,0, boat1.position.z);
         tar1 = boat1.position.x;
         tar2 = 0;
         tar3 = boat1.position.z;
        break;
    }
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height) &&
            abs(a.z - b.z) * 2 < (a.length + b.length));
}



void zoom_camera(int type){
    float l,m,n;
    if(view==4)
    {
         l = tar1-eye1;
         m = tar2-eye2;
         n = tar3-eye3;
         if(type==-1)
         {
             eye3=eye3+10;
         }
         else if(type==1)
        {
            if(eye3>tar3+10)
            {
                eye3=eye3-10;
            }
        }
         eye2 = m*(eye3-tar3)/n+tar2;
        eye1 = l*(eye3-tar3)/n+tar1;
    }
}

//    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);

void heli_camera(float x, float y){
    if(view==4)
    {
        tar1 = x-300 + boat1.position.x;
        if(y<=300)
        {
            tar2 = (300-y)/2 + (boat1.position.y);
        }
    }
}
