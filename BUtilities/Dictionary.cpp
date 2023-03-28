/* Dictionary.cpp
 * Copyright (C) 2022 - 2023  Sven Jähnichen
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

#include "Dictionary.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
#include <locale>

namespace BUtilities 
{

//std::mutex Dictionary::mx_;

void Dictionary::setLanguage (const std::string& language)
{
    Dict& d = getDict();
    //mx_.lock();
    d.lang_ = language;
    //mx_.unlock();
}

void Dictionary::add (const std::string& word, const std::string& language, const std::string& translation)
{
    Dict& d = getDict();
    //mx_.lock();
    d.map_[word][language] = translation;
    //mx_.unlock();
}

void Dictionary::add (const std::string& word, const std::vector<std::pair<std::string, std::string>>& translations)
{
    Dict& d = getDict();
    //mx_.lock();
    for (const std::pair<std::string, std::string>& t : translations) d.map_[word][t.first] = t.second;
    //mx_.unlock();
}

void Dictionary::add (const std::vector<std::pair<std::string, std::vector<std::pair<std::string, std::string>>>>& translations)
{
    Dict& d = getDict();
    //mx_.lock();
    for (const std::pair<std::string, std::vector<std::pair<std::string, std::string>>>& w : translations)
    {
        for (const std::pair<std::string, std::string>& t : w.second) d.map_[w.first][t.first] = t.second;
    }
    //mx_.unlock();
}

void Dictionary::alsoUseCatalogue (const std::string& cat)
{
    Dict& d = getDict();
    //mx_.lock();
    d.catalog_ = cat;
    //mx_.unlock();
}

std::string Dictionary::get (const std::string& word)
{
    Dict& d = getDict();
    //mx_.lock();
    std::string translation = "";

    // Dictionary translation using full locale symbol
    std::map<std::string, std::map<std::string, std::string>>::const_iterator it = d.map_.find (word);
    if (it != d.map_.end ()) 
    {
        std::map<std::string, std::string>::const_iterator it2 = (*it).second.find (d.lang_);
        if (it2 != (it)->second.end()) translation = (*it2).second;
    

        // Dictionary translation using language_territory from locale symbol
        if (translation == "")
        {
            const std::string lang_terr = d.lang_.substr(0, d.lang_.find_first_of("."));
            for (std::map<std::string, std::string>::const_iterator it3 = (*it).second.begin(); it3 !=(*it).second.end(); ++it3)
            {
                if (it3->first.find (lang_terr) == 0)
                {
                    translation = (*it3).second;
                    break;
                }
            }
        }

        // Dictionary translation using language only from locale symbol
        if (translation == "")
        {
            const std::string lang = d.lang_.substr(0, d.lang_.find_first_of("_"));
            for (std::map<std::string, std::string>::const_iterator it4 = (*it).second.begin(); it4 !=(*it).second.end(); ++it4)
            {
                if (it4->first.find (lang) == 0)
                {
                    translation = (*it4).second;
                    break;
                }
            }
        }
    }

    // Full locale symbol-based dictionary translation
    if ((translation == "") && (d.catalog_ != ""))
    {
        std::locale loc (d.lang_);
        std::cout.imbue (loc);
        const std::messages<char>& facet = std::use_facet<std::messages<char>>(loc);
        std::messages_base::catalog cat = facet.open (d.catalog_, loc);
        if (cat >= 0) translation = facet.get(cat, 0, 0, word);
        facet.close(cat);
    }

    // No translation found
    if (translation == "") translation = word;

    //mx_.unlock();
    return translation;
}

std::map<std::string, std::map<std::string, std::string>> Dictionary::makeMap ()
{
    std::vector<std::pair<std::string, std::vector<std::pair<std::string, std::string>>>> il =
#ifdef BUTILITIES_DICTIONARY_DATAFILE
#include BUTILITIES_DICTIONARY_DATAFILE
#else
    {}
#endif
    ;
    
    std::map<std::string, std::map<std::string, std::string>> m;
    for (const std::pair<std::string, std::vector<std::pair<std::string, std::string>>>& w : il)
    {
        for (const std::pair<std::string, std::string>& t : w.second) m[w.first][t.first] = t.second;
    }
    return m;
}

Dictionary::Dict& Dictionary::getDict()
{
    static Dict dictionaryDict_ = {Dictionary::makeMap(), BUTILITIES_DICTIONARY_LANGUAGE, BUTILITIES_DICTIONARY_EXTERNAL_CATALOGUE};
    return dictionaryDict_;
}

}