add_executable(analyse analysis_task.cc analysis_task.h)
target_link_libraries(analyse PUBLIC ROOT::EG at_task_main)