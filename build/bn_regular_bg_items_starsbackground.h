#ifndef BN_REGULAR_BG_ITEMS_STARSBACKGROUND_H
#define BN_REGULAR_BG_ITEMS_STARSBACKGROUND_H

#include "bn_regular_bg_item.h"

//{{BLOCK(starsbackground_bn_gfx)

//======================================================================
//
//	starsbackground_bn_gfx, 256x256@4, 
//	+ palette 16 entries, not compressed
//	+ 890 tiles (t|f|p reduced) not compressed
//	+ regular map (flat), not compressed, 32x32 
//	Total size: 32 + 28480 + 2048 = 30560
//
//	Time-stamp: 2024-12-04, 16:30:47
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_STARSBACKGROUND_BN_GFX_H
#define GRIT_STARSBACKGROUND_BN_GFX_H

#define starsbackground_bn_gfxTilesLen 28480
extern const bn::tile starsbackground_bn_gfxTiles[890];

#define starsbackground_bn_gfxMapLen 2048
extern const bn::regular_bg_map_cell starsbackground_bn_gfxMap[1024];

#define starsbackground_bn_gfxPalLen 32
extern const bn::color starsbackground_bn_gfxPal[16];

#endif // GRIT_STARSBACKGROUND_BN_GFX_H

//}}BLOCK(starsbackground_bn_gfx)

namespace bn::regular_bg_items
{
    constexpr inline regular_bg_item starsbackground(
            regular_bg_tiles_item(span<const tile>(starsbackground_bn_gfxTiles, 890), bpp_mode::BPP_4, compression_type::NONE), 
            bg_palette_item(span<const color>(starsbackground_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE),
            regular_bg_map_item(starsbackground_bn_gfxMap[0], size(32, 32), compression_type::NONE, 1, false));
}

#endif

