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
#include "/src/PxrUnityPluginLoader.c"

/* LEGACY (TODO) */
bool ovrp_PreInitialize() {
    return 0;
}
bool ovrp_Initialize(/*RenderAPIType*/int apiType, intptr_t platformArgs) {
    return 0;
}
bool ovrp_Shutdown() {
    return 0;
}
bool ovrp_SetupDistortionWindow() {
    return 0;
}
bool ovrp_DestroyDistortionWindow() {
    return 0;
}
bool ovrp_RecreateEyeTexture(Eye eyeId, int stage, void* device, int height, int width, int samples, bool isSRGB, void* result) {
    return 0;
}
bool ovrp_SetEyeTexture(Eye eyeId, intptr_t texture) {
    return 0;
}
bool ovrp_Update(int frameIndex) {
    return 0;
}
bool ovrp_BeginFrame(int frameIndex) {
    return Pxr_BeginFrame();
}
bool ovrp_EndEye(Eye eye) {
    return 0;
}
bool ovrp_EndFrame(int frameIndex) {
    return Pxr_EndFrame();
}
bool ovrp_RecenterPose() {
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
    Sizei sizeiDummy;
    return sizeiDummy;
}
bool ovrp_SetOverlayQuad2(bool onTop, bool headLocked, intptr_t texture, intptr_t device, Posef pose, Vector3f scale) {
    return 0;
}

Posef getPosefForController(int deviceID) {
    PxrControllerTracking tracking;
    float *headSensorData;

    Pxr_GetHeadSensorData(headSensorData);
    Pxr_GetControllerTrackingState(deviceID, 0, headSensorData, &tracking);

    Posef poseControllerState = {
            .Orientation = *((Quatf*)&tracking.localControllerPose.pose.orientation),
            .Position = *((Vector3f*)&tracking.localControllerPose.pose.position),
    };
    return poseControllerState;
}

Posef ovrp_GetNodePose(Node nodeId) {
    PxrSensorState2 sensorState;

    int sensorFrameIndex;
    double predictedDisplayTimeMS;

    Posef poseStateDummy;

    switch (nodeId) {
        case EyeCenter:
        case Head:
            Pxr_GetPredictedDisplayTime(&predictedDisplayTimeMS);

            Pxr_GetPredictedMainSensorState2(predictedDisplayTimeMS, &sensorState, &sensorFrameIndex);

            Posef poseHeadState = {
                    .Orientation = *((Quatf*)&sensorState.pose.orientation),
                    .Position = *((Vector3f*)&sensorState.pose.position),
            };

            return poseHeadState;
            break;
        case HandLeft:
        case HandRight:
            return getPosefForController(nodeId - 3);
        default:
            return poseStateDummy;
            break;
    }
}

bool ovrp_SetControllerVibration(uint controllerMask, float frequency, float amplitude) {
    return 0;
}
Posef ovrp_GetNodeVelocity(Node nodeId) {
    Posef posefDummy;
    
    return posefDummy;
}
Posef ovrp_GetNodeAcceleration(Node nodeId) {
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
    return 0;
}
intptr_t ovrp_GetAudioInId() {
    return 0;
}
float ovrp_GetEyeTextureScale() {
    return 0;
}
bool ovrp_SetEyeTextureScale(float value) {
    return 0;
}
bool ovrp_GetTrackingOrientationSupported() {
    return 0;
}
bool ovrp_GetTrackingOrientationEnabled() {
    return 0;
}
bool ovrp_SetTrackingOrientationEnabled(bool value) {
    return 0;
}
bool ovrp_GetTrackingPositionSupported() {
    return 0;
}
bool ovrp_GetTrackingPositionEnabled() {
    return 0;
}
bool ovrp_SetTrackingPositionEnabled(bool value) {
    return 0;
}
bool ovrp_GetNodePresent(Node nodeId) {
    
    return 1;
}
bool ovrp_GetNodeOrientationTracked(Node nodeId) {
    
    return 1;
}
bool ovrp_GetNodePositionTracked(Node nodeId) {
    
    return 1;
}
Frustumf ovrp_GetNodeFrustum(Node nodeId) {
    Frustumf frustumfDummy;
    return frustumfDummy;
}

int getConnectedControllers() {
    int connectedControllers = 2;

    //Check controller status
    connectedControllers -= Pxr_GetControllerConnectStatus(PXR_CONTROLLER_LEFT);
    connectedControllers -= Pxr_GetControllerConnectStatus(PXR_CONTROLLER_RIGHT);
    return connectedControllers;
}

uint getButtonsFromState(PxrControllerInputState pxrState, uint start) {
    uint state = 0;
    state |= pxrState.AXValue * Button_One;
    state |= pxrState.BYValue * Button_Two;
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
    return 0;
}
//Deprecated. Replaced by ovrp_SetSuggestedCpuPerformanceLevel
bool ovrp_SetSystemCpuLevel(int value) {
    return 0;
}
//Deprecated. Replaced by ovrp_GetSuggestedGpuPerformanceLevel
int ovrp_GetSystemGpuLevel() {
    return 0;
}
//Deprecated. Replaced by ovrp_SetSuggestedGpuPerformanceLevel
bool ovrp_SetSystemGpuLevel(int value) {
    return 0;
}
bool ovrp_GetSystemPowerSavingMode() {
    return 0;
}
float ovrp_GetSystemDisplayFrequency() {
    return 0;
}
int ovrp_GetSystemVSyncCount() {
    return 0;
}
float ovrp_GetSystemVolume() {
    return 0;
}
BatteryStatus ovrp_GetSystemBatteryStatus() {
    return Full;
}
float ovrp_GetSystemBatteryLevel() {
    return 0;
}
float ovrp_GetSystemBatteryTemperature() {
    return 0;
}
intptr_t ovrp_GetSystemProductName() {
    return 0;
}
bool ovrp_ShowSystemUI(PlatformUI ui) {
    return 0;
}
bool ovrp_GetAppMonoscopic() {
    return 0;
}
bool ovrp_SetAppMonoscopic(bool value) {
    return 0;
}
bool ovrp_GetAppHasVrFocus() {
    return 0;
}
bool ovrp_GetAppShouldQuit() {
    return 0;
}
bool ovrp_GetAppShouldRecenter() {
    return 0;
}
intptr_t ovrp_GetAppLatencyTimings() {
    return 0;
}
bool ovrp_GetUserPresent() {
    return 0;
}
float ovrp_GetUserIPD() {
    return Pxr_GetIPD();
}
bool ovrp_SetUserIPD(float value) {
    //Maybe later, need to test if this doesn't set it to dangerous levels.
    return 0;
}
float ovrp_GetUserEyeDepth() {
    return 0;
}
bool ovrp_SetUserEyeDepth(float value) {
    return 0;
}
float ovrp_GetUserEyeHeight() {
    return 0;
}
bool ovrp_SetUserEyeHeight(float value) {
    return 0;
}
bool ovrp_SetSystemVSyncCount(int vsyncCount) {
    return 0;
}
bool ovrpi_SetTrackingCalibratedOrigin() {
    return 0;
}
bool ovrp_GetEyeOcclusionMeshEnabled() {
    return 0;
}
bool ovrp_SetEyeOcclusionMeshEnabled(bool value) {
    return 0;
}
bool ovrp_GetSystemHeadphonesPresent() {
    return 0;
}
SystemRegion ovrp_GetSystemRegion() {
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
    HapticsDesc hapticsDescDummy;
    return hapticsDescDummy;
}
HapticsState ovrp_GetControllerHapticsState(uint controllerMask) {
    HapticsState hapticsStateDummy;
    return hapticsStateDummy;
}
bool ovrp_SetControllerHaptics(uint controllerMask, HapticsBuffer hapticsBuffer) {
    return 0;
}
bool ovrp_SetOverlayQuad3(uint flags, intptr_t textureLeft, intptr_t textureRight, intptr_t device, Posef pose, Vector3f scale, int layerIndex) {
    return 0;
}
float ovrp_GetEyeRecommendedResolutionScale() {
    return 0;
}
float ovrp_GetAppCpuStartToGpuEndTime() {
    return 0;
}
int ovrp_GetSystemRecommendedMSAALevel() {
    return 0;
}
bool ovrp_GetAppChromaticCorrection() {
    return 0;
}
bool ovrp_SetAppChromaticCorrection(bool value) {
    return 0;
}
bool ovrp_GetBoundaryConfigured() {
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
    BoundaryGeometry boundaryGeometryDummy;
    return boundaryGeometryDummy;
}
Vector3f ovrp_GetBoundaryDimensions(BoundaryType boundaryType) {
    Vector3f vector3FDummy;
    return vector3FDummy;
}
//Deprecated. This function will not be supported in OpenXR
bool ovrp_GetBoundaryVisible() {
    return 0;
}
//Deprecated. This function will not be supported in OpenXR
bool ovrp_SetBoundaryVisible(bool value) {
    return 0;
}
bool ovrp_Update2(int stateId, int frameIndex, double predictionSeconds) {
    return 0;
}
Posef ovrp_GetNodePose2(int stateId, Node nodeId) {
    Posef posefDummy;
    
    return posefDummy;
}
Posef ovrp_GetNodeVelocity2(int stateId, Node nodeId) {
    Posef posefDummy;
    
    return posefDummy;
}
Posef ovrp_GetNodeAcceleration2(int stateId, Node nodeId) {
    Posef posefDummy;
    
    return posefDummy;
}
enum SystemHeadset ovrp_GetSystemHeadsetType() {
    return Meta_Quest_3;
}
Controller ovrp_GetActiveController() {
    return All;
}
Controller ovrp_GetConnectedControllers() {
    return All;
}
bool ovrp_GetBoundaryGeometry2(BoundaryType boundaryType, intptr_t points, int *pointsCount) {
    return 0;
}
AppPerfStats ovrp_GetAppPerfStats() {
    AppPerfStats appPerfStatsDummy;
    return appPerfStatsDummy;
}
bool ovrp_ResetAppPerfStats() {
    return 0;
}
bool ovrp_SetDesiredEyeTextureFormat(EyeTextureFormat value) {
    return 0;
}
EyeTextureFormat ovrp_GetDesiredEyeTextureFormat() {
    return 0;
}
float ovrp_GetAppFramerate() {
    return 0;
}
PoseStatef ovrp_GetNodePoseState(Step stepId, Node nodeId) {
    /*__android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called! with params:"
                                                       "stepId: %d"
                                                       "nodeId: %d",
                                                       __func__,
                                                       stepId,
                                                       nodeId);*/
    PxrSensorState sensorState;
    int sensorFrameIndex;

    PoseStatef poseStatefDummy;

    switch (nodeId) {
        case EyeCenter:
        case Head:
            Pxr_GetPredictedMainSensorState(0, &sensorState, &sensorFrameIndex);

            PoseStatef poseHeadState = {
              .Velocity = *((Vector3f*)&sensorState.linearVelocity),
              .Acceleration = *((Vector3f*)&sensorState.linearAcceleration),
              .AngularVelocity = *((Vector3f*)&sensorState.angularVelocity),
              .AngularAcceleration = *((Vector3f*)&sensorState.angularAcceleration),
            };

            return poseHeadState;
            break;
        default:
            return poseStatefDummy;
            break;
    }
}
ControllerState2 ovrp_GetControllerState2(uint controllerMask) {

    

    PxrControllerInputState controllerRight;
    Pxr_GetControllerInputState(PXR_CONTROLLER_RIGHT, &controllerRight);

    ControllerState2 controllerState = {
            .ConnectedControllers = 1,
            //TODO
            .RIndexTrigger = controllerRight.triggerValue,
    };

    return controllerState;
}
Result ovrp_InitializeMixedReality() {
    return 0;
}
Result ovrp_ShutdownMixedReality() {
    return 0;
}
bool ovrp_GetMixedRealityInitialized() {
    return 0;
}
Result ovrp_UpdateExternalCamera() {
    return 0;
}
Result ovrp_GetExternalCameraCount(int *cameraCount) {
    return 0;
}
Result ovrp_GetExternalCameraName(int cameraId, char *cameraName) {
    return 0;
}
Result ovrp_GetExternalCameraIntrinsics(int cameraId, CameraIntrinsics *cameraIntrinsics) {
    return 0;
}
Result ovrp_GetExternalCameraExtrinsics(int cameraId, CameraExtrinsics *cameraExtrinsics) {
    return 0;
}
Result ovrp_CalculateLayerDesc(OverlayShape shape, LayerLayout layout, Sizei *textureSize,
                               int mipLevels, int sampleCount, EyeTextureFormat format, int layerFlags, LayerDesc *layerDesc) {
    return 0;
}
Result ovrp_EnqueueSetupLayer(LayerDesc *desc, intptr_t layerId) {
    return 0;
}
Result ovrp_EnqueueDestroyLayer(intptr_t layerId) {
    return 0;
}
Result ovrp_GetLayerTextureStageCount(int layerId, int *layerTextureStageCount) {
    return 0;
}
Result ovrp_GetLayerTexturePtr(int layerId, int stage, Eye eyeId, intptr_t *textureHandle) {
    return 0;
}
Result ovrp_EnqueueSubmitLayer(uint flags, intptr_t textureLeft, intptr_t textureRight, int layerId, int frameIndex, Posef *pose, Vector3f *scale, int layerIndex) {
    return 0;
}
Result ovrp_GetNodeFrustum2(Node nodeId, Frustumf2 *nodeFrustum) {
    
    return 0;
}
bool ovrp_GetEyeTextureArrayEnabled() {
    return 0;
}
Result ovrp_UpdateCameraDevices() {
    return 0;
}
bool ovrp_IsCameraDeviceAvailable(CameraDevice cameraDevice) {
    return 0;
}
Result ovrp_SetCameraDevicePreferredColorFrameSize(CameraDevice cameraDevice, Sizei preferredColorFrameSize) {
    return 0;
}
Result ovrp_OpenCameraDevice(CameraDevice cameraDevice) {
    return 0;
}
Result ovrp_CloseCameraDevice(CameraDevice cameraDevice) {
    return 0;
}
bool ovrp_HasCameraDeviceOpened(CameraDevice cameraDevice) {
    return 0;
}
bool ovrp_IsCameraDeviceColorFrameAvailable(CameraDevice cameraDevice) {
    return 0;
}
Result ovrp_GetCameraDeviceColorFrameSize(CameraDevice cameraDevice, Sizei *colorFrameSize) {
    return 0;
}
Result ovrp_GetCameraDeviceColorFrameBgraPixels(CameraDevice cameraDevice, intptr_t *colorFrameBgraPixels, int *colorFrameRowPitch) {
    return 0;
}
Result ovrp_GetControllerState4(uint controllerMask, ControllerState4 *controllerState) {
    
    return 0;
}

// UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN
Result ovrp_GetExternalCameraPose(CameraDevice camera, Posef *cameraPose) {
    return 0;
}
Result ovrp_ConvertPoseToCameraSpace(CameraDevice camera, Posef *trackingSpacePose, Posef *cameraSpacePose) {
    return 0;
}
Result ovrp_GetCameraDeviceIntrinsicsParameters(CameraDevice camera, bool *supportIntrinsics, CameraDeviceIntrinsicsParameters *intrinsicsParameters) {
    return 0;
}
Result ovrp_DoesCameraDeviceSupportDepth(CameraDevice camera, bool *supportDepth) {
    return 0;
}
Result ovrp_GetCameraDeviceDepthSensingMode(CameraDevice camera, CameraDeviceDepthSensingMode *depthSensoringMode) {
    return 0;
}
Result ovrp_SetCameraDeviceDepthSensingMode(CameraDevice camera, CameraDeviceDepthSensingMode depthSensoringMode) {
    return 0;
}
Result ovrp_GetCameraDevicePreferredDepthQuality(CameraDevice camera, CameraDeviceDepthQuality *depthQuality) {
    return 0;
}
Result ovrp_SetCameraDevicePreferredDepthQuality(CameraDevice camera, CameraDeviceDepthQuality depthQuality) {
    return 0;
}
Result ovrp_IsCameraDeviceDepthFrameAvailable(CameraDevice camera, bool *available) {
    return 0;
}
Result ovrp_GetCameraDeviceDepthFrameSize(CameraDevice camera, Sizei *depthFrameSize) {
    return 0;
}
Result ovrp_GetCameraDeviceDepthFramePixels(CameraDevice cameraDevice, intptr_t *depthFramePixels, int *depthFrameRowPitch) {
    return 0;
}
Result ovrp_GetCameraDeviceDepthConfidencePixels(CameraDevice cameraDevice, intptr_t *depthConfidencePixels, int *depthConfidenceRowPitch) {
    return 0;
}
//END

Result ovrp_SetHandNodePoseStateLatency(double latencyInSeconds) {
    return 0;
}
Result ovrp_GetHandNodePoseStateLatency(double *latencyInSeconds) {
    return 0;
}
Result ovrp_GetAppHasInputFocus(bool *appHasInputFocus) {
    return 0;
}
Result ovrp_GetTiledMultiResSupported(bool *foveationSupported) {
    return 0;
}
Result ovrp_GetTiledMultiResLevel(FixedFoveatedRenderingLevel *level) {
    return 0;
}
Result ovrp_SetTiledMultiResLevel(FixedFoveatedRenderingLevel level) {
    return 0;
}
Result ovrp_GetGPUUtilSupported(bool *gpuUtilSupported) {
    return 0;
}
Result ovrp_GetGPUUtilLevel(float *gpuUtil) {
    return 0;
}
Result ovrp_GetSystemDisplayFrequency2(float *systemDisplayFrequency) {
    return 0;
}
Result ovrp_GetSystemDisplayAvailableFrequencies(intptr_t systemDisplayAvailableFrequencies, int *numFrequencies) {
    return 0;
}
Result ovrp_SetSystemDisplayFrequency(float requestedFrequency) {
    return 0;
}
Result ovrp_GetAppAsymmetricFov(bool *useAsymmetricFov) {
    return 0;
}
Result ovrp_GetDominantHand(Handedness *dominantHand) {
    return 0;
}
Result ovrp_SendEvent(char *name, char *param) {
    return 0;
}
Result ovrp_EnqueueSetupLayer2(LayerDesc *desc, int compositionDepth, intptr_t layerId) {
    return 0;
}
Result ovrp_GetLayerAndroidSurfaceObject(int layerId, intptr_t *surfaceObject) {
    return 0;
}
Result ovrp_SetHeadPoseModifier(Quatf *relativeRotation, Vector3f *relativeTranslation) {
    return 0;
}
Result ovrp_GetHeadPoseModifier(Quatf *relativeRotation, Vector3f *relativeTranslation) {
    return 0;
}
Result ovrp_GetNodePoseStateRaw(Step stepId, int frameIndex, Node nodeId, PoseStatef *nodePoseState) {
    
    return 0;
}
Result ovrp_GetCurrentTrackingTransformPose(Posef *trackingTransformPose) {
    return 0;
}
Result ovrp_GetTrackingTransformRawPose(Posef *trackingTransformRawPose) {
    return 0;
}
Result ovrp_SendEvent2(char *name, char *param, char *source) {
    return 0;
}
Result ovrp_IsPerfMetricsSupported(PerfMetrics perfMetrics, bool *isSupported) {
    return 0;
}
Result ovrp_GetPerfMetricsFloat(PerfMetrics perfMetrics, float *value) {
    return 0;
}
Result ovrp_GetPerfMetricsInt(PerfMetrics perfMetrics, int *value) {
    return 0;
}
Result ovrp_GetTimeInSeconds(double *value) {
    return 0;
}
Result ovrp_SetColorScaleAndOffset(Vector4 colorScale, Vector4 colorOffset, bool applyToAllLayers) {
    return 0;
}
Result ovrp_AddCustomMetadata(char *name, char *param) {
    return 0;
}
Result ovrp_EnqueueSubmitLayer2(uint flags, intptr_t textureLeft, intptr_t textureRight, int layerId, int frameIndex, Posef *pose, Vector3f *scale, int layerIndex, bool overrideTextureRectMatrix, TextureRectMatrixf *textureRectMatrix, bool overridePerLayerColorScaleAndOffset, Vector4 *colorScale, Vector4 *colorOffset) {
    return 0;
}
Result ovrp_GetTrackingTransformRelativePose(Posef *trackingTransformRelativePose, TrackingOrigin trackingOrigin) {
    return 0;
}
Result ovrp_Media_Initialize() {
    return 0;
}
Result ovrp_Media_Shutdown() {
    return 0;
}
Result ovrp_Media_GetInitialized(bool *initialized) {
    return 0;
}
Result ovrp_Media_Update() {
    return 0;
}
Result ovrp_Media_GetMrcActivationMode(MrcActivationMode *activationMode) {
    return 0;
}
Result ovrp_Media_SetMrcActivationMode(MrcActivationMode activationMode) {
    return 0;
}
Result ovrp_Media_IsMrcEnabled(bool *mrcEnabled) {
    return 0;
}
Result ovrp_Media_IsMrcActivated(bool *mrcActivated) {
    return 0;
}
Result ovrp_Media_UseMrcDebugCamera(bool *useMrcDebugCamera) {
    return 0;
}
Result ovrp_Media_SetMrcInputVideoBufferType(InputVideoBufferType inputVideoBufferType) {
    return 0;
}
Result ovrp_Media_GetMrcInputVideoBufferType(InputVideoBufferType *inputVideoBufferType) {
    return 0;
}
Result ovrp_Media_SetMrcFrameSize(int frameWidth, int frameHeight) {
    return 0;
}
Result ovrp_Media_GetMrcFrameSize(int *frameWidth, int *frameHeight) {
    return 0;
}
Result ovrp_Media_SetMrcAudioSampleRate(int sampleRate) {
    return 0;
}
Result ovrp_Media_GetMrcAudioSampleRate(int *sampleRate) {
    return 0;
}
Result ovrp_Media_SetMrcFrameImageFlipped(bool flipped) {
    return 0;
}
Result ovrp_Media_GetMrcFrameImageFlipped(bool *flipped) {
    return 0;
}
Result ovrp_Media_EncodeMrcFrame(intptr_t rawBuffer, intptr_t audioDataPtr, int audioDataLen, int audioChannels, double timestamp, int *outSyncId) {
    return 0;
}
Result ovrp_Media_EncodeMrcFrameWithDualTextures(intptr_t backgroundTextureHandle, intptr_t foregroundTextureHandle, intptr_t audioData, int audioDataLen, int audioChannels, double timestamp, int *outSyncId) {
    return 0;
}
Result ovrp_Media_SyncMrcFrame(int syncId) {
    return 0;
}
//Result ovrp_GetExternalCameraCalibrationRawPose(int cameraId, Posef *rawPose)
Result ovrp_SetDeveloperMode(bool active) {
    return 0;
}
Result ovrp_GetNodeOrientationValid(Node nodeId, bool *nodeOrientationValid) {
    
    return 0;
}
Result ovrp_GetNodePositionValid(Node nodeId, bool *nodePositionValid) {
    
    return 0;
}
Result ovrp_GetAdaptiveGpuPerformanceScale2(float *adaptiveGpuPerformanceScale) {
    return 0;
}
Result ovrp_GetHandTrackingEnabled(bool *handTrackingEnabled) {
    return 0;
}
Result ovrp_GetHandState(Step stepId, Hand hand, HandStateInternal *handState) {
    return 0;
}
Result ovrp_GetSkeleton(SkeletonType skeletonType, Skeleton *skeleton) {
    return 0;
}
Result ovrp_GetMesh(MeshType meshType, intptr_t meshPtr) {
    return 0;
}
Result ovrp_OverrideExternalCameraFov(int cameraId, bool useOverriddenFov, Fovf *fov) {
    return 0;
}
Result ovrp_GetUseOverriddenExternalCameraFov(int cameraId, bool *useOverriddenFov) {
    return 0;
}
Result ovrp_OverrideExternalCameraStaticPose(int cameraId, bool useOverriddenPose, Posef *poseInStageOrigin) {
    return 0;
}
Result ovrp_GetUseOverriddenExternalCameraStaticPose(int cameraId, bool *useOverriddenStaticPose) {
    return 0;
}
Result ovrp_ResetDefaultExternalCamera() {
    return 0;
}
Result ovrp_SetDefaultExternalCamera(char *cameraName, CameraIntrinsics *cameraIntrinsics, CameraExtrinsics *cameraExtrinsics) {
    return 0;
}
Result ovrp_GetLocalTrackingSpaceRecenterCount(int *recenterCount) {
    return 0;
}
Result ovrp_GetSystemHmd3DofModeEnabled(bool *enabled) {
    return 0;
}
Result ovrp_Media_SetAvailableQueueIndexVulkan(uint queueIndexVk) {
    return 0;
}
Result ovrp_GetTiledMultiResDynamic(bool *isDynamic) {
    return 0;
}
Result ovrp_SetTiledMultiResDynamic(bool isDynamic) {
    return 0;
}
Result ovrp_SetExternalCameraProperties(char *cameraName, CameraIntrinsics *cameraIntrinsics, CameraExtrinsics *cameraExtrinsics) {
    return 0;
}
Result ovrp_SetClientColorDesc(ColorSpace colorSpace) {
    return 0;
}
Result ovrp_GetHmdColorDesc(ColorSpace *colorSpace) {
    return 0;
}
Result ovrp_Media_EncodeMrcFrameWithPoseTime(intptr_t rawBuffer, intptr_t audioDataPtr, int audioDataLen, int audioChannels, double timestamp, double poseTime, int *outSyncId) {
    return 0;
}
Result ovrp_Media_EncodeMrcFrameDualTexturesWithPoseTime(intptr_t backgroundTextureHandle, intptr_t foregroundTextureHandle, intptr_t audioData, int audioDataLen, int audioChannels, double timestamp, double poseTime, int *outSyncId) {
    return 0;
}
Result ovrp_Media_SetHeadsetControllerPose(Posef headsetPose, Posef leftControllerPose, Posef rightControllerPose) {
    return 0;
}
Result ovrp_Media_EnumerateCameraAnchorHandles(int *anchorCount, intptr_t *CameraAnchorHandle) {
    return 0;
}
Result ovrp_Media_GetCurrentCameraAnchorHandle(intptr_t *anchorHandle) {
    return 0;
}
Result ovrp_Media_GetCameraAnchorName(intptr_t anchorHandle, char *cameraName) {
    return 0;
}
Result ovrp_Media_GetCameraAnchorHandle(intptr_t anchorName, intptr_t *anchorHandle) {
    return 0;
}
Result ovrp_Media_GetCameraAnchorType(intptr_t anchorHandle, CameraAnchorType *anchorType) {
    return 0;
}
Result ovrp_Media_CreateCustomCameraAnchor(intptr_t anchorName, intptr_t *anchorHandle) {
    return 0;
}
Result ovrp_Media_DestroyCustomCameraAnchor(intptr_t anchorHandle) {
    return 0;
}
Result ovrp_Media_GetCustomCameraAnchorPose(intptr_t anchorHandle, Posef *pose) {
    return 0;
}
Result ovrp_Media_SetCustomCameraAnchorPose(intptr_t anchorHandle, Posef pose) {
    return 0;
}
Result ovrp_Media_GetCameraMinMaxDistance(intptr_t anchorHandle, double *minDistance, double *maxDistance) {
    return 0;
}
Result ovrp_Media_SetCameraMinMaxDistance(intptr_t anchorHandle, double minDistance, double maxDistance) {
    return 0;
}
Result ovrp_Media_SetPlatformInitialized() {
    return 0;
}
Result ovrp_GetSkeleton2(SkeletonType skeletonType, Skeleton2Internal *skeleton) {
    return 0;
}
Result ovrp_PollEvent(EventDataBuffer *eventDataBuffer) {
    return 0;
}
Result ovrp_GetNativeXrApiType(XrApi *xrApi) {
    return 0;
}
Result ovrp_GetNativeOpenXRHandles(uint64_t *xrInstance, uint64_t *xrSession) {
    return 0;
}
Result ovrp_PollEvent2(EventType *eventType, intptr_t *eventData) {
    return 0;
}
Result ovrp_Media_GetPlatformCameraMode(PlatformCameraMode *platformCameraMode) {
    return 0;
}
Result ovrp_Media_SetPlatformCameraMode(PlatformCameraMode platformCameraMode) {
    return 0;
}
Result ovrp_SetEyeFovPremultipliedAlphaMode(bool enabled) {
    return 0;
}
Result ovrp_GetEyeFovPremultipliedAlphaMode(bool *enabled) {
    return 0;
}
Result ovrp_SetKeyboardOverlayUV(Vector2f uv) {
    return 0;
}
Result ovrp_InitializeInsightPassthrough() {
    return 0;
}
Result ovrp_ShutdownInsightPassthrough() {
    return 0;
}
bool ovrp_GetInsightPassthroughInitialized() {
    return 0;
}
Result ovrp_SetInsightPassthroughStyle(int layerId, InsightPassthroughStyle style) {
    return 0;
}
Result ovrp_CreateInsightTriangleMesh(int layerId, intptr_t vertices, int vertexCount, intptr_t triangles, int triangleCount, unsigned long *meshHandle) {
    return 0;
}
Result ovrp_DestroyInsightTriangleMesh(unsigned long meshHandle) {
    return 0;
}
Result ovrp_AddInsightPassthroughSurfaceGeometry(int layerId, unsigned long meshHandle, Matrix4x4 T_world_model, unsigned long *geometryInstanceHandle) {
    return 0;
}
Result ovrp_DestroyInsightPassthroughGeometryInstance(unsigned long geometryInstanceHandle) {
    return 0;
}
Result ovrp_UpdateInsightPassthroughGeometryTransform(unsigned long geometryInstanceHandle, Matrix4x4 T_world_model) {
    return 0;
}
Result ovrp_LocateSpace(Posef *location, uint64_t *space, TrackingOrigin trackingOrigin) {
    return 0;
}
Result ovrp_KtxLoadFromMemory(intptr_t *data, uint length, intptr_t *texture) {
    return 0;
}
Result ovrp_KtxTextureWidth(intptr_t texture, uint *width) {
    return 0;
}
Result ovrp_KtxTextureHeight(intptr_t texture, uint *height) {
    return 0;
}
Result ovrp_KtxTranscode(intptr_t texture, uint format) {
    return 0;
}
Result ovrp_KtxGetTextureData(intptr_t texture, intptr_t data, uint bufferSize) {
    return 0;
}
Result ovrp_KtxTextureSize(intptr_t texture, uint *size) {
    return 0;
}
Result ovrp_KtxDestroy(intptr_t texture) {
    return 0;
}
Result ovrp_DestroySpace(uint64_t *space) {
    return 0;
}
Result ovrp_GetInsightPassthroughInitializationState() {
    return 0;
}
Result ovrp_Media_IsCastingToRemoteClient(bool *isCasting) {
    return 0;
}
Result ovrp_LoadRenderModel(uint64_t modelKey, uint bufferInputCapacity, uint *bufferCountOutput, intptr_t buffer) {
    return 0;
}
Result ovrp_GetRenderModelPaths(uint index, intptr_t path) {
    return 0;
}
Result ovrp_GetRenderModelProperties(char *path, RenderModelPropertiesInternal *properties) {
    return 0;
}
Result ovrp_SetInsightPassthroughKeyboardHandsIntensity(int layerId, InsightPassthroughKeyboardHandsIntensity intensity) {
    return 0;
}
Result ovrp_StartKeyboardTracking(uint64_t trackedKeyboardId) {
    return 0;
}
Result ovrp_StopKeyboardTracking() {
    return 0;
}
Result ovrp_GetSystemKeyboardDescription(TrackedKeyboardQueryFlags keyboardQueryFlags, KeyboardDescription *keyboardDescription) {
    return 0;
}
Result ovrp_GetKeyboardState(Step stepId, int frameIndex, KeyboardState *keyboardState) {
    return 0;
}
Result ovrp_GetNodePoseStateImmediate(Node nodeId, PoseStatef *nodePoseState) {
    
    return 0;
}
Result ovrp_SetLogCallback2(LogCallback2DelegateType logCallback) {
    return 0;
}
Result ovrp_IsInsightPassthroughSupported(bool *supported) {
    return 0;
}
void ovrp_UnityOpenXR_SetClientVersion(int majorVersion, int minorVersion, int patchVersion) {
    return;
}
intptr_t ovrp_UnityOpenXR_HookGetInstanceProcAddr(intptr_t func) {
    return 0;
}
Result ovrp_UnityOpenXR_OnInstanceCreate(uint64_t xrInstance) {
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
    return 0;
}
Result ovrp_GetSuggestedCpuPerformanceLevel(ProcessorPerformanceLevel *perfLevel) {
    return 0;
}
Result ovrp_SetSuggestedGpuPerformanceLevel(ProcessorPerformanceLevel perfLevel) {
    return 0;
}
Result ovrp_GetSuggestedGpuPerformanceLevel(ProcessorPerformanceLevel *perfLevel) {
    return 0;
}
Result ovrp_CreateSpatialAnchor(SpatialAnchorCreateInfo *createInfo, uint64_t *requestId) {
    return 0;
}
Result ovrp_SetSpaceComponentStatus(uint64_t *space, SpaceComponentType componentType, bool enable, double timeout, uint64_t *requestId) {
    return 0;
}
Result ovrp_GetSpaceComponentStatus(uint64_t *space, SpaceComponentType componentType, bool *enabled, bool *changePending) {
    return 0;
}
Result ovrp_EnumerateSpaceSupportedComponents(uint64_t *space, uint componentTypesCapacityInput, uint *componentTypesCountOutput, SpaceComponentType *componentTypes) {
    return 0;
}
Result ovrp_SaveSpace(uint64_t *space, SpaceStorageLocation location, SpaceStoragePersistenceMode mode, uint64_t *requestId) {
    return 0;
}
Result ovrp_QuerySpaces(SpaceQueryInfo *queryInfo, uint64_t *requestId) {
    return 0;
}
Result ovrp_RetrieveSpaceQueryResults(uint64_t *requestId, uint32_t resultCapacityInput, uint32_t *resultCountOutput, intptr_t results) {
    return 0;
}
Result ovrp_EraseSpace(uint64_t *space, SpaceStorageLocation location, uint64_t *requestId) {
    return 0;
}
Result ovrp_GetSpaceContainer(uint64_t *space, SpaceContainerInternal *containerInternal) {
    return 0;
}
Result ovrp_GetSpaceBoundingBox2D(uint64_t *space, Rectf *rect) {
    return 0;
}
Result ovrp_GetSpaceBoundingBox3D(uint64_t *space, Boundsf *bounds) {
    return 0;
}
Result ovrp_GetSpaceSemanticLabels(uint64_t *space, SpaceSemanticLabelInternal *labelsInternal) {
    return 0;
}
Result ovrp_GetSpaceRoomLayout(uint64_t *space, RoomLayoutInternal *roomLayoutInternal) {
    return 0;
}
Result ovrp_GetSpaceBoundary2D(uint64_t *space, PolygonalBoundary2DInternal *boundaryInternal) {
    return 0;
}
Result ovrp_RequestSceneCapture(SceneCaptureRequestInternal *request, uint64_t *requestId) {
    return 0;
}