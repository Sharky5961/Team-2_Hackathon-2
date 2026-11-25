#ifndef OBJECT_H
#define OBJECT_H

#include "raylib.h"
#include <string>
#include <vector>

class Object {
    public:
        // Declerations
        Object();
        Object(const char *filePath, float x = 0, float y = 0, int width = 100, int height = 100); // doesn't need w, h

        // Getters
        std::vector<float> getPosition();
        std::vector<float> getSize();
        std::string getPath();

        // Back-end changes
        void resizeImage(float width, float height);
        void repositionImage(float x, float y); // DOES NOT OUTPUT

        // Front-end changes
        void updateImage(float x, float y, int width = -1, int height = -1); // only needs x, y
        void updateImage(); // overloading for a general refresh

        Rectangle hitBox();
        void centerAt(float x, float y);

        // Clean-up
        void delObject();


    private:
        Texture2D image;
        Rectangle source, destination;

        float width, height;
        float x, y;

        std::string path;

};

#endif
