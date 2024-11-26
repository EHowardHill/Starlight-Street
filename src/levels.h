#include "bn_core.h"
#include <bn_vector.h>

#include "bn_regular_bg_items_bg_berylsroom.h"

struct ActionableItem {
    int x;
    int action;
    bool singleuse;
};

struct Room {
    const bn::regular_bg_item &bg;
    const ActionableItem (&items)[64]; // Use reference to array
    int init_x;
    int init_action;
};

enum Rooms {
    ROOM_BEDROOM
};

enum Conversations
{
    C_TEST0,
    C_INITCONV,
    C_BED,
    C_INITCASTOR
};

// Define the actionable items as a constexpr array
constexpr ActionableItem room_items[1][64] = {

    // Bedroom
    {
        {-64, C_BED, false},
        {64, C_TEST0, false}
    }
};

// Function to return a Room object
constexpr Room make_room(const bn::regular_bg_item &bg, const ActionableItem (&items)[64], int init_x, int init_action) {
    return Room{bg, items, init_x, init_action};
}

constexpr Room room_map(int room_no) {
    constexpr ActionableItem empty_items[64] = {}; // Define the empty array inline
    switch (room_no) {
        case ROOM_BEDROOM:
            return make_room(bn::regular_bg_items::bg_berylsroom, room_items[ROOM_BEDROOM], -64, C_INITCONV);
        default:
            return make_room(bn::regular_bg_items::bg_berylsroom, empty_items, 0, 0);
    }
}
