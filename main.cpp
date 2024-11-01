#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include <chrono>

#include "logic_inst.h"

const int SCREEN_WIDTH = 200;
const int SCREEN_HEIGHT = 300;

// 定义七段数码管每个段的位置
const std::vector<SDL_Rect> segmentRects = {
    { 50, 20, 100, 20 },   // Top
    { 150, 40, 20, 100 },  // Top-right
    { 150, 160, 20, 100 }, // Bottom-right
    { 50, 260, 100, 20 },  // Bottom
    { 30, 160, 20, 100 },  // Bottom-left
    { 30, 40, 20, 100 },   // Top-left
    { 50, 140, 100, 20 }   // Middle
};

// 绘制数字
void drawDigit(SDL_Renderer* renderer, bool v[7]) {
    for (int i = 0; i < 7; ++i) {
        if (v[i]) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // 红色段
            SDL_RenderFillRect(renderer, &segmentRects[i]);
        }
    }
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Seven Segment Display",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool quit = false;
    SDL_Event e;

    int digit = 8;  // 显示数字8
    auto start_time = std::chrono::steady_clock::now();
    auto end_time = std::chrono::steady_clock::now();

    logic_inst logic_inst;
    bool v[7];

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
        if (dur > 500) {
            digit = (digit + 1) % 10;

            logic_inst.run(digit, v);

            start_time = end_time;
        }
        end_time = std::chrono::steady_clock::now();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        drawDigit(renderer, v);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
