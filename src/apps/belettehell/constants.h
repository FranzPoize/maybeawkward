#ifndef constants_h__
#define constants_h__

#include "user_constants.h"

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720
#define EPSILON 0.0000001f
#define ORIGIN origin_bottom_left
#define MAX_OBJECTS_QUAD_TREE 15
#define MAX_LEVELS_QUAD_TREE 0 
#define CULLING_FACTOR_H 1.5f
#define CULLING_FACTOR_V 1.5f

const float PLAN_THREE_FACTOR = 0.5f;
const float PLAN_FOUR_FACTOR = 0.2f;

const float SECURITY_MARGIN = 4;
const float WIN_WIDTH_SQUARED = WIN_WIDTH*WIN_WIDTH*SECURITY_MARGIN;
const float WIN_HEIGHT_SQUARED = WIN_HEIGHT*WIN_HEIGHT*SECURITY_MARGIN;

const int ABNORMAL_TIME = 20;
const int FRAME_TIME_TARGET = 13;

const float ORBITAL_ENEMY_WEIGHT = 500;
const float ORBITAL_STARTING_SPEED = 20;

const float SINUS_STYLE_MOVEMENT_SPEED = 450;
const float SINUS_AMPLITUDE = 4000;

const float AI_REACTION_DISTANCE = 300;
const float AI_ATTRACTION_TO_TARGET = 10;

//pixels/sec
const float TOP_SPEED = 600;

const float GRAVITY_X = 0.0f;
const float GRAVITY_Y = 30.0f;

const int PHYSICS_Y_LIMIT = 710;

const float BULLET_SPEED = 1000;


#endif // constants_h__