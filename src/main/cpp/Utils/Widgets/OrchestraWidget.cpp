// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Utils/Widgets/OrchestraWidget.h"

#include <memory>
#include <utility>

#include <networktables/DoubleArrayTopic.h>
#include <networktables/NTSendableBuilder.h>
#include <wpi/sendable/SendableRegistry.h>


OrchestraWidget::OrchestraWidget(std::filesystem::path musicFolder) {
    UpdateTrackList(musicFolder);
    wpi::SendableRegistry::Add(this, "OrchestraWidget");
}

OrchestraWidget::OrchestraWidget(OrchestraWidget&& rhs) : SendableHelper(std::move(rhs)) {
    std::swap(m_table, rhs.m_table);
}

OrchestraWidget& OrchestraWidget::operator=(OrchestraWidget&& rhs) {
    SendableHelper::operator=(std::move(rhs));
    std::swap(m_table, rhs.m_table);
    return *this;
}

// void OrchestraWidget::Update(ctre::phoenix6::Orchestra::impl::OrchestraDrivetrainImpl::OrchestraDriveState OrchestraState){
//     m_robotAngle = OrchestraState.Pose.Rotation();

//     for(int i = 0; i < 4; i++){
//         m_moduleStates[i] = OrchestraState.ModuleStates[i];
//     }
// }

// void OrchestraWidget::Update(wpi::array<frc::OrchestraModuleState, 4U> moduleStates, frc::Rotation2d robotHeading){
//     m_robotAngle = robotHeading;
//     m_moduleStates = moduleStates;
// }


void OrchestraWidget::InitSendable(nt::NTSendableBuilder& builder) {
    builder.SetSmartDashboardType("Orchestra Controls");

    //track.filename().generic_string()
    //builder.AddBooleanArrayProperty()

    m_table = builder.GetTable();
}

void OrchestraWidget::UpdateTrackList(std::filesystem::path musicFolder){
    // To check if the directory exists or not 
    if (std::filesystem::exists(musicFolder)
        && std::filesystem::is_directory(musicFolder)) {
        // Loop through each item (file or subdirectory) in 
        // the directory 
        for (const auto& entry :
            std::filesystem::directory_iterator(musicFolder)) {
            //Check if the entry points to a file
            if(entry.is_regular_file()){
                m_Tracks.push_back(entry.path());
            }
        }
    }
}
