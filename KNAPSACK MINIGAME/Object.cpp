#include "Object.h"
#include "raylib.h"
#include <vector>

Object::Object() {}

Object::Object(const char *filePath, float x, float y, int width, int height) {
    // query: "change image size in raylib" || model: Gemini
    Image image = LoadImage(filePath);
    ImageResize(&image, width, height);

    this->image = LoadTextureFromImage(image); // ex. "items\apple.jpg"
    UnloadImage(image);

    this->x = x; // set x-pos
    this->y = y; // set y-pos
    this->width = width;
    this->height = height;

    Object::centerAt(x, y);

    path = filePath;
}

void Object::resizeImage(float width, float height) {
    Image image = LoadImageFromTexture(this->image);

    ImageResize(&image, width, height);
    this->image = LoadTextureFromImage(image);

    this->width = width;
    this->height = height;

    UnloadImage(image); // free memory
}

void Object::repositionImage(float x, float y) {
    this->x = x;
    this->y = y;
}

std::vector<float> Object::getPosition() {
    return std::vector<float>{x, y};
}

std::vector<float> Object::getSize() {
    return std::vector<float>{width, height};
}

std::string Object::getPath() {
    return path;
}

void Object::updateImage(float x, float y, int width, int height) {

    if (width > -1 && height > -1) {
        resizeImage(width, height);
        this->width = width;
        this->height = height;
    }

    this->x = x;
    this->y = y;

    source = {x, y, (float)image.width, (float)image.height};

    DrawTexture(image, x, y, WHITE);
}


void Object::updateImage() {
    source = {x, y, (float)image.width, (float)image.height};

    DrawTexture(image, x, y, WHITE);
}

void Object::centerAt(float x, float y) {
    x -= width/2;
    y -= height/2;

    this->x = x;
    this->y = y;

    DrawTexture(image, x, y, WHITE);
}

Rectangle Object::hitBox() {
    return source;
}

void Object::delObject() {
    UnloadTexture(image);
}
