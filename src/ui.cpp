//
// Created by dmytro2006 03/04/2025.
//

#include "ui.h"

void UI::CentredText::draw() {
    Vector2 textSize = MeasureTextEx(font, text.c_str(), fontSize, spacing);
    Vector2 textPosition = {position.x + (size.x - textSize.x) / 2, position.y + (size.y - textSize.y) / 2};
    DrawTextEx(font, text.c_str(), textPosition, fontSize, spacing, color);
}

void UI::Button::draw() {
    DrawRectangleV(position, size, backgroundColor);
    if (outlined)
        DrawRectangleLinesEx({position.x, position.y, size.x, size.y}, outlineThickness, outlineColor);
    label.draw();
}

bool UI::Button::checkMouseCollision(Vector2 mousePosition) const {
    return mousePosition.x >= position.x && mousePosition.x < position.x + size.x && mousePosition.y >= position.y &&
            mousePosition.y < position.y + size.y;
}
