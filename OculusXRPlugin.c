#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <time.h>
#include <math.h>
#include <android/log.h>

#include "OculusXRPlugin.h"
#include "/include/PxrPlatform.h"
#include "/include/PxrPlugin.h"
#include "/include/Globals.h"

ovrpVector4f s_ColorScale = {1.0f, 1.0f, 1.0f, 1.0f};

void SetColorScale(float x, float y, float z, float w) {
    s_ColorScale.x = x;
    s_ColorScale.y = y;
    s_ColorScale.z = z;
    s_ColorScale.w = w;
}

ovrpVector4f s_ColorOffset = {1.0f, 1.0f, 1.0f, 1.0f};

void SetColorOffset(float x, float y, float z, float w) {
    s_ColorOffset.x = x;
    s_ColorOffset.y = y;
    s_ColorOffset.z = z;
    s_ColorOffset.w = w;
}

bool GetIsSupportedDevice() {
    return true;
}

bool LoadOVRPlugin(char *ovrpPath) {
    
    return Pxr_LoadPlugin();
}

void UnloadOVRPlugin() {
    
    return Pxr_UnloadPlugin();
}

Quaternion ConvertRotationWith2Vector(Vector3 from, Vector3 to) {
    float f1 = sqrtf(from.x * from.x + from.y * from.y + from.z * from.z);
    float f2 = sqrtf(to.x * to.x + to.y * to.y + to.z * to.z);
    if (f1 < 1e-6f || f2 < 1e-6f) {
        return (Quaternion){1.0f, 0.0f, 0.0f, 0.0f};
    }
    Vector3 nfrom = {from.x / f1, from.y / f1, from.z / f1};
    Vector3 nto = {to.x / f2, to.y / f2, to.z / f2};
    Vector3 axis = {nfrom.y * nto.z - nfrom.z * nto.y,
                    nfrom.z * nto.x - nfrom.x * nto.z,
                    nfrom.x * nto.y - nfrom.y * nto.x};
    float htheta = acosf(fminf(1.0f, nfrom.x * nto.x + nfrom.y * nto.y + nfrom.z * nto.z));
    Quaternion quat = {cosf(htheta), axis.x * sinf(htheta), axis.y * sinf(htheta), axis.z * sinf(htheta)};
    return quat;
}

//God, theres different versions of UserDefinedSettings... :(
void SetUserDefinedSettings(UserDefinedSettings *settings) {
    __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "Hello World! Made by thoricelli.");

    PICO_UserDefinedSettings picoUserDefinedSettings =
    {
        .stereoRenderingMode = settings->stereoRenderingMode,
        .colorSpace = settings->colorSpace,
        .systemDisplayFrequency = 72,
        .useContentProtect = 0,
        .optimizeBufferDiscards = settings->optimizeBufferDiscards,
        .enableAppSpaceWarp = settings->spaceWarp,
        .enableSubsampled = 1,
        .lateLatchingDebug = settings->lateLatchingDebug,
        .enableStageMode = 0,
    };

    Pxr_Construct(&ConvertRotationWith2Vector);
    Pxr_SetUserDefinedSettings(picoUserDefinedSettings);
    return;
}

//This would have been handy PICO...
int SetCPULevel(int cpuLevel) {
    return cpuLevel;
}

int SetGPULevel(int gpuLevel) {
    return gpuLevel;
}

void GetOVRPVersion(char* version) {
    version = OVRP_VERSION;
    return;
}

void EnablePerfMetrics(bool enable) {
    return;
}

void EnableAppMetrics(bool enable) {
    return;
}

bool SetDeveloperModeStrict(bool active) {
    return true;
}

bool GetAppHasInputFocus() {
    return true;
}

bool GetBoundaryConfigured() {
    return Pxr_GetBoundaryConfigured();
}

//bool GetBoundaryDimensions(Boundary.BoundaryType boundaryType, Vector3 dimensions) {

bool GetBoundaryDimensions(void* boundaryType, void* dimensions) {
    return Pxr_GetBoundaryDimensions(true, dimensions);
}

bool GetBoundaryVisible() {
    return Pxr_GetBoundaryVisible();
}

void SetBoundaryVisible(bool boundaryVisible) {
    Pxr_SetBoundaryVisible(boundaryVisible);
}

bool GetAppShouldQuit() {
    return false;
}

bool GetDisplayAvailableFrequencies(uint32_t *ptr, float *numFrequencies) {
    return Pxr_GetDisplayRefreshRatesAvailable(ptr, &numFrequencies);
}

bool SetDisplayFrequency(float refreshRate) {
    return Pxr_SetDisplayRefreshRate(refreshRate);
}

bool GetDisplayFrequency(float refreshRate) {
    return Pxr_GetConfigFloat(PXR_GET_DISPLAY_RATE, &refreshRate);
}

enum SystemHeadset GetSystemHeadsetType() {
    //I mean, something like that, right?
    return Meta_Quest_3;
}

bool GetTiledMultiResSupported() {
    return true;
}

void SetTiledMultiResLevel(int level) {
    return;
}

int GetTiledMultiResLevel() {
    return 1;
}

void SetTiledMultiResDynamic(bool isDynamic) {
    return;
}

bool GetEyeTrackedFoveatedRenderingSupported() {
    return false;
}

bool GetEyeTrackedFoveatedRenderingEnabled() {
    return false;
}

void SetEyeTrackedFoveatedRenderingEnabled(bool isEnabled) {
    return;
}

bool GetShouldRestartSession() {
    return false;
}

bool SetupEnvironmentDepth(EnvironmentDepthCreateParamsInternal* createParams) {
    return false;
}

bool SetEnvironmentDepthRendering(bool isEnabled) {
    return false;
}

bool ShutdownEnvironmentDepth() {
    return false;
}

bool GetEnvironmentDepthTextureId(uint id) {
    return false;
}

bool GetEnvironmentDepthFrameDesc(EnvironmentDepthFrameDescInternal* frameDesc, int eye) {
    return false;
}

bool SetEnvironmentDepthHandRemoval(bool isEnabled) {
    return false;
}

bool GetEnvironmentDepthSupported() {
    return false;
}

bool GetEnvironmentDepthHandRemovalSupported() {
    return false;
}