# A Simple Direct3D Demo

## Compilation
1. Install `CMake`

2. Install `vcpkg`   

``` shell
git clone https://github.com/Microsoft/vcpkg
cd vcpkg
.\booststrap-vcpkg.bat
.\vcpkg integrate install
```

3. Install dependencies with `vcpkg`
```shell
.\vcpkg_install.bat
```

4. Set `CMake cmd parameter`
```
-DCMAKE_TOOLCHAIN_FILE=%vcpkg root%\scripts\buildsystems\vcpkg.cmake
```

>Tips: If your IDE support CMake like `Visual Studio 2017`, this cmd parameter can be setup in the IDE project settings.

5. Compile project with `CMake` (`Visual Studio 2017` or `visual studio code + C++ extension + CMake extension`  are recommanded.)

## Compile Tools
- vcpkg
- CMake

## Dpendencies
- Direct3D 11
- DirectInput 8
- DirectXTex
- rapidjson

## Contact
- a1026121287@163.com
- yuwenhuisama@outlook.com
