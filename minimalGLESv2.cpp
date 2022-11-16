/* bare minimal OpenGLES2.0 triangle example in C++
 *
 * extracted from /opt/vc/src/triangle2
 * deliberately non-OO: choose your own architecture
 * deliberately no model view projection matrix
 *
 * Stefan Rapp (24.11.2019)
 */

#include <iostream>
#include <X11/Xlib.h>
#include <string.h>
extern "C" {
//#include <bcm_host.h>

#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <X11/Xatom.h>
#include <assert.h>
}

using namespace std;

// EGL handles
EGLDisplay display;
EGLSurface surface;
EGLContext context;

// Screen size for glViewport
EGLint screenHeight;
EGLint screenWidth;

int _width = 800;
int _height = 600;
// shader and program handles
GLuint vertexShader;
GLuint fragmentShader;
GLuint program;

// attribute and uniform locations
GLuint aVertex;
GLuint uColor;


//raspi4 globals
Display* _xDisplay;
Window _xWindow;

// a square as a simple triangle fan
// (it shows as a rectangle without a projection matrix ;) )
const GLfloat vertexData[] = {
     -0.5,-0.5,0.0,1.0,
     0.5,-0.5,0.0,1.0,
     0.5,0.5,0.0,1.0,
     -0.5,0.5,0.0,1.0
};

/*
 * some helper functions / macros
 */

#define check() assert(glGetError() == 0)

void showCompilerLog(GLint shader)
{
   char log[1024];
   glGetShaderInfoLog(shader, sizeof log, NULL, log);
   cout << "Shader (#" << shader << ") compilation:\n" << log << endl;
}

void showLinkerLog(GLint program)
{
   char log[1024];
   glGetProgramInfoLog(program, sizeof log, NULL, log);
   cout << "Shader (#" << program << ") linking:\n" << log << endl;
}

void resize()
{
        // Raspberry Pi 4: query window size from X11
        XWindowAttributes  gwa;
        XGetWindowAttributes ( _xDisplay , _xWindow , &gwa );
        _width = gwa.width;
        _height = gwa.height;
        glViewport(0, 0, _width, _height);

}


void handleXEvents()
{
   bool quit = false;
   // under Raspberry Pi 4 we can process keys from X11
   while ( XPending ( _xDisplay ) ) {   // check for events from the x-server
      XEvent  xev;
      XNextEvent( _xDisplay, &xev );
      switch(xev.type)
      {
      case KeyPress:
         switch(xev.xkey.keycode)
         {
            case  9://ESC
            case 24://Q
               exit(0);
               break;
         }
         break;
      case ButtonPress:
         switch (xev.xbutton.button)
         {
            case 4:// left mouse button or touch screen
               std::cout << "Up" << std::endl; 
               break;
            case 5:// left mouse button or touch screen
               std::cout << "Down" << std::endl; 
               break;
         }          
         break;
         case Expose:
         case PropertyNotify:
            resize();
            break;
      }
   } 
}

void createXWindow()
{

   _xDisplay = XOpenDisplay(NULL);
   if (NULL==_xDisplay)
   {
          throw runtime_error("could not connect to X server");
   }

   Window root = DefaultRootWindow(_xDisplay);

   XSetWindowAttributes windowAttributes;
   windowAttributes.event_mask = KeyPressMask | ButtonPressMask | Button1MotionMask | ExposureMask | PropertyChangeMask;

   _xWindow = XCreateWindow(_xDisplay, root,
                  0, 0, _width, _height,
                  0, CopyFromParent, InputOutput, CopyFromParent,
                  CWEventMask, &windowAttributes);

// the code below follows
// https://wiki.maemo.org/SimpleGL_example
// it may or may not be needed, depending on platform and window manager.

   // override window placement by the window manager
   windowAttributes.override_redirect = False;
   XChangeWindowAttributes ( _xDisplay, _xWindow, CWOverrideRedirect, &windowAttributes );

   // change to fullscreen on ubuntu
   Atom atom = XInternAtom ( _xDisplay, "_NET_WM_STATE_FULLSCREEN", True );
   XChangeProperty (
                  _xDisplay, _xWindow,
                  XInternAtom ( _xDisplay, "_NET_WM_STATE", True ),
                  XA_ATOM,  32,  PropModeReplace,
                  (unsigned char*) &atom,  1 );

   // set focus management
   XWMHints hints;
   hints.input = True;                        // get focus from wm without explicitly setting it
   hints.flags = InputHint;        // enable the input field above
   XSetWMHints(_xDisplay, _xWindow, &hints);

   // change window title
   XStoreName(_xDisplay,_xWindow,"h_da fbi Visual Hearing Aid");

   // map window -- causes it to be finally displayed
   XMapWindow(_xDisplay,_xWindow);

   // another means to communicate fullscreen to a window manager
   // also works on ubuntu
   Atom wm_state   = XInternAtom ( _xDisplay, "_NET_WM_STATE", False );
   Atom fullscreen = XInternAtom ( _xDisplay, "_NET_WM_STATE_FULLSCREEN", False );

   XEvent xev;
   memset ( &xev, 0, sizeof(xev) );

   xev.type                 = ClientMessage;
   xev.xclient.window       = _xWindow;
   xev.xclient.message_type = wm_state;
   xev.xclient.format       = 32;
   xev.xclient.data.l[0]    = 1;
   xev.xclient.data.l[1]    = fullscreen;
   XSendEvent (                // send an event mask to the X-server
                  _xDisplay,
                  DefaultRootWindow ( _xDisplay ),
                  False,
                  SubstructureNotifyMask,
                  &xev );
}


/*
 * initOGL()
 *
 * sets up an OpenGL ES2 surface and clears the screen to hda_darkblue
 */

static void initOGL()
{
   EGLBoolean result;
   EGLint num_config;

   static const EGLint attribute_list[] =
   {
      EGL_RED_SIZE, 8,
      EGL_GREEN_SIZE, 8,
      EGL_BLUE_SIZE, 8,
      EGL_ALPHA_SIZE, 8,
      EGL_NONE
   };

   static const EGLint context_attributes[] =
   {
      EGL_CONTEXT_CLIENT_VERSION, 2,
      EGL_NONE
   };
   EGLConfig config;


   // get an EGL display connection
   display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
   assert(display!=EGL_NO_DISPLAY);
   check();

   // initialize the EGL display connection
   result = eglInitialize(display, NULL, NULL);
   assert(EGL_FALSE != result);
   check();

   // get an appropriate EGL frame buffer configuration
   result = eglChooseConfig(display, attribute_list, &config, 1, &num_config);
   assert(EGL_FALSE != result);
   check();

   // get an appropriate EGL frame buffer configuration
   result = eglBindAPI(EGL_OPENGL_ES_API);
   assert(EGL_FALSE != result);
   check();

   // create an EGL rendering context
   context = eglCreateContext(display, config, EGL_NO_CONTEXT, context_attributes);
   assert(context!=EGL_NO_CONTEXT);
   check();
   
   createXWindow();
   // create an EGL window surface
   surface = eglCreateWindowSurface( display, config, _xWindow, NULL );
   assert(surface != EGL_NO_SURFACE);
   check();

   // connect the context to the surface
   result = eglMakeCurrent(display, surface, surface, context);
   assert(EGL_FALSE != result);
   check();

   // Set background color and clear buffers
   glClearColor(0.0627f, 0.1765f, 0.3608f, 1.0f); // some dark blue
   glClear( GL_COLOR_BUFFER_BIT );

   check();
}


static void initShaders()
{
   const GLchar *vertexShaderSource =
               "precision mediump float;"
               "attribute vec4 vertex;"
               "void main(void) {"
               " vec4 pos = vertex;"
               " gl_Position = pos;"
               "}";

   const GLchar *fragmentShaderSource =
               "precision mediump float;"
               "uniform vec4 color;"
               "void main(void) {"
               "  gl_FragColor = color;"
               "}";

   vertexShader = glCreateShader(GL_VERTEX_SHADER);
   glShaderSource(vertexShader, 1, &vertexShaderSource, 0);
   glCompileShader(vertexShader);
   check();

   showCompilerLog(vertexShader);


   fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
   glShaderSource(fragmentShader, 1, &fragmentShaderSource, 0);
   glCompileShader(fragmentShader);
   check();

   showCompilerLog(fragmentShader);


   program = glCreateProgram();
   glAttachShader(program, vertexShader);
   glAttachShader(program, fragmentShader);
   glLinkProgram(program);
   check();

   showLinkerLog(program);


   aVertex = glGetAttribLocation(program, "vertex");
   uColor  = glGetUniformLocation(program, "color");
}


void setupViewport()
{

/*
   // query size using a broadcom function, raspi only
   int32_t success = graphics_get_display_size(0, &screenWidth, &screenHeight);
   assert( success >= 0 );
   cout << "screen is " << screenWidth << "x" << screenHeight << endl;
*/

   // query surface size using EGL, more general
   eglQuerySurface(display, surface, EGL_WIDTH, &screenWidth);
   eglQuerySurface(display, surface, EGL_HEIGHT, &screenHeight);
   cout << "screen is " << screenWidth << "x" << screenHeight << endl;

   glViewport ( 0, 0, screenWidth, screenHeight );
   check();
}
void setupVertexData()
{
   glVertexAttribPointer(aVertex, 4, GL_FLOAT, GL_FALSE, 0, vertexData);
   glEnableVertexAttribArray(aVertex);
   check();
}


static void draw()
{
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        check();

   // could also be set just once
        // unless different ones are used
        glUseProgram ( program );
        check();

	// also color is unnecessarily set each time
        // consider to pass it as an attribute instead
        glUniform4f(uColor, 0.3176, 0.6118, 0.8588, 1.0); // some blue
	//glUniform4f(uColor, 0.4824, 0.6784, 0.1490, 1.0); // some green
        check();

	// actual drawing happens here
        glDrawArrays ( GL_TRIANGLE_FAN, 0, 4 );
        check();

        // finalize
        glFlush();
        glFinish();
        check();

	// swap buffers: show what we just painted
        eglSwapBuffers(display, surface);
        check();
}

//==============================================================================

int main ()
{
   // only raspberry pi needs this
   //bcm_host_init();


   initOGL();
   cout << "OpenGL ES2 initialized." << endl;

   initShaders();
   cout << "Shaders initialized." << endl;

   setupViewport();
   cout << "Viewport set up." << endl;

   setupVertexData();
   cout << "Vertex data set up." << endl;

   while (true)
   {
      //we usually run our own event loop in OpenGL ES2
      handleXEvents();
      draw();
      cout << "Triangles drawn." << endl;
   }
   return 0;
}
