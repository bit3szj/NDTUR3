// Auto-generated. Do not edit!

// (in-package admittance_controller.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class parameter_msg {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.parameter_name = null;
      this.parameter_value = null;
    }
    else {
      if (initObj.hasOwnProperty('parameter_name')) {
        this.parameter_name = initObj.parameter_name
      }
      else {
        this.parameter_name = '';
      }
      if (initObj.hasOwnProperty('parameter_value')) {
        this.parameter_value = initObj.parameter_value
      }
      else {
        this.parameter_value = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type parameter_msg
    // Serialize message field [parameter_name]
    bufferOffset = _serializer.string(obj.parameter_name, buffer, bufferOffset);
    // Serialize message field [parameter_value]
    bufferOffset = _serializer.float32(obj.parameter_value, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type parameter_msg
    let len;
    let data = new parameter_msg(null);
    // Deserialize message field [parameter_name]
    data.parameter_name = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [parameter_value]
    data.parameter_value = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += _getByteLength(object.parameter_name);
    return length + 8;
  }

  static datatype() {
    // Returns string type for a message object
    return 'admittance_controller/parameter_msg';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '2222a6ad43d45b6065719775535b8a26';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string parameter_name
    float32 parameter_value
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new parameter_msg(null);
    if (msg.parameter_name !== undefined) {
      resolved.parameter_name = msg.parameter_name;
    }
    else {
      resolved.parameter_name = ''
    }

    if (msg.parameter_value !== undefined) {
      resolved.parameter_value = msg.parameter_value;
    }
    else {
      resolved.parameter_value = 0.0
    }

    return resolved;
    }
};

module.exports = parameter_msg;
