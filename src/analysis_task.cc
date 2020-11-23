//
// Created by mikhail on 6/16/20.
//

#include "analysis_task.h"

namespace AnalysisTree {
void AnalysisTask::Init(std::map<std::string, void *> &branch_map) {
  // linking pointers with branch fields
  RecEventHeader_ = static_cast<EventHeader *>(branch_map.at("RecEventHeader"));
  SimParticles_ = static_cast<Particles *>(branch_map.at("SimParticles"));
  VtxTracks_ = static_cast<TrackDetector *>(branch_map.at("VtxTracks"));
  TofHits_ = static_cast<HitDetector *>(branch_map.at("TofHits"));
  PsdModules_ = static_cast<HitDetector *>(branch_map.at("PsdModules"));
  VtxTracks2SimParticles_ = static_cast<Matching *>(branch_map.at("VtxTracks2SimParticles"));
  VtxTracks2TofHits_ = static_cast<Matching *>(branch_map.at("VtxTracks2TofHits"));

  // getting branch configurations, which store information about fields in branches
  auto RecEventHeader_config = config_->GetBranchConfig("RecEventHeader");
  auto SimParticles_config = config_->GetBranchConfig("SimParticles");
  auto VtxTracks_config = config_->GetBranchConfig("VtxTracks");
  auto TofHits_config = config_->GetBranchConfig("TofHits");

  // linking necessary for analysis fields with enumerator for fast access to them
  fields_id_.insert(std::make_pair(FIELDS::MULT, RecEventHeader_config.GetFieldId("M")));

  // initializing histograms
  hMultiplicity_ = new TH1F( "hMultiplicity", "Multiplicity;Ntracks;counts", 1000, 0, 1000 );
  h2pTyProton_ = new TH2F( "h2pTyProton", "p_{T} vs #it{y} (protons);#it{y};p_{T} (GeV/c);counts", 500, 0, 5, 500, 0, 5. );
}

void AnalysisTask::Exec() {
  auto mult = RecEventHeader_->GetField<int>(fields_id_.at(FIELDS::MULT)); // getting multiplicity from event header
  hMultiplicity_->Fill(mult); // fill 1D histogram

  int nTracks = VtxTracks_->GetNumberOfChannels(); // number of tracks in current event
  for (int i = 0; i < nTracks; ++i) { // loop over all tracks in current event
    auto track = VtxTracks_->GetChannel(i); // getting track from track detector
    int matched_particle_index = VtxTracks2SimParticles_->GetMatchDirect(i); // getting index of matched sim particle
    if (matched_particle_index < 0) // matched sim particle is not stored
      continue;
    auto simParticle = SimParticles_->GetChannel(matched_particle_index); // getting sim particle matched to the track 
    auto pid = simParticle.GetPid(); // get particle type
    auto pt = track.GetPt(); // getting transverse momentum
    auto y = track.GetRapidity(pid); // getting rapidity
    // filling distributions
    if (pid == 2212)
      h2pTyProton_->Fill(y,pt); // fill 2D histogram
  }
}

void AnalysisTask::Finish() {
  // Writing histograms to file
  hMultiplicity_->Write();
  h2pTyProton_->Write();
}
} // namespace AnalysisTree
