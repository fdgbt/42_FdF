# 42_FdF
This project aims to represent the wire mesh of a map in 3D.

## Example
![Screenshot 2022-12-17 at 05-08-52 fdf fr pdf](https://user-images.githubusercontent.com/52746061/208224943-5dac3770-68c6-4598-998c-c7f87e2f023c.png)  
Example of a Conical representation.

## Expected Result
The objective is to create graphically the schematic representation in “wireframe” (or "Fil de Fer" in French) of a map in relief by connecting different points (x, y, z) by segments.  
The coordinates of the map will be stored in a file passed in parameter, here is an example with the map "42.fdf":

![Screenshot 2022-12-17 at 05-10-29 fdf fr pdf](https://user-images.githubusercontent.com/52746061/208225048-76bb29ad-3c6b-411a-8043-c6f8fba7ff8a.png)  

Each number corresponds to a point in space:
- The horizontal position corresponds to its abscissa.  
- The vertical position corresponds to its ordinate.
- The value corresponds to its altitude.

By executing the command ```./fdf 42.fdf```, we should see something similar to the picture below.  
![Screenshot 2022-12-17 at 05-11-10 fdf fr pdf](https://user-images.githubusercontent.com/52746061/208225368-5b75a8b6-c537-40bf-b472-8801e84ce048.png)  

A minimal of two projections were expected.  
In my case, three types of projections are included in the program:
- Isometric
- Parallel
- Perspective

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
