#include <iostream>
#include "raylib.h"
using namespace std;

// The code to switch between screens was adapted from:
// https://www.raylib.com/examples/core/loader.html?name=core_basic_screen_manager
typedef enum GameScreen {TITLE, INTRODUCTION, MINIGAME_INTRO, MINIGAME, NEXT} GameScreen;

int main() {

    string username;
    cout << "Hello, please enter the username you would like to use:" << endl;
    cin >> username;

    const int screenWidth = 800;
    const int screenHeight = 450;
    const int fps = 30;

    InitWindow(screenWidth, screenHeight, "hackathon");
    SetTargetFPS(fps);
    GameScreen current_screen = TITLE;  // the starting screen is TITLE
    int frames_counter_title = 0;
    int frames_counter_intro = 0;
    int frames_counter_minigame_intro = 0;

    while (!WindowShouldClose())
    {
        switch (current_screen) // update screen
        {
            case TITLE:
            {
                if (IsKeyPressed(KEY_ENTER))
                {
                    current_screen = INTRODUCTION;
                }
            } break;
            case INTRODUCTION:
            {
                if (IsKeyPressed(KEY_ENTER))
                {
                    current_screen = MINIGAME_INTRO;
                }
            } break;
            case MINIGAME_INTRO:
            {
                if (IsKeyPressed(KEY_ENTER))
                {
                    current_screen = MINIGAME;
                }
            } break;
            case MINIGAME:
            {
                if (IsKeyPressed(KEY_ENTER))
                {
                    current_screen = NEXT;
                }
            } break;
            case NEXT:
            {

            } break;
            default: break;
        }

        BeginDrawing();
            switch (current_screen)
            {
                case TITLE:
                {
                    ClearBackground(BLACK);

                    string title = "Bio-Inspired Computing: Genetic Algorithms";
                    int title_font_size = 35;
                    DrawText(
                        title.c_str(),
                        (screenWidth - MeasureText(title.c_str(), title_font_size)) / 2,
                        screenHeight / 3.0f * 1,
                        title_font_size, 
                        GREEN
                    );

                    string welcome_message = "Welcome aboard, " + username;
                    int welcome_message_font_size = 30;
                    DrawText(
                        welcome_message.c_str(),
                        (screenWidth - MeasureText(welcome_message.c_str(), welcome_message_font_size)) / 2,
                        screenHeight / 2.0f * 1,
                        welcome_message_font_size, 
                        GREEN
                    );

                    string blinking_text = "PRESS ENTER TO CONTINUE";
                    int blinking_text_font_size = 15;
                    frames_counter_title++;
                    if (((frames_counter_title / fps) % 2) == 0)
                    {
                        DrawText(
                            blinking_text.c_str(),
                            (screenWidth - MeasureText(blinking_text.c_str(), blinking_text_font_size)) / 2,
                            screenHeight / 1.1f * 1,
                            blinking_text_font_size,
                            WHITE
                        );
                    }
                } break;

                case INTRODUCTION:
                {
                    ClearBackground(RAYWHITE);

                    frames_counter_intro++;

                    string intro_text_1 = "Hey " + username + "!";
                    int intro_text_1_font_size = 20;
                    DrawText(
                        intro_text_1.c_str(),
                        20,
                        screenHeight / 10.0f * 1,
                        intro_text_1_font_size,
                        BLACK
                    );
                    
                    if (frames_counter_intro > fps)
                    {
                        string intro_text_2 = "Genetic algorithms are a type of biologically-inspired computation\ntechnique, which are designed to mimic processes found in nature,\naimed to solve complex optimization problems.";
                        int intro_text_2_font_size = 20;
                        DrawText(
                            intro_text_2.c_str(),
                            20,
                            screenHeight / 10.0f * 2,
                            intro_text_2_font_size,
                            BLACK
                        );
                    }

                    if (frames_counter_intro > fps*4)   // fix: add more information, add visualization
                    {
                        string intro_text_3 = "Did you know that Amazon _?";
                        int intro_text_3_font_size = 20;
                        DrawText(
                            intro_text_3.c_str(),
                            20,
                            screenHeight / 10.0f * 4,
                            intro_text_3_font_size,
                            BLACK
                        );
                    }
                    
                    if (frames_counter_intro > fps*6)
                    {
                        string intro_text_4 = "PRESS ENTER TO CONTINUE";
                        int intro_text_4_font_size = 15;
                        if (((frames_counter_intro / fps) % 2) == 0)
                        {
                            DrawText(
                                intro_text_4.c_str(),
                                (screenWidth - MeasureText(intro_text_4.c_str(), intro_text_4_font_size)) / 2,
                                screenHeight / 1.1f * 1,
                                intro_text_4_font_size,
                                BLACK
                            );
                        }
                    }

                } break;

                case MINIGAME_INTRO:
                {
                    ClearBackground(RAYWHITE);

                    frames_counter_minigame_intro++;

                    string minigame_intro_text_1 = "But what really is a Genetic Algorithm?";   // or "what does biologically-inspired mean?"
                    int minigame_intro_text_1_font_size = 35;
                    DrawText(
                        minigame_intro_text_1.c_str(),
                        20,
                        screenHeight / 3.0f * 1,
                        minigame_intro_text_1_font_size,
                        BLACK
                    );

                    if (frames_counter_minigame_intro > fps)
                    {
                        string minigame_intro_text_2 = "Let's try figuring this out using a simple example of where it came from!"; // maybe remove "of where it came from"?
                        int minigame_intro_text_2_font_size = 20;
                        DrawText(
                            minigame_intro_text_2.c_str(),
                            20,
                            screenHeight / 2.0f * 1,
                            minigame_intro_text_2_font_size,
                            BLACK
                        );
                    }

                    //TO-DO: add START and SKIP buttons


                } break;

                case MINIGAME:
                {
                    ClearBackground(RAYWHITE);

                } break;

                case NEXT:
                {
                    ClearBackground(RAYWHITE);

                } break;
            }
        EndDrawing();
    }

    return 0;
}