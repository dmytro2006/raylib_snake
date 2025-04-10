//
// Created by dmytro2006 on 03/04/2025.
//

#ifndef UI_H
#define UI_H
#include "raylib.h"
#include <string>

namespace UI {
    void draw_button(const std::string &text, Vector2 position, Vector2 size, Color text_color, Color background_color,
                     float font_size);

    void draw_button(const std::string &text, Vector2 position, Vector2 size, Color text_color, Color background_color,
                     float font_size, Color outline_color, float outline_thickness);

    void draw_button(const std::string &text, Vector2 position, Vector2 size, Color text_color, Color background_color,
                     float font_size, float spacing, Color outline_color, float outline_thickness, Font font);

    void draw_centred_text(const std::string &text, Vector2 position, Vector2 size, Color color, float font_size);

    void draw_centred_text(const std::string &text, Vector2 position, Vector2 size, Color color, float font_size,
                           float spacing);

    void draw_centred_text(const std::string &text, Vector2 position, Vector2 size, Color color, float font_size,
                           Font font);

    void draw_centred_text(const std::string &text, Vector2 position, Vector2 size, Color color, float font_size,
                           float spacing, Font font);

    bool is_pressed(Vector2 button_position, Vector2 button_size, Vector2 mouse_position);
}

#endif //UI_H
