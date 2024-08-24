#pragma once
#include "../../src/Globals/hIncludes.h"

void SetConsoleTextColor(WORD color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}


struct Color
{
    int r, g, b, a;

    Color() : r(0), g(0), b(0), a(255) {}
    Color(int r, int g, int b, int a = 255) : r(r), g(g), b(b), a(a) {}

    static Color fromHSV(float h, float s, float v) {
        float p, q, t, ff;
        long i;
        Color out;

        if (s <= 0.0) {
            out.r = out.g = out.b = static_cast<int>(v * 255.0f);
            return out;
        }

        h /= 60.0f;
        i = static_cast<long>(h);
        ff = h - i;
        p = v * (1.0f - s);
        q = v * (1.0f - (s * ff));
        t = v * (1.0f - (s * (1.0f - ff)));

        switch (i) {
        case 0:
            out.r = static_cast<int>(v * 255.0f);
            out.g = static_cast<int>(t * 255.0f);
            out.b = static_cast<int>(p * 255.0f);
            break;
        case 1:
            out.r = static_cast<int>(q * 255.0f);
            out.g = static_cast<int>(v * 255.0f);
            out.b = static_cast<int>(p * 255.0f);
            break;
        case 2:
            out.r = static_cast<int>(p * 255.0f);
            out.g = static_cast<int>(v * 255.0f);
            out.b = static_cast<int>(t * 255.0f);
            break;
        case 3:
            out.r = static_cast<int>(p * 255.0f);
            out.g = static_cast<int>(q * 255.0f);
            out.b = static_cast<int>(v * 255.0f);
            break;
        case 4:
            out.r = static_cast<int>(t * 255.0f);
            out.g = static_cast<int>(p * 255.0f);
            out.b = static_cast<int>(v * 255.0f);
            break;
        case 5:
        default:
            out.r = static_cast<int>(v * 255.0f);
            out.g = static_cast<int>(p * 255.0f);
            out.b = static_cast<int>(q * 255.0f);
            break;
        }
        return out;
    }

    DWORD64 convertToARGB(Color c) {
        return ((DWORD64)c.a << 24) | ((DWORD64)c.r << 16) | ((DWORD64)c.g << 8) | (DWORD64)c.b;
    }

    // Function to convert DWORD64 to ImGui color
    void ConvertDWORD64ToImGuiColor(DWORD64 colorARGB, float outColor[4]) {
        outColor[0] = ((colorARGB >> 16) & 0xFF) / 255.0f;  // Red
        outColor[1] = ((colorARGB >> 8) & 0xFF) / 255.0f;   // Green
        outColor[2] = (colorARGB & 0xFF) / 255.0f;          // Blue
        outColor[3] = ((colorARGB >> 24) & 0xFF) / 255.0f;  // Alpha
    }

    // Function to convert ImGui color to DWORD64
    DWORD64 ConvertImGuiColorToDWORD64(const float color[4]) {
        return (static_cast<DWORD64>(color[3] * 255.0f) << 24) |
            (static_cast<DWORD64>(color[0] * 255.0f) << 16) |
            (static_cast<DWORD64>(color[1] * 255.0f) << 8) |
            (static_cast<DWORD64>(color[2] * 255.0f));
    }

    // Overload the << operator to print color
    friend std::ostream& operator<<(std::ostream& os, const Color& color) {
        os << "Color(R: " << color.r << ", G: " << color.g << ", B: " << color.b << ", A: " << color.a << ")";
        return os;
    }

};
