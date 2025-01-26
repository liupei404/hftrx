ARM处理器编译环境准备说明如下.

ATMEGA/ATXMEGA:

编译时使用

AVR Studio 4.19 (build 730):
http://www.atmel.com/Images/AvrStudio4Setup.exe

必须安装 
Atmel AVR 8-bit and 32-bit Toolchain 3.4.2 - Windows 
http://www.atmel.com/images/avr-toolchain-installer-3.4.2.1573-win32.win32.x86.exe

ARM:

为了进行编译，使用了 www.yagarto.de 网站上的一组工具
此外，在针对 CORTEX-M3 处理器进行编译时，会使用 ARM LIMITED 的 CMSIS 库。该目录与项目目录同级. 

安装两个安装 – 
yagarto-bu-2.23.1_gcc-4.7.2-c-c++_nl-1.20.0_gdb-7.5.1_eabi_20121222.exe
yagarto-tools-20121018-setup.exe

编译器更新 - 现在在这里: https://launchpad.net/gcc-arm-embedded
最新版本 - 
https://developer.arm.com/-/media/Files/downloads/gnu-rm/6_1-2017q1/gcc-arm-none-eabi-6-2017-q1-update-win32.exe
See:
https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads
旧产品页面:
https://launchpad.net/gcc-arm-embedded

CMSIS:
https://silver.arm.com/download/ARM_and_AMBA_Architecture/CMSIS-SP-00300-r4p4-00rel0/CMSIS-SP-00300-r4p4-00rel0.tgz (.zip - 里面的格式文件)
See:
https://developer.arm.com/embedded/cmsis
https://github.com/ARM-software/CMSIS_5/releases/tag/5.2.0

一般的:

在product.h文件中选择目标项目配置
根据所选的配置和目标处理器（arm/atmega），选择一对配置文件
.\board\*ctlstyle*.h 和 .\board\*cpustyle*.h.
ctlstyle 描述外部（与处理器相关）硬件特性 - spi 总线上设备的地址，
使用的芯片类型和指示器类型（等等）. 
cpustyle 描述处理器引脚的分配（I/O 端口之间的分配）.


