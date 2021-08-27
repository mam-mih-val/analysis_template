# analysis_template
Template of analysis made with AnalysisTree package.

# Requirement

* CMake 3.11 or newer
* ROOT v6-20-04 or v6-18-04 built with C++17
* Boost

# Building

Clone this repository with
```
  $ git clone https://github.com/mam-mih-val/analysis_template
```
Change directory and checkout to the mpd branch
```
  $ cd analysis_template
  $ git checkout na61
```
Create the build directory
```
  $ mkdir build
  $ cd build
```
Source root environment
```
  $ source /path/to/root/install/bin/thisroot.sh
``` 
Build the project
```
  $ cmake ..
  $ make -j
```

# Usage
To list all the options run
```
  ./analyse -h
```
Available options are bellow
```asm
   -h [ --help ]                   print usage message
   --tasks                         print registered tasks
  -i [ --input-filelists ] arg    lists of AT ROOT Files
  -t [ --tree-names ] arg         Tree names
  -o [ --output-file-name ] arg   Output ROOT filename
  --output-tree-name arg (=aTree) Output tree name
  -n [ --n-events ] arg (=-1)     Number of events to process (-1 = until the 
                                  end)
  --enable-tasks arg              Enable specific tasks
                                  Tasks: AnalysisTask 
  --disable-tasks arg             Disable specific tasks
                                  Tasks: AnalysisTask 
  --cuts-macro arg                Macro with cuts definitions
  --event-cuts arg                Name of event cuts
  --branch-cuts arg               Name(s) of branch cuts
```
Example of command which executes with file list "/path/to/file/list/na61.list" containing root files with tree "aTree" and writes the output to file "/path/to/file/out/out.root" and 10K events to be processed.
```
  $ analyse /path/to/file/list/na61.list -t aTree -o /path/to/file/out/out.root -n 10000
```

Detailed description of how to work with AnalysisTree is stored in https://docs.google.com/document/d/1pWh8T4xAjVvJJyB1OQYLRzVW_HHinZ_uxHHPz_1rfQs/edit.
