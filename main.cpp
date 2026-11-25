#include <iostream>
#include "raylib.h"
using namespace std;

// The code to switch between screens was adapted from:
// https://www.raylib.com/examples/core/loader.html?name=core_basic_screen_manager
typedef enum GameScreen {TITLE, INTRODUCTION, PRE_MINIGAME, MINIGAME, NEXT_SCREEN} GameScreen;

int main() {

    string username;
    cout << "Hello, please enter the username you would like to use:" << endl;
    cin >> username;

    const int screenWidth = 800;
    const int screenHeight = 450;
    const int fps = 30;

    InitWindow(screenWidth, screenHeight, "hackathon");
    SetTargetFPS(fps);

    // starting screen is TITLE
    GameScreen current_screen = TITLE;

    // frame counters need to be initialized before the while loop, otherwise the frame counter never counts past 0
    int frames_counter_title = 0;
    int frames_counter_intro = 0;
    int frames_counter_minigame_intro = 0;
    int frames_counter_minigame = 0;

    // variables to check whether mouse is hovering over START or SKIP buttons in MINIGAME_INTRO
    bool hovering_over_start = false;
    bool hovering_over_skip = false;

    // variables and initialization for MINIGAME
    Rectangle individual_static = {40, 100, 50, 50};
    Rectangle individual = {720, 20, 50, 50};
    Rectangle individual_area =  {35, 215, 60, 60};
    Rectangle individual_static_mutate = {40, 100, 50, 50};
    bool grabbing_individual = false;
    bool placed_individual = false;
    Vector2 mouse_offset = { 0.0f, 0.0f };
    bool minigame_complete = false;
    bool mutation = false;

    while (!WindowShouldClose())
    {
        switch (current_screen) // update current screen
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
                    current_screen = PRE_MINIGAME;
                }
            } break;
            case PRE_MINIGAME:
            {
                if (hovering_over_start == true && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    current_screen = MINIGAME;
                }
                if (hovering_over_skip == true && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    current_screen = NEXT_SCREEN;
                }
            } break;
            case MINIGAME:
            {
                if (placed_individual && IsKeyPressed(KEY_ENTER))
                {
                    current_screen = NEXT_SCREEN;
                }
            } break;
            case NEXT_SCREEN:
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
                        // string intro_text_2 = "Genetic algorithms are a type of biologically-inspired computation\ntechnique, which are designed to mimic processes found in nature,\naimed to solve complex optimization problems.";
                        string intro_text_2 = "Genetic algorithms are a type of biologically-inspired computation\ntechnique aimed to solve complex optimization problems.";
                        int intro_text_2_font_size = 20;
                        DrawText(
                            intro_text_2.c_str(),
                            20,
                            screenHeight / 10.0f * 2,
                            intro_text_2_font_size,
                            BLACK
                        );
                    }

                    if (frames_counter_intro > fps*4)
                    {
                        string intro_text_3 = "Did you know?\n\nAmazon uses genetic algorithms to optimize their delivery routes.\n\nThey determine the most efficient path for delivery drivers by taking\ninto account variables such as number of delivery stops, the distance\nbetween these stops, traffic, etc.";
                        // more info about Amazon's genetic algorithms can be found below:
                        // https://aws.amazon.com/blogs/machine-learning/using-genetic-algorithms-on-aws-for-optimization-problems/
                        // https://github.com/aws-samples/genetic-algorithm-on-aws
                        int intro_text_3_font_size = 20;
                        DrawText(
                            intro_text_3.c_str(),
                            20,
                            screenHeight / 10.0f * 5,
                            intro_text_3_font_size,
                            DARKBLUE
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

                case PRE_MINIGAME:
                {
                    ClearBackground(RAYWHITE);

                    frames_counter_minigame_intro++;

                    string minigame_intro_text_1 = "But what does biologically-inspired mean?";
                    int minigame_intro_text_1_font_size = 35;
                    DrawText(
                        minigame_intro_text_1.c_str(),
                        (screenWidth - MeasureText(minigame_intro_text_1.c_str(), minigame_intro_text_1_font_size)) / 2,
                        screenHeight / 3.0f * 1,
                        minigame_intro_text_1_font_size,
                        BLACK
                    );

                    if (frames_counter_minigame_intro > fps*2)
                    {
                        string minigame_intro_text_2 = "Let's try figuring this out by playing a simple minigame!";
                        int minigame_intro_text_2_font_size = 25;
                        DrawText(
                            minigame_intro_text_2.c_str(),
                            (screenWidth - MeasureText(minigame_intro_text_2.c_str(), minigame_intro_text_2_font_size)) / 2,
                            screenHeight / 2.0f * 1,
                            minigame_intro_text_2_font_size,
                            BLACK
                        );

                        // start button
                        float start_button_width = 250;
                        float start_button_height = 100;
                        Rectangle start_button = {
                            (screenWidth - start_button_width) / 2.0f,
                            screenHeight / 1.5f,
                            start_button_width,
                            start_button_height
                        };
                        string start_button_text = "START";
                        int start_button_font_size = 50;
                        int start_button_thickness = 3;
                        DrawRectangleRec(start_button, SKYBLUE);
                        DrawRectangleLinesEx(start_button, start_button_thickness, BLACK);
                        DrawText(
                            start_button_text.c_str(),
                            ((screenWidth - start_button_width) / 2.0f) + (start_button_width - MeasureText(start_button_text.c_str(), start_button_font_size)) / 2,
                            (screenHeight / 1.5f) + (start_button_height - start_button_font_size) / 2,
                            start_button_font_size,
                            BLACK
                        );

                        // skip button
                        float skip_button_width = 100;
                        float skip_button_height = 50;
                        Rectangle skip_button = {
                            screenWidth / 1.2f,
                            screenHeight / 1.2f,
                            skip_button_width,
                            skip_button_height
                        };
                        string skip_button_text = "SKIP";
                        int skip_button_font_size = 25;
                        int skip_button_thickness = 2;
                        DrawRectangleRec(skip_button, LIGHTGRAY);
                        DrawRectangleLinesEx(skip_button, skip_button_thickness, BLACK);
                        DrawText(
                            skip_button_text.c_str(),
                            (screenWidth / 1.2f) + (skip_button_width - MeasureText(skip_button_text.c_str(), skip_button_font_size)) / 2,
                            (screenHeight / 1.2f) + (skip_button_height - skip_button_font_size) / 2,
                            skip_button_font_size,
                            BLACK
                        );

                        // check if mouse is currently hovering over the start or skip buttons
                        Vector2 mouse_position = GetMousePosition();
                        hovering_over_start = CheckCollisionPointRec(mouse_position, start_button);
                        hovering_over_skip = CheckCollisionPointRec(mouse_position, skip_button);
                    }
                } break;

                case MINIGAME:
                {
                    ClearBackground(RAYWHITE);

                    // The code to drag and drop was adapted from:
                    // https://www.raylib.com/examples/shapes/loader.html?name=shapes_drag_puzzle
                    for (int i = 0; i < 4; i++)
                    {
                        individual_static.y = 100 + (i * 60);
                        if (i != 2)
                        {
                            if (i % 2 == 0)
                            {
                                DrawRectangleRec(individual_static, ORANGE);
                            }
                            else
                            {
                                DrawRectangleRec(individual_static, BLUE);
                            }
                        }
                        else{}
                    }
                    if (!mutation)
                    {
                        individual_static_mutate.y = 100 + (4 * 60);
                        DrawRectangleRec(individual_static_mutate, ORANGE);
                    }
                    else
                    {
                        individual_static_mutate.x = 40 + 10;
                        individual_static_mutate.y = 100 + (4 * 60) + 10;
                        individual_static_mutate.width = 30;
                        individual_static_mutate.height = 30;
                        DrawRectangleRec(individual_static_mutate, ORANGE);
                    }

                    Vector2 mouse_position = GetMousePosition();
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mouse_position, individual))
                    {
                        grabbing_individual = true;
                        mouse_offset = (Vector2) { individual.x - mouse_position.x, individual.y - mouse_position.y };
                    }
                    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && grabbing_individual)
                    {
                        grabbing_individual = false;
                    }
                    if (grabbing_individual)
                    {
                        individual.x = mouse_position.x + mouse_offset.x;
                        individual.y = mouse_position.y + mouse_offset.y;
                    }
                    Rectangle individual_collision = GetCollisionRec(individual_area, individual);
                    if (individual_collision.width == individual.width && individual_collision.height == individual.height)
                    {
                        placed_individual = true;
                        minigame_complete = true;
                    }
                    DrawRectangleLinesEx(individual_area, 2.0f, placed_individual ? GREEN : RED);
                    DrawRectangleRec(individual, ORANGE);

                    if (minigame_complete == false)
                    {
                        string minigame_text_1 = "Drag and drop the square on the right into the correct spot!";
                        int intro_text_1_font_size = 20;
                        DrawText(
                            minigame_text_1.c_str(),
                            10,
                            10,
                            intro_text_1_font_size,
                            GRAY
                        );
                    }
                    else
                    {
                        frames_counter_minigame++;
                        string minigame_text_1 = "Biologically-inspired techniques mimic processes found in nature.\n\nGenetic ALgorithm is an example of one.";
                        int minigame_text_1_font_size = 20;
                        DrawText(
                            minigame_text_1.c_str(),
                            10,
                            10,
                            minigame_text_1_font_size,
                            BLACK
                        );

                        if (frames_counter_minigame > fps*3)
                        {
                            string minigame_text_2 = "You can think of this sequence as a small POPULATION.\nThere are currently only 2 possibile variations in the population,\norange and blue.";
                            int minigame_text_2_font_size = 20;
                            DrawText(
                                minigame_text_2.c_str(),
                                120,
                                140,
                                minigame_text_2_font_size,
                                BLACK
                            );
                        }
                        if (frames_counter_minigame > fps*6)
                        {
                            string minigame_text_3 = "We can introduce more DIVERSITY in our population by adding\nnew variations.";
                            int minigame_text_3_font_size = 20;
                            DrawText(
                                minigame_text_3.c_str(),
                                120,
                                250,
                                minigame_text_3_font_size,
                                BLACK
                            );
                        }

                        if (frames_counter_minigame > fps*8)
                        {
                            individual_static.y = 100 + (0 * 60);
                            DrawRectangleRec(individual_static, GREEN);
                            individual_static.y = 100 + (3 * 60);
                            DrawRectangleRec(individual_static, PURPLE);
                        }

                        if (frames_counter_minigame > fps*10)
                        {
                            mutation = true;
                        }

                        if (frames_counter_minigame > fps*11)
                        {
                            mutation = true;
                            string minigame_text_4 = "Hmm, it looks like the last individual randomly MUTATED.\n This also introduces more diversity.";
                            int minigame_text_4_font_size = 20;
                            DrawText(
                                minigame_text_4.c_str(),
                                120,
                                350,
                                minigame_text_4_font_size,
                                BLACK
                            );
                        }

                        if (frames_counter_minigame > fps*12)
                        {
                            string minigame_text_5 = "PRESS ENTER TO CONTINUE";
                            int minigame_text_5_font_size = 15;
                            if (((frames_counter_minigame / fps) % 2) == 0)
                            {
                                DrawText(
                                    minigame_text_5.c_str(),
                                    (screenWidth - MeasureText(minigame_text_5.c_str(), minigame_text_5_font_size)) / 2,
                                    screenHeight / 1.1f * 1,
                                    minigame_text_5_font_size,
                                    BLACK
                                );
                            }
                        }
                    }
                } break;

                case NEXT_SCREEN:
                {
                    ClearBackground(RAYWHITE);

                } break;
            }
        EndDrawing();
    }

    return 0;
}