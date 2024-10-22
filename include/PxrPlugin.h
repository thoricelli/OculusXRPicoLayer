﻿#ifndef PXR_API_H
#define PXR_API_H

#include "PxrTypes.h"

#if defined(__cplusplus)
extern "C" {
#endif

// Preinit
int Pxr_SetGraphicOption(PxrGraphicOption graphic);
int Pxr_SetPlatformOption(PxrPlatformOption platform);

// Init and shutdown
bool Pxr_IsInitialized();
int Pxr_SetInitializeData(PxrInitParamData* params);
int Pxr_Initialize();
int Pxr_Shutdown();

// Vulkan
int Pxr_GetDeviceExtensionsVk(const char** extensionNamesArray, uint32_t* extensionCount);
int Pxr_GetInstanceExtensionsVk(const char** extensionNamesArray, uint32_t* extensionCount);
int Pxr_GetDeviceExtensionsXRPlatform(char** namesString, uint32_t* extensionCount, uint32_t namesCapacityIn);
int Pxr_GetInstanceExtensionsXRPlatform(char** namesString, uint32_t* extensionCount, uint32_t namesCapacityIn);
int Pxr_CreateVulkanSystem(const PxrVulkanBinding* vulkanBinding);

bool Pxr_GetFeatureSupported(PxrFeatureType feature);

// Create layers
int Pxr_GetConfigViewsInfos(uint32_t* maxImageRectWidth, uint32_t* maxImageRectHeight, uint32_t* recommendedImageRectWidth, uint32_t* recommendedImageRectHeight);
int Pxr_CreateLayer(const PxrLayerParam* layerParam);
int Pxr_GetLayerImageCount(int layerId, PxrEyeType eye, uint32_t* imageCount);
int Pxr_GetLayerImage(int layerId, PxrEyeType eye, int imageIndex, uint64_t* image);
int Pxr_GetLayerNextImageIndex(int layerId, int* imageIndex);
int Pxr_GetLayerAndroidSurface(int layerId, PxrEyeType eye, jobject* androidSurface);
int Pxr_GetLayerFoveationImage(int layerId, PxrEyeType eye, uint64_t* foveationImage, uint32_t* width, uint32_t* height);
int Pxr_DestroyLayer(int layerId);

// Begin and end Xr mode
bool Pxr_IsRunning();
int Pxr_BeginXr();
int Pxr_EndXr();

// Tracking sensor
int Pxr_GetPredictedDisplayTime(double* predictedDisplayTimeMs);
int Pxr_GetPredictedMainSensorState(double predictTimeMs, PxrSensorState* sensorState, int* sensorFrameIndex);
int Pxr_GetPredictedMainSensorState2(double predictTimeMs, PxrSensorState2* sensorState, int* sensorFrameIndex);
int Pxr_GetPredictedMainSensorStateWithEyePose(double predictTimeMs, PxrSensorState* sensorState, int* sensorFrameIndex, int eyeCount, PxrPosef* eyePoses);
int Pxr_ResetSensor(PxrResetSensorOption option);

// Submit
int Pxr_WaitFrame();
int Pxr_BeginFrame();
int Pxr_SubmitLayer(const PxrLayerHeader* layer);
int Pxr_SubmitLayer2(const PxrLayerHeader2* layer);
int Pxr_EndFrame();

// Event
bool Pxr_PollEvent(int eventCountMAX,int* eventDataCountOutput, PxrEventDataBuffer** eventDataPtr);

// Log print
extern unsigned int minLogLevel_PxrAPI;
void Pxr_LogPrint(int priority, const char * tag, const char * fmt, ...);

// Fov
int Pxr_GetFov(PxrEyeType eye, float* fovLeft, float* fovRight, float* fovUp, float* fovDown);
int Pxr_GetFrustum(PxrEyeType eye,float* left, float* right, float* top, float* bottom, float *near, float* far);
int Pxr_SetFrustum(PxrEyeType eye,float left, float right, float top, float bottom,float near,float far);

// Performance level
int Pxr_SetPerformanceLevels(PxrPerfSettings which,int level);
int Pxr_GetPerformanceLevels(PxrPerfSettings which,int* level);

// ColorSpace
int Pxr_SetColorSpace(PxrColorSpace colorSpace);

// FFR
PxrFoveationLevel Pxr_GetFoveationLevel();
int Pxr_SetFoveationLevel(PxrFoveationLevel level);
int Pxr_SetFoveationParams(PxrFoveationParams params);

// Tracking mode
int Pxr_SetTrackingMode(PxrTrackingModeFlags trackingMode);
// Get supported tracking mode
int Pxr_GetTrackingMode(PxrTrackingModeFlags* trackingMode);

// Eye tracking
int Pxr_GetEyeTrackingData(PxrEyeTrackingData* eyeTrackingData);

//Face tracking
int Pxr_GetFaceTrackingData(int64_t ts, int flags, PxrFTInfo *data);
int Pxr_GetPupilDistance(float* ipd);
int Pxr_StartEyeTracking();
int Pxr_StopEyeTracking(int mode);
// Tracking origin
int Pxr_SetTrackingOrigin(PxrTrackingOrigin trackingOrigin);
int Pxr_GetTrackingOrigin(PxrTrackingOrigin* trackingOrigin);

// IPD
float Pxr_GetIPD();
bool Pvr_SetIPD(float distance);
float Pvr_GetIPD();
bool Pvr_SetTrackingIPDEnabled(bool enable);
bool Pvr_GetTrackingIPDEnabled();
bool Pvr_GetEyeTrackingAutoIPD(float *autoIPD);

int Pxr_GetEyeOrientation(int eyeIndex,PxrQuaternionf *orientation);
// AppFocus
bool Pxr_GetAppHasFocus();

// Configs
int Pxr_GetConfigInt(PxrConfigType configIndex, int* configData);
int Pxr_GetConfigFloat(PxrConfigType configIndex, float* configData);
int Pxr_GetConfigString(PxrConfigType configIndex, char* data);

int Pxr_SetConfigInt(PxrConfigType configSetIndex, int configSetData);
int Pxr_SetConfigString(PxrConfigType configIndex, const char* configSetData);
int Pxr_SetConfigUint64(PxrConfigType configIndex, uint64_t configSetData);
int Pxr_SetConfigIntArray(PxrConfigType configIndex, int configSetData[], int dataCount);
int Pxr_SetConfigFloatArray(PxrConfigType configIndex, float configSetData[], int dataCount);


void Pxr_RegisteKeyEventCallback(void* func);

bool Pxr_GetIntSysProc(char * command,int* rlt);

// Boundary
int Pxr_SetGuardianSystemDisable( bool disable);
int Pxr_ResumeGuardianSystemForSTS();
int Pxr_PauseGuardianSystemForSTS();
int Pxr_ShutdownSdkGuardianSystem();
int Pxr_GetCameraDataExt(uint8_t** data);
int Pxr_StartSdkBoundary();
int Pxr_StartCameraPreview(int value);
int Pxr_GetRoomModeState();
int Pxr_GetDialogState();
int Pxr_DisableBoundary();
int Pxr_SetMonoMode(bool mono);
bool Pxr_GetBoundaryConfigured();
bool Pxr_GetBoundaryEnabled();
int Pxr_SetBoundaryVisible(bool value);
int Pxr_SetSeeThroughBackground( bool value);
bool Pxr_GetBoundaryVisible();
int Pxr_SetSeeThroughVisible( bool value);
int Pxr_SetControllerPoseToBoundary(const PxrPosef* pose, PxrControllerHandness hand, bool valid);
int Pxr_TestNodeIsInBoundary(PxrBoundaryTestNode node, bool isPlayArea, PxrBoundaryTriggerInfo* info);
int Pxr_TestPointIsInBoundary(const PxrVector3f* point, bool isPlayArea, PxrBoundaryTriggerInfo* info);
int Pxr_GetBoundaryGeometry(bool isPlayArea, uint32_t pointsCountInput, uint32_t* pointsCountOutput, PxrVector3f* outPoints);
int Pxr_GetBoundaryGeometry2(bool isPlayArea, float ** outPointsFloat, uint32_t *pointsCountOutput);
int Pxr_GetBoundaryDimensions(bool isPlayArea, PxrVector3f* dimension);
int Pxr_SetSeeThroughImageExtent(uint32_t width, uint32_t height);
int Pxr_GetSeeThroughData(PxrSeeThoughData* data);
void Pxr_SetOriginOfLargeSpace(float*pose);
// Multiview
bool Pxr_EnableMultiview(bool enable);

// Mrc extended api
int Pxr_GetMrcPose(PxrPosef* pose);
int Pxr_SetMrcPose(const PxrPosef* pose);
int Pxr_SetIsSupportMovingMrc(bool support);
bool Pxr_GetMrcStatus();

int Pxr_SetSensorLostCustomMode(bool value);
int Pxr_SetSensorLostCMST(bool value);

int Pxr_GetDisplayRefreshRatesAvailable(uint32_t* count, float** rateArray);
int Pxr_SetDisplayRefreshRate(float refreshRate);
int Pxr_GetDisplayRefreshRate(float* refreshRate);
void Pxr_ResetSensorHard();
int Pxr_GetTrackingState();
bool Pxr_SetExtraLatencyMode(int mode);

void Pxr_InitPsensor(jobject activity);
int Pxr_getPsensorState();
void Pxr_UnregisterPsensor();

int Pxr_GetStringMetaFromApplication(const char* keyname,char* value);
int  Pxr_GetIntMetaFromApplication(const char* keyname,int * value);

#if defined(__cplusplus)
} // extern "C"
#endif

#endif  // PXR_API_H
