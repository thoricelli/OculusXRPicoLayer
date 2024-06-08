#ifndef OCULUS_XR_TYPES_H
#define OCULUS_XR_TYPES_H

#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>

typedef struct Colorf_
{
    float r;
    float g;
    float b;
    float a;
} Colorf;

typedef struct Quatf_
{
    float x;
    float y;
    float z;
    float w;
} Quatf;

typedef struct Vector3f
{
    float x;
    float y;
    float z;
} Vector3f;

typedef struct Posef_
{
    Quatf Orientation;
    Vector3f Position;
} Posef;

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

typedef struct VirtualKeyboardCreateInfo_
{
} VirtualKeyboardCreateInfo;


typedef enum VirtualKeyboardInputSource_
{
    VirtualKeyboardInputSource_Invalid = 0,
    VirtualKeyboardInputSource_ControllerRayLeft = 1,
    VirtualKeyboardInputSource_ControllerRayRight = 2,
    VirtualKeyboardInputSource_HandRayLeft = 3,
    VirtualKeyboardInputSource_HandRayRight = 4,
    VirtualKeyboardInputSource_ControllerDirectLeft = 5,
    VirtualKeyboardInputSource_ControllerDirectRight = 6,
    VirtualKeyboardInputSource_HandDirectIndexTipLeft = 7,
    VirtualKeyboardInputSource_HandDirectIndexTipRight = 8,
    VirtualKeyboardInputSource_EnumSize = 0x7FFFFFFF,
} VirtualKeyboardInputSource;

typedef enum VirtualKeyboardInputStateFlags_
{
    IsPressed = 0x0000000000000001,
} VirtualKeyboardInputStateFlags;

typedef struct VirtualKeyboardInputInfo_
{
    VirtualKeyboardInputSource inputSource;
    Posef inputPose;
    VirtualKeyboardInputStateFlags inputState;
} VirtualKeyboardInputInfo;

typedef enum VirtualKeyboardLocationType_
{
    Custom = 0,
    Far = 1,
    Direct = 2
} VirtualKeyboardLocationType;

typedef struct VirtualKeyboardSpaceCreateInfo_
{
    VirtualKeyboardLocationType locationType;
    // Pose only set if locationType == Custom
    Posef pose;
} VirtualKeyboardSpaceCreateInfo;

typedef struct VirtualKeyboardLocationInfo_
{
    VirtualKeyboardLocationType locationType;
    // Pose & Scale only set if locationType == Custom
    Posef pose;
    float scale;
} VirtualKeyboardLocationInfo;

typedef struct VirtualKeyboardSoundInternal_
{
    uint32_t SoundId;
    uint32_t Channels;
    uint32_t Frequency;
    uint32_t SoundCapacityInput;
    uint32_t SoundCountOutput;
    intptr_t SoundBuffer;
} VirtualKeyboardSoundInternal;

typedef struct VirtualKeyboardSwipeTrailState_
{
    float lifetimeSeconds;
    Colorf color;
    float startWidth;
    uint32_t shapeCapacityInput;
    uint32_t shapeCountOutput;
    intptr_t shape;
} VirtualKeyboardSwipeTrailState;

#endif