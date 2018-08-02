/*
 File for defining color types and utilities
 */

// Guard condition so that contents of file are not included more than once.  
#ifndef COLR_DEFINITIONS
#define	COLR_DEFINITIONS

#include <p24Fxxxx.h>
#include <xc.h>
#include "conf_master.h"

// structure that defines a single color
typedef struct Color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Color;

// macros holding default colors for initial defining
#define COLOR_DEF_RED       {.r=255, .g=0,   .b=0}
#define COLOR_DEF_GREEN     {.r=0,   .g=255, .b=0}
#define COLOR_DEF_BLUE      {.r=0,   .g=0,   .b=255}
#define COLOR_DEF_YELLOW    {.r=255, .g=255, .b=0}
#define COLOR_DEF_CYAN      {.r=0,   .g=255, .b=255}
#define COLOR_DEF_MAGENTA   {.r=255, .g=0,   .b=255}
#define COLOR_DEF_WHITE     {.r=255, .g=255, .b=255}
#define COLOR_DEF_BLACK     {.r=0,   .g=0,   .b=0}

// macros holding default colors for assignments
#define COLOR_SET_RED       (Color)COLOR_DEF_RED
#define COLOR_SET_GREEN     (Color)COLOR_DEF_GREEN
#define COLOR_SET_BLUE      (Color)COLOR_DEF_BLUE
#define COLOR_SET_YELLOW    (Color)COLOR_DEF_YELLOW
#define COLOR_SET_CYAN      (Color)COLOR_DEF_CYAN
#define COLOR_SET_MAGENTA   (Color)COLOR_DEF_MAGENTA
#define COLOR_SET_WHITE     (Color)COLOR_DEF_WHITE
#define COLOR_SET_BLACK     (Color)COLOR_DEF_BLACK

// color utility functions
bool is_equal(Color*, Color*);          // test two colors for equality
void set_next_rainbow_exp(Color*);      // set explicit color to next explicit rainbow color
void set_prev_rainbow_exp(Color*);      // set explicit color to previous explicit rainbow color
void set_next_rainbow(Color*);          // set color to next rainbow color
void set_prev_rainbow(Color*);          // set color to previous rainbow color

#endif	/* COLR_DEFINITIONS */

