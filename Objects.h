#ifndef OBJECTS_H
#define OBJECTS_H

#include "Object.h"
#include <string>
#include <vector>

class Objects {
    private:
        std::vector<Object> items;

    public:
        Objects();
        Objects(std::vector<std::string> filePaths, bool list = true); // if to list out

        void addItem(Object item);
        void deleteItem();

        void activateAll();
        void deactivateAll();
        std::vector<Object> getObjects();

};

#endif
