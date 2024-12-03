
#include <iostream>
#include <raylib.h>
#include <vector>
class Game {
public:
    bool win = false;
    int level;
    int enemyhealth;
    struct Player {
        int health;
        bool block;
        
    } player;

    Game(int health, int level, int block) {
        player.health = health;
        this->level = level;
        player.block = block;
    }

    void Reset(int health, int level, int block) {
        player.health = health;
        this->level = level;
        player.block = block;
    }

    void Draw() {
        // Логика отрисовки игрока
    }

    void Update() {
        // Логика обновления состояния игры
    }

    void Collision() {
        // Логика обработки столкновений
    }

    void Level(int level) {
        // Логика изменения уровня
    }
};
class Paddle {

public:
    int r_x;
    int r_y;
    int r_width;
    int r_height;
    float speed;
    void Draw() {
        DrawRectangle(r_x, r_y, r_width, r_height, BLUE);
    };
}

    int main()
    {
        InitWindow(1280, 1024, "Space Battle");
        SetTargetFPS(60);

        Game game = Game(10, 10, 20);
        int enemyhealth = 10;
        r_x = 10;
        r_y = 100;
        r_width = 30;
        r_height = 20;
        int start_timer;
        int level_timer = 10000;
        int level_count = 0;
        int count = 0;
        bool pause = false;
        int pause_timer = clock();
        bool defeat = false;
        int defeat_timer;
        bool start_game = false;
        bool start_game_preparation = false;
        bool new_game = false;
        int new_game_timer = 0;
        Texture2D field = LoadTexture(".\\field.png");
        Texture2D main_menu = LoadTexture(".\\main_menu.png");
        Texture2D button_exit = LoadTexture(".\\button_exit2.png");
        Texture2D button_start_game = LoadTexture(".\\button_start_game2.png");

        while (!(WindowShouldClose())) {
            BeginDrawing();
            if (start_game == false) {
                DrawTexture(main_menu, 0, 0, WHITE);
                DrawText("MAIN MENU", GetScreenWidth() / 2 - MeasureText("MAIN MENU", 20) / 2 - 290, GetScreenHeight() / 2 - 450, 120, WHITE);
                DrawRectangle(GetScreenWidth() / 2 - 400, GetScreenHeight() / 2 - 250, 800, 200, BLUE);
                DrawRectangle(GetScreenWidth() / 2 - 400, GetScreenHeight() / 2 + 100, 800, 200, BLUE);
                DrawTexture(button_start_game, GetScreenWidth() / 2 - 400, GetScreenHeight() / 2 - 250, WHITE);
                DrawTexture(button_exit, GetScreenWidth() / 2 - 400, GetScreenHeight() / 2 + 100, WHITE);

                if (CheckCollisionPointRec(GetMousePosition(), { float(GetScreenWidth()) / 2 - 400, float(GetScreenHeight()) / 2 - 250, 800, 200 }) and IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                    new_game = true;
                    new_game_timer = clock();
                }
                if (new_game == true and clock() - new_game_timer > 10) {
                    start_game = true;
                    start_game_preparation = false;
                }
                if (CheckCollisionPointRec(GetMousePosition(), { float(GetScreenWidth()) / 2 - 400, float(GetScreenHeight()) / 2 + 100, 800, 200 }) and IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                    exit(0);
                }
            }
            else if (start_game == true) {
                if (start_game_preparation == false) {
                    game.Reset(10, 10, 20);
                    start_game_preparation = true;
                }
                DrawTexture(field, 0, 0, WHITE);
                if (IsKeyDown(KEY_SPACE) and clock() - pause_timer > 300) {
                    pause_timer = clock();
                    if (pause == false) {
                        pause = true;
                    }
                    else if (pause == true) {
                        pause = false;
                    }
                }
                if (game.player.health > 0 and game.win == false) {
                    game.Draw();
                    DrawRectangle(GetScreenWidth() / 2 - 205, GetScreenHeight() - 55, 410, 20, GRAY);
                    DrawRectangle(GetScreenWidth() / 2 - 200, GetScreenHeight() - 50, 400, 10, WHITE);
                    DrawRectangle(GetScreenWidth() / 2 - 200, GetScreenHeight() - 50, game.player.health, 10, RED);
                    if (pause == true) {
                        DrawText("PAUSE", GetScreenWidth() / 2 - MeasureText("PAUSE", 20) / 2, GetScreenHeight() / 2, 30, WHITE);}
                    if (pause == false) {
                        game.Collision();
                        game.Update();
                        game.Level(game.level);

                        if (game.player.block == true) {
                            if (count == 0) {
                                start_timer = clock();
                                ++count;
                            }
                            else if (count == 1 and (clock() - start_timer) > 500) {
                                game.player.block = false;
                                count = 0;
                            }
                        }
                    }
   /*                 if (game.Chek_Enemy() == false) {
                        if (game.level == 1) {
                            DrawText("LEVEL 1 WIN", GetScreenWidth() / 2 - MeasureText("LEVEL 1 WIN", 20) / 2, GetScreenHeight() / 2 - 50, 30, WHITE);
                        }
                        else if (game.level == 2) {
                            DrawText("LEVEL 2 WIN", GetScreenWidth() / 2 - MeasureText("LEVEL 2 WIN", 20) / 2, GetScreenHeight() / 2 - 50, 30, WHITE);
                        }
                        else if (game.level == 3) {
                            DrawText("LEVEL 3 WIN", GetScreenWidth() / 2 - MeasureText("LEVEL 3 WIN", 20) / 2, GetScreenHeight() / 2 - 50, 30, WHITE);
                        }
                        else if (game.level == 4) {
                            DrawText("LEVEL 4 WIN", GetScreenWidth() / 2 - MeasureText("LEVEL 4 WIN", 20) / 2, GetScreenHeight() / 2 - 50, 30, WHITE);
                        }
                        else {
                            DrawText("WIN", GetScreenWidth() / 2 - MeasureText("WIN", 20) / 2, GetScreenHeight() / 2 - 50, 30, WHITE);
                        }
                        if (level_count == 0 and pause == false) {
                            level_timer = clock();
                            ++level_count;
                        }
                        if (clock() - level_timer > 3000 and pause == false) {
                            game.level += 1;
                            game.preparation = false;
                            level_count = 0;
                        }
                    }*/
                }
                else {
                    if (defeat == false) {
                        defeat = true;
                        defeat_timer = clock();
                    }
                    if (clock() - defeat_timer < 5) {
                        DrawText("DEFEAT", GetScreenWidth() / 2 - MeasureText("DEFEAT", 20) / 2, GetScreenHeight() / 2 - 50, 30, WHITE);
                    }
                    else {
                        DrawText("PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth() / 2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20) / 2 - 30, GetScreenHeight() / 2 - 50, 30, WHITE);
                        DrawText("PRESS [M] TO EXIT TO MAIN MENU", GetScreenWidth() / 2 - MeasureText("PRESS [M] TO EXIT TO MAIN MENU", 20) / 2 - 30, GetScreenHeight() / 2, 30, WHITE);
                        if (IsKeyDown(KEY_ENTER)) {
                            start_game_preparation = false;
                            pause = false;
                        }
                        else if (IsKeyDown(KEY_M)) {
                            start_game = false;
                            new_game = false;
                        }
                    }
                }
            }
            EndDrawing();
        }
    }

