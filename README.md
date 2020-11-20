# analysis_template
Template of analysis made with AnalysisTree package.

# Requirement

* CMake 3.0
* ROOT v6-18-04
* AnalysisTree (see https://docs.google.com/document/d/1ztejoeJ45Aqdgq3a4m1DXTg4A1hUR3SDqk4ybYkboLA/edit for instructions)

# Building

Clone this repository with
```
  git clone https://github.com/mam-mih-val/analysis_template
```
Create build directory
```
  cd analysis_template
  mkdir build
  cd build
```
Source root environment
```
  source /path/to/root/install/bin/thisroot.sh
``` 
Export AnalysisTree library
```
  export AnalysisTree_DIR=/path/to/AnalysisTree/install/lib/cmake/AnalysisTree/
```
Build the project
```
  cmake ..
  make -j
```

# Usage
To use the program run
```
  ./analyse path/to/file.list
```
Example of file list you can find in "lists" directory.

Detailed description of how to work with AnalysisTree is stored in https://docs.google.com/document/d/1pWh8T4xAjVvJJyB1OQYLRzVW_HHinZ_uxHHPz_1rfQs/edit.
