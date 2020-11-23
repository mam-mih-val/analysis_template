//
// Created by mikhail on 6/16/20.
//

#ifndef QUALITY_ASSURANCE_SRC_TREE_READER_H_
#define QUALITY_ASSURANCE_SRC_TREE_READER_H_

#include <TChain.h>
#include <TH3F.h>
#include <TProfile2D.h>

#include <AnalysisTree/EventHeader.hpp>
#include <AnalysisTree/FillTask.hpp>
#include <AnalysisTree/Cuts.hpp>
#include <AnalysisTree/Detector.hpp>
#include <AnalysisTree/Matching.hpp>

namespace AnalysisTree {
class AnalysisTask : public FillTask{
public:
 AnalysisTask() = default;
  ~AnalysisTask() override = default;
  void Init( std::map<std::string, void*>& branch_map ) override;
  void Exec() override;
  void Finish() override;
private:
 enum class FIELDS{ // enumerator to fast access to detectors' fields
   MULT, 	// Hits in TOF
   HITS_PSD, 	// Hits in PSD 
  };
  std::map<FIELDS, int> fields_id_; // map to match detectors' fields with enumerator

  /* pointers to link tree's branches with */
  EventHeader* SimEventHeader_{nullptr}; 		// MC event info
  EventHeader* RecEventHeader_{nullptr}; 		// reconstructed event info
  Particles* SimParticles_{nullptr}; 		// MC tracks
  TrackDetector* VtxTracks_{nullptr}; 		// reconstructed tracks
  HitDetector* TofHits_{nullptr}; 		// TOF
  HitDetector* PsdModules_{nullptr}; 		// PSD 
  Matching* VtxTracks2SimParticles_{nullptr}; 	// matching between MC and reconstructed tracks
  Matching* VtxTracks2TofHits_{nullptr}; 	// matching between reconstructed tracks and TOF hits

  TH1F* hMultiplicity_; 	// 1D distribution of event variable 
  TH2F* h2pTyProton_; 		// 2D distribution of track variables
};
} // namespace AnalysisTree
#endif // QUALITY_ASSURANCE_SRC_TREE_READER_H_
