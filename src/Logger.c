#include <android/log.h>
#include "./include/Logger.h"
#include "../include/Globals.h"

//Logs that the function had been called.
void LogFunction(LogFunctionType type, CallFrequency frequency, char* func) {
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