=== SuperN0va ===
N0va Desktop 'converter', named after the Dance Dance Revolution game because it's funny.

Has both Python and C versions.
The C one is smaller and faster, the Python one is used as a reference (and when you don't have a C compiler).

## Compiling on Unix
`sudo apt-get install build-essential` if you don't already have the compiler installed.
`gcc -g extract.c -o extract`

## Compiling on Windows
Open the .sln in Visual Studio and compile it. C++ build tools required.

The Python version can be packed with `pyinstaller --onefile extract.py`. The resulting exe will be 4MB.

## Some info
The video files in N0va are mp4s with 2 extra bytes at the beginning.
The static images are just PNG. You can open them in any image viewer (other than Windows) and they will work.