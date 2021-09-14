//
// Created by mikhail on 6/16/20.
//

#include "analysis_task.h"

TASK_IMPL(AnalysisTask)

void AnalysisTask::UserInit(std::map<std::string, void *> &branch_map) {
  // linking pointers with branch fields
  event_header_ = GetInBranch("RecEventHeader");
  vtx_tracks_ = GetInBranch("VtxTracks");
  psd_modules_ = GetInBranch("PsdModules");

  pT_distribution_ = new TH1F( "pT_distribution", ";p_{T} [GeV/c];entries", 250, 0., 2.5 );
  psd_energy_distribution_ = new TH1F( "psd_energy_distribution", ";E [GeV];entries", 500, 0., 100.0 );
  psd_modules_xy_ = new TH2F( "psd_modules_xy", ";X;Y", 100, -100., 100.0, 100, -100., 100.0 );
}

void AnalysisTask::UserExec() {
  using AnalysisTree::Track;
  using AnalysisTree::Module;
  for( auto& track : vtx_tracks_->Loop() ){
    auto mom3 = track.DataT<Track>()->GetMomentum3();
    auto pT = mom3.Pt();
    pT_distribution_->Fill(pT);
  }
  auto psd_modules_posotions = data_header_->GetModulePositions(0);
  for( auto& module : psd_modules_->Loop() ){
    auto id = module.DataT<Module>()->GetId();
    auto module_pos = psd_modules_posotions.GetChannel(id);
    auto signal = module.DataT<Module>()->GetSignal();
    psd_energy_distribution_->Fill(signal);
    psd_modules_xy_->Fill( module_pos.GetX(), module_pos.GetY() );
  }
}

void AnalysisTask::UserFinish() {
  // Writing histograms to file
  out_file_->cd();
  pT_distribution_->Write();
  psd_energy_distribution_->Write();
  psd_modules_xy_->Write();
}
boost::program_options::options_description AnalysisTask::GetBoostOptions() {
  return UserTask::GetBoostOptions();
}