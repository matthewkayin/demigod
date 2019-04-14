//Demigod
//globals.hpp - full of global variables to be used across classes

#ifndef GLOBALS_H
#define GLOBALS_H

//variables for when we're rendering only onto specific frames of the UI
//the FRAME variables describe where we render the UI section
const int FRAME_X = 20;
const int FRAME_Y = 15;
const int FRAME_W = 1028;
const int FRAME_H = 516;
const int FRAME_THICKNESS = 4;
//the CANVAS variables describe where we're allowed to render inside the frame
const int CANVAS_X = FRAME_X + FRAME_THICKNESS;
const int CANVAS_Y = FRAME_Y + FRAME_THICKNESS;
const int CANVAS_W = FRAME_W - FRAME_THICKNESS;
const int CANVAS_H = FRAME_H - FRAME_THICKNESS;
//the size of the canvas in tiles
const int CANVAS_TILE_W = CANVAS_W / 32;
const int CANVAS_TILE_H = CANVAS_H / 32;

#endif
