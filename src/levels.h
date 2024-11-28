#include "bn_core.h"
#include <bn_vector.h>

#include "bn_regular_bg_items_bg_berylsroom.h"

struct ActionableItem {
    int x;
    int action;
    bool automatic;
};

struct Room {
    const bn::regular_bg_item &bg;
    const ActionableItem (&items)[64]; // Use reference to array
    int init_x;
    bool loops;
};

enum Rooms {
    ROOM_BEDROOM
};

enum Conversations
{
    C_INITCONV,
    C_BED,
    C_INITCASTOR,
    C_BED_LOOP,
    C_BED_DESK,
    C_BED_SHELF,
    C_BED_CLOSET,
    C_BED_COUCH,
    C_BED_DOOR,
};

// Define the actionable items as a constexpr array
constexpr ActionableItem room_items[1][64] = {

    // Bedroom
    {
        {-240, C_INITCONV, true},
        {-240, C_BED, false},
        {64, C_INITCASTOR, true},
        {-480, C_BED_LOOP, true},
        {-76, C_BED_DESK, false},
        {24, C_BED_SHELF, false},
        {258, C_BED_CLOSET, false},
        {136, C_BED_COUCH, false},
        {-344, C_BED_DOOR, false}
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
            return make_room(bn::regular_bg_items::bg_berylsroom, room_items[ROOM_BEDROOM], -240, true);
        default:
            return make_room(bn::regular_bg_items::bg_berylsroom, empty_items, 0, 0);
    }
}
