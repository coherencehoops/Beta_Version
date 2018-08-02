
#include "colr_color_run.h"

// concatenate two runs using the *next and *last pointers
void concatenate_color_runs(Color_Run *run1, Color_Run *run2) {
    run1->last->next = run2;
    run2->last->next = run1;
    run1->last = run2->last;
}

// extract the current color from the color run
Color_Pack extract_color(Color_Run *run, unsigned int deltaStep) {
    unsigned int totalSteps = (unsigned int)run->curStep + deltaStep;
    unsigned int curIndex   = (unsigned int)run->curColor;
    
    // step through color run until we get to the current color
    while ((totalSteps > run->steps[curIndex]) && (run->steps[curIndex] != 0)){
        // adjust steps and jump to next color
        totalSteps -= run->steps[curIndex++];
        
        // end of color array
        if (curIndex >= run->length){
            if (run->repeat == 0){                      // need to repeat this color run forever
                curIndex = 0;
            } else if (run->curRepeat < run->repeat){   // not done repeating this color run
                run->curRepeat++;
                curIndex = 0;
            } else {                                    // move on to next color run
                run->curRepeat = 1;
                run->curStep   = 1;
                run->curColor  = 0;
                curIndex = 0;
                run = run->next;
            }
        }
    }
    
    // create output structure
    Color_Pack pack;
    pack.run = run;
    pack.steps = (unsigned char)(run->steps[curIndex] - totalSteps + 1);
    
    // if we're repeating this color forever, just return it
    if (run->steps[curIndex] == 0) {
        pack.col = run->colors[curIndex];
        return pack;
    }
    
    // update current color run with position
    run->curColor = (unsigned char)curIndex;
    run->curStep  = (unsigned char)totalSteps;
    
    // get first color to generate new color from
    Color *color1 = run->colors + curIndex;
    unsigned short x2 = (unsigned short)run->steps[curIndex]+1;
    
    // get second color to generate new color from
    Color *color2;
    if (curIndex+1 < run->length) {color2 = color1+1;}  // next color is next in array
    else if (run->repeat == 0) {color2 = run->colors;}  // next color is first element in array
    else {color2 = run->next->colors;}                  // next color is first element of next array
    
    // generate current color and return
    pack.col = generate_color_behavior(color1, color2, 
                                       1, x2, (unsigned short)totalSteps,
                                       run->behavior[curIndex]);
    return pack;
}

// use transition behavior to generate current color
Color generate_color_behavior(Color *color1, Color *color2,
                              unsigned short x1, unsigned short x2,
                              unsigned short x, unsigned char behavior) {
    
    // if behavior is jump or trigger, just return the first color
    if ((behavior == BEH_JUMP) || (behavior == BEH_TRIG)) {
        return *color1;
    }
    
    // calculate x lengths of right-triangle
    int duration = (int)x2 - (int)x1;
    int position = (int)x - (int)x1;
    
    // behavior is PWM transition
    if (behavior == BEH_PWM) {
        if (position > (duration - (1<<NUM_PWM_SHFT)*(position % (duration >> NUM_PWM_SHFT)))){
            return *color2;
        } else {
            return *color1;
        }
    }
    
    // behavior is fade between colors
    if (behavior == BEH_FADE) {
        // calculate y lengths of right-triangles
        int diffR = (int)color2->r - (int)color1->r;
        int diffG = (int)color2->g - (int)color1->g;
        int diffB = (int)color2->b - (int)color1->b;

        // slope of line connecting colors (rise / run)
        diffR /= duration;
        diffG /= duration;
        diffB /= duration;

        // calculate change in colors (slope * run)
        diffR *= position;
        diffG *= position;
        diffB *= position;

        // create new color and return
        Color newColor;
        newColor.r = (unsigned char)((int)color1->r + diffR);
        newColor.g = (unsigned char)((int)color1->g + diffG);
        newColor.b = (unsigned char)((int)color1->b + diffB);
        return newColor;
    }
    
    return *color1;  // default just stay on current color
}





