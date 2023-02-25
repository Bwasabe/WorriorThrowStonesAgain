#pragma once

enum class IMAGE_TYPE
{
	MAGENTA_IMAGE,
	TRANSPARENT_IMAGE,
};


typedef enum class TAGS
{
	DEFAULT = 1<< 0,
	PLAYER = 1 << 1,
	BULLET = 1 << 2,
	ENEMY = 1 << 3,

}TAG;



//Enum | Enum != 0 == HasFlag


