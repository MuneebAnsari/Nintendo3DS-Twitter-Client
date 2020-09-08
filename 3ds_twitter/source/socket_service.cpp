#include <3ds.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <cstdarg>
#include <cstdio>
#include <malloc.h>
#include <stdlib.h>
#include "socket_service.h"

SocketService::SocketService(u32 *contextAddr, u32 contextAlign, u32 contextSize)
{
    this->contextAddr = contextAddr;
    this->contextAlign = contextAlign;
    this->contextSize = contextSize;
}

void SocketService::init()
{

    this->allocateBuffer(&this->contextAddr);
    if (this->contextAddr == NULL)
    {
        this->failExit("memalign: failed to allocate\n");
    }

    // init 3ds socket service
    Result initRes;
    if ((initRes = socInit(this->contextAddr, this->contextSize)) != 0)
    {
        this->failExit("socInit: 0x%08X\n", (unsigned int)initRes);
    }
}

void SocketService::allocateBuffer(u32 **contextAddr)
{
    *contextAddr = (u32 *)memalign(this->contextAlign, this->contextSize);
}

void SocketService::failExit(const char *fmt, ...)
{

    // if (sock > 0)
    //     close(sock);
    consoleInit(GFX_BOTTOM, NULL);
    va_list ap;

    printf(CONSOLE_RED);
    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);
    printf(CONSOLE_RESET);
    printf("\nPress B to exit\n");

    while (aptMainLoop())
    {
        gspWaitForVBlank();
        hidScanInput();

        u32 kDown = hidKeysDown();
        if (kDown & KEY_B)
            exit(0);
    }
}

void SocketService::shutdown()
{
    printf("waiting for socExit...\n");
    socExit();
}