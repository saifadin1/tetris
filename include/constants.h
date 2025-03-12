#pragma once


// escape sequences
#define HORIZONTAL_BAR "\u2500"
#define VERTICAL_BAR "\u2551"
#define TOP_LEFT_CORNER "\u250C"
#define TOP_RIGHT_CORNER "\u2510"
#define BOTTOM_LEFT_CORNER "\u2514"
#define BOTTOM_RIGHT_CORNER "\u2518"
#define BLOCK_CHAR "\U0001F02B"
#define SHADE_CHAR "\U0001F006"
// #define BLOCK_CHAR "R"


// colors
#define RED "\033[0;31m"    
#define GREEN "\033[0;32m"  
#define YELLOW "\033[0;33m" 
#define BLUE "\033[0;34m"   
#define ORANGE "\033[0;35m" 
#define PURPLE "\033[0;35m" 
#define CYAN "\033[0;36m"   
#define WHITE "\033[0;37m"  
#define RESET "\033[0m"     






// keys 
#define _CTRL(k) ((k) & 0x1f)
#define UP_ARROW "\033[A"
#define DOWN_ARROW "\x1B[B"
#define RIGHT_ARROW "\x1B[C"
#define LEFT_ARROW "\x1B[D"