#ifndef HMI_GRAPHICS_H
#define HMI_GRAPHICS_H

#include <iostream>
#include <X11/Xutil.h>
#include <X11/Xlib.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <map>
#include "Node.h"
#include "Color.h"
#include "Game.h"

extern "C" {
//#include <bcm_host.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <X11/Xatom.h>
#include <assert.h>
}
using namespace std;

#define NUM_VERTICES 128 // define the number of vertices in the circle
#define DEFAULT_RADIUS 0.5

#define check() assert(glGetError() == 0)

class Graphics {
private:
    // EGL handles
    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;

    // Screen size for glViewport
    EGLint screenHeight;
    EGLint screenWidth;

    // MVP matrix
    glm::mat4 projection;
    glm::mat4 view;
    glm::mat4 model;

    int _width = 800;
    int _height = 600;

    // shader and program handles
    GLuint program;

    // attribute and uniform locations
    GLuint aPosition;
    GLuint aProjection;
    GLuint aView;
    GLuint aModel;
    GLuint uColor;

    // raspi4 globals
    Display *_xDisplay;
    Window _xWindow;

    // node screen positions
    map<string, pair<float, float>> nodePositions;

    // Game instance
    Game game;

    //Mouse coordinates
    float mouse_posX;
    float mouse_posY;

    float spacingX = DEFAULT_RADIUS * 2 + 0.005;
    float spacingY = 0.875;

    float diffX = -3.5f * spacingX;
    float diffY = 6 * spacingY;

    float offsetY = 1;

    void showCompilerLog(GLint shader);
    void showLinkerLog(GLint prog);
    void resize();
    void createXWindow();
    void initOGL();
    void print_shader_info_log(GLuint shader);
    GLuint load_shader(GLenum type, const string &path);
    void initShaders();
    void initNodePositions();
    void setupViewport();
    void drawSquare(GLfloat squareData[]);
    void drawCircle(GLfloat centerX = 0.0, GLfloat centerY = 0.0, GLfloat radius = DEFAULT_RADIUS);
    void drawCircleByName(string name, Color color);

public:
    Graphics();

    void draw();
    void handleXEvents();
};


#endif //HMI_GRAPHICS_H
