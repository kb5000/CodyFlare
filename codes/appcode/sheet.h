#pragma once
#include "vector.h"
#include "utility.h"
#include "color.h"

/// name: show_sheet
/// func: show a sheet one tick
/// para: content expects a Vector* contains Vector, which includes char*, start expects the left_bottom pos, 
///       size expects the whole size, row and col expects the whole size, including title if have, 
///       hasTitle expects whether use the first row to be title, hasInnerLines expects whether it has inner 
///       grid lines, titleHight expects the hight of the title, gridColor, textColor, backColor expects their
///       colors, titleFont, titleSize, textFont, textSize expects the font info of title and text, align
///       expects the align way of the text, but title will always be in the middle
/// visb: public
int show_sheet(Vector* content, Pos start, Pos size, int row, int col, int hasTitle, int hasInnerLines,
				double titleHight, Color gridColor, Color textColor, Color backColor,
				const char* titleFont, int titleSize, const char* textFont, int textSize, char align);
