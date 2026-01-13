#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <cmath>

struct ColorRGB {
    Uint8 r, g, b;
    ColorRGB(Uint8 r = 0, Uint8 g = 0, Uint8 b = 0) : r(r), g(g), b(b) {}
    ColorRGB operator/(int divisor) const {
        return ColorRGB(r / divisor, g / divisor, b / divisor);
    }
};

const ColorRGB RGB_Red(255, 0, 0);
const ColorRGB RGB_Green(0, 255, 0);
const ColorRGB RGB_Blue(0, 0, 255);
const ColorRGB RGB_White(255, 255, 255);
const ColorRGB RGB_Yellow(255, 255, 0);

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;
SDL_Texture *texture = nullptr;
Uint32 *pixels = nullptr;
int w, h;
bool shouldExit = false;

void screen(int width, int height, int flags, const char *title) {
    w = width;
    h = height;
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    pixels = new Uint32[width * height];
    memset(pixels, 0, width * height * sizeof(Uint32));
}

bool done() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            shouldExit = true;
        }
    }
    return shouldExit;
}

Uint32 colorToUint32(ColorRGB c) {
    return (0xFF << 24) | (c.r << 16) | (c.g << 8) | c.b;
}

void verLine(int x, int drawStart, int drawEnd, ColorRGB color) {
    Uint32 col = colorToUint32(color);
    for (int y = drawStart; y <= drawEnd; y++) {
        if (y >= 0 && y < h) {
            pixels[y * w + x] = col;
        }
    }
}

Uint32 getTicks() {
    return SDL_GetTicks();
}

void print(double fps) {
    // Simple FPS counter (can be enhanced)
    std::cout << "FPS: " << fps << std::endl;
}

void redraw() {
    SDL_UpdateTexture(texture, nullptr, pixels, w * sizeof(Uint32));
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}

void cls() {
    memset(pixels, 0, w * h * sizeof(Uint32));
}

bool keys[512] = {false};

void readKeys() {
    const Uint8 *keystate = SDL_GetKeyboardState(nullptr);
    for (int i = 0; i < 512; i++) {
        keys[i] = keystate[i];
    }
}

bool keyDown(SDL_Keycode key) {
    const Uint8 *keystate = SDL_GetKeyboardState(nullptr);
    return keystate[SDL_GetScancodeFromKey(key)];
}

#endif
