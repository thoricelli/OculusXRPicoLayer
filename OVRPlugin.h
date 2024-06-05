#ifndef OVR_PLUGIN_TYPES_H
#define OVR_PLUGIN_TYPES_H

#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>

#include "OculusXRPlugin.h"

typedef struct Sizei_
{
    int32_t w;
    int32_t h;
} Sizei;

typedef enum Eye_
{
    Eye_None = -1,
    Left = 0,
    Right = 1,
    Count = 2
} Eye;

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


typedef enum Node_
{
    none = -1,
    EyeLeft = 0,
    EyeRight = 1,
    EyeCenter = 2,
    HandLeft = 3,
    HandRight = 4,
    TrackerZero = 5,
    TrackerOne = 6,
    TrackerTwo = 7,
    TrackerThree = 8,
    Head = 9,
    DeviceObjectZero = 10,
    TrackedKeyboard = 11,
    Node_count,
} Node;

typedef enum TrackingOrigin_
{
    EyeLevel = 0,
    FloorLevel = 1,
    Stage = 2,
    View = 4,
    TrackingOrigin_count,
} TrackingOrigin;

typedef struct Frustumf_
{
    float zNear;
    float zFar;
    float fovX;
    float fovY;
} Frustumf;

typedef struct Vector2f_
{
    float x;
    float y;
} Vector2f;

typedef struct ControllerState_
{
    uint ConnectedControllers;
    uint Buttons;
    uint Touches;
    uint NearTouches;
    float LIndexTrigger;
    float RIndexTrigger;
    float LHandTrigger;
    float RHandTrigger;
    Vector2f LThumbstick;
    Vector2f RThumbstick;
} ControllerState;

typedef enum ControllerButtons_
{
    Button_A,
    Button_B,
} ControllerButtons;

typedef enum ControllerType_
{
    RightController_Start = 0,
    LeftController_Start = 0x80000000,
} ControllerType;

typedef enum Button_
{
    Button_None                      = 0,          ///< Maps to RawButton: [Gamepad, Touch, LTouch, RTouch, Remote: None]
    Button_One                       = 0x00000001, ///< Maps to RawButton: [Gamepad, Touch, RTouch: A], [LTouch: X], [Remote: Start]
    Button_Two                       = 0x00000002, ///< Maps to RawButton: [Gamepad, Touch, RTouch: B], [LTouch: Y], [Remote: Back]
    Button_Three                     = 0x00000004, ///< Maps to RawButton: [Gamepad, Touch: X], [LTouch, RTouch, Remote: None]
    Button_Four                      = 0x00000008, ///< Maps to RawButton: [Gamepad, Touch: Y], [LTouch, RTouch, Remote: None]
    Button_Start                     = 0x00000100, ///< Maps to RawButton: [Gamepad: Start], [Touch, LTouch, Remote: Start], [RTouch: None]
    Button_Back                      = 0x00000200, ///< Maps to RawButton: [Gamepad, Remote: Back], [Touch, LTouch, RTouch: None]
    Button_PrimaryShoulder           = 0x00001000, ///< Maps to RawButton: [Gamepad: LShoulder], [Touch, LTouch, RTouch, Remote: None]
    Button_PrimaryIndexTrigger       = 0x00002000, ///< Maps to RawButton: [Gamepad, Touch, LTouch: LIndexTrigger], [RTouch: RIndexTrigger], [Remote: None]
    Button_PrimaryHandTrigger        = 0x00004000, ///< Maps to RawButton: [Touch, LTouch: LHandTrigger], [RTouch: RHandTrigger], [Gamepad, Remote: None]
    Button_PrimaryThumbstick         = 0x00008000, ///< Maps to RawButton: [Gamepad, Touch, LTouch: LThumbstick], [RTouch: RThumbstick], [Remote: None]
    Button_PrimaryThumbstickUp       = 0x00010000, ///< Maps to RawButton: [Gamepad, Touch, LTouch: LThumbstickUp], [RTouch: RThumbstickUp], [Remote: None]
    Button_PrimaryThumbstickDown     = 0x00020000, ///< Maps to RawButton: [Gamepad, Touch, LTouch: LThumbstickDown], [RTouch: RThumbstickDown], [Remote: None]
    Button_PrimaryThumbstickLeft     = 0x00040000, ///< Maps to RawButton: [Gamepad, Touch, LTouch: LThumbstickLeft], [RTouch: RThumbstickLeft], [Remote: None]
    Button_PrimaryThumbstickRight    = 0x00080000, ///< Maps to RawButton: [Gamepad, Touch, LTouch: LThumbstickRight], [RTouch: RThumbstickRight], [Remote: None]
    Button_PrimaryTouchpad           = 0x00000400, ///< Maps to RawButton: [Gamepad, Touch, LTouch, RTouch, Remote: None]
    Button_SecondaryShoulder         = 0x00100000, ///< Maps to RawButton: [Gamepad: RShoulder], [Touch, LTouch, RTouch, Remote: None]
    Button_SecondaryIndexTrigger     = 0x00200000, ///< Maps to RawButton: [Gamepad, Touch: RIndexTrigger], [LTouch, RTouch, Remote: None]
    Button_SecondaryHandTrigger      = 0x00400000, ///< Maps to RawButton: [Touch: RHandTrigger], [Gamepad, LTouch, RTouch, Remote: None]
    Button_SecondaryThumbstick       = 0x00800000, ///< Maps to RawButton: [Gamepad, Touch: RThumbstick], [LTouch, RTouch, Remote: None]
    Button_SecondaryThumbstickUp     = 0x01000000, ///< Maps to RawButton: [Gamepad, Touch: RThumbstickUp], [LTouch, RTouch, Remote: None]
    Button_SecondaryThumbstickDown   = 0x02000000, ///< Maps to RawButton: [Gamepad, Touch: RThumbstickDown], [LTouch, RTouch, Remote: None]
    Button_SecondaryThumbstickLeft   = 0x04000000, ///< Maps to RawButton: [Gamepad, Touch: RThumbstickLeft], [LTouch, RTouch, Remote: None]
    Button_SecondaryThumbstickRight  = 0x08000000, ///< Maps to RawButton: [Gamepad, Touch: RThumbstickRight], [LTouch, RTouch, Remote: None]
    Button_SecondaryTouchpad         = 0x00000800, ///< Maps to RawButton: [Gamepad, Touch, LTouch, RTouch, Remote: None]
    Button_DpadUp                    = 0x00000010, ///< Maps to RawButton: [Gamepad, Remote: DpadUp], [Touch, LTouch, RTouch: None]
    Button_DpadDown                  = 0x00000020, ///< Maps to RawButton: [Gamepad, Remote: DpadDown], [Touch, LTouch, RTouch: None]
    Button_DpadLeft                  = 0x00000040, ///< Maps to RawButton: [Gamepad, Remote: DpadLeft], [Touch, LTouch, RTouch: None]
    Button_DpadRight                 = 0x00000080, ///< Maps to RawButton: [Gamepad, Remote: DpadRight], [Touch, LTouch, RTouch: None]
    Button_Up                        = 0x10000000, ///< Maps to RawButton: [Gamepad, Touch, LTouch: LThumbstickUp], [RTouch: RThumbstickUp], [Remote: DpadUp]
    Button_Down                      = 0x20000000, ///< Maps to RawButton: [Gamepad, Touch, LTouch: LThumbstickDown], [RTouch: RThumbstickDown], [Remote: DpadDown]
    Button_Left                      = 0x40000000, ///< Maps to RawButton: [Gamepad, Touch, LTouch: LThumbstickLeft], [RTouch: RThumbstickLeft], [Remote: DpadLeft]
    Button_Right      = 0x80000000,///< Maps to RawButton: [Gamepad, Touch, LTouch: LThumbstickRight], [RTouch: RThumbstickRight], [Remote: DpadRight]
    Button_Any                       = ~Button_None,      ///< Maps to RawButton: [Gamepad, Touch, LTouch, RTouch: Any]
} Button;

typedef enum BatteryStatus_
{
    Charging = 0,
    Discharging,
    Full,
    NotCharging,
    Unknown,
} BatteryStatus;

typedef enum PlatformUI_
{
    PlatformUI_none = -1,
    ConfirmQuit = 1,
    GlobalMenuTutorial, // Deprecated
} PlatformUI;

typedef enum SystemRegion_
{
    Unspecified = 0,
    Japan,
    China,
} SystemRegion;

typedef struct HapticsDesc_
{
    int SampleRateHz;
    int SampleSizeInBytes;
    int MinimumSafeSamplesQueued;
    int MinimumBufferSamplesCount;
    int OptimalBufferSamplesCount;
    int MaximumBufferSamplesCount;
} HapticsDesc;

typedef struct HapticsState_
{
    int SamplesAvailable;
    int SamplesQueued;
} HapticsState;

typedef struct HapticsBuffer_
{
    uintptr_t Samples;
    int SamplesCount;
} HapticsBuffer;

typedef struct BoundaryTestResult_
{
    bool IsTriggering;
    float ClosestDistance;
    Vector3f ClosestPoint;
    Vector3f ClosestPointNormal;
} BoundaryTestResult;

typedef enum BoundaryType_
{
    OuterBoundary = 0x0001,
    PlayArea = 0x0100,
} BoundaryType;

typedef struct BoundaryGeometry_
{
    BoundaryType BoundaryType;
    Vector3f *Points;
    int PointsCount;
} BoundaryGeometry;

typedef enum Controller_
{
    Controller_None = 0,
    LTouch = 0x00000001,
    RTouch = 0x00000002,
    Touch = LTouch | RTouch,
    Remote = 0x00000004,
    Gamepad = 0x00000010,
    LHand = 0x00000020,
    RHand = 0x00000040,
    Hands = LHand | RHand,
    Active = 0x80000000,
    All = ~Controller_None,
} Controller;

typedef struct AppPerfFrameStats_
{
    int HmdVsyncIndex;
    int AppFrameIndex;
    int AppDroppedFrameCount;
    float AppMotionToPhotonLatency;
    float AppQueueAheadTime;
    float AppCpuElapsedTime;
    float AppGpuElapsedTime;
    int CompositorFrameIndex;
    int CompositorDroppedFrameCount;
    float CompositorLatency;
    float CompositorCpuElapsedTime;
    float CompositorGpuElapsedTime;
    float CompositorCpuStartToGpuEndElapsedTime;
    float CompositorGpuEndToVsyncElapsedTime;
} AppPerfFrameStats;

typedef struct AppPerfStats_
{
    AppPerfFrameStats *FrameStats;
    int FrameStatsCount;
    bool AnyFrameStatsDropped;
    float AdaptiveGpuPerformanceScale;
} AppPerfStats;

typedef enum EyeTextureFormat_
{
    Default = 0,
    R16G16B16A16_FP = 2,
    R11G11B10_FP = 3,
} EyeTextureFormat;

typedef struct PoseStatef_
{
    Posef Pose;
    Vector3f Velocity;
    Vector3f Acceleration;
    Vector3f AngularVelocity;
    Vector3f AngularAcceleration;
    double Time;
} PoseStatef;

typedef enum Step_
{
    Render = -1,
    Physics = 0, // will be deprecated when using OpenXR
} Step;

typedef struct ControllerState2_ {
    uint ConnectedControllers;
    uint Buttons;
    uint Touches;
    uint NearTouches;
    float LIndexTrigger;
    float RIndexTrigger;
    float LHandTrigger;
    float RHandTrigger;
    Vector2f LThumbstick;
    Vector2f RThumbstick;
    Vector2f LTouchpad;
    Vector2f RTouchpad;
} ControllerState2;

typedef enum Result_
{
    /// Success
    Success = 0,
    Success_EventUnavailable = 1,
    Success_Pending = 2,

    /// Failure
    Failure = -1000,
    Failure_InvalidParameter = -1001,
    Failure_NotInitialized = -1002,
    Failure_InvalidOperation = -1003,
    Failure_Unsupported = -1004,
    Failure_NotYetImplemented = -1005,
    Failure_OperationFailed = -1006,
    Failure_InsufficientSize = -1007,
    Failure_DataIsInvalid = -1008,
    Failure_DeprecatedOperation = -1009
} Result;

typedef struct Fovf_
{
    float UpTan;
    float DownTan;
    float LeftTan;
    float RightTan;
} Fovf;

typedef struct CameraIntrinsics_
{
    bool IsValid;
    double LastChangedTimeSeconds;
    Fovf FOVPort;
    float VirtualNearPlaneDistanceMeters;
    float VirtualFarPlaneDistanceMeters;
    Sizei ImageSensorPixelResolution;
} CameraIntrinsics;

typedef enum CameraStatus_
{
    CameraStatus_None,
    CameraStatus_Connected,
    CameraStatus_Calibrating,
    CameraStatus_CalibrationFailed,
    CameraStatus_Calibrated,
    CameraStatus_ThirdPerson,
    CameraStatus_EnumSize = 0x7fffffff
} CameraStatus;

typedef struct CameraExtrinsics_
{
    bool IsValid;
    double LastChangedTimeSeconds;
    CameraStatus CameraStatusData;
    Node AttachedToNode;
    Posef RelativePose;
} CameraExtrinsics;

typedef enum OverlayShape_
{
    Quad = 0,
    Cylinder = 1,
    Cubemap = 2,
    OffcenterCubemap = 4,
    Equirect = 5,
    ReconstructionPassthrough = 7,
    SurfaceProjectedPassthrough = 8,
    Fisheye = 9,
    KeyboardHandsPassthrough = 10,
} OverlayShape;

typedef enum LayerLayout_
{
    Stereo = 0,
    Mono = 1,
    DoubleWide = 2,
    Array = 3,
    EnumSize = 0xF
} LayerLayout;

typedef struct Sizef_
{
    float w;
    float h;
} Sizef;

typedef struct Rectf_
{
    Vector2f Pos;
    Sizef Size;
} Rectf;

typedef struct LayerDesc_
{
    OverlayShape Shape;
    LayerLayout Layout;
    Sizei TextureSize;
    int MipLevels;
    int SampleCount;
    EyeTextureFormat Format;
    int LayerFlags;
    Fovf *Fov;
    Rectf *VisibleRect;
    Sizei MaxViewportSize;
    EyeTextureFormat DepthFormat;

    EyeTextureFormat MotionVectorFormat;
    EyeTextureFormat MotionVectorDepthFormat;
    Sizei MotionVectorTextureSize;
} LayerDesc;

typedef struct Frustumf2_
{
    float zNear;
    float zFar;
    Fovf Fov;
} Frustumf2;

typedef enum CameraDevice_
{
    None = 0,
    WebCamera0 = 100,
    WebCamera1 = 101,
    ZEDCamera = 300,
} CameraDevice;

typedef struct ControllerState4 {
    uint ConnectedControllers;
    uint Buttons;
    uint Touches;
    uint NearTouches;
    float LIndexTrigger;
    float RIndexTrigger;
    float LHandTrigger;
    float RHandTrigger;
    Vector2f LThumbstick;
    Vector2f RThumbstick;
    Vector2f LTouchpad;
    Vector2f RTouchpad;
    unsigned char LBatteryPercentRemaining;
    unsigned char RBatteryPercentRemaining;
    unsigned char LRecenterCount;
    unsigned char RRecenterCount;
    unsigned char Reserved_27;
    unsigned char Reserved_26;
    unsigned char Reserved_25;
    unsigned char Reserved_24;
    unsigned char Reserved_23;
    unsigned char Reserved_22;
    unsigned char Reserved_21;
    unsigned char Reserved_20;
    unsigned char Reserved_19;
    unsigned char Reserved_18;
    unsigned char Reserved_17;
    unsigned char Reserved_16;
    unsigned char Reserved_15;
    unsigned char Reserved_14;
    unsigned char Reserved_13;
    unsigned char Reserved_12;
    unsigned char Reserved_11;
    unsigned char Reserved_10;
    unsigned char Reserved_09;
    unsigned char Reserved_08;
    unsigned char Reserved_07;
    unsigned char Reserved_06;
    unsigned char Reserved_05;
    unsigned char Reserved_04;
    unsigned char Reserved_03;
    unsigned char Reserved_02;
    unsigned char Reserved_01;
    unsigned char Reserved_00;
} ControllerState4;

typedef struct CameraDeviceIntrinsicsParameters_
{
    float fx; /* Focal length in pixels along x axis. */
    float fy; /* Focal length in pixels along y axis. */
    float cx; /* Optical center along x axis, defined in pixels (usually close to width/2). */
    float cy; /* Optical center along y axis, defined in pixels (usually close to height/2). */
    double disto0; /* Distortion factor : [ k1, k2, p1, p2, k3 ]. Radial (k1,k2,k3) and Tangential (p1,p2) distortion.*/
    double disto1;
    double disto2;
    double disto3;
    double disto4;
    float v_fov; /* Vertical field of view after stereo rectification, in degrees. */
    float h_fov; /* Horizontal field of view after stereo rectification, in degrees.*/
    float d_fov; /* Diagonal field of view after stereo rectification, in degrees.*/
    int w; /* Resolution width */
    int h; /* Resolution height */
} CameraDeviceIntrinsicsParameters;

typedef enum CameraDeviceDepthSensingMode_
{
    Standard = 0,
    Fill = 1,
} CameraDeviceDepthSensingMode;

typedef enum CameraDeviceDepthQuality_
{
    Low = 0,
    Medium = 1,
    High = 2,
} CameraDeviceDepthQuality;

typedef enum FixedFoveatedRenderingLevel_
{
    Off = 0,
    FixedFoveatedRenderingLevel_Low = 1,
    FixedFoveatedRenderingLevel_Medium = 2,
    FixedFoveatedRenderingLevel_High = 3,
    // High foveation setting with more detail toward the bottom of the view and more foveation near the top (Same as High on Oculus Go)
    HighTop = 4,
    FixedFoveatedRenderingLevel_EnumSize = 0x7FFFFFFF
} FixedFoveatedRenderingLevel;

typedef enum Handedness_
{
    Unsupported = 0,
    LeftHanded = 1,
    RightHanded = 2,
} Handedness;

typedef enum PerfMetrics_
{
    App_CpuTime_Float = 0,
    App_GpuTime_Float = 1,

    Compositor_CpuTime_Float = 3,
    Compositor_GpuTime_Float = 4,
    Compositor_DroppedFrameCount_Int = 5,

    System_GpuUtilPercentage_Float = 7,
    System_CpuUtilAveragePercentage_Float = 8,
    System_CpuUtilWorstPercentage_Float = 9,

    // Added 1.32.0
    Device_CpuClockFrequencyInMHz_Float = 10, // Deprecated 1.68.0
    Device_GpuClockFrequencyInMHz_Float = 11, // Deprecated 1.68.0
    Device_CpuClockLevel_Int = 12, // Deprecated 1.68.0
    Device_GpuClockLevel_Int = 13, // Deprecated 1.68.0

    Compositor_SpaceWarp_Mode_Int = 14,

    Device_CpuCore0UtilPercentage_Float = 32,
    Device_CpuCore1UtilPercentage_Float = Device_CpuCore0UtilPercentage_Float + 1,
    Device_CpuCore2UtilPercentage_Float = Device_CpuCore0UtilPercentage_Float + 2,
    Device_CpuCore3UtilPercentage_Float = Device_CpuCore0UtilPercentage_Float + 3,
    Device_CpuCore4UtilPercentage_Float = Device_CpuCore0UtilPercentage_Float + 4,
    Device_CpuCore5UtilPercentage_Float = Device_CpuCore0UtilPercentage_Float + 5,
    Device_CpuCore6UtilPercentage_Float = Device_CpuCore0UtilPercentage_Float + 6,
    Device_CpuCore7UtilPercentage_Float = Device_CpuCore0UtilPercentage_Float + 7,
    // Enum value 32~63 are reserved for CPU Cores' utilization (assuming at most 32 cores).

    PerfMetrics_Count,
    PerfMetrics_EnumSize = 0x7FFFFFFF
} PerfMetrics;

typedef struct Rect_
{
    float x;
    float y;
    float z;
    float w;
    float h;
} Rect;

typedef struct TextureRectMatrixf_
{
    Rect leftRect;
    Rect rightRect;
    Vector4 leftScaleBias;
    Vector4 rightScaleBias;
} TextureRectMatrixf;

typedef enum MrcActivationMode_
{
    Automatic = 0,
    Disabled = 1,
    MrcActivationMode_EnumSize = 0x7fffffff
} MrcActivationMode;

typedef enum InputVideoBufferType_
{
    Memory = 0,
    TextureHandle = 1,
    InputVideoBufferType_EnumSize = 0x7fffffff
} InputVideoBufferType;

typedef enum Hand_
{
    Hand_None = -1,
    Hand_HandLeft = 0,
    Hand_HandRight = 1,
} Hand;

typedef enum HandStatus_
{
    HandTracked = (1 << 0), // if this is set the hand pose and bone rotations data is usable
    InputStateValid = (1 << 1), // if this is set the pointer pose and pinch data is usable
    SystemGestureInProgress = (1 << 6), // if this is set the hand is currently processing a system gesture
    DominantHand = (1 << 7), // if this is set the hand is currently the dominant hand
    MenuPressed = (1 << 8) // if this is set the hand performed a menu press
} HandStatus;

typedef enum HandFinger_
{
    HandFinger_Thumb = 0,
    HandFinger_Index = 1,
    HandFinger_Middle = 2,
    HandFinger_Ring = 3,
    HandFinger_Pinky = 4,
    HandFinger_Max = 5,
} HandFinger;

typedef enum HandFingerPinch_
{
    HandFingerPinch_Thumb  = (1 << HandFinger_Thumb),
    HandFingerPinch_Index  = (1 << HandFinger_Index),
    HandFingerPinch_Middle = (1 << HandFinger_Middle),
    HandFingerPinch_Ring   = (1 << HandFinger_Ring),
    HandFingerPinch_Pinky  = (1 << HandFinger_Pinky),
} HandFingerPinch;

typedef enum TrackingConfidence_
{
    TrackingConfidence_Low = 0,
    TrackingConfidence_High = 0x3f800000,
} TrackingConfidence;

typedef struct HandStateInternal_
{
    HandStatus Status;
    Posef RootPose;
    Quatf BoneRotations_0;
    Quatf BoneRotations_1;
    Quatf BoneRotations_2;
    Quatf BoneRotations_3;
    Quatf BoneRotations_4;
    Quatf BoneRotations_5;
    Quatf BoneRotations_6;
    Quatf BoneRotations_7;
    Quatf BoneRotations_8;
    Quatf BoneRotations_9;
    Quatf BoneRotations_10;
    Quatf BoneRotations_11;
    Quatf BoneRotations_12;
    Quatf BoneRotations_13;
    Quatf BoneRotations_14;
    Quatf BoneRotations_15;
    Quatf BoneRotations_16;
    Quatf BoneRotations_17;
    Quatf BoneRotations_18;
    Quatf BoneRotations_19;
    Quatf BoneRotations_20;
    Quatf BoneRotations_21;
    Quatf BoneRotations_22;
    Quatf BoneRotations_23;
    HandFingerPinch Pinches;
    float PinchStrength_0;
    float PinchStrength_1;
    float PinchStrength_2;
    float PinchStrength_3;
    float PinchStrength_4;
    Posef PointerPose;
    float HandScale;
    TrackingConfidence HandConfidence;
    TrackingConfidence FingerConfidences_0;
    TrackingConfidence FingerConfidences_1;
    TrackingConfidence FingerConfidences_2;
    TrackingConfidence FingerConfidences_3;
    TrackingConfidence FingerConfidences_4;
    double RequestedTimeStamp;
    double SampleTimeStamp;
} HandStateInternal;

typedef enum SkeletonType_
{
    SkeletonType_None = -1,
    SkeletonType_HandLeft = 0,
    SkeletonType_HandRight = 1,
} SkeletonType;

typedef enum BoneId
{
    Invalid                 = -1,

    // hand bones
    Hand_Start              = 0,
    Hand_WristRoot          = Hand_Start + 0, // root frame of the hand, where the wrist is located
    Hand_ForearmStub        = Hand_Start + 1, // frame for user's forearm
    Hand_Thumb0             = Hand_Start + 2, // thumb trapezium bone
    Hand_Thumb1             = Hand_Start + 3, // thumb metacarpal bone
    Hand_Thumb2             = Hand_Start + 4, // thumb proximal phalange bone
    Hand_Thumb3             = Hand_Start + 5, // thumb distal phalange bone
    Hand_Index1             = Hand_Start + 6, // index proximal phalange bone
    Hand_Index2             = Hand_Start + 7, // index intermediate phalange bone
    Hand_Index3             = Hand_Start + 8, // index distal phalange bone
    Hand_Middle1            = Hand_Start + 9, // middle proximal phalange bone
    Hand_Middle2            = Hand_Start + 10, // middle intermediate phalange bone
    Hand_Middle3            = Hand_Start + 11, // middle distal phalange bone
    Hand_Ring1              = Hand_Start + 12, // ring proximal phalange bone
    Hand_Ring2              = Hand_Start + 13, // ring intermediate phalange bone
    Hand_Ring3              = Hand_Start + 14, // ring distal phalange bone
    Hand_Pinky0             = Hand_Start + 15, // pinky metacarpal bone
    Hand_Pinky1             = Hand_Start + 16, // pinky proximal phalange bone
    Hand_Pinky2             = Hand_Start + 17, // pinky intermediate phalange bone
    Hand_Pinky3             = Hand_Start + 18, // pinky distal phalange bone
    Hand_MaxSkinnable       = Hand_Start + 19,
    // Bone tips are position only. They are not used for skinning but are useful for hit-testing.
    // NOTE: Hand_ThumbTip == Hand_MaxSkinnable since the extended tips need to be contiguous
    Hand_ThumbTip           = Hand_MaxSkinnable + 0, // tip of the thumb
    Hand_IndexTip           = Hand_MaxSkinnable + 1, // tip of the index finger
    Hand_MiddleTip          = Hand_MaxSkinnable + 2, // tip of the middle finger
    Hand_RingTip            = Hand_MaxSkinnable + 3, // tip of the ring finger
    Hand_PinkyTip           = Hand_MaxSkinnable + 4, // tip of the pinky
    Hand_End                = Hand_MaxSkinnable + 5,


    // add new bones here

    Max = Hand_End > 70 ? Hand_End : 70,
} BoneId;

typedef struct Bone_
{
    BoneId Id;
    short ParentBoneIndex;
    Posef Pose;
} Bone;

typedef struct BoneCapsule_
{
    short BoneIndex;
    Vector3f StartPoint;
    Vector3f EndPoint;
    float Radius;
} BoneCapsule;

typedef struct Skeleton_
{
    SkeletonType Type;
    uint NumBones;
    uint NumBoneCapsules;
    Bone* Bones;
    BoneCapsule *BoneCapsules;
} Skeleton;

typedef enum MeshType_
{
    MeshType_None = -1,
    MeshType_HandLeft = 0,
    MeshType_HandRight = 1,
} MeshType;

typedef enum ColorSpace_
{
    /// The default value from GetHmdColorSpace until SetClientColorDesc is called. Only valid on PC, and will be remapped to Quest on Mobile
    ColorSpace_Unknown = 0,
    /// No color correction, not recommended for production use. See documentation for more info
    ColorSpace_Unmanaged = 1,
    /// Preferred color space for standardized color across all Oculus HMDs with D65 white point
    ColorSpace_Rec_2020 = 2,
    /// Rec. 709 is used on Oculus Go and shares the same primary color coordinates as sRGB
    ColorSpace_Rec_709 = 3,
    /// Oculus Rift CV1 uses a unique color space, see documentation for more info
    ColorSpace_Rift_CV1 = 4,
    /// Oculus Rift S uses a unique color space, see documentation for more info
    ColorSpace_Rift_S = 5,
    /// Oculus Quest's native color space is slightly different than Rift CV1
    ColorSpace_Quest = 6,
    /// Similar to DCI-P3. See documentation for more details on P3
    ColorSpace_P3 = 7,
    /// Similar to sRGB but with deeper greens using D65 white point
    ColorSpace_Adobe_RGB = 8,
} ColorSpace;

typedef enum CameraAnchorType_
{
    CameraAnchorType_PreDefined = 0,
    CameraAnchorType_Custom = 1,
    CameraAnchorType_Count,
    CameraAnchorType_EnumSize = 0x7fffffff
} CameraAnchorType;

typedef struct Skeleton2Internal_
{
    SkeletonType Type;
    uint NumBones;
    uint NumBoneCapsules;
    Bone Bones_0;
    Bone Bones_1;
    Bone Bones_2;
    Bone Bones_3;
    Bone Bones_4;
    Bone Bones_5;
    Bone Bones_6;
    Bone Bones_7;
    Bone Bones_8;
    Bone Bones_9;
    Bone Bones_10;
    Bone Bones_11;
    Bone Bones_12;
    Bone Bones_13;
    Bone Bones_14;
    Bone Bones_15;
    Bone Bones_16;
    Bone Bones_17;
    Bone Bones_18;
    Bone Bones_19;
    Bone Bones_20;
    Bone Bones_21;
    Bone Bones_22;
    Bone Bones_23;
    Bone Bones_24;
    Bone Bones_25;
    Bone Bones_26;
    Bone Bones_27;
    Bone Bones_28;
    Bone Bones_29;
    Bone Bones_30;
    Bone Bones_31;
    Bone Bones_32;
    Bone Bones_33;
    Bone Bones_34;
    Bone Bones_35;
    Bone Bones_36;
    Bone Bones_37;
    Bone Bones_38;
    Bone Bones_39;
    Bone Bones_40;
    Bone Bones_41;
    Bone Bones_42;
    Bone Bones_43;
    Bone Bones_44;
    Bone Bones_45;
    Bone Bones_46;
    Bone Bones_47;
    Bone Bones_48;
    Bone Bones_49;
    Bone Bones_50;
    Bone Bones_51;
    Bone Bones_52;
    Bone Bones_53;
    Bone Bones_54;
    Bone Bones_55;
    Bone Bones_56;
    Bone Bones_57;
    Bone Bones_58;
    Bone Bones_59;
    Bone Bones_60;
    Bone Bones_61;
    Bone Bones_62;
    Bone Bones_63;
    Bone Bones_64;
    Bone Bones_65;
    Bone Bones_66;
    Bone Bones_67;
    Bone Bones_68;
    Bone Bones_69;
    BoneCapsule BoneCapsules_0;
    BoneCapsule BoneCapsules_1;
    BoneCapsule BoneCapsules_2;
    BoneCapsule BoneCapsules_3;
    BoneCapsule BoneCapsules_4;
    BoneCapsule BoneCapsules_5;
    BoneCapsule BoneCapsules_6;
    BoneCapsule BoneCapsules_7;
    BoneCapsule BoneCapsules_8;
    BoneCapsule BoneCapsules_9;
    BoneCapsule BoneCapsules_10;
    BoneCapsule BoneCapsules_11;
    BoneCapsule BoneCapsules_12;
    BoneCapsule BoneCapsules_13;
    BoneCapsule BoneCapsules_14;
    BoneCapsule BoneCapsules_15;
    BoneCapsule BoneCapsules_16;
    BoneCapsule BoneCapsules_17;
    BoneCapsule BoneCapsules_18;
} Skeleton2Internal;

typedef enum EventType_
{
    EventType_Unknown = 0,
    DisplayRefreshRateChanged = 1,

    SpatialAnchorCreateComplete = 49,
    SpaceSetComponentStatusComplete = 50,
    SpaceQueryResults = 51,
    SpaceQueryComplete = 52,
    SpaceSaveComplete = 53,
    SpaceEraseComplete = 54,


    SceneCaptureComplete = 100,
} EventType;

typedef struct EventDataBuffer_
{
    EventType EventType;
    unsigned char *EventData;
} EventDataBuffer;

typedef enum XrApi_
{
    XrApi_Unknown = 0,
    CAPI = 1,
    VRAPI = 2,
    OpenXR = 3,
    XrApi_EnumSize = 0x7fffffff
} XrApi;

typedef enum PlatformCameraMode_
{
    PlatformCameraMode_Disabled = -1,
    Initialized = 0,
    UserControlled = 1,
    SmartNavigated = 2,
    StabilizedPoV = 3,
    RemoteDroneControlled = 4,
    RemoteSpatialMapped = 5,
    SpectatorMode = 6,
    MobileMRC = 7,
    PlatformCameraMode_EnumSize = 0x7fffffff
} PlatformCameraMode;

typedef struct Colorf_
{
    float r;
    float g;
    float b;
    float a;
} Colorf;

typedef enum InsightPassthroughStyleFlags_
{
    HasTextureOpacityFactor = 1 << 0,
    HasEdgeColor = 1 << 1,
    HasTextureColorMap = 1 << 2
} InsightPassthroughStyleFlags;


typedef enum InsightPassthroughColorMapType_
{
    InsightPassthroughColorMapType_None = 0,
    MonoToRgba = 1,
    MonoToMono = 2,
    BrightnessContrastSaturation = 4,
} InsightPassthroughColorMapType;

typedef struct InsightPassthroughStyle_
{
    InsightPassthroughStyleFlags Flags;
    float TextureOpacityFactor;
    Colorf EdgeColor;
    InsightPassthroughColorMapType TextureColorMapType;
    uint TextureColorMapDataSize;
    intptr_t TextureColorMapData;
} InsightPassthroughStyle;

typedef struct Matrix4x4_
{
    float data[16];
} Matrix4x4;

typedef struct RenderModelPropertiesInternal_
{
    unsigned char* ModelName;
    uint64_t ModelKey;
    uint VendorId;
    uint ModelVersion;
} RenderModelPropertiesInternal;

typedef struct InsightPassthroughKeyboardHandsIntensity_
{
    float LeftHandIntensity;
    float RightHandIntensity;
} InsightPassthroughKeyboardHandsIntensity;

typedef enum TrackedKeyboardQueryFlags_
{
    TrackedKeyboardQueryFlags_Local = 2,
    TrackedKeyboardQueryFlags_Remote = 4,
} TrackedKeyboardQueryFlags;

typedef enum TrackedKeyboardFlags_
{
    TrackedKeyboardFlags_Exists = 1,
    TrackedKeyboardFlags_Local = 2,
    TrackedKeyboardFlags_Remote = 4,
    TrackedKeyboardFlags_Connected = 8,
} TrackedKeyboardFlags;

typedef enum TrackedKeyboardPresentationStyles_
{
    TrackedKeyboardPresentationStyles_Unknown = 0,
    TrackedKeyboardPresentationStyles_Opaque = 1,
    TrackedKeyboardPresentationStyles_KeyLabel = 2,
} TrackedKeyboardPresentationStyles;

typedef struct KeyboardDescription_
{
    char *Name;
    uint64_t TrackedKeyboardId;
    Vector3f Dimensions;
    TrackedKeyboardFlags KeyboardFlags;
    TrackedKeyboardPresentationStyles SupportedPresentationStyles;
} KeyboardDescription;

typedef struct Vector4f_
{
    float x;
    float y;
    float z;
    float w;
} Vector4f;

typedef struct KeyboardState_
{
    bool IsActive;
    bool OrientationValid;
    bool PositionValid;
    bool OrientationTracked;
    bool PositionTracked;
    PoseStatef PoseState;
    Vector4f ContrastParameters;
} KeyboardState;

typedef enum LogLevel_
{
    Debug = 0,
    Info = 1,
    Error = 2
} LogLevel;

typedef void (*LogCallback2DelegateType)(LogLevel, intptr_t, int32_t);

typedef enum ProcessorPerformanceLevel
{
    PowerSavings = 0,
    SustainedLow = 1,
    SustainedHigh = 2,
    Boost = 3,
    ProcessorPerformanceLevel_EnumSize = 0x7FFFFFFF
} ProcessorPerformanceLevel;

typedef struct SpatialAnchorCreateInfo_
{
    TrackingOrigin BaseTracking;
    Posef PoseInSpace;
    double Time;
} SpatialAnchorCreateInfo;

typedef enum SpaceComponentType_
{
    Locatable = 0,
    Storable = 1,
    Bounded2D = 3,
    Bounded3D = 4,
    SemanticLabels = 5,
    RoomLayout = 6,
    SpaceContainer = 7,
} SpaceComponentType;

typedef enum SpaceStorageLocation_
{
    SpaceStorageLocation_Invalid = 0,
    SpaceStorageLocation_Local = 1,
} SpaceStorageLocation;

typedef enum SpaceStoragePersistenceMode_
{
    SpaceStoragePersistenceMode_Invalid = 0,
    SpaceStoragePersistenceMode_Indefinite = 1
} SpaceStoragePersistenceMode;

typedef enum SpaceQueryType_
{
    Action = 0
} SpaceQueryType;

typedef enum SpaceQueryActionType_
{
    Load = 0,
} SpaceQueryActionType;

typedef enum SpaceQueryFilterType_
{
    SpaceQueryFilterType_None = 0,
    SpaceQueryFilterType_Ids = 1,
    SpaceQueryFilterType_Components = 2,
} SpaceQueryFilterType;

typedef struct Guid_
{
    uint32_t Data1;
    uint16_t Data2;
    uint16_t Data3;
    uint8_t Data4[8];
} Guid;

typedef struct SpaceFilterInfoIds_
{
    Guid *Ids;
    int NumIds;
} SpaceFilterInfoIds;

typedef struct SpaceFilterInfoComponents_
{
    SpaceComponentType *Components;
    int NumComponents;
} SpaceFilterInfoComponents;

typedef struct SpaceQueryInfo_
{
    SpaceQueryType QueryType;
    int MaxQuerySpaces;
    double Timeout;
    SpaceStorageLocation Location;
    SpaceQueryActionType ActionType;
    SpaceQueryFilterType FilterType;
    SpaceFilterInfoIds IdInfo;
    SpaceFilterInfoComponents ComponentsInfo;
} SpaceQueryInfo;

typedef struct SpaceContainerInternal_
{
    int uuidCapacityInput;
    int uuidCountOutput;
    intptr_t uuids;
} SpaceContainerInternal;

typedef struct Size3f_
{
    float w;
    float h;
    float d;
} Size3f;

typedef struct Boundsf_
{
    Vector3f Pos;
    Size3f Size;
} Boundsf;

typedef struct SpaceSemanticLabelInternal_
{
    int byteCapacityInput;
    int byteCountOutput;
    intptr_t labels;
} SpaceSemanticLabelInternal;

typedef struct RoomLayoutInternal_
{
    Guid floorUuid;
    Guid ceilingUuid;
    int wallUuidCapacityInput;
    int wallUuidCountOutput;
    intptr_t wallUuids;
} RoomLayoutInternal;

typedef struct PolygonalBoundary2DInternal_
{
    int vertexCapacityInput;
    int vertexCountOutput;
    intptr_t vertices;
} PolygonalBoundary2DInternal;

typedef struct SceneCaptureRequestInternal_
{
    int requestByteCount;
    char *request;
} SceneCaptureRequestInternal;

//Nowhere to be found?
/*typedef struct RenderAPIType_
{

} RenderAPIType;*/

#endif