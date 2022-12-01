# 42_FdF
This project aims to represent the wire mesh of a map in isometric 3D.

## Example

## Expected Result

## MinilibX
This project use the "MinilibX" library.  
The installation process include the compilation from sources, the linking and the creation of the static library.

Some external packages can be necessary, depending on your OS: https://github.com/42Paris/minilibx-linux  

A MacOs version is included in the "lib" folder. In this case, update the makefile for "minilibx-macos".

## Install
Create or update the "fdf" program from sources.
```
make
```

## Reinstall
Recompile completely the program.
```
make re
```

## Clean
Delete object files created during installation.
```
make clean
```

## Uninstall
Delete object files but also the compiled program.  
It will not affect the source code.
```
make fclean
```

## Usage
```
./fdf test_maps/42.fdf
```

## MAN (complete user manual)
```
./fdf -h
```

## Screenshots

## Notes
I recommand to use the "clang" compiler because "gcc" generates linking error with the minilibx.  
Check that clang compiler is installed on your system.

## Keywords
Simple graphics library  
Plot of segments  
Events  
3D to 2D projection  
