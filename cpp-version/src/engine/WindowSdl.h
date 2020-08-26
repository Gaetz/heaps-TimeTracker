#ifndef WINDOW_SDL_H
#define WINDOW_SDL_H
#include <string>
#include <memory>

#ifdef __linux__
#include <SDL2/SDL.h>
#elif _WIN32
#include <SDL.h>
#endif


// Used by SDL_Window unique pointer
struct SdlWindowDestroyer
{
    void operator()(SDL_Window *window) const
    {
        SDL_DestroyWindow(window);
    }
};

// Manage game's window and drawing in this window.
// The window title bar gives some info, as game's title
// or FPS counter.
class WindowSdl
{
public:
    WindowSdl(const std::string& title);
    virtual ~WindowSdl();

    bool initialize(int xPos, int yPos, int width, int height, bool isFullscreen, const std::string& titleP);
    void logGlParams();
    void updateFpsCounter(long dt);
    void swapBuffer();
    void clean();

    int getWidth() const { return width; }
    int getHeight() const { return height; }

private:
    //std::unique_ptr<SDL_Window, SdlWindowDestroyer> window;
    SDL_Window* window;
    SDL_GLContext context;
    std::string title;

    int width;
    int height;

    double previousSeconds;
    double currentSeconds;
    int frameCount;

    WindowSdl();
    WindowSdl(const WindowSdl &);
    WindowSdl &operator=(const WindowSdl &);
};

#endif