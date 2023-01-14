/* symbols.cpp
 * Copyright (C) 2018 - 2022  Sven Jähnichen
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

#include "../BWidgets/Window.hpp"
#include "../BWidgets/Symbol.hpp"
#include <memory>

using namespace BWidgets;

int main ()
{
    Window window (660, 440, 0, BUTILITIES_URID_UNKNOWN_URID, "B.Widgets Symbols");

    std::array<std::unique_ptr<Symbol>, static_cast<int>(Symbol::SymbolType::newFolder) + 1> symbols;
    for (int i = 0; i <= static_cast<int>(Symbol::SymbolType::newFolder); ++i)
    {
        symbols[i] = std::unique_ptr<Symbol> (new Symbol (10 + 40 * (i % 16), 10 + 40 * int (i / 16), 32, 32, Symbol::SymbolType(i)));
        window.add (symbols[i].get());
    }

    window.run();
}