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

//Because OVR's measurement is in m/s and PICO's is cm/s... ok...
//Still, /100 is still a bit too much?
Vector3f PxrVector3ToOVRVector3(PxrVector3f vector3F) {
    Vector3f ovrVector3  = {
            .x = vector3F.x / 700,
            .y = vector3F.y / 700,
            .z = vector3F.z / 700,
    };
    return ovrVector3;
}

Posef PxrPosefFlipped(PxrPosef posef) {
    Posef flipped = *((Posef*)&posef);

    flipped.Position.z = -flipped.Position.z;

    flipped.Orientation.x = -flipped.Orientation.x;
    flipped.Orientation.y = -flipped.Orientation.y;

    return flipped;
}

void PxrHandCombinedStateToOVRHandState(
        PxrHandAimState aimState,
        PxrHandJointsLocations jointsLocations,
        HandStateInternal *handStateInternal
) {
        Posef posefDummy;

        posefDummy.Orientation.x = 0;
        posefDummy.Orientation.y = 0;
        posefDummy.Orientation.z = 0;
        posefDummy.Orientation.w = 0;

        posefDummy.Position.x = 0;
        posefDummy.Position.y = 1;
        posefDummy.Position.z = 0;

        handStateInternal->Status = *((HandStatus *)&aimState.Status);
        handStateInternal->RootPose = posefDummy;

        handStateInternal->BoneRotations_0 = PxrPosefToOVRQuatf(jointsLocations.jointLocations[0].pose);
        handStateInternal->BoneRotations_1 = PxrPosefToOVRQuatf(jointsLocations.jointLocations[1].pose);
        handStateInternal->BoneRotations_2 = PxrPosefToOVRQuatf(jointsLocations.jointLocations[2].pose);
        handStateInternal->BoneRotations_3 = PxrPosefToOVRQuatf(jointsLocations.jointLocations[3].pose);
        handStateInternal->BoneRotations_4 = PxrPosefToOVRQuatf(jointsLocations.jointLocations[4].pose);
        handStateInternal->BoneRotations_5 = PxrPosefToOVRQuatf(jointsLocations.jointLocations[5].pose);
        handStateInternal->BoneRotations_6 = PxrPosefToOVRQuatf(jointsLocations.jointLocations[6].pose);
        handStateInternal->BoneRotations_7 = PxrPosefToOVRQuatf(jointsLocations.jointLocations[7].pose);
        handStateInternal->BoneRotations_8 = PxrPosefToOVRQuatf(jointsLocations.jointLocations[8].pose);
        handStateInternal->BoneRotations_9 = PxrPosefToOVRQuatf(jointsLocations.jointLocations[9].pose);
        handStateInternal->BoneRotations_10 = PxrPosefToOVRQuatf(jointsLocations.jointLocations[10].pose);
        handStateInternal->BoneRotations_11 = PxrPosefToOVRQuatf(jointsLocations.jointLocations[11].pose);
        handStateInternal->BoneRotations_12 = PxrPosefToOVRQuatf(jointsLocations.jointLocations[12].pose);
        handStateInternal->BoneRotations_13 = PxrPosefToOVRQuatf(jointsLocations.jointLocations[13].pose);
        handStateInternal->BoneRotations_14 = PxrPosefToOVRQuatf(jointsLocations.jointLocations[14].pose);
        handStateInternal->BoneRotations_15 = PxrPosefToOVRQuatf(jointsLocations.jointLocations[15].pose);
        handStateInternal->BoneRotations_16 = PxrPosefToOVRQuatf(jointsLocations.jointLocations[16].pose);
        handStateInternal->BoneRotations_17 = PxrPosefToOVRQuatf(jointsLocations.jointLocations[17].pose);
        handStateInternal->BoneRotations_18 = PxrPosefToOVRQuatf(jointsLocations.jointLocations[18].pose);
        handStateInternal->BoneRotations_19 = PxrPosefToOVRQuatf(jointsLocations.jointLocations[19].pose);
        handStateInternal->BoneRotations_20 = PxrPosefToOVRQuatf(jointsLocations.jointLocations[20].pose);
        handStateInternal->BoneRotations_21 = PxrPosefToOVRQuatf(jointsLocations.jointLocations[21].pose);
        handStateInternal->BoneRotations_22 = PxrPosefToOVRQuatf(jointsLocations.jointLocations[22].pose);
        handStateInternal->BoneRotations_23 = PxrPosefToOVRQuatf(jointsLocations.jointLocations[23].pose);

        handStateInternal->Pinches = HandFingerPinch_Thumb;//aimState.Pinches;

        handStateInternal->PinchStrength_0 = aimState.pinchStrengthIndex;
        handStateInternal->PinchStrength_1 = aimState.pinchStrengthMiddle;
        handStateInternal->PinchStrength_2 = aimState.pinchStrengthRing;
        handStateInternal->PinchStrength_3 = aimState.pinchStrengthLittle;
        handStateInternal->PinchStrength_4 = aimState.ClickStrength;

        handStateInternal->PointerPose = posefDummy;//PxrPosefFlipped(aimState.aimPose);
        handStateInternal->HandScale = jointsLocations.HandScale;
        handStateInternal->HandConfidence = TrackingConfidence_High;//*((TrackingConfidence*)&handState.HandConfidence);

        handStateInternal->FingerConfidences_0 = TrackingConfidence_High;
        handStateInternal->FingerConfidences_1 = TrackingConfidence_High;
        handStateInternal->FingerConfidences_2 = TrackingConfidence_High;
        handStateInternal->FingerConfidences_3 = TrackingConfidence_High;
        handStateInternal->FingerConfidences_4 = TrackingConfidence_High;

        /*handStateInternal->RequestedTimeStamp = handState.RequestedTimeStamp;
        handStateInternal->SampleTimeStamp = handState.SampleTimeStamp;*/

    __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "Old root pose X: %f, new root pose X: %f", aimState.aimPose.position.x, handStateInternal->RootPose.Position.x);
}
