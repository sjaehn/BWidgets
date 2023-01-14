/* Color.hpp
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

#ifndef BSTYLES_COLOR_HPP_
#define BSTYLES_COLOR_HPP_

#include <algorithm>
#include <cmath>

#define CAIRO_RGB(col) (col).red, (col).green, (col).blue
#define CAIRO_RGBA(col) (col).red, (col).green, (col).blue, (col).alpha

namespace BStyles
{


/**
 *  @brief RGBA colors represented by values ranging from 0.0 to 1.0, each.
 */
struct Color
{
    static constexpr double normalLighted = 0.0;
    static constexpr double highLighted = 0.5;
    static constexpr double illuminated = 0.333;
    static constexpr double shadowed = -0.333;
    static constexpr double darkened = -0.5;
    
    double red, green, blue, alpha;

    /**
     *  @brief  Creates an "empty" %Color representing invisible black.
     */
    constexpr Color () : Color (0.0, 0.0, 0.0, 0.0) {}


    /**
     *  @brief  Creates a %Color from the passed RGB(A) values.
     *  @param red  Red value [0,1] of RGB(A).
     *  @param green  Green value [0,1] of RGB(A).
     *  @param blue  Blue value [0,1] of RGB(A).
     *  @param alpha  Optional, alpha value [0,1] of RGBA. Default = 1.0.
     */
	constexpr Color (const double red, const double green, const double blue, double alpha = 1.0) :
        red (red), green (green), blue (blue), alpha (alpha)
    {

    }

    //constexpr Color (const Color& that) = default;

	bool operator== (const Color& that) const 
    {
        return (red == that.red) && (green == that.green) && (blue == that.blue) && (alpha == that.alpha);
    }

	bool operator!= (const Color& that) const {return !operator== (that);}

    /**
     *  @brief  Sets colors from HSV.
     *  @param hue  Hue [0,1].
     *  @param saturation  Saturation [0,1].
     *  @param value  Value [0,1].
     */
    void setHSV (const double hue, const double saturation, const double value)
    {
        const double hi = floor (6.0 * hue);
        const double f = 6.0 * hue - hi;
        const double p = value * (1.0 - saturation);
        const double q = value * (1.0 - f * saturation);
        const double t = value * (1.0 - (1.0 - f) * saturation);

        switch (static_cast<int>(hi))
        {
            case 6:
            case 0: red = value;
                    green = t;
                    blue = p;
                    break;

            case 1: red = q;
                    green = value;
                    blue = p;
                    break;

            case 2: red = p;
                    green = value;
                    blue = t;
                    break;

            case 3: red = p;
                    green = q;
                    blue = value;
                    break;

            case 4: red = t;
                    green = p;
                    blue = value;
                    break;

            case 5: red = value;
                    green = p;
                    blue = q;
                    break;
        };
    }

    /**
     *  @brief  Sets colors from HSV.
     *  @param hue  Hue [0,1].
     *  @param saturation  Saturation [0,1].
     *  @param value  Value [0,1].
     *  @param alpha  Optional, alpha value [0,1]. Default = 1.0.
     */
    void setHSV (const double hue, const double saturation, const double value, double alpha)
    {
        setHSV (hue, saturation, value);
        this->alpha = alpha;
    }

    /**
     *  @brief  Gets the hue for this %Color.
     *  @return  Hue [0,1]. 
     */
    double hue () const
    {
        const double mx = std::max ({red, green, blue});
        const double mn = std::min ({red, green, blue});

        if (mx == mn) return 0.0;
        if (mx == red) return ((green - blue) / (mx - mn) + (blue > green) * 6.0) / 6.0;
        if (mx == green) return (2.0 + (blue - red) / (mx - mn)) / 6.0;
        return (4.0 + (red - green) / (mx - mn)) / 6.0;
    }

    /**
     *  @brief  Gets the saturation for this %Color.
     *  @return  Saturation [0,1]. 
     */
    double saturation () const
    {
        const double mx = std::max ({red, green, blue});
        const double mn = std::min ({red, green, blue});

        if (mx == 0.0) return 0.0;
        return (mx - mn) / mx;
    }

    /**
     *  @brief  Gets the value (HSV) for this %Color.
     *  @return  Value [0,1]. 
     */
    double value () const
    {
        return std::max ({red, green, blue});
    }

	/**
	 *  @brief Changes the red, green and blue values of the by a given brightness.
	 *  @param brightness  Brightness ranging from -1.0 (full darkness => black
	 *  over 0.0 (normal => unchanged) to 1.0 (full brightness => white)
     *  @return  %Color after illumination. 
	 */
	Color illuminate (const double brightness) const
    {
        const double b = (brightness < -1.0 ? -1.0 : (brightness > 1.0 ? 1.0 : brightness));
        if (b < 0) return  Color (red * (b + 1.0), green * (b + 1.0), blue * (b + 1.0), alpha);
        else if (b > 0) return Color (red + (1.0 - red) * b, green + (1.0 - green) * b, blue + (1.0 - blue) * b, alpha);
        else return *this;
    }
};

constexpr Color white = Color (1.0, 1.0, 1.0, 1.0);
constexpr Color black = Color (0.0, 0.0, 0.0, 1.0);
constexpr Color red = Color (1.0, 0.0, 0.0, 1.0);
constexpr Color green = Color (0.0, 1.0, 0.0, 1.0);
constexpr Color blue = Color (0.0, 0.0, 1.0, 1.0);
constexpr Color yellow = Color (1.0, 1.0, 0.0, 1.0);
constexpr Color grey = Color (0.5, 0.5, 0.5, 1.0);
constexpr Color lightred = Color (1.0, 0.5, 0.5, 1.0);
constexpr Color darkred = Color (0.5, 0.0, 0.0, 1.0);
constexpr Color lightyellow = Color (1.0, 1.0, 0.5, 1.0);
constexpr Color darkyellow = Color (0.5, 0.5, 0.0, 1.0);
constexpr Color lightgreen = Color (0.5, 1.0, 0.5, 1.0);
constexpr Color darkgreen = Color (0.0, 0.5, 0.0, 1.0);
constexpr Color lightblue = Color (0.5, 0.5, 1.0, 1.0);
constexpr Color darkblue = Color (0.0, 0.0, 0.5, 1.0);
constexpr Color lightlightgrey = Color (0.9, 0.9, 0.9, 1.0);
constexpr Color lightgrey = Color (0.75, 0.75, 0.75, 1.0);
constexpr Color darkgrey = Color (0.25, 0.25, 0.25, 1.0);
constexpr Color darkdarkgrey = Color (0.1, 0.1, 0.1, 1.0);
constexpr Color grey80 = Color (0.8, 0.8, 0.8, 1.0);
constexpr Color grey60 = Color (0.6, 0.6, 0.6, 1.0);
constexpr Color grey40 = Color (0.4, 0.4, 0.4, 1.0);
constexpr Color grey20 = Color (0.2, 0.2, 0.2, 1.0);
constexpr Color invisible = Color (0.0, 0.0, 0.0, 0.0);

}

#endif /* BSTYLES_COLOR_HPP_ */
