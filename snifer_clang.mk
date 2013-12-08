##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=snifer_clang
ConfigurationName      :=Release
WorkspacePath          := "/home/maxis11/sources/clang/snifer_clang"
ProjectPath            := "/home/maxis11/sources/clang/snifer_clang"
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=maxis11
Date                   :=12/09/13
CodeLitePath           :="/home/maxis11/.codelite"
LinkerName             :=clang++
SharedObjectLinkerName :=clang++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="snifer_clang.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)pthread 
ArLibs                 :=  "pthread" 
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := clang++
CC       := clang
CXXFLAGS :=  -O2 -Wall -std=c++11 $(Preprocessors)
CFLAGS   :=  -O2 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := llvm-as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main$(ObjectSuffix) $(IntermediateDirectory)/concurent_queue$(ObjectSuffix) $(IntermediateDirectory)/iflog$(ObjectSuffix) $(IntermediateDirectory)/ifscanner$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

$(IntermediateDirectory)/.d:
	@test -d ./Release || $(MakeDirCommand) ./Release

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main$(ObjectSuffix): main.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/maxis11/sources/clang/snifer_clang/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main$(PreprocessSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main$(PreprocessSuffix) "main.cpp"

$(IntermediateDirectory)/concurent_queue$(ObjectSuffix): concurent_queue.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/maxis11/sources/clang/snifer_clang/concurent_queue.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/concurent_queue$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/concurent_queue$(PreprocessSuffix): concurent_queue.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/concurent_queue$(PreprocessSuffix) "concurent_queue.cpp"

$(IntermediateDirectory)/iflog$(ObjectSuffix): iflog.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/maxis11/sources/clang/snifer_clang/iflog.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/iflog$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/iflog$(PreprocessSuffix): iflog.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/iflog$(PreprocessSuffix) "iflog.cpp"

$(IntermediateDirectory)/ifscanner$(ObjectSuffix): ifscanner.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/maxis11/sources/clang/snifer_clang/ifscanner.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ifscanner$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ifscanner$(PreprocessSuffix): ifscanner.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ifscanner$(PreprocessSuffix) "ifscanner.cpp"

##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/main$(DependSuffix)
	$(RM) $(IntermediateDirectory)/main$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/concurent_queue$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/concurent_queue$(DependSuffix)
	$(RM) $(IntermediateDirectory)/concurent_queue$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/iflog$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/iflog$(DependSuffix)
	$(RM) $(IntermediateDirectory)/iflog$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/ifscanner$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/ifscanner$(DependSuffix)
	$(RM) $(IntermediateDirectory)/ifscanner$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) ".build-release/snifer_clang"


