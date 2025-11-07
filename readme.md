# SuperN0va
N0va Desktop 'converter', named after the Dance Dance Revolution game because it's funny.

Has both Python and C versions.

The C one is smaller and faster, the Python one is used as a reference (and when you don't have a C compiler).

## Usage

Head to %ProgramFiles%\N0vaDesktop\N0vaDesktopCache and find the ndfs you want to extract, then drag and drop them onto extract.exe.

Unix/Linux usage: `./extract *.ndf`

## Compiling on Unix/Linux
If you don't already have gcc installed, google how to install it for your Unix/Linux distribution. It usually involves installing a package named `build-essential`.

Then `gcc -g extract.c -o extract`

## Compiling on Windows
### Easy option
- Download [tcc](https://www.bellard.org/tcc/)
- extract zip
- put extract.c in the tcc directory
- Drag and drop it on top of tcc.exe

### Tedious option
Visual Studio C++ build tools are required.
- Open VS command prompt from the start menu
- cd to this folder
- `cl extract.c`

The Python version can be packed with `pyinstaller --onefile extract.py`. The resulting exe will be 4MB.

## Some info
The video files in N0va are mp4s with 2 extra bytes at the beginning.
The static images are just PNG. You can open them in any image viewer (other than Windows) and they will work.

