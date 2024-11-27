/*
 * Butano Engine - Copyright (c) 2020-2024 Gustavo Valiente gustavo.valiente@protonmail.com
 * zlib License, see LICENSE file.
 */

#include "bn_core.h"
#include "bn_log.h"
#include <bn_fixed.h>
#include <bn_vector.h>
#include "bn_display.h"
#include <bn_keypad.h>
#include "bn_blending.h"
#include <bn_sprite_ptr.h>
#include <bn_camera_ptr.h>
#include <bn_sprite_animate_actions.h>
#include <bn_sprite_text_generator.h>
#include <bn_sprite_font.h>
#include "bn_sound_items.h"
#include <bn_string.h>
#include <bn_random.h>
#include <bn_math.h>
#include <bn_sound_actions.h>
#include <bn_cameras.h>
#include "bn_camera_actions.h"
#include <bn_optional.h>
#include <bn_blending.h>
#include <bn_rect_window.h>
#include <bn_math.h>

#include "bn_music.h"
#include "bn_music_items.h"
#include "bn_music_items_info.h"

#include "bn_regular_bg_ptr.h"

#include "bn_sprite_items_beryl.h"
#include "bn_sprite_items_font.h"
#include "bn_sprite_items_ui_bubble.h"
#include "bn_sprite_items_dialogue_back.h"
#include "bn_sprite_items_castor.h"
#include "bn_regular_bg_items_starsbackground.h"
#include "bn_regular_bg_items_bg_berylsroom.h"

using namespace bn;
using namespace core;
using namespace keypad;
using namespace sprite_items;
using namespace regular_bg_items;

#include "main.h"
#include "dialogue.h"
#include "levels.h"

fixed_t<12> lerp(bn::fixed a, int b, bn::fixed_t<12> t)
{
    // Promote to higher precision during computation
    auto high_precision_a = bn::fixed_t<12>(a);
    auto high_precision_b = bn::fixed_t<12>(b);
    auto high_precision_t = bn::fixed_t<12>(t);

    // Perform computation in the same precision
    fixed_t<12> expected = high_precision_a * (1 - high_precision_t) + high_precision_b * high_precision_t;

    return expected;
}

bool close(int a, int b, int dist)
{
    int c = a - b;
    if (c < 0)
        c = c * -1;
    return c < dist;
}

class Castor
{
public:
    sprite_ptr spr = castor.create_sprite(0, -120);
    int ideal_y;
    int ticker;

    void update()
    {
        ticker++;
        spr.set_y(lerp(spr.y().integer(), ideal_y + (int)(degrees_sin((ticker * 2) % 360) * 12), 0.2));
    }
};

class TextElement
{
public:
    int ticker = 0;
    vector<sprite_ptr, MAX_TEXT_LENGTH> text_vector;
    int x = 0;
    int y = 0;
    int offset = 0;
    int line = 0;
    int i = 0;
    int conversation;
    int current_line;
    bool active = false;
    bool is_talking = false;
    const DialogueLine *dl;
    Castor castor;

    vector<sprite_ptr, 2> spr_dialogue_back;

    sprite_ptr a_button = ui_bubble.create_sprite(100, -86, 2);

    int calculate_word_width(int start_index)
    {
        int word_width = 0;
        int idx = start_index;
        while (dl->line[idx] != '\0' && dl->line[idx] != ' ' && idx < MAX_TEXT_LENGTH)
        {
            auto metadata = char_map(dl->line[idx]);
            word_width += metadata.width;
            idx++;
        }
        return word_width;
    }

    // Setup function to initialize the text element
    void setup(int X, int Y, int conversation_)
    {
        text_vector.clear();
        ticker = 0;
        i = 0;
        y = Y;
        x = X;
        offset = 0;
        line = 0;
        conversation = conversation_;
        active = true;

        a_button.set_z_order(-5);

        auto db_spr = dialogue_back.create_sprite(-64, -64, 0);
        auto db_spr2 = dialogue_back.create_sprite(-64, 64, 0);
        db_spr.set_scale(2, 2);
        db_spr2.set_scale(2, 2);
        db_spr.set_blending_enabled(true);
        db_spr2.set_blending_enabled(true);
        blending::set_transparency_alpha(0.9);
        spr_dialogue_back.push_back(db_spr);
        spr_dialogue_back.push_back(db_spr2);

        current_line = 0; // Copy the string to the member variable
    }

    void update()
    {
        a_button.set_y(lerp(a_button.y(), -64, 0.2));
        castor.update();

        auto new_scale = lerp(a_button.horizontal_scale(), 1, 0.2);
        a_button.set_scale(new_scale, new_scale);
        dl = &gamelines[conversation][current_line];

        switch (dl->action)
        {
        case EXIT:
            active = false;
            is_talking = false;
            break;

        case PLAY_WELCOME:
            music_items::welcome.play();
            break;

        case CASTOR_APPEAR:
        {
            Castor c;
            c.ideal_y = -32;
            castor = c;
            break;
        }

        case CASTOR_DISAPPEAR:
            castor.ideal_y = -120;
            break;

        default:
            break;
        }

        // Action item
        if (dl->line == "?")
        {
            current_line++;
            text_vector.clear();
            ticker = 0;
            i = 0;
            offset = 0;
            line = 0;
        }

        // Dialogue item
        else if (dl->action != EXIT)
        {

            if (i < MAX_TEXT_LENGTH)
            {
                is_talking = true;

                if (ticker % 2 == 0) // Update every 2 ticks
                {
                    if (i < MAX_TEXT_LENGTH) // Ensure index is within bounds
                    {
                        char current_char = dl->line[i];

                        if (current_char == '\0')
                        {
                            i = MAX_TEXT_LENGTH;
                        }
                        else
                        {
                            // Check if current_char is whitespace
                            if (current_char == ' ')
                            {
                                offset += 8;
                                i++;
                            }
                            else
                            {
                                // Calculate the width of the next word
                                int word_width = calculate_word_width(i);

                                // Check if the word fits in the current line
                                if (offset + word_width > DIALOGUE_MAX_WIDTH)
                                {
                                    // Wrap to next line
                                    offset = 0;
                                    line++;
                                }

                                // Now proceed to add the character
                                auto metadata = char_map(current_char); // Get metadata for the character
                                auto letter = font.create_sprite(
                                    x + offset,
                                    y + (line * 32),
                                    metadata.index);
                                letter.set_z_order(-5);
                                text_vector.push_back(letter);
                                offset += metadata.width;
                                i++;
                                sound_items::click.play();
                            }
                        }
                    }
                }

                if (a_pressed())
                {
                    a_button.set_scale(1.2, 1.2);

                    do
                    {
                        char current_char = dl->line[i];

                        if (current_char == '\0')
                        {
                            i = MAX_TEXT_LENGTH;
                        }
                        else
                        {
                            // Check if current_char is whitespace
                            if (current_char == ' ')
                            {
                                // Just add the whitespace character
                                offset += 8;
                                i++;
                            }
                            else
                            {
                                // Calculate the width of the next word
                                int word_width = calculate_word_width(i);

                                // Check if the word fits in the current line
                                if (offset + word_width > DIALOGUE_MAX_WIDTH)
                                {
                                    // Wrap to next line
                                    offset = 0;
                                    line++;
                                }

                                // Now proceed to add the character
                                auto metadata = char_map(current_char); // Get metadata for the character
                                auto letter = font.create_sprite(
                                    x + offset,
                                    y + (line * 32),
                                    metadata.index);
                                letter.set_z_order(-5);
                                text_vector.push_back(letter);
                                offset += metadata.width;
                                i++;
                            }
                        }
                    } while (i < MAX_TEXT_LENGTH);
                }
            }
            else
            {
                is_talking = false;

                if (a_pressed())
                {
                    a_button.set_scale(1.2, 1.2);
                    current_line++;
                    text_vector.clear();
                    ticker = 0;
                    i = 0;
                    offset = 0;
                    line = 0;
                }
            }

            ticker++; // Increment ticker unconditionally
        }
    }
};

class global_data
{
public:
    bn::random rnd;
    bool is_talking;
    bool currently_talking;
    optional<TextElement> opt_te;

    global_data()
    {
        //
    }
};

global_data *globals;

class Beryl
{
public:
    bool facing_left;
    sprite_ptr spr_beryl[4] = {
        beryl.create_sprite(-32, -32 + 24, 0),
        beryl.create_sprite(-32, 32 + 24, 1),
        beryl.create_sprite(32, -32 + 24, 2),
        beryl.create_sprite(32, 32 + 24, 3),
    };
    int state = 0;
    int ticker = 0;
    camera_ptr cam = camera_ptr::create(0, 0);

    Beryl()
    {
        spr_beryl[0].set_camera(cam);
        spr_beryl[1].set_camera(cam);
        spr_beryl[2].set_camera(cam);
        spr_beryl[3].set_camera(cam);
    }

    void set_x(fixed_t<12> new_x)
    {
        spr_beryl[0].set_x(new_x - 32);
        spr_beryl[1].set_x(new_x - 32);
        spr_beryl[2].set_x(new_x + 32);
        spr_beryl[3].set_x(new_x + 32);
    }

    void set_y(fixed_t<12> new_y)
    {
        spr_beryl[0].set_y(new_y - 32);
        spr_beryl[1].set_y(new_y + 32);
        spr_beryl[2].set_y(new_y - 32);
        spr_beryl[3].set_y(new_y + 32);
    }

    fixed_t<12> x()
    {
        return spr_beryl[0].x() + 32.0;
    }

    fixed_t<12> y()
    {
        return spr_beryl[0].y() + 32.0;
    }

    void set_frame(int frame)
    {
        for (int t = 0; t < 4; ++t)
        {
            int tile_index = facing_left ? ((frame * 4) + ((t + 2) % 4)) : ((frame * 4) + t);
            spr_beryl[t].set_horizontal_flip(facing_left);
            spr_beryl[t].set_tiles(beryl.tiles_item(), tile_index);
        }
    }

    void update()
    {
        ticker++;

        if (globals->opt_te.has_value())
        {
            globals->opt_te.value().castor.spr.set_camera(cam);
            globals->opt_te.value().castor.spr.set_x(x() + 64);

            switch (globals->opt_te.value().dl->action)
            {
            case CASTOR_APPEAR:
            {
                facing_left = false;
                break;
            }
            case BERYL_LEFT:
            {
                facing_left = true;
                break;
            }
            case BERYL_RIGHT:
            {
                facing_left = false;
                break;
            }
            default:
            {
                break;
            }
            }

            if (globals->opt_te.value().dl->ch_id == CH_BERYL)
            {
                if (globals->opt_te.value().is_talking)
                {
                    set_frame(9 + (globals->opt_te.value().dl->emo_id * 2) + ((ticker % 8) > 4));
                }
                else
                {
                    set_frame(9 + (globals->opt_te.value().dl->emo_id * 2));
                }
            }
        }
        else
        {
            if (right_held())
            {
                if (ticker % 16 == 0)
                {
                    fixed_t<12> vol = globals->rnd.get_int(8) / 8.0;
                    sound_items::footstep.play(vol);
                }
                facing_left = false;
                state = 1;
                set_x(x() + 1.0);
            }
            else if (left_held())
            {
                if (ticker % 16 == 0)
                {
                    fixed_t<12> vol = globals->rnd.get_int(8) / 8.0;
                    sound_items::footstep.play(vol);
                }
                facing_left = true;
                state = 1;
                set_x(x() - 1.0);
            }
            else
            {
                state = 0;
            }

            if (state == 1)
            {
                set_frame((ticker / walk_speed) % 8);
            }
            else
            {
                set_frame(8);
            }
        }
    }
};

int main()
{
    init();
    globals = new global_data();
    vector<int, 64> spent_dialogue;

    auto bg = starsbackground.create_bg(0, 48);

    const Room current_room = room_map(ROOM_BEDROOM);
    auto bg_room = current_room.bg.create_bg(0, 0);

    Beryl b;
    bg_room.set_camera(b.cam);
    b.set_x(current_room.init_x);

    auto action_bubble = ui_bubble.create_sprite(0, -110, 0);

    int ticker = 0;
    while (true)
    {
        b.update();

        if (globals->opt_te.has_value())
        {
            globals->opt_te.value().update();
            if (!globals->opt_te.value().active)
            {
                globals->opt_te.reset();
            }

            b.cam.set_x(lerp(b.cam.x(), b.x().integer() - 64 + (32 - (64 * b.facing_left)), 0.2));
        }
        else
        {
            b.cam.set_x(lerp(b.cam.x(), b.x().integer(), 0.5));
        }

        bool show_bubble = false;
        for (int i = 0; i < 64; i++)
        {
            if (current_room.items[i].x == 0)
            {
                i = 64;
            }
            else
            {
                int action = current_room.items[i].action;
                bool exists = false;

                for (int t = 0; t < spent_dialogue.size(); t++)
                {
                    exists = exists || (spent_dialogue.at(t) == action);
                    if (exists)
                        t = spent_dialogue.size();
                }

                if (close(b.x().integer(), current_room.items[i].x, 5) && !globals->opt_te.has_value() && !(exists && current_room.items[i].automatic))
                {
                    show_bubble = true;

                    if (current_room.items[i].automatic || a_pressed())
                    {
                        if (!exists)
                        {
                            spent_dialogue.push_back(action);
                        }

                        TextElement te;
                        te.setup(-108, -60, 0);
                        te.conversation = action;
                        globals->opt_te = te;
                        i = 64;
                    }
                }
            }
        }
        if (show_bubble) {
            action_bubble.set_y(lerp(action_bubble.y(), -64, 0.2));
        } else {
            action_bubble.set_y(lerp(action_bubble.y(), -110, 0.2));
        }

        ticker++;
        update();
    }

    return 0;
}