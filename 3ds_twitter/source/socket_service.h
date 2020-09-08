#ifndef SOCKET_SERVICE_H
#define SOCKET_SERVICE_H

#include <3ds.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdarg>
#include <cstdio>
#include <malloc.h>
#include <stdlib.h>

class SocketService
{
private:
    u32 *contextAddr;
    u32 contextAlign;
    u32 contextSize;
    void allocateBuffer(u32 **SOC_buffer);

public:
    SocketService(u32 *contextAddr,
                  u32 contextAlign,
                  u32 contextSize);

    void init();
    void failExit(const char *fmt, ...);
    static void shutdown();
};

#endif