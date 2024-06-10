#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <time.h>
#include <math.h>
#include <android/log.h>

#include "OVRPlugin.h"
#include "OculusXRPlugin.h"
#include "/include/PxrPlugin.h"
#include "/include/PxrInput.h"
#include "/include/Globals.h"
#include "/include/PxrPlatform.h"
#include "/include/PxrPlatformLoader.h"
#include "/src/PxrUnityPluginLoader.c"
#include "/src/PxrToOculusMapper.c"

/* LEGACY (TODO) */
bool ovrp_PreInitialize() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 1;
}
bool ovrp_Initialize(RenderAPIType apiType, intptr_t platformArgs) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    Pxr_SetGraphicOption(PXR_OPENGL_ES);
    return Pxr_Initialize();
}
bool ovrp_Shutdown() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return Pxr_Shutdown();
}
bool ovrp_SetupDistortionWindow() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
bool ovrp_DestroyDistortionWindow() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
bool ovrp_RecreateEyeTexture(Eye eyeId, int stage, void* device, int height, int width, int samples, bool isSRGB, void* result) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
bool ovrp_SetEyeTexture(Eye eyeId, intptr_t texture) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
bool ovrp_Update(int frameIndex) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return Pxr_WaitFrame();
}
bool ovrp_BeginFrame(int frameIndex) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return Pxr_BeginFrame();
}
bool ovrp_EndEye(Eye eye) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
bool ovrp_EndFrame(int frameIndex) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return Pxr_EndFrame();
}
bool ovrp_RecenterPose() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
/* END */

//NON-LEGACY
void UnityPluginLoad(void *unityInterfaces) {
    //Crashes the game...
    /*
    Pxr_UnityPluginLoad(unityInterfaces);*/
}
Sizei ovrp_GetEyeTextureSize(Eye eyeId) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    Sizei sizeiDummy;
    return sizeiDummy;
}
bool ovrp_SetOverlayQuad2(bool onTop, bool headLocked, intptr_t texture, intptr_t device, Posef pose, Vector3f scale) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}

PoseStatef getPosefStateForController(int deviceID) {
    PxrControllerTracking tracking;
    float *headSensorData;

    Pxr_GetHeadSensorData(headSensorData);
    Pxr_GetControllerTrackingState(deviceID, 0, headSensorData, &tracking);

    PoseStatef poseStatef = {
            .Pose = *((Posef*)&tracking.localControllerPose.pose),
            .Velocity = *((Vector3f*)&tracking.localControllerPose.linearVelocity),
            .Acceleration = *((Vector3f*)&tracking.localControllerPose.linearAcceleration),
            .AngularVelocity = *((Vector3f*)&tracking.localControllerPose.angularVelocity),
            .AngularAcceleration = *((Vector3f*)&tracking.localControllerPose.angularAcceleration),
    };
    return poseStatef;
}

PoseStatef getPosefStateForSensor() {
    int sensorFrameIndex;
    double predictedDisplayTimeMS;

    PxrSensorState2 sensorState;

    Pxr_GetPredictedDisplayTime(&predictedDisplayTimeMS);

    Pxr_GetPredictedMainSensorState2(predictedDisplayTimeMS, &sensorState, &sensorFrameIndex);

    PoseStatef poseStatef = {
            .Pose = *((Posef*)&sensorState.pose),
            .Velocity = *((Vector3f*)&sensorState.linearVelocity),
            .Acceleration = *((Vector3f*)&sensorState.linearAcceleration),
            .AngularVelocity = *((Vector3f*)&sensorState.angularVelocity),
            .AngularAcceleration = *((Vector3f*)&sensorState.angularVelocity),
    };

    return poseStatef;
}

Posef getPosefForController(int deviceID) {
    return getPosefStateForController(deviceID).Pose;
}

Posef getPosefForSensor() {
    return getPosefStateForSensor().Pose;
}

Posef GetNodePose(Node nodeId) {
    Posef poseStateDummy;

    switch (nodeId) {
        case EyeCenter:
        case Head:
            return getPosefForSensor();
            break;
        case HandLeft:
        case HandRight:
            return getPosefForController(nodeId - 3);
        default:
            return poseStateDummy;
            break;
    }
}

PoseStatef GetNodePoseState(Node nodeId) {
    PoseStatef poseStateDummy;

    switch (nodeId) {
        case EyeCenter:
        case Head:
            return getPosefStateForSensor();
            break;
        case HandLeft:
        case HandRight:
            return getPosefStateForController(nodeId - 3);
        default:
            return poseStateDummy;
            break;
    }
}

Posef ovrp_GetNodePose(Node nodeId) {
    __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    return GetNodePose(nodeId);
}

bool ovrp_SetControllerVibration(uint controllerMask, float frequency, float amplitude) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Posef ovrp_GetNodeVelocity(Node nodeId) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    Posef posefDummy;
    return posefDummy;
}
Posef ovrp_GetNodeAcceleration(Node nodeId) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    Posef posefDummy;
    return posefDummy;
}
TrackingOrigin ovrp_GetTrackingOriginType() {
    PxrTrackingOrigin pxrTrackingOriginDummy;
    //Doesn't actually use the argument?
    return (TrackingOrigin)Pxr_GetTrackingOrigin(&pxrTrackingOriginDummy);
}
bool ovrp_SetTrackingOriginType(TrackingOrigin originType) {
    return Pxr_SetTrackingOrigin((PxrTrackingOrigin) originType);
}
Posef ovrp_GetTrackingCalibratedOrigin() {
    Posef posefDummy;
    return posefDummy;
}
bool ovrp_RecenterTrackingOrigin(uint flags) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
bool ovrp_GetInitialized() {
    return Pxr_IsInitialized();
}
intptr_t ovrp_GetVersion() {
    return ((intptr_t)OVRP_VERSION);
}
intptr_t ovrp_GetNativeSDKVersion() {
    return ((intptr_t)OVRP_VERSION);
}
intptr_t ovrp_GetAudioOutId() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
intptr_t ovrp_GetAudioInId() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
float ovrp_GetEyeTextureScale() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
bool ovrp_SetEyeTextureScale(float value) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
bool ovrp_GetTrackingOrientationSupported() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
bool ovrp_GetTrackingOrientationEnabled() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
bool ovrp_SetTrackingOrientationEnabled(bool value) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
bool ovrp_GetTrackingPositionSupported() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
bool ovrp_GetTrackingPositionEnabled() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
bool ovrp_SetTrackingPositionEnabled(bool value) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
bool ovrp_GetNodePresent(Node nodeId) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 1;
}
bool ovrp_GetNodeOrientationTracked(Node nodeId) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 1;
}
bool ovrp_GetNodePositionTracked(Node nodeId) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 1;
}
Frustumf ovrp_GetNodeFrustum(Node nodeId) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    float left, right, top, bottom, near, far;

    if (nodeId <= 2) {
        Pxr_GetFrustum(*((PxrEyeType*)&nodeId), &left, &right, &top, &bottom, &near, &far);
    }
    Frustumf frustumf = {
            .zNear = near,
            .zFar = far,
            .fovX = top,
            .fovY = bottom,
    };
    return frustumf;
}

int getConnectedControllers() {
    int connectedControllers = 2;

    //Check controller status
    connectedControllers -= Pxr_GetControllerConnectStatus(PXR_CONTROLLER_LEFT);
    connectedControllers -= Pxr_GetControllerConnectStatus(PXR_CONTROLLER_RIGHT);
    return connectedControllers;
}

uint getButtonsFromState(PxrControllerInputState pxrState, uint shift) {
    uint state = 0;
    state |= pxrState.AXValue * Button_One << shift;
    state |= pxrState.BYValue * Button_Two << shift;
    return state;
}

//Refer to Controller enum.
ControllerState getControllerState(uint controllerMask) {

    PxrControllerInputState controllerState;
    ControllerState state;

    state.Buttons = 0;

    if (controllerMask & LTouch) {
        Pxr_GetControllerInputState(PXR_CONTROLLER_LEFT, &controllerState);

        state.Buttons |= getButtonsFromState(controllerState, LeftController_Start);

        state.LIndexTrigger = controllerState.triggerValue;
        state.LHandTrigger = controllerState.gripValue;
        state.LThumbstick = *((Vector2f*)&controllerState.Joystick);
    }

    if (controllerMask & RTouch) {
        Pxr_GetControllerInputState(PXR_CONTROLLER_RIGHT, &controllerState);

        state.Buttons |= getButtonsFromState(controllerState, RightController_Start);

        state.RIndexTrigger = controllerState.triggerValue;
        state.RHandTrigger = controllerState.gripValue;
        state.RThumbstick = *((Vector2f*)&controllerState.Joystick);
    }

    state.ConnectedControllers = getConnectedControllers();
    return state;
}

ControllerState ovrp_GetControllerState(uint controllerMask) {
    return getControllerState(controllerMask);
}

// Deprecated. Replaced by ovrp_GetSuggestedCpuPerformanceLevel
int ovrp_GetSystemCpuLevel() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
//Deprecated. Replaced by ovrp_SetSuggestedCpuPerformanceLevel
bool ovrp_SetSystemCpuLevel(int value) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
//Deprecated. Replaced by ovrp_GetSuggestedGpuPerformanceLevel
int ovrp_GetSystemGpuLevel() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
//Deprecated. Replaced by ovrp_SetSuggestedGpuPerformanceLevel
bool ovrp_SetSystemGpuLevel(int value) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
bool ovrp_GetSystemPowerSavingMode() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
float ovrp_GetSystemDisplayFrequency() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
int ovrp_GetSystemVSyncCount() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
float ovrp_GetSystemVolume() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
BatteryStatus ovrp_GetSystemBatteryStatus() {
    return Full;
}
float ovrp_GetSystemBatteryLevel() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
float ovrp_GetSystemBatteryTemperature() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
intptr_t ovrp_GetSystemProductName() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
bool ovrp_ShowSystemUI(PlatformUI ui) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
bool ovrp_GetAppMonoscopic() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
bool ovrp_SetAppMonoscopic(bool value) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
bool ovrp_GetAppHasVrFocus() {
    return 1;
}
bool ovrp_GetAppShouldQuit() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
bool ovrp_GetAppShouldRecenter() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
intptr_t ovrp_GetAppLatencyTimings() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
bool ovrp_GetUserPresent() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 1;
}
float ovrp_GetUserIPD() {
    return Pxr_GetIPD();
}
bool ovrp_SetUserIPD(float value) {
    //Maybe later, need to test if this doesn't set it to dangerous levels.
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
float ovrp_GetUserEyeDepth() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
bool ovrp_SetUserEyeDepth(float value) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
float ovrp_GetUserEyeHeight() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
bool ovrp_SetUserEyeHeight(float value) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
bool ovrp_SetSystemVSyncCount(int vsyncCount) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
bool ovrpi_SetTrackingCalibratedOrigin() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
bool ovrp_GetEyeOcclusionMeshEnabled() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
bool ovrp_SetEyeOcclusionMeshEnabled(bool value) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
bool ovrp_GetSystemHeadphonesPresent() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
SystemRegion ovrp_GetSystemRegion() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
bool ovrp_GetTrackingIPDEnabled() {
    return false;
    //return Pvr_GetTrackingIPDEnabled();
}
bool ovrp_SetTrackingIPDEnabled(bool value) {
    return false;
    //return Pvr_SetTrackingIPDEnabled(value);
}
HapticsDesc ovrp_GetControllerHapticsDesc(uint controllerMask) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    HapticsDesc hapticsDescDummy;
    return hapticsDescDummy;
}
HapticsState ovrp_GetControllerHapticsState(uint controllerMask) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    HapticsState hapticsStateDummy;
    return hapticsStateDummy;
}
bool ovrp_SetControllerHaptics(uint controllerMask, HapticsBuffer hapticsBuffer) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
bool ovrp_SetOverlayQuad3(uint flags, intptr_t textureLeft, intptr_t textureRight, intptr_t device, Posef pose, Vector3f scale, int layerIndex) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
float ovrp_GetEyeRecommendedResolutionScale() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
float ovrp_GetAppCpuStartToGpuEndTime() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
int ovrp_GetSystemRecommendedMSAALevel() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
bool ovrp_GetAppChromaticCorrection() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
bool ovrp_SetAppChromaticCorrection(bool value) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
bool ovrp_GetBoundaryConfigured() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
//Deprecated. This function will not be supported in OpenXR
BoundaryTestResult ovrp_TestBoundaryNode(Node nodeId, BoundaryType boundaryType) {
    BoundaryTestResult boundaryTestResultDummy;
    return boundaryTestResultDummy;
}
//Deprecated. This function will not be supported in OpenXR
BoundaryTestResult ovrp_TestBoundaryPoint(Vector3f point, BoundaryType boundaryType) {
    BoundaryTestResult boundaryTestResultDummy;
    return boundaryTestResultDummy;
}
BoundaryGeometry ovrp_GetBoundaryGeometry(BoundaryType boundaryType) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    BoundaryGeometry boundaryGeometryDummy;
    return boundaryGeometryDummy;
}
Vector3f ovrp_GetBoundaryDimensions(BoundaryType boundaryType) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    Vector3f vector3FDummy;
    return vector3FDummy;
}
//Deprecated. This function will not be supported in OpenXR
bool ovrp_GetBoundaryVisible() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
//Deprecated. This function will not be supported in OpenXR
bool ovrp_SetBoundaryVisible(bool value) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
bool ovrp_Update2(int stateId, int frameIndex, double predictionSeconds) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Posef ovrp_GetNodePose2(int stateId, Node nodeId) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    //TODO: StateId?
    return GetNodePose(nodeId);
}
Posef ovrp_GetNodeVelocity2(int stateId, Node nodeId) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    Posef posefDummy;
    return posefDummy;
}
Posef ovrp_GetNodeAcceleration2(int stateId, Node nodeId) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    Posef posefDummy;
    return posefDummy;
}
enum SystemHeadset ovrp_GetSystemHeadsetType() {
    return Meta_Quest_3;
}
Controller ovrp_GetActiveController() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return All;
}
Controller ovrp_GetConnectedControllers() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return All;
}
bool ovrp_GetBoundaryGeometry2(BoundaryType boundaryType, intptr_t points, int *pointsCount) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
AppPerfStats ovrp_GetAppPerfStats() {
    AppPerfStats appPerfStatsDummy;
    return appPerfStatsDummy;
}
bool ovrp_ResetAppPerfStats() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
bool ovrp_SetDesiredEyeTextureFormat(EyeTextureFormat value) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
EyeTextureFormat ovrp_GetDesiredEyeTextureFormat() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
float ovrp_GetAppFramerate() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
PoseStatef ovrp_GetNodePoseState(Step stepId, Node nodeId) {
    return GetNodePoseState(nodeId);
}
ControllerState2 ovrp_GetControllerState2(uint controllerMask) {
    ControllerState state = getControllerState(controllerMask);
    ControllerState2 base = *((ControllerState2*)&state);
    //Add more.
    return base;
}
Result ovrp_InitializeMixedReality() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_ShutdownMixedReality() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
bool ovrp_GetMixedRealityInitialized() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_UpdateExternalCamera() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetExternalCameraCount(int *cameraCount) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetExternalCameraName(int cameraId, char *cameraName) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetExternalCameraIntrinsics(int cameraId, CameraIntrinsics *cameraIntrinsics) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetExternalCameraExtrinsics(int cameraId, CameraExtrinsics *cameraExtrinsics) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}

//LAYERS
Result ovrp_CalculateLayerDesc(OverlayShape shape, LayerLayout layout, Sizei *textureSize,
                               int mipLevels, int sampleCount, EyeTextureFormat format, int layerFlags, LayerDesc *layerDesc) {
    __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
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
    return 1;
}

char layersCreated[15];
char layersCreated2[15];
Result ovrp_EnqueueSetupLayer(LayerDesc *desc, int *layerId) {
    if (layersCreated[*layerId] != true) {
        PxrLayerParam layerParam = {
                .layerId = (*layerId)+1,
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
                .layerFlags = desc->LayerFlags,

                .externalImageCount = 0,
        };
        layersCreated[*layerId] = true;
        return Pxr_CreateLayer(&layerParam);
    }
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_EnqueueDestroyLayer(int *layerId) {
    layersCreated[*layerId] = false;
    layersCreated2[*layerId] = false;
    return Pxr_DestroyLayer((*layerId) + 1);
}
Result ovrp_GetLayerTextureStageCount(int layerId, uint32_t *layerTextureStageCount) {
    return Pxr_GetLayerImageCount(layerId, PXR_EYE_BOTH, layerTextureStageCount);
}
Result ovrp_GetLayerTexturePtr(int layerId, int stage, Eye eyeId, uint64_t *textureHandle) {
    return Pxr_GetLayerImage(layerId, *((PxrEyeType*)&eyeId), stage, textureHandle);
}
Result ovrp_EnqueueSubmitLayer(uint flags, intptr_t textureLeft, intptr_t textureRight, int layerId, int frameIndex, Posef *pose, Vector3f *scale, int layerIndex) {
    //Idfk
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
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetNodeFrustum2(Node nodeId, Frustumf2 *nodeFrustum) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif

    float left, right, top, bottom, near, far;
    float fovLeft, fovRight, fovUp, fovDown;

    if (nodeId <= 2) {
        Pxr_GetFov(*((PxrEyeType*)&nodeId), &fovLeft, &fovRight, &fovUp, &fovDown);
        Pxr_GetFrustum(*((PxrEyeType*)&nodeId), &left, &right, &top, &bottom, &near, &far);
    }

    Frustumf2 frustumf = {
            .zNear = near,
            .zFar = far,
            .Fov = fovUp,
    };

    *nodeFrustum = frustumf;
    return 0;
}
bool ovrp_GetEyeTextureArrayEnabled() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_UpdateCameraDevices() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
bool ovrp_IsCameraDeviceAvailable(CameraDevice cameraDevice) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_SetCameraDevicePreferredColorFrameSize(CameraDevice cameraDevice, Sizei preferredColorFrameSize) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_OpenCameraDevice(CameraDevice cameraDevice) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_CloseCameraDevice(CameraDevice cameraDevice) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
bool ovrp_HasCameraDeviceOpened(CameraDevice cameraDevice) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
bool ovrp_IsCameraDeviceColorFrameAvailable(CameraDevice cameraDevice) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetCameraDeviceColorFrameSize(CameraDevice cameraDevice, Sizei *colorFrameSize) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetCameraDeviceColorFrameBgraPixels(CameraDevice cameraDevice, intptr_t *colorFrameBgraPixels, int *colorFrameRowPitch) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetControllerState4(uint controllerMask, ControllerState4 *controllerState) {
    ControllerState state = getControllerState(controllerMask);
    *controllerState = *((ControllerState4*)&state);
    return 0;
}

// UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN
Result ovrp_GetExternalCameraPose(CameraDevice camera, Posef *cameraPose) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_ConvertPoseToCameraSpace(CameraDevice camera, Posef *trackingSpacePose, Posef *cameraSpacePose) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetCameraDeviceIntrinsicsParameters(CameraDevice camera, bool *supportIntrinsics, CameraDeviceIntrinsicsParameters *intrinsicsParameters) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_DoesCameraDeviceSupportDepth(CameraDevice camera, bool *supportDepth) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetCameraDeviceDepthSensingMode(CameraDevice camera, CameraDeviceDepthSensingMode *depthSensoringMode) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_SetCameraDeviceDepthSensingMode(CameraDevice camera, CameraDeviceDepthSensingMode depthSensoringMode) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetCameraDevicePreferredDepthQuality(CameraDevice camera, CameraDeviceDepthQuality *depthQuality) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_SetCameraDevicePreferredDepthQuality(CameraDevice camera, CameraDeviceDepthQuality depthQuality) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_IsCameraDeviceDepthFrameAvailable(CameraDevice camera, bool *available) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetCameraDeviceDepthFrameSize(CameraDevice camera, Sizei *depthFrameSize) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetCameraDeviceDepthFramePixels(CameraDevice cameraDevice, intptr_t *depthFramePixels, int *depthFrameRowPitch) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetCameraDeviceDepthConfidencePixels(CameraDevice cameraDevice, intptr_t *depthConfidencePixels, int *depthConfidenceRowPitch) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
//END

Result ovrp_SetHandNodePoseStateLatency(double latencyInSeconds) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetHandNodePoseStateLatency(double *latencyInSeconds) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetAppHasInputFocus(bool *appHasInputFocus) {
    *appHasInputFocus = 1;
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetTiledMultiResSupported(bool *foveationSupported) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetTiledMultiResLevel(FixedFoveatedRenderingLevel *level) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_SetTiledMultiResLevel(FixedFoveatedRenderingLevel level) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetGPUUtilSupported(bool *gpuUtilSupported) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetGPUUtilLevel(float *gpuUtil) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetSystemDisplayFrequency2(float *systemDisplayFrequency) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetSystemDisplayAvailableFrequencies(int *systemDisplayAvailableFrequencies, int *numFrequencies) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif

    /**numFrequencies = 1;
    int frequencies[1] = {72};
    systemDisplayAvailableFrequencies = *((int **)&frequencies);*/

    return 0;//Pxr_GetDisplayRefreshRatesAvailable(numFrequencies, &systemDisplayAvailableFrequencies);
}
Result ovrp_SetSystemDisplayFrequency(float requestedFrequency) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetAppAsymmetricFov(bool *useAsymmetricFov) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetDominantHand(Handedness *dominantHand) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_SendEvent(char *name, char *param) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}

Result ovrp_EnqueueSetupLayer2(LayerDesc *desc, int compositionDepth, int *layerId) {
    if (layersCreated2[*layerId] != true) {
        PxrLayerParam layerParam = {
                .layerId = (*layerId) + 1,
                .layerShape = PXRConvertToOverLayShape(desc->Shape),
                .layerType = PXR_OVERLAY,
                .layerLayout = PXRConvertToLayerLayout(desc->Layout),
                .format = 0x8058,//*((int*)&desc->Format),
                .width = desc->TextureSize.w,
                .height = desc->TextureSize.h,
                .sampleCount = desc->SampleCount,

                .faceCount = 1,
                .arraySize = 1,

                .mipmapCount = desc->MipLevels,
                .layerFlags = desc->LayerFlags,

                .externalImageCount = 0,
        };
        layersCreated2[*layerId] = true;
        return Pxr_CreateLayer(&layerParam);
    }
    return 0;
}
Result ovrp_GetLayerAndroidSurfaceObject(int layerId, intptr_t *surfaceObject) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_SetHeadPoseModifier(Quatf *relativeRotation, Vector3f *relativeTranslation) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetHeadPoseModifier(Quatf *relativeRotation, Vector3f *relativeTranslation) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetNodePoseStateRaw(Step stepId, int frameIndex, Node nodeId, PoseStatef *nodePoseState) {
    __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called! But not implemented!", __func__);
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetCurrentTrackingTransformPose(Posef *trackingTransformPose) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetTrackingTransformRawPose(Posef *trackingTransformRawPose) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_SendEvent2(char *name, char *param, char *source) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_IsPerfMetricsSupported(PerfMetrics perfMetrics, bool *isSupported) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetPerfMetricsFloat(PerfMetrics perfMetrics, float *value) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetPerfMetricsInt(PerfMetrics perfMetrics, int *value) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetTimeInSeconds(double *value) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_SetColorScaleAndOffset(Vector4 colorScale, Vector4 colorOffset, bool applyToAllLayers) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_AddCustomMetadata(char *name, char *param) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_EnqueueSubmitLayer2(uint flags, intptr_t textureLeft, intptr_t textureRight, int layerId, int frameIndex, Posef *pose, Vector3f *scale, int layerIndex, bool overrideTextureRectMatrix, TextureRectMatrixf *textureRectMatrix, bool overridePerLayerColorScaleAndOffset, Vector4 *colorScale, Vector4 *colorOffset) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetTrackingTransformRelativePose(Posef *trackingTransformRelativePose, TrackingOrigin trackingOrigin) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_Media_Initialize() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_Media_Shutdown() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_Media_GetInitialized(bool *initialized) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    //*initialized = 1;
    return 0;
}
Result ovrp_Media_Update() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_Media_GetMrcActivationMode(MrcActivationMode *activationMode) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_Media_SetMrcActivationMode(MrcActivationMode activationMode) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_Media_IsMrcEnabled(bool *mrcEnabled) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_Media_IsMrcActivated(bool *mrcActivated) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_Media_UseMrcDebugCamera(bool *useMrcDebugCamera) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_Media_SetMrcInputVideoBufferType(InputVideoBufferType inputVideoBufferType) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_Media_GetMrcInputVideoBufferType(InputVideoBufferType *inputVideoBufferType) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_Media_SetMrcFrameSize(int frameWidth, int frameHeight) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_Media_GetMrcFrameSize(int *frameWidth, int *frameHeight) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_Media_SetMrcAudioSampleRate(int sampleRate) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif

    return 0;
}
Result ovrp_Media_GetMrcAudioSampleRate(int *sampleRate) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_Media_SetMrcFrameImageFlipped(bool flipped) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_Media_GetMrcFrameImageFlipped(bool *flipped) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_Media_EncodeMrcFrame(intptr_t rawBuffer, intptr_t audioDataPtr, int audioDataLen, int audioChannels, double timestamp, int *outSyncId) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_Media_EncodeMrcFrameWithDualTextures(intptr_t backgroundTextureHandle, intptr_t foregroundTextureHandle, intptr_t audioData, int audioDataLen, int audioChannels, double timestamp, int *outSyncId) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_Media_SyncMrcFrame(int syncId) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
//Result ovrp_GetExternalCameraCalibrationRawPose(int cameraId, Posef *rawPose)
Result ovrp_SetDeveloperMode(bool active) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetNodeOrientationValid(Node nodeId, bool *nodeOrientationValid) {
    
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetNodePositionValid(Node nodeId, bool *nodePositionValid) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    //*nodePositionValid = 1;
    return 0;
}
Result ovrp_GetAdaptiveGpuPerformanceScale2(float *adaptiveGpuPerformanceScale) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetHandTrackingEnabled(bool *handTrackingEnabled) {
    *handTrackingEnabled = false;
    //return Pxr_GetHandTrackerSettingState(handTrackingEnabled);
    return 0;
}
void GetPXRHandStateForOVR(int hand, HandStateInternal *handState) {
    //Get aim state.
    PxrHandAimState aimState;
    Pxr_GetHandTrackerAimState(hand, &aimState);

    //Get the joint locations
    PxrHandJointsLocations jointsLocations;
    Pxr_GetHandTrackerJointLocations(hand, &jointsLocations);

    PoseStatef headsetPosef = getPosefStateForSensor();

    PxrHandCombinedStateToOVRHandState(aimState, jointsLocations, handState);
}
Result ovrp_GetHandState(Step stepId, Hand hand, HandStateInternal *handState) {
    GetPXRHandStateForOVR(hand, handState);
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetSkeleton(SkeletonType skeletonType, Skeleton *skeleton) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetMesh(MeshType meshType, intptr_t meshPtr) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_OverrideExternalCameraFov(int cameraId, bool useOverriddenFov, Fovf *fov) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetUseOverriddenExternalCameraFov(int cameraId, bool *useOverriddenFov) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_OverrideExternalCameraStaticPose(int cameraId, bool useOverriddenPose, Posef *poseInStageOrigin) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetUseOverriddenExternalCameraStaticPose(int cameraId, bool *useOverriddenStaticPose) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_ResetDefaultExternalCamera() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_SetDefaultExternalCamera(char *cameraName, CameraIntrinsics *cameraIntrinsics, CameraExtrinsics *cameraExtrinsics) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetLocalTrackingSpaceRecenterCount(int *recenterCount) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetSystemHmd3DofModeEnabled(bool *enabled) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_Media_SetAvailableQueueIndexVulkan(uint queueIndexVk) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetTiledMultiResDynamic(bool *isDynamic) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_SetTiledMultiResDynamic(bool isDynamic) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_SetExternalCameraProperties(char *cameraName, CameraIntrinsics *cameraIntrinsics, CameraExtrinsics *cameraExtrinsics) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_SetClientColorDesc(ColorSpace colorSpace) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetHmdColorDesc(ColorSpace *colorSpace) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_Media_EncodeMrcFrameWithPoseTime(intptr_t rawBuffer, intptr_t audioDataPtr, int audioDataLen, int audioChannels, double timestamp, double poseTime, int *outSyncId) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_Media_EncodeMrcFrameDualTexturesWithPoseTime(intptr_t backgroundTextureHandle, intptr_t foregroundTextureHandle, intptr_t audioData, int audioDataLen, int audioChannels, double timestamp, double poseTime, int *outSyncId) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_Media_SetHeadsetControllerPose(Posef headsetPose, Posef leftControllerPose, Posef rightControllerPose) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_Media_EnumerateCameraAnchorHandles(int *anchorCount, intptr_t *CameraAnchorHandle) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_Media_GetCurrentCameraAnchorHandle(intptr_t *anchorHandle) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_Media_GetCameraAnchorName(intptr_t anchorHandle, char *cameraName) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_Media_GetCameraAnchorHandle(intptr_t anchorName, intptr_t *anchorHandle) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_Media_GetCameraAnchorType(intptr_t anchorHandle, CameraAnchorType *anchorType) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_Media_CreateCustomCameraAnchor(intptr_t anchorName, intptr_t *anchorHandle) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_Media_DestroyCustomCameraAnchor(intptr_t anchorHandle) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_Media_GetCustomCameraAnchorPose(intptr_t anchorHandle, Posef *pose) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_Media_SetCustomCameraAnchorPose(intptr_t anchorHandle, Posef pose) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_Media_GetCameraMinMaxDistance(intptr_t anchorHandle, double *minDistance, double *maxDistance) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_Media_SetCameraMinMaxDistance(intptr_t anchorHandle, double minDistance, double maxDistance) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_Media_SetPlatformInitialized() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetSkeleton2(SkeletonType skeletonType, Skeleton2Internal *skeleton) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_PollEvent(EventDataBuffer *eventDataBuffer) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetNativeXrApiType(XrApi *xrApi) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetNativeOpenXRHandles(uint64_t *xrInstance, uint64_t *xrSession) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_PollEvent2(EventType *eventType, intptr_t *eventData) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_Media_GetPlatformCameraMode(PlatformCameraMode *platformCameraMode) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_Media_SetPlatformCameraMode(PlatformCameraMode platformCameraMode) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_SetEyeFovPremultipliedAlphaMode(bool enabled) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetEyeFovPremultipliedAlphaMode(bool *enabled) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_SetKeyboardOverlayUV(Vector2f uv) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_InitializeInsightPassthrough() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_ShutdownInsightPassthrough() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
bool ovrp_GetInsightPassthroughInitialized() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_SetInsightPassthroughStyle(int layerId, InsightPassthroughStyle style) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_CreateInsightTriangleMesh(int layerId, intptr_t vertices, int vertexCount, intptr_t triangles, int triangleCount, unsigned long *meshHandle) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_DestroyInsightTriangleMesh(unsigned long meshHandle) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_AddInsightPassthroughSurfaceGeometry(int layerId, unsigned long meshHandle, Matrix4x4 T_world_model, unsigned long *geometryInstanceHandle) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_DestroyInsightPassthroughGeometryInstance(unsigned long geometryInstanceHandle) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_UpdateInsightPassthroughGeometryTransform(unsigned long geometryInstanceHandle, Matrix4x4 T_world_model) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_LocateSpace(Posef *location, uint64_t *space, TrackingOrigin trackingOrigin) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_KtxLoadFromMemory(intptr_t *data, uint length, intptr_t *texture) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_KtxTextureWidth(intptr_t texture, uint *width) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_KtxTextureHeight(intptr_t texture, uint *height) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_KtxTranscode(intptr_t texture, uint format) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_KtxGetTextureData(intptr_t texture, intptr_t data, uint bufferSize) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_KtxTextureSize(intptr_t texture, uint *size) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_KtxDestroy(intptr_t texture) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_DestroySpace(uint64_t *space) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetInsightPassthroughInitializationState() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_Media_IsCastingToRemoteClient(bool *isCasting) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_LoadRenderModel(uint64_t modelKey, uint bufferInputCapacity, uint *bufferCountOutput, intptr_t buffer) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetRenderModelPaths(uint index, intptr_t path) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetRenderModelProperties(char *path, RenderModelPropertiesInternal *properties) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_SetInsightPassthroughKeyboardHandsIntensity(int layerId, InsightPassthroughKeyboardHandsIntensity intensity) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_StartKeyboardTracking(uint64_t trackedKeyboardId) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_StopKeyboardTracking() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetSystemKeyboardDescription(TrackedKeyboardQueryFlags keyboardQueryFlags, KeyboardDescription *keyboardDescription) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetKeyboardState(Step stepId, int frameIndex, KeyboardState *keyboardState) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetNodePoseStateImmediate(Node nodeId, PoseStatef *nodePoseState) {
    __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called! But not implemented!", __func__);
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_SetLogCallback2(LogCallback2DelegateType logCallback) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_IsInsightPassthroughSupported(bool *supported) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
void ovrp_UnityOpenXR_SetClientVersion(int majorVersion, int minorVersion, int patchVersion) {
    return;
}
intptr_t ovrp_UnityOpenXR_HookGetInstanceProcAddr(intptr_t func) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_UnityOpenXR_OnInstanceCreate(uint64_t xrInstance) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
void ovrp_UnityOpenXR_OnInstanceDestroy(uint64_t xrInstance) {
    return;
}
void ovrp_UnityOpenXR_OnSessionCreate(uint64_t xrSession) {
    return;
}
void ovrp_UnityOpenXR_OnAppSpaceChange(uint64_t xrSpace) {
    return;
}
void ovrp_UnityOpenXR_OnSessionStateChange(int oldState, int newState) {
    return;
}
void ovrp_UnityOpenXR_OnSessionBegin(uint64_t xrSession) {
    return;
}
void ovrp_UnityOpenXR_OnSessionEnd(uint64_t xrSession) {
    return;
}
void ovrp_UnityOpenXR_OnSessionExiting(uint64_t xrSession) {
    return;
}
void ovrp_UnityOpenXR_OnSessionDestroy(uint64_t xrSession) {
    return;
}
Result ovrp_SetSuggestedCpuPerformanceLevel(ProcessorPerformanceLevel perfLevel) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetSuggestedCpuPerformanceLevel(ProcessorPerformanceLevel *perfLevel) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_SetSuggestedGpuPerformanceLevel(ProcessorPerformanceLevel perfLevel) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetSuggestedGpuPerformanceLevel(ProcessorPerformanceLevel *perfLevel) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_CreateSpatialAnchor(SpatialAnchorCreateInfo *createInfo, uint64_t *requestId) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_SetSpaceComponentStatus(uint64_t *space, SpaceComponentType componentType, bool enable, double timeout, uint64_t *requestId) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetSpaceComponentStatus(uint64_t *space, SpaceComponentType componentType, bool *enabled, bool *changePending) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_EnumerateSpaceSupportedComponents(uint64_t *space, uint componentTypesCapacityInput, uint *componentTypesCountOutput, SpaceComponentType *componentTypes) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_SaveSpace(uint64_t *space, SpaceStorageLocation location, SpaceStoragePersistenceMode mode, uint64_t *requestId) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_QuerySpaces(SpaceQueryInfo *queryInfo, uint64_t *requestId) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_RetrieveSpaceQueryResults(uint64_t *requestId, uint32_t resultCapacityInput, uint32_t *resultCountOutput, intptr_t results) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_EraseSpace(uint64_t *space, SpaceStorageLocation location, uint64_t *requestId) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetSpaceContainer(uint64_t *space, SpaceContainerInternal *containerInternal) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetSpaceBoundingBox2D(uint64_t *space, Rectf *rect) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetSpaceBoundingBox3D(uint64_t *space, Boundsf *bounds) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetSpaceSemanticLabels(uint64_t *space, SpaceSemanticLabelInternal *labelsInternal) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetSpaceRoomLayout(uint64_t *space, RoomLayoutInternal *roomLayoutInternal) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetSpaceBoundary2D(uint64_t *space, PolygonalBoundary2DInternal *boundaryInternal) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_RequestSceneCapture(SceneCaptureRequestInternal *request, uint64_t *requestId) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetSpaceUuid(uint64_t *space, Guid *uuid) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}


Result ovrp_CreateVirtualKeyboard(VirtualKeyboardCreateInfo createInfo) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}


Result ovrp_DestroyVirtualKeyboard() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}


Result ovrp_SendVirtualKeyboardInput(VirtualKeyboardInputInfo inputInfo, Posef *interactorRootPose) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}


Result ovrp_ChangeVirtualKeyboardTextContext(char *textContext) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}


Result ovrp_CreateVirtualKeyboardSpace(VirtualKeyboardSpaceCreateInfo createInfo, uint64_t *keyboardSpace) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}


Result ovrp_SuggestVirtualKeyboardLocation(VirtualKeyboardLocationInfo locationInfo) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}


Result ovrp_GetVirtualKeyboardScale(float *location) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}


Result ovrp_GetVirtualKeyboardSound(VirtualKeyboardSoundInternal *sound) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}


Result ovrp_GetVirtualKeyboardSwipeTrailState(VirtualKeyboardSwipeTrailState *swipeTrailState) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}

Result ovrp_GetRenderModelProperties2(char *path, RenderModelFlags flags, RenderModelPropertiesInternal *properties) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetNodePoseStateAtTime(double time, Node nodeId, PoseStatef *nodePoseState) {
    __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called! But not implemented!", __func__);
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetPassthroughCapabilityFlags(PassthroughCapabilityFlags *capabilityFlags) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetFoveationEyeTrackedSupported(bool *foveationSupported) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetFoveationEyeTracked(bool *isEyeTrackedFoveation) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_SetFoveationEyeTracked(bool isEyeTrackedFoveation) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_StartFaceTracking() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_StopFaceTracking() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_StartBodyTracking() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_StopBodyTracking() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_StartEyeTracking() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_StopEyeTracking() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetEyeTrackingSupported(bool *eyeTrackingSupported) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetFaceTrackingSupported(bool *faceTrackingSupported) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetBodyTrackingEnabled(bool *value) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetBodyTrackingSupported(bool *value) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetBodyState(Step stepId, int frameIndex, BodyStateInternal *bodyState) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetFaceTrackingEnabled(bool *faceTrackingEnabled) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetFaceState(Step stepId, int frameIndex, FaceStateInternal *faceState) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetEyeTrackingEnabled(bool *eyeTrackingEnabled) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetEyeGazesState(Step stepId, int frameIndex, EyeGazesStateInternal *eyeGazesState) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetControllerState5(uint controllerMask, ControllerState5 *controllerState) {
    ControllerState state = getControllerState(controllerMask);
    *controllerState = *((ControllerState5*)&state);
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_SetControllerLocalizedVibration(Controller controllerMask, HapticsLocation hapticsLocationMask, float frequency, float amplitude) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetLocalDimmingSupported(bool *localDimmingSupported) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_SetLocalDimming(bool localDimmingMode) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetLocalDimming(bool *localDimmingMode) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetCurrentInteractionProfile(Hand hand, InteractionProfile *interactionProfile) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_SetControllerHapticsAmplitudeEnvelope(
        Controller controllerMask,
        HapticsAmplitudeEnvelopeVibration hapticsVibration) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_SetControllerHapticsPcm(
        Controller controllerMask,
        HapticsPcmVibration hapticsVibration) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetControllerSampleRateHz(Controller controller, float *sampleRateHz) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
//NEW
Result ovrp_ShareSpaces(uint64_t *spaces, uint32_t numSpaces, unsigned long* userHandles, uint32_t numUsers, uint64_t *requestId) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_SaveSpaceList(uint64_t *spaces, uint32_t numSpaces, SpaceStorageLocation location, uint64_t *requestId) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetSpaceUserId(uint64_t *spaceUserHandle, uint64_t *spaceUserId) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_CreateSpaceUser(uint64_t *spaceUserId, uint64_t *spaceUserHandle) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_DestroySpaceUser(uint64_t *userHandle) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_LocateSpace2(SpaceLocationf *location, uint64_t *space, TrackingOrigin trackingOrigin) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_DeclareUser(uint64_t *userId, uint64_t *userHandle) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetSpaceTriangleMesh(uint64_t *space, TriangleMeshInternal *triangleMeshInternal) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetControllerState6(uint controllerMask, ControllerState6 *controllerState) {
    ControllerState state = getControllerState(controllerMask);
    *controllerState = *((ControllerState6*)&state);
    return 0;
}
Result ovrp_GetVirtualKeyboardModelAnimationStates(VirtualKeyboardModelAnimationStatesInternal *animationStates) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetVirtualKeyboardDirtyTextures(VirtualKeyboardTextureIdsInternal *textureIds) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetVirtualKeyboardTextureData(uint64_t textureId, VirtualKeyboardTextureData *textureData) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_SetVirtualKeyboardModelVisibility(VirtualKeyboardModelVisibility *visibility) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_CreatePassthroughColorLut(PassthroughColorLutChannels channels, uint32_t resolution, PassthroughColorLutData data, unsigned long *colorLut) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_DestroyPassthroughColorLut(unsigned long colorLut) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_UpdatePassthroughColorLut(unsigned long colorLut, PassthroughColorLutData data) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_SetInsightPassthroughStyle2(int layerId, InsightPassthroughStyle2 *style) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetLayerRecommendedResolution(int layerId, Sizei *recommendedDimensions) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetEyeLayerRecommendedResolution(Sizei *recommendedDimensions) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_QplMarkerStart(int markerId, int instanceKey, long timestampMs) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_QplMarkerEnd(int markerId, QplResultType resultTypeId, int instanceKey, long timestampMs) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_QplMarkerPoint(int markerId, char *name, int instanceKey, long timestampMs) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_QplMarkerPointCached(int markerId, int nameHandle, int instanceKey, long timestampMs) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_QplMarkerAnnotation(int markerId, char *annotationKey, char *annotationValue, int instanceKey) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_QplCreateMarkerHandle(char *name, int *nameHandle) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_QplDestroyMarkerHandle(int nameHandle) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_OnEditorShutdown() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetPassthroughCapabilities(PassthroughCapabilities *capabilityFlags) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_SetControllerDrivenHandPoses(bool controllerDrivenHandPoses) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_IsControllerDrivenHandPosesEnabled(bool *enabled) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_AreHandPosesGeneratedByControllerData(Step stepId, Node nodeId, bool *isGeneratedByControllerData) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_SetMultimodalHandsControllersSupported(bool supported) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_IsMultimodalHandsControllersSupported(bool *supported) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetCurrentDetachedInteractionProfile(Hand hand, InteractionProfile *interactionProfile) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetControllerIsInHand(Step stepId, Node nodeId, bool *isInHand) {
    *isInHand = false;
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetPassthroughPreferences(PassthroughPreferences *preferences) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_SetEyeBufferSharpenType(LayerSharpenType sharpenType) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_SetControllerDrivenHandPosesAreNatural(bool controllerDrivenHandPosesAreNatural) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_AreControllerDrivenHandPosesNatural(bool *natural) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_SetSimultaneousHandsAndControllersEnabled(bool enabled) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetFaceState2(Step stepId, int frameIndex, FaceState2Internal *faceState) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_StartFaceTracking2(FaceTrackingDataSource *requestedDataSources, uint requestedDataSourcesCount) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_StopFaceTracking2() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetFaceTracking2Enabled(bool *faceTracking2Enabled) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetFaceTracking2Supported(bool *faceTracking2Enabled) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_RequestBodyTrackingFidelity(BodyTrackingFidelity2 fidelity) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_SuggestBodyTrackingCalibrationOverride(BodyTrackingCalibrationInfo calibrationInfo) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_ResetBodyTrackingCalibration() {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetBodyState4(Step stepId, int frameIndex, BodyState4Internal *bodyState) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_GetSkeleton3(SkeletonType skeletonType, Skeleton3Internal *skeleton) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_StartBodyTracking2(BodyJointSet jointSet) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_QplSetConsent(bool consent) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_SetWideMotionModeHandPoses(bool wideMotionModeHandPoses) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_IsSetWideMotionModeHandPosesEnabled(bool *enabled) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_SetDeveloperTelemetryConsent(bool consent) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_QplMarkerAnnotationVariant(int markerId, char *annotationKey, QplVariant *annotationValue, int instanceKey) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_QplMarkerPointData(int markerId, char *name, QplAnnotation *annotations, int annotationCount, int instanceKey, long timestampMs) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_DiscoverSpaces(SpaceDiscoveryInfo *info, uint64_t *requestId) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_RetrieveSpaceDiscoveryResults(uint64_t requestId, SpaceDiscoveryResults *results) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_SaveSpaces(uint32_t spaceCount, uint64_t *spaces, uint64_t *requestId) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}
Result ovrp_EraseSpaces(uint32_t spaceCount, uint64_t *spaces, uint32_t uuidCount, Guid *uuids, uint64_t *requestId) {
    #if VERBOSE
        __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__);
    #endif
    return 0;
}