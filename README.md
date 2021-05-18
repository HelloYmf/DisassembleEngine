# 反汇编引擎

### 开发环境：
Win10  VisualStudio2019 Win32SDK 多字节集 x86

### 介绍：
基于Win32 SDK实现的带有图形界面的反汇编引擎，基本框架已经完成。支持16位和32位模式下对Intel指令的解析。

### 用到知识：

硬编码(Intel白皮书)
    
### 目前可以解析：
前缀指令，部分OpCode(mov,add,nop)，ModR/M，SIB，立即数。

### 需要完善：
指令解析部分，让其支持解析更多的指令。

### 演示：
![反汇编引擎-解析结果1](https://i.loli.net/2021/05/12/y2kMTLq6cY7edHj.png)

![反汇编引擎-解析结果2](https://i.loli.net/2021/05/12/GxzvWyrhsBg7ZDN.png)
