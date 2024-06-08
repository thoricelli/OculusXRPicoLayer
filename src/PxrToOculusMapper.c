#include "../include/PxrEnums.h"
#include "../OVRPlugin.h"
#include "../include/PxrInput.h"

//LAYERS
PxrLayerShape PXRConvertToOverLayShape(OverlayShape layerShape) {
    switch (layerShape) {
        case Quad:
                return PXR_LAYER_QUAD;

        case Cylinder:
                return PXR_LAYER_CYLINDER;

        case OffcenterCubemap:
        case Cubemap:
                return PXR_LAYER_CUBE;

        case Equirect:
            return PXR_LAYER_EQUIRECT;

        default:
            return PXR_LAYER_PROJECTION;
    }
}

PxrLayerLayout PXRConvertToLayerLayout(LayerLayout layer) {
    switch (layer) {
        case Stereo:
            return PXR_LAYER_LAYOUT_STEREO;
        case Mono:
            return PXR_LAYER_LAYOUT_MONO;
        case DoubleWide:
            return PXR_LAYER_LAYOUT_DOUBLE_WIDE;
        case Array:
            return PXR_LAYER_LAYOUT_ARRAY;
        default:
            return PXR_LAYER_LAYOUT_STEREO;
    }
}

Quatf PxrPosefToOVRQuatf(PxrPosef posef) {
    return *((Quatf*)&posef.orientation);
}

HandStateInternal PxrHandStateToOVRHandState(PxrHandState handState) {
    HandStateInternal ovrHandState = {
        .Status = handState.Status,
        .RootPose = *((Posef*)&handState.RootPose),

        .BoneRotations_0 = PxrPosefToOVRQuatf(handState.BonePose[0]),
        .BoneRotations_1 = PxrPosefToOVRQuatf(handState.BonePose[1]),
        .BoneRotations_2 = PxrPosefToOVRQuatf(handState.BonePose[2]),
        .BoneRotations_3 = PxrPosefToOVRQuatf(handState.BonePose[3]),
        .BoneRotations_4 = PxrPosefToOVRQuatf(handState.BonePose[4]),
        .BoneRotations_5 = PxrPosefToOVRQuatf(handState.BonePose[5]),
        .BoneRotations_6 = PxrPosefToOVRQuatf(handState.BonePose[6]),
        .BoneRotations_7 = PxrPosefToOVRQuatf(handState.BonePose[7]),
        .BoneRotations_8 = PxrPosefToOVRQuatf(handState.BonePose[8]),
        .BoneRotations_9 = PxrPosefToOVRQuatf(handState.BonePose[9]),
        .BoneRotations_10 = PxrPosefToOVRQuatf(handState.BonePose[10]),
        .BoneRotations_11 = PxrPosefToOVRQuatf(handState.BonePose[11]),
        .BoneRotations_12 = PxrPosefToOVRQuatf(handState.BonePose[12]),
        .BoneRotations_13 = PxrPosefToOVRQuatf(handState.BonePose[13]),
        .BoneRotations_14 = PxrPosefToOVRQuatf(handState.BonePose[14]),
        .BoneRotations_15 = PxrPosefToOVRQuatf(handState.BonePose[15]),
        .BoneRotations_16 = PxrPosefToOVRQuatf(handState.BonePose[16]),
        .BoneRotations_17 = PxrPosefToOVRQuatf(handState.BonePose[17]),
        .BoneRotations_18 = PxrPosefToOVRQuatf(handState.BonePose[18]),
        .BoneRotations_19 = PxrPosefToOVRQuatf(handState.BonePose[19]),
        .BoneRotations_20 = PxrPosefToOVRQuatf(handState.BonePose[20]),
        .BoneRotations_21 = PxrPosefToOVRQuatf(handState.BonePose[21]),
        .BoneRotations_22 = PxrPosefToOVRQuatf(handState.BonePose[22]),
        .BoneRotations_23 = PxrPosefToOVRQuatf(handState.BonePose[23]),

        .Pinches = handState.Pinches,

        .PinchStrength_0 = handState.PinchStrength[0],
        .PinchStrength_1 = handState.PinchStrength[1],
        .PinchStrength_2 = handState.PinchStrength[2],
        .PinchStrength_3 = handState.PinchStrength[3],
        .PinchStrength_4 = handState.PinchStrength[4],

        .PointerPose = *((Posef*)&handState.PointerPose),
        .HandScale = handState.HandScale,
        .HandConfidence = *((TrackingConfidence*)&handState.HandConfidence),

        .FingerConfidences_0 = *((TrackingConfidence*)&handState.FingerConfidence[0]),
        .FingerConfidences_1 = *((TrackingConfidence*)&handState.FingerConfidence[1]),
        .FingerConfidences_2 = *((TrackingConfidence*)&handState.FingerConfidence[2]),
        .FingerConfidences_3 = *((TrackingConfidence*)&handState.FingerConfidence[3]),
        .FingerConfidences_4 = *((TrackingConfidence*)&handState.FingerConfidence[4]),

        .RequestedTimeStamp = handState.RequestedTimeStamp,
        .SampleTimeStamp = handState.SampleTimeStamp,
    };
    return ovrHandState;
}
