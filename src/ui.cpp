//
// Created by dmytro2006 03/04/2025.
//

#include "ui.h"

void UI::CentredText::draw() {
    Vector2 textSize = MeasureTextEx(font, text.c_str(), fontSize, spacing);
    Vector2 textPosition = {position.x + (size.x - textSize.x) / 2, position.y + (size.y - textSize.y) / 2};
    DrawTextEx(font, text.c_str(), textPosition, fontSize, spacing, color);
}
