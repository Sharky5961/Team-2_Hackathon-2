#include "Objects.h"
#include "Object.h"

Objects::Objects() {}

Objects::Objects(std::vector<std::string> filePaths, bool list) {
    if (list == true) {
        int num = 150;

        for (int i = 0; i < filePaths.size(); i++) {
            // query: string to const char* c++ || model: Gemini
            Object temp(filePaths[i].c_str(), 100, num);

            items.push_back(temp);

            num += 100;
        }
    }

    for (int i = 0; i < filePaths.size(); i++) {
        Object temp(filePaths[i].c_str(), 100, 200); // pushes all to same area
    }
}

void Objects::addItem(Object item) {
    items.push_back(item);
}

void Objects::deleteItem() {
    if (items.size() > 0) {
        items.resize(items.size()-1);
    }
}

void Objects::activateAll() {
    for (int i = 0; i < items.size(); i++) {
        items.at(i).updateImage();
    }
}

void Objects::deactivateAll() {
    for (int i = 0; i < items.size(); i++) {
        items.at(i).delObject();
    }
}

std::vector<Object> Objects::getObjects() {
    return items;
}
