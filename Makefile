PLUGIN := AirwindowsCompressorsUI.clap
SOURCES := AirwindowsCompressorsUI.cpp
SOURCES += AirwindowsCompressorUIPlugin.cpp
SOURCES += ParameterWidget.cpp CompressionMeter.cpp
SOURCES += Pressure4Plugin.cpp Pressure5.cpp curvePlugin.cpp ButterComp2Plugin.cpp Pop2Plugin.cpp
SOURCES += VariMu.cpp PurestSquish.cpp Dynamics.cpp Pop.cpp DigitalBlack.cpp Logical4.cpp Recurve.cpp
SOURCES += Pyewacket.cpp BlockParty.cpp SoftGate.cpp Thunder.cpp Compresaturator.cpp
SOURCES += ButterComp.cpp BrassRider.cpp Point.cpp Gatelope.cpp
SOURCES += MessageQueue.cpp Settings.cpp SettingsParser.cpp
AIRWINDOWS_DIR := from-airwindows
AIRWINDOWS_SOURCES += Pressure4Proc.cpp Pressure5Proc.cpp curveProc.cpp ButterComp2Proc.cpp Pop2Proc.cpp
AIRWINDOWS_SOURCES += VariMuProc.cpp PurestSquishProc.cpp DynamicsProc.cpp PopProc.cpp DigitalBlackProc.cpp
AIRWINDOWS_SOURCES += Logical4Proc.cpp RecurveProc.cpp PyewacketProc.cpp BlockPartyProc.cpp SoftGateProc.cpp
AIRWINDOWS_SOURCES += ThunderProc.cpp CompresaturatorProc.cpp ButterCompProc.cpp BrassRiderProc.cpp
AIRWINDOWS_SOURCES += PointProc.cpp GatelopeProc.cpp
SOURCES += $(foreach source,$(AIRWINDOWS_SOURCES),$(AIRWINDOWS_DIR)/$(source))
FRAMEWORK_DIR := CLAPFramework
FRAMEWORK_SOURCES += CLAPPlugin.cpp
FRAMEWORK_SOURCES += CLAPPosixFDExtension.cpp CLAPCairoGUIExtension.cpp
FRAMEWORK_SOURCES += CLAPAudioPortsExtension.cpp CLAPNotePortsExtension.cpp
FRAMEWORK_SOURCES += CLAPParamsExtension.cpp CLAPStateExtension.cpp CLAPTimerSupportExtension.cpp
FRAMEWORK_SOURCES += CLAPStream.cpp
SOURCES += $(foreach source,$(FRAMEWORK_SOURCES),$(FRAMEWORK_DIR)/$(source))
WIDGETS_DIR := CairoWidgets
WIDGET_SOURCES += Widget.cpp Button.cpp Scrollbar.cpp FileList.cpp FileChooser.cpp
WIDGET_SOURCES += Label.cpp ProgressBar.cpp TextBox.cpp Checkbox.cpp HorizontalSlider.cpp
WIDGET_SOURCES += TimeSeconds.cpp
SOURCES += $(foreach source,$(WIDGET_SOURCES),$(WIDGETS_DIR)/$(source))
LIBRARIES += X11 cairo
SUBDIRS += $(AIRWINDOWS_DIR) $(FRAMEWORK_DIR) $(WIDGETS_DIR)
OBJECTS_DIR := objects

CFLAGS += -fPIC --no-exceptions --no-rtti -DTUNINGS_NO_EXCEPTIONS
CFLAGS += -Wall
LINK_FLAGS += -shared

-include Makefile.local

OBJECTS = $(foreach source,$(SOURCES),$(OBJECTS_DIR)/$(source:.cpp=.o))
OBJECTS_SUBDIRS = $(foreach dir,$(SUBDIRS),$(OBJECTS_DIR)/$(dir))

ifndef VERBOSE_MAKE
	QUIET := @
endif

all: $(PLUGIN)

CPP := g++
CFLAGS += -MMD
CFLAGS += -g
CFLAGS += -I.
CFLAGS += $(foreach dir,$(SUBDIRS),-I$(dir))
CFLAGS += $(foreach switch,$(DEFINES),-D$(switch))
CFLAGS += $(foreach switch,$(SWITCHES),-D$(switch))
LINK_FLAGS += -g
LINK_FLAGS += $(foreach lib,$(LIBRARIES),-l$(lib))

$(OBJECTS_DIR)/%.o: %.cpp
	@echo Compiling $<...
	$(QUIET) $(CPP) -c $< -g $(CFLAGS) -o $@

$(OBJECTS): | $(OBJECTS_DIR)

$(PLUGIN): $(OBJECTS)
	@echo "Linking $@..."
	$(QUIET) $(CPP) $(filter-out $(OBJECTS_DIR),$^) $(LINK_FLAGS) -o $@

$(OBJECTS_DIR):
	@echo "Making $@..."
	$(QUIET) mkdir -p $(OBJECTS_DIR) $(OBJECTS_SUBDIRS)

-include $(OBJECTS_DIR)/*.d
-include $(OBJECTS_DIR)/*/*.d


.PHONY: clean
clean:
	rm -rf $(OBJECTS_DIR)

.PHONY: tags
tags:
	ctags -R .

NON_FILES = AirwindowsCompressorsUI.h $(foreach source,$(AIRWINDOWS_SOURCES),$(AIRWINDOWS_DIR)/$(source:.cpp=.h))
.PHONY: edit-all
edit-all:
	@ $(EDITOR) $(filter-out $(NON_FILES),$(foreach source,$(SOURCES),$(source:.cpp=.h) $(source)))

.PHONY: validate
validate: $(PLUGIN)
	$(QUIET) clap-validator validate --only-failed --no-parallel $(PLUGIN)
.PHONY: test
test: $(PLUGIN)
	$(QUIET) clap-host -p ./$(PLUGIN)

