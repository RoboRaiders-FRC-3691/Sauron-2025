#pragma once

#include <memory>
#include <string_view>
#include <sstream>

#include <networktables/NTSendable.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableEntry.h>
#include <networktables/DoubleTopic.h>

#include <units/length.h>
#include <wpi/array.h>
#include <wpi/sendable/SendableHelper.h>

#include "ctre/phoenix6/swerve/impl/SwerveDrivetrainImpl.hpp"
#include "frc/kinematics/SwerveModuleState.h"

class SwerveWidget : public nt::NTSendable, public wpi::SendableHelper<SwerveWidget> {
    public:
        using Entry = size_t;

        SwerveWidget();

        SwerveWidget(SwerveWidget&& rhs);
        SwerveWidget& operator=(SwerveWidget&& rhs);

        void InitSendable(nt::NTSendableBuilder& builder) override;

        void Update(ctre::phoenix6::swerve::impl::SwerveDrivetrainImpl::SwerveDriveState swerveState);

        void Update(wpi::array<frc::SwerveModuleState, 4U> moduleStates, frc::Rotation2d robotHeading);

    private:        
        std::shared_ptr<nt::NetworkTable> m_table;
        wpi::array<frc::SwerveModuleState, 4U> m_moduleStates = {frc::SwerveModuleState(), frc::SwerveModuleState(), frc::SwerveModuleState(), frc::SwerveModuleState()};
        frc::Rotation2d m_robotAngle;

};

