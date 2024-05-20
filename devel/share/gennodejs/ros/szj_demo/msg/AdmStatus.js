// Auto-generated. Do not edit!

// (in-package szj_demo.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class AdmStatus {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.forceTarget = null;
      this.forceNow = null;
      this.paraB = null;
      this.deltaB = null;
      this.zdd = null;
      this.commandVel = null;
      this.actualVel = null;
    }
    else {
      if (initObj.hasOwnProperty('forceTarget')) {
        this.forceTarget = initObj.forceTarget
      }
      else {
        this.forceTarget = 0.0;
      }
      if (initObj.hasOwnProperty('forceNow')) {
        this.forceNow = initObj.forceNow
      }
      else {
        this.forceNow = 0.0;
      }
      if (initObj.hasOwnProperty('paraB')) {
        this.paraB = initObj.paraB
      }
      else {
        this.paraB = 0.0;
      }
      if (initObj.hasOwnProperty('deltaB')) {
        this.deltaB = initObj.deltaB
      }
      else {
        this.deltaB = 0.0;
      }
      if (initObj.hasOwnProperty('zdd')) {
        this.zdd = initObj.zdd
      }
      else {
        this.zdd = 0.0;
      }
      if (initObj.hasOwnProperty('commandVel')) {
        this.commandVel = initObj.commandVel
      }
      else {
        this.commandVel = 0.0;
      }
      if (initObj.hasOwnProperty('actualVel')) {
        this.actualVel = initObj.actualVel
      }
      else {
        this.actualVel = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type AdmStatus
    // Serialize message field [forceTarget]
    bufferOffset = _serializer.float64(obj.forceTarget, buffer, bufferOffset);
    // Serialize message field [forceNow]
    bufferOffset = _serializer.float64(obj.forceNow, buffer, bufferOffset);
    // Serialize message field [paraB]
    bufferOffset = _serializer.float64(obj.paraB, buffer, bufferOffset);
    // Serialize message field [deltaB]
    bufferOffset = _serializer.float64(obj.deltaB, buffer, bufferOffset);
    // Serialize message field [zdd]
    bufferOffset = _serializer.float64(obj.zdd, buffer, bufferOffset);
    // Serialize message field [commandVel]
    bufferOffset = _serializer.float64(obj.commandVel, buffer, bufferOffset);
    // Serialize message field [actualVel]
    bufferOffset = _serializer.float64(obj.actualVel, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type AdmStatus
    let len;
    let data = new AdmStatus(null);
    // Deserialize message field [forceTarget]
    data.forceTarget = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [forceNow]
    data.forceNow = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [paraB]
    data.paraB = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [deltaB]
    data.deltaB = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [zdd]
    data.zdd = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [commandVel]
    data.commandVel = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [actualVel]
    data.actualVel = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 56;
  }

  static datatype() {
    // Returns string type for a message object
    return 'szj_demo/AdmStatus';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '0eec79276a71eca81aff53272305516b';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64 forceTarget
    float64 forceNow
    float64 paraB
    float64 deltaB
    float64 zdd
    float64 commandVel
    float64 actualVel
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new AdmStatus(null);
    if (msg.forceTarget !== undefined) {
      resolved.forceTarget = msg.forceTarget;
    }
    else {
      resolved.forceTarget = 0.0
    }

    if (msg.forceNow !== undefined) {
      resolved.forceNow = msg.forceNow;
    }
    else {
      resolved.forceNow = 0.0
    }

    if (msg.paraB !== undefined) {
      resolved.paraB = msg.paraB;
    }
    else {
      resolved.paraB = 0.0
    }

    if (msg.deltaB !== undefined) {
      resolved.deltaB = msg.deltaB;
    }
    else {
      resolved.deltaB = 0.0
    }

    if (msg.zdd !== undefined) {
      resolved.zdd = msg.zdd;
    }
    else {
      resolved.zdd = 0.0
    }

    if (msg.commandVel !== undefined) {
      resolved.commandVel = msg.commandVel;
    }
    else {
      resolved.commandVel = 0.0
    }

    if (msg.actualVel !== undefined) {
      resolved.actualVel = msg.actualVel;
    }
    else {
      resolved.actualVel = 0.0
    }

    return resolved;
    }
};

module.exports = AdmStatus;
