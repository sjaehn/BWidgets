# BMusic

The BMusic namespace contains classes and algorithms for audio processing.

```
()
 ╰── Sample
```

## Sample

A `Sample` consists of the sound file meta data (format, file name, extension,
path), the audio binary data, and the sample meta data (region, loop).
 
Sample uses the sndfile library to load sound files. Thus, all file types
supported by sndfiles are supported by Sample too. In addition, Sample
supports mp3 using minimp3.