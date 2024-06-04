//For both libpxr_api & libPxrPlatform.
#include <stdint.h>
#include "PxrTypes.h"

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

extern bool Pxr_LoadPlugin();
extern void Pxr_UnloadPlugin();
extern void Pxr_SetUserDefinedSettings(PICO_UserDefinedSettings settings);
extern bool Pxr_GetBoundaryConfigured();
extern int Pxr_GetBoundaryDimensions(bool isPlayArea, PxrVector3f *dimension);
extern bool Pxr_GetBoundaryVisible();
extern int Pxr_SetBoundaryVisible(bool value);
extern int Pxr_SetDisplayRefreshRate(float refreshRate);
typedef Quaternion (*ConvertRotationWith2VectorDelegate)(Vector3 from, Vector3 to);
extern void Pxr_Construct(ConvertRotationWith2VectorDelegate fromToRotation);