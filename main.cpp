/*
 *  Note on writing convention:
 *
 *  I got lazy (Frank) and never added using namespace std,
 *  so most of it is just me writing using std::f_n when necessary.
 *
 *  C:
 */

#include "Object.h"
#include "raylib.h"
#include "Objects.h"

#include <iostream>
#include <cctype>
#include <vector>
#include <string>

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

    /* raylib graphics + games library: open a window, size 1000x800 pixels */
    InitWindow(xPixels, yPixels, "hackathon example");
    // FPS = frame rate, 30 per second, caps the window rendering
    SetTargetFPS(60);

    Color textColor = BLACK;
    std::string message;

    std::string filePath = "items" + url + "knapsack.jpg"; 
    Object knapsack(filePath.c_str(), xPixels/2.f + 50, yPixels/2.f, xPixels/2, yPixels/2);

    std::vector<std::string> filePaths =
        {"items" + url + "apple.jpg",
         "items" + url + "banana.png",
         "items" + url + "peach.jpg",
         "items" + url + "water.jpg"};

    // using numbers provided by https://arpitbhayani.me/blogs/genetic-knapsack/ because I'm unoriginal :P
    std::vector<float> weight = { 1, 2, 4, 7 };
    std::vector<float> cost   = { 7, 4, 2, 5 };

    Objects items(filePaths); // list out into vector

    std::vector<Objects> itemsAdded(4); // Apples, Banana, Peaches, Water respectively

    int w = xPixels, h = yPixels;
    float mouse_xpos, mouse_ypos;

    while (!WindowShouldClose()) {
        mouse_xpos = GetMouseX();
        mouse_ypos = GetMouseY();

        BeginDrawing();
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

        EndDrawing();
    }

    knapsack.delObject();
    items.deactivateAll();

    CloseWindow();

    {
        using namespace std;

        for (int i = 0; i < itemsAdded.size(); i++) {
            cout << itemsAdded[i].getObjects()[0].getPath() << " picked: " << itemsAdded[i].getObjects().size() << endl;
            itemsAdded[i].deactivateAll();
        }

    }

    for (int i = 0; i < itemsAdded.size(); i++) {
        itemsAdded[i].deactivateAll();
    }

    std::cout << "Program ran successfully!" << std::endl;

    return 0;
}
