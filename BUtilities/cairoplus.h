/* cairoplus.h
 * Copyright (C) 2018 - 2023  Sven Jähnichen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef BUTILITIES_CAIROPLUS_H_
#define BUTILITIES_CAIROPLUS_H_

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <cairo/cairo.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct {
	double red;
	double green;
	double blue;
	double alpha;
} cairoplus_rgba;

typedef struct {
	char family[64];
	double size;
	cairo_font_slant_t slant;
	cairo_font_weight_t weight;
} cairoplus_text_decorations;

/**
 *  @brief  Draws a rectangle with selected rounded edges.
 *  @param cr  Cairo context.
 *  @param x  X coordinate upper right.
 *  @param y  Y coordinate upper right.
 *  @param width  Rectangle width.
 *  @param height  Rectangle height.
 *  @param radius  Radius of edges.
 *  @param corners  Optional, bits set for the corners with rounded edges in
 *  clockwise direction starting with upper right.
 */
void cairoplus_rectangle_rounded (cairo_t* cr, double x, double y, double width, double height, double radius, uint8_t corners);

/**
 *  @brief  Creates a new Cairo image surface and copies the content from a 
 *  source Cairo image surface.
 *  @param sourceSurface  Source Cairo (image) surface.
 *  @return  Created new Cairo image surface.
 */
cairo_surface_t* cairoplus_image_surface_clone_from_image_surface (cairo_surface_t* sourceSurface);

/**
 *  @brief  Clears a Cairo surface.
 *  @param surface Cairo surface.
 */
void cairoplus_surface_clear (cairo_surface_t* surface);

/**
 *  @brief  Splits off a text that fits within an output area defined by its 
 *  width.
 *  @param cr  Cairo context.
 *  @param decorations  Cairo plus font decorations.
 *  @param text  Text to be parsed. The output text will be clipped off
 *  and thus the text will be shortened.
 *  @return  New created output text. Note, it will never return NULL.
 *  If memory allocation fails, a pointer to a nil text will be returned.
 */
char* cairoplus_create_text_fitted (cairo_t* cr, double width, cairoplus_text_decorations decorations, char* text);

/**
 *  @brief  Destroys a Cairo plus text and frees memory.
 *  @param text  Cairo plus text.
 */
void cairoplus_text_destroy (char* text);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* BUTILITIES_CAIROPLUS_H_ */
