/*
  ==============================================================================

   Ebeamer OSC module
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

  ID:                 ebeamer_osc
  vendor:             Eventide
  version:            1.0.0
  name:               Ebeamer OSC library
  description:      Ebeamer OSC classes
  website:            http://www.eventideaudio.com
  license:            GPL/Commercial

  dependencies:       juce_osc juce_data_structures ebeamer_common

 END_JUCE_MODULE_DECLARATION

*******************************************************************************/


#pragma once
#define JUCE_EBEAMER_OSC_H_INCLUDED

#include <juce_core/juce_core.h>
#include <juce_events/juce_events.h>
#include <juce_osc/juce_osc.h>
#include <juce_data_structures/juce_data_structures.h>
#include <ebeamer_common/ebeamer_common.h>

#include "osc/ebeamer_Server.h"
#include "osc/ebeamer_ServerList.h"
#include "osc/ebeamer_OSCServerBroadcast.h"
#include "osc/ebeamer_OSCController.h"

#define BROADCAST_PORT 9011

namespace juce{

const std::list<Identifier> commonIdentifiersList = {
    energyIdentifier,
    steerX1Identifier,
    steerX2Identifier,
    steerY1Identifier,
    steerY2Identifier,
    width1Identifier,
    width2Identifier,
    pan1Identifier,
    pan2Identifier,
    level1Identifier,
    level2Identifier,
    mute1Identifier,
    mute2Identifier,
    inMetersIdentifier,
    outMeter1Identifier,
    outMeter2Identifier,
    hpfIdentifier,
    gainIdentifier,
    cpuIdentifier,
    frontIdentifier,
    configIdentifier
};

void     registerCommonOscParameters(OSCController&);

}
