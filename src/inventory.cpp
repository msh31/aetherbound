#include "inventory.h"

Inventory::Inventory(int maxWeight, int currentWeight) {
    this->maxWeight = maxWeight;
    this->currentWeight = currentWeight;
}

bool Inventory::giveItem(const std::string& itemName, int quantity) {
    return false;
}
