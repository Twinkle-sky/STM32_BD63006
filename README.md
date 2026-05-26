

# STM32_BD63006

STM32F103C8T6 嵌入式固件工程，基于 STM32CubeMX 生成，使用 CMake + ARM GCC 工具链构建。

## 硬件

| 项目 | 说明 |
|------|------|
| MCU  | STM32F103C8T6 (Cortex-M3) |
| 外设 | GPIO (PA3 LED 输出) |

## 工程结构

```
├── Core/                  # 用户代码
│   ├── Inc/               # 头文件
│   └── Src/               # 源文件
├── Drivers/               # HAL 库 & CMSIS
│   ├── CMSIS/
│   └── STM32F1xx_HAL_Driver/
├── cmake/                 # CMake 工具链 & STM32CubeMX 子模块
├── CMakeLists.txt         # 顶层 CMake 配置
├── CMakePresets.json      # CMake 预设 (Debug / Release)
└── STM32_BD63006.ioc      # STM32CubeMX 工程文件
```

## 构建

### 前置条件

- [CMake](https://cmake.org/) >= 3.22
- [Ninja](https://ninja-build.org/)
- [ARM GNU Toolchain](https://developer.arm.com/Tools%20and%20Software/GNU%20Toolchain) (arm-none-eabi-gcc)

### 编译

```bash
# Debug 构建
cmake --preset Debug
cmake --build build/Debug

# Release 构建
cmake --preset Release
cmake --build build/Release
```

### 烧录

使用 ST-Link / J-Link 等调试器烧录生成的 ELF 或 HEX 文件：

```bash
# 示例: ST-Link (通过 OpenOCD)
openocd -f interface/stlink.cfg -f target/stm32f1x.cfg \
  -c "program build/Debug/STM32_BD63006.elf verify reset exit"
```

## License

本项目采用 [MIT License](LICENSE) 开源。

ST 官方驱动文件 (`Drivers/`) 版权归 STMicroelectronics 所有，按其自带许可证分发。
