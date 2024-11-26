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
#include <bn_optional.h>

#include "bn_music.h"
#include "bn_music_items.h"
#include "bn_music_items_info.h"

#include "bn_regular_bg_ptr.h"

#include "bn_sprite_items_beryl.h"
#include "bn_sprite_items_font.h"
#include "bn_sprite_items_ui_bubble.h"
#include "bn_sprite_items_dialogue_back.h"
#include "bn_regular_bg_items_starsbackground.h"
#include "bn_regular_bg_items_bg_berylsroom.h"

using namespace bn;
using namespace core;
using namespace keypad;
using namespace sprite_items;
using namespace regular_bg_items;

#include "goodies.cpp"

class TextElement;

constexpr int walk_speed = 4;
constexpr int DIALOGUE_MAX_WIDTH = 110;
constexpr int MAX_TEXT_LENGTH = 64;

fixed_t<12> lerp(bn::fixed a, int b, bn::fixed_t<12> t)
{
    return a * (1 - t) + b * t;
}

class TextElement
{
public:
    int ticker = 0;
    vector<sprite_ptr, MAX_TEXT_LENGTH> text_vector;
    int y = 0;
    int x = 0;
    int offset = 0;
    int line = 0;
    int i = 0;
    int conversation;
    int current_line;
    int current_ch;
    int current_emo;
    bool active = false;
    bool is_talking = false;
    const DialogueLine *dl;

    vector<sprite_ptr, 2> spr_dialogue_back;

    sprite_ptr a_button = ui_bubble.create_sprite(100, -86, 2);

    int calculate_word_width(int start_index)
    {
        current_ch = dl->ch_id;
        current_emo = dl->emo_id;

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

        auto new_scale = lerp(a_button.horizontal_scale(), 1, 0.2);
        a_button.set_scale(new_scale, new_scale);
        dl = &gamelines[conversation][current_line];

        if (dl->sound_id == -1)
        {
            active = false;
            is_talking = false;
        }
        else
        {
            BN_LOG("IN: ", is_talking);

            if (i < MAX_TEXT_LENGTH)
            {
                is_talking = true;
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
                                auto metadata = char_map(current_char);
                                auto letter = font.create_sprite(
                                    x + offset,
                                    y + (line * 32),
                                    metadata.index);
                                text_vector.push_back(letter);
                                offset += metadata.width;
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
                            // Just add the whitespace character
                            auto metadata = char_map(current_char);
                            auto letter = font.create_sprite(
                                x + offset,
                                y + (line * 32),
                                metadata.index);
                            text_vector.push_back(letter);
                            offset += metadata.width;
                            i++;
                            sound_items::click.play();
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
            ticker++; // Increment ticker unconditionally
        }
    }
};

class global_data
{
public:
    random rnd;
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
    sprite_ptr spr_beryl[4] = {
        beryl.create_sprite(-32, -32 + 24, 0),
        beryl.create_sprite(-32, 32 + 24, 1),
        beryl.create_sprite(32, -32 + 24, 2),
        beryl.create_sprite(32, 32 + 24, 3),
    };
    int state = 0;
    int ticker = 0;
    camera_ptr cam = camera_ptr::create(0, 0);
    bool facing_left = true;

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
            if (globals->opt_te.value().is_talking)
            {
                set_frame(9 + (globals->opt_te.value().current_emo * 2) + ((ticker % 8) > 4));
            }
            else
            {
                set_frame(9 + (globals->opt_te.value().current_emo * 2));
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

    auto bg = starsbackground.create_bg(0, 48);
    auto bg_room = bg_berylsroom.create_bg(0, 0);

    Beryl b;
    bg_room.set_camera(b.cam);

    int ticker = 0;
    while (true)
    {
        b.update();

        if (b_pressed() && !globals->opt_te.has_value())
        {
            TextElement te;
            te.setup(-110, -60, 0);
            globals->opt_te = te;
        }

        if (globals->opt_te.has_value())
        {
            globals->opt_te.value().update();
            if (!globals->opt_te.value().active)
            {
                globals->opt_te.reset();
            }

            b.cam.set_x(lerp(b.cam.x(), b.x().integer() - 64, 0.2));
        }
        else
        {
            b.cam.set_x(lerp(b.cam.x(), b.x().integer(), 0.5));
        }

        ticker++;
        update();
    }

    return 0;
}