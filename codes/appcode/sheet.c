#include "sheet.h"
#include "graphics.h"
#include "imgui.h"
#include "extgraph.h"
#include "input.h"

//void draw_grid(Pos start, Pos size, int row, int col) {
//	
//}

int show_sheet(Vector* content, Pos start, Pos size, int row, int col, int hasTitle, int hasInnerLines, double titleHight, 
				Color gridColor, Color textColor, Color backColor, 
				const char* titleFont, int titleSize, const char* textFont, int textSize) {
	Pos elementSize = new_pos(size.x / col, (size.y - !!hasTitle * titleHight) / (row - !!hasTitle)); //normalize
	set_color(backColor);
	drawRectangle(start.x, start.y, size.x, size.y, 1);
	set_color(gridColor);
	drawRectangle(start.x, start.y, size.x, size.y, 0);
	for (int i = 0; i < row; i++) {
		Vector* chrs = pcalls(content, at, i);
		if (hasTitle && i == 0) {
			char* a = pcalls(chrs, at, 0);
			SetFont((char*)titleFont);
			SetPointSize(titleSize);
			drawBoxFree(start.x, start.y + size.y - titleHight, size.x, titleHight, 0, a, 'C', textColor, hasInnerLines);
			continue;
		}
		SetFont((char*)textFont);
		SetPointSize(textSize);
		for (int j = 0; j < col; j++) {
			char* a = pcalls(chrs, at, j);
			set_color(gridColor);
			drawBoxFree(start.x + j * elementSize.x, start.y + (row - i - 1) * elementSize.y, 
						elementSize.x, elementSize.y, 0, a, 'C', textColor, hasInnerLines);
		}
	}
	MouseKeys mk = get_mouse_key();
	return mk.left == 0 && pos_in_rect(mk.pos, start, add_pos(start, size));
}
