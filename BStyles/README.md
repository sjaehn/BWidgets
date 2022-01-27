# BStyles

The BStyles namespace contain classes to describe a widget style.


## Types

Basic types to describe a Property. It can be a Color, or a Font, or anything
else. Like an `int` value.

```
()
 ├── Color
 ├── ColorMap
 ├── Line
 ├── Border
 ├── Fill
 ╰── Font
```


## StyleProperties

A Property is data structure containing an identifier and the data. Properties 
realized as `std::pair`. In the case of a StyleProperty, the data structure 
contain an URID and the style [Type](#Types) data. Thus, StyleProperty objects
describe widget element style properties. Like a foreground color or a widget 
border.


## Styles

Style objects describe a whole widget style. Styles may take up multiple 
[StyleProperties](#StyleProperties) within a `std::map`. Like a widget
foreground and a widget background and a widget border. Styles may also take up
other Styles within its StyleProperty elements. This can be used to describe
composite widgets.

Example:
```
┌───────────────────────────────────────────────────────┐
│TEXTBUTTONSTYLE                                        │
│┌────────────────────────────────┐                     │
││LABELSTYLE                      │                     │
││┌──────────┐┌───────┐┌─────────┐│                     │
│││FONT      ││TXCOLOR││BGCOLOR  ││┌─────────┐┌────────┐│  
│││sans, 12pt││white  ││invisible│││FGCOLOR  ││BGCOLOR ││ 
││╰──────────┘╰───────┘╰─────────┘││lightgrey││darkgrey││
│╰────────────────────────────────┘╰─────────┘╰────────┘│
╰───────────────────────────────────────────────────────┘
```

