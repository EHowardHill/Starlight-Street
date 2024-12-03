#ifndef BN_SPRITE_ITEMS_FONT_H
#define BN_SPRITE_ITEMS_FONT_H

#include "bn_sprite_item.h"

//{{BLOCK(font_bn_gfx)

//======================================================================
//
//	font_bn_gfx, 32x1856@4, 
//	+ palette 16 entries, not compressed
//	+ 928 tiles not compressed
//	Total size: 32 + 29696 = 29728
//
//	Time-stamp: 2024-12-02, 23:47:52
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_FONT_BN_GFX_H
#define GRIT_FONT_BN_GFX_H

#define font_bn_gfxTilesLen 29696
extern const bn::tile font_bn_gfxTiles[928];

#define font_bn_gfxPalLen 32
extern const bn::color font_bn_gfxPal[16];

#endif // GRIT_FONT_BN_GFX_H

//}}BLOCK(font_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item font(sprite_shape_size(sprite_shape::SQUARE, sprite_size::BIG), 
            sprite_tiles_item(span<const tile>(font_bn_gfxTiles, 928), bpp_mode::BPP_4, compression_type::NONE, 58), 
            sprite_palette_item(span<const color>(font_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

