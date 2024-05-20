
"use strict";

let GetProgramState = require('./GetProgramState.js')
let Popup = require('./Popup.js')
let IsProgramSaved = require('./IsProgramSaved.js')
let RawRequest = require('./RawRequest.js')
let GetRobotMode = require('./GetRobotMode.js')
let Load = require('./Load.js')
let IsProgramRunning = require('./IsProgramRunning.js')
let AddToLog = require('./AddToLog.js')
let GetLoadedProgram = require('./GetLoadedProgram.js')
let IsInRemoteControl = require('./IsInRemoteControl.js')
let GetSafetyMode = require('./GetSafetyMode.js')

module.exports = {
  GetProgramState: GetProgramState,
  Popup: Popup,
  IsProgramSaved: IsProgramSaved,
  RawRequest: RawRequest,
  GetRobotMode: GetRobotMode,
  Load: Load,
  IsProgramRunning: IsProgramRunning,
  AddToLog: AddToLog,
  GetLoadedProgram: GetLoadedProgram,
  IsInRemoteControl: IsInRemoteControl,
  GetSafetyMode: GetSafetyMode,
};
