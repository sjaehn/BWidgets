/* Dictionary.hpp
 * Copyright (C) 2022  Sven Jähnichen
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
#ifndef BUTILITIES_DICTIONARY_HPP_
#define BUTILITIES_DICTIONARY_HPP_

#include <string>
#include <map>
#include <vector>
#include <mutex>
#include <utility>

#ifndef BUTILITIES_DICTIONARY_DATAFILE
#define BUTILITIES_DICTIONARY_DATAFILE "Dictionary.data"
#endif

#ifndef BUTILITIES_DICTIONARY_LANGUAGE
#define BUTILITIES_DICTIONARY_LANGUAGE std::locale("").name()
#endif

namespace BUtilities 
{

/**
 *  @brief  Map class to store and translate words for any language.
 *
 *  Dictionary provides an addition and a shortcut to the system locale /
 *  messages. It may store additional words and translations but it also allows
 *  fallback access to the system provided vocabulary and translations.
 *  
 *  Additional vocabulary can be stored in the 
 *  @c BUTILITIES_DICTIONARY_DATAFILE (default "Dictionary.data") in the format:
 *  @code {.cpp}
 *  {
        {
            "Word or phrase1",       
            {
                {"language_code1", "Translation1"},
                {"language_code2", "Translation2"},
                {...}
            }
        },
        {
            ...
        }
    }
 *  @endcode
 *  with the language_code is represented as the full or partial POSIX locale 
 * (language[_territory][.codeset][@modifier], e. g. "en_US.utf8").
 *
 *  To use an alternative dictionary, define the 
 *  @c BUTILITIES_DICTIONARY_DATAFILE variable prior the include of 
 *  %Dictionary. 
 *
 *  @todo  System locale / messages.
 */
class Dictionary
{
protected:
    static std::map<std::string, std::map<std::string, std::string>> map_;
    static std::string lang_;
    static std::mutex mx_;
    
public:

    /**
     *  @brief  Set the language for the global scope.
     *  @param language  Full or partial POSIX locale 
     *  (language[_territory][.codeset][@modifier], e. g. "en_US.utf8").
     */
    static void setLanguage (const std::string& language);

    /**
     *  @brief  Adds a word or a phrase to the dictionary.
     *  @param word  Word or phrase in english or word symbol.
     *  @param language  Full or partial POSIX locale 
     *  (language[_territory][.codeset][@modifier], e. g. "en_US.utf8").
     *  @param translation  Translated word.
     */
    static void add (const std::string& word, const std::string& language, const std::string& translation);

    /**
     *  @brief  Adds a word or a phrase to a dictionary.
     *  @param word  Word or phrase in english or word symbol.
     *  @param translation  Vector containing translations (language, 
     *  translation) for the @a word.
     */
    static void add (const std::string& word, const std::vector<std::pair<std::string, std::string>>& translations);

    /**
     *  @brief  Adds a list of words or phrases to a dictionary.
     *  @param translation  Vector containing words (word or phrase in
     *  english or word symbol, (language, translation)).
     */
    static void add (const std::vector<std::pair<std::string, std::vector<std::pair<std::string, std::string>>>>& translations);

    /**
     *  @brief  Translates a word or a phrase from the dictionary to the 
     *  language of the globlal scope.
     *  @param word  Word or phrase in english or word symbol to be translated.
     *  @return  Translation.
     *
     *  1. Returns the translation for the full locale symbol stored
     *     (e. g. "de_AT.utf8") if it exists, otherwise
     *  2. Returns the translation for the first matching language and 
     *     territory from the locale symbol (e. g. "de_AT") if it exists, 
     *     otherwise
     *  3. Returns the translation for the first matching language from the 
     *     locale symbol (e. g. any "de") if it exists, otherwise
     *  4. TODO: Return the system-provided translation for the full language 
     *     symbol, otherwise
     *  5. Returns @a word.
     */
    static std::string get (const std::string& uri);

private:
    static std::map<std::string, std::map<std::string, std::string>> makeMap ();
};

}

#endif /* BUTILITIES_DICTIONARY_HPP_ */