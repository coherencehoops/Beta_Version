
#include "colr_definitions.h"

// test two colors for equality
bool is_equal(Color *color1, Color *color2) {
    if ((color1->r == color2->r) && (color1->g == color2->g) && (color1->b == color2->b))
        return true;
    else
        return false;
}

// set a explicit color to the next explicit rainbow color r-y-g-c-b-m-r
void set_next_rainbow_exp(Color *col) {
    Color COLOR_VAR = COLOR_DEF_RED;    
    if (is_equal(col, &COLOR_VAR)) {*col = COLOR_SET_YELLOW; return;}
    
    COLOR_VAR = COLOR_SET_YELLOW;    
    if (is_equal(col, &COLOR_VAR)) {*col = COLOR_SET_GREEN; return;}
    
    COLOR_VAR = COLOR_SET_GREEN;    
    if (is_equal(col, &COLOR_VAR)) {*col = COLOR_SET_CYAN; return;}
    
    COLOR_VAR = COLOR_SET_CYAN;    
    if (is_equal(col, &COLOR_VAR)) {*col = COLOR_SET_BLUE; return;}
    
    COLOR_VAR = COLOR_SET_BLUE;    
    if (is_equal(col, &COLOR_VAR)) {*col = COLOR_SET_MAGENTA; return;}
    
    COLOR_VAR = COLOR_SET_MAGENTA;    
    if (is_equal(col, &COLOR_VAR)) {*col = COLOR_SET_RED; return;}
    
    *col = COLOR_SET_BLACK;
}

// set an explicit color to the previous explicit rainbow color r-y-g-c-b-m-r
void set_prev_rainbow_exp(Color *col) {
    Color COLOR_VAR = COLOR_DEF_RED;    
    if (is_equal(col, &COLOR_VAR)) {*col = COLOR_SET_MAGENTA; return;}
    
    COLOR_VAR = COLOR_SET_YELLOW;    
    if (is_equal(col, &COLOR_VAR)) {*col = COLOR_SET_RED; return;}
    
    COLOR_VAR = COLOR_SET_GREEN;    
    if (is_equal(col, &COLOR_VAR)) {*col = COLOR_SET_YELLOW; return;}
    
    COLOR_VAR = COLOR_SET_CYAN;    
    if (is_equal(col, &COLOR_VAR)) {*col = COLOR_SET_GREEN; return;}
    
    COLOR_VAR = COLOR_SET_BLUE;    
    if (is_equal(col, &COLOR_VAR)) {*col = COLOR_SET_CYAN; return;}
    
    COLOR_VAR = COLOR_SET_MAGENTA;    
    if (is_equal(col, &COLOR_VAR)) {*col = COLOR_SET_BLUE; return;}
    
    *col = COLOR_SET_BLACK;
}

// set a color to the next rainbow color r-y-g-c-b-m-r
void set_next_rainbow(Color *col) {
    if (col->r){                            //1,2,5,6
        if (col->g){                        //1,2
            if (col->r == 255){             //1
                col->r = (255 - col->g);
                col->g = 255;
            } else {                        //2
                col->b = (255 - col->r);
                col->r = 0;
            }
        } else {                            //5,6
            if (col->r == 255){             //6
                col->g = (255 - col->b);
                col->b = 0;
            } else {                        //5
                col->b = (255 - col->r);
                col->r = 255;
            }
        }
    } else if (col->g){                     //3,4
        if (col->g == 255){                 //3
            col->g = (255 - col->b);
            col->b = 255;
        } else {                            //4
            col->r = (255 - col->g);
            col->g = 0;
        }
    } else {                                //b
        col->r = 255;
    }
}

// set a color to the previous rainbow color r-y-g-c-b-m-r
void set_prev_rainbow(Color *col) {
    if (col->r){                            //1,2,5,6
        if (col->g){                        //1,2
            if (col->r == 255){             //1
                col->b = (255 - col->g);
                col->g = 0;
            } else {                        //2
                col->g = (255 - col->r);
                col->r = 255;
            }
        } else {                            //5,6
            if (col->r == 255){             //6
                col->r = (255 - col->b);
                col->b = 255;
            } else {                        //5
                col->g = (255 - col->r);
                col->r = 0;
            }
        }
    } else if (col->g){                     //3,4
        if (col->g == 255){                 //3
            col->r = (255 - col->b);
            col->b = 0;
        } else {                            //4
            col->b = (255 - col->g);
            col->g = 255;
        }
    } else {                                //b
        col->g = 255;
    }
}

