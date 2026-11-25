// headers here ...
#include <iostream>
#include "raylib.h"
#include <vector>
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
int main() {
    
    const int screenWidth = 1100;
    const int screenHeight = 700;
    int worldPageNumber = 2;
    int localPageNumber = 0;

     InitWindow(screenWidth, screenHeight, "Slide Holder");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    Vector2 mousePos = {0.0, 0.0};

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
    //Texture2D backShow = LoadTexture("next-button.png");

    Rectangle frameForWorld = {0, 0, (float)forWorld.width, (float)forWorld.height};
    Rectangle frameBackWorld = {0,0, (float)backWorld.width, (float)backWorld.height};

    Rectangle forSlideHolder = {0,0, (float)forShow1.width, (float)forShow1.height};

    Rectangle FWbounder = {(screenWidth)/1.5, screenHeight/8, (float)forWorld.width, (float)forWorld.height};
    Rectangle BWbounder = {(screenWidth)/4, screenHeight/8, (float)backWorld.width, (float)backWorld.height};
    Rectangle showBounder = {screenWidth/2 - forShow1.width/2.0f, screenHeight/2 - forShow1.height/2.0f, forShow1.width, forShow1.height};


    vector<Texture2D> textPhase1 = {forShow1, forShow2, forShow3, forShow4, forShow5};
         
    vector<Texture2D> textPhase2 = {backShow1, backShow2, backShow3, backShow4, backShow5};

    vector<Texture2D> whereTo = textPhase2;
   
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
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


        //----------------------------------------------------------------------------------
    


    return 0;
}