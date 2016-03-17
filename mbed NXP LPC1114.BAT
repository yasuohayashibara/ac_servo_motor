SET PATH=C:\Keil\ARM\ARMCC\bin\;C:\Program Files (x86)\Microchip\MPLAB C30\bin;C:\ProgramData\Oracle\Java\javapath;C:\Program Files (x86)\Intel\iCLS Client\;C:\Program Files\Intel\iCLS Client\;C:\Program Files\Common Files\Microsoft Shared\Windows Live;C:\Program Files (x86)\Common Files\Microsoft Shared\Windows Live;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Program Files\Intel\Intel(R) Management Engine Components\DAL;C:\Program Files\Intel\Intel(R) Management Engine Components\IPT;C:\Program Files (x86)\Intel\Intel(R) Management Engine Components\DAL;C:\Program Files (x86)\Intel\Intel(R) Management Engine Components\IPT;C:\Program Files (x86)\Symantec\VIP Access Client\;c:\Program Files (x86)\Microsoft SQL Server\90\Tools\binn\;C:\Program Files\Intel\WiFi\bin\;C:\Program Files\Common Files\Intel\WirelessCommon\;C:\Program Files\TortoiseGit\bin;C:\Program Files\doxygen\bin;;C:\Qt\4.8.6\bin;C:\Program Files (x86)\ZeroC\Ice-3.4.2\bin;C:\Program Files (x86)\V-REP3\V-REP_PLAYER;C:\Python27;C:\OpenCV2.2.0\bin;C:\ProgramData\chocolatey\lib\swig\tools\swigwin-3.0.2;C:\SDL-1.2.15;C:\Program Files (x86)\Windows Live\Shared;C:\Program Files (x86)\Skype\Phone\;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Windows\system32\config\systemprofile\.dnx\bin;C:\Program Files\Microsoft DNX\Dnvm\;C:\Program Files (x86)\Windows Kits\8.1\Windows Performance Toolkit\;C:\Program Files\Intel\WiFi\bin\;C:\Program Files\Common Files\Intel\WirelessCommon\;c:\Users\haya\AppData\Local\atom\bin;C:\ProgramData\chocolatey\bin;C:\Users\haya\AppData\Local\atom\bin
SET CPU_TYPE=LPC1114/102
SET CPU_VENDOR=NXP (founded by Philips)
SET UV2_TARGET=mbed NXP LPC1114
SET CPU_CLOCK=0x00B71B00
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\build\main.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\build\as5600.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\build\makisumiacmotor.__i"
"C:\Keil\ARM\ARMCC\bin\ArmLink" --Via ".\build\mbed_project.lnp"
"C:\Keil\ARM\ARMCC\bin\fromelf.exe" ".\build\mbed_project.axf" --i32combined --output ".\build\mbed_project.hex"
fromelf --bin -o mbed_project_LPC1114.bin build\mbed_project.axf
