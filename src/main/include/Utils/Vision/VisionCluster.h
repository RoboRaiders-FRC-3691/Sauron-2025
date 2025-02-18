#pragma once

#include <units/length.h>

#include <frc/Filesystem.h>
#include <filesystem>
#include <wpi/array.h>

#include <string>
#include <vector>

#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>

#include <frc/smartdashboard/SmartDashboard.h>

#include "Utils/Vision/JsonCamera.h"
#include "Utils/Vision/PhotonCamEstimator.h"

#include <Constants.h>

struct VisionPoseResult {
    photon::EstimatedRobotPose estimatedPose;
    wpi::array<double, 3U> standardDeviations;
};

class VisionCluster{
    public:
        VisionCluster();

        std::vector<VisionPoseResult> GetVisionEstimates();

        std::optional<VisionPoseResult> FilterVisionEstimate(std::optional<photon::EstimatedRobotPose> estimatedPosition);

    private:
        std::vector<PhotonCamEstimator> m_photonCameras;
        std::vector<VisionPoseResult> m_visionEst;
};