//
// Created by mikhail on 6/16/20.
//

#include "analysis_task.h"

void AnalysisTask::Init(std::map<std::string, void *> &branch_map) {
  // linking pointers with branch fields
  event_header_ = static_cast<AnalysisTree::EventHeader*>(branch_map.at("RecoEvent."));
  vtx_tracks_ = static_cast<AnalysisTree::TrackDetector *>(branch_map.at("TpcTracks."));
  fhcal_modules_ = static_cast<AnalysisTree::ModuleDetector *>(branch_map.at("FHCalModules."));
  fhcal_modules_positions_ = data_header_->GetModulePositions(0);

  pT_distribution_ = new TH1F( "pT_distribution", ";p_{T} [GeV/c];entries", 250, 0., 2.5 );
  std::vector<float> bin_edges{0.0f, 8.0f, 11.0f, 16.0f};
  new TH1F( "name", "", bin_edges.size()-1, bin_edges.data() );
  fhcal_energy_distribution_ = new TH1F( "fhcal_energy_distribution", ";E [GeV];entries", 500, 0., 1.0 );
  fhcal_phi_distribution_ = new TH1F( "fhcal_phi_distribution", ";E [GeV];entries", 350, -3.5, 3.5 );
  fhcal_modules_xy_ = new TH2F( "fhcal_modules_xy", ";X;Y", 100, -50., 50.0, 100, -50., 50.0 );
}

void AnalysisTask::Exec() {
  for( auto& track : *vtx_tracks_->GetChannels() ){
    auto mom3 = track.GetMomentum3();
    auto pT = mom3.Pt();
    pT_distribution_->Fill(pT);
  }
  for( auto& module : *fhcal_modules_->GetChannels()){
    auto id = module.GetId();
    auto module_pos = fhcal_modules_positions_.GetChannel(id);
    auto signal = module.GetSignal();
    fhcal_energy_distribution_->Fill(signal);
    fhcal_phi_distribution_->Fill(module_pos.GetPhi());
    fhcal_modules_xy_->Fill( module_pos.GetX(), module_pos.GetY() );
  }
}

void AnalysisTask::Finish() {
  // Writing histograms to file
  out_file_->cd();
  pT_distribution_->Write();
  fhcal_energy_distribution_->Write();
  fhcal_phi_distribution_->Write();
  fhcal_modules_xy_->Write();
}