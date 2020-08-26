#include "WindowSdl.h"
#include "Log.h"
#include <GL/glew.h>
using std::string;

WindowSdl::WindowSdl(const std::string &title) : title(title),
                                                 previousSeconds(0),
                                                 currentSeconds(0),
                                                 frameCount(0),
                                                 context(nullptr), 
                                                 window(nullptr)
{
}

WindowSdl::~WindowSdl()
{
        LOG(Info) << "Bye :)";
}

bool WindowSdl::initialize(int xPos, int yPos, int width, int height, bool isFullscreen, const string& titleP)
{
    title = titleP;

    int flags = SDL_WINDOW_OPENGL;
    if (isFullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        LOG(Info) << "Subsystems initialised";

        // WindowSdl
        window = SDL_CreateWindow(title.c_str(), xPos, yPos, width, height, flags);
        if (window)
        {
            LOG(Info) << "WindowSdl initialised";
        }
        else
            return false;

        // OpenGL context
        context = SDL_GL_CreateContext(window);
        if (context)
        {
            LOG(Info) << "OpenGL Context initialised";
        }
        else
            return false;

        return true;
    }
    else
    {
        LOG(Error) << "SDL initialisation failed";
        LOG(Error) << SDL_GetError();
        return false;
    }
}

void WindowSdl::logGlParams()
{
    GLenum params[] = {
        GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
        GL_MAX_CUBE_MAP_TEXTURE_SIZE,
        GL_MAX_DRAW_BUFFERS,
        GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,
        GL_MAX_TEXTURE_IMAGE_UNITS,
        GL_MAX_TEXTURE_SIZE,
        GL_MAX_VARYING_FLOATS,
        GL_MAX_VERTEX_ATTRIBS,
        GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
        GL_MAX_VERTEX_UNIFORM_COMPONENTS,
        GL_MAX_VIEWPORT_DIMS,
        GL_STEREO,
    };
    const char *names[] = {
        "GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS",
        "GL_MAX_CUBE_MAP_TEXTURE_SIZE",
        "GL_MAX_DRAW_BUFFERS",
        "GL_MAX_FRAGMENT_UNIFORM_COMPONENTS",
        "GL_MAX_TEXTURE_IMAGE_UNITS",
        "GL_MAX_TEXTURE_SIZE",
        "GL_MAX_VARYING_FLOATS",
        "GL_MAX_VERTEX_ATTRIBS",
        "GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS",
        "GL_MAX_VERTEX_UNIFORM_COMPONENTS",
        "GL_MAX_VIEWPORT_DIMS",
        "GL_STEREO",
    };
    LOG(Info) << "-----------------------------";
    LOG(Info) << "GL Context Params:";
    // integers - only works if the order is 0-10 integer return types
    for (int i = 0; i < 10; i++)
    {
        int v = 0;
        glGetIntegerv(params[i], &v);
        LOG(Info) << names[i] << " " << v;
    }
    // others
    int v[2];
    v[0] = v[1] = 0;
    glGetIntegerv(params[10], v);
    LOG(Info) << names[10] << " " << v[0] << " " << v[1];
    unsigned char s = 0;
    glGetBooleanv(params[11], &s);
    LOG(Info) << names[11] << " " << (unsigned int)s;
    LOG(Info) << "";
};

void WindowSdl::updateFpsCounter(long dt)
{
    double elapsedSeconds;

    currentSeconds += dt / 1000.0;
    elapsedSeconds = currentSeconds - previousSeconds;
    /* limit text updates to 4 per second */
    if (elapsedSeconds > 0.25)
    {
        previousSeconds = currentSeconds;
        char tmp[128];
        double fps = (double)frameCount / elapsedSeconds;
#if __linux__
        sprintf(tmp, "%s @ fps: %.2f", title.c_str(), fps);
#else
        sprintf_s(tmp, "%s @ fps: %.2f", title.c_str(), fps);
#endif
        SDL_SetWindowTitle(window, tmp);
        frameCount = 0;
    }
    frameCount++;
}

void WindowSdl::swapBuffer()
{
    SDL_GL_SwapWindow(window);
}

void WindowSdl::clean()
{
    // SDL_DestroyWindow(window); Handled by unique_ptr
    SDL_GL_DeleteContext(context);
}
