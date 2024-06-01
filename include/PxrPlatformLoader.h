#include <stdint.h>

typedef enum {
    ppfPlatformInitializeResult_Unknown = -999,
    ppfPlatformInitializeResult_NetError = -6,
    ppfPlatformInitializeResult_MissingImpl = -5,
    ppfPlatformInitializeResult_LoadImplFailed = -4,
    ppfPlatformInitializeResult_InternalError = -3,
    ppfPlatformInitializeResult_InvalidParams = -2,
    ppfPlatformInitializeResult_AlreadyInitialized = -1,
    ppfPlatformInitializeResult_Success = 0
} ppfPlatformInitializeResult;

typedef uint64_t ppfRequest;

extern ppfPlatformInitializeResult ppf_UnityInitWrapper(const char *appId);
extern ppfRequest ppf_UnityInitAsynchronousWrapper(const char *appId);