#ifndef _COMMANDS_FLAGS_H_
#define _COMMANDS_FLAGS_H_

// 这个头文件服务端和客户端都要包含
// 用于将合法的命令与FLAG参数绑定

#define COMMANDS_FLAGS_CD   0x00000001
#define COMMANDS_FLAGS_LS   0x00000002
#define COMMANDS_FLAGS_PWD  0x00000003

#define COMMANDS_FLAGS_PUTS 0x00000010
#define COMMANDS_FLAGS_GETS 0x00000020

#define COMMANDS_FLAGS_RM    0x00000100
#define COMMANDS_FLAGS_MKDIR 0x00000200
#define COMMANDS_FLAGS_RMDIR 0x00000300

#endif // _COMMANDS_FLAGS_H_
