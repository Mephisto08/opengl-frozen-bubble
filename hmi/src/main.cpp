#include  <iostream>
#include  <cstdlib>
#include  <cstring>
using namespace std;

#include  <cmath>
#include  <sys/time.h>

#include  <X11/Xlib.h>
#include  <X11/Xatom.h>
#include  <X11/Xutil.h>

#include  <GLES2/gl2.h>
#include  <EGL/egl.h>
#include <fstream>
#include <sstream>

//#include "../framework/libheaders.h"
#include "../framework/OBJLoader.h"
#include "SceneElements/Renderable.h"

//  some more formulas to play with...
//      cos( 20.*(pos.x*pos.x + pos.y*pos.y) - phase );
//      cos( 20.*sqrt(pos.x*pos.x + pos.y*pos.y) + atan(pos.y,pos.x) - phase );
//      cos( 30.*sqrt(pos.x*pos.x + 1.5*pos.y*pos.y - 1.8*pos.x*pos.y*pos.y)
//            + atan(pos.y,pos.x) - phase );


void
print_shader_info_log (
   GLuint  shader      // handle to the shader
)
{
   GLint  length;

   glGetShaderiv ( shader , GL_INFO_LOG_LENGTH , &length );

   if ( length ) {
      char* buffer  =  new char [ length ];
      glGetShaderInfoLog ( shader , length , NULL , buffer );
      cout << "shader info: " <<  buffer << flush;
      delete [] buffer;

      GLint success;
      glGetShaderiv( shader, GL_COMPILE_STATUS, &success );
      if ( success != GL_TRUE )   exit ( 1 );
   }
}


GLuint
load_shader (
   
   GLenum       type,
   const std::string & path
)
{
   std::string Code;
	std::ifstream ShaderFile;
   //glm::vec3 test;

	ShaderFile.exceptions(std::ifstream::badbit);
	try
	{
		ShaderFile.open(path);
		if (!ShaderFile.is_open())
			throw std::invalid_argument("Vertex shader file not found.");
		
		std::stringstream ShaderStream;
		ShaderStream << ShaderFile.rdbuf();

		ShaderFile.close();

	    Code = ShaderStream.str();
	}
    catch (const std::exception& ex)
	{
		std::string errmsg;
		errmsg.append("Error: Shader files couldn't be read:\n");
		errmsg.append(ex.what());
		throw std::logic_error(errmsg.c_str());
	}
   const GLchar* ShaderCode = Code.c_str();
   GLuint  shader = glCreateShader( type );

   glShaderSource  ( shader , 1 , &ShaderCode, NULL );
   glCompileShader ( shader );

   print_shader_info_log ( shader );

   return shader;
}



Display    *x_display;
Window      win;
EGLDisplay  egl_display;
EGLContext  egl_context;
EGLSurface  egl_surface;

GLfloat
   norm_x    =  0.0,
   norm_y    =  0.0,
   offset_x  =  0.0,
   offset_y  =  0.0,
   p1_pos_x  =  0.0,
   p1_pos_y  =  0.0;

GLint
   phase_loc,
   offset_loc,
   position_loc;


bool        update_pos = false;

const float vertexArray[] = {
   0.0,  0.5,  0.0,
  -0.5,  0.0,  0.0,
   0.0, -0.5,  0.0,
   0.5,  0.0,  0.0,
   0.0,  0.5,  0.0 
}; 


void  render()
{
   static float  phase = 0;
   static int    donesetup = 0;

   static XWindowAttributes gwa;

   //// draw

   if ( !donesetup ) {
      XWindowAttributes  gwa;
      XGetWindowAttributes ( x_display , win , &gwa );
      glViewport ( 0 , 0 , gwa.width , gwa.height );
      glClearColor ( 0.08 , 0.06 , 0.07 , 1.);    // background color
      donesetup = 1;
   }
   glClear ( GL_COLOR_BUFFER_BIT );

   glUniform1f ( phase_loc , phase );  // write the value of phase to the shaders phase
   phase  =  fmodf ( phase + 0.5f , 2.f * 3.141f );    // and update the local variable

   if ( update_pos ) {  // if the position of the texture has changed due to user action
      GLfloat old_offset_x  =  offset_x;
      GLfloat old_offset_y  =  offset_y;

      offset_x  =  norm_x - p1_pos_x;
      offset_y  =  norm_y - p1_pos_y;

      p1_pos_x  =  norm_x;
      p1_pos_y  =  norm_y;

      offset_x  +=  old_offset_x;
      offset_y  +=  old_offset_y;

      update_pos = false;
   }

   glUniform4f ( offset_loc  ,  offset_x , offset_y , 0.0 , 0.0 );

   glVertexAttribPointer ( position_loc, 3, GL_FLOAT, false, 0, vertexArray );
   glEnableVertexAttribArray ( position_loc );
   glDrawArrays ( GL_TRIANGLE_STRIP, 0, 5 );

   eglSwapBuffers ( egl_display, egl_surface );  // get the rendered buffer to the screen
}

Renderable* groundRenderable = nullptr;

void initscene(){
    //Load shader
    //m_assets.addShaderProgram("shader", AssetManager::createShaderProgram("assets/shaders/vertex.glsl",
    //                                                                      "assets/shaders/fragment.glsl"));
    //m_shader = m_assets.getShaderProgram("shader");
   //std::cout << "test" << std::endl;
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    try {
        bool calcnormals = false;
        bool calctangents = false;

        OBJResult sphereResult = OBJLoader::loadOBJ("/home/osboxes/Desktop/hmi/assets/sphere.obj", calcnormals, calctangents);
        std::vector<OBJMesh> sphereMeshes = sphereResult.objects.at(0).meshes;

        groundRenderable = new Renderable(sphereMeshes);
      }
      catch (std::exception &ex) {
        throw std::logic_error("Scene initialization failed:\n" + std::string(ex.what()) + "\n");
    }
}

void renderNew() {
   static float  phase = 0;
   static int    donesetup = 0;

   static XWindowAttributes gwa;

   //// draw

   if ( !donesetup ) {
      XWindowAttributes  gwa;
      XGetWindowAttributes ( x_display , win , &gwa );
      glViewport ( 0 , 0 , gwa.width , gwa.height );
      glClearColor ( 0.08 , 0.06 , 0.07 , 1.);    // background color
      donesetup = 1;
   }
   glClear ( GL_COLOR_BUFFER_BIT );

   if ( update_pos ) {  // if the position of the texture has changed due to user action
      GLfloat old_offset_x  =  offset_x;
      GLfloat old_offset_y  =  offset_y;

      offset_x  =  norm_x - p1_pos_x;
      offset_y  =  norm_y - p1_pos_y;

      p1_pos_x  =  norm_x;
      p1_pos_y  =  norm_y;

      offset_x  +=  old_offset_x;
      offset_y  +=  old_offset_y;

      update_pos = false;
   }

   glUniform4f ( offset_loc  ,  offset_x , offset_y , 0.0 , 0.0 );

   groundRenderable->render();

   eglSwapBuffers ( egl_display, egl_surface );  // get the rendered buffer to the screen
}



////////////////////////////////////////////////////////////////////////////////////////////


int  main()
{
   ///////  the X11 part  //////////////////////////////////////////////////////////////////
   // in the first part the program opens a connection to the X11 window manager
   //

   x_display = XOpenDisplay ( NULL );   // open the standard display (the primary screen)
   if ( x_display == NULL ) {
      cerr << "cannot connect to X server" << endl;
      return 1;
   }

   Window root  =  DefaultRootWindow( x_display );   // get the root window (usually the whole screen)

   XSetWindowAttributes  swa;
   swa.event_mask  =  ExposureMask | PointerMotionMask | KeyPressMask;

   win  =  XCreateWindow (   // create a window with the provided parameters
              x_display, root,
              0, 0, 800, 480,   0,
              CopyFromParent, InputOutput,
              CopyFromParent, CWEventMask,
              &swa );

   XSetWindowAttributes  xattr;
   Atom  atom;
   int   one = 1;

   xattr.override_redirect = False;
   XChangeWindowAttributes ( x_display, win, CWOverrideRedirect, &xattr );

   atom = XInternAtom ( x_display, "_NET_WM_STATE_FULLSCREEN", True );
   XChangeProperty (
      x_display, win,
      XInternAtom ( x_display, "_NET_WM_STATE", True ),
      XA_ATOM,  32,  PropModeReplace,
      (unsigned char*) &atom,  1 );

   XChangeProperty (
      x_display, win,
      XInternAtom ( x_display, "_HILDON_NON_COMPOSITED_WINDOW", False ),
      XA_INTEGER,  32,  PropModeReplace,
      (unsigned char*) &one,  1);

   XWMHints hints;
   hints.input = True;
   hints.flags = InputHint;
   XSetWMHints(x_display, win, &hints);

   XMapWindow ( x_display , win );             // make the window visible on the screen
   XStoreName ( x_display , win , "GL test" ); // give the window a name

   //// get identifiers for the provided atom name strings
   Atom wm_state   = XInternAtom ( x_display, "_NET_WM_STATE", False );
   Atom fullscreen = XInternAtom ( x_display, "_NET_WM_STATE_FULLSCREEN", False );

   XEvent xev;
   memset ( &xev, 0, sizeof(xev) );

   xev.type                 = ClientMessage;
   xev.xclient.window       = win;
   xev.xclient.message_type = wm_state;
   xev.xclient.format       = 32;
   xev.xclient.data.l[0]    = 1;
   xev.xclient.data.l[1]    = fullscreen;
   XSendEvent (                // send an event mask to the X-server
      x_display,
      DefaultRootWindow ( x_display ),
      False,
      SubstructureNotifyMask,
      &xev );


   ///////  the egl part  //////////////////////////////////////////////////////////////////
   //  egl provides an interface to connect the graphics related functionality of openGL ES
   //  with the windowing interface and functionality of the native operation system (X11
   //  in our case.

   egl_display  =  eglGetDisplay( (EGLNativeDisplayType) x_display );
   if ( egl_display == EGL_NO_DISPLAY ) {
      cerr << "Got no EGL display." << endl;
      return 1;
   }

   if ( !eglInitialize( egl_display, NULL, NULL ) ) {
      cerr << "Unable to initialize EGL" << endl;
      return 1;
   }

   EGLint attr[] = {       // some attributes to set up our egl-interface
      EGL_BUFFER_SIZE, 16,
      EGL_RENDERABLE_TYPE,
      EGL_OPENGL_ES2_BIT,
      EGL_NONE
   };

   EGLConfig  ecfg;
   EGLint     num_config;
   if ( !eglChooseConfig( egl_display, attr, &ecfg, 1, &num_config ) ) {
      cerr << "Failed to choose config (eglError: " << eglGetError() << ")" << endl;
      return 1;
   }

   if ( num_config != 1 ) {
      cerr << "Didn't get exactly one config, but " << num_config << endl;
      return 1;
   }

   egl_surface = eglCreateWindowSurface ( egl_display, ecfg, win, NULL );
   if ( egl_surface == EGL_NO_SURFACE ) {
      cerr << "Unable to create EGL surface (eglError: " << eglGetError() << ")" << endl;
      return 1;
   }

   //// egl-contexts collect all state descriptions needed required for operation
   EGLint ctxattr[] = {
      EGL_CONTEXT_CLIENT_VERSION, 2,
      EGL_NONE
   };
   egl_context = eglCreateContext ( egl_display, ecfg, EGL_NO_CONTEXT, ctxattr );
   if ( egl_context == EGL_NO_CONTEXT ) {
      cerr << "Unable to create EGL context (eglError: " << eglGetError() << ")" << endl;
      return 1;
   }

   //// associate the egl-context with the egl-surface
   eglMakeCurrent( egl_display, egl_surface, egl_surface, egl_context );


   ///////  the openGL part  ///////////////////////////////////////////////////////////////

   GLuint vertexShader   = load_shader (  GL_VERTEX_SHADER,"shaders/vertex.glsl" );     // load vertex shader
   GLuint fragmentShader = load_shader (  GL_FRAGMENT_SHADER,"shaders/fragment.glsl" );  // load fragment shader

   GLuint shaderProgram  = glCreateProgram ();                 // create program object
   glAttachShader ( shaderProgram, vertexShader );             // and attach both...
   glAttachShader ( shaderProgram, fragmentShader );           // ... shaders to it

   glLinkProgram ( shaderProgram );    // link the program
   glUseProgram  ( shaderProgram );    // and select it for usage

   //// now get the locations (kind of handle) of the shaders variables
   /*position_loc  = glGetAttribLocation  ( shaderProgram , "position" );
   /phase_loc     = glGetUniformLocation ( shaderProgram , "phase"    );
   offset_loc    = glGetUniformLocation ( shaderProgram , "offset"   );
   if ( position_loc < 0  ||  phase_loc < 0  ||  offset_loc < 0 ) {
      cerr << "Unable to get uniform location" << endl;
      return 1;
   }*/


   const float
      window_width  = 800.0,
      window_height = 480.0;

   //// this is needed for time measuring  -->  frames per second
   struct  timezone  tz;
   timeval  t1, t2;
   gettimeofday ( &t1 , &tz );
   int  num_frames = 0;

   bool quit = false;
   while ( !quit ) {    // the main loop

      while ( XPending ( x_display ) ) {   // check for events from the x-server

         XEvent  xev;
         XNextEvent( x_display, &xev );

         if ( xev.type == MotionNotify ) {  // if mouse has moved
//            cout << "move to: << xev.xmotion.x << "," << xev.xmotion.y << endl;
            GLfloat window_y  =  (window_height - xev.xmotion.y) - window_height / 2.0;
            norm_y            =  window_y / (window_height / 2.0);
            GLfloat window_x  =  xev.xmotion.x - window_width / 2.0;
            norm_x            =  window_x / (window_width / 2.0);
            update_pos = true;
         }

         if ( xev.type == KeyPress )   quit = true;
      }

      //glewInit();

      //render();   // now we finally put something on the screen

      initscene();
      renderNew();


      if ( ++num_frames % 100 == 0 ) {
         gettimeofday( &t2, &tz );
         float dt  =  t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec) * 1e-6;
         cout << "fps: " << num_frames / dt << endl;
         num_frames = 0;
         t1 = t2;
      }
//      usleep( 1000*10 );
   }


   ////  cleaning up...
   eglDestroyContext ( egl_display, egl_context );
   eglDestroySurface ( egl_display, egl_surface );
   eglTerminate      ( egl_display );
   XDestroyWindow    ( x_display, win );
   XCloseDisplay     ( x_display );

   return 0;
}