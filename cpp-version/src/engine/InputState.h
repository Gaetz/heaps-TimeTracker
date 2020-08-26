#ifndef INPUT_STATE_H
#define INPUT_STATE_H

#include "Input_KeyboardState.h"
#include "Input_MouseState.h"

struct InputState
{
	KeyboardState keyboardState;
	MouseState mouse;
};

#endif