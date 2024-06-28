#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <time.h>
#include <math.h>
#include <android/log.h>
#include <jni.h>

#include "OVRPlugin.h"
#include "OculusXRPlugin.h"

// PXR
#include "include/PxrPlugin.h"
#include "include/PxrInput.h"
#include "include/PxrPlatform.h"
#include "include/PxrPlatformLoader.h"

#include "include/Globals.h"
#include "src/PxrToOculusMapper.cpp"
#include "src/Logger.cpp"

#if defined(__cplusplus)
extern "C"
{
#endif

    JavaVM *VM;
    JNIEnv *env;

    jint JNI_OnLoad(JavaVM *vm, void *reserved)
    {
        VM = vm;

        // Load JNI environment
        VM->AttachCurrentThread(&env, NULL);

        return 0;
    }

    /* LEGACY (TODO) */
    bool ovrp_PreInitialize()
    {
        int success = 0;

        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        // This just fails. Great.
        success += Pxr_SetConfigInt(PXR_PXRPLUGIN_LOG_LEVEL, 8);
        success += Pxr_SetConfigInt(PXR_RUNTIME_LOG_LEVEL, 8);
        success += Pxr_SetConfigInt(PXR_UNITY_LOG_LEVEL, 8);
        success += Pxr_SetConfigInt(PXR_UNREAL_LOG_LEVEL, 8);
        success += Pxr_SetConfigInt(PXR_NATIVE_LOG_LEVEL, 8);

        if (success != 0)
            __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "SetConfig failed!");

        return 1;
    }
    bool ovrp_Initialize(RenderAPIType apiType, intptr_t platformArgs)
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        Pxr_SetConfigInt(PXR_UNREAL_OPENGL_NOERROR, 1);
        return Pxr_Initialize();
    }
    bool ovrp_Shutdown()
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        return Pxr_Shutdown();
    }
    bool ovrp_SetupDistortionWindow()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    bool ovrp_DestroyDistortionWindow()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    bool ovrp_RecreateEyeTexture(Eye eyeId, int stage, void *device, int height, int width, int samples, bool isSRGB, void *result)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    bool ovrp_SetEyeTexture(Eye eyeId, intptr_t texture)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    bool ovrp_Update(int frameIndex)
    {
        LogFunction(NON_IMPLEMENTED, FREQUENT, __func__);

        return 0;
    }
    bool ovrp_BeginFrame(int frameIndex)
    {
        LogFunction(NON_IMPLEMENTED, FREQUENT, __func__);

        return Pxr_BeginFrame();
    }
    bool ovrp_EndEye(Eye eye)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    bool ovrp_EndFrame(int frameIndex)
    {
        LogFunction(IMPLEMENTED, FREQUENT, __func__);

        return Pxr_EndFrame();
    }
    bool ovrp_RecenterPose()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    /* END */

    // NON-LEGACY
    void UnityPluginLoad(void *unityInterfaces)
    {
        LogFunction(NON_IMPLEMENTED, FREQUENT, __func__);

        // This is done by the PICO plugin.
        // Probably in the future, if this doesn't work out, I'll have implement an own way of doing this.
        //(This probably requires porting this to C++).
        minLogLevel_PxrAPI = 8;
    }
    Sizei ovrp_GetEyeTextureSize(Eye eyeId)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        Sizei sizeiDummy;
        return sizeiDummy;
    }
    bool ovrp_SetOverlayQuad2(bool onTop, bool headLocked, intptr_t texture, intptr_t device, Posef pose, Vector3f scale)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }

    PoseStatef getPosefStateForController(int deviceID)
    {
        PxrControllerTracking tracking;
        float headSensorData[7] = {0, 0, 0, 0, 0, 0, 0};

        Pxr_GetControllerTrackingState(deviceID, 0, headSensorData, &tracking);

        PoseStatef poseStatef = {
            .Pose = *((Posef *)&tracking.localControllerPose.pose),

            // cm/s -> m/s
            .Velocity = PxrVector3ToOVRVector3(tracking.localControllerPose.linearVelocity),
            // cm/s² -> m/s²
            .Acceleration = PxrVector3ToOVRVector3(tracking.localControllerPose.linearAcceleration),

            .AngularVelocity = *((Vector3f *)&tracking.localControllerPose.angularVelocity),
            .AngularAcceleration = *((Vector3f *)&tracking.localControllerPose.angularAcceleration),
        };
        return poseStatef;
    }

    PoseStatef getPosefStateForSensor()
    {
        int sensorFrameIndex;
        double predictedDisplayTimeMS;

        PxrSensorState2 sensorState;

        Pxr_GetPredictedDisplayTime(&predictedDisplayTimeMS);

        Pxr_GetPredictedMainSensorState2(predictedDisplayTimeMS, &sensorState, &sensorFrameIndex);

        PoseStatef poseStatef = {
            .Pose = *((Posef *)&sensorState.pose),
            .Velocity = *((Vector3f *)&sensorState.linearVelocity),
            .Acceleration = *((Vector3f *)&sensorState.linearAcceleration),
            .AngularVelocity = *((Vector3f *)&sensorState.angularVelocity),
            .AngularAcceleration = *((Vector3f *)&sensorState.angularVelocity),
        };

        return poseStatef;
    }

    Posef getPosefForController(int deviceID)
    {
        return getPosefStateForController(deviceID).Pose;
    }

    Posef getPosefForSensor()
    {
        return getPosefStateForSensor().Pose;
    }

    Posef GetNodePose(Node nodeId)
    {
        Posef poseStateDummy;

        switch (nodeId)
        {
        case EyeCenter:
        case Head:
            return getPosefForSensor();
            break;
        case HandLeft:
        case HandRight:
            return getPosefForController(nodeId - 3);
        case ControllerLeft:
        case ControllerRight:
            return getPosefForController(nodeId - 12);
        default:
            return poseStateDummy;
            break;
        }
    }

    PoseStatef GetNodePoseState(Node nodeId)
    {
        PoseStatef poseStateDummy;

        switch (nodeId)
        {
        case EyeCenter:
        case Head:
            return getPosefStateForSensor();
        case HandLeft:
        case HandRight:
            return getPosefStateForController(nodeId - 3);
        case ControllerLeft:
        case ControllerRight:
            return getPosefStateForController(nodeId - 12);
        default:
            return poseStateDummy;
            break;
        }
    }

    Posef ovrp_GetNodePose(Node nodeId)
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        return GetNodePose(nodeId);
    }

    bool ovrp_SetControllerVibration(uint controllerMask, float frequency, float amplitude)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    Posef ovrp_GetNodeVelocity(Node nodeId)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        Posef posefDummy;
        return posefDummy;
    }
    Posef ovrp_GetNodeAcceleration(Node nodeId)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        Posef posefDummy;
        return posefDummy;
    }
    TrackingOrigin ovrp_GetTrackingOriginType()
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        PxrTrackingOrigin pxrTrackingOrigin;
        Pxr_GetTrackingOrigin(&pxrTrackingOrigin);

        return (TrackingOrigin)pxrTrackingOrigin;
    }

    float originDeltaY = 0;

    bool ovrp_SetTrackingOriginType(TrackingOrigin originType)
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        if (originType == EyeLevel)
            Pxr_GetConfigFloat(PXR_TO_DELTA_SENSOR_Y, &originDeltaY);

        return Pxr_SetTrackingOrigin((PxrTrackingOrigin)originType);
    }
    Posef ovrp_GetTrackingCalibratedOrigin()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        Posef origin = {
            //.Position.y = calibratedHeight,
        };
        return origin;
    }
    bool ovrp_RecenterTrackingOrigin(uint flags)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    bool ovrp_GetInitialized()
    {
        LogFunction(IMPLEMENTED, FREQUENT, __func__);

        return Pxr_IsInitialized();
    }
    intptr_t ovrp_GetVersion()
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        return ((intptr_t)OVRP_VERSION);
    }
    intptr_t ovrp_GetNativeSDKVersion()
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        return ((intptr_t)OVRP_VERSION);
    }
    intptr_t ovrp_GetAudioOutId()
    {
        LogFunction(NON_IMPLEMENTED, FREQUENT, __func__);

        return 0;
    }
    intptr_t ovrp_GetAudioInId()
    {
        LogFunction(NON_IMPLEMENTED, FREQUENT, __func__);

        return 0;
    }
    float ovrp_GetEyeTextureScale()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    bool ovrp_SetEyeTextureScale(float value)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    bool ovrp_GetTrackingOrientationSupported()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    bool ovrp_GetTrackingOrientationEnabled()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    bool ovrp_SetTrackingOrientationEnabled(bool value)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 1;
    }
    bool ovrp_GetTrackingPositionSupported()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    bool ovrp_GetTrackingPositionEnabled()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    bool ovrp_SetTrackingPositionEnabled(bool value)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 1;
    }
    bool ovrp_GetNodePresent(Node nodeId)
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        return 1;
    }
    bool ovrp_GetNodeOrientationTracked(Node nodeId)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 1;
    }
    Frustumf ovrp_GetNodeFrustum(Node nodeId)
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        float left, right, top, bottom, near, far;

        if (nodeId <= 2)
        {
            Pxr_GetFrustum(*((PxrEyeType *)&nodeId), &left, &right, &top, &bottom, &near, &far);
        }
        Frustumf frustumf = {
            .zNear = near,
            .zFar = far,
            .fovX = top,
            .fovY = bottom,
        };
        return frustumf;
    }

    uint32_t getConnectedController(PxrControllerHandness controller)
    {
        uint32_t connectedControllers = 0;

        switch (controller)
        {
        case PXR_CONTROLLER_LEFT:
            connectedControllers |= Pxr_GetControllerConnectStatus(PXR_CONTROLLER_LEFT) * LTouch;
            break;
        case PXR_CONTROLLER_RIGHT:
            connectedControllers |= Pxr_GetControllerConnectStatus(PXR_CONTROLLER_RIGHT) * RTouch;
            break;
        default:
            break;
        }

        return connectedControllers;
    }

    // Move to mapper maybe?
    uint32_t getButtonsFromState(PxrControllerInputState pxrState, PxrControllerHandness controllerType)
    {
        uint32_t state = 0;
        switch (controllerType)
        {
        case PXR_CONTROLLER_RIGHT:
            state |= pxrState.AXValue * Button_One;
            state |= pxrState.BYValue * Button_Two;

            break;
        case PXR_CONTROLLER_LEFT:
            state |= pxrState.AXValue * Button_Three;
            state |= pxrState.BYValue * Button_Four;
            break;
        default:
            break;
        }

        // The same for both controllers
        state |= pxrState.homeValue * Button_Start;
        state |= pxrState.backValue * Button_Back;

        return state;
    }

    uint32_t getTouchFromState(PxrControllerInputState pxrState, PxrControllerHandness controllerType)
    {
        uint32_t state = 0;
        switch (controllerType)
        {
        case PXR_CONTROLLER_RIGHT:
            state |= pxrState.AXTouchValue * RawTouch_A;
            state |= pxrState.BYTouchValue * RawTouch_B;

            state |= pxrState.triggerTouchValue * RawTouch_RIndexTrigger;

            state |= pxrState.thumbrestTouchValue * RawTouch_RThumbRest;
            break;
        case PXR_CONTROLLER_LEFT:
            state |= pxrState.AXTouchValue * RawTouch_X;
            state |= pxrState.BYTouchValue * RawTouch_Y;

            state |= pxrState.triggerTouchValue * RawTouch_LIndexTrigger;

            state |= pxrState.thumbrestTouchValue * RawTouch_LThumbRest;
            break;
        default:
            break;
        }

        return state;
    }

    uint32_t getNearTouchFromState(PxrControllerInputState pxrState, PxrControllerHandness controllerType)
    {
        uint32_t state = 0;
        switch (controllerType)
        {
        case PXR_CONTROLLER_RIGHT:
            state |= pxrState.triggerTouchValue * RawNearTouch_RIndexTrigger;

            state |= pxrState.AXTouchValue * RawNearTouch_RThumbButtons;
            state |= pxrState.BYTouchValue * RawNearTouch_RThumbButtons;
            break;
        case PXR_CONTROLLER_LEFT:
            state |= pxrState.triggerTouchValue * RawNearTouch_LIndexTrigger;

            state |= pxrState.AXTouchValue * RawNearTouch_LThumbButtons;
            state |= pxrState.BYTouchValue * RawNearTouch_LThumbButtons;
            break;
        default:
            break;
        }

        return state;
    }
    // Refer to Controller enum.
    ControllerState6 getControllerState(uint controllerMask)
    {
        PxrControllerInputState controllerState;
        ControllerState6 state = {0};

        if ((controllerMask & LTouch) == LTouch)
        {
            Pxr_GetControllerInputState(PXR_CONTROLLER_LEFT, &controllerState);

            state.Buttons |= getButtonsFromState(controllerState, PXR_CONTROLLER_LEFT);
            state.Touches |= getTouchFromState(controllerState, PXR_CONTROLLER_LEFT);
            state.NearTouches |= getNearTouchFromState(controllerState, PXR_CONTROLLER_LEFT);

            state.LIndexTrigger = controllerState.triggerValue;
            state.LHandTrigger = controllerState.gripValue;
            state.LThumbstick = *((Vector2f *)&controllerState.Joystick);

            state.ConnectedControllers |= getConnectedController(PXR_CONTROLLER_LEFT);
        }

        if ((controllerMask & RTouch) == RTouch)
        {
            Pxr_GetControllerInputState(PXR_CONTROLLER_RIGHT, &controllerState);

            state.Buttons |= getButtonsFromState(controllerState, PXR_CONTROLLER_RIGHT);
            state.Touches |= getTouchFromState(controllerState, PXR_CONTROLLER_RIGHT);
            state.NearTouches |= getNearTouchFromState(controllerState, PXR_CONTROLLER_RIGHT);

            state.RIndexTrigger = controllerState.triggerValue;
            state.RHandTrigger = controllerState.gripValue;
            state.RThumbstick = *((Vector2f *)&controllerState.Joystick);

            state.ConnectedControllers |= getConnectedController(PXR_CONTROLLER_RIGHT);
        }
        return state;
    }

    ControllerState ovrp_GetControllerState(uint controllerMask)
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        ControllerState6 state6 = getControllerState(controllerMask);
        return *((ControllerState *)&state6);
    }

    // Deprecated. Replaced by ovrp_GetSuggestedCpuPerformanceLevel
    int ovrp_GetSystemCpuLevel()
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        int level;
        Pxr_GetPerformanceLevels(PXR_PERF_SETTINGS_CPU, &level);

        return level;
    }
    // Deprecated. Replaced by ovrp_SetSuggestedCpuPerformanceLevel
    bool ovrp_SetSystemCpuLevel(int value)
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        return Pxr_SetPerformanceLevels(PXR_PERF_SETTINGS_CPU, value);
    }
    // Deprecated. Replaced by ovrp_GetSuggestedGpuPerformanceLevel
    int ovrp_GetSystemGpuLevel()
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        int level;
        Pxr_GetPerformanceLevels(PXR_PERF_SETTINGS_GPU, &level);

        return level;
    }
    // Deprecated. Replaced by ovrp_SetSuggestedGpuPerformanceLevel
    bool ovrp_SetSystemGpuLevel(int value)
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        return Pxr_SetPerformanceLevels(PXR_PERF_SETTINGS_GPU, value);
    }
    bool ovrp_GetSystemPowerSavingMode()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    float ovrp_GetSystemDisplayFrequency()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    int ovrp_GetSystemVSyncCount()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    float ovrp_GetSystemVolume()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    BatteryStatus ovrp_GetSystemBatteryStatus()
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        return Full;
    }
    float ovrp_GetSystemBatteryLevel()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    float ovrp_GetSystemBatteryTemperature()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    intptr_t ovrp_GetSystemProductName()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    bool ovrp_ShowSystemUI(PlatformUI ui)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    bool ovrp_GetAppMonoscopic()
    {
        LogFunction(NON_IMPLEMENTED, FREQUENT, __func__);

        return 0;
    }
    bool ovrp_SetAppMonoscopic(bool value)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    bool ovrp_GetAppHasVrFocus()
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        return 1;
    }
    bool ovrp_GetAppShouldQuit()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    bool ovrp_GetAppShouldRecenter()
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        return false;
    }
    intptr_t ovrp_GetAppLatencyTimings()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    bool ovrp_GetUserPresent()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 1;
    }
    float ovrp_GetUserIPD()
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        return Pxr_GetIPD();
    }
    bool ovrp_SetUserIPD(float value)
    {
        // Maybe later, need to test if this doesn't set it to dangerous levels.
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    float ovrp_GetUserEyeDepth()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    bool ovrp_SetUserEyeDepth(float value)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    float ovrp_GetUserEyeHeight()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    bool ovrp_SetUserEyeHeight(float value)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    bool ovrp_SetSystemVSyncCount(int vsyncCount)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    bool ovrpi_SetTrackingCalibratedOrigin()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    bool ovrp_GetEyeOcclusionMeshEnabled()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    bool ovrp_SetEyeOcclusionMeshEnabled(bool value)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    bool ovrp_GetSystemHeadphonesPresent()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    SystemRegion ovrp_GetSystemRegion()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Unspecified;
    }
    bool ovrp_GetTrackingIPDEnabled()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return false;
        // return Pvr_GetTrackingIPDEnabled();
    }
    bool ovrp_SetTrackingIPDEnabled(bool value)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return false;
        // return Pvr_SetTrackingIPDEnabled(value);
    }
    HapticsDesc ovrp_GetControllerHapticsDesc(uint controllerMask)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        HapticsDesc hapticsDescDummy;
        return hapticsDescDummy;
    }
    HapticsState ovrp_GetControllerHapticsState(uint controllerMask)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        HapticsState hapticsStateDummy;
        return hapticsStateDummy;
    }
    bool ovrp_SetControllerHaptics(uint controllerMask, HapticsBuffer hapticsBuffer)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    bool ovrp_SetOverlayQuad3(uint flags, intptr_t textureLeft, intptr_t textureRight, intptr_t device, Posef pose, Vector3f scale, int layerIndex)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    float ovrp_GetEyeRecommendedResolutionScale()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    float ovrp_GetAppCpuStartToGpuEndTime()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    int ovrp_GetSystemRecommendedMSAALevel()
    {
        LogFunction(NON_IMPLEMENTED, FREQUENT, __func__);

        int data;
        Pxr_GetConfigInt(PXR_MSAA_LEVEL_RECOMMENDED, &data);
        return 0; // data;
    }
    bool ovrp_GetAppChromaticCorrection()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    bool ovrp_SetAppChromaticCorrection(bool value)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    bool ovrp_GetBoundaryConfigured()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    // Deprecated. This function will not be supported in OpenXR
    BoundaryTestResult ovrp_TestBoundaryNode(Node nodeId, BoundaryType boundaryType)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        BoundaryTestResult boundaryTestResultDummy;
        return boundaryTestResultDummy;
    }
    // Deprecated. This function will not be supported in OpenXR
    BoundaryTestResult ovrp_TestBoundaryPoint(Vector3f point, BoundaryType boundaryType)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        BoundaryTestResult boundaryTestResultDummy;
        return boundaryTestResultDummy;
    }
    BoundaryGeometry ovrp_GetBoundaryGeometry(BoundaryType boundaryType)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        BoundaryGeometry boundaryGeometryDummy;
        return boundaryGeometryDummy;
    }
    Vector3f ovrp_GetBoundaryDimensions(BoundaryType boundaryType)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        Vector3f vector3FDummy;
        return vector3FDummy;
    }
    // Deprecated. This function will not be supported in OpenXR
    bool ovrp_GetBoundaryVisible()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    // Deprecated. This function will not be supported in OpenXR
    bool ovrp_SetBoundaryVisible(bool value)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    bool ovrp_Update2(int stateId, int frameIndex, double predictionSeconds)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    Posef ovrp_GetNodePose2(int stateId, Node nodeId)
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);
        // TODO: StateId?
        return GetNodePose(nodeId);
    }
    Posef ovrp_GetNodeVelocity2(int stateId, Node nodeId)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        Posef posefDummy;
        return posefDummy;
    }
    Posef ovrp_GetNodeAcceleration2(int stateId, Node nodeId)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        Posef posefDummy;
        return posefDummy;
    }
    enum SystemHeadset ovrp_GetSystemHeadsetType()
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        return Meta_Quest_3;
    }
    Controller ovrp_GetActiveController()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return All;
    }
    Controller ovrp_GetConnectedControllers()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return All;
    }
    bool ovrp_GetBoundaryGeometry2(BoundaryType boundaryType, intptr_t points, int *pointsCount)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    AppPerfStats ovrp_GetAppPerfStats()
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        AppPerfStats appPerfStatsDummy;
        return appPerfStatsDummy;
    }
    bool ovrp_ResetAppPerfStats()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    bool ovrp_SetDesiredEyeTextureFormat(EyeTextureFormat value)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    EyeTextureFormat ovrp_GetDesiredEyeTextureFormat()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Default;
    }
    float ovrp_GetAppFramerate()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    PoseStatef ovrp_GetNodePoseState(Step stepId, Node nodeId)
    {
        // Logging this causes issues when holding objects? WTF?
        // LogFunction(IMPLEMENTED, NORMAL, __func__);

        return GetNodePoseState(nodeId);
    }
    ControllerState2 ovrp_GetControllerState2(uint controllerMask)
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        ControllerState6 state6 = getControllerState(controllerMask);
        ControllerState2 base = *((ControllerState2 *)&state6);
        // Add more.
        return base;
    }
    Result ovrp_InitializeMixedReality()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_ShutdownMixedReality()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    bool ovrp_GetMixedRealityInitialized()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    Result ovrp_UpdateExternalCamera()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetExternalCameraCount(int *cameraCount)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetExternalCameraName(int cameraId, char *cameraName)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetExternalCameraIntrinsics(int cameraId, CameraIntrinsics *cameraIntrinsics)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetExternalCameraExtrinsics(int cameraId, CameraExtrinsics *cameraExtrinsics)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }

    // LAYERS
    Result ovrp_CalculateLayerDesc(OverlayShape shape, LayerLayout layout, Sizei *textureSize,
                                   int mipLevels, int sampleCount, EyeTextureFormat format, int layerFlags, LayerDesc *layerDesc)
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        LayerDesc layer = {
            .Shape = shape,
            .Layout = layout,
            .TextureSize = *textureSize,
            .MipLevels = mipLevels,
            .SampleCount = sampleCount,
            .Format = format,
            .LayerFlags = layerFlags,
        };
        *layerDesc = layer;

        return Success;
    }

    char layersCreated[15];
    char layersCreated2[15];
    Result ovrp_EnqueueSetupLayer(LayerDesc *desc, int *layerId)
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        if (layersCreated[*layerId] != true)
        {
            PxrLayerParam layerParam = {
                .layerId = (*layerId) + 1,
                .layerShape = PXRConvertToOverLayShape(desc->Shape),
                .layerType = PXR_OVERLAY,
                .layerLayout = PXRConvertToLayerLayout(desc->Layout),
                .format = *((uint64_t *)&desc->Format),
                .width = static_cast<uint32_t>(desc->MaxViewportSize.w),
                .height = static_cast<uint32_t>(desc->MaxViewportSize.h),
                .sampleCount = static_cast<uint32_t>(desc->SampleCount),

                .faceCount = 1,
                .arraySize = 1,

                .mipmapCount = static_cast<uint32_t>(desc->MipLevels),
                .layerFlags = static_cast<uint32_t>(desc->LayerFlags),

                .externalImageCount = 0,
            };
            layersCreated[*layerId] = true;
            return static_cast<Result>(Pxr_CreateLayer(&layerParam));
        }
        return Success;
    }
    Result ovrp_EnqueueDestroyLayer(int *layerId)
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        layersCreated[*layerId] = false;
        layersCreated2[*layerId] = false;
        return static_cast<Result>(Pxr_DestroyLayer((*layerId) + 1));
    }
    Result ovrp_GetLayerTextureStageCount(int layerId, uint32_t *layerTextureStageCount)
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        return static_cast<Result>(Pxr_GetLayerImageCount(layerId, PXR_EYE_BOTH, layerTextureStageCount));
    }
    Result ovrp_GetLayerTexturePtr(int layerId, int stage, Eye eyeId, uint64_t *textureHandle)
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        return static_cast<Result>(Pxr_GetLayerImage(layerId, *((PxrEyeType *)&eyeId), stage, textureHandle));
    }
    Result ovrp_EnqueueSubmitLayer(uint flags, intptr_t textureLeft, intptr_t textureRight, int layerId, int frameIndex, Posef *pose, Vector3f *scale, int layerIndex)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
        // Idfk
        /*uint64_t* externalImages[2] = [&textureLeft, &textureLeft]

        PxrLayerParam layerParam = {
                .layerId = layerId,
                .layerShape = PXRConvertToOverLayShape(desc->Shape),
                .layerType = PXR_OVERLAY,
                .layerLayout = PXRConvertToLayerLayout(desc->Layout),
                .format = *((uint64_t*)&desc->Format),
                .width = desc->MaxViewportSize.w,
                .height = desc->MaxViewportSize.h,
                .sampleCount = desc->SampleCount,

                .faceCount = 1,
                .arraySize = 1,

                .mipmapCount = desc->MipLevels,
                .layerFlags = flags,

                .externalImageCount = 2,
                .externalImages = externalImages,
        };
        return Pxr_CreateLayer(&layerParam);*/
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetNodeFrustum2(Node nodeId, Frustumf2 *nodeFrustum)
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        float left, right, top, bottom, near, far;
        float fovLeft, fovRight, fovUp, fovDown;

        if (nodeId <= 2)
        {
            Pxr_GetFrustum(*((PxrEyeType *)&nodeId), &left, &right, &top, &bottom, &near, &far);
        }

        Frustumf2 frustumf = {
            .zNear = near,
            .zFar = far,
            .Fov.UpTan = top,
            .Fov.DownTan = bottom,
            .Fov.LeftTan = left,
            .Fov.RightTan = right,
        };

        *nodeFrustum = frustumf;
        return Success;
    }
    bool ovrp_GetEyeTextureArrayEnabled()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    Result ovrp_UpdateCameraDevices()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    bool ovrp_IsCameraDeviceAvailable(CameraDevice cameraDevice)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    Result ovrp_SetCameraDevicePreferredColorFrameSize(CameraDevice cameraDevice, Sizei preferredColorFrameSize)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_OpenCameraDevice(CameraDevice cameraDevice)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_CloseCameraDevice(CameraDevice cameraDevice)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    bool ovrp_HasCameraDeviceOpened(CameraDevice cameraDevice)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    bool ovrp_IsCameraDeviceColorFrameAvailable(CameraDevice cameraDevice)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    Result ovrp_GetCameraDeviceColorFrameSize(CameraDevice cameraDevice, Sizei *colorFrameSize)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetCameraDeviceColorFrameBgraPixels(CameraDevice cameraDevice, intptr_t *colorFrameBgraPixels, int *colorFrameRowPitch)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetControllerState4(uint controllerMask, ControllerState4 *controllerState)
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        ControllerState6 state6 = getControllerState(controllerMask);
        *controllerState = *((ControllerState4 *)&state6);

        return Success;
    }

    // UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN
    Result ovrp_GetExternalCameraPose(CameraDevice camera, Posef *cameraPose)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_ConvertPoseToCameraSpace(CameraDevice camera, Posef *trackingSpacePose, Posef *cameraSpacePose)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetCameraDeviceIntrinsicsParameters(CameraDevice camera, bool *supportIntrinsics, CameraDeviceIntrinsicsParameters *intrinsicsParameters)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_DoesCameraDeviceSupportDepth(CameraDevice camera, bool *supportDepth)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetCameraDeviceDepthSensingMode(CameraDevice camera, CameraDeviceDepthSensingMode *depthSensoringMode)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_SetCameraDeviceDepthSensingMode(CameraDevice camera, CameraDeviceDepthSensingMode depthSensoringMode)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetCameraDevicePreferredDepthQuality(CameraDevice camera, CameraDeviceDepthQuality *depthQuality)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_SetCameraDevicePreferredDepthQuality(CameraDevice camera, CameraDeviceDepthQuality depthQuality)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_IsCameraDeviceDepthFrameAvailable(CameraDevice camera, bool *available)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetCameraDeviceDepthFrameSize(CameraDevice camera, Sizei *depthFrameSize)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetCameraDeviceDepthFramePixels(CameraDevice cameraDevice, intptr_t *depthFramePixels, int *depthFrameRowPitch)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetCameraDeviceDepthConfidencePixels(CameraDevice cameraDevice, intptr_t *depthConfidencePixels, int *depthConfidenceRowPitch)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    // END

    Result ovrp_SetHandNodePoseStateLatency(double latencyInSeconds)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetHandNodePoseStateLatency(double *latencyInSeconds)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetAppHasInputFocus(bool *appHasInputFocus)
    {
        *appHasInputFocus = 1;
        LogFunction(NON_IMPLEMENTED, FREQUENT, __func__);

        return Success;
    }
    Result ovrp_GetTiledMultiResSupported(bool *foveationSupported)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetTiledMultiResLevel(FixedFoveatedRenderingLevel *level)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_SetTiledMultiResLevel(FixedFoveatedRenderingLevel level)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetGPUUtilSupported(bool *gpuUtilSupported)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetGPUUtilLevel(float *gpuUtil)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetSystemDisplayFrequency2(float *systemDisplayFrequency)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetSystemDisplayAvailableFrequencies(int *systemDisplayAvailableFrequencies, int *numFrequencies)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        /**numFrequencies = 1;
        int frequencies[1] = {72};
        systemDisplayAvailableFrequencies = *((int **)&frequencies);*/

        return Success; // Pxr_GetDisplayRefreshRatesAvailable(numFrequencies, &systemDisplayAvailableFrequencies);
    }
    Result ovrp_SetSystemDisplayFrequency(float requestedFrequency)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetAppAsymmetricFov(bool *useAsymmetricFov)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetDominantHand(Handedness *dominantHand)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_SendEvent(char *name, char *param)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }

    Result ovrp_EnqueueSetupLayer2(LayerDesc *desc, int compositionDepth, int *layerId)
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        if (layersCreated2[*layerId] != true)
        {
            PxrLayerParam layerParam = {
                .layerId = (*layerId) + 1,
                .layerShape = PXRConvertToOverLayShape(desc->Shape),
                .layerType = PXR_OVERLAY,
                .layerLayout = PXRConvertToLayerLayout(desc->Layout),
                .format = static_cast<uint64_t>(desc->Format),
                .width = static_cast<uint32_t>(desc->TextureSize.w),
                .height = static_cast<uint32_t>(desc->TextureSize.h),
                .sampleCount = static_cast<uint32_t>(desc->SampleCount),

                .faceCount = 1,
                .arraySize = 1,

                .mipmapCount = static_cast<uint32_t>(desc->MipLevels),
                .layerFlags = static_cast<uint32_t>(desc->LayerFlags),

                .externalImageCount = 0,
            };
            layersCreated2[*layerId] = true;
            return static_cast<Result>(Pxr_CreateLayer(&layerParam));
        }
        return Success;
    }
    Result ovrp_GetLayerAndroidSurfaceObject(int layerId, intptr_t *surfaceObject)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_SetHeadPoseModifier(Quatf *relativeRotation, Vector3f *relativeTranslation)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetHeadPoseModifier(Quatf *relativeRotation, Vector3f *relativeTranslation)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetNodePoseStateRaw(Step stepId, int frameIndex, Node nodeId, PoseStatef *nodePoseState)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetCurrentTrackingTransformPose(Posef *trackingTransformPose)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetTrackingTransformRawPose(Posef *trackingTransformRawPose)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_SendEvent2(char *name, char *param, char *source)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_IsPerfMetricsSupported(PerfMetrics perfMetrics, bool *isSupported)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetPerfMetricsFloat(PerfMetrics perfMetrics, float *value)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetPerfMetricsInt(PerfMetrics perfMetrics, int *value)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetTimeInSeconds(double *value)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_SetColorScaleAndOffset(Vector4 colorScale, Vector4 colorOffset, bool applyToAllLayers)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_AddCustomMetadata(char *name, char *param)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_EnqueueSubmitLayer2(uint flags, intptr_t textureLeft, intptr_t textureRight, int layerId, int frameIndex, Posef *pose, Vector3f *scale, int layerIndex, bool overrideTextureRectMatrix, TextureRectMatrixf *textureRectMatrix, bool overridePerLayerColorScaleAndOffset, Vector4 *colorScale, Vector4 *colorOffset)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetTrackingTransformRelativePose(Posef *trackingTransformRelativePose, TrackingOrigin trackingOrigin)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_Media_Initialize()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_Media_Shutdown()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_Media_GetInitialized(bool *initialized)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        //*initialized = 1;
        return Success;
    }
    Result ovrp_Media_Update()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_Media_GetMrcActivationMode(MrcActivationMode *activationMode)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_Media_SetMrcActivationMode(MrcActivationMode activationMode)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_Media_IsMrcEnabled(bool *mrcEnabled)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_Media_IsMrcActivated(bool *mrcActivated)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_Media_UseMrcDebugCamera(bool *useMrcDebugCamera)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_Media_SetMrcInputVideoBufferType(InputVideoBufferType inputVideoBufferType)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_Media_GetMrcInputVideoBufferType(InputVideoBufferType *inputVideoBufferType)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_Media_SetMrcFrameSize(int frameWidth, int frameHeight)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_Media_GetMrcFrameSize(int *frameWidth, int *frameHeight)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_Media_SetMrcAudioSampleRate(int sampleRate)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_Media_GetMrcAudioSampleRate(int *sampleRate)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_Media_SetMrcFrameImageFlipped(bool flipped)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_Media_GetMrcFrameImageFlipped(bool *flipped)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_Media_EncodeMrcFrame(intptr_t rawBuffer, intptr_t audioDataPtr, int audioDataLen, int audioChannels, double timestamp, int *outSyncId)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_Media_EncodeMrcFrameWithDualTextures(intptr_t backgroundTextureHandle, intptr_t foregroundTextureHandle, intptr_t audioData, int audioDataLen, int audioChannels, double timestamp, int *outSyncId)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_Media_SyncMrcFrame(int syncId)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    // Result ovrp_GetExternalCameraCalibrationRawPose(int cameraId, Posef *rawPose)
    Result ovrp_SetDeveloperMode(bool active)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetNodeOrientationValid(Node nodeId, bool *nodeOrientationValid)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetNodePositionValid(Node nodeId, bool *nodePositionValid)
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__); // Technically not implemented yet

        *nodePositionValid = 1;
        return Success;
    }
    Result ovrp_GetAdaptiveGpuPerformanceScale2(float *adaptiveGpuPerformanceScale)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetHandTrackingEnabled(bool *handTrackingEnabled)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        *handTrackingEnabled = false;
        // return Pxr_GetHandTrackerSettingState(handTrackingEnabled);
        return Success;
    }
    void GetPXRHandStateForOVR(int hand, HandStateInternal *handState)
    {
        // Get aim state.
        PxrHandAimState aimState;
        Pxr_GetHandTrackerAimState(hand, &aimState);

        // Get the joint locations
        PxrHandJointsLocations jointsLocations;
        Pxr_GetHandTrackerJointLocations(hand, &jointsLocations);

        PoseStatef headsetPosef = getPosefStateForSensor();

        PxrHandCombinedStateToOVRHandState(aimState, jointsLocations, handState);
    }
    Result ovrp_GetHandState(Step stepId, Hand hand, HandStateInternal *handState)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__); // Not done yet

        GetPXRHandStateForOVR(hand, handState);

        return Success;
    }
    Result ovrp_GetSkeleton(SkeletonType skeletonType, Skeleton *skeleton)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetMesh(MeshType meshType, intptr_t meshPtr)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_OverrideExternalCameraFov(int cameraId, bool useOverriddenFov, Fovf *fov)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetUseOverriddenExternalCameraFov(int cameraId, bool *useOverriddenFov)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_OverrideExternalCameraStaticPose(int cameraId, bool useOverriddenPose, Posef *poseInStageOrigin)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetUseOverriddenExternalCameraStaticPose(int cameraId, bool *useOverriddenStaticPose)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_ResetDefaultExternalCamera()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_SetDefaultExternalCamera(char *cameraName, CameraIntrinsics *cameraIntrinsics, CameraExtrinsics *cameraExtrinsics)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetLocalTrackingSpaceRecenterCount(int *recenterCount)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetSystemHmd3DofModeEnabled(bool *enabled)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_Media_SetAvailableQueueIndexVulkan(uint queueIndexVk)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetTiledMultiResDynamic(bool *isDynamic)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_SetTiledMultiResDynamic(bool isDynamic)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_SetExternalCameraProperties(char *cameraName, CameraIntrinsics *cameraIntrinsics, CameraExtrinsics *cameraExtrinsics)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_SetClientColorDesc(ColorSpace colorSpace)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetHmdColorDesc(ColorSpace *colorSpace)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_Media_EncodeMrcFrameWithPoseTime(intptr_t rawBuffer, intptr_t audioDataPtr, int audioDataLen, int audioChannels, double timestamp, double poseTime, int *outSyncId)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_Media_EncodeMrcFrameDualTexturesWithPoseTime(intptr_t backgroundTextureHandle, intptr_t foregroundTextureHandle, intptr_t audioData, int audioDataLen, int audioChannels, double timestamp, double poseTime, int *outSyncId)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_Media_SetHeadsetControllerPose(Posef headsetPose, Posef leftControllerPose, Posef rightControllerPose)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_Media_EnumerateCameraAnchorHandles(int *anchorCount, intptr_t *CameraAnchorHandle)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_Media_GetCurrentCameraAnchorHandle(intptr_t *anchorHandle)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_Media_GetCameraAnchorName(intptr_t anchorHandle, char *cameraName)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_Media_GetCameraAnchorHandle(intptr_t anchorName, intptr_t *anchorHandle)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_Media_GetCameraAnchorType(intptr_t anchorHandle, CameraAnchorType *anchorType)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_Media_CreateCustomCameraAnchor(intptr_t anchorName, intptr_t *anchorHandle)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_Media_DestroyCustomCameraAnchor(intptr_t anchorHandle)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_Media_GetCustomCameraAnchorPose(intptr_t anchorHandle, Posef *pose)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_Media_SetCustomCameraAnchorPose(intptr_t anchorHandle, Posef pose)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_Media_GetCameraMinMaxDistance(intptr_t anchorHandle, double *minDistance, double *maxDistance)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_Media_SetCameraMinMaxDistance(intptr_t anchorHandle, double minDistance, double maxDistance)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_Media_SetPlatformInitialized()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetSkeleton2(SkeletonType skeletonType, Skeleton2Internal *skeleton)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_PollEvent(EventDataBuffer *eventDataBuffer)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetNativeXrApiType(XrApi *xrApi)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetNativeOpenXRHandles(uint64_t *xrInstance, uint64_t *xrSession)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_PollEvent2(EventType *eventType, intptr_t *eventData)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_Media_GetPlatformCameraMode(PlatformCameraMode *platformCameraMode)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_Media_SetPlatformCameraMode(PlatformCameraMode platformCameraMode)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_SetEyeFovPremultipliedAlphaMode(bool enabled)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetEyeFovPremultipliedAlphaMode(bool *enabled)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_SetKeyboardOverlayUV(Vector2f uv)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_InitializeInsightPassthrough()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_ShutdownInsightPassthrough()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    bool ovrp_GetInsightPassthroughInitialized()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_SetInsightPassthroughStyle(int layerId, InsightPassthroughStyle style)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_CreateInsightTriangleMesh(int layerId, intptr_t vertices, int vertexCount, intptr_t triangles, int triangleCount, unsigned long *meshHandle)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_DestroyInsightTriangleMesh(unsigned long meshHandle)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_AddInsightPassthroughSurfaceGeometry(int layerId, unsigned long meshHandle, Matrix4x4 T_world_model, unsigned long *geometryInstanceHandle)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_DestroyInsightPassthroughGeometryInstance(unsigned long geometryInstanceHandle)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_UpdateInsightPassthroughGeometryTransform(unsigned long geometryInstanceHandle, Matrix4x4 T_world_model)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_LocateSpace(Posef *location, uint64_t *space, TrackingOrigin trackingOrigin)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_KtxLoadFromMemory(intptr_t *data, uint length, intptr_t *texture)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_KtxTextureWidth(intptr_t texture, uint *width)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_KtxTextureHeight(intptr_t texture, uint *height)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_KtxTranscode(intptr_t texture, uint format)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_KtxGetTextureData(intptr_t texture, intptr_t data, uint bufferSize)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_KtxTextureSize(intptr_t texture, uint *size)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_KtxDestroy(intptr_t texture)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_DestroySpace(uint64_t *space)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetInsightPassthroughInitializationState()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_Media_IsCastingToRemoteClient(bool *isCasting)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_LoadRenderModel(uint64_t modelKey, uint bufferInputCapacity, uint *bufferCountOutput, intptr_t buffer)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetRenderModelPaths(uint index, intptr_t path)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetRenderModelProperties(char *path, RenderModelPropertiesInternal *properties)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_SetInsightPassthroughKeyboardHandsIntensity(int layerId, InsightPassthroughKeyboardHandsIntensity intensity)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_StartKeyboardTracking(uint64_t trackedKeyboardId)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_StopKeyboardTracking()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetSystemKeyboardDescription(TrackedKeyboardQueryFlags keyboardQueryFlags, KeyboardDescription *keyboardDescription)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetKeyboardState(Step stepId, int frameIndex, KeyboardState *keyboardState)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetNodePoseStateImmediate(Node nodeId, PoseStatef *nodePoseState)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_SetLogCallback2(LogCallback2DelegateType logCallback)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_IsInsightPassthroughSupported(bool *supported)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    void ovrp_UnityOpenXR_SetClientVersion(int majorVersion, int minorVersion, int patchVersion)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return;
    }
    intptr_t ovrp_UnityOpenXR_HookGetInstanceProcAddr(intptr_t func)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    Result ovrp_UnityOpenXR_OnInstanceCreate(uint64_t xrInstance)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    void ovrp_UnityOpenXR_OnInstanceDestroy(uint64_t xrInstance)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return;
    }
    void ovrp_UnityOpenXR_OnSessionCreate(uint64_t xrSession)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return;
    }
    void ovrp_UnityOpenXR_OnAppSpaceChange(uint64_t xrSpace)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return;
    }
    void ovrp_UnityOpenXR_OnSessionStateChange(int oldState, int newState)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return;
    }
    void ovrp_UnityOpenXR_OnSessionBegin(uint64_t xrSession)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return;
    }
    void ovrp_UnityOpenXR_OnSessionEnd(uint64_t xrSession)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return;
    }
    void ovrp_UnityOpenXR_OnSessionExiting(uint64_t xrSession)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return;
    }
    void ovrp_UnityOpenXR_OnSessionDestroy(uint64_t xrSession)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return;
    }
    Result ovrp_SetSuggestedCpuPerformanceLevel(ProcessorPerformanceLevel perfLevel)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetSuggestedCpuPerformanceLevel(ProcessorPerformanceLevel *perfLevel)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_SetSuggestedGpuPerformanceLevel(ProcessorPerformanceLevel perfLevel)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetSuggestedGpuPerformanceLevel(ProcessorPerformanceLevel *perfLevel)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_CreateSpatialAnchor(SpatialAnchorCreateInfo *createInfo, uint64_t *requestId)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_SetSpaceComponentStatus(uint64_t *space, SpaceComponentType componentType, bool enable, double timeout, uint64_t *requestId)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetSpaceComponentStatus(uint64_t *space, SpaceComponentType componentType, bool *enabled, bool *changePending)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_EnumerateSpaceSupportedComponents(uint64_t *space, uint componentTypesCapacityInput, uint *componentTypesCountOutput, SpaceComponentType *componentTypes)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_SaveSpace(uint64_t *space, SpaceStorageLocation location, SpaceStoragePersistenceMode mode, uint64_t *requestId)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_QuerySpaces(SpaceQueryInfo *queryInfo, uint64_t *requestId)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_RetrieveSpaceQueryResults(uint64_t *requestId, uint32_t resultCapacityInput, uint32_t *resultCountOutput, intptr_t results)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_EraseSpace(uint64_t *space, SpaceStorageLocation location, uint64_t *requestId)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetSpaceContainer(uint64_t *space, SpaceContainerInternal *containerInternal)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetSpaceBoundingBox2D(uint64_t *space, Rectf *rect)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetSpaceBoundingBox3D(uint64_t *space, Boundsf *bounds)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetSpaceSemanticLabels(uint64_t *space, SpaceSemanticLabelInternal *labelsInternal)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetSpaceRoomLayout(uint64_t *space, RoomLayoutInternal *roomLayoutInternal)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetSpaceBoundary2D(uint64_t *space, PolygonalBoundary2DInternal *boundaryInternal)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_RequestSceneCapture(SceneCaptureRequestInternal *request, uint64_t *requestId)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetSpaceUuid(uint64_t *space, Guid *uuid)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }

    Result ovrp_CreateVirtualKeyboard(VirtualKeyboardCreateInfo createInfo)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }

    Result ovrp_DestroyVirtualKeyboard()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }

    Result ovrp_SendVirtualKeyboardInput(VirtualKeyboardInputInfo inputInfo, Posef *interactorRootPose)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }

    Result ovrp_ChangeVirtualKeyboardTextContext(char *textContext)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }

    Result ovrp_CreateVirtualKeyboardSpace(VirtualKeyboardSpaceCreateInfo createInfo, uint64_t *keyboardSpace)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }

    Result ovrp_SuggestVirtualKeyboardLocation(VirtualKeyboardLocationInfo locationInfo)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }

    Result ovrp_GetVirtualKeyboardScale(float *location)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }

    Result ovrp_GetVirtualKeyboardSound(VirtualKeyboardSoundInternal *sound)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }

    Result ovrp_GetVirtualKeyboardSwipeTrailState(VirtualKeyboardSwipeTrailState *swipeTrailState)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }

    Result ovrp_GetRenderModelProperties2(char *path, RenderModelFlags flags, RenderModelPropertiesInternal *properties)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetNodePoseStateAtTime(double time, Node nodeId, PoseStatef *nodePoseState)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetPassthroughCapabilityFlags(PassthroughCapabilityFlags *capabilityFlags)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetFoveationEyeTrackedSupported(bool *foveationSupported)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetFoveationEyeTracked(bool *isEyeTrackedFoveation)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_SetFoveationEyeTracked(bool isEyeTrackedFoveation)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_StartFaceTracking()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_StopFaceTracking()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_StartBodyTracking()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_StopBodyTracking()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_StartEyeTracking()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_StopEyeTracking()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetEyeTrackingSupported(bool *eyeTrackingSupported)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetFaceTrackingSupported(bool *faceTrackingSupported)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetBodyTrackingEnabled(bool *value)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetBodyTrackingSupported(bool *value)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetBodyState(Step stepId, int frameIndex, BodyStateInternal *bodyState)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetFaceTrackingEnabled(bool *faceTrackingEnabled)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetFaceState(Step stepId, int frameIndex, FaceStateInternal *faceState)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetEyeTrackingEnabled(bool *eyeTrackingEnabled)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetEyeGazesState(Step stepId, int frameIndex, EyeGazesStateInternal *eyeGazesState)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetControllerState5(uint controllerMask, ControllerState5 *controllerState)
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        ControllerState6 state = getControllerState(controllerMask);
        *controllerState = *((ControllerState5 *)&state);
        return Success;
    }
    Result ovrp_SetControllerLocalizedVibration(Controller controllerMask, HapticsLocation hapticsLocationMask, float frequency, float amplitude)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetLocalDimmingSupported(bool *localDimmingSupported)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_SetLocalDimming(bool localDimmingMode)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetLocalDimming(bool *localDimmingMode)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetCurrentInteractionProfile(Hand hand, InteractionProfile *interactionProfile)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_SetControllerHapticsAmplitudeEnvelope(
        Controller controllerMask,
        HapticsAmplitudeEnvelopeVibration hapticsVibration)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_SetControllerHapticsPcm(
        Controller controllerMask,
        HapticsPcmVibration hapticsVibration)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetControllerSampleRateHz(Controller controller, float *sampleRateHz)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    // NEW
    Result ovrp_ShareSpaces(uint64_t *spaces, uint32_t numSpaces, unsigned long *userHandles, uint32_t numUsers, uint64_t *requestId)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_SaveSpaceList(uint64_t *spaces, uint32_t numSpaces, SpaceStorageLocation location, uint64_t *requestId)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetSpaceUserId(uint64_t *spaceUserHandle, uint64_t *spaceUserId)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_CreateSpaceUser(uint64_t *spaceUserId, uint64_t *spaceUserHandle)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_DestroySpaceUser(uint64_t *userHandle)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_LocateSpace2(SpaceLocationf *location, uint64_t *space, TrackingOrigin trackingOrigin)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_DeclareUser(uint64_t *userId, uint64_t *userHandle)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetSpaceTriangleMesh(uint64_t *space, TriangleMeshInternal *triangleMeshInternal)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetControllerState6(uint controllerMask, ControllerState6 *controllerState)
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        ControllerState6 state = getControllerState(controllerMask);
        *controllerState = state;
        return Success;
    }
    Result ovrp_GetVirtualKeyboardModelAnimationStates(VirtualKeyboardModelAnimationStatesInternal *animationStates)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetVirtualKeyboardDirtyTextures(VirtualKeyboardTextureIdsInternal *textureIds)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetVirtualKeyboardTextureData(uint64_t textureId, VirtualKeyboardTextureData *textureData)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_SetVirtualKeyboardModelVisibility(VirtualKeyboardModelVisibility *visibility)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_CreatePassthroughColorLut(PassthroughColorLutChannels channels, uint32_t resolution, PassthroughColorLutData data, unsigned long *colorLut)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_DestroyPassthroughColorLut(unsigned long colorLut)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_UpdatePassthroughColorLut(unsigned long colorLut, PassthroughColorLutData data)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_SetInsightPassthroughStyle2(int layerId, InsightPassthroughStyle2 *style)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetLayerRecommendedResolution(int layerId, Sizei *recommendedDimensions)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetEyeLayerRecommendedResolution(Sizei *recommendedDimensions)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_QplMarkerStart(int markerId, int instanceKey, long timestampMs)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_QplMarkerEnd(int markerId, QplResultType resultTypeId, int instanceKey, long timestampMs)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_QplMarkerPoint(int markerId, char *name, int instanceKey, long timestampMs)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_QplMarkerPointCached(int markerId, int nameHandle, int instanceKey, long timestampMs)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_QplMarkerAnnotation(int markerId, char *annotationKey, char *annotationValue, int instanceKey)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_QplCreateMarkerHandle(char *name, int *nameHandle)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_QplDestroyMarkerHandle(int nameHandle)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_OnEditorShutdown()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetPassthroughCapabilities(PassthroughCapabilities *capabilityFlags)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_SetControllerDrivenHandPoses(bool controllerDrivenHandPoses)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_IsControllerDrivenHandPosesEnabled(bool *enabled)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_AreHandPosesGeneratedByControllerData(Step stepId, Node nodeId, bool *isGeneratedByControllerData)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_SetMultimodalHandsControllersSupported(bool supported)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_IsMultimodalHandsControllersSupported(bool *supported)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetCurrentDetachedInteractionProfile(Hand hand, InteractionProfile *interactionProfile)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetControllerIsInHand(Step stepId, Node nodeId, bool *isInHand)
    {
        *isInHand = false;
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetPassthroughPreferences(PassthroughPreferences *preferences)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_SetEyeBufferSharpenType(LayerSharpenType sharpenType)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_SetControllerDrivenHandPosesAreNatural(bool controllerDrivenHandPosesAreNatural)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_AreControllerDrivenHandPosesNatural(bool *natural)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_SetSimultaneousHandsAndControllersEnabled(bool enabled)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetFaceState2(Step stepId, int frameIndex, FaceState2Internal *faceState)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_StartFaceTracking2(FaceTrackingDataSource *requestedDataSources, uint requestedDataSourcesCount)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_StopFaceTracking2()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetFaceTracking2Enabled(bool *faceTracking2Enabled)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetFaceTracking2Supported(bool *faceTracking2Enabled)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_RequestBodyTrackingFidelity(BodyTrackingFidelity2 fidelity)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_SuggestBodyTrackingCalibrationOverride(BodyTrackingCalibrationInfo calibrationInfo)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_ResetBodyTrackingCalibration()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetBodyState4(Step stepId, int frameIndex, BodyState4Internal *bodyState)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetSkeleton3(SkeletonType skeletonType, Skeleton3Internal *skeleton)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_StartBodyTracking2(BodyJointSet jointSet)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_QplSetConsent(bool consent)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_SetWideMotionModeHandPoses(bool wideMotionModeHandPoses)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_IsSetWideMotionModeHandPosesEnabled(bool *enabled)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_SetDeveloperTelemetryConsent(bool consent)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_QplMarkerAnnotationVariant(int markerId, char *annotationKey, QplVariant *annotationValue, int instanceKey)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_QplMarkerPointData(int markerId, char *name, QplAnnotation *annotations, int annotationCount, int instanceKey, long timestampMs)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_DiscoverSpaces(SpaceDiscoveryInfo *info, uint64_t *requestId)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_RetrieveSpaceDiscoveryResults(uint64_t requestId, SpaceDiscoveryResults *results)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_SaveSpaces(uint32_t spaceCount, uint64_t *spaces, uint64_t *requestId)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_EraseSpaces(uint32_t spaceCount, uint64_t *spaces, uint32_t uuidCount, Guid *uuids, uint64_t *requestId)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }

    bool initializeOVRP(RenderAPIType apiType, int *logCallBack, jobject *activity, VkInstance *OVRPInstance, VkPhysicalDevice *OVRPPhysicalDevice, VkDevice *OvrpDevice, int *OVRPCommandQueue, int *initializeFlags)
    {
        int eventCount = 0;

        // Log everything please.
        minLogLevel_PxrAPI = 8;

        PxrInitParamData initParamData = {
            .activity = activity,
            .vm = VM,
            .controllerdof = 1,
            .headdof = 1,
        };

        Pxr_SetInitializeData(&initParamData);
        Pxr_SetPlatformOption(PXR_UNITY);

        switch (apiType)
        {
        case ovrRenderAPI_Vulkan:
        {
            Pxr_SetGraphicOption(PXR_VULKAN);

            PxrVulkanBinding vulkanBinding = {
                .instance = *OVRPInstance,
                .physicalDevice = *OVRPPhysicalDevice,
                .device = *OvrpDevice,
            };

            Pxr_Initialize();

            Pxr_CreateVulkanSystem(&vulkanBinding);
            break;
        }
        case ovrRenderAPI_OpenGL:
        {
            Pxr_SetGraphicOption(PXR_OPENGL_ES);

            Pxr_Initialize();
            break;
        }
        default:
        {
            break;
        }
        }

        PxrEventDataBuffer *eventDataPointer[20]{};

        while (Pxr_PollEvent(20, &eventCount, eventDataPointer))
        {
            for (int i = 0; i < eventCount; i++)
            {
                if (eventDataPointer[i]->type == PXR_TYPE_EVENT_DATA_SESSION_STATE_READY)
                {
                    Pxr_BeginXr();
                }
                else if (eventDataPointer[i]->type == PXR_TYPE_EVENT_DATA_SESSION_STATE_STOPPING)
                {
                    Pxr_EndXr();
                }
                else if (eventDataPointer[i]->type == PXR_TYPE_EVENT_DATA_CONTROLLER)
                {
                    PxrEventDataControllerChanged *data = ((PxrEventDataControllerChanged *)eventDataPointer[i]);
                }
            }
        }

        return true;
    }

    // Vulkan
    bool ovrp_Initialize5(RenderAPIType apiType, int *logCallBack, jobject *activity, VkInstance *OVRPInstance, VkPhysicalDevice *OVRPPhysicalDevice, VkDevice *OvrpDevice, int *OVRPCommandQueue, int *initializeFlags)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        if (activity == NULL)
        {
            // We don't have an activity class.
            // Find either the Unity Player or the Unreal class
            jobject unityPlayerClass = env->FindClass("com/unity3d/player/UnityPlayer");
            if (unityPlayerClass == NULL)
            {
                jobject unrealClass = env->FindClass("com/epicgames/ue4/GameActivity");
                if (unrealClass == NULL)
                {
                    // Unable to find.
                    return false;
                }
                else
                {
                    activity = &unrealClass;
                }
            }
            else
            {
                activity = &unityPlayerClass;
            }

            initializeOVRP(apiType, logCallBack, activity, OVRPInstance, OVRPPhysicalDevice, OvrpDevice, OVRPCommandQueue, initializeFlags);
        }
        else
        {
            initializeOVRP(apiType, logCallBack, activity, OVRPInstance, OVRPPhysicalDevice, OvrpDevice, OVRPCommandQueue, initializeFlags);
        }

        return Pxr_Initialize();
    }

    Result ovrp_GetNativeSDKPointer2()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetDisplayAdapterId(void *luid)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_SetupDistortionWindow3(int ovrpDistortionWindowFlag)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_DestroyDistortionWindow2()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_SetupEyeTexture2(Eye eye, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }

    Result ovrp_DestroyEyeTexture(Eye eye, int param_2)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetEyeTextureStageCount()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_SetEyeTextureFlippedY(int param_1)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_SetEyeViewportScale(float eyeViewPortScale)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetEyeOcclusionMesh()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetEyePreviewRect(Eye eye, long param_2)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_EndEye2(Eye eye, int param_2)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetNodeOrientationTracked2(Node nodeId, bool *nodeOrientationTracked)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        *nodeOrientationTracked = true;
        return Success;
    }
    Result ovrp_GetNodePositionTracked2(Node nodeId, bool *nodePositionTracked)
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        /*switch (nodeId)
        {
        case HandLeft:
        case HandRight:
        case EyeCenter:
            *nodePositionTracked = true;
            break;

        default:
            *nodePositionTracked = false;
            break;
        }*/
        *nodePositionTracked = true;

        return Success;
    }
    bool ovrp_GetNodePositionTracked(Node nodeId)
    {
        LogFunction(IMPLEMENTED, NORMAL, __func__);

        bool isTracked;

        ovrp_GetNodePositionTracked2(nodeId, &isTracked);

        return isTracked;
    }
    bool ovrp_GetAppShouldRecreateDistortionWindow()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetAppShouldRecreateDistortionWindow2(bool *shouldRecreateDistortionWindow)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_SetupDisplayObjects()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_SetupDisplayObjects2(long eglContext, long display, long nativeWindow)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    bool ovrp_GetSystemMultiViewSupported()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    Result ovrp_GetSystemMultiViewSupported2(bool *systemMultiViewSupported)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    bool ovrp_GetEyeTextureArraySupported()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return 0;
    }
    Result ovrp_GetEyeTextureArraySupported2(bool *eyeTextureArraySupported)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_SetEyeTextureArrayEnabled(bool *setEyeTextureArrayEnabled)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_SetThreadPerformance()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_AutoThreadScheduling()
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetInstanceExtensionsVk(uint8_t *extensionsData, int32_t *extensionCount)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetDeviceExtensionsVk(uint8_t *extensionsData, int32_t *extensionCount)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetLayerTextureFoveation(int OVRPLayerId, int textureIndex, Eye eye, long *foveationTextures, long *foveationTextureSize)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_SetAppAsymmetricFov(bool appAsymmetricFovEnabled)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetDepthCompositingSupported(bool *depthSupported)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetLayerTexture2(int OVRPLayerId, int textureIndex, Eye eye, unsigned long *colorTextures, unsigned long *depthTextures)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_SetupLayerDepth(long param_1, int param_2, int param_3)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_GetEyeFovLayerId(long layerId)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }
    Result ovrp_SetDepthProjInfo(long param_1, long param_2, int param_3)
    {
        LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

        return Success;
    }

#if defined(__cplusplus)
} // extern "C"
#endif