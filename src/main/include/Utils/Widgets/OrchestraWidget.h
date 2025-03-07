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

#include <filesystem>
#include <frc/filesystem.h>


class OrchestraWidget : public nt::NTSendable, public wpi::SendableHelper<OrchestraWidget> {
    public:
        using Entry = size_t;

        //OrchestraWidget Constructor (Takes a file path to the folder that the music files are stored)
        OrchestraWidget(std::filesystem::path musicFolder);

        OrchestraWidget(OrchestraWidget&& rhs);
        OrchestraWidget& operator=(OrchestraWidget&& rhs);

        void InitSendable(nt::NTSendableBuilder& builder) override;

        void UpdateTrackList(std::filesystem::path musicFolder);

    private:        
        std::shared_ptr<nt::NetworkTable> m_table;
        std::vector<std::filesystem::path> m_Tracks;
        

};

