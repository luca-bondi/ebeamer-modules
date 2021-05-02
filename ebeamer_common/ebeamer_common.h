/*
  ==============================================================================

 Ebeamer common module
 Eventide Inc.
 Copyright Eventide Inc. 2021
 Author: Luca Bondi (bondi.luca@gmail.com)

  ==============================================================================
*/


/*******************************************************************************
 The block below describes the properties of this module, and is read by
 the Projucer to automatically generate project code that uses it.
 For details about the syntax and how to create or use a module, see the
 JUCE Module Format.md file.


 BEGIN_JUCE_MODULE_DECLARATION

  ID:                 ebeamer_common
  vendor:             Eventide
  version:            1.0.0
  name:               Ebeamer commons
  description:      Ebeamer common classes
  website:            http://www.eventideaudio.com
  license:            GPL/Commercial

  dependencies: juce_core juce_data_structures

 END_JUCE_MODULE_DECLARATION

*******************************************************************************/


#pragma once
#define JUCE_EBEAMER_COMMON_H_INCLUDED


/* db to color thresholds */

#define RED_LT -0.5f //dB
#define ORANGE_LT -6.0f //dB
#define YELLOW_LT -12.0f //dB
#define GREEN_LT -40.0f //dB

#define MIN_GAIN 0.
#define MAX_GAIN 40.
#define DEFAULT_GAIN 20.

#define MIN_HPF 20.
#define MAX_HPF 500.
#define DEFAULT_HPF 250.

#define MIN_LEVEL -10.
#define MAX_LEVEL +10.


#include <juce_core/juce_core.h>
#include <juce_data_structures/juce_data_structures.h>

const float pi = juce::MathConstants<float>::pi;

#include "common/ebeamer_MicConfig.h"
#include "common/ebeamer_ValueTreeFile.h"
#include "common/ebeamer_Identifiers.h"
#include "common/ebeamer_MidiCC.h"

namespace juce{

void initValueTreeParameters(ValueTree&);

}
