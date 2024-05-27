#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <time.h>
#include <math.h>
#include <android/log.h>

#include "OculusXRPlugin.h"
#include "include/PXR_Plugin.h"

ovrpVector4f s_ColorScale = {1.0f, 1.0f, 1.0f, 1.0f};

extern void SetColorScale(float x, float y, float z, float w) {
    s_ColorScale.x = x;
    s_ColorScale.y = y;
    s_ColorScale.z = z;
    s_ColorScale.w = w;
}

ovrpVector4f s_ColorOffset = {1.0f, 1.0f, 1.0f, 1.0f};

extern void SetColorOffset(float x, float y, float z, float w) {
    s_ColorOffset.x = x;
    s_ColorOffset.y = y;
    s_ColorOffset.z = z;
    s_ColorOffset.w = w;
}

extern bool GetIsSupportedDevice() {
    return true;
}

extern bool LoadOVRPlugin(char *ovrpPath) {
    return Pxr_LoadPlugin();
}

extern void UnloadOVRPlugin() {
    return Pxr_UnloadPlugin();
}

//God, theres different versions of UserDefinedSettings... :(
extern void SetUserDefinedSettings(UserDefinedSettings *settings) {
    __android_log_print(ANDROID_LOG_INFO, "OculusXRPicoLayer", "Hello World! Made by thoricelli.");

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

    Pxr_SetUserDefinedSettings(picoUserDefinedSettings);
    return;
}

//This would have been handy PICO...
extern int SetCPULevel(int cpuLevel) {
    return cpuLevel;
}

extern int SetGPULevel(int gpuLevel) {
    return gpuLevel;
}

extern void GetOVRPVersion(char* version) {
    return;
}

extern void EnablePerfMetrics(bool enable) {
    return;
}

extern void EnableAppMetrics(bool enable) {
    return;
}

extern bool SetDeveloperModeStrict(bool active) {
    return true;
}

extern bool GetAppHasInputFocus() {
    return true;
}

extern bool GetBoundaryConfigured() {
    return Pxr_GetBoundaryConfigured();
}

//extern bool GetBoundaryDimensions(Boundary.BoundaryType boundaryType, Vector3 dimensions) {

extern bool GetBoundaryDimensions(void* boundaryType, void* dimensions) {
    return Pxr_GetBoundaryDimensions(true, dimensions);
}

extern bool GetBoundaryVisible() {
    return Pxr_GetBoundaryVisible();
}

extern void SetBoundaryVisible(bool boundaryVisible) {
    Pxr_SetBoundaryVisible(boundaryVisible);
}

extern bool GetAppShouldQuit() {
    return false;
}

extern bool GetDisplayAvailableFrequencies(int *ptr, int *numFrequencies) {
    return Pxr_GetDisplayRefreshRatesAvailable(ptr, numFrequencies);
}

extern bool SetDisplayFrequency(float refreshRate) {
    return Pxr_SetDisplayRefreshRate(refreshRate);
}

extern bool GetDisplayFrequency(float refreshRate) {
    return Pxr_GetConfigFloat(SystemDisplayRate, &refreshRate);
}

extern enum SystemHeadset GetSystemHeadsetType() {
    //I mean, something like that, right?
    return Meta_Quest_3;
}

extern bool GetTiledMultiResSupported() {
    return true;
}

extern void SetTiledMultiResLevel(int level) {
    return;
}

extern int GetTiledMultiResLevel() {
    return 1;
}

extern void SetTiledMultiResDynamic(bool isDynamic) {
    return;
}

extern bool GetEyeTrackedFoveatedRenderingSupported() {
    return true;
}

extern bool GetEyeTrackedFoveatedRenderingEnabled() {
    return true;
}

extern void SetEyeTrackedFoveatedRenderingEnabled(bool isEnabled) {
    return;
}

extern bool GetShouldRestartSession() {
    return false;
}

extern bool SetupEnvironmentDepth(EnvironmentDepthCreateParamsInternal* createParams) {
    return true;
}

extern bool SetEnvironmentDepthRendering(bool isEnabled) {
    return true;
}

extern bool ShutdownEnvironmentDepth() {
    return true;
}

extern bool GetEnvironmentDepthTextureId(uint id) {
    return true;
}

extern bool GetEnvironmentDepthFrameDesc(EnvironmentDepthFrameDescInternal* frameDesc, int eye) {
    return true;
}

extern bool SetEnvironmentDepthHandRemoval(bool isEnabled) {
    return true;
}

extern bool GetEnvironmentDepthSupported() {
    return false;
}

extern bool GetEnvironmentDepthHandRemovalSupported() {
    return true;
}