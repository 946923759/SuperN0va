# SuperN0va
N0va Desktop 'converter', named after the Dance Dance Revolution game because it's funny.

Has both Python and C versions.

The C one is smaller and faster, the Python one is used as a reference (and when you don't have a C compiler).

## Usage
**Copy .ndf files outside of Program Files before using this program! The program cannot write to Program Files folder.**

Drop any .ndf on top of it to convert it. The program is extremely fast and should only take .1 sec at most.

You can drop multiple files, you can even select all the files in the folder then drag and drop them on top.

Unix/Linux usage: `./extract *.ndf` in bash, or anything else to batch execute the program.

## Compiling on Unix/Linux
If you don't already have gcc installed, google how to install it for your Unix/Linux distribution. It usually involves installing a package named `build-essential`.

Then `gcc -g extract.c -o extract`

## Compiling on Windows
### Easy option
- Download [tcc](https://www.bellard.org/tcc/)
- extract
- put in extractor.c in the tcc directory
- type `tcc extract.c` in the folder, it will produce your executable

### Tedious option
Visual Studio C++ build tools are required.
- Open VS command prompt from the start menu
- cd to this folder
- `cl extract.c`

The Python version can be packed with `pyinstaller --onefile extract.py`. The resulting exe will be 4MB.

## Some info
The video files in N0va are mp4s with 2 extra bytes at the beginning.
The static images are just PNG. You can open them in any image viewer (other than Windows) and they will work.
