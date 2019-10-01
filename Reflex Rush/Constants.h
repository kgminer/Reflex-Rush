#pragma once

#include "GameManager.h"

//Asteroid Constants
static int ASTEROID_SCREEN_SIZE_X = 180, ASTEROID_SCREEN_SIZE_Y = -180, ASTEROID_SCREEN_SIZE_W = 180, ASTEROID_SCREEN_SIZE_H = 180;
static int ASTEROID_IMAGE_X = 35, ASTEROID_IMAGE_Y = 256, ASTEROID_IMAGE_W = 180, ASTEROID_IMAGE_H = 190, ASTEROID_IMAGE_SPACING = 25;
static int NUMBER_OF_SPRITE_IMAGES = 8;
//GameManager Constants
static double SPAWN_TIMER = 1.1, SPAWN_TIMER_ADJUSTMENT = .3;
static double CONVERT_MS_TO_SEC = 1000.0;
static int CHANCE_TO_SPAWN_ASTEROID = 30, SPAWN_THRESHOLD_ADJUSTMENT = 5, ASTEROID_ARRAY_ROWS = 5, ASTEROID_ARRAY_COLS = 8;
static int AUDIO_FREQUENCY = 44100, AUDIO_CHANNELS = 2, AUDIO_CHUNKSIZE = 2048;
static int STARTING_LEVEL_THRESHOLD = 12000;
static int PLAYER_MOVEMENT_VELOCITY = 2;
static const int REPLAY_PRESSED = 1, RETURN_PRESSED = 2, PLAY_PRESSED = 3;
//main Constants
static int GAME_WIDTH = 1440;
static int GAME_HEIGHT = 800;
//Player Constants
static int PLAYER_SCREEN_SIZE_X_SPACING = 110, PLAYER_SCREEN_SIZE_Y_SPACING = 110, PLAYER_SCREEN_SIZE_W = 110, PLAYER_SCREEN_SIZE_H = 110;
static int PLAYER_IMAGE_X = 60, PLAYER_IMAGE_Y = 30, PLAYER_IMAGE_W = 135, PLAYER_IMAGE_H = 180;
//UIManager Constants
static int TITLE_LABEL_SIZE = 64, TITLE_LABEL_X = 500, TITLE_LABEL_Y = 300;
static int GAME_OVER_LABEL_SIZE = 64, GAME_OVER_LABEL_X = 500, GAME_OVER_LABEL_Y = 300;
static int PAUSE_LABEL_SIZE = 100, PAUSE_LABEL_X = 500, PAUSE_LABEL_Y = 0;
static int UNPAUSE_TIP_LABEL_SIZE = 32, UNPAUSE_TIP_LABEL_X = 510, UNPAUSE_TIP_LABEL_Y = 100;
static int SCORE_LABEL_SIZE = 25, SCORE_LABEL_X = 0, SCORE_LABEL_Y = 25;
static int LEVEL_LABEL_SIZE = 25, LEVEL_LABEL_X = 0, LEVEL_LABEL_Y = 0;
static int FINAL_SCORE_LABEL_SIZE = 40, FINAL_SCORE_LABEL_X = 500, FINAL_SCORE_LABEL_Y = 380;
static int PLAY_LABEL_SIZE = 40, PLAY_LABEL_X = 590, PLAY_LABEL_Y = 480;
static int PLAY_BUTTON_X = 700, PLAY_BUTTON_Y = 450, PLAY_BUTTON_W = 100, PLAY_BUTTON_H = 100;
static int REPLAY_LABEL_SIZE = 40, REPLAY_LABEL_X = 580, REPLAY_LABEL_Y = 580;
static int REPLAY_BUTTON_X = 750, REPLAY_BUTTON_Y = 550, REPLAY_BUTTON_W = 100, REPLAY_BUTTON_H = 100;
static int RETURN_TO_MENU_LABEL_SIZE = 40, RETURN_TO_MENU_LABEL_X = 400, RETURN_TO_MENU_LABEL_Y = 480;
static int RETURN_TO_MENU_BUTTON_X = 750, RETURN_TO_MENU_BUTTON_Y = 450, RETURN_TO_MENU_BUTTON_W = 100, RETURN_TO_MENU_BUTTON_H = 100;