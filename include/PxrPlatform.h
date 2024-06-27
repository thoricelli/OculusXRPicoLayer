#ifndef PXR_PLATFORM_H
#define PXR_PLATFORM_H

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

#if defined(__cplusplus)
extern "C" {
#endif

bool Pxr_LoadPlugin();
void Pxr_UnloadPlugin();
void Pxr_SetUserDefinedSettings(PICO_UserDefinedSettings settings);
bool Pxr_GetBoundaryConfigured();
int Pxr_GetBoundaryDimensions(bool isPlayArea, PxrVector3f *dimension);
bool Pxr_GetBoundaryVisible();
int Pxr_SetBoundaryVisible(bool value);
int Pxr_SetDisplayRefreshRate(float refreshRate);
typedef Quaternion (*ConvertRotationWith2VectorDelegate)(Vector3 from, Vector3 to);
void Pxr_Construct(ConvertRotationWith2VectorDelegate fromToRotation);

#if defined(__cplusplus)
} // extern "C"
#endif

#endif  // PXR_PLATFORM_H