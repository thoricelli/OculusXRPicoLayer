#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <time.h>
#include <math.h>
#include <android/log.h>

#include "OVRPlugin.h"
#include "OculusXRPlugin.h"

//PXR
#include "/include/PxrPlugin.h"
#include "/include/PxrInput.h"
#include "/include/PxrPlatform.h"
#include "/include/PxrPlatformLoader.h"

#include "/include/Globals.h"
#include "/src/PxrUnityPluginLoader.c"
#include "/src/PxrToOculusMapper.c"
#include "/src/Logger.c"

/* LEGACY (TODO) */
bool ovrp_PreInitialize() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 1;
}
bool ovrp_Initialize(RenderAPIType apiType, intptr_t platformArgs) {
    LogFunction(IMPLEMENTED, NORMAL, __func__);
    
    Pxr_SetGraphicOption(PXR_OPENGL_ES);
    return Pxr_Initialize();
}
bool ovrp_Shutdown() {
    LogFunction(IMPLEMENTED, NORMAL, __func__);
    
    return Pxr_Shutdown();
}
bool ovrp_SetupDistortionWindow() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
bool ovrp_DestroyDistortionWindow() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
bool ovrp_RecreateEyeTexture(Eye eyeId, int stage, void* device, int height, int width, int samples, bool isSRGB, void* result) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
bool ovrp_SetEyeTexture(Eye eyeId, intptr_t texture) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
bool ovrp_Update(int frameIndex) {
    LogFunction(NON_IMPLEMENTED, FREQUENT, __func__);
    
    return Pxr_WaitFrame();
}
bool ovrp_BeginFrame(int frameIndex) {
    LogFunction(NON_IMPLEMENTED, FREQUENT, __func__);
    
    return Pxr_BeginFrame();
}
bool ovrp_EndEye(Eye eye) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
bool ovrp_EndFrame(int frameIndex) {
    LogFunction(IMPLEMENTED, FREQUENT, __func__);
    
    return Pxr_EndFrame();
}
bool ovrp_RecenterPose() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
/* END */

//NON-LEGACY
void UnityPluginLoad(void *unityInterfaces) {
    LogFunction(NON_IMPLEMENTED, FREQUENT, __func__);
    //Crashes the game...
    /*
    Pxr_UnityPluginLoad(unityInterfaces);*/
}
Sizei ovrp_GetEyeTextureSize(Eye eyeId) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    Sizei sizeiDummy;
    return sizeiDummy;
}
bool ovrp_SetOverlayQuad2(bool onTop, bool headLocked, intptr_t texture, intptr_t device, Posef pose, Vector3f scale) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
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
    LogFunction(IMPLEMENTED, NORMAL, __func__);

    return GetNodePose(nodeId);
}

bool ovrp_SetControllerVibration(uint controllerMask, float frequency, float amplitude) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Posef ovrp_GetNodeVelocity(Node nodeId) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    Posef posefDummy;
    return posefDummy;
}
Posef ovrp_GetNodeAcceleration(Node nodeId) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    Posef posefDummy;
    return posefDummy;
}
TrackingOrigin ovrp_GetTrackingOriginType() {
    LogFunction(IMPLEMENTED, NORMAL, __func__);

    PxrTrackingOrigin pxrTrackingOriginDummy;
    //Doesn't actually use the argument?
    return (TrackingOrigin)Pxr_GetTrackingOrigin(&pxrTrackingOriginDummy);
}
bool ovrp_SetTrackingOriginType(TrackingOrigin originType) {
    LogFunction(IMPLEMENTED, NORMAL, __func__);
    return Pxr_SetTrackingOrigin((PxrTrackingOrigin) originType);
}
Posef ovrp_GetTrackingCalibratedOrigin() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    Posef posefDummy;
    return posefDummy;
}
bool ovrp_RecenterTrackingOrigin(uint flags) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
bool ovrp_GetInitialized() {
    LogFunction(IMPLEMENTED, NORMAL, __func__);

    return Pxr_IsInitialized();
}
intptr_t ovrp_GetVersion() {
    LogFunction(IMPLEMENTED, NORMAL, __func__);

    return ((intptr_t)OVRP_VERSION);
}
intptr_t ovrp_GetNativeSDKVersion() {
    LogFunction(IMPLEMENTED, NORMAL, __func__);

    return ((intptr_t)OVRP_VERSION);
}
intptr_t ovrp_GetAudioOutId() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
intptr_t ovrp_GetAudioInId() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
float ovrp_GetEyeTextureScale() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
bool ovrp_SetEyeTextureScale(float value) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
bool ovrp_GetTrackingOrientationSupported() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
bool ovrp_GetTrackingOrientationEnabled() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
bool ovrp_SetTrackingOrientationEnabled(bool value) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
bool ovrp_GetTrackingPositionSupported() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
bool ovrp_GetTrackingPositionEnabled() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
bool ovrp_SetTrackingPositionEnabled(bool value) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
bool ovrp_GetNodePresent(Node nodeId) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 1;
}
bool ovrp_GetNodeOrientationTracked(Node nodeId) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 1;
}
bool ovrp_GetNodePositionTracked(Node nodeId) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 1;
}
Frustumf ovrp_GetNodeFrustum(Node nodeId) {
    LogFunction(IMPLEMENTED, NORMAL, __func__);
    
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
    LogFunction(IMPLEMENTED, NORMAL, __func__);

    return getControllerState(controllerMask);
}

// Deprecated. Replaced by ovrp_GetSuggestedCpuPerformanceLevel
int ovrp_GetSystemCpuLevel() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
//Deprecated. Replaced by ovrp_SetSuggestedCpuPerformanceLevel
bool ovrp_SetSystemCpuLevel(int value) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
//Deprecated. Replaced by ovrp_GetSuggestedGpuPerformanceLevel
int ovrp_GetSystemGpuLevel() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
//Deprecated. Replaced by ovrp_SetSuggestedGpuPerformanceLevel
bool ovrp_SetSystemGpuLevel(int value) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
bool ovrp_GetSystemPowerSavingMode() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
float ovrp_GetSystemDisplayFrequency() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
int ovrp_GetSystemVSyncCount() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
float ovrp_GetSystemVolume() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
BatteryStatus ovrp_GetSystemBatteryStatus() {
    LogFunction(IMPLEMENTED, NORMAL, __func__);

    return Full;
}
float ovrp_GetSystemBatteryLevel() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
float ovrp_GetSystemBatteryTemperature() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
intptr_t ovrp_GetSystemProductName() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
bool ovrp_ShowSystemUI(PlatformUI ui) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
bool ovrp_GetAppMonoscopic() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
bool ovrp_SetAppMonoscopic(bool value) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
bool ovrp_GetAppHasVrFocus() {
    LogFunction(IMPLEMENTED, NORMAL, __func__);

    return 1;
}
bool ovrp_GetAppShouldQuit() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
bool ovrp_GetAppShouldRecenter() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
intptr_t ovrp_GetAppLatencyTimings() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
bool ovrp_GetUserPresent() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 1;
}
float ovrp_GetUserIPD() {
    LogFunction(IMPLEMENTED, NORMAL, __func__);

    return Pxr_GetIPD();
}
bool ovrp_SetUserIPD(float value) {
    //Maybe later, need to test if this doesn't set it to dangerous levels.
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
float ovrp_GetUserEyeDepth() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
bool ovrp_SetUserEyeDepth(float value) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
float ovrp_GetUserEyeHeight() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
bool ovrp_SetUserEyeHeight(float value) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
bool ovrp_SetSystemVSyncCount(int vsyncCount) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
bool ovrpi_SetTrackingCalibratedOrigin() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
bool ovrp_GetEyeOcclusionMeshEnabled() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
bool ovrp_SetEyeOcclusionMeshEnabled(bool value) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
bool ovrp_GetSystemHeadphonesPresent() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
SystemRegion ovrp_GetSystemRegion() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
bool ovrp_GetTrackingIPDEnabled() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

    return false;
    //return Pvr_GetTrackingIPDEnabled();
}
bool ovrp_SetTrackingIPDEnabled(bool value) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

    return false;
    //return Pvr_SetTrackingIPDEnabled(value);
}
HapticsDesc ovrp_GetControllerHapticsDesc(uint controllerMask) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    HapticsDesc hapticsDescDummy;
    return hapticsDescDummy;
}
HapticsState ovrp_GetControllerHapticsState(uint controllerMask) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    HapticsState hapticsStateDummy;
    return hapticsStateDummy;
}
bool ovrp_SetControllerHaptics(uint controllerMask, HapticsBuffer hapticsBuffer) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
bool ovrp_SetOverlayQuad3(uint flags, intptr_t textureLeft, intptr_t textureRight, intptr_t device, Posef pose, Vector3f scale, int layerIndex) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
float ovrp_GetEyeRecommendedResolutionScale() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
float ovrp_GetAppCpuStartToGpuEndTime() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
int ovrp_GetSystemRecommendedMSAALevel() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
bool ovrp_GetAppChromaticCorrection() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
bool ovrp_SetAppChromaticCorrection(bool value) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
bool ovrp_GetBoundaryConfigured() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
//Deprecated. This function will not be supported in OpenXR
BoundaryTestResult ovrp_TestBoundaryNode(Node nodeId, BoundaryType boundaryType) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

    BoundaryTestResult boundaryTestResultDummy;
    return boundaryTestResultDummy;
}
//Deprecated. This function will not be supported in OpenXR
BoundaryTestResult ovrp_TestBoundaryPoint(Vector3f point, BoundaryType boundaryType) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

    BoundaryTestResult boundaryTestResultDummy;
    return boundaryTestResultDummy;
}
BoundaryGeometry ovrp_GetBoundaryGeometry(BoundaryType boundaryType) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    BoundaryGeometry boundaryGeometryDummy;
    return boundaryGeometryDummy;
}
Vector3f ovrp_GetBoundaryDimensions(BoundaryType boundaryType) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    Vector3f vector3FDummy;
    return vector3FDummy;
}
//Deprecated. This function will not be supported in OpenXR
bool ovrp_GetBoundaryVisible() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
//Deprecated. This function will not be supported in OpenXR
bool ovrp_SetBoundaryVisible(bool value) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
bool ovrp_Update2(int stateId, int frameIndex, double predictionSeconds) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Posef ovrp_GetNodePose2(int stateId, Node nodeId) {
    LogFunction(IMPLEMENTED, NORMAL, __func__);
    //TODO: StateId?
    return GetNodePose(nodeId);
}
Posef ovrp_GetNodeVelocity2(int stateId, Node nodeId) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    Posef posefDummy;
    return posefDummy;
}
Posef ovrp_GetNodeAcceleration2(int stateId, Node nodeId) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    Posef posefDummy;
    return posefDummy;
}
enum SystemHeadset ovrp_GetSystemHeadsetType() {
    LogFunction(IMPLEMENTED, NORMAL, __func__);

    return Meta_Quest_3;
}
Controller ovrp_GetActiveController() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return All;
}
Controller ovrp_GetConnectedControllers() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return All;
}
bool ovrp_GetBoundaryGeometry2(BoundaryType boundaryType, intptr_t points, int *pointsCount) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
AppPerfStats ovrp_GetAppPerfStats() {
    LogFunction(IMPLEMENTED, NORMAL, __func__);

    AppPerfStats appPerfStatsDummy;
    return appPerfStatsDummy;
}
bool ovrp_ResetAppPerfStats() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
bool ovrp_SetDesiredEyeTextureFormat(EyeTextureFormat value) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
EyeTextureFormat ovrp_GetDesiredEyeTextureFormat() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
float ovrp_GetAppFramerate() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
PoseStatef ovrp_GetNodePoseState(Step stepId, Node nodeId) {
    LogFunction(IMPLEMENTED, NORMAL, __func__);

    return GetNodePoseState(nodeId);
}
ControllerState2 ovrp_GetControllerState2(uint controllerMask) {
    LogFunction(IMPLEMENTED, NORMAL, __func__);

    ControllerState state = getControllerState(controllerMask);
    ControllerState2 base = *((ControllerState2*)&state);
    //Add more.
    return base;
}
Result ovrp_InitializeMixedReality() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_ShutdownMixedReality() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
bool ovrp_GetMixedRealityInitialized() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_UpdateExternalCamera() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetExternalCameraCount(int *cameraCount) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetExternalCameraName(int cameraId, char *cameraName) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetExternalCameraIntrinsics(int cameraId, CameraIntrinsics *cameraIntrinsics) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetExternalCameraExtrinsics(int cameraId, CameraExtrinsics *cameraExtrinsics) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}

//LAYERS
Result ovrp_CalculateLayerDesc(OverlayShape shape, LayerLayout layout, Sizei *textureSize,
                               int mipLevels, int sampleCount, EyeTextureFormat format, int layerFlags, LayerDesc *layerDesc) {
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
    return 1;
}

char layersCreated[15];
char layersCreated2[15];
Result ovrp_EnqueueSetupLayer(LayerDesc *desc, int *layerId) {
    LogFunction(IMPLEMENTED, NORMAL, __func__);

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
    return 0;
}
Result ovrp_EnqueueDestroyLayer(int *layerId) {
    LogFunction(IMPLEMENTED, NORMAL, __func__);

    layersCreated[*layerId] = false;
    layersCreated2[*layerId] = false;
    return Pxr_DestroyLayer((*layerId) + 1);
}
Result ovrp_GetLayerTextureStageCount(int layerId, uint32_t *layerTextureStageCount) {
    LogFunction(IMPLEMENTED, NORMAL, __func__);

    return Pxr_GetLayerImageCount(layerId, PXR_EYE_BOTH, layerTextureStageCount);
}
Result ovrp_GetLayerTexturePtr(int layerId, int stage, Eye eyeId, uint64_t *textureHandle) {
    LogFunction(IMPLEMENTED, NORMAL, __func__);

    return Pxr_GetLayerImage(layerId, *((PxrEyeType*)&eyeId), stage, textureHandle);
}
Result ovrp_EnqueueSubmitLayer(uint flags, intptr_t textureLeft, intptr_t textureRight, int layerId, int frameIndex, Posef *pose, Vector3f *scale, int layerIndex) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
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
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetNodeFrustum2(Node nodeId, Frustumf2 *nodeFrustum) {
    LogFunction(IMPLEMENTED, NORMAL, __func__);

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
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_UpdateCameraDevices() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
bool ovrp_IsCameraDeviceAvailable(CameraDevice cameraDevice) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_SetCameraDevicePreferredColorFrameSize(CameraDevice cameraDevice, Sizei preferredColorFrameSize) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_OpenCameraDevice(CameraDevice cameraDevice) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_CloseCameraDevice(CameraDevice cameraDevice) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
bool ovrp_HasCameraDeviceOpened(CameraDevice cameraDevice) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
bool ovrp_IsCameraDeviceColorFrameAvailable(CameraDevice cameraDevice) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetCameraDeviceColorFrameSize(CameraDevice cameraDevice, Sizei *colorFrameSize) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetCameraDeviceColorFrameBgraPixels(CameraDevice cameraDevice, intptr_t *colorFrameBgraPixels, int *colorFrameRowPitch) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetControllerState4(uint controllerMask, ControllerState4 *controllerState) {
    LogFunction(IMPLEMENTED, NORMAL, __func__);

    ControllerState state = getControllerState(controllerMask);
    *controllerState = *((ControllerState4*)&state);
    return 0;
}

// UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN
Result ovrp_GetExternalCameraPose(CameraDevice camera, Posef *cameraPose) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_ConvertPoseToCameraSpace(CameraDevice camera, Posef *trackingSpacePose, Posef *cameraSpacePose) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetCameraDeviceIntrinsicsParameters(CameraDevice camera, bool *supportIntrinsics, CameraDeviceIntrinsicsParameters *intrinsicsParameters) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_DoesCameraDeviceSupportDepth(CameraDevice camera, bool *supportDepth) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetCameraDeviceDepthSensingMode(CameraDevice camera, CameraDeviceDepthSensingMode *depthSensoringMode) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_SetCameraDeviceDepthSensingMode(CameraDevice camera, CameraDeviceDepthSensingMode depthSensoringMode) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetCameraDevicePreferredDepthQuality(CameraDevice camera, CameraDeviceDepthQuality *depthQuality) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_SetCameraDevicePreferredDepthQuality(CameraDevice camera, CameraDeviceDepthQuality depthQuality) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_IsCameraDeviceDepthFrameAvailable(CameraDevice camera, bool *available) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetCameraDeviceDepthFrameSize(CameraDevice camera, Sizei *depthFrameSize) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetCameraDeviceDepthFramePixels(CameraDevice cameraDevice, intptr_t *depthFramePixels, int *depthFrameRowPitch) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetCameraDeviceDepthConfidencePixels(CameraDevice cameraDevice, intptr_t *depthConfidencePixels, int *depthConfidenceRowPitch) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
//END

Result ovrp_SetHandNodePoseStateLatency(double latencyInSeconds) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetHandNodePoseStateLatency(double *latencyInSeconds) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetAppHasInputFocus(bool *appHasInputFocus) {
    *appHasInputFocus = 1;
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetTiledMultiResSupported(bool *foveationSupported) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetTiledMultiResLevel(FixedFoveatedRenderingLevel *level) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_SetTiledMultiResLevel(FixedFoveatedRenderingLevel level) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetGPUUtilSupported(bool *gpuUtilSupported) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetGPUUtilLevel(float *gpuUtil) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetSystemDisplayFrequency2(float *systemDisplayFrequency) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetSystemDisplayAvailableFrequencies(int *systemDisplayAvailableFrequencies, int *numFrequencies) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    

    /**numFrequencies = 1;
    int frequencies[1] = {72};
    systemDisplayAvailableFrequencies = *((int **)&frequencies);*/

    return 0;//Pxr_GetDisplayRefreshRatesAvailable(numFrequencies, &systemDisplayAvailableFrequencies);
}
Result ovrp_SetSystemDisplayFrequency(float requestedFrequency) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetAppAsymmetricFov(bool *useAsymmetricFov) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetDominantHand(Handedness *dominantHand) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_SendEvent(char *name, char *param) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}

Result ovrp_EnqueueSetupLayer2(LayerDesc *desc, int compositionDepth, int *layerId) {
    LogFunction(IMPLEMENTED, NORMAL, __func__);

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
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_SetHeadPoseModifier(Quatf *relativeRotation, Vector3f *relativeTranslation) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetHeadPoseModifier(Quatf *relativeRotation, Vector3f *relativeTranslation) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetNodePoseStateRaw(Step stepId, int frameIndex, Node nodeId, PoseStatef *nodePoseState) {
    __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called! But not implemented!", __func__);
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetCurrentTrackingTransformPose(Posef *trackingTransformPose) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetTrackingTransformRawPose(Posef *trackingTransformRawPose) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_SendEvent2(char *name, char *param, char *source) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_IsPerfMetricsSupported(PerfMetrics perfMetrics, bool *isSupported) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetPerfMetricsFloat(PerfMetrics perfMetrics, float *value) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetPerfMetricsInt(PerfMetrics perfMetrics, int *value) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetTimeInSeconds(double *value) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_SetColorScaleAndOffset(Vector4 colorScale, Vector4 colorOffset, bool applyToAllLayers) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_AddCustomMetadata(char *name, char *param) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_EnqueueSubmitLayer2(uint flags, intptr_t textureLeft, intptr_t textureRight, int layerId, int frameIndex, Posef *pose, Vector3f *scale, int layerIndex, bool overrideTextureRectMatrix, TextureRectMatrixf *textureRectMatrix, bool overridePerLayerColorScaleAndOffset, Vector4 *colorScale, Vector4 *colorOffset) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetTrackingTransformRelativePose(Posef *trackingTransformRelativePose, TrackingOrigin trackingOrigin) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_Media_Initialize() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_Media_Shutdown() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_Media_GetInitialized(bool *initialized) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    //*initialized = 1;
    return 0;
}
Result ovrp_Media_Update() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_Media_GetMrcActivationMode(MrcActivationMode *activationMode) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_Media_SetMrcActivationMode(MrcActivationMode activationMode) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_Media_IsMrcEnabled(bool *mrcEnabled) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_Media_IsMrcActivated(bool *mrcActivated) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_Media_UseMrcDebugCamera(bool *useMrcDebugCamera) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_Media_SetMrcInputVideoBufferType(InputVideoBufferType inputVideoBufferType) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_Media_GetMrcInputVideoBufferType(InputVideoBufferType *inputVideoBufferType) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_Media_SetMrcFrameSize(int frameWidth, int frameHeight) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_Media_GetMrcFrameSize(int *frameWidth, int *frameHeight) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_Media_SetMrcAudioSampleRate(int sampleRate) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    

    return 0;
}
Result ovrp_Media_GetMrcAudioSampleRate(int *sampleRate) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_Media_SetMrcFrameImageFlipped(bool flipped) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_Media_GetMrcFrameImageFlipped(bool *flipped) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_Media_EncodeMrcFrame(intptr_t rawBuffer, intptr_t audioDataPtr, int audioDataLen, int audioChannels, double timestamp, int *outSyncId) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_Media_EncodeMrcFrameWithDualTextures(intptr_t backgroundTextureHandle, intptr_t foregroundTextureHandle, intptr_t audioData, int audioDataLen, int audioChannels, double timestamp, int *outSyncId) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_Media_SyncMrcFrame(int syncId) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
//Result ovrp_GetExternalCameraCalibrationRawPose(int cameraId, Posef *rawPose)
Result ovrp_SetDeveloperMode(bool active) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetNodeOrientationValid(Node nodeId, bool *nodeOrientationValid) {
    
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetNodePositionValid(Node nodeId, bool *nodePositionValid) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    //*nodePositionValid = 1;
    return 0;
}
Result ovrp_GetAdaptiveGpuPerformanceScale2(float *adaptiveGpuPerformanceScale) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetHandTrackingEnabled(bool *handTrackingEnabled) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

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
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__); //Not done yet

    GetPXRHandStateForOVR(hand, handState);
    
    return 0;
}
Result ovrp_GetSkeleton(SkeletonType skeletonType, Skeleton *skeleton) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetMesh(MeshType meshType, intptr_t meshPtr) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_OverrideExternalCameraFov(int cameraId, bool useOverriddenFov, Fovf *fov) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetUseOverriddenExternalCameraFov(int cameraId, bool *useOverriddenFov) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_OverrideExternalCameraStaticPose(int cameraId, bool useOverriddenPose, Posef *poseInStageOrigin) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetUseOverriddenExternalCameraStaticPose(int cameraId, bool *useOverriddenStaticPose) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_ResetDefaultExternalCamera() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_SetDefaultExternalCamera(char *cameraName, CameraIntrinsics *cameraIntrinsics, CameraExtrinsics *cameraExtrinsics) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetLocalTrackingSpaceRecenterCount(int *recenterCount) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetSystemHmd3DofModeEnabled(bool *enabled) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_Media_SetAvailableQueueIndexVulkan(uint queueIndexVk) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetTiledMultiResDynamic(bool *isDynamic) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_SetTiledMultiResDynamic(bool isDynamic) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_SetExternalCameraProperties(char *cameraName, CameraIntrinsics *cameraIntrinsics, CameraExtrinsics *cameraExtrinsics) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_SetClientColorDesc(ColorSpace colorSpace) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetHmdColorDesc(ColorSpace *colorSpace) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_Media_EncodeMrcFrameWithPoseTime(intptr_t rawBuffer, intptr_t audioDataPtr, int audioDataLen, int audioChannels, double timestamp, double poseTime, int *outSyncId) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_Media_EncodeMrcFrameDualTexturesWithPoseTime(intptr_t backgroundTextureHandle, intptr_t foregroundTextureHandle, intptr_t audioData, int audioDataLen, int audioChannels, double timestamp, double poseTime, int *outSyncId) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_Media_SetHeadsetControllerPose(Posef headsetPose, Posef leftControllerPose, Posef rightControllerPose) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_Media_EnumerateCameraAnchorHandles(int *anchorCount, intptr_t *CameraAnchorHandle) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_Media_GetCurrentCameraAnchorHandle(intptr_t *anchorHandle) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_Media_GetCameraAnchorName(intptr_t anchorHandle, char *cameraName) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_Media_GetCameraAnchorHandle(intptr_t anchorName, intptr_t *anchorHandle) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_Media_GetCameraAnchorType(intptr_t anchorHandle, CameraAnchorType *anchorType) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_Media_CreateCustomCameraAnchor(intptr_t anchorName, intptr_t *anchorHandle) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_Media_DestroyCustomCameraAnchor(intptr_t anchorHandle) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_Media_GetCustomCameraAnchorPose(intptr_t anchorHandle, Posef *pose) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_Media_SetCustomCameraAnchorPose(intptr_t anchorHandle, Posef pose) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_Media_GetCameraMinMaxDistance(intptr_t anchorHandle, double *minDistance, double *maxDistance) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_Media_SetCameraMinMaxDistance(intptr_t anchorHandle, double minDistance, double maxDistance) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_Media_SetPlatformInitialized() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetSkeleton2(SkeletonType skeletonType, Skeleton2Internal *skeleton) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_PollEvent(EventDataBuffer *eventDataBuffer) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetNativeXrApiType(XrApi *xrApi) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetNativeOpenXRHandles(uint64_t *xrInstance, uint64_t *xrSession) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_PollEvent2(EventType *eventType, intptr_t *eventData) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_Media_GetPlatformCameraMode(PlatformCameraMode *platformCameraMode) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_Media_SetPlatformCameraMode(PlatformCameraMode platformCameraMode) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_SetEyeFovPremultipliedAlphaMode(bool enabled) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetEyeFovPremultipliedAlphaMode(bool *enabled) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_SetKeyboardOverlayUV(Vector2f uv) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_InitializeInsightPassthrough() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_ShutdownInsightPassthrough() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
bool ovrp_GetInsightPassthroughInitialized() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_SetInsightPassthroughStyle(int layerId, InsightPassthroughStyle style) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_CreateInsightTriangleMesh(int layerId, intptr_t vertices, int vertexCount, intptr_t triangles, int triangleCount, unsigned long *meshHandle) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_DestroyInsightTriangleMesh(unsigned long meshHandle) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_AddInsightPassthroughSurfaceGeometry(int layerId, unsigned long meshHandle, Matrix4x4 T_world_model, unsigned long *geometryInstanceHandle) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_DestroyInsightPassthroughGeometryInstance(unsigned long geometryInstanceHandle) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_UpdateInsightPassthroughGeometryTransform(unsigned long geometryInstanceHandle, Matrix4x4 T_world_model) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_LocateSpace(Posef *location, uint64_t *space, TrackingOrigin trackingOrigin) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_KtxLoadFromMemory(intptr_t *data, uint length, intptr_t *texture) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_KtxTextureWidth(intptr_t texture, uint *width) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_KtxTextureHeight(intptr_t texture, uint *height) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_KtxTranscode(intptr_t texture, uint format) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_KtxGetTextureData(intptr_t texture, intptr_t data, uint bufferSize) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_KtxTextureSize(intptr_t texture, uint *size) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_KtxDestroy(intptr_t texture) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_DestroySpace(uint64_t *space) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetInsightPassthroughInitializationState() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_Media_IsCastingToRemoteClient(bool *isCasting) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_LoadRenderModel(uint64_t modelKey, uint bufferInputCapacity, uint *bufferCountOutput, intptr_t buffer) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetRenderModelPaths(uint index, intptr_t path) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetRenderModelProperties(char *path, RenderModelPropertiesInternal *properties) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_SetInsightPassthroughKeyboardHandsIntensity(int layerId, InsightPassthroughKeyboardHandsIntensity intensity) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_StartKeyboardTracking(uint64_t trackedKeyboardId) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_StopKeyboardTracking() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetSystemKeyboardDescription(TrackedKeyboardQueryFlags keyboardQueryFlags, KeyboardDescription *keyboardDescription) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetKeyboardState(Step stepId, int frameIndex, KeyboardState *keyboardState) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetNodePoseStateImmediate(Node nodeId, PoseStatef *nodePoseState) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_SetLogCallback2(LogCallback2DelegateType logCallback) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_IsInsightPassthroughSupported(bool *supported) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
void ovrp_UnityOpenXR_SetClientVersion(int majorVersion, int minorVersion, int patchVersion) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

    return;
}
intptr_t ovrp_UnityOpenXR_HookGetInstanceProcAddr(intptr_t func) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_UnityOpenXR_OnInstanceCreate(uint64_t xrInstance) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
void ovrp_UnityOpenXR_OnInstanceDestroy(uint64_t xrInstance) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

    return;
}
void ovrp_UnityOpenXR_OnSessionCreate(uint64_t xrSession) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

    return;
}
void ovrp_UnityOpenXR_OnAppSpaceChange(uint64_t xrSpace) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

    return;
}
void ovrp_UnityOpenXR_OnSessionStateChange(int oldState, int newState) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

    return;
}
void ovrp_UnityOpenXR_OnSessionBegin(uint64_t xrSession) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

    return;
}
void ovrp_UnityOpenXR_OnSessionEnd(uint64_t xrSession) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

    return;
}
void ovrp_UnityOpenXR_OnSessionExiting(uint64_t xrSession) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

    return;
}
void ovrp_UnityOpenXR_OnSessionDestroy(uint64_t xrSession) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);

    return;
}
Result ovrp_SetSuggestedCpuPerformanceLevel(ProcessorPerformanceLevel perfLevel) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetSuggestedCpuPerformanceLevel(ProcessorPerformanceLevel *perfLevel) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_SetSuggestedGpuPerformanceLevel(ProcessorPerformanceLevel perfLevel) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetSuggestedGpuPerformanceLevel(ProcessorPerformanceLevel *perfLevel) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_CreateSpatialAnchor(SpatialAnchorCreateInfo *createInfo, uint64_t *requestId) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_SetSpaceComponentStatus(uint64_t *space, SpaceComponentType componentType, bool enable, double timeout, uint64_t *requestId) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetSpaceComponentStatus(uint64_t *space, SpaceComponentType componentType, bool *enabled, bool *changePending) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_EnumerateSpaceSupportedComponents(uint64_t *space, uint componentTypesCapacityInput, uint *componentTypesCountOutput, SpaceComponentType *componentTypes) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_SaveSpace(uint64_t *space, SpaceStorageLocation location, SpaceStoragePersistenceMode mode, uint64_t *requestId) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_QuerySpaces(SpaceQueryInfo *queryInfo, uint64_t *requestId) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_RetrieveSpaceQueryResults(uint64_t *requestId, uint32_t resultCapacityInput, uint32_t *resultCountOutput, intptr_t results) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_EraseSpace(uint64_t *space, SpaceStorageLocation location, uint64_t *requestId) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetSpaceContainer(uint64_t *space, SpaceContainerInternal *containerInternal) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetSpaceBoundingBox2D(uint64_t *space, Rectf *rect) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetSpaceBoundingBox3D(uint64_t *space, Boundsf *bounds) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetSpaceSemanticLabels(uint64_t *space, SpaceSemanticLabelInternal *labelsInternal) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetSpaceRoomLayout(uint64_t *space, RoomLayoutInternal *roomLayoutInternal) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetSpaceBoundary2D(uint64_t *space, PolygonalBoundary2DInternal *boundaryInternal) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_RequestSceneCapture(SceneCaptureRequestInternal *request, uint64_t *requestId) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetSpaceUuid(uint64_t *space, Guid *uuid) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}


Result ovrp_CreateVirtualKeyboard(VirtualKeyboardCreateInfo createInfo) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}


Result ovrp_DestroyVirtualKeyboard() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}


Result ovrp_SendVirtualKeyboardInput(VirtualKeyboardInputInfo inputInfo, Posef *interactorRootPose) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}


Result ovrp_ChangeVirtualKeyboardTextContext(char *textContext) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}


Result ovrp_CreateVirtualKeyboardSpace(VirtualKeyboardSpaceCreateInfo createInfo, uint64_t *keyboardSpace) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}


Result ovrp_SuggestVirtualKeyboardLocation(VirtualKeyboardLocationInfo locationInfo) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}


Result ovrp_GetVirtualKeyboardScale(float *location) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}


Result ovrp_GetVirtualKeyboardSound(VirtualKeyboardSoundInternal *sound) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}


Result ovrp_GetVirtualKeyboardSwipeTrailState(VirtualKeyboardSwipeTrailState *swipeTrailState) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}

Result ovrp_GetRenderModelProperties2(char *path, RenderModelFlags flags, RenderModelPropertiesInternal *properties) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetNodePoseStateAtTime(double time, Node nodeId, PoseStatef *nodePoseState) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetPassthroughCapabilityFlags(PassthroughCapabilityFlags *capabilityFlags) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetFoveationEyeTrackedSupported(bool *foveationSupported) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetFoveationEyeTracked(bool *isEyeTrackedFoveation) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_SetFoveationEyeTracked(bool isEyeTrackedFoveation) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_StartFaceTracking() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_StopFaceTracking() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_StartBodyTracking() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_StopBodyTracking() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_StartEyeTracking() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_StopEyeTracking() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetEyeTrackingSupported(bool *eyeTrackingSupported) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetFaceTrackingSupported(bool *faceTrackingSupported) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetBodyTrackingEnabled(bool *value) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetBodyTrackingSupported(bool *value) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetBodyState(Step stepId, int frameIndex, BodyStateInternal *bodyState) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetFaceTrackingEnabled(bool *faceTrackingEnabled) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetFaceState(Step stepId, int frameIndex, FaceStateInternal *faceState) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetEyeTrackingEnabled(bool *eyeTrackingEnabled) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetEyeGazesState(Step stepId, int frameIndex, EyeGazesStateInternal *eyeGazesState) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetControllerState5(uint controllerMask, ControllerState5 *controllerState) {
    LogFunction(IMPLEMENTED, NORMAL, __func__);

    ControllerState state = getControllerState(controllerMask);
    *controllerState = *((ControllerState5*)&state);
    return 0;
}
Result ovrp_SetControllerLocalizedVibration(Controller controllerMask, HapticsLocation hapticsLocationMask, float frequency, float amplitude) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetLocalDimmingSupported(bool *localDimmingSupported) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_SetLocalDimming(bool localDimmingMode) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetLocalDimming(bool *localDimmingMode) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetCurrentInteractionProfile(Hand hand, InteractionProfile *interactionProfile) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_SetControllerHapticsAmplitudeEnvelope(
        Controller controllerMask,
        HapticsAmplitudeEnvelopeVibration hapticsVibration) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_SetControllerHapticsPcm(
        Controller controllerMask,
        HapticsPcmVibration hapticsVibration) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetControllerSampleRateHz(Controller controller, float *sampleRateHz) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
//NEW
Result ovrp_ShareSpaces(uint64_t *spaces, uint32_t numSpaces, unsigned long* userHandles, uint32_t numUsers, uint64_t *requestId) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_SaveSpaceList(uint64_t *spaces, uint32_t numSpaces, SpaceStorageLocation location, uint64_t *requestId) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetSpaceUserId(uint64_t *spaceUserHandle, uint64_t *spaceUserId) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_CreateSpaceUser(uint64_t *spaceUserId, uint64_t *spaceUserHandle) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_DestroySpaceUser(uint64_t *userHandle) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_LocateSpace2(SpaceLocationf *location, uint64_t *space, TrackingOrigin trackingOrigin) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_DeclareUser(uint64_t *userId, uint64_t *userHandle) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetSpaceTriangleMesh(uint64_t *space, TriangleMeshInternal *triangleMeshInternal) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetControllerState6(uint controllerMask, ControllerState6 *controllerState) {
    LogFunction(IMPLEMENTED, NORMAL, __func__);

    ControllerState state = getControllerState(controllerMask);
    *controllerState = *((ControllerState6*)&state);
    return 0;
}
Result ovrp_GetVirtualKeyboardModelAnimationStates(VirtualKeyboardModelAnimationStatesInternal *animationStates) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetVirtualKeyboardDirtyTextures(VirtualKeyboardTextureIdsInternal *textureIds) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetVirtualKeyboardTextureData(uint64_t textureId, VirtualKeyboardTextureData *textureData) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_SetVirtualKeyboardModelVisibility(VirtualKeyboardModelVisibility *visibility) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_CreatePassthroughColorLut(PassthroughColorLutChannels channels, uint32_t resolution, PassthroughColorLutData data, unsigned long *colorLut) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_DestroyPassthroughColorLut(unsigned long colorLut) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_UpdatePassthroughColorLut(unsigned long colorLut, PassthroughColorLutData data) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_SetInsightPassthroughStyle2(int layerId, InsightPassthroughStyle2 *style) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetLayerRecommendedResolution(int layerId, Sizei *recommendedDimensions) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetEyeLayerRecommendedResolution(Sizei *recommendedDimensions) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_QplMarkerStart(int markerId, int instanceKey, long timestampMs) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_QplMarkerEnd(int markerId, QplResultType resultTypeId, int instanceKey, long timestampMs) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_QplMarkerPoint(int markerId, char *name, int instanceKey, long timestampMs) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_QplMarkerPointCached(int markerId, int nameHandle, int instanceKey, long timestampMs) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_QplMarkerAnnotation(int markerId, char *annotationKey, char *annotationValue, int instanceKey) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_QplCreateMarkerHandle(char *name, int *nameHandle) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_QplDestroyMarkerHandle(int nameHandle) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_OnEditorShutdown() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetPassthroughCapabilities(PassthroughCapabilities *capabilityFlags) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_SetControllerDrivenHandPoses(bool controllerDrivenHandPoses) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_IsControllerDrivenHandPosesEnabled(bool *enabled) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_AreHandPosesGeneratedByControllerData(Step stepId, Node nodeId, bool *isGeneratedByControllerData) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_SetMultimodalHandsControllersSupported(bool supported) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_IsMultimodalHandsControllersSupported(bool *supported) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetCurrentDetachedInteractionProfile(Hand hand, InteractionProfile *interactionProfile) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetControllerIsInHand(Step stepId, Node nodeId, bool *isInHand) {
    *isInHand = false;
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetPassthroughPreferences(PassthroughPreferences *preferences) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_SetEyeBufferSharpenType(LayerSharpenType sharpenType) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_SetControllerDrivenHandPosesAreNatural(bool controllerDrivenHandPosesAreNatural) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_AreControllerDrivenHandPosesNatural(bool *natural) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_SetSimultaneousHandsAndControllersEnabled(bool enabled) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetFaceState2(Step stepId, int frameIndex, FaceState2Internal *faceState) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_StartFaceTracking2(FaceTrackingDataSource *requestedDataSources, uint requestedDataSourcesCount) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_StopFaceTracking2() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetFaceTracking2Enabled(bool *faceTracking2Enabled) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetFaceTracking2Supported(bool *faceTracking2Enabled) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_RequestBodyTrackingFidelity(BodyTrackingFidelity2 fidelity) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_SuggestBodyTrackingCalibrationOverride(BodyTrackingCalibrationInfo calibrationInfo) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_ResetBodyTrackingCalibration() {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetBodyState4(Step stepId, int frameIndex, BodyState4Internal *bodyState) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_GetSkeleton3(SkeletonType skeletonType, Skeleton3Internal *skeleton) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_StartBodyTracking2(BodyJointSet jointSet) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_QplSetConsent(bool consent) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_SetWideMotionModeHandPoses(bool wideMotionModeHandPoses) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_IsSetWideMotionModeHandPosesEnabled(bool *enabled) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_SetDeveloperTelemetryConsent(bool consent) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_QplMarkerAnnotationVariant(int markerId, char *annotationKey, QplVariant *annotationValue, int instanceKey) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_QplMarkerPointData(int markerId, char *name, QplAnnotation *annotations, int annotationCount, int instanceKey, long timestampMs) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_DiscoverSpaces(SpaceDiscoveryInfo *info, uint64_t *requestId) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_RetrieveSpaceDiscoveryResults(uint64_t requestId, SpaceDiscoveryResults *results) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_SaveSpaces(uint32_t spaceCount, uint64_t *spaces, uint64_t *requestId) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}
Result ovrp_EraseSpaces(uint32_t spaceCount, uint64_t *spaces, uint32_t uuidCount, Guid *uuids, uint64_t *requestId) {
    LogFunction(NON_IMPLEMENTED, NORMAL, __func__);
    
    return 0;
}