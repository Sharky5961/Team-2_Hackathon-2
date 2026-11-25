// headers here ...
#include <iostream>
#include "raylib.h"
#include <vector>
using namespace std;

int main() {
    
    const int screenWidth = 960;
    const int screenHeight = 540;
    int worldPageNumber = 0;
    int localPageNumber = 0;

     InitWindow(screenWidth, screenHeight, "Slide Holder");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    Vector2 mousePos = {0.0, 0.0};

    Texture2D forWorld = LoadTexture("world-button.png");
    //Texture2D backWorld = LoadTexture("world-button.png");

    Texture2D forShow1 = LoadTexture("expo-slide1.png");
    Texture2D forShow2 = LoadTexture("expo-slide2.png");
    Texture2D forShow3 = LoadTexture("expo-slide3.png");
    Texture2D forShow4 = LoadTexture("expo-slide4.png");
    Texture2D forShow5 = LoadTexture("expo-slide5.png");

    Texture2D backShow1 = LoadTexture("expo-slide1.png");
    Texture2D backShow2 = LoadTexture("expo-slide2.png");
    Texture2D backShow3 = LoadTexture("expo-slide3.png");
    Texture2D backShow4 = LoadTexture("expo-slide4.png");
    Texture2D backShow5 = LoadTexture("expo-slide5.png");
    //Texture2D backShow = LoadTexture("next-button.png");

    Rectangle frameForWorld = {0, 0, (float)forWorld.width, (float)forWorld.height};
    Rectangle slideHolder = {0,0, (float)forShow1.width, (float)forShow1.height};

    Rectangle FWbounder = {(screenWidth)/1.5, screenHeight/4, (float)forWorld.width, (float)forWorld.height};
    //Rectangle BWbounder = ();
    Rectangle FSBounder = {screenWidth/2 - forShow1.width/2.0f, screenHeight/2 - forShow1.height/2.0f, forShow1.width, forShow1.height};
    //Rectangle BSbounder = ();


    vector<Texture2D> textPhase1 = {forShow1, forShow2, forShow3, forShow4, forShow5};
         
    vector<Texture2D> textPhase2 = {backShow1, backShow2, backShow3, backShow4, backShow5};

    vector<Texture2D> whereTo = textPhase1;
   
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
                if(prevShow != localPageNumber){
                    
                }
            }
        }
        

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BEIGE);
        DrawTextureRec(forWorld, frameForWorld, (Vector2){ FWbounder.x, FWbounder.y }, WHITE);
        DrawTextureRec(whereTo[localPageNumber], slideHolder, (Vector2){FSBounder.x, FSBounder.y }, WHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }


        //----------------------------------------------------------------------------------
    


    return 0;
}