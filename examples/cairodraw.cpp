/* widgetgalery.cpp
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

#include <cmath>
#include <cstdio>
#include <string>
#define MINIMP3_IMPLEMENTATION

#include "../BWidgets/Window.hpp"
#include "../BWidgets/Image.hpp"
#include "../BWidgets/Label.hpp"
#include "../BEvents/ExposeEvent.hpp"
#include <cairo/cairo.h>
#include <cstdlib>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <vector>
#include <ctime>

#define URI "https://github.com/sjaehn/BWidgets/cairodraw.cpp"

using namespace BWidgets;
using namespace BStyles;

int main ()
{
    // Window
    Window window (400, 300, 0, BUTILITIES_URID_UNKNOWN_URID, "Window", true);

    // Image
    Image image (0, 0, 400, 300);
    image.createImage(Status::normal);
    cairo_surface_t* s = image.getImageSurface(Status::normal);
    cairo_t* cr = cairo_create(s);
    window.add (&image);

    const std::chrono::steady_clock::time_point t0 = std::chrono::steady_clock::now();

    while (!window.isQuit())
    {
        const std::chrono::steady_clock::time_point t = std::chrono::steady_clock::now();
        const std::chrono::duration<double> dt = t - t0;
        const double x = dt.count();
        cairo_set_source_rgba(cr, sin (x), sin (x + 0.667 * M_PI), sin (x + 1.333 * M_PI), 1.0);
        cairo_rectangle(cr, 0, 0, 400, 300);
        cairo_fill (cr);
        image.update();
        window.handleEvents();
    }

    cairo_destroy (cr);
}