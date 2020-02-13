# A Simple Direct3D Demo

## 程序配置
- 程序根目录下的`game_configure.json`用于相关参数的配置
> `"car"`字段中的数据用于指定小车的加速度、减速度、拐弯角度、最大速度等参数
>
> `"camera"`字段中的数据用于控制第一人称和第三人称摄像机的默认位置、朝向、鼠标转动灵敏度等参数
>
> `"random_ground"`字段中的数据用于设置随机生成场景的贴图、随机模型生成概率、随机模型缩放范围等参数
>
> `"skybox"`字段中的数据用于设置天空盒的尺寸和贴图参数
>
> `"light"`字段中的数据用于设置光源位置、生成阴影贴图所需要的光空间视锥的参数以及所生成的阴影贴图的尺寸

## 操作
- 使用`WS`键控制小车前进后退
- 使用`AD`键控制小车转向
- 使用`R`键能够在第一人称视角和第三人称视角之间切换
- 在第一人称视角下，按住鼠标左键移动鼠标能够环顾四周
- 在第三人称视角下，按住鼠标左键移动鼠标能够调整摄像机视角，摄像机始终朝向小车
- 在第三人称视角下，滑动鼠标滚轮能够滑动放缩摄像机和小车的距离
- 使用`Y`键能够打开或者关闭阴影效果

## 相关说明
- 源码使用了`C++ 17`的特性，因此编译器需要打开`C++ 17`的编译开关（如果默认没有打开）
- 随机场景生成方法参见`GameObject/JsonObjects/Ground.cpp`中的`_DecideGeneratingRegion()`和`_RandomGenerateModels()`方法
- 光照模型使用`Blinn-Phong`光照模型，阴影生成算法使用了`阴影贴图`，具体实现参见`HLSL/shadow_map_shape_ps.fx`、`HLSL/shadow_map_shape_vs.fx`以及`DxUtils/Shaders/SHdowedLightCommonVertexShader.h/.cpp`、`DxUtils/Shaders/SHdowedLightCommonPixelShader.h/.cpp`
- 渲染框架实现了一个渲染命令队列，具体参见`DxUtils/RenderCommandQueueManager.h/.cpp`
- 外设输入控制使用了`DirectInput`库，具体参见`DxUtils/InputManager.h/.cpp`
- 为了方便组合模型的搭建，使用了json文件来进行描述，具体参见`SimpleModels`文件夹下的模型描述文件
- 使用了`rapidjson`库来进行json文件的解析，具体参见`GameObjects/JsonObjects/JsonModel.h/.cpp`

## 编译
> - 源程序通过CMake构建工程，因此建议使用CMake进行编译（`Visual Studio 2017`及以后版本支持CMake编译。
> - 建议使用`vcpkg`安装相关依赖

1. 安装 `CMake`

2. 安装 `vcpkg`   

``` shell
git clone https://github.com/Microsoft/vcpkg
cd vcpkg
.\booststrap-vcpkg.bat
.\vcpkg integrate install
```

3. 使用 `vcpkg` 安装依赖
```shell
cd .
.\vcpkg_install.bat
```

4. 设置`CMake`的命令行参数
```
-DCMAKE_TOOLCHAIN_FILE=%%你的vcpkg根目录%%\scripts\buildsystems\vcpkg.cmake
```

>注意: 如果你的IDE支持CMake（如`Visual Studio 2017`），这个参数可以在IDE的CMake设置中进行配置。

5. 使用`CMake`构建工程（如果使用`Visual Studio 2017`，那么可以直接生成工程）。

## 编译工具
- vcpkg
- CMake

## 依赖
- Direct3D 11
- DirectInput 8
- DirectXTex
- rapidjson

## 联系方式
- a1026121287@163.com
- yuwenhuisama@outlook.com
