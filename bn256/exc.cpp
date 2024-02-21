#include <exception>
#include <string.h>
#include "export.h"

static char ms_GlobExcp[4096] = { 0 };
static int ms_GlobExcpLen = 0;


#if defined(_MSC_VER)
class InternalException : public std::exception
{
public:
    InternalException(const char* err) : std::exception(err) {}
};
#endif

void ThrowException(const char* s_Messg)
{
    ms_GlobExcpLen = strlen(s_Messg);
    memcpy(ms_GlobExcp, s_Messg, ms_GlobExcpLen);
#if defined(_MSC_VER)
    throw InternalException(s_Messg);
#else
    // Unmanaged exceptions cannot be handled by c# well: https://stackoverflow.com/questions/65693051/how-do-i-catch-a-custom-exception-generated-in-a-c-dll-on-c
    return;
#endif
}


extern "C" {
    EXPORT void GetLastException(unsigned char* data)
    {
        char* _data = (char*)data;

        memcpy(_data, ms_GlobExcp, ms_GlobExcpLen);
    }
}

