#pragma once

/* Origins Controller ________________________________________________ *
 * The origins controller works by mapping controller/keyboard inputs  *
 * to `eventMaps` which trigger a particular event if a given state    *
 * or conditional is true.                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <functional>
#include <map>

#include "SDL.h"
#include "Camera.hpp"
#include "Entity.hpp"

typedef enum {
    MOUSE_DOWN, // 0x00
    MOUSE_UP,   // 0x01
} ORG_MOUSE_EVENT;

typedef enum {
    LEFT_CLICK,  // 0x00
    RIGHT_CLICK, // 0x01
} ORG_MOUSE_INPUT;

typedef enum {
    KEY_DOWN,   // 0x00
    KEY_UP,     // 0x01
} ORG_KEY_EVENT;

const std::map<char, int> ORG_SDL_KEY_MAPPING = {
    {'a', SDLK_a},
    {'b', SDLK_b},
    {'c', SDLK_c},
    {'s', SDLK_s},
    {'q', SDLK_q}
};

// We use std::functions to store events (entity member functions)
// to different user inputs.
using MouseEvent = std::function<void(int, int)>;
using KeyEvent = std::function<void()>;

class Controller
{
public:

    ///
    Controller();

    ///
    ~Controller() = default;

    /// Reads the current state as reported by SDL
    /// and cycls through event maps to fire the appropriate events.
    void poll();

    /// Ties clicking of a particular game object to an event
    void addEventOnClick(Entity& object,
                         const MouseEvent conditional,
                         const MouseEvent event);

    void addEventOnDragOver();

    /// Creates a listener on mouse click
    /// @param mouseButton: specifies the mouse button to listen on
    /// @param clickType:   specifies the click type to listen on
    /// @param eventMap:    maps an entity or state to an event
    /// @param priority:    used to set the order of event firing.
    ///                     smaller values for priority fire before higher values,
    ///                     negative priority events will never fire.
    void addMouseListener(ORG_MOUSE_INPUT mouseButton,
                          ORG_MOUSE_EVENT clickType,
                          MouseEvent event,
                          int priority);

    /// Creates a listener on a keystroke
    /// @param mouseButton: specifies the mouse button to listen on
    /// @param clickType:   specifies the click type to listen on
    /// @param event:       maps an entity or state to an event
    /// @param priority:    used to set the order of event firing.
    ///                     smaller values for priority fire before higher values,
    ///                     negative priority events will never fire.
    void addKeyListener(char key,
                        ORG_KEY_EVENT strokeType,
                        KeyEvent event,
                        int priority);

private:
    std::map<ORG_MOUSE_INPUT, MouseEvent> _mouseEventMap{};
    std::map<int, KeyEvent> _keyEventMap{};
};
