//
// Created by mikhail on 6/16/20.
//

#include "analysis_task.h"

TASK_IMPL(AnalysisTask)

void AnalysisTask::UserInit(std::map<std::string, void *> &branch_map) {
  // linking pointers with branch fields
  event_header_ = GetInBranch("RecoEvent.");
  vtx_tracks_ = GetInBranch("TpcTracks.");
  fhcal_modules_ = GetInBranch("FHCalModules.");

  pT_distribution_ = new TH1F( "pT_distribution", ";p_{T} [GeV/c];entries", 250, 0., 2.5 );
  fhcal_energy_distribution_ = new TH1F( "fhcal_energy_distribution", ";E [GeV];entries", 500, 0., 1.0 );
  fhcal_modules_xy_ = new TH2F( "fhcal_modules_xy", ";X;Y", 100, -50., 50.0, 100, -50., 50.0 );
}

void AnalysisTask::UserExec() {
  using AnalysisTree::Track;
  using AnalysisTree::Module;
  for( auto& track : vtx_tracks_->Loop() ){
    auto mom3 = track.DataT<Track>()->GetMomentum3();
    auto pT = mom3.Pt();
    pT_distribution_->Fill(pT);
  }
  auto fhcal_modules_posotions = data_header_->GetModulePositions(0);
  for( auto& module : fhcal_modules_->Loop()){
    auto id = module.DataT<Module>()->GetId();
    auto module_pos = fhcal_modules_posotions.GetChannel(id);
    auto signal = module.DataT<Module>()->GetSignal();
    fhcal_energy_distribution_->Fill(signal);
    fhcal_modules_xy_->Fill( module_pos.GetX(), module_pos.GetY() );
  }
}

void AnalysisTask::UserFinish() {
  // Writing histograms to file
  out_file_->cd();
  pT_distribution_->Write();
  fhcal_energy_distribution_->Write();
  fhcal_modules_xy_->Write();
}
boost::program_options::options_description AnalysisTask::GetBoostOptions() {
  return UserTask::GetBoostOptions();
}