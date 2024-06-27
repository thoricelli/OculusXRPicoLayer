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

    //Logging causes physics to break?
    #if VERBOSE
    if (type == IMPLEMENTED) {
        #if VERBOSITY_FUNCTIONS >= 0
            if (frequency == NORMAL)
                __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "[IMPLEMENTED] %s called.", func);
            #if FUNCTIONS_ALLOW_SPAM
                else
                    __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "[IMPLEMENTED, SPAM] %s called.", func);
            #endif
        #endif
    } else if (type == NON_IMPLEMENTED) {
        #if VERBOSITY_FUNCTIONS <= 0
            if (frequency == NORMAL)
                __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "[NOT IMPLEMENTED] %s called.", func);
            #if FUNCTIONS_ALLOW_SPAM
                else
                    __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "[NOT IMPLEMENTED, SPAM] %s called.", func);
            #endif
        #endif
    }
    #endif
}