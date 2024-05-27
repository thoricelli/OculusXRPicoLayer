//For both libpxr_api & libPxrPlatform.

typedef struct PICO_UserDefinedSettings
{
    unsigned short stereoRenderingMode;
    unsigned short colorSpace;
    unsigned short systemDisplayFrequency;
    unsigned short useContentProtect;
    unsigned short optimizeBufferDiscards;
    unsigned short enableAppSpaceWarp;
    unsigned short enableSubsampled;
    unsigned short lateLatchingDebug;
    unsigned short enableStageMode;
} PICO_UserDefinedSettings;

typedef struct PxrVector3f_ {
    float    x;
    float    y;
    float    z;
} PxrVector3f;

enum ConfigType
{
    RenderTextureWidth,
    RenderTextureHeight,
    ShowFps,
    RuntimeLogLevel,
    PluginLogLevel,
    UnityLogLevel,
    UnrealLogLevel,
    NativeLogLevel,
    TargetFrameRate,
    NeckModelX,
    NeckModelY,
    NeckModelZ,
    DisplayRefreshRate,
    Ability6Dof,
    DeviceModel,
    PhysicalIPD,
    ToDelaSensorY,
    SystemDisplayRate,
    FoveationSubsampledEnabled,
    TrackingOriginHeight,
    EngineVersion,
    UnrealOpenglNoError,
    EnableCPT,
    MRCTextureID,
    RenderFPS,
    AntiAliasingLevelRecommended,
    MRCTextureID2,
    PxrSetSurfaceView,
    PxrAPIVersion,
    PxrMrcPosiyionYOffset,
    PxrMrcTextureWidth,
    PxrMrcTextureHeight,
    PxrAndroidLayerDimensions = 34,
    PxrANDROID_SN,
    PxrSetDesiredFPS,
    PxrGetSeethroughState,
    PxrSetLayerBlend,
    PxrLeftEyeFOV,
    PxrRightEyeFOV,
    PxrBothEyeFOV,
    SupportQuickSeethrough,
    SetFilterType,
    SetSubmitLayerEXTItemColorMatrix,
};

extern bool Pxr_LoadPlugin();
extern void Pxr_UnloadPlugin();
extern void Pxr_SetUserDefinedSettings(PICO_UserDefinedSettings settings);
extern bool Pxr_GetBoundaryConfigured();
extern int Pxr_GetBoundaryDimensions(bool isPlayArea, PxrVector3f *dimension);
extern bool Pxr_GetBoundaryVisible();
extern int Pxr_SetBoundaryVisible(bool value);
extern bool Pxr_GetDisplayRefreshRatesAvailable(int *configCount, int *configArray);
extern int Pxr_SetDisplayRefreshRate(float refreshRate);
extern int Pxr_GetConfigFloat(enum ConfigType configIndex, float* value);