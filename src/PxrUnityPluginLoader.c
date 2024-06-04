#include <dlfcn.h>
#include "../include/Globals.h"

void Pxr_UnityPluginLoad(void *unityInterfaces) {
    __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s was called!", __func__ );

    void (*PxrUnityPluginLoad)(void *);

    void *handle = dlopen("./libpxr_api.so", RTLD_LAZY);
    PxrUnityPluginLoad = dlsym(handle, "UnityPluginLoad");

    PxrUnityPluginLoad(unityInterfaces);
}