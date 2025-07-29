#ifndef INVENTORY_H
#define INVENTORY_H

#include "raylib.h"
#include <string>
#include <vector>

#include "item.h"

#define MAX_WEIGHT 100
#define MAX_ALLOWED_ORBS INT32_MAX

class Inventory {
    public:
        Inventory(int maxWeight, int currentWeight);

        bool hasItem(const std::string& itemName, int quantity);
        bool giveItem(const std::string& itemName, int quantity);
        bool removeItem(const std::string& itemName, int quantity);

    private:
        std::vector<Item> items;
        int maxWeight = MAX_WEIGHT;
        int currentWeight = 0;
};



#endif