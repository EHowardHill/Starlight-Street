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
#include "bn_sprite_items_dialogue_back.h"
#include "bn_regular_bg_items_starsbackground.h"
#include "bn_regular_bg_items_bg_berylsroom.h"

using namespace bn;
using namespace core;
using namespace keypad;
using namespace sprite_items;
using namespace regular_bg_items;

#include "goodies.cpp"

constexpr int walk_speed = 4;

const DialogueLine gamelines[64][64] = {
    {{0, 0, "I'm wondering, does this look at all familiar to you?"},
     {0, 0, "Is this working?"},
     {-1}}};

fixed_t<12> lerp(bn::fixed a, int b, bn::fixed_t<12> t)
{
    return a * (1 - t) + b * t;
}

class TextElement
{
public:
    int ticker = 0;
    vector<sprite_ptr, 64> text_vector; // Fixed incorrect vector declaration
    int y = 0;
    int x = 0;
    int width = 0;
    int offset = 0;
    int line = 0;
    int i = 0;
    int conversation;
    int current_line;
    bool active = false;

    vector<sprite_ptr, 2> spr_dialogue_back;

    int calculate_word_width(int start_index)
    {
        DialogueLine dl = gamelines[conversation][current_line];

        int word_width = 0;
        int idx = start_index;
        while (dl.line[idx] != '\0' && dl.line[idx] != ' ' && idx < 64)
        {
            auto metadata = char_map(dl.line[idx]);
            word_width += metadata.width;
            idx++;
        }
        return word_width;
    }

    // Setup function to initialize the text element
    void setup(int X, int Y, int width_, int conversation_)
    {
        text_vector.clear();
        ticker = 0;
        i = 0;
        y = Y;
        x = X;
        offset = 0;
        line = 0;
        width = width_;
        conversation = conversation_;
        active = true;

        auto db_spr = dialogue_back.create_sprite(-64, 40, 0);
        auto db_spr2 = dialogue_back.create_sprite(64, 40, 0);
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
        DialogueLine dl = gamelines[conversation][current_line];

        if (dl.sound_id == -1)
        {
            active = false;
        }
        else
        {
            if (i < 64)
            {
                if (a_pressed())
                {
                    do
                    {
                        char current_char = dl.line[i];

                        if (current_char == '\0')
                        {
                            i = 64;
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
                                if (offset + word_width > width)
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
                    } while (i < 64);
                }
            }
            else
            {
                if (a_pressed())
                {
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
                if (i < 64) // Ensure index is within bounds
                {
                    char current_char = dl.line[i];

                    if (current_char == '\0')
                    {
                        i = 64;
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
                            if (offset + word_width > width)
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

    void update()
    {
        if (right_held())
        {
            facing_left = false;
            state = 1;
            set_x(x() + 1.0);
        }
        else if (left_held())
        {
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
            // cam.set_x(lerp(cam.x(), spr_beryl[0].x().integer() + 64, 0.1));
            ticker++;

            for (int t = 0; t < 4; t++)
            {
                if (facing_left)
                {
                    spr_beryl[t].set_horizontal_flip(true);
                    if (t < 2)
                    {
                        spr_beryl[t].set_tiles(beryl.tiles_item(), (((ticker / walk_speed) % 8) * 4) + t + 2);
                        spr_beryl[t].set_tiles(beryl.tiles_item(), (((ticker / walk_speed) % 8) * 4) + t + 2);
                    }
                    else
                    {
                        spr_beryl[t].set_tiles(beryl.tiles_item(), (((ticker / walk_speed) % 8) * 4) + t - 2);
                        spr_beryl[t].set_tiles(beryl.tiles_item(), (((ticker / walk_speed) % 8) * 4) + t - 2);
                    }
                }
                else
                {
                    spr_beryl[t].set_horizontal_flip(false);
                    spr_beryl[t].set_tiles(beryl.tiles_item(), (((ticker / walk_speed) % 8) * 4) + t);
                    spr_beryl[t].set_tiles(beryl.tiles_item(), (((ticker / walk_speed) % 8) * 4) + t);
                }
            }
        }
        else
        {
            // cam.set_x(lerp(cam.x(), spr_beryl[0].x().integer() - 32, 0.1));

            for (int t = 0; t < 4; t++)
            {
                if (facing_left)
                {
                    spr_beryl[t].set_horizontal_flip(true);

                    if (t < 2)
                    {
                        spr_beryl[t].set_tiles(beryl.tiles_item(), (8 * 4) + t + 2);
                    }
                    else
                    {
                        spr_beryl[t].set_tiles(beryl.tiles_item(), (8 * 4) + t - 2);
                    }
                }
                else
                {
                    spr_beryl[t].set_horizontal_flip(false);
                    spr_beryl[t].set_tiles(beryl.tiles_item(), (8 * 4) + t);
                }
            }
        }

        cam.set_x(x() + 32);
    }
};

int main()
{
    init();

    music_items::lt01.play();

    auto bg = starsbackground.create_bg(0, 48);
    auto bg_room = bg_berylsroom.create_bg(0, 0);

    Beryl b;
    bg_room.set_camera(b.cam);

    optional<TextElement> opt_te;

    const char *l = gamelines[0][0].line;
    BN_LOG(l);

    int ticker = 0;
    while (true)
    {
        b.update();

        if (b_pressed() && !opt_te.has_value())
        {
            TextElement te;
            te.setup(-110, 0, 220, 0);
            opt_te = te;
        }

        if (opt_te.has_value())
        {
            b.cam.set_y(lerp(b.cam.y(), 32, 0.2));
            opt_te.value().update();
            if (!opt_te.value().active)
            {
                opt_te.reset();
            }
        }
        else
        {
            b.cam.set_y(lerp(b.cam.y(), 0, 0.2));
        }

        ticker++;
        update();
    }

    return 0;
}