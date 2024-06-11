#include <android/log.h>
#include "../include/Globals.h"

typedef enum CallFrequency_ {
    NORMAL,
    FREQUENT
} CallFrequency;

typedef enum LogFunctionType_ {
    NON_IMPLEMENTED, //A function that is empty.
    IMPLEMENTED //A function that is already fully implemented
} LogFunctionType;

//Logs that the function had been called.
void LogFunction(LogFunctionType type, CallFrequency frequency, const char func[]) {
    #if VERBOSE
        #if VERBOSITY_FUNCTIONS > 0 && !FUNCTIONS_ALLOW_SPAM
        if (type == IMPLEMENTED && frequency == NORMAL)
            __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s has been called!", func);
        #endif
        #if VERBOSITY_FUNCTIONS <= 0 && !FUNCTIONS_ALLOW_SPAM
        if (type == NON_IMPLEMENTED && frequency == NORMAL)
            __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called, but not implemented!", func);
        #endif

        #if VERBOSITY_FUNCTIONS > 0 && FUNCTIONS_ALLOW_SPAM
            if (type == IMPLEMENTED && frequency == FREQUENT)
                __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s has been called!", func);
        #endif
        #if VERBOSITY_FUNCTIONS <= 0 && FUNCTIONS_ALLOW_SPAM
            if (type == NON_IMPLEMENTED && frequency == FREQUENT)
                __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called, but not implemented!", func);
        #endif
    #endif
}