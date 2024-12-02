#include "bn_core.h"
#include <bn_vector.h>

#include "bn_regular_bg_items_bg_berylsroom.h"

struct ActionableItem
{
    int x;
    int action;
    bool automatic;
};

struct Room
{
    const bn::regular_bg_item &bg;
    const ActionableItem (&items)[64]; // Use reference to array
    int init_x;
    bool loops;
    bool fadedown;
};

enum Rooms
{
    ROOM_BEDROOM,
    ROOM_GRASS,
    ROOM_CONBINI,
    COUNT_ROOMS
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
    C_INITGRASS1,
    C_ENDOFDEMO,
    C_INITCONBINI,
    C_CON_COUNTER,
    C_CON_SODA,
    C_CON_CREAM,
    C_CON_CASTOR,
    C_CON_CAR,
    C_CON_DING,
    COUNT_CONVERSATIONS
};

// Define the actionable items as a constexpr array
constexpr ActionableItem room_items[COUNT_ROOMS][64] = {

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
    },

    // Grass
    {
        {1, C_INITGRASS1, true},
        {900, C_ENDOFDEMO, false}
    },

    // Conbini
    {
        {-240, C_INITCONBINI, true},
        {-298, C_CON_COUNTER, false},
        {9, C_CON_SODA, false},
        {230, C_CON_CREAM, false},
        {345, C_CON_CASTOR, false},
        {-495, C_CON_CAR, false},
        {-415, C_CON_DING, false}
    }
    
};

// Function to return a Room object
constexpr Room make_room(const bn::regular_bg_item &bg, const ActionableItem (&items)[64], int init_x, bool loops, bool fadedown)
{
    return Room{bg, items, init_x, loops, fadedown};
}

constexpr Room room_map(int room_no)
{
    constexpr ActionableItem empty_items[64] = {}; // Define the empty array inline

    switch (room_no)
    {
    case ROOM_BEDROOM:
        return make_room(bn::regular_bg_items::bg_berylsroom, room_items[ROOM_BEDROOM], -240, true, true);
    case ROOM_GRASS:
        return make_room(bn::regular_bg_items::bg_grass, room_items[ROOM_GRASS], 0, false, true);
    case ROOM_CONBINI:
        return make_room(bn::regular_bg_items::bg_conbini, room_items[ROOM_CONBINI], -240, true, true);
    default:
        return make_room(bn::regular_bg_items::bg_berylsroom, empty_items, 0, false, false);
    }
}

enum CUTSCENES
{
    C_2018,
    C_GASP,
    C_STARS,
    C_THX,
    C_S1
};

// 850
// 1400
// 2100