# Easy Breakout
Breakout game, an arcade video game, and so easy to play

> Screenshot of Easy Breakout
![alt text](https://github.com/inthelamp/EasyBreakout/blob/master/EasyBreakout.png?raw=true "Easy Breakout")

### Windows version
Use the following to build Windows version of the game

``` bash
cmake -B build -DCMAKE_TOOLCHAIN_FILE=./mingw64.cmake -DCMAKE_BUILD_TYPE=MINSIZEREL
cmake --build build
```

### Linux version
Use the following to build Linux version of the game

``` bash
cmake -B build -DCMAKE_BUILD_TYPE=MINSIZEREL
cmake --build build
```

Install the game as follows

``` bash
cmake --install ./build --prefix .
cd bin/Release
```