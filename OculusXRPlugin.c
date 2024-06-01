#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <time.h>
#include <math.h>
#include <android/log.h>

#include "OculusXRPlugin.h"
#include "/include/PxrPlatform.h"
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

bool GetDisplayAvailableFrequencies(intptr_t *ptr, int32_t *numFrequencies) {
    return Pxr_GetDisplayRefreshRatesAvailable(ptr, numFrequencies);
}

bool SetDisplayFrequency(float refreshRate) {
    return Pxr_SetDisplayRefreshRate(refreshRate);
}

bool GetDisplayFrequency(float refreshRate) {
    return Pxr_GetConfigFloat(SystemDisplayRate, &refreshRate);
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
    return true;
}

bool GetEyeTrackedFoveatedRenderingEnabled() {
    return true;
}

void SetEyeTrackedFoveatedRenderingEnabled(bool isEnabled) {
    return;
}

bool GetShouldRestartSession() {
    return false;
}

bool SetupEnvironmentDepth(EnvironmentDepthCreateParamsInternal* createParams) {
    return true;
}

bool SetEnvironmentDepthRendering(bool isEnabled) {
    return true;
}

bool ShutdownEnvironmentDepth() {
    return true;
}

bool GetEnvironmentDepthTextureId(uint id) {
    return true;
}

bool GetEnvironmentDepthFrameDesc(EnvironmentDepthFrameDescInternal* frameDesc, int eye) {
    return true;
}

bool SetEnvironmentDepthHandRemoval(bool isEnabled) {
    return true;
}

bool GetEnvironmentDepthSupported() {
    return false;
}

bool GetEnvironmentDepthHandRemovalSupported() {
    return true;
}