## Introduction

`screen-util` (in the components directory) is a screen utility (C++ classes) for ESP32 series MCUs.
This is the demo project that is using the `screen-util` library.


## VSCode and CMake

To prepare the environment for ESP32 development, you need to add the follow configuration
to you settings file (~/.config/Code/User/settings.json)

> If you install the ESPIDF extension, this should have been done automatically.

> The following example contains user-specific path, change it when necessary

```jsonc
{
    //...
    "idf.espIdfPath": "/home/wallace/esp/esp-idf",
    "idf.pythonBinPath": "/home/wallace/.espressif/python_env/idf4.4_py3.8_env/bin/python",
    "idf.toolsPath": "/home/wallace/.espressif",
    "idf.customExtraPaths": "/home/wallace/.espressif/tools/xtensa-esp32-elf/esp-2021r2-8.4.0/xtensa-esp32-elf/bin:/home/wallace/.espressif/tools/xtensa-esp32s2-elf/esp-2021r2-8.4.0/xtensa-esp32s2-elf/bin:/home/wallace/.espressif/tools/xtensa-esp32s3-elf/esp-2021r2-8.4.0/xtensa-esp32s3-elf/bin:/home/wallace/.espressif/tools/riscv32-esp-elf/esp-2021r2-8.4.0/riscv32-esp-elf/bin:/home/wallace/.espressif/tools/esp32ulp-elf/2.28.51-esp-20191205/esp32ulp-elf-binutils/bin:/home/wallace/.espressif/tools/esp32s2ulp-elf/2.28.51-esp-20191205/esp32s2ulp-elf-binutils/bin:/home/wallace/.espressif/tools/cmake/3.20.3/bin:/home/wallace/.espressif/tools/openocd-esp32/v0.11.0-esp32-20211220/openocd-esp32/bin:/home/wallace/.espressif/tools/ninja/1.10.2",
    "idf.customExtraVars": "{\"OPENOCD_SCRIPTS\":\"/home/wallace/.espressif/tools/openocd-esp32/v0.11.0-esp32-20211220/openocd-esp32/share/openocd/scripts\"}",
    "idf.gitPath": "/usr/bin/git",
    //...
}
```

