/* Task message definitions for serialTask -> picocTask communication */
#ifndef __TASK_MSG_H__
#define __TASK_MSG_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    MSG_SOURCE_LINE,    /* one C source line (REPL or LOAD) */
    MSG_LOAD_BEGIN,     /* :load command, enter load mode */
    MSG_LOAD_END,       /* :end command, execute loaded script */
    MSG_LOAD_ABORT,     /* :abort command in load mode, cancel load */
    MSG_RESET,          /* :reset command, reinitialize PicoC */
} TaskMsgType;

typedef struct {
    TaskMsgType type;
    uint16_t len;
    char data[64];
} TaskMsg;

#ifdef __cplusplus
}
#endif

#endif /* __TASK_MSG_H__ */
