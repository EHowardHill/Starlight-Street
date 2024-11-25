#ifndef BN_SPRITE_ITEMS_UI_BUBBLE_H
#define BN_SPRITE_ITEMS_UI_BUBBLE_H

#include "bn_sprite_item.h"

//{{BLOCK(ui_bubble_bn_gfx)

//======================================================================
//
//	ui_bubble_bn_gfx, 32x64@4, 
//	+ palette 16 entries, not compressed
//	+ 32 tiles not compressed
//	Total size: 32 + 1024 = 1056
//
//	Time-stamp: 2024-11-24, 23:38:53
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_UI_BUBBLE_BN_GFX_H
#define GRIT_UI_BUBBLE_BN_GFX_H

#define ui_bubble_bn_gfxTilesLen 1024
extern const bn::tile ui_bubble_bn_gfxTiles[32];

#define ui_bubble_bn_gfxPalLen 32
extern const bn::color ui_bubble_bn_gfxPal[16];

#endif // GRIT_UI_BUBBLE_BN_GFX_H

//}}BLOCK(ui_bubble_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item ui_bubble(sprite_shape_size(sprite_shape::SQUARE, sprite_size::BIG), 
            sprite_tiles_item(span<const tile>(ui_bubble_bn_gfxTiles, 32), bpp_mode::BPP_4, compression_type::NONE, 2), 
            sprite_palette_item(span<const color>(ui_bubble_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

