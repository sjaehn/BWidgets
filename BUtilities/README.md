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
 ├── Node
 ├── Point
 ├── Property
 ├── Shape
 ╰── URID
```


### Any

Container to type-safely take up the content of any copy constructible type.
Similar classes are in the std (C++>=17) and boost.


### Area \<T\>

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
`BUTILITIES_DICTIONARY_DATAFILE` (default "Dictionary.data") in the format
(example):
```
{
    {
        "Yes",       
        {
            {"de_DE", "Ja"},
            {"fr_FR", "Oui"}
        }
    },
    {
       "No",       
        {
            {"de_DE", "Nein"},
            {"fr_FR", "Non"}
        }
    }
}
```
with the language_code is represented as the full or partial POSIX locale 
(language[_territory][.codeset][@modifier], e. g. "en_US.utf8").

To use an alternative dictionary, define the 
`BUTILITIES_DICTIONARY_DATAFILE` variable prior to the *compiling* of the
Dictionary. Or add translations at runtime using `add()`. Or include a GNU
gettext message catalogue (.mo) as fallback using `alsoUseCatalogue()`.


### Node \<T\>

Template class describing a node as a point with up to two handles.


### Point \<T\>

2D Point coordinates.


### Property  \<Tid, Tdata\>

A Property is a data pair and consists of a constant @a ID and the assigned
@a data. It can only be set upon construction. No change, no assignment.


### Shape \<T, res\>

A Shape is a container of transferred nodes to interpolate any point between 
the nodes and thus to create a 2D graph.


### URID

Map class to store and convert URIs.


## Functions

### stof

Converts a floating point number-containing string to a float value. Similar 
to std::stof. But this method is tolerant over different types of decimal 
signs (point / comma).


### to_string

Converts a floaing point number into a string output with a defined format. 
Similar to std::to_string. But the format specifier @a format allows a
formatted value output.


### mix

Mixes two values in a given ratio.