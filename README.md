## Introduction

`screen-util` (in the `components` directory) is a set of screen utilities written in C++ for ESP32 series MCUs.

## VSCode and CMake

To prepare the environment for ESP32 development, you need to add the follow configurations
to you settings file (For Linux, it's ~/.config/Code/User/settings.json)

> If you install the ESPIDF extension, this should have been done automatically.

> The following example contains user-specific pathes, change it when necessary.

```jsonc
{
    //...
    "idf.espIdfPath": "${env:IDF_PATH}",
    "idf.pythonBinPath": "${env:HOME}/.espressif/python_env/idf4.4_py3.8_env/bin/python",
    "idf.toolsPath": "${env:HOME}/.espressif",
    "idf.customExtraPaths": "${env:HOME}/.espressif/tools/xtensa-esp32-elf/esp-2021r2-8.4.0/xtensa-esp32-elf/bin:${env:HOME}/.espressif/tools/xtensa-esp32s2-elf/esp-2021r2-8.4.0/xtensa-esp32s2-elf/bin:${env:HOME}/.espressif/tools/xtensa-esp32s3-elf/esp-2021r2-8.4.0/xtensa-esp32s3-elf/bin:${env:HOME}/.espressif/tools/riscv32-esp-elf/esp-2021r2-8.4.0/riscv32-esp-elf/bin:${env:HOME}/.espressif/tools/esp32ulp-elf/2.28.51-esp-20191205/esp32ulp-elf-binutils/bin:${env:HOME}/.espressif/tools/esp32s2ulp-elf/2.28.51-esp-20191205/esp32s2ulp-elf-binutils/bin:${env:HOME}/.espressif/tools/cmake/3.20.3/bin:${env:HOME}/.espressif/tools/openocd-esp32/v0.11.0-esp32-20211220/openocd-esp32/bin:${env:HOME}/.espressif/tools/ninja/1.10.2",
    "idf.customExtraVars": "{\"OPENOCD_SCRIPTS\":\"${env:HOME}/.espressif/tools/openocd-esp32/v0.11.0-esp32-20211220/openocd-esp32/share/openocd/scripts\"}",
    "idf.gitPath": "/usr/bin/git"
    //...
}
```

The environment variable `IDF_PATH` is also used by CMakeLists.txt,
so setting `idf.espIdfPath` (of VSCode) by `IDF_PATH` is a good way to keep the configuration consistent.

### Notice

The first time you open the project, the CMake extension of VSCode will create the `build` directory
based on CMakeLists.txt automatically, which is not what ESP32 needs.

You can try removing the `build` directory and then `Ctrl-P` > `ESP-IDF: Build your project`,
which should fix this problem.
