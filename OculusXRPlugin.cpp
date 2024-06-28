#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <time.h>
#include <math.h>
#include <android/log.h>

#include "OculusXRPlugin.h"

// PXR
#include "include/PxrPlatform.h"
#include "include/PxrPlugin.h"

#include "include/Globals.h"
#include "src/Logger.cpp"

#if defined(__cplusplus)
extern "C"
{
#endif

    ovrpVector4f s_ColorScale = {1.0f, 1.0f, 1.0f, 1.0f};

    void SetColorScale(float x, float y, float z, float w)
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        s_ColorScale.x = x;
        s_ColorScale.y = y;
        s_ColorScale.z = z;
        s_ColorScale.w = w;
    }

    ovrpVector4f s_ColorOffset = {1.0f, 1.0f, 1.0f, 1.0f};

    void SetColorOffset(float x, float y, float z, float w)
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        s_ColorOffset.x = x;
        s_ColorOffset.y = y;
        s_ColorOffset.z = z;
        s_ColorOffset.w = w;
    }

    bool GetIsSupportedDevice()
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        return true;
    }

    bool LoadOVRPlugin(char *ovrpPath)
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        return Pxr_LoadPlugin();
    }

    void UnloadOVRPlugin()
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        return Pxr_UnloadPlugin();
    }

    Quaternion ConvertRotationWith2Vector(Vector3 from, Vector3 to)
    {
        float f1 = sqrtf(from.x * from.x + from.y * from.y + from.z * from.z);
        float f2 = sqrtf(to.x * to.x + to.y * to.y + to.z * to.z);
        if (f1 < 1e-6f || f2 < 1e-6f)
        {
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

    // God, theres different versions of UserDefinedSettings... :(
    void SetUserDefinedSettings(UserDefinedSettings *settings)
    {

        LogFunction(IMPLEMENTED, NORMAL, __func__);

        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "Hello World! Made by thoricelli.");
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called with stereoRenderingMode: %d, colorSpace: %d, optimizeBufferDiscards: %d, spaceWarp: %d, lateLatchingDebug: %d", __func__, settings->stereoRenderingMode, settings->colorSpace, settings->optimizeBufferDiscards, settings->spaceWarp, settings->lateLatchingDebug);

        PICO_UserDefinedSettings picoUserDefinedSettings =
            {
                .stereoRenderingMode = settings->stereoRenderingMode,
                .colorSpace = settings->colorSpace,
                .systemDisplayFrequency = 72,
                .useContentProtect = 0,
                .optimizeBufferDiscards = settings->optimizeBufferDiscards,
                .enableAppSpaceWarp = settings->spaceWarp,
                .enableSubsampled = 0,
                .lateLatchingDebug = settings->lateLatchingDebug,
                .enableStageMode = 0,
            };

        Pxr_Construct(&ConvertRotationWith2Vector);
        Pxr_SetUserDefinedSettings(picoUserDefinedSettings);
        return;
    }

    // This would have been handy PICO...
    int SetCPULevel(int cpuLevel)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return cpuLevel;
    }

    int SetGPULevel(int gpuLevel)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return gpuLevel;
    }

    void GetOVRPVersion(const char *version)
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        version = OVRP_VERSION;
        return;
    }

    void EnablePerfMetrics(bool enable)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return;
    }

    void EnableAppMetrics(bool enable)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return;
    }

    bool SetDeveloperModeStrict(bool active)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return true;
    }

    bool GetAppHasInputFocus()
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__); // Still have to implement it with PXR.

        return true;
    }

    bool GetBoundaryConfigured()
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        return Pxr_GetBoundaryConfigured();
    }

    bool GetBoundaryDimensions(void *boundaryType, void *dimensions)
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        return Pxr_GetBoundaryDimensions(true, ((PxrVector3f_ *)&dimensions));
    }

    bool GetBoundaryVisible()
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        return Pxr_GetBoundaryVisible();
    }

    void SetBoundaryVisible(bool boundaryVisible)
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        Pxr_SetBoundaryVisible(boundaryVisible);
    }

    bool GetAppShouldQuit()
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        return false;
    }

    bool GetDisplayAvailableFrequencies(uint32_t *ptr, float *numFrequencies)
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        return Pxr_GetDisplayRefreshRatesAvailable(ptr, &numFrequencies);
    }

    bool SetDisplayFrequency(float refreshRate)
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        return Pxr_SetDisplayRefreshRate(refreshRate);
    }

    bool GetDisplayFrequency(float refreshRate)
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        return Pxr_GetConfigFloat(PXR_GET_DISPLAY_RATE, &refreshRate);
    }

    enum SystemHeadset GetSystemHeadsetType()
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        // I mean, something like that, right?
        return Meta_Quest_3;
    }

    bool GetTiledMultiResSupported()
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        return true;
    }

    void SetTiledMultiResLevel(int level)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return;
    }

    int GetTiledMultiResLevel()
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        return 1;
    }

    void SetTiledMultiResDynamic(bool isDynamic)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return;
    }

    bool GetEyeTrackedFoveatedRenderingSupported()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return false;
    }

    bool GetEyeTrackedFoveatedRenderingEnabled()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return false;
    }

    void SetEyeTrackedFoveatedRenderingEnabled(bool isEnabled)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return;
    }

    bool GetShouldRestartSession()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return false;
    }

    bool SetupEnvironmentDepth(EnvironmentDepthCreateParamsInternal *createParams)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return false;
    }

    bool SetEnvironmentDepthRendering(bool isEnabled)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return false;
    }

    bool ShutdownEnvironmentDepth()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return false;
    }

    bool GetEnvironmentDepthTextureId(uint id)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return false;
    }

    bool GetEnvironmentDepthFrameDesc(EnvironmentDepthFrameDescInternal *frameDesc, int eye)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return false;
    }

    bool SetEnvironmentDepthHandRemoval(bool isEnabled)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return false;
    }

    bool GetEnvironmentDepthSupported()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return false;
    }

    bool GetEnvironmentDepthHandRemovalSupported()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return false;
    }

#if defined(__cplusplus)
} // extern "C"
#endif