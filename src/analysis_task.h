//
// Created by mikhail on 6/16/20.
//

#ifndef QUALITY_ASSURANCE_SRC_TREE_READER_H_
#define QUALITY_ASSURANCE_SRC_TREE_READER_H_

#include <TFile.h>
#include <TTree.h>
#include <TH2F.h>

#include <AnalysisTree/Detector.hpp>
#include <AnalysisTree/EventHeader.hpp>
#include <AnalysisTree/DataHeader.hpp>
#include <TH1F.h>
#include <TH2F.h>
#include <TH3F.h>
#include <TProfile.h>
#include <at_task/Task.h>
#include <memory>
#include <string>

class AnalysisTask : public UserFillTask{
public:
 AnalysisTask() = default;
  ~AnalysisTask() override = default;
  void UserInit( std::map<std::string, void*>& branch_map ) override;
  void UserExec() override;
  void UserFinish() override;
  boost::program_options::options_description GetBoostOptions() override;
  void PreInit() override {};
  void PostFinish() override {
    UserTask::PostFinish();
  }

private:
  /* pointers to link tree's branches with */
  ATI2::Branch* event_header_{nullptr}; 		// event info
  ATI2::Branch* vtx_tracks_{nullptr}; 		        // reconstructed tracks
  ATI2::Branch*fhcal_modules_{nullptr}; 		// modules of FhCal branch
  TH1F* pT_distribution_;
  TH1F* fhcal_energy_distribution_;
  TH2F*fhcal_modules_xy_;
TASK_DEF(AnalysisTask, 0)
};
#endif // QUALITY_ASSURANCE_SRC_TREE_READER_H_
