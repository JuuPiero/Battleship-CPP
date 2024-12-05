#pragma once

enum ShipType {
    SUBMARINE,
    DESTROYER,
    CRUISER,
    AIRCRAFT_CARRIER
};
// Ship types = [1, 2, 3, 4]
struct Ship {
    int type;
    char direction;
    int x, y;
};