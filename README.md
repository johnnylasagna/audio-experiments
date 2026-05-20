# audio-experiments

## piano

All right a bit of music theory heads up.
Modern music is basically just 12 notes.


Different instruments lay the notes out in different ways.
A piano should be the easiest instrument to write and compose on because of the linear nature of the placment of the keys.
But they ruined it with by separating the notes into white keys and black keys.
It makes it harder for me to spot the interval between notes.


So I made my own virtual piano that has all 12 notes and all the keys have the same width.
I also learnt how to generate sound from scratch in the process.

## Dependencies

Before compiling, copy miniaudio.h into the include directory for the project you want to build.

For raylib, follow the installation instructions on the official website.

If you want to set a custom font you can add one in the font directory. Name it

```font.ttf```

## Compilation


Miniaudio is a header-only library, so once the header is in place you can build the project with:

```make```

You can also build it through the VS Code task configuration.

## External libaries used

- raylib: https://www.raylib.com/
- miniaudio: https://miniaud.io/ 

## Comments

- This is not optimised for tiling managers
- Learnt a lot about namespaces and classes in the process
- Shoutout github copilot inline suggestions 
