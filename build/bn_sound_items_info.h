#ifndef BN_SOUND_ITEMS_INFO_H
#define BN_SOUND_ITEMS_INFO_H

#include "bn_span.h"
#include "bn_sound_item.h"
#include "bn_string_view.h"

namespace bn::sound_items_info
{
    constexpr inline pair<sound_item, string_view> array[] = {
        make_pair(sound_item(0), string_view("castor")),
        make_pair(sound_item(1), string_view("click")),
        make_pair(sound_item(2), string_view("cutscene01")),
        make_pair(sound_item(3), string_view("cutscene02")),
        make_pair(sound_item(4), string_view("door")),
        make_pair(sound_item(5), string_view("footstep")),
        make_pair(sound_item(6), string_view("gasp")),
        make_pair(sound_item(11), string_view("sebenereben")),
        make_pair(sound_item(15), string_view("twinkle")),
        make_pair(sound_item(16), string_view("v_2018")),
    };

    constexpr inline span<const pair<sound_item, string_view>> span(array);
}

#endif

