#ifndef constants_h__
#define constants_h__

#include "user_constants.h"

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

const int ABNORMAL_TIME = 20;
const int FRAME_TIME_TARGET = 13;

const float ORBITAL_ENEMY_WEIGHT = 20;
const float ORBITAL_PLAYER_WEIGHT = 20;
const float ORBITAL_STARTING_SPEED = 20;

const float SINUS_STYLE_MOVEMENT_SPEED = 20;

const float AI_REACTION_DISTANCE = 500;

//pixels/sec
const float TOP_SPEED = 200;

const float GRAVITY_X = 0.0f;
const float GRAVITY_Y = 30.0f;

const int PHYSICS_Y_LIMIT = 800;

#endif // constants_h__