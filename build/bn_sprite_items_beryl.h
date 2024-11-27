#ifndef BN_SPRITE_ITEMS_BERYL_H
#define BN_SPRITE_ITEMS_BERYL_H

#include "bn_sprite_item.h"

//{{BLOCK(beryl_bn_gfx)

//======================================================================
//
//	beryl_bn_gfx, 64x5376@4, 
//	+ palette 16 entries, not compressed
//	+ 5376 tiles not compressed
//	Total size: 32 + 172032 = 172064
//
//	Time-stamp: 2024-11-27, 00:25:04
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_BERYL_BN_GFX_H
#define GRIT_BERYL_BN_GFX_H

#define beryl_bn_gfxTilesLen 172032
extern const bn::tile beryl_bn_gfxTiles[5376];

#define beryl_bn_gfxPalLen 32
extern const bn::color beryl_bn_gfxPal[16];

#endif // GRIT_BERYL_BN_GFX_H

//}}BLOCK(beryl_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item beryl(sprite_shape_size(sprite_shape::SQUARE, sprite_size::HUGE), 
            sprite_tiles_item(span<const tile>(beryl_bn_gfxTiles, 5376), bpp_mode::BPP_4, compression_type::NONE, 84), 
            sprite_palette_item(span<const color>(beryl_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

