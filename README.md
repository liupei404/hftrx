# 高频梦想接收器项目 (高频梦想接收器)
## 作者 吉娜·扎维多夫斯基 mgs2001@mail.ru UA1ARN

环境准备及编译说明：

## 微控制器：

### Windows

1. 设置环境（用于构建项目的编译器和实用程序） <br>
1.1 **ARM:** ARM GNU Toolchain https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads (最新测试版本 arm-none-eabi-gcc (Arm GNU Toolchain 13.2.rel1 (Build arm-13.7)) 13.2.1 20231009) <br>
1.2 **ATMEGA/ATXMEGA:** AVR 8-bit Toolchain https://www.microchip.com/mplab/avr-support/avr-and-arm-toolchains-c-compilers 或者 https://blog.zakkemble.net/avr-gcc-builds/<br> 直接链接 https://github.com/ZakKemble/avr-gcc-build/releases/download/v12.1.0-1/avr-gcc-12.1.0-x64-windows.zip (解压，在PATH环境变量中设置BIN文件夹的路径)<br>
1.3 **RISC-V:** riscv-none-elf-gcc.exe (xPack GNU RISC-V Embedded GCC v13.2.0-2) https://github.com/xpack-dev-tools/riscv-none-elf-gcc-xpack/releases/ <br>
https://github.com/xpack-dev-tools/riscv-none-elf-gcc-xpack/releases/download/v13.2.0-2/xpack-riscv-none-elf-gcc-13.2.0-2-win32-x64.zip <br>
要启用编译，请更改文件 CMSIS_5/CMSIS/Core_A/Include/cmsis_gcc.h используя cmsis_5_riscv_patch.diff <br>
1.4 **构建实用程序:** https://xpack.github.io/dev-tools/windows-build-tools/releases/ https://github.com/xpack-dev-tools/windows-build-tools-xpack/releases/download/v4.4.1-2/xpack-windows-build-tools-4.4.1-2-win32-x64.zip <br>
1.5 **用于使用 GIT 存储库的实用程序** https://git-scm.com/downloads <br>

2. 下载其他库并将它们解压到比项目文件夹更高的级别. <br>
2.1 **ATMEL ARM:** 如果您使用的是 Atmel ARM (SAM) 处理器，请下载高级软件框架 (ASF) 包并将其解压到“xdk-asf”文件夹中. <https://www.microchip.com/mplab/avr-support/advanced-software-framework <br>

3. 安装IDE进行开发 <br>
3.1 下载并安装 Eclipse https://www.eclipse.org/downloads/ <br>
3.2 在顶部菜单中 Help -> Check for updates, 安装更新 <br>
3.3 在顶部菜单中 Help -> Eclipse Marketplace, 安装更新 <br>
3.4 在顶部菜单中 Help -> Eclipse Marketplace, 使用搜索安装 GNU MCU Eclipse 扩展

4. 将项目放在一起 <br>
4.1 使用命令下载最新版本的项目 "git clone https://github.com/ua1arn/hftrx hftrx" <br>
4.2 前往目录 hftrx "cd hftrx"<br>
4.3 下载子模块 "git submodule update --init --recursive" <br>
4.4 通过打开项目 File -> Open projects from File System
4.5 将 product_template.h 复制到 product.h <br>

4.4 让我们取消注释所选配置所需的常量 <br>
4.5 在 Eclipse 菜单中, Project -> Build configurations -> Set active 选择所需的处理器（或通过ToolBox中的锤子下拉菜单）. Build target 选择 default.

5. 闪烁 <br>
5.1 复制的固件位于文件夹中 /build/<processor>/ <br>
5.2 要通过引导加载程序更新 RENESAS 处理器的固件，命令文件使用项目中的实用程序 https://sourceforge.net/projects/dfu-util/files/latest/download

### Linux

需要安装的包:
- arm-none-eabi-gcc (gcc-arm-none-eabi for Ubuntu)
- arm-none-eabi-newlib (libnewlib-arm-none-eabi for Ubuntu)
- dfu-util

根据微控制器，选择映像构建目录（对于 Sokol Pro“build/stm32mp157axx”）。此外，图像构建目录隐含在“BUILD_DIR”变量中

#### 建筑公用设施

所有脚本均显示为从存储库的根目录启动

- stm32image
  ```shell
  cd tools/stm32image
  make
  cp stm32image $BUILD_DIR
  ```
- bin2ihex
  ```shell
  cd tools/bin2ihex
  make
  cp bin2ihex $BUILD_DIR
  ```

#### 构建镜像

##### 应用图片
- 将 `product_template.h` 复制到 `product.h`
- 使用命令下载所有子模块 `git submodule update --init --recursive`
- 在 `$BUILD_DIR` 目录中运行 `make`

##### 装载机
- 将 `product_template.h` 复制到 `product.h`
- 在 `product.h` 中取消注释该行
  ```C
  #define WITHISBOOTLOADER	1	/* 我们使用相应的 Build Target 来编译和组装 bootloader */
  ```
- 使用命令下载所有子模块 `git submodule update --init --recursive`
- 在 `$BUILD_DIR` 目录中运行 `make bootloader`

## FPGA:

使用 Quartis II 13.1（带更新）付费版本 http://download.altera.com/akdlm/software/acdsinst/13.1/162/ib_tar/Quartus-13.1.0.162-windows-complete.tar <br>
并在之后更新 http://download.altera.com/akdlm/software/acdsinst/13.1.4/182/update/QuartusSetup-13.1.4.182.exe

## 一般的:

在product.h文件中选择目标项目配置 <br>
根据所选的配置和目标处理器（arm/atmel），选择一对配置文件 <br>
.\board\*ctlstyle*.h 和 .\board\*cpustyle*.h. <br>
ctlstyle 描述外部（与处理器相关）硬件特性 - spi 总线上设备的地址、使用的芯片类型和指示器类型（等等）.  <br>
cpustyle 描述处理器引脚的用途（I/O 端口之间的分配）.

