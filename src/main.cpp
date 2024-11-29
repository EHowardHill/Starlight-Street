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
#include <bn_music_actions.h>

#include "bn_regular_bg_ptr.h"

#include "bn_sprite_items_beryl.h"
#include "bn_sprite_items_font.h"
#include "bn_sprite_items_ui_bubble.h"
#include "bn_sprite_items_dialogue_back.h"
#include "bn_sprite_items_castor.h"
#include "bn_sprite_items_rake01.h"
#include "bn_sprite_items_star.h"
#include "bn_sprite_items_grass.h"
#include "bn_sprite_items_spr_text.h"
#include "bn_sprite_items_sign.h"
#include "bn_regular_bg_items_starsbackground.h"
#include "bn_regular_bg_items_bg_berylsroom.h"
#include "bn_regular_bg_items_bg_grass.h"
#include "bn_regular_bg_items_thx.h"

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

// VirtualSprite class definition
class VirtualSprite
{
public:
    optional<sprite_ptr> spr;
    const sprite_item *base_item;
    camera_ptr *camera;
    fixed_t<12> x;
    fixed_t<12> y;
    int index;

    // Constructor with initialization list
    VirtualSprite(const sprite_item *base_item_, camera_ptr *camera_, int x_ = 0, int y_ = 0, int index_ = 0)
        : base_item(base_item_), camera(camera_), x(x_), y(y_), index(index_)
    {
    }

    void update()
    {
        if ((x - camera->x() < -150) || (x - camera->x() > 150))
        {
            if (spr.has_value())
            {
                spr.reset();
            }
        }
        else
        {
            if (!spr.has_value())
            {
                auto new_spr = base_item->create_sprite(x, y, index);
                new_spr.set_z_order(2);
                new_spr.set_camera(*camera); // Dereference pointer
                spr = new_spr;               // Assign to optional
            }
        }
    }
}; // Added semicolon

class Castor
{
public:
    sprite_ptr spr = castor.create_sprite(0, -150);
    int ideal_y;
    int ticker;

    void update()
    {
        ticker++;
        spr.set_y(lerp(spr.y().integer(), ideal_y + (int)(degrees_sin((ticker * 2) % 360) * 12), 0.2));
    }
};

class Rake
{
public:
    sprite_ptr p_1 = rake01.create_sprite(80, -74, 0);
    sprite_ptr p_2 = rake01.create_sprite(80, 54, 1);
    sprite_ptr p_3 = rake01.create_sprite(208, -74, 2);
    sprite_ptr p_4 = rake01.create_sprite(208, 54, 3);
    bool first_view = false;

    Rake(camera_ptr &cam, int x)
    {
        p_1.set_scale(2, 2);
        p_2.set_scale(2, 2);
        p_1.set_camera(cam);
        p_2.set_camera(cam);
        p_1.set_x(x);
        p_2.set_x(x);

        p_3.set_scale(2, 2);
        p_4.set_scale(2, 2);
        p_3.set_camera(cam);
        p_4.set_camera(cam);
        p_3.set_x(x + 128);
        p_4.set_x(x + 128);
    }

    void update()
    {
        p_1.set_x(p_1.x() - 2);
        p_2.set_x(p_2.x() - 2);
        p_3.set_x(p_3.x() - 2);
        p_4.set_x(p_4.x() - 2);
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
        castor.spr.set_visible(false);

        a_button.set_z_order(-5);

        auto db_spr = dialogue_back.create_sprite(-64, -64, 0);
        auto db_spr2 = dialogue_back.create_sprite(-64, 64, 0);
        db_spr.set_scale(2, 2);
        db_spr2.set_scale(2, 2);
        db_spr.set_blending_enabled(true);
        db_spr2.set_blending_enabled(true);
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

        case MUSIC_STOP:
            music::stop();
            break;

        case CASTOR_APPEAR:
        {
            castor.spr.set_visible(true);
            castor.ideal_y = -32;
            sound_items::castor.play();
            break;
        }

        case CASTOR_DISAPPEAR:
            castor.ideal_y = -150;
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
    bool is_scared = false;

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
                    set_frame(15 + (globals->opt_te.value().dl->emo_id * 2) + ((ticker % 8) > 4));
                }
                else
                {
                    set_frame(15 + (globals->opt_te.value().dl->emo_id * 2));
                }
            }
        }
        else
        {
            if (b_held() || is_scared)
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
                    set_x(x() + 4.0);
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
                    set_x(x() - 4.0);
                }
                else
                {
                    state = 0;
                }

                if (state == 1)
                {
                    set_frame(9 + (ticker / walk_speed) % 6);
                }
                else
                {
                    set_frame(21);
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
    }
};

class Grass
{
public:
    vector<sprite_ptr, 3> blades;
    int init_frame[3];
    int ticker = 0;
    camera_ptr *local_camera; // Use pointer instead of reference

    Grass(camera_ptr *cam)
    { // Accept pointer in the constructor
        local_camera = cam;
        for (int t = 0; t < 3; t++)
        {
            init_frame[t] = globals->rnd.get_int(10);
            auto g = grass.create_sprite(-200 + globals->rnd.get_int(400), 64 - globals->rnd.get_int(12), init_frame[t]);
            g.set_camera(*cam);
            blades.push_back(g);
        }
    }

    void update()
    {
        for (int t = 0; t < blades.size(); t++)
        {
            blades.at(t).set_tiles(grass.tiles_item(), (ticker + init_frame[t]) % 9);

            auto corrected_x = blades.at(t).x() - local_camera->x(); // Use -> for pointer
            if (corrected_x < -200)
            {
                blades.at(t).set_x(local_camera->x() + 200 + globals->rnd.get_int(150));
            }
            else if (corrected_x > 200)
            {
                blades.at(t).set_x(local_camera->x() - 200 - globals->rnd.get_int(150));
            }
        }
        ticker++;
    }
};

void play_room(int current_room_int)
{
    vector<regular_bg_ptr, 3> bgs;
    vector<int, 64> spent_dialogue;
    vector<VirtualSprite, 64> virtual_sprites;

    Room current_room = room_map(current_room_int);

    Beryl b;
    b.set_x(current_room.init_x);
    b.cam.set_x(b.x());

    blending::set_transparency_alpha(0.9);
    {
        auto bg = starsbackground.create_bg(0, 48);
        auto bg_room = current_room.bg.create_bg(0, 0);
        bg_room.set_camera(b.cam);

        if (current_room.fadedown)
        {
            bg.set_blending_enabled(true);
            blending::set_transparency_alpha(0);
        }

        bgs.push_back(bg);
        bgs.push_back(bg_room);
    }

    auto action_bubble = ui_bubble.create_sprite(0, -110, 0);

    optional<Rake> r;
    optional<Grass> g;

    switch (current_room_int)
    {
    case ROOM_GRASS:
    {
        Grass gg = {&b.cam};
        g = gg;

        VirtualSprite text01 = {&spr_text, &b.cam, 400, 0, 0};
        VirtualSprite text02 = {&spr_text, &b.cam, 400 + 64, 0, 1};
        VirtualSprite text03 = {&spr_text, &b.cam, 400 + 128, 0, 2};
        VirtualSprite text04 = {&spr_text, &b.cam, 400 + 192, 0, 3};
        VirtualSprite text05 = {&spr_text, &b.cam, 400 + 256, 0, 4};

        VirtualSprite sign01 = {&sign, &b.cam, 950, 0, 0};
        VirtualSprite sign02 = {&sign, &b.cam, 950, 32, 1};

        virtual_sprites.push_back(text01);
        virtual_sprites.push_back(text02);
        virtual_sprites.push_back(text03);
        virtual_sprites.push_back(text04);
        virtual_sprites.push_back(text05);
        virtual_sprites.push_back(sign01);
        virtual_sprites.push_back(sign02);
        break;
    }
    default:
    {
        break;
    }
    }

    if (current_room.fadedown)
    {
        b.cam.set_y(-150);
    }

    int ticker = 0;
    bool is_playing = true;
    while (is_playing)
    {
        for (int t = 0; t < virtual_sprites.size(); t++)
        {
            virtual_sprites.at(t).update();
        }

        if (g.has_value())
        {
            g.value().update();
        }

        if (current_room.fadedown)
        {
            if (blending::transparency_alpha() < 0.9)
            {
                blending::set_transparency_alpha(blending::transparency_alpha() + 0.005);
            }
            else
            {
                bgs.at(0).set_blending_enabled(false);
                blending::set_transparency_alpha(0.9);
            }
        }

        if (r.has_value())
        {
            r.value().update();

            if (close(b.x().integer(), r.value().p_1.x().integer(), 48))
            {
                is_playing = false;
            }
        }

        if (current_room.loops)
        {
            if (b.x().integer() < -500)
            {
                if (b.is_scared)
                {
                    bgs.clear();
                }
                else
                {
                    auto c_offset = b.x() - b.cam.x();
                    b.set_x(500);
                    b.cam.set_x(500 - c_offset);
                }
            }
            else if (b.x().integer() > 500)
            {
                if (b.is_scared)
                {
                    bgs.clear();
                }
                else
                {
                    auto c_offset = b.x() - b.cam.x();
                    b.set_x(-500);
                    b.cam.set_x(-500 - c_offset);
                }
            }
        }

        if (globals->opt_te.has_value())
        {
            globals->opt_te.value().update();

            if (!globals->opt_te.value().active)
            {
                globals->opt_te.reset();
            }

            b.cam.set_x(lerp(b.cam.x(), b.x().integer() - 64 + (32 - (64 * b.facing_left)), 0.5));
            // b.cam.set_x(b.x().integer() - 64 + (32 - (64 * b.facing_left)));
        }
        else
        {
            // b.cam.set_x(b.x());
            b.cam.set_x(lerp(b.cam.x(), b.x().integer(), 0.5));
        }

        bool show_bubble = false;
        if (!b.is_scared)
        {
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
        }

        if (show_bubble)
        {
            action_bubble.set_y(lerp(action_bubble.y(), -64, 0.2));
        }
        else
        {
            action_bubble.set_y(lerp(action_bubble.y(), -110, 0.2));
        }

        b.update();

        if (ticker % 64 == 0)
        {
            BN_LOG("X: ", b.x());
            BN_LOG("CAMX: ", b.cam.x());
        }

        // Room-specific actions
        switch (current_room_int)
        {
        case ROOM_BEDROOM:
        {
            if (spent_dialogue.size() == 9 && b.x() < 50 && b.x() > -240 && !globals->opt_te.has_value())
            {
                b.is_scared = true;
                sound_items::door.play();
                music::stop();
                spent_dialogue.push_back(-1);

                Rake rr = {b.cam, 300};
                r = rr;
            }

            if (b.is_scared && b.x() < -750)
            {
                is_playing = false;
            }
            break;
        }
        case ROOM_GRASS:
        {
            if (!music::playing())
            {
                music_items::lt01.play();
                music_volume_manager::set(0);
            }

            if (b.x().integer() > 100 && b.x().integer() <= 500)
            {
                music_volume_manager::set((b.x() - 100.0) / 400.0);
            }

            for (int t = 0; t < spent_dialogue.size(); t++)
            {
                if (spent_dialogue.at(t) == C_ENDOFDEMO && !globals->opt_te.has_value())
                {
                    is_playing = false;
                }
            }

            break;
        }
        default:
        {
            break;
        }
        }

        if (b.cam.y() < 0)
        {
            b.cam.set_y(b.cam.y() + 0.5);
        }

        ticker++;
        update();
    }
}

void cutscene(int scene)
{
    int ticker = 0;
    switch (scene)
    {
    case C_2018:
    {
        sound_items::v_2018.play();
        while (ticker < 420)
        {
            ticker++;
            update();
        }
        break;
    }
    case C_GASP:
    {
        sound_items::gasp.play();
        while (ticker < 350)
        {
            ticker++;
            update();
        }
        break;
    }
    case C_STARS:
    {
        sound_items::twinkle.play();
        ticker++;
        vector<sprite_ptr, 16> stars;
        for (int t = 0; t < 16; t++)
        {
            auto s = star.create_sprite(120 - globals->rnd.get_int(240), 150 + globals->rnd.get_int(240));
            fixed_t<12> scale_rnd = globals->rnd.get_int(3);
            fixed_t<12> scale = 0.4 + (scale_rnd / 10.0);
            s.set_scale(scale, scale);
            s.set_rotation_angle(globals->rnd.get_int(360));
            stars.push_back(s);
        }
        while (ticker < 700)
        {
            for (int t = 0; t < 16; t++)
            {
                stars.at(t).set_y(stars.at(t).y() - (2 * (stars.at(t).horizontal_scale())));

                if (t % 3 == 0)
                {
                    stars.at(t).set_rotation_angle((stars.at(t).rotation_angle() + 1) % 360);
                }
            }

            ticker++;
            update();
        }
        break;
    }
    case C_THX:
    {
        music_items::st01.play();
        auto bg_thx = thx.create_bg(0, 0);
        while (true)
        {
            update();
        }
        break;
    }
    default:
    {
        break;
    }
    }
}

int main()
{
    init();
    globals = new global_data();

    cutscene(C_2018);
    play_room(ROOM_BEDROOM);
    cutscene(C_GASP);
    cutscene(C_STARS);
    play_room(ROOM_GRASS);
    cutscene(C_STARS);
    cutscene(C_THX);

    // Stuck end
    while (true)
    {
        update();
    }

    return 0;
}