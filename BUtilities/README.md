# BUtilities

Contains a collection of different useful C and C++ tools.


## Classes
```
()
 ├── Any
 ├── Area
 ├── cairoplus
 |    ├── cairoplus_rgba
 |    ╰── cairoplus_text_decorations
 ├── Dictionary
 ├── Point
 ├── Property
 ╰── URID
```


### Any

Container to type-safely take up the content of any copy constructible type.
Similar classes are in the std (C++>=17) and boost.


### Area

2D coordinates of a rectangular area.


### cairoplus

C extension to the Cairo package.


### cairoplus_rgba

RGBA colors.


### cairoplus_text_decorations

Contains the font family, the font size, the font slant and the font weight.


### Dictionary

Dictionary provides an addition and a shortcut to the system locale /
messages. It may store additional words and translations but it also allows
fallback access to the system provided vocabulary and translations.

Additional vocabulary can be stored in the 
`BUTILITIES_DICTIONARY_DATAFILE` (default "Dictionary.data") in the format:
```
{
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
```
with the language_code is represented as the full or partial POSIX locale 
(language[_territory][.codeset][@modifier], e. g. "en_US.utf8").

To use an alternative dictionary, define the 
`BUTILITIES_DICTIONARY_DATAFILE` variable prior the include of 
Dictionary. 


### Point

2D Point coordinates.


### Property

A Property is a data pair and consists of a constant @a ID and the assigned
@a data. It can only be set upon construction. No change, no assignment.


### URID

Map class to store and convert URIs.


## Functions