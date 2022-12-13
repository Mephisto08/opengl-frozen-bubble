#include "Graphics.h"

Graphics::Graphics() {
    cout << "Initializing OpenGL ES..." << endl;
    initOGL();

    cout << "Initializing shaders..." << endl;
    initShaders();

    cout << "Setting up viewport..." << endl;
    setupViewport();

    cout << "Initializing node screen positions..." << endl;
    initNodePositions();
}

void Graphics::showCompilerLog(GLint shader) {
    char log[1024];
    glGetShaderInfoLog(shader, sizeof log, NULL, log);
    cout << "Shader (#" << shader << ") compilation:\n" << log << endl;
}

void Graphics::showLinkerLog(GLint prog) {
    char log[1024];
    glGetProgramInfoLog(program, sizeof log, NULL, log);
    cout << "Shader (#" << program << ") linking:\n" << log << endl;
}

void Graphics::resize() {
    // Raspberry Pi 4: query window size from X11
    XWindowAttributes gwa;
    XGetWindowAttributes(_xDisplay, _xWindow, &gwa);
    _width = gwa.width;
    _height = gwa.height;
    glViewport(0, 0, _width, _height);

    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    projection = glm::perspective(glm::radians(45.0f), (float) _width / (float) _height, 0.1f, 100.0f);
}

void Graphics::handleXEvents() {
    bool quit = false;
    // under Raspberry Pi 4 we can process keys from X11
    while (XPending(_xDisplay)) {   // check for events from the x-server
        XEvent xev;
        XNextEvent(_xDisplay, &xev);
        switch (xev.type) {
            case KeyPress:
                switch (xev.xkey.keycode) {
                    case 9://ESC
                    case 24://Q
                        exit(0);
                        break;
                }
                break;
            case ButtonPress:
                switch (xev.xbutton.button) {
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

void Graphics::createXWindow() {

    _xDisplay = XOpenDisplay(NULL);
    if (NULL == _xDisplay) {
        throw runtime_error("could not connect to X server");
    }

    Window root = DefaultRootWindow(_xDisplay);

    XSetWindowAttributes windowAttributes;
    windowAttributes.event_mask =
            KeyPressMask | ButtonPressMask | Button1MotionMask | ExposureMask | PropertyChangeMask;

    _xWindow = XCreateWindow(_xDisplay, root,
                             0, 0, _width, _height,
                             0, CopyFromParent, InputOutput, CopyFromParent,
                             CWEventMask, &windowAttributes);

// the code below follows
// https://wiki.maemo.org/SimpleGL_example
// it may or may not be needed, depending on platform and window manager.

    // override window placement by the window manager
    windowAttributes.override_redirect = False;
    XChangeWindowAttributes(_xDisplay, _xWindow, CWOverrideRedirect, &windowAttributes);

    // change to fullscreen on ubuntu
    Atom atom = XInternAtom(_xDisplay, "_NET_WM_STATE_FULLSCREEN", True);
    XChangeProperty(
            _xDisplay, _xWindow,
            XInternAtom(_xDisplay, "_NET_WM_STATE", True),
            XA_ATOM, 32, PropModeReplace,
            (unsigned char *) &atom, 1);

    // set focus management
    XWMHints hints;
    hints.input = True;             // get focus from wm without explicitly setting it
    hints.flags = InputHint;        // enable the input field above
    XSetWMHints(_xDisplay, _xWindow, &hints);

    // change window title
    XStoreName(_xDisplay, _xWindow, "OpenGL - Frozen Bubble");

    // map window -- causes it to be finally displayed
    XMapWindow(_xDisplay, _xWindow);

    // another means to communicate fullscreen to a window manager
    // also works on ubuntu
    Atom wm_state = XInternAtom(_xDisplay, "_NET_WM_STATE", False);
    Atom fullscreen = XInternAtom(_xDisplay, "_NET_WM_STATE_FULLSCREEN", False);

    XEvent xev;
    memset(&xev, 0, sizeof(xev));

    xev.type = ClientMessage;
    xev.xclient.window = _xWindow;
    xev.xclient.message_type = wm_state;
    xev.xclient.format = 32;
    xev.xclient.data.l[0] = 1;
    xev.xclient.data.l[1] = fullscreen;
    XSendEvent(                // send an event mask to the X-server
            _xDisplay,
            DefaultRootWindow (_xDisplay),
            False,
            SubstructureNotifyMask,
            &xev);
}

/*
 * initOGL()
 *
 * sets up an OpenGL ES2 surface and clears the screen to hda_darkblue
 */

void Graphics::initOGL() {
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
    assert(display != EGL_NO_DISPLAY);
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
    assert(context != EGL_NO_CONTEXT);
    check();

    createXWindow();
    // create an EGL window surface
    surface = eglCreateWindowSurface(display, config, _xWindow, NULL);
    assert(surface != EGL_NO_SURFACE);
    check();

    // connect the context to the surface
    result = eglMakeCurrent(display, surface, surface, context);
    assert(EGL_FALSE != result);
    check();

    // Set background color and clear buffers
    glClearColor(0.0627f, 0.1765f, 0.3608f, 1.0f); // some dark blue
    glClear(GL_COLOR_BUFFER_BIT);

    check();
}

void Graphics::print_shader_info_log(GLuint shader) {  // handle to the shader
    GLint length;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

    if (length) {
        char *buffer = new char[length];
        glGetShaderInfoLog(shader, length, NULL, buffer);
        cout << "shader info: " << buffer << flush;
        delete[] buffer;

        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (success != GL_TRUE) exit(1);
    }
}

GLuint Graphics::load_shader(GLenum type, const string &path) {
    string Code;
    ifstream ShaderFile;

    ShaderFile.exceptions(ifstream::badbit);
    try {
        ShaderFile.open(path);
        if (!ShaderFile.is_open())
            throw invalid_argument("Vertex shader file not found.");

        stringstream ShaderStream;
        ShaderStream << ShaderFile.rdbuf();

        ShaderFile.close();

        Code = ShaderStream.str();
    } catch (const exception &ex) {
        string errmsg;
        errmsg.append("Error: Shader files couldn't be read:\n");
        errmsg.append(ex.what());
        throw logic_error(errmsg.c_str());
    }
    const GLchar *ShaderCode = Code.c_str();
    GLuint shader = glCreateShader(type);

    glShaderSource(shader, 1, &ShaderCode, NULL);
    glCompileShader(shader);

    print_shader_info_log(shader);
    return shader;
}

void Graphics::initShaders() {
    GLuint vertexShader = load_shader(GL_VERTEX_SHADER, "shader/vertex.glsl");         // load vertex shader
    GLuint fragmentShader = load_shader(GL_FRAGMENT_SHADER, "shader/fragment.glsl");   // load fragment shader

    check();
    showCompilerLog(vertexShader);
    check();
    showCompilerLog(fragmentShader);

    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    check();

    showLinkerLog(program);

    aPosition = glGetAttribLocation(program, "Position");
    aProjection = glGetUniformLocation(program, "Projection");
    aView = glGetUniformLocation(program, "View");
    aModel = glGetUniformLocation(program, "Model");
    uColor = glGetUniformLocation(program, "Color");
}

void Graphics::initNodePositions() {
    for (int y = 0; y < 13; ++y) {
        if (y % 2 == 0) {
            for (int x = 0; x < 8; ++x) {
                auto res = nodePositions.insert(make_pair(static_cast<char>('A' + y) + to_string(x),
                                                          make_pair((float) x * spacingX + diffX,
                                                                    (float) y * -spacingY + diffY + offsetY)));
                if (!res.second) {
                    throw invalid_argument("Cannot add nodePosition!");
                }
            }
        } else {
            for (int x = 0; x < 7; ++x) {
                auto res = nodePositions.insert(make_pair(static_cast<char>('A' + y) + to_string(x),
                                                          make_pair((float) x * spacingX + diffX + spacingX / 2,
                                                                    (float) y * -spacingY + diffY + offsetY)));
                if (!res.second) {
                    throw invalid_argument("Cannot add nodePosition!");
                }
            }
        }
    }
}

void Graphics::setupViewport() {
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

    // Camera matrix
    view = glm::lookAt(
            glm::vec3(0, 0, 17.5), // Camera in World Space
            glm::vec3(0, 0, 0), // and looks at the origin
            glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
    );

    // Model matrix : an identity matrix (model will be at the origin)
    model = glm::mat4(1.0f);

    glViewport(0, 0, screenWidth, screenHeight);
    check();
}

void Graphics::drawSquare(GLfloat squareData[]) {
    glVertexAttribPointer(aPosition, 4, GL_FLOAT, GL_FALSE, 0, squareData);
    glEnableVertexAttribArray(aPosition);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    check();
}

void Graphics::drawCircle(GLfloat centerX, GLfloat centerY, GLfloat radius) {
    // array to hold the vertices of the circle
    GLfloat vertices[NUM_VERTICES][2];

    // calculate the vertices of the circle
    for (int i = 0; i < NUM_VERTICES; i++) {
        GLfloat angle = 2 * M_PI * i / NUM_VERTICES;
        vertices[i][0] = radius * cos(angle) + centerX;
        vertices[i][1] = radius * sin(angle) + centerY;
    }

    // draw the circle using the vertices array
    glVertexAttribPointer(aPosition, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(aPosition);
    glDrawArrays(GL_TRIANGLE_FAN, 0, NUM_VERTICES);
    glDrawArrays(GL_TRIANGLE_FAN, 0, NUM_VERTICES);
    check();
}

void Graphics::drawCircleByName(string name, Color color) {
    auto res = nodePositions.find(name);
    if (res == nodePositions.end()) {
        throw invalid_argument("Cannot draw circle: Name '"+name+"' wasn't found!");
        return;
    }
    const float x = res->second.first;
    const float y = res->second.second;

    glUniform4f(uColor, color.r/255, color.g/255, color.b/255, color.a); // some black
    drawCircle(x, y);
}

void Graphics::draw(map<string, Node> nodes) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    check();

    // could also be set just once
    // unless different ones are used
    glUseProgram(program);
    check();

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
    glUniformMatrix4fv(aProjection, 1, GL_FALSE, &projection[0][0]);
    glUniformMatrix4fv(aView, 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(aModel, 1, GL_FALSE, &model[0][0]);
    check();

    // a square as a simple triangle fan
    // (it shows as a rectangle without a projection matrix ;) )
    GLfloat squareData[] = {
            -4 * spacingX, -6.6f * spacingY + offsetY, 0.0, 1.0,
            4 * spacingX, -6.6f * spacingY + offsetY, 0.0, 1.0,
            4 * spacingX, 6.6f * spacingY + offsetY, 0.0, 1.0,
            -4 * spacingX, 6.6f * spacingY + offsetY, 0.0, 1.0
    };
    glUniform4f(uColor, 0.3176, 0.6118, 0.8588, 1.0); // some blue
    drawSquare(squareData);


    for (const pair<string, Node> &node: nodes) {
        if(node.first != "ROOT") {
            drawCircleByName(node.first, node.second.getColor());
        }
    }

    check();

    // finalize
    glFlush();
    glFinish();
    check();

    // swap buffers: show what we just painted
    eglSwapBuffers(display, surface);
    check();
}