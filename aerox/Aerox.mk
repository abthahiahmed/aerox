##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=Aerox
ConfigurationName      :=Release
WorkspaceConfiguration :=Release
WorkspacePath          :=/mnt/sdb/Projects/CPP/CPP
ProjectPath            :=/mnt/sdb/Projects/CPP/CPP/WebServer/aerox
IntermediateDirectory  :=$(ConfigurationName)
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Abthahi Ahmed Rifat
Date                   :=05/09/25
CodeLitePath           :=/home/iamabthahi/.codelite
LinkerName             :=g++
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputDirectory        :=$(IntermediateDirectory)
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)NDEBUG 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="Aerox.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overridden using an environment variable
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -O2 -Wall $(Preprocessors)
CFLAGS   :=  -O2 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/threads.cpp$(ObjectSuffix) $(IntermediateDirectory)/aerox.cpp$(ObjectSuffix) $(IntermediateDirectory)/parser.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d $(ConfigurationName) || $(MakeDirCommand) $(ConfigurationName)


$(IntermediateDirectory)/.d:
	@test -d $(ConfigurationName) || $(MakeDirCommand) $(ConfigurationName)

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/mnt/sdb/Projects/CPP/CPP/WebServer/aerox/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

$(IntermediateDirectory)/threads.cpp$(ObjectSuffix): threads.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/mnt/sdb/Projects/CPP/CPP/WebServer/aerox/threads.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/threads.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/threads.cpp$(PreprocessSuffix): threads.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/threads.cpp$(PreprocessSuffix) threads.cpp

$(IntermediateDirectory)/aerox.cpp$(ObjectSuffix): aerox.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/mnt/sdb/Projects/CPP/CPP/WebServer/aerox/aerox.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/aerox.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/aerox.cpp$(PreprocessSuffix): aerox.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/aerox.cpp$(PreprocessSuffix) aerox.cpp

$(IntermediateDirectory)/parser.cpp$(ObjectSuffix): parser.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/mnt/sdb/Projects/CPP/CPP/WebServer/aerox/parser.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/parser.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/parser.cpp$(PreprocessSuffix): parser.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/parser.cpp$(PreprocessSuffix) parser.cpp

##
## Clean
##
clean:
	$(RM) -r $(ConfigurationName)/


