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
#include <glm/gtx/intersect.hpp>
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

#define FOV_Y 45.0f
#define LOOKAT_Z 17.5

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
    float mouse_posX = 0;
    float mouse_posY = 0;

    glm::vec3 intersectionPoint = glm::vec3(0);
    glm::vec3 newPoint = glm::vec3(0);
    glm::vec3 startingPoint = glm::vec3(0.0f,-5.5625f,1.0f);
    glm::vec3 endPoint = glm::vec3(1);

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
    void drawLine();
    void calculateNewPosition();
    glm::vec3 crossProduct(glm::vec3 vec1, glm::vec3 vec2);
    glm::vec3 intersectLine(glm::vec3 borderBottom, glm::vec3 borderTop, glm::vec3 shootStart, glm::vec3 shootEnd);
    glm::vec3 get_line_intersection(glm::vec3 bottomBorder, glm::vec3 topBorder, glm::vec3 lineStart, glm::vec3 lineEnd);
    pair<float, float> screenToWorld(int screenPosX, int screenPosY);

public:
    Graphics();

    void draw();
    void handleXEvents();
};


#endif //HMI_GRAPHICS_H
