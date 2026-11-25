// headers here ...
#include <iostream>
#include "raylib.h"
#include <vector>
#include "Objects.h"

using namespace std;
/*
    Information for Explanation of Genetic Algorithms:
    https://www.ebsco.com/research-starters/computer-science/genetic-algorithm-ga/#bibliography
    https://www.geeksforgeeks.org/dsa/genetic-algorithms/

    Information for Historical Combinations:

    https://help-risk.lumivero.com/v8_13/en/Evolver/Optimization-Methods/Genetic-Algorithms/Genetic-Algorithms.htm
    https://link.springer.com/article/10.1007/s11831-025-10487-2
    https://en.wikipedia.org/wiki/Genetic_algorithm

*/

typedef enum GameScreen {TITLE, INTRODUCTION, PRE_MINIGAME, MINIGAME, NEXT_SCREEN} GameScreen;

std::string floatToString(float number, int digits = 3) {
    std::string strNumber = std::to_string(number);
    std::string temp = "";

    for (int i = 0; i < strNumber.size(); i++) {
        if (std::isdigit(strNumber[i])) {
            digits--;
        }
        temp += strNumber[i];

        if (digits <= 0) {
            return temp;
        }
    }

    return temp;

}

int main() {



    //--------------------------------------------------------------------------------------
    //
    string username;
    cout << "Hello, please enter the username you would like to use:" << endl;
    cin >> username;

    const int dnaWidth = 800;
    const int dnaHeight = 450;
    const int fps = 30;

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
    //--------------------------------------------------------------------------------------------

    /*
        Cleaning up for future Linux/Mac/Windows issues early
        by using user prompting
    */

    std::string opSys;

    std::cout << "What is your OS?" << std::endl;
    std::cin >> opSys;

    std::string temp = "";
    for (int i = 0; i < opSys.size(); i++) {
        temp += tolower(opSys[i]); // type matching
    }
    opSys = temp;

    std::string url = "";
    if (opSys.find("win") < opSys.size()) {
        url = "\\";
    }
    else {
        url = "/";
    }

    // START ACTUAL PROGRAM

    const int xPixels = 900, yPixels = 800;

    Color textColor = BLACK;
    std::string message;

    std::string filePath = "items" + url + "knapsack.jpg";

    std::vector<std::string> filePaths =
        {"items" + url + "apple.jpg",
         "items" + url + "banana.png",
         "items" + url + "peach.jpg",
         "items" + url + "water.jpg"};

    // using numbers provided by https://arpitbhayani.me/blogs/genetic-knapsack/ because I'm unoriginal :P
    std::vector<float> weight = { 1, 2, 4, 7 };
    std::vector<float> cost   = { 7, 4, 2, 5 };



    int w = xPixels, h = yPixels;
    float mouse_xpos, mouse_ypos;

    //

    const int screenWidth = 1100;
    const int screenHeight = 700;
    int worldPageNumber = 2;
    int localPageNumber = 0;

    InitWindow(screenWidth, screenHeight, "Slide Holder");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    Vector2 mousePos = {0.0, 0.0};

    Objects items(filePaths); // list out into vector
    Object knapsack(filePath.c_str(), xPixels/2.f + 50, yPixels/2.f, xPixels/2, yPixels/2);
    std::vector<Objects> itemsAdded(4); // Apples, Banana, Peaches, Water respectively

    Texture2D forWorld = LoadTexture("world-button.png");
    Texture2D backWorld = LoadTexture("backworld-button.png");

    Texture2D forShow1 = LoadTexture("exposlide1.png");
    Texture2D forShow2 = LoadTexture("exposlide2.png");
    Texture2D forShow3 = LoadTexture("exposlide3.png");
    Texture2D forShow4 = LoadTexture("exposlide4.png");
    Texture2D forShow5 = LoadTexture("exposlide5.png");

    Texture2D backShow1 = LoadTexture("histoslide1.png");
    Texture2D backShow2 = LoadTexture("histoslide2.png");
    Texture2D backShow3 = LoadTexture("histoslide3.png");
    Texture2D backShow4 = LoadTexture("histoslide4.png");
    Texture2D backShow5 = LoadTexture("histoslide5.png");
    Texture2D backShow6 = LoadTexture("histoslide6.png");

    Texture2D finalSlide = LoadTexture("final.png");

    Rectangle frameForWorld = {0, 0, (float)forWorld.width, (float)forWorld.height};
    Rectangle frameBackWorld = {0,0, (float)backWorld.width, (float)backWorld.height};

    Rectangle forSlideHolder = {0,0, (float)forShow1.width, (float)forShow1.height};

    Rectangle FWbounder = {(screenWidth)/1.5, screenHeight/8, (float)forWorld.width, (float)forWorld.height};
    Rectangle BWbounder = {(screenWidth)/4, screenHeight/8, (float)backWorld.width, (float)backWorld.height};
    Rectangle showBounder = {screenWidth/2 - forShow1.width/2.0f, screenHeight/2 - forShow1.height/2.0f, forShow1.width, forShow1.height};


    vector<Texture2D> textPhase2 = {backShow1, backShow2, backShow3, backShow4, backShow5, backShow6, forShow1, forShow2, forShow3, forShow4, forShow5, finalSlide};

    vector<Texture2D> whereTo = textPhase2;

    bool nextBatch = false;
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

//----------------------------------------START OF SLIDES------------------------------------------

    if (localPageNumber < 6 || nextBatch) { // special case before moving to explanation of Genetic algorithm slides
        // Update
        mousePos = GetMousePosition();
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            //int prevWorld = worldPageNumber
            int prevShow = localPageNumber;
            /*
            if(CheckCollisionPointRec(mousePos, FWbounder)){
                if(worldPageNumber != 4){
                    worldPageNumber++;
                }
                if(prevWorld != worldPageNumber){
                    localPageNumber = 0;
                    if(worldPageNumber == 1){
                        whereTo = textPhase1;
                    }
                    else if(worldPageNumber == 2){
                        whereTo = textPhase2;
                    }

                }
            }
                */
            if(CheckCollisionPointRec(mousePos, FWbounder)){
                if(localPageNumber != whereTo.size()-1){
                    localPageNumber++;
                }
            }
            else if(CheckCollisionPointRec(mousePos, BWbounder)){
                if(localPageNumber != 0){
                    localPageNumber--;
                }
            }
        }


        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(WHITE);
            DrawTextureRec(forWorld, frameForWorld, (Vector2){ FWbounder.x, FWbounder.y }, WHITE);
            DrawTextureRec(backWorld, frameBackWorld, (Vector2){BWbounder.x, BWbounder.y},WHITE);
            DrawTextureRec(whereTo[localPageNumber], forSlideHolder, (Vector2){showBounder.x, showBounder.y }, WHITE);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    else {

//----------------------------------------START OF DNA SEQUENCE MINIGAME AREA/INFORMATION------------------------------------------

        switch (current_screen) // update current screen
        {
            case TITLE:
            {
                SetWindowSize(dnaWidth, dnaHeight);
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
                    SetWindowSize(xPixels, yPixels);
                }
            } break;
            case MINIGAME:
            {
                if (placed_individual && IsKeyPressed(KEY_ENTER))
                {
                    current_screen = NEXT_SCREEN;
                    SetWindowSize(xPixels, yPixels);
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
                        (dnaWidth - MeasureText(title.c_str(), title_font_size)) / 2,
                        dnaHeight / 3.0f * 1,
                        title_font_size,
                        GREEN
                    );

                    string welcome_message = "Welcome aboard, " + username;
                    int welcome_message_font_size = 30;
                    DrawText(
                        welcome_message.c_str(),
                        (dnaWidth - MeasureText(welcome_message.c_str(), welcome_message_font_size)) / 2,
                        dnaHeight / 2.0f * 1,
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
                            (dnaWidth - MeasureText(blinking_text.c_str(), blinking_text_font_size)) / 2,
                            dnaHeight / 1.1f * 1,
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
                        dnaHeight / 10.0f * 1,
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
                            dnaHeight / 10.0f * 2,
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
                            dnaHeight / 10.0f * 5,
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
                                (dnaWidth - MeasureText(intro_text_4.c_str(), intro_text_4_font_size)) / 2,
                                dnaHeight / 1.1f * 1,
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
                        (dnaWidth - MeasureText(minigame_intro_text_1.c_str(), minigame_intro_text_1_font_size)) / 2,
                        dnaHeight / 3.0f * 1,
                        minigame_intro_text_1_font_size,
                        BLACK
                    );

                    if (frames_counter_minigame_intro > fps*2)
                    {
                        string minigame_intro_text_2 = "Let's try figuring this out by playing a simple minigame!";
                        int minigame_intro_text_2_font_size = 25;
                        DrawText(
                            minigame_intro_text_2.c_str(),
                            (dnaWidth - MeasureText(minigame_intro_text_2.c_str(), minigame_intro_text_2_font_size)) / 2,
                            dnaHeight / 2.0f * 1,
                            minigame_intro_text_2_font_size,
                            BLACK
                        );

                        // start button
                        float start_button_width = 250;
                        float start_button_height = 100;
                        Rectangle start_button = {
                            (dnaWidth - start_button_width) / 2.0f,
                            dnaHeight / 1.5f,
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
                            ((dnaWidth - start_button_width) / 2.0f) + (start_button_width - MeasureText(start_button_text.c_str(), start_button_font_size)) / 2,
                            (dnaHeight / 1.5f) + (start_button_height - start_button_font_size) / 2,
                            start_button_font_size,
                            BLACK
                        );

                        // skip button
                        float skip_button_width = 100;
                        float skip_button_height = 50;
                        Rectangle skip_button = {
                            dnaWidth / 1.2f,
                            dnaHeight / 1.2f,
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
                            (dnaWidth / 1.2f) + (skip_button_width - MeasureText(skip_button_text.c_str(), skip_button_font_size)) / 2,
                            (dnaHeight / 1.2f) + (skip_button_height - skip_button_font_size) / 2,
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
                                    (dnaWidth - MeasureText(minigame_text_5.c_str(), minigame_text_5_font_size)) / 2,
                                    dnaHeight / 1.1f * 1,
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


//----------------------------------------START OF KNAPSACK MINIGAME AREA------------------------------------------
    {

        mouse_xpos = GetMouseX();
        mouse_ypos = GetMouseY();

        ClearBackground(WHITE);

        knapsack.updateImage();

        // prints mouse position (x, y) on top left of screen
        if (0 <= mouse_xpos && mouse_xpos <= xPixels && 0 <= mouse_ypos && mouse_ypos <= yPixels) {
            message = "(" + std::to_string(mouse_xpos) + ", " + std::to_string(mouse_ypos) + ")";
            DrawText(message.c_str(), 40, 40, 24, textColor);
        }

// MAIN PURPOSE: Adding an object when their image is left-clicked
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            for (int i = 0; i < items.getObjects().size(); i++) {

                if (CheckCollisionPointRec(GetMousePosition(), items.getObjects().at(i).hitBox())) {

                    for (int j = 0; j < filePaths.size(); j++) { // looks for matching file-path

                        if (filePaths[j] == items.getObjects().at(i).getPath()) {
                            itemsAdded[j].addItem(Object(filePaths[j].c_str()));
                        }
                    }
                }
            }
        }

// MAIN PURPOSE: Removing an object when their image is right-clicked

        else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            for (int i = 0; i < items.getObjects().size(); i++) {

                if (CheckCollisionPointRec(GetMousePosition(), items.getObjects().at(i).hitBox())) {

                    for (int j = 0; j < filePaths.size(); j++) { // looks for matching file-path

                        if (filePaths[j] == items.getObjects().at(i).getPath()) {
                            itemsAdded[j].deleteItem();
                        }
                    }
                }
            }
        }

    // lists out ALL of the POSSIBLE OBJECTS (apples, water, peach, etc.)
        items.activateAll();

    // going to use this to PRINT out the COST and WEIGHT in parallel
        std::vector<float> pos, scale;

        for (int i = 0; i < items.getObjects().size(); i++) {
            pos   = items.getObjects().at(i).getPosition();
            scale = items.getObjects().at(i).getSize();

            message = "(" + floatToString(weight[i]) + "kg, $" + floatToString(cost[i]) + ")";
            DrawText(message.c_str(), pos[0] + scale[0] + 10, pos[1] + scale[1]/2, 20, BLUE);

        }

// BOTTOM UI to show how many TIMES clicked of EACH FRUIT
        int num = 300;
        for (int i = 0; i < itemsAdded.size()/2; i++) {

            std::string message1 = filePaths[i]  + " picked: " + std::to_string(itemsAdded[i].getObjects().size());
            std::string message2 = filePaths[i+2] + " picked: " + std::to_string(itemsAdded[i+2].getObjects().size());
            DrawText(message1.c_str(), 200 + num * i, 600, 20, BLACK);
            DrawText(message2.c_str(), 200 + num * i, 700, 20, BLACK);

        }

// MAIN PURPOSE: User tracks their items in relation to cap ( > 15 kg ) and total cost
        int freq;
        float total_cost = 0, total_kg = 0;

        for (int i = 0; i < itemsAdded.size(); i++) {
            freq = itemsAdded[i].getObjects().size(); // freq of item

            total_cost += cost.at(i) * freq;
            total_kg   += weight.at(i) * freq;
        }

        message = floatToString(total_kg) + "kg out of 15kg Limit \n\n" + "\t\tCost: $" + floatToString(total_cost);
        DrawText(message.c_str(), xPixels-300, 150, 24, RED);


        if (total_kg >= 15) {
            nextBatch = true;
            SetWindowSize(screenWidth, screenHeight);

        }

                    }
                } break;
            }
        EndDrawing();
    }


    }

    knapsack.delObject();
    items.deactivateAll();

    CloseWindow();

    for (int i = 0; i < itemsAdded.size(); i++) {
        itemsAdded[i].deactivateAll();
    }

    return 0;
}
