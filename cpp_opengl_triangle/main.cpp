// Failed attempt. compelte mess.

#include <GL/glx.h>

#include <X11/Xlib.h>

#include <iostream>

bool g_contrinue_main = true;

int main() try
{
    // Forward Declarations
    // Xorg
    Display* rx_display = nullptr;
    XVisualInfo* vx_buffer_config = nullptr;
    XSetWindowAttributes vx_window_attributes = {};
    Window vx_window = {};
    // GL X extensions
    GLXContext vglx_context = nullptr;
    GLXFBConfig* vglx_fbconfigurations = nullptr;
    GLXFBConfig vglx_fbselection = nullptr;
    int vglx_fb_count = -1;
    int vglx_major = -1;
    int bglx_minor = -1;

// Get a matching FB config
    static int vglx_visual_attributes[] =
        {
            GLX_X_RENDERABLE    , True,
            GLX_DRAWABLE_TYPE   , GLX_WINDOW_BIT,
            GLX_RENDER_TYPE     , GLX_RGBA_BIT,
            GLX_X_VISUAL_TYPE   , GLX_TRUE_COLOR,
            GLX_RED_SIZE        , 8,
            GLX_GREEN_SIZE      , 8,
            GLX_BLUE_SIZE       , 8,
            GLX_ALPHA_SIZE      , 8,
            GLX_DEPTH_SIZE      , 24,
            GLX_STENCIL_SIZE    , 8,
            GLX_DOUBLEBUFFER    , True,
            //GLX_SAMPLE_BUFFERS  , 1,
            //GLX_SAMPLES         , 4,
            None
        };

    // Setup X11 Window and OpenGL Context
    rx_display = XOpenDisplay(nullptr);
    if (rx_display == nullptr)
    {
        std::cout << "Could not open X display" << std::endl;
        goto cleanup;
    }
    vglx_fbconfigurations = glXChooseFBConfig(rx_display, DefaultScreen(rx_display), vglx_visual_attributes, &vglx_fb_count);
    vglx_fbselection = vglx_fbconfigurations[4];
    vx_buffer_config = glXGetVisualFromFBConfig(rx_display, vglx_fbselection);
    vglx_context =  glXCreateContext(rx_display, vx_buffer_config, nullptr, 2);


    vx_window_attributes.colormap = XCreateColormap( rx_display,
                                                     RootWindow(rx_display,
                                                                vx_buffer_config->screen),
                                                     vx_buffer_config->visual, AllocNone );
    vx_window_attributes.background_pixmap = None ;
    vx_window_attributes.border_pixel      = 0;
    vx_window_attributes.event_mask        = StructureNotifyMask;
    vx_window = XCreateWindow( rx_display,
                               RootWindow( rx_display, vx_buffer_config->screen ),
                               500, 500, 500, 500, 0,
                               vx_buffer_config->depth,
                               InputOutput,
                               vx_buffer_config->visual,
                               CWBorderPixel|CWColormap|CWEventMask,
                               &vx_window_attributes );
    XMapWindow( rx_display, vx_window );
    glXMakeCurrent( rx_display, vx_window, vglx_context);
    glClearColor( 0, 0.5, 1, 1 );
    glClear ( GL_COLOR_BUFFER_BIT );
    glXSwapBuffers ( rx_display, vx_window );
    for (;;) {}
    for (int i = 0; i < 1000'000'000; ++i) {}

cleanup:
    XFree(vx_buffer_config);
    XCloseDisplay(rx_display);
    catch (...)
    {

    }
}