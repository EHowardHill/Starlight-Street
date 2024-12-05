#ifndef BN_REGULAR_BG_ITEMS_BG_BERYLSROOM_H
#define BN_REGULAR_BG_ITEMS_BG_BERYLSROOM_H

#include "bn_regular_bg_item.h"

//{{BLOCK(bg_berylsroom_bn_gfx)

//======================================================================
//
//	bg_berylsroom_bn_gfx, 1024x1024@4, 
//	+ palette 16 entries, not compressed
//	+ 989 tiles (t|f|p reduced) not compressed
//	+ regular map (flat), not compressed, 128x128 
//	Total size: 32 + 31648 + 32768 = 64448
//
//	Time-stamp: 2024-12-05, 12:36:03
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_BG_BERYLSROOM_BN_GFX_H
#define GRIT_BG_BERYLSROOM_BN_GFX_H

#define bg_berylsroom_bn_gfxTilesLen 31648
extern const bn::tile bg_berylsroom_bn_gfxTiles[989];

#define bg_berylsroom_bn_gfxMapLen 32768
extern const bn::regular_bg_map_cell bg_berylsroom_bn_gfxMap[16384];

#define bg_berylsroom_bn_gfxPalLen 32
extern const bn::color bg_berylsroom_bn_gfxPal[16];

#endif // GRIT_BG_BERYLSROOM_BN_GFX_H

//}}BLOCK(bg_berylsroom_bn_gfx)

namespace bn::regular_bg_items
{
    constexpr inline regular_bg_item bg_berylsroom(
            regular_bg_tiles_item(span<const tile>(bg_berylsroom_bn_gfxTiles, 989), bpp_mode::BPP_4, compression_type::NONE), 
            bg_palette_item(span<const color>(bg_berylsroom_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE),
            regular_bg_map_item(bg_berylsroom_bn_gfxMap[0], size(128, 128), compression_type::NONE, 1, true));
}

#endif

