
#include <GL/glut.h>
#include <math.h>

#include "../helpers.h"
#include "../shaderutils.h"
#include "water.h"
#include "black.h"
#include "tunnel.h"
#include "screen.h"
#include "space.h"

// import -window root filnamn.jpg där d finns imagemagick
// screencapture -S filnamn.jpg på mac

#define LOAD 0
#define INIT 1
#define DISP 2

#define SCENES 5

#define WATER 0
#define BLACK 1
#define TUNNEL 3
#define SCREEN 4
#define SPACE 2

#define START_SCENE TUNNEL

struct _SceneStruct {
 void (*init)();
 void (*load)();
 void (*disp)();
 void (*opts)(int, int);
 int time;
};

struct _SceneStruct scenes [SCENES];

int millis_on_scene = 0;
int curr_scene = WATER;
int w_height = 800;
int w_width = 800;

void display()
{
  // This function is called whenever it is time to render
  // a new frame; due to the idle()-function below, this
  // function will get called several times per second
  /*
  // Clear framebuffer & zbuffer
  glClearColor(0.3, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Set current material  
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuseColor);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specularColor);
  

  // Place camera and light
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(100,50,50, 0, 0, 0, 0, 1, 0); // No manual control but better place from the start
  glLoadMatrixd(getCameraMatrix());
  glLightfv(GL_LIGHT0, GL_POSITION, light_position); // After camera matrix - camera independent!
*/
  scenes[curr_scene].disp();
  // Render the scene!
  
  // Swap front- and backbuffers
  glutSwapBuffers();
}

void init(int scene)
{
  glPushAttrib(GL_ALL_ATTRIB_BITS);
  scenes[scene].init();
}

void timer(int i)
{
  glutTimerFunc(20, timer, i);
  millis_on_scene += 20;
  //printf (" %d, %d : %d \n", curr_scene, millis_on_scene, scenes[curr_scene].time);
  if (millis_on_scene >= scenes[curr_scene].time) {
    millis_on_scene = 0;
    curr_scene++;
    glPopAttrib();
    init(curr_scene);
    if (curr_scene >= SCENES) {
      exit(0);
    }
  }
  glutPostRedisplay();
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);

  // Configure GLUT:
  //  - framebuffer with RGB + Alpha values per pixel
  //  - Z-buffer
  //  - two sets of above mentioned buffers, so that
  //    doublebuffering is possible
  //
  // Initial window size 800x800
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
  glutInitWindowSize(w_width, w_height);
  glutCreateWindow("Lab 4");

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(90, 1, 0.01, 1000);
  glMatrixMode(GL_MODELVIEW);
  
  initHelperLibrary();
  scenes[WATER].init = water_init;
  scenes[WATER].load = water_load;
  scenes[WATER].disp = water_disp;
  scenes[WATER].time = 5000;

  scenes[BLACK].init = black_init;
  scenes[BLACK].load = black_load;
  scenes[BLACK].disp = black_disp;
  scenes[BLACK].time = 10000;

  scenes[TUNNEL].init = tunnel_init;
  scenes[TUNNEL].load = tunnel_load;
  scenes[TUNNEL].disp = tunnel_disp;
  scenes[TUNNEL].time = 20000;

  scenes[SCREEN].init = screen_init;
  scenes[SCREEN].load = screen_load;
  scenes[SCREEN].disp = screen_disp;
  scenes[SCREEN].time = 120000;
 
  screen_opts(w_width, w_height);

  scenes[SPACE].init = space_init;
  scenes[SPACE].load = space_load;
  scenes[SPACE].disp = space_disp;
  scenes[SPACE].time = 41000;

  curr_scene = START_SCENE;
  int i;
  for (i = 0; i < SCENES; i++) {
    scenes[i].load();
  }

  init(START_SCENE);

  // Register our display- and idle-functions with GLUT
  glutDisplayFunc(display);
  glutTimerFunc(20, timer, 0);

  // Enter GLUT's main loop; this function will never return
  glutMainLoop();

  return 0;
}
