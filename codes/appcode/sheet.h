#pragma once
#include "vector.h"
#include "utility.h"
#include "color.h"

void show_sheet(Vector* content, Pos start, Pos size, int row, int col, int hasTitle, int hasInnerLines, double titleHight, 
				Color gridColor, Color textColor, Color backColor,
				const char* titleFont, int titleSize, const char* textFont, int textSize);
