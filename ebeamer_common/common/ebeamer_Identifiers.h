/*
  ==============================================================================

 Ebeamer common module
 Eventide Inc.
 Copyright Eventide Inc. 2021
 Author: Luca Bondi (bondi.luca@gmail.com)

  ==============================================================================
*/

namespace juce {

const Identifier energyIdentifier = Identifier("doaEnergy");

const String steerXIdentifierPrefix = "steerBeamX";
const String steerYIdentifierPrefix = "steerBeamY";
const Identifier steerX1Identifier = Identifier(steerXIdentifierPrefix + "1");
const Identifier steerX2Identifier = Identifier(steerXIdentifierPrefix + "2");
const Identifier steerY1Identifier = Identifier(steerYIdentifierPrefix + "1");
const Identifier steerY2Identifier = Identifier(steerYIdentifierPrefix + "2");


const String widthIdentifierPrefix = "widthBeam";
const Identifier width1Identifier = Identifier(widthIdentifierPrefix + "1");
const Identifier width2Identifier = Identifier(widthIdentifierPrefix + "2");

const String panIdentifierPrefix = "panBeam";
const Identifier pan1Identifier = Identifier(panIdentifierPrefix+"1");
const Identifier pan2Identifier = Identifier(panIdentifierPrefix+"2");

const String levelIdentifierPrefix = "levelBeam";
const Identifier level1Identifier = Identifier(levelIdentifierPrefix+"1");
const Identifier level2Identifier = Identifier(levelIdentifierPrefix+"2");

const String muteIdentifierPrefix = "muteBeam";
const Identifier mute1Identifier = Identifier(muteIdentifierPrefix+"1");
const Identifier mute2Identifier = Identifier(muteIdentifierPrefix+"2");

const Identifier inMetersIdentifier = Identifier("inMeters");

const Identifier outMeter1Identifier = Identifier("outMeter1");
const Identifier outMeter2Identifier = Identifier("outMeter2");

const Identifier hpfIdentifier = Identifier("hpf");
const Identifier gainIdentifier = Identifier("gainMic");
const Identifier cpuIdentifier = Identifier("cpuLoad");
const Identifier frontIdentifier = Identifier("frontFacing");
const Identifier configIdentifier = Identifier("config");

const Identifier serversIdentifier = Identifier("servers");

const Identifier serverIpIdentifier = Identifier("serverIp");
const Identifier serverPortIdentifier = Identifier("serverPort");

const Identifier subscribeIdentifier = Identifier("subscribe");
const Identifier unsubscribeIdentifier = Identifier("unsubscribe");

}
