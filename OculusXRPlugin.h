#ifndef OCULUS_XR_TYPES_H
#define OCULUS_XR_TYPES_H

#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>

typedef struct _ovrpVector4f {
    float x;
    float y;
    float z;
    float w;
} ovrpVector4f;

typedef struct _UserDefinedSettings {
    unsigned short sharedDepthBuffer;
    unsigned short dashSupport;
    unsigned short stereoRenderingMode;
    unsigned short colorSpace;
    unsigned short lowOverheadMode;
    unsigned short optimizeBufferDiscards;
    unsigned short phaseSync;
    unsigned short symmetricProjection;
    unsigned short subsampledLayout;
    unsigned short lateLatching;
    unsigned short lateLatchingDebug;
    unsigned short enableTrackingOriginStageMode;
    unsigned short spaceWarp;
    unsigned short depthSubmission;
    unsigned short foveatedRenderingMethod;
} UserDefinedSettings;

enum SystemHeadset
{
    SystemHeadset_None = 0,

    // Standalone headsets
    Oculus_Quest = 8,
    Oculus_Quest_2 = 9,
    Meta_Quest_Pro = 10,
    Placeholder_10 = 10,
    Meta_Quest_3 = 11,
    Placeholder_11 = 11,
    Placeholder_12,
    Placeholder_13,
    Placeholder_14,

    // PC headsets
    Rift_DK1 = 0x1000,
    Rift_DK2,
    Rift_CV1,
    Rift_CB,
    Rift_S,
    Oculus_Link_Quest,
    Oculus_Link_Quest_2,
    Meta_Link_Quest_Pro,
    PC_Placeholder_4103 = Meta_Link_Quest_Pro,
    Meta_Link_Quest_3,
    PC_Placeholder_4104 = Meta_Link_Quest_3,
    PC_Placeholder_4105,
    PC_Placeholder_4106,
    PC_Placeholder_4107
};

typedef struct EnvironmentDepthCreateParamsInternal
{
    bool removeHands;
} EnvironmentDepthCreateParamsInternal;

typedef struct Vector3
{
    float x, y, z;
} Vector3;

typedef struct Vector4
{
    float w, x, y, z;
} Vector4;

typedef struct EnvironmentDepthFrameDescInternal {
    bool isValid;
    double createTime;
    double predictedDisplayTime;
    int swapchainIndex;
    Vector3 createPoseLocation;
    Vector4 createPoseRotation;
    float fovLeftAngle;
    float fovRightAngle;
    float fovTopAngle;
    float fovDownAngle;
    float nearZ;
    float farZ;
    float minDepth;
    float maxDepth;
} EnvironmentDepthFrameDescInternal;

#endif