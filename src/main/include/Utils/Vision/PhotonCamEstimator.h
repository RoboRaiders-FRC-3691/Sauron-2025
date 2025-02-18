#pragma once

#include <frc/geometry/Transform3d.h>

#include <vector>
#include <string>

#include <photon/PhotonCamera.h>
#include <photon/PhotonPoseEstimator.h>

#include <frc/apriltag/AprilTagFieldLayout.h>
#include <frc/apriltag/AprilTagFields.h>

class PhotonCamEstimator : public photon::PhotonCamera, public photon::PhotonPoseEstimator {
    public:
        PhotonCamEstimator(std::string name, frc::AprilTagFieldLayout aprilTags, photon::PoseStrategy poseStrategy, frc::Transform3d robotToCam);

        std::vector <std::optional<photon::EstimatedRobotPose>> Update();

    private:
        std::vector <photon::PhotonPipelineResult> m_results;
        std::vector <std::optional<photon::EstimatedRobotPose>> m_robotPositions;
};