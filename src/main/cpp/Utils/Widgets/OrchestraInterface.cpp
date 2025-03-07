#include <Utils/Widgets/OrchestraInterface.h>

OrchestraInterface::OrchestraInterface(ctre::phoenix6::Orchestra& _orchestra, std::filesystem::path musicFolder) : m_orchestraRef(_orchestra), m_PausePlay("Pause-Play"), m_StopTrack("Stop Track"){
    
    UpdateTrackList(musicFolder);
    
    frc::SmartDashboard::PutData("Track Select", &m_TrackSelector);
    
    m_PausePlay.GetButton().OnTrue(frc2::cmd::RunOnce([this]{ m_orchestraRef.Play(); }));
    m_PausePlay.GetButton().OnFalse(frc2::cmd::RunOnce([this]{ m_orchestraRef.Pause(); }));
    m_StopTrack.GetButton().OnTrue(frc2::cmd::RunOnce([this]{ m_orchestraRef.Stop(); }));

    m_TrackSelector.OnChange([this](std::filesystem::path trackChoice){
            if(m_orchestraRef.IsPlaying()){
                m_StopTrack.SetState(false);
                m_PausePlay.SetState(false);
                m_orchestraRef.Stop();  //"Manually" stop to ensure the track is stopped even if the trigger loop hasnt run yet (May be unneeded and removed later)
            }

            m_orchestraRef.LoadMusic(trackChoice.generic_string().c_str());

    });

}

void OrchestraInterface::UpdateTrackList(std::filesystem::path musicFolder){
    // To check if the directory exists or not 
    if (std::filesystem::exists(musicFolder)
        && std::filesystem::is_directory(musicFolder)) {
        // Loop through each item (file or subdirectory) in 
        // the directory 
        for (const auto& entry :
            std::filesystem::directory_iterator(musicFolder)) {
            //Check if the entry points to a file
            if(entry.is_regular_file()){
                m_TrackSelector.AddOption(entry.path().filename().generic_string(), entry.path());
            }
        }
    }
}