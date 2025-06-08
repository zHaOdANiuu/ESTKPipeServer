# ESTKPipeServer

## 什么是 ESTKPipeServer？

### 项目介绍

ESTKPipeServer 是一个基于命名管道(Named Pipe)的外部通信服务,专为支持 [ExtendScript](https://extendscript.docsforadobe.dev/) 规范的 Adobe 系列软件设计。

### 快速开始

以 After Effect 为例子
运行After Effect,同时打开[pwsh](https://learn.microsoft.com/zh-cn/powershell/scripting/install/installing-powershell-on-windows?view=powershell-7.5#install-powershell-using-winget-recommended)
然后运行以下命令

```powershell
cd .\frontend\
.runServer.ps1
```

### 编译构建

```powershell
cd .\build\
cmake --build .
```

## 开发背景

当尝试与 Adobe 软件进行外部通信时,遇到以下问题:

### 1. 直接命令执行

通过 After.exe -s 发送脚本命令的方式存在明显局限,通常需要借助临时文件传递执行结果

### 2. 官方调试工具限制

使用 Adobe 官方的 [ExtendScript Debugger](https://marketplace.visualstudio.com/items?itemName=Adobe.extendscript-debug) 需要依赖 Node.js 环境,并且逆向分析表明 Adobe 使用私有的 BridgeTalk 协议实现通信,难以二次开发

### ESTKPipeServer 通过自主实现的管道通信方案,完美解决了上述痛点,遥遥领先

## 技术优势

| diff          | Afterfx Cli       | ExtendScript Debugger | ESTKPipeServer   |
|---------------|-------------------|-----------------------|------------------|
| 环境依赖      | 无                | Node.js               | 无               |
| 执行效率      | 低                | 高                    | 遥遥领先           |
| 通信稳定性    | 中                | 高                    | 遥遥领先            |
| 开发扩展性    | 无                | 协议封闭              | 完全开源可控     |

## 项目结构

```test
ESTKPipeServe
├─backend  // 后端cpp代码
└─frontend // 前端powershell脚本
```
