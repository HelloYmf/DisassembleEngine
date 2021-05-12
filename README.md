# DisassembleEngine
  
### 开发环境：

Win10  VisualStudio2019  多字符集编码   x86
  
### 介绍：
  基于Win32 SDK实现的带有图形界面的反汇编引擎，基本框架已经实现。支持16位和32位模式下对Intel指令的解析。
    目前可以解析：
        前缀指令，
        部分OpCode(mov,add,nop)，
        ModR/M，
        SIB，
        立即数。
       
### 需要完善：
  指令解析部分，让其支持解析更多的指令。
