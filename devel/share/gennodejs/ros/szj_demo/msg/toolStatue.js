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

class toolStatue {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.linearX = null;
      this.linearY = null;
      this.linearZ = null;
      this.angularX = null;
      this.angularY = null;
      this.angularZ = null;
      this.velLinearX = null;
      this.velLinearY = null;
      this.velLinearZ = null;
      this.velAngularX = null;
      this.velAngularY = null;
      this.velAngularZ = null;
    }
    else {
      if (initObj.hasOwnProperty('linearX')) {
        this.linearX = initObj.linearX
      }
      else {
        this.linearX = 0.0;
      }
      if (initObj.hasOwnProperty('linearY')) {
        this.linearY = initObj.linearY
      }
      else {
        this.linearY = 0.0;
      }
      if (initObj.hasOwnProperty('linearZ')) {
        this.linearZ = initObj.linearZ
      }
      else {
        this.linearZ = 0.0;
      }
      if (initObj.hasOwnProperty('angularX')) {
        this.angularX = initObj.angularX
      }
      else {
        this.angularX = 0.0;
      }
      if (initObj.hasOwnProperty('angularY')) {
        this.angularY = initObj.angularY
      }
      else {
        this.angularY = 0.0;
      }
      if (initObj.hasOwnProperty('angularZ')) {
        this.angularZ = initObj.angularZ
      }
      else {
        this.angularZ = 0.0;
      }
      if (initObj.hasOwnProperty('velLinearX')) {
        this.velLinearX = initObj.velLinearX
      }
      else {
        this.velLinearX = 0.0;
      }
      if (initObj.hasOwnProperty('velLinearY')) {
        this.velLinearY = initObj.velLinearY
      }
      else {
        this.velLinearY = 0.0;
      }
      if (initObj.hasOwnProperty('velLinearZ')) {
        this.velLinearZ = initObj.velLinearZ
      }
      else {
        this.velLinearZ = 0.0;
      }
      if (initObj.hasOwnProperty('velAngularX')) {
        this.velAngularX = initObj.velAngularX
      }
      else {
        this.velAngularX = 0.0;
      }
      if (initObj.hasOwnProperty('velAngularY')) {
        this.velAngularY = initObj.velAngularY
      }
      else {
        this.velAngularY = 0.0;
      }
      if (initObj.hasOwnProperty('velAngularZ')) {
        this.velAngularZ = initObj.velAngularZ
      }
      else {
        this.velAngularZ = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type toolStatue
    // Serialize message field [linearX]
    bufferOffset = _serializer.float64(obj.linearX, buffer, bufferOffset);
    // Serialize message field [linearY]
    bufferOffset = _serializer.float64(obj.linearY, buffer, bufferOffset);
    // Serialize message field [linearZ]
    bufferOffset = _serializer.float64(obj.linearZ, buffer, bufferOffset);
    // Serialize message field [angularX]
    bufferOffset = _serializer.float64(obj.angularX, buffer, bufferOffset);
    // Serialize message field [angularY]
    bufferOffset = _serializer.float64(obj.angularY, buffer, bufferOffset);
    // Serialize message field [angularZ]
    bufferOffset = _serializer.float64(obj.angularZ, buffer, bufferOffset);
    // Serialize message field [velLinearX]
    bufferOffset = _serializer.float64(obj.velLinearX, buffer, bufferOffset);
    // Serialize message field [velLinearY]
    bufferOffset = _serializer.float64(obj.velLinearY, buffer, bufferOffset);
    // Serialize message field [velLinearZ]
    bufferOffset = _serializer.float64(obj.velLinearZ, buffer, bufferOffset);
    // Serialize message field [velAngularX]
    bufferOffset = _serializer.float64(obj.velAngularX, buffer, bufferOffset);
    // Serialize message field [velAngularY]
    bufferOffset = _serializer.float64(obj.velAngularY, buffer, bufferOffset);
    // Serialize message field [velAngularZ]
    bufferOffset = _serializer.float64(obj.velAngularZ, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type toolStatue
    let len;
    let data = new toolStatue(null);
    // Deserialize message field [linearX]
    data.linearX = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [linearY]
    data.linearY = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [linearZ]
    data.linearZ = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [angularX]
    data.angularX = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [angularY]
    data.angularY = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [angularZ]
    data.angularZ = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [velLinearX]
    data.velLinearX = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [velLinearY]
    data.velLinearY = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [velLinearZ]
    data.velLinearZ = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [velAngularX]
    data.velAngularX = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [velAngularY]
    data.velAngularY = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [velAngularZ]
    data.velAngularZ = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 96;
  }

  static datatype() {
    // Returns string type for a message object
    return 'szj_demo/toolStatue';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'fc2d79cf8b7f949061e6ffc3b214e01e';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64 linearX
    float64 linearY
    float64 linearZ
    float64 angularX
    float64 angularY
    float64 angularZ
    float64 velLinearX
    float64 velLinearY
    float64 velLinearZ
    float64 velAngularX
    float64 velAngularY
    float64 velAngularZ
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new toolStatue(null);
    if (msg.linearX !== undefined) {
      resolved.linearX = msg.linearX;
    }
    else {
      resolved.linearX = 0.0
    }

    if (msg.linearY !== undefined) {
      resolved.linearY = msg.linearY;
    }
    else {
      resolved.linearY = 0.0
    }

    if (msg.linearZ !== undefined) {
      resolved.linearZ = msg.linearZ;
    }
    else {
      resolved.linearZ = 0.0
    }

    if (msg.angularX !== undefined) {
      resolved.angularX = msg.angularX;
    }
    else {
      resolved.angularX = 0.0
    }

    if (msg.angularY !== undefined) {
      resolved.angularY = msg.angularY;
    }
    else {
      resolved.angularY = 0.0
    }

    if (msg.angularZ !== undefined) {
      resolved.angularZ = msg.angularZ;
    }
    else {
      resolved.angularZ = 0.0
    }

    if (msg.velLinearX !== undefined) {
      resolved.velLinearX = msg.velLinearX;
    }
    else {
      resolved.velLinearX = 0.0
    }

    if (msg.velLinearY !== undefined) {
      resolved.velLinearY = msg.velLinearY;
    }
    else {
      resolved.velLinearY = 0.0
    }

    if (msg.velLinearZ !== undefined) {
      resolved.velLinearZ = msg.velLinearZ;
    }
    else {
      resolved.velLinearZ = 0.0
    }

    if (msg.velAngularX !== undefined) {
      resolved.velAngularX = msg.velAngularX;
    }
    else {
      resolved.velAngularX = 0.0
    }

    if (msg.velAngularY !== undefined) {
      resolved.velAngularY = msg.velAngularY;
    }
    else {
      resolved.velAngularY = 0.0
    }

    if (msg.velAngularZ !== undefined) {
      resolved.velAngularZ = msg.velAngularZ;
    }
    else {
      resolved.velAngularZ = 0.0
    }

    return resolved;
    }
};

module.exports = toolStatue;
