#include <stdio.h>

// Define the structure
struct CharProperties {
    int width;
    int v_offset;
    int index;
};

// Create a constexpr function to initialize the properties for each character
constexpr CharProperties char_map(char ch) {
    switch (ch) {
        case 'A': return {15, 0, 0};
        case 'B': return {15, 0, 1};
        case 'C': return {17, 0, 2};
        case 'D': return {13, 0, 3};
        case 'E': return {15, 0, 4};
        case 'F': return {13, 0, 5};
        case 'G': return {16, 0, 6};
        case 'H': return {17, 0, 7};
        case 'I': return {3, 0, 8};
        case 'J': return {15, 0, 9};
        case 'K': return {14, 0, 10};
        case 'L': return {15, 0, 11};
        case 'M': return {19, 0, 12};
        case 'N': return {18, 0, 13};
        case 'O': return {15, 0, 14};
        case 'P': return {14, 0, 15};
        case 'Q': return {15, 0, 16};
        case 'R': return {16, 0, 17};
        case 'S': return {12, 0, 18};
        case 'T': return {14, 0, 19};
        case 'U': return {17, 0, 20};
        case 'V': return {15, 0, 21};
        case 'W': return {19, 0, 22};
        case 'X': return {18, 0, 23};
        case 'Y': return {13, 0, 24};
        case 'Z': return {16, 0, 25};
        case 'a': return {9, 0, 26};
        case 'b': return {9, 0, 27};
        case 'c': return {9, 0, 28};
        case 'd': return {9, 0, 29};
        case 'e': return {8, 0, 30};
        case 'f': return {9, 0, 31};
        case 'g': return {11, 9, 32};
        case 'h': return {9, 0, 33};
        case 'i': return {4, 0, 34};
        case 'j': return {4, 5, 35};
        case 'k': return {9, 0, 36};
        case 'l': return {7, 0, 37};
        case 'm': return {12, 0, 38};
        case 'n': return {9, 0, 39};
        case 'o': return {8, 0, 40};
        case 'p': return {7, 9, 41};
        case 'q': return {10, 9, 42};
        case 'r': return {8, 0, 43};
        case 's': return {8, 0, 44};
        case 't': return {9, 0, 45};
        case 'u': return {10, 0, 46};
        case 'v': return {10, 0, 47};
        case 'w': return {14, 0, 48};
        case 'x': return {10, 0, 49};
        case 'y': return {10, 0, 50};
        case 'z': return {9, 0, 51};
        case ',': return {4, 0, 52};
        case '.': return {3, 0, 53};
        case '\'': return {5, 0, 54};
        case '!': return {3, 0, 55};
        case '?': return {10, 0, 56};
        default: return {8, 0, 57};    // Space
    }
}

enum Characters {
    CH_BERYL,
    CH_CASTOR,
    CH_NONE
};

enum Emotions {
    SIT_NORMAL,
    SIT_CONFUSED,
    EMO_NORMAL,
    EMO_CONFUSED,
    EMO_SAD,
    EMO_SURPRISED,
};

enum Actions {
    BERYL_LEFT,
    BERYL_RIGHT,
};

struct DialogueLine {
    int sound_id;
    int ch_id;
    int emo_id;
    int action;
    const char *line;
};

const DialogueLine gamelines[64][64] = {
    {{0, CH_BERYL, SIT_CONFUSED, 0, "...My head..."},
     {0, CH_BERYL, SIT_NORMAL, 0, "..Where am I?"},
     {0, CH_BERYL, SIT_CONFUSED, 0, "...I don't even... remember who I am..."},
     {-1}}};

     