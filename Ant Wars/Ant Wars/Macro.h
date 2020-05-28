#pragma once

#pragma region system include
#include <iostream>
#pragma endregion

#pragma region value macro
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define COLLISION_CHECK_TIME 0.01f
#define COLLISION_RANGE 256.0f
#define MOVETIMER 15.0f
#define PLAYERMAXHP 100
#pragma endregion

#pragma region function macro
#define LOG(TEXT)				\
std::cout << TEXT << std::endl;

#define LOG_ERROR(ERROR, ID)		\
std::cout << ERROR << std::endl;	\
return ID;

#define LOG_SDL_ERROR(CHECK, ID)				\
if(CHECK)										\
{												\
	std::cout << SDL_GetError() << std::endl;	\
	return ID;									\
}
#pragma endregion