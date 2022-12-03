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
![42](https://user-images.githubusercontent.com/52746061/205414797-4ea6928f-4eaf-401a-871f-6241bd930b78.png)  
![42-h](https://user-images.githubusercontent.com/52746061/205414817-995f5869-9c09-4fe6-b7f9-927e4b7592cf.png)  
![42-p](https://user-images.githubusercontent.com/52746061/205414827-06ce5a62-fdd0-4e33-bdeb-1682fd5bbbb8.png)  
![elem-h](https://user-images.githubusercontent.com/52746061/205414883-747c82c1-f3d0-4f7c-ae2b-cee0d791b69b.png)  
![pyra-h](https://user-images.githubusercontent.com/52746061/205414904-2aae3db0-1004-4ee3-bc1f-852ba4e38efa.png)  
![France](https://user-images.githubusercontent.com/52746061/205414742-305a9893-7d30-4d29-98eb-e82c2e5f5282.png)  

More screenshots are available in the "screens" folder.  

## Notes
I recommand to use the "clang" compiler because "gcc" generates linking error with the minilibx.  
Check that clang compiler is installed on your system.

If there is permission issue:
```
chmod 774 lib/minilibx-linux/configure
```

## Keywords
Simple graphics library  
Plot of segments  
Events  
3D to 2D projection  
