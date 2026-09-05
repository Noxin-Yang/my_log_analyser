# C++ Lab 2. 日志分析器

这里的项目记录了我在中山大学计算机学院就读时完成的个人c++ lab 项目，以记录学习进度，提升能力
>
> 这是一个基于 C++ 的命令行日志分析工具，用于分析 `access.log`，输出 5XX 请求，并统计给定时间窗口内的最大请求量区间。
>查看我之前的项目
>[Lab 1. Coffeebeans Management System](https://github.com/10249204/coffeemanager)

## 项目概览

| 项目项 | 说明 |
| --- | --- |
| 开发语言 | C++ |
| 技术栈  | C++ , stl , cmake |


## 任务

实现一个日志分析工具，基于 `access.log` 完成以下功能：

1. 输出状态码为 `5XX` 的请求。
2. 找出指定时间窗口内请求数量最多的时间区间。

---

## 程序参数

程序支持以下命令行参数：

| 短参数 | 长参数 | 默认值 | 说明 |
|---|---|---|---|
| `-o path` | `--output=path` | 无 | 将 5XX 请求写入指定文件。 |
| `-p` | `--print` | 无 | 将 5XX 请求同时输出到标准输出。 |
| `-s n` | `--stats=n` | `10` | 输出出现频率最高的前 `n` 个 5XX 请求。 |
| `-w t` | `--window=t` | `0` | 统计长度为 `t` 秒的最大请求窗口。`0` 表示不统计。 |
| `-f time` | `--from=time` | 无 | 只分析大于等于该时间戳的日志。 |
| `-e time` | `--to=time` | 无 | 只分析小于等于该时间戳的日志。 |

程序调用格式如下：

```bash
my_log_analyser [OPTIONS] logs_filename
```

---

## 日志格式

日志文件每一行表示一次访问事件，格式如下：

```text
<remote_addr> - - [<local_time>] "<request>" <status> <bytes_send>
```

字段说明：

| 字段 | 说明 |
|---|---|
| `remote_addr` | 请求来源地址 |
| `local_time` | 请求到达时间 |
| `request` | 请求内容 |
| `status` | HTTP 状态码 |
| `bytes_send` | 返回字节数 |

示例：

```text
198.112.92.15 - - [03/Jul/2024:10:50:02 -0400] "GET /shuttle/countdown/HTTP/1.0" 200 3985
198.112.92.15 - - [03/Jul/2024:10:50:04 -0400] "GET /shuttle/nosuchpath/HTTP/1.0" 500 144
127.0.0.1 - - [03/Jul/2024:10:50:10 -0400] "GET /api/test HTTP/1.0" 503 200
```

---

## 运行示例

```bash
my_log_analyser access.log --output=result.txt
```

```bash
my_log_analyser access.log --output=result.txt --print --stats 5
```

```bash
my_log_analyser --stats=2 --window=60 --from=805821284 --to=807117284 access.log
```

```bash
my_log_analyser -s 2 access.log
```

```bash
my_log_analyser -w 10 access.log
```

```bash
my_log_analyser access.log -w 10
```

---

## 项目结构

| 文件 / 目录 | 作用 |
|---|---|
| `bin/main.cpp` | 程序入口，负责参数解析 |
| `lib/processLog.cpp` | 日志读取、5XX 输出、统计与窗口分析 |
| `lib/core` | 基础解析工具 |
| `lib/analysis` | 统计与窗口分析逻辑 |

---

## 构建与运行

本项目使用 CMake 构建。

```bash
cmake -S . -B out/build/x64-debug
cmake --build out/build/x64-debug
```

运行示例：

```bash
.\out\build\x64-debug\bin\my_log_analyser.exe access.log --output=result.txt --print --stats 5
```

---

## 说明

- 日志文件可能较大，程序应尽量避免一次性占用过多内存。
- 当前实现按日志顺序处理输入数据。
- 该项目为课程作业风格的命令行工具，重点是清晰的参数和输出结果。

---

## 限制

- 不使用第三方库
- 仅使用标准 C / C++ 库

