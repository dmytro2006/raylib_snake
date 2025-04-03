//
// Created by dmytro2006 on 03/04/2025.
//

#ifndef UI_H
#define UI_H
#include "raylib.h"
#include <string>

namespace UI {
    class CentredText {
    public:
        CentredText(const std::string &text, Color color, Vector2 position, Vector2 size, float fontSize): color(color),
            text(text), fontSize(fontSize), position(position), size(size) {
        };

        CentredText(const std::string &text, Color color, Vector2 position, Vector2 size, float fontSize,
                    float spacing): color(color),
                                    text(text), fontSize(fontSize), position(position), size(size), spacing(spacing) {
        };


        ~CentredText() = default;

        void draw();

    private:
        Font font = GetFontDefault();
        Color color;
        std::string text;
        float fontSize;
        Vector2 position;
        Vector2 size;
        float spacing = 2;
    };

    class Button {
    public:
        Button(const std::string &text, Vector2 position, Vector2 size, Color textColor,
               Color backgroundColor, float fontSize): label(text, textColor, position, size, fontSize),
                                                       position(position),
                                                       size(size),
                                                       backgroundColor(backgroundColor),
                                                       outlineColor(WHITE),
                                                       outlineThickness(0),
                                                       outlined(false) {
        };

        Button(const std::string &text, Vector2 position, Vector2 size, Color textColor,
               Color backgroundColor, float fontSize,
               Color outlineColor, float outlineThickness): label(text, textColor, position, size, fontSize),
                                                            position(position),
                                                            size(size),
                                                            backgroundColor(backgroundColor),
                                                            outlineColor(outlineColor),
                                                            outlineThickness(outlineThickness),
                                                            outlined(true) {
        } ;

        ~Button() = default;

        void draw();

        bool checkMouseCollision(Vector2 mousePosition) const;

    private:
        CentredText label;
        Vector2 position;
        Vector2 size;
        Color backgroundColor;
        Color outlineColor;
        float outlineThickness;
        bool outlined;
    };
}

#endif //UI_H
