ARM���������뻷��׼��˵������.

ATMEGA/ATXMEGA:

����ʱʹ��

AVR Studio 4.19 (build 730):
http://www.atmel.com/Images/AvrStudio4Setup.exe

���밲װ 
Atmel AVR 8-bit and 32-bit Toolchain 3.4.2 - Windows 
http://www.atmel.com/images/avr-toolchain-installer-3.4.2.1573-win32.win32.x86.exe

ARM:

Ϊ�˽��б��룬ʹ���� www.yagarto.de ��վ�ϵ�һ�鹤��
���⣬����� CORTEX-M3 ���������б���ʱ����ʹ�� ARM LIMITED �� CMSIS �⡣��Ŀ¼����ĿĿ¼ͬ��. 

��װ������װ �C 
yagarto-bu-2.23.1_gcc-4.7.2-c-c++_nl-1.20.0_gdb-7.5.1_eabi_20121222.exe
yagarto-tools-20121018-setup.exe

���������� - ����������: https://launchpad.net/gcc-arm-embedded
���°汾 - 
https://developer.arm.com/-/media/Files/downloads/gnu-rm/6_1-2017q1/gcc-arm-none-eabi-6-2017-q1-update-win32.exe
See:
https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads
�ɲ�Ʒҳ��:
https://launchpad.net/gcc-arm-embedded

CMSIS:
https://silver.arm.com/download/ARM_and_AMBA_Architecture/CMSIS-SP-00300-r4p4-00rel0/CMSIS-SP-00300-r4p4-00rel0.tgz (.zip - ����ĸ�ʽ�ļ�)
See:
https://developer.arm.com/embedded/cmsis
https://github.com/ARM-software/CMSIS_5/releases/tag/5.2.0

һ���:

��product.h�ļ���ѡ��Ŀ����Ŀ����
������ѡ�����ú�Ŀ�괦������arm/atmega����ѡ��һ�������ļ�
.\board\*ctlstyle*.h �� .\board\*cpustyle*.h.
ctlstyle �����ⲿ���봦������أ�Ӳ������ - spi �������豸�ĵ�ַ��
ʹ�õ�оƬ���ͺ�ָʾ�����ͣ��ȵȣ�. 
cpustyle �������������ŵķ��䣨I/O �˿�֮��ķ��䣩.


