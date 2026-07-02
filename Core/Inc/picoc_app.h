/* PicoC 应用层头文件 — 串口 REPL 交互与脚本加载引擎 API
 *
 * 主要接口：
 *   PicocApp_Init()              — 初始化 PicoC 解释器并显示启动提示符
 *   PicocApp_Abort()             — 请求中断正在执行的 PicoC 脚本
 *   PicocApp_ProcessChars()      — 处理一批 UART 字符，返回需要入队的消息
 *   PicocApp_RunSourceLine()     — 执行一行 REPL 源码
 *   PicocApp_ExecuteLoadSource() — 执行加载模式下累积的全部源代码
 *   PicocApp_Reset()             — 重置 PicoC 解释器实例
 *   PicocApp_ConsoleGetCharBlocking() — 阻塞读取单个控制台字符（供平台 I/O 层使用）
 */

#ifndef __PICOC_APP_H__
#define __PICOC_APP_H__

#include "task_msg.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 初始化 PicoC 应用：创建解释器实例，默认进入 UDP 桥接模式 */
void PicocApp_Init(void);

/* 从 UDP 桥接模式切换到 RICE REPL 模式，显示启动横幅和提示符 */
void PicocApp_ActivateRice(void);

/* 请求中断正在执行的 PicoC 脚本（供 serialTask 收到 :abort 时调用） */
void PicocApp_Abort(void);

/* 执行一行 REPL 源码（供 picocTask 收到 MSG_SOURCE_LINE 时调用） */
void PicocApp_RunSourceLine(const char *source);

/* 执行加载模式下累积的全部源代码（供 picocTask 收到 MSG_LOAD_END 时调用） */
void PicocApp_ExecuteLoadSource(void);

/* 重置 PicoC 解释器实例（供 picocTask 收到 MSG_RESET 时调用） */
void PicocApp_Reset(void);

/* 处理一批 UART 字符，返回需要入队的消息
 * 返回 1 表示 out_msg 有效，0 表示无消息（内部处理或缓冲中） */
int PicocApp_ProcessChars(const uint8_t *data, uint32_t len, TaskMsg *out_msg);

/* 阻塞读取单个控制台字符，无数据时忙等待 */
int PicocApp_ConsoleGetCharBlocking(void);

#ifdef __cplusplus
}
#endif

#endif /* __PICOC_APP_H__ */
