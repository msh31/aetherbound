#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
    public:
        Item(int weight, const std::string& description);

        int getWeight() const { return weight; }

        std::string getDescription() const { return description; }

    private:
        int weight;
        std::string description;
};

#endif