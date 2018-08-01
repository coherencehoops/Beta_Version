
// Guard condition so that contents of file are not included more than once.  
#ifndef COLR_COLOR_RUN
#define	COLR_COLOR_RUN

#include <p24Fxxxx.h>
#include <xc.h>

// values to use for transition behaviors
#define BEH_JUMP 0  // jump from one color to the next
#define BEH_FADE 1  // fade from one color to the next
#define BEH_PWM  2  // pulse width modulate from one color to the next
#define BEH_TRIG 3  // wait for trigger to transition colors
#define NUM_PWM_SHFT 3 // 2^this is the number of transistions to do during PWM

// structure that defines a single color
struct Color {
    unsigned char r,g,b;
};

// structure that defines a pattern of colors to transition through
struct Color_Run {
    struct Color *colors;       // colors in the current color run
    unsigned char length;       // length of arrays (number of colors in run)
    unsigned char *steps;       // number of steps to stay on each color (0=inf)
    unsigned char *behavior;    // transition behavior between colors
    unsigned char repeat;       // number of times to repeat color run before going to next (0=inf)
    unsigned char curStep;      // current step in color run
    unsigned char curColor;     // index of last color accessed in array
    unsigned char curRepeat;    // current iteration through the color run
    struct Color_Run *next;     // next color run to transition to
    struct Color_Run *last;     // end of *next pointer chain
};

// structure that groups a color, a run, and a number of steps
struct Color_Pack {
    struct Color col;
    struct Color_Run *run;
    unsigned char steps;
};

// concatenate two runs using the *next pointer
void concatenate_color_runs(struct Color_Run*, struct Color_Run*);

// extract the current color from the color run
struct Color_Pack extract_color(struct Color_Run*, unsigned int);

// use transition behavior to generate current color
struct Color generate_color_behavior(struct Color*, struct Color*,
                                     unsigned short, unsigned short,
                                     unsigned short, unsigned char);

#endif	/* COLR_COLOR_RUN */

