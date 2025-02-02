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


typedef enum Node_
{
    Node_None = -1,
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
    ControllerLeft = 12,
    ControllerRight = 13,
    Node_Count,
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

typedef enum RawButton_
{
    RawButton_None                      = 0,          ///< Maps to Physical Button: [Gamepad, Touch, LTouch, RTouch, Remote: None]
    RawButton_A                         = 0x00000001, ///< Maps to Physical Button: [Gamepad, Touch, RTouch: A], [LTouch, Remote: None]
    RawButton_B                         = 0x00000002, ///< Maps to Physical Button: [Gamepad, Touch, RTouch: B], [LTouch, Remote: None]
    RawButton_X                         = 0x00000100, ///< Maps to Physical Button: [Gamepad, Touch, LTouch: X], [RTouch, Remote: None]
    RawButton_Y                         = 0x00000200, ///< Maps to Physical Button: [Gamepad, Touch, LTouch: Y], [RTouch, Remote: None]
    RawButton_Start                     = 0x00100000, ///< Maps to Physical Button: [Gamepad, Touch, LTouch, Remote: Start], [RTouch: None]
    RawButton_Back                      = 0x00200000, ///< Maps to Physical Button: [Gamepad, Remote: Back], [Touch, LTouch, RTouch: None]
    RawButton_LShoulder                 = 0x00000800, ///< Maps to Physical Button: [Gamepad: LShoulder], [Touch, LTouch, RTouch, Remote: None]
    RawButton_LIndexTrigger             = 0x10000000, ///< Maps to Physical Button: [Gamepad, Touch, LTouch: LIndexTrigger], [RTouch, Remote: None]
    RawButton_LHandTrigger              = 0x20000000, ///< Maps to Physical Button: [Touch, LTouch: LHandTrigger], [Gamepad, RTouch, Remote: None]
    RawButton_LThumbstick               = 0x00000400, ///< Maps to Physical Button: [Gamepad, Touch, LTouch: LThumbstick], [RTouch, Remote: None]
    RawButton_LThumbstickUp             = 0x00000010, ///< Maps to Physical Button: [Gamepad, Touch, LTouch: LThumbstickUp], [RTouch, Remote: None]
    RawButton_LThumbstickDown           = 0x00000020, ///< Maps to Physical Button: [Gamepad, Touch, LTouch: LThumbstickDown], [RTouch, Remote: None]
    RawButton_LThumbstickLeft           = 0x00000040, ///< Maps to Physical Button: [Gamepad, Touch, LTouch: LThumbstickLeft], [RTouch, Remote: None]
    RawButton_LThumbstickRight          = 0x00000080, ///< Maps to Physical Button: [Gamepad, Touch, LTouch: LThumbstickRight], [RTouch, Remote: None]
    RawButton_LTouchpad                 = 0x40000000, ///< Maps to Physical Button: [Gamepad, Touch, LTouch, RTouch, Remote: None]
    RawButton_RShoulder                 = 0x00000008, ///< Maps to Physical Button: [Gamepad: RShoulder], [Touch, LTouch, RTouch, Remote: None]
    RawButton_RIndexTrigger             = 0x04000000, ///< Maps to Physical Button: [Gamepad, Touch, RTouch: RIndexTrigger], [LTouch, Remote: None]
    RawButton_RHandTrigger              = 0x08000000, ///< Maps to Physical Button: [Touch, RTouch: RHandTrigger], [Gamepad, LTouch, Remote: None]
    RawButton_RThumbstick               = 0x00000004, ///< Maps to Physical Button: [Gamepad, Touch, RTouch: RThumbstick], [LTouch, Remote: None]
    RawButton_RThumbstickUp             = 0x00001000, ///< Maps to Physical Button: [Gamepad, Touch, RTouch: RThumbstickUp], [LTouch, Remote: None]
    RawButton_RThumbstickDown           = 0x00002000, ///< Maps to Physical Button: [Gamepad, Touch, RTouch: RThumbstickDown], [LTouch, Remote: None]
    RawButton_RThumbstickLeft           = 0x00004000, ///< Maps to Physical Button: [Gamepad, Touch, RTouch: RThumbstickLeft], [LTouch, Remote: None]
    RawButton_RThumbstickRight          = 0x00008000, ///< Maps to Physical Button: [Gamepad, Touch, RTouch: RThumbstickRight], [LTouch, Remote: None]
    RawButton_RTouchpad  = 0x80000000,///< Maps to Physical Button: [Gamepad, Touch, LTouch, RTouch, Remote: None]
    RawButton_DpadUp                    = 0x00010000, ///< Maps to Physical Button: [Gamepad, Remote: DpadUp], [Touch, LTouch, RTouch: None]
    RawButton_DpadDown                  = 0x00020000, ///< Maps to Physical Button: [Gamepad, Remote: DpadDown], [Touch, LTouch, RTouch: None]
    RawButton_DpadLeft                  = 0x00040000, ///< Maps to Physical Button: [Gamepad, Remote: DpadLeft], [Touch, LTouch, RTouch: None]
    RawButton_DpadRight                 = 0x00080000, ///< Maps to Physical Button: [Gamepad, Remote: DpadRight], [Touch, LTouch, RTouch: None]
    RawButton_Any                       = ~RawButton_None,      ///< Maps to Physical Button: [Gamepad, Touch, LTouch, RTouch, Remote: Any]
} RawButton;

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
    Button_Right      =                0x80000000,///< Maps to RawButton: [Gamepad, Touch, LTouch: LThumbstickRight], [RTouch: RThumbstickRight], [Remote: DpadRight]
    Button_Any                       = ~Button_None,      ///< Maps to RawButton: [Gamepad, Touch, LTouch, RTouch: Any]
} Button;

typedef struct ControllerState_
{
    uint32_t ConnectedControllers;
    uint32_t Buttons;
    uint32_t Touches;
    uint32_t NearTouches;
    float LIndexTrigger;
    float RIndexTrigger;
    float LHandTrigger;
    float RHandTrigger;
    Vector2f LThumbstick;
    Vector2f RThumbstick;
} ControllerState;

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
    int SampleSizeInchars;
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

    LTrackedRemote     = 0x01000000,
    RTrackedRemote     = 0x02000000,
    Touchpad           = 0x08000000,

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
    R8G8B8A8_sRGB = 0,
    R8G8B8A8 = 1,
    R16G16B16A16_FP = 2,
    R11G11B10_FP = 3,
    B8G8R8A8_sRGB = 4,
    B8G8R8A8 = 5,
    R5G6B5 = 11,
    EyeTextureFormat_EnumSize = 0x7fffffff
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
    uint32_t ConnectedControllers;
    uint32_t Buttons;
    uint32_t Touches;
    uint32_t NearTouches;
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
    uint32_t ConnectedControllers;
    uint32_t Buttons;
    uint32_t Touches;
    uint32_t NearTouches;
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
    int charCapacityInput;
    int charCountOutput;
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
    int requestcharCount;
    char *request;
} SceneCaptureRequestInternal;

typedef enum RenderAPIType_
{
    ovrRenderAPI_None,
    ovrRenderAPI_OpenGL,
    ovrRenderAPI_Android_GLES,  // May include extra native window pointers, etc.
    ovrRenderAPI_D3D9,
    ovrRenderAPI_D3D10,
    ovrRenderAPI_D3D11,
    ovrRenderAPI_Vulkan,
    ovrRenderAPI_Count
} RenderAPIType;

typedef enum RenderModelFlags_
{
    SupportsGltf20Subset1 = 1,
    SupportsGltf20Subset2 = 2,
} RenderModelFlags;

typedef enum PassthroughCapabilityFlags_
{
    Passthrough = 1 << 0,
    Color       = 1 << 1,
    Depth       = 1 << 2
} PassthroughCapabilityFlags;

typedef enum SpaceLocationFlags_
{
    /// <summary>
    /// Indicates that the pose field's orientation field contains valid data.
    /// </summary>
    /// <remarks>
    /// Applications must not read a pose field's orientation if this flag is unset.
    /// </remarks>
    OrientationValid = 0x00000001,

    /// <summary>
    /// Indicates that the pose field's position field contains valid data.
    /// </summary>
    /// <remarks>
    /// Applications must not read a pose field's position if this flag is unset.
    /// </remarks>
    PositionValid = 0x00000002,

    /// <summary>
    /// Indicates that a pose field's orientation field represents an actively tracked orientation.
    /// </summary>
    /// <remarks>
    /// When a space location tracking an object whose orientation is no longer known during tracking loss
    /// (e.g. an observed QR code), the orientation will be a valid but untracked orientation and will be
    /// meaningful to use.
    /// </remarks>
    OrientationTracked = 0x00000004,

    /// <summary>
    /// Indicates that a pose field's position field represents an actively tracked position.
    /// </summary>
    /// <remarks>
    /// When a space location loses tracking, the position will be a valid but untracked value that is inferred or
    /// last-known, e.g. based on neck model updates, inertial dead reckoning, or a last-known position, and will be
    /// meaningful to use.
    /// </remarks>
    PositionTracked = 0x00000008,
} SpaceLocationFlags;

typedef struct BodyJointLocation_
{
    /// <summary>
    /// The <see cref="SpaceLocationFlags"/> for this <see cref="BodyJointLocation"/>.
    /// </summary>
    SpaceLocationFlags LocationFlags;

    /// <summary>
    /// The pose of this <see cref="BodyJointLocation"/>.
    /// </summary>
    Posef Pose;

    /// <summary>
    /// Indicates that the <see cref="Pose"/>'s <see cref="Posef.Orientation"/> contains valid data.
    /// </summary>
    bool OrientationValid;// = (LocationFlags & SpaceLocationFlags.OrientationValid) != 0;

    /// <summary>
    /// Indicates that the <see cref="Pose"/>'s <see cref="Posef.Position"/> contains valid data.
    /// </summary>
    bool PositionValid;// = (LocationFlags & SpaceLocationFlags.PositionValid) != 0;

    /// <summary>
    /// Indicates that the <see cref="Pose"/>'s <see cref="Posef.Orientation"/> represents an actively tracked
    /// orientation.
    /// </summary>
    bool OrientationTracked;// = (LocationFlags & SpaceLocationFlags.OrientationTracked) != 0;

    /// <summary>
    /// Indicates that the <see cref="Pose"/>'s <see cref="Posef.Position"/> represents an actively tracked
    /// position.
    /// </summary>
    bool PositionTracked;// = (LocationFlags & SpaceLocationFlags.PositionTracked) != 0;
} BodyJointLocation;

typedef struct BodyStateInternal_
{
    bool IsActive;
    float Confidence;
    uint64_t SkeletonChangedCount;
    double Time;
    BodyJointLocation JointLocation_0;
    BodyJointLocation JointLocation_1;
    BodyJointLocation JointLocation_2;
    BodyJointLocation JointLocation_3;
    BodyJointLocation JointLocation_4;
    BodyJointLocation JointLocation_5;
    BodyJointLocation JointLocation_6;
    BodyJointLocation JointLocation_7;
    BodyJointLocation JointLocation_8;
    BodyJointLocation JointLocation_9;
    BodyJointLocation JointLocation_10;
    BodyJointLocation JointLocation_11;
    BodyJointLocation JointLocation_12;
    BodyJointLocation JointLocation_13;
    BodyJointLocation JointLocation_14;
    BodyJointLocation JointLocation_15;
    BodyJointLocation JointLocation_16;
    BodyJointLocation JointLocation_17;
    BodyJointLocation JointLocation_18;
    BodyJointLocation JointLocation_19;
    BodyJointLocation JointLocation_20;
    BodyJointLocation JointLocation_21;
    BodyJointLocation JointLocation_22;
    BodyJointLocation JointLocation_23;
    BodyJointLocation JointLocation_24;
    BodyJointLocation JointLocation_25;
    BodyJointLocation JointLocation_26;
    BodyJointLocation JointLocation_27;
    BodyJointLocation JointLocation_28;
    BodyJointLocation JointLocation_29;
    BodyJointLocation JointLocation_30;
    BodyJointLocation JointLocation_31;
    BodyJointLocation JointLocation_32;
    BodyJointLocation JointLocation_33;
    BodyJointLocation JointLocation_34;
    BodyJointLocation JointLocation_35;
    BodyJointLocation JointLocation_36;
    BodyJointLocation JointLocation_37;
    BodyJointLocation JointLocation_38;
    BodyJointLocation JointLocation_39;
    BodyJointLocation JointLocation_40;
    BodyJointLocation JointLocation_41;
    BodyJointLocation JointLocation_42;
    BodyJointLocation JointLocation_43;
    BodyJointLocation JointLocation_44;
    BodyJointLocation JointLocation_45;
    BodyJointLocation JointLocation_46;
    BodyJointLocation JointLocation_47;
    BodyJointLocation JointLocation_48;
    BodyJointLocation JointLocation_49;
    BodyJointLocation JointLocation_50;
    BodyJointLocation JointLocation_51;
    BodyJointLocation JointLocation_52;
    BodyJointLocation JointLocation_53;
    BodyJointLocation JointLocation_54;
    BodyJointLocation JointLocation_55;
    BodyJointLocation JointLocation_56;
    BodyJointLocation JointLocation_57;
    BodyJointLocation JointLocation_58;
    BodyJointLocation JointLocation_59;
    BodyJointLocation JointLocation_60;
    BodyJointLocation JointLocation_61;
    BodyJointLocation JointLocation_62;
    BodyJointLocation JointLocation_63;
    BodyJointLocation JointLocation_64;
    BodyJointLocation JointLocation_65;
    BodyJointLocation JointLocation_66;
    BodyJointLocation JointLocation_67;
    BodyJointLocation JointLocation_68;
    BodyJointLocation JointLocation_69;
} BodyStateInternal;

typedef struct FaceExpressionStatusInternal_
{
    bool IsValid;
    bool IsEyeFollowingBlendshapesValid;
} FaceExpressionStatusInternal;

typedef struct FaceStateInternal_
{
    float ExpressionWeights_0;
    float ExpressionWeights_1;
    float ExpressionWeights_2;
    float ExpressionWeights_3;
    float ExpressionWeights_4;
    float ExpressionWeights_5;
    float ExpressionWeights_6;
    float ExpressionWeights_7;
    float ExpressionWeights_8;
    float ExpressionWeights_9;
    float ExpressionWeights_10;
    float ExpressionWeights_11;
    float ExpressionWeights_12;
    float ExpressionWeights_13;
    float ExpressionWeights_14;
    float ExpressionWeights_15;
    float ExpressionWeights_16;
    float ExpressionWeights_17;
    float ExpressionWeights_18;
    float ExpressionWeights_19;
    float ExpressionWeights_20;
    float ExpressionWeights_21;
    float ExpressionWeights_22;
    float ExpressionWeights_23;
    float ExpressionWeights_24;
    float ExpressionWeights_25;
    float ExpressionWeights_26;
    float ExpressionWeights_27;
    float ExpressionWeights_28;
    float ExpressionWeights_29;
    float ExpressionWeights_30;
    float ExpressionWeights_31;
    float ExpressionWeights_32;
    float ExpressionWeights_33;
    float ExpressionWeights_34;
    float ExpressionWeights_35;
    float ExpressionWeights_36;
    float ExpressionWeights_37;
    float ExpressionWeights_38;
    float ExpressionWeights_39;
    float ExpressionWeights_40;
    float ExpressionWeights_41;
    float ExpressionWeights_42;
    float ExpressionWeights_43;
    float ExpressionWeights_44;
    float ExpressionWeights_45;
    float ExpressionWeights_46;
    float ExpressionWeights_47;
    float ExpressionWeights_48;
    float ExpressionWeights_49;
    float ExpressionWeights_50;
    float ExpressionWeights_51;
    float ExpressionWeights_52;
    float ExpressionWeights_53;
    float ExpressionWeights_54;
    float ExpressionWeights_55;
    float ExpressionWeights_56;
    float ExpressionWeights_57;
    float ExpressionWeights_58;
    float ExpressionWeights_59;
    float ExpressionWeights_60;
    float ExpressionWeights_61;
    float ExpressionWeights_62;
    float ExpressionWeightConfidences_0;
    float ExpressionWeightConfidences_1;
    FaceExpressionStatusInternal Status;
    double Time;
} FaceStateInternal;

typedef struct EyeGazeState_
{
    Posef Pose;
    float Confidence;
    bool IsValid;
} EyeGazeState;

typedef struct EyeGazesStateInternal_
{
    EyeGazeState EyeGazes_0;
    EyeGazeState EyeGazes_1;
    double Time;
} EyeGazesStateInternal;

typedef struct ControllerState5_
{
    uint32_t ConnectedControllers;
    uint32_t Buttons;
    uint32_t Touches;
    uint32_t NearTouches;
    float LIndexTrigger;
    float RIndexTrigger;
    float LHandTrigger;
    float RHandTrigger;
    Vector2f LThumbstick;
    Vector2f RThumbstick;
    Vector2f LTouchpad;
    Vector2f RTouchpad;
    char LBatteryPercentRemaining;
    char RBatteryPercentRemaining;
    char LRecenterCount;
    char RRecenterCount;
    float LThumbRestForce;
    float RThumbRestForce;
    float LStylusForce;
    float RStylusForce;
    float LIndexTriggerCurl;
    float RIndexTriggerCurl;
    float LIndexTriggerSlide;
    float RIndexTriggerSlide;
} ControllerState5;


typedef enum HapticsLocation_
{
    HapticsLocation_None = 0x00,
    HapticsLocation_Hand = 0x01,
    HapticsLocation_Thumb = 0x02,
    HapticsLocation_Index = 0x04,
} HapticsLocation;


typedef enum InteractionProfile
{
    InteractionProfile_None = 0,
    InteractionProfile_Touch = 1,
    InteractionProfile_TouchPro = 2,
} InteractionProfile;

typedef struct HapticsAmplitudeEnvelopeVibration_
{
    float Duration;
    uint32_t AmplitudeCount;
    intptr_t Amplitudes;
} HapticsAmplitudeEnvelopeVibration;

typedef struct HapticsPcmVibration_
{
    uint32_t BufferSize;
    intptr_t Buffer;
    float SampleRateHz;
    bool Append;
    uint32_t SamplesConsumed;
} HapticsPcmVibration;

typedef struct SpaceLocationf_
{
    SpaceLocationFlags locationFlags;
    Posef pose;
} SpaceLocationf;

typedef struct TriangleMeshInternal_
{
    int vertexCapacityInput;
    int vertexCountOutput;
    intptr_t vertices;
    int indexCapacityInput;
    int indexCountOutput;
    intptr_t indices;
} TriangleMeshInternal;

typedef struct ControllerState6_
{
    uint32_t ConnectedControllers;
    uint32_t Buttons;
    uint32_t Touches;
    uint32_t NearTouches;
    float LIndexTrigger;
    float RIndexTrigger;
    float LHandTrigger;
    float RHandTrigger;
    Vector2f LThumbstick;
    Vector2f RThumbstick;
    Vector2f LTouchpad;
    Vector2f RTouchpad;
    char LBatteryPercentRemaining;
    char RBatteryPercentRemaining;
    char LRecenterCount;
    char RRecenterCount;
    float LThumbRestForce;
    float RThumbRestForce;
    float LStylusForce;
    float RStylusForce;
    float LIndexTriggerCurl;
    float RIndexTriggerCurl;
    float LIndexTriggerSlide;
    float RIndexTriggerSlide;
    float LIndexTriggerForce;
    float RIndexTriggerForce;
} ControllerState6;

typedef enum RawTouch_
{
    RawTouch_None                      = 0,                            ///< Maps to Physical Touch: [Gamepad, Touch, LTouch, RTouch, Remote: None]
    RawTouch_A                         = RawButton_A,                  ///< Maps to Physical Touch: [Touch, RTouch: A], [Gamepad, LTouch, Remote: None]
    RawTouch_B                         = RawButton_B,                  ///< Maps to Physical Touch: [Touch, RTouch: B], [Gamepad, LTouch, Remote: None]
    RawTouch_X                         = RawButton_X,                  ///< Maps to Physical Touch: [Touch, LTouch: X], [Gamepad, RTouch, Remote: None]
    RawTouch_Y                         = RawButton_Y,                  ///< Maps to Physical Touch: [Touch, LTouch: Y], [Gamepad, RTouch, Remote: None]
    RawTouch_LIndexTrigger             = 0x00001000,                   ///< Maps to Physical Touch: [Touch, LTouch: LIndexTrigger], [Gamepad, RTouch, Remote: None]
    RawTouch_LThumbstick               = RawButton_LThumbstick,        ///< Maps to Physical Touch: [Touch, LTouch: LThumbstick], [Gamepad, RTouch, Remote: None]
    RawTouch_LThumbRest                = 0x00000800,                   ///< Maps to Physical Touch: [Touch, LTouch: LThumbRest], [Gamepad, RTouch, Remote: None]
    RawTouch_LTouchpad                 = RawButton_LTouchpad,          ///< Maps to Physical Touch: [Gamepad, Touch, LTouch, RTouch, Remote: None]
    RawTouch_RIndexTrigger             = 0x00000010,                   ///< Maps to Physical Touch: [Touch, RTouch: RIndexTrigger], [Gamepad, LTouch, Remote: None]
    RawTouch_RThumbstick               = RawButton_RThumbstick,        ///< Maps to Physical Touch: [Touch, RTouch: RThumbstick], [Gamepad, LTouch, Remote: None]
    RawTouch_RThumbRest                = 0x00000008,                   ///< Maps to Physical Touch: [Touch, RTouch: RThumbRest], [Gamepad, LTouch, Remote: None]
    RawTouch_RTouchpad                 = RawButton_RTouchpad,          ///< Maps to Physical Touch: [Gamepad, Touch, LTouch, RTouch, Remote: None]
    RawTouch_Any                       = ~RawTouch_None,                        ///< Maps to Physical Touch: [Touch, LTouch, RTouch: Any], [Gamepad, Remote: None]
} RawTouch;

typedef enum RawNearTouch_
{
    RawNearTouch_None                      = 0,          ///< Maps to Physical NearTouch: [Gamepad, Touch, LTouch, RTouch, Remote: None]
    RawNearTouch_LIndexTrigger             = 0x00000001, ///< Maps to Physical NearTouch: [Touch, LTouch: Implies finger is in close proximity to LIndexTrigger.], [Gamepad, RTouch, Remote: None]
    RawNearTouch_LThumbButtons             = 0x00000002, ///< Maps to Physical NearTouch: [Touch, LTouch: Implies thumb is in close proximity to LThumbstick OR X/Y buttons.], [Gamepad, RTouch, Remote: None]
    RawNearTouch_RIndexTrigger             = 0x00000004, ///< Maps to Physical NearTouch: [Touch, RTouch: Implies finger is in close proximity to RIndexTrigger.], [Gamepad, LTouch, Remote: None]
    RawNearTouch_RThumbButtons             = 0x00000008, ///< Maps to Physical NearTouch: [Touch, RTouch: Implies thumb is in close proximity to RThumbstick OR A/B buttons.], [Gamepad, LTouch, Remote: None]
    RawNearTouch_Any                       = ~RawNearTouch_None,      ///< Maps to Physical NearTouch: [Touch, LTouch, RTouch: Any], [Gamepad, Remote: None]
} RawNearTouch;

typedef struct VirtualKeyboardModelAnimationStatesInternal_
{
    uint32_t StateCapacityInput;
    uint32_t StateCountOutput;
    intptr_t StatesBuffer;
} VirtualKeyboardModelAnimationStatesInternal;

typedef struct VirtualKeyboardTextureIdsInternal_
{
    uint32_t TextureIdCapacityInput;
    uint32_t TextureIdCountOutput;
    intptr_t TextureIdsBuffer;
} VirtualKeyboardTextureIdsInternal;

typedef struct VirtualKeyboardTextureData_
{
    uint32_t TextureWidth;
    uint32_t TextureHeight;
    uint32_t BufferCapacityInput;
    uint32_t BufferCountOutput;
    intptr_t Buffer;
} VirtualKeyboardTextureData;

typedef struct VirtualKeyboardModelVisibility_
{
    bool Visible;
} VirtualKeyboardModelVisibility;

typedef enum PassthroughColorLutChannels_
{
    Rgb = 1,
    Rgba = 2
} PassthroughColorLutChannels;

typedef struct PassthroughColorLutData_
{
    uint32_t BufferSize;
    intptr_t Buffer;
} PassthroughColorLutData;

typedef struct InsightPassthroughStyle2_
{
    InsightPassthroughStyleFlags Flags;
    float TextureOpacityFactor;
    Colorf EdgeColor;
    InsightPassthroughColorMapType TextureColorMapType;
    uint32_t TextureColorMapDataSize;
    intptr_t TextureColorMapData;
    uint64_t LutSource;
    uint64_t LutTarget;
    float LutWeight;
} InsightPassthroughStyle2;

typedef enum QplResultType_
{
    QplResultType_Success = 2,
    QplResultType_Fail = 3,
    QplResultType_Cancel = 4
} QplResultType;

typedef enum PassthroughCapabilityFields_
{
    Flags = 1 << 0,
    MaxColorLutResolution = 1 << 1,
} PassthroughCapabilityFields;

typedef struct PassthroughCapabilities_
{
    PassthroughCapabilityFields Fields;
    PassthroughCapabilityFlags Flags;
    uint32_t MaxColorLutResolution;
} PassthroughCapabilities;

typedef enum PassthroughPreferenceFields_
{
    PassthroughPreferenceFields_Flags = 1 << 0
} PassthroughPreferenceFields;

typedef enum PassthroughPreferenceFlags_
{
    DefaultToActive = 1 << 0
} PassthroughPreferenceFlags;

typedef struct PassthroughPreferences_
{
    PassthroughPreferenceFields Fields;
    PassthroughPreferenceFlags Flags;
} PassthroughPreferences;

typedef enum LayerSharpenType_
{
    LayerSharpenType_None = 0,
    LayerSharpenType_Normal = 1 << 13,
    LayerSharpenType_Quality = 1 << 16,
    LayerSharpenType_Automatic = 1 << 18,
} LayerSharpenType;

typedef struct FaceExpressionStatus_
{
    bool IsValid;
    bool IsEyeFollowingBlendshapesValid;
} FaceExpressionStatus;

typedef enum FaceTrackingDataSource_
{
    Visual = 0,
    Audio = 1,
    FaceTrackingDataSource_Count = 2,
} FaceTrackingDataSource;

typedef struct FaceState_
{
    float *ExpressionWeights;
    float *ExpressionWeightConfidences;
    FaceExpressionStatus Status;
    FaceTrackingDataSource DataSource;
    double Time;
} FaceState;

typedef struct FaceState2Internal_
{
    float ExpressionWeights_0;
    float ExpressionWeights_1;
    float ExpressionWeights_2;
    float ExpressionWeights_3;
    float ExpressionWeights_4;
    float ExpressionWeights_5;
    float ExpressionWeights_6;
    float ExpressionWeights_7;
    float ExpressionWeights_8;
    float ExpressionWeights_9;
    float ExpressionWeights_10;
    float ExpressionWeights_11;
    float ExpressionWeights_12;
    float ExpressionWeights_13;
    float ExpressionWeights_14;
    float ExpressionWeights_15;
    float ExpressionWeights_16;
    float ExpressionWeights_17;
    float ExpressionWeights_18;
    float ExpressionWeights_19;
    float ExpressionWeights_20;
    float ExpressionWeights_21;
    float ExpressionWeights_22;
    float ExpressionWeights_23;
    float ExpressionWeights_24;
    float ExpressionWeights_25;
    float ExpressionWeights_26;
    float ExpressionWeights_27;
    float ExpressionWeights_28;
    float ExpressionWeights_29;
    float ExpressionWeights_30;
    float ExpressionWeights_31;
    float ExpressionWeights_32;
    float ExpressionWeights_33;
    float ExpressionWeights_34;
    float ExpressionWeights_35;
    float ExpressionWeights_36;
    float ExpressionWeights_37;
    float ExpressionWeights_38;
    float ExpressionWeights_39;
    float ExpressionWeights_40;
    float ExpressionWeights_41;
    float ExpressionWeights_42;
    float ExpressionWeights_43;
    float ExpressionWeights_44;
    float ExpressionWeights_45;
    float ExpressionWeights_46;
    float ExpressionWeights_47;
    float ExpressionWeights_48;
    float ExpressionWeights_49;
    float ExpressionWeights_50;
    float ExpressionWeights_51;
    float ExpressionWeights_52;
    float ExpressionWeights_53;
    float ExpressionWeights_54;
    float ExpressionWeights_55;
    float ExpressionWeights_56;
    float ExpressionWeights_57;
    float ExpressionWeights_58;
    float ExpressionWeights_59;
    float ExpressionWeights_60;
    float ExpressionWeights_61;
    float ExpressionWeights_62;
    float ExpressionWeights_63;
    float ExpressionWeights_64;
    float ExpressionWeights_65;
    float ExpressionWeights_66;
    float ExpressionWeights_67;
    float ExpressionWeights_68;
    float ExpressionWeights_69;
    float ExpressionWeightConfidences_0;
    float ExpressionWeightConfidences_1;
    FaceExpressionStatusInternal Status;
    FaceTrackingDataSource DataSource;
    double Time;
} FaceState2Internal;

typedef enum BodyTrackingFidelity2_
{
    BodyTrackingFidelity2_Low = 1,
    BodyTrackingFidelity2_High = 2
} BodyTrackingFidelity2;

typedef struct BodyTrackingCalibrationInfo_
{
    float BodyHeight;
} BodyTrackingCalibrationInfo;

typedef enum BodyTrackingCalibrationState_
{
    BodyTrackingCalibrationState_Valid = 1,
    BodyTrackingCalibrationState_Calibrating = 2,
    BodyTrackingCalibrationState_Invalid = 3
} BodyTrackingCalibrationState;

typedef struct BodyState4Internal_
{
    bool IsActive;
    float Confidence;
    uint32_t SkeletonChangedCount;
    double Time;
    BodyJointLocation JointLocation_0;
    BodyJointLocation JointLocation_1;
    BodyJointLocation JointLocation_2;
    BodyJointLocation JointLocation_3;
    BodyJointLocation JointLocation_4;
    BodyJointLocation JointLocation_5;
    BodyJointLocation JointLocation_6;
    BodyJointLocation JointLocation_7;
    BodyJointLocation JointLocation_8;
    BodyJointLocation JointLocation_9;
    BodyJointLocation JointLocation_10;
    BodyJointLocation JointLocation_11;
    BodyJointLocation JointLocation_12;
    BodyJointLocation JointLocation_13;
    BodyJointLocation JointLocation_14;
    BodyJointLocation JointLocation_15;
    BodyJointLocation JointLocation_16;
    BodyJointLocation JointLocation_17;
    BodyJointLocation JointLocation_18;
    BodyJointLocation JointLocation_19;
    BodyJointLocation JointLocation_20;
    BodyJointLocation JointLocation_21;
    BodyJointLocation JointLocation_22;
    BodyJointLocation JointLocation_23;
    BodyJointLocation JointLocation_24;
    BodyJointLocation JointLocation_25;
    BodyJointLocation JointLocation_26;
    BodyJointLocation JointLocation_27;
    BodyJointLocation JointLocation_28;
    BodyJointLocation JointLocation_29;
    BodyJointLocation JointLocation_30;
    BodyJointLocation JointLocation_31;
    BodyJointLocation JointLocation_32;
    BodyJointLocation JointLocation_33;
    BodyJointLocation JointLocation_34;
    BodyJointLocation JointLocation_35;
    BodyJointLocation JointLocation_36;
    BodyJointLocation JointLocation_37;
    BodyJointLocation JointLocation_38;
    BodyJointLocation JointLocation_39;
    BodyJointLocation JointLocation_40;
    BodyJointLocation JointLocation_41;
    BodyJointLocation JointLocation_42;
    BodyJointLocation JointLocation_43;
    BodyJointLocation JointLocation_44;
    BodyJointLocation JointLocation_45;
    BodyJointLocation JointLocation_46;
    BodyJointLocation JointLocation_47;
    BodyJointLocation JointLocation_48;
    BodyJointLocation JointLocation_49;
    BodyJointLocation JointLocation_50;
    BodyJointLocation JointLocation_51;
    BodyJointLocation JointLocation_52;
    BodyJointLocation JointLocation_53;
    BodyJointLocation JointLocation_54;
    BodyJointLocation JointLocation_55;
    BodyJointLocation JointLocation_56;
    BodyJointLocation JointLocation_57;
    BodyJointLocation JointLocation_58;
    BodyJointLocation JointLocation_59;
    BodyJointLocation JointLocation_60;
    BodyJointLocation JointLocation_61;
    BodyJointLocation JointLocation_62;
    BodyJointLocation JointLocation_63;
    BodyJointLocation JointLocation_64;
    BodyJointLocation JointLocation_65;
    BodyJointLocation JointLocation_66;
    BodyJointLocation JointLocation_67;
    BodyJointLocation JointLocation_68;
    BodyJointLocation JointLocation_69;
    BodyJointLocation JointLocation_70;
    BodyJointLocation JointLocation_71;
    BodyJointLocation JointLocation_72;
    BodyJointLocation JointLocation_73;
    BodyJointLocation JointLocation_74;
    BodyJointLocation JointLocation_75;
    BodyJointLocation JointLocation_76;
    BodyJointLocation JointLocation_77;
    BodyJointLocation JointLocation_78;
    BodyJointLocation JointLocation_79;
    BodyJointLocation JointLocation_80;
    BodyJointLocation JointLocation_81;
    BodyJointLocation JointLocation_82;
    BodyJointLocation JointLocation_83;
    BodyTrackingCalibrationState CalibrationStatus;
    BodyTrackingFidelity2 Fidelity;
} BodyState4Internal;

typedef struct Skeleton3Internal_
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
    Bone Bones_70;
    Bone Bones_71;
    Bone Bones_72;
    Bone Bones_73;
    Bone Bones_74;
    Bone Bones_75;
    Bone Bones_76;
    Bone Bones_77;
    Bone Bones_78;
    Bone Bones_79;
    Bone Bones_80;
    Bone Bones_81;
    Bone Bones_82;
    Bone Bones_83;
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
} Skeleton3Internal;

typedef enum BodyJointSet_
{
    BodyJointSet_None = -1,
    BodyJointSet_UpperBody = 0,
    BodyJointSet_FullBody = 1,
} BodyJointSet;


typedef enum VariantType_
{
    VariantType_None = 0,
    VariantType_String = 1,
    VariantType_Int = 2,
    VariantType_Double = 3,
    VariantType_Bool = 4,
    VariantType_StringArray = 5,
    VariantType_IntArray = 6,
    VariantType_DoubleArray = 7,
    VariantType_BoolArray = 8,
} VariantType;

typedef struct QplVariant_
{
    VariantType Type;
    int Count;
    unsigned long *StringValue;
    long LongValue;
    double DoubleValue;
    bool BoolValue;
    unsigned long **StringValues;
    long *LongValues;
    double *DoubleValues;
    unsigned long *BoolValues;
} QplVariant;

typedef struct QplAnnotation_
{
    char *Key;
    QplVariant Value;
} QplAnnotation;

typedef enum SpaceDiscoveryFilterType
{
    SpaceDiscoveryFilterType_None = 0,
    SpaceDiscoveryFilterType_Ids = 2,
    SpaceDiscoveryFilterType_Component = 3,
} SpaceDiscoveryFilterType;

typedef struct SpaceDiscoveryFilterInfoHeader_
{
    SpaceDiscoveryFilterType Type;
} SpaceDiscoveryFilterInfoHeader;

typedef struct SpaceDiscoveryInfo_
{
    uint32_t NumFilters;
    SpaceDiscoveryFilterInfoHeader** Filters;
} SpaceDiscoveryInfo;

typedef struct SpaceDiscoveryResult_
{
    unsigned long Space;
    Guid Uuid;
} SpaceDiscoveryResult;

typedef struct SpaceDiscoveryResults_
{
    uint32_t ResultCapacityInput;
    uint32_t ResultCountOutput;
    SpaceDiscoveryResult* Results;
} SpaceDiscoveryResults;

#endif