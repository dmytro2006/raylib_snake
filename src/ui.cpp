//
// Created by dmytro2006 03/04/2025.
//

#include "ui.h"

void UI::draw_centred_text(const std::string &text, Vector2 position, Vector2 size, Color color, float font_size) {
    draw_centred_text(text, position, size, color, font_size, font_size / 10, GetFontDefault());
}

void UI::draw_centred_text(const std::string &text, Vector2 position, Vector2 size, Color color, float font_size,
                           float spacing) {
    draw_centred_text(text, position, size, color, font_size, spacing, GetFontDefault());
}

void UI::draw_centred_text(const std::string &text, Vector2 position, Vector2 size, Color color, float font_size,
                           float spacing, Font font) {
    Vector2 text_size = MeasureTextEx(font, text.c_str(), font_size, spacing);
    Vector2 text_position = {position.x + (size.x - text_size.x) / 2, position.y + (size.y - text_size.y) / 2};
    DrawTextEx(font, text.c_str(), text_position, font_size, spacing, color);
}

void UI::draw_centred_text(const std::string &text, Vector2 position, Vector2 size, Color color, float font_size,
                           Font font) {
    draw_centred_text(text, position, size, color, font_size, 1, font);
}

void UI::draw_button(const std::string &text, Vector2 position, Vector2 size, Color text_color, Color background_color,
                     float font_size) {
    draw_button(text, position, size, text_color, background_color, font_size, font_size / 10, BLACK, 0,
                GetFontDefault());
}

void UI::draw_button(const std::string &text, Vector2 position, Vector2 size, Color text_color, Color background_color,
                     float font_size, Color outline_color, float outline_thickness) {
    draw_button(text, position, size, text_color, background_color, font_size, font_size / 10, outline_color,
                outline_thickness, GetFontDefault());
}

void UI::draw_button(const std::string &text, Vector2 position, Vector2 size, Color text_color, Color background_color,
                     float font_size, float spacing, Color outline_color, float outline_thickness, Font font) {
    DrawRectangleV(position, size, background_color);
    if (outline_thickness > 0)
        DrawRectangleLinesEx({position.x, position.y, size.x, size.y}, outline_thickness, outline_color);
    draw_centred_text(text, position, size, text_color, font_size, spacing, GetFontDefault());
}

bool UI::is_pressed(Vector2 button_position, Vector2 button_size, Vector2 mouse_position) {
    return mouse_position.x >= button_position.x && mouse_position.x < button_position.x + button_size.x &&
           mouse_position.y >= button_position.y &&
           mouse_position.y < button_position.y + button_size.y;
}
