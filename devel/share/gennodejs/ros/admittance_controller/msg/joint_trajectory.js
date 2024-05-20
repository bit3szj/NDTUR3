// Auto-generated. Do not edit!

// (in-package admittance_controller.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let parameter_msg = require('./parameter_msg.js');
let sensor_msgs = _finder('sensor_msgs');

//-----------------------------------------------------------

class joint_trajectory {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.trajectory = null;
      this.extra_data = null;
      this.velocity_scaling_percentage = null;
    }
    else {
      if (initObj.hasOwnProperty('trajectory')) {
        this.trajectory = initObj.trajectory
      }
      else {
        this.trajectory = [];
      }
      if (initObj.hasOwnProperty('extra_data')) {
        this.extra_data = initObj.extra_data
      }
      else {
        this.extra_data = [];
      }
      if (initObj.hasOwnProperty('velocity_scaling_percentage')) {
        this.velocity_scaling_percentage = initObj.velocity_scaling_percentage
      }
      else {
        this.velocity_scaling_percentage = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type joint_trajectory
    // Serialize message field [trajectory]
    // Serialize the length for message field [trajectory]
    bufferOffset = _serializer.uint32(obj.trajectory.length, buffer, bufferOffset);
    obj.trajectory.forEach((val) => {
      bufferOffset = sensor_msgs.msg.JointState.serialize(val, buffer, bufferOffset);
    });
    // Serialize message field [extra_data]
    // Serialize the length for message field [extra_data]
    bufferOffset = _serializer.uint32(obj.extra_data.length, buffer, bufferOffset);
    obj.extra_data.forEach((val) => {
      bufferOffset = parameter_msg.serialize(val, buffer, bufferOffset);
    });
    // Serialize message field [velocity_scaling_percentage]
    bufferOffset = _serializer.int64(obj.velocity_scaling_percentage, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type joint_trajectory
    let len;
    let data = new joint_trajectory(null);
    // Deserialize message field [trajectory]
    // Deserialize array length for message field [trajectory]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.trajectory = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.trajectory[i] = sensor_msgs.msg.JointState.deserialize(buffer, bufferOffset)
    }
    // Deserialize message field [extra_data]
    // Deserialize array length for message field [extra_data]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.extra_data = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.extra_data[i] = parameter_msg.deserialize(buffer, bufferOffset)
    }
    // Deserialize message field [velocity_scaling_percentage]
    data.velocity_scaling_percentage = _deserializer.int64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    object.trajectory.forEach((val) => {
      length += sensor_msgs.msg.JointState.getMessageSize(val);
    });
    object.extra_data.forEach((val) => {
      length += parameter_msg.getMessageSize(val);
    });
    return length + 16;
  }

  static datatype() {
    // Returns string type for a message object
    return 'admittance_controller/joint_trajectory';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '9047f34bd5bbdb3efed33b5595650679';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    sensor_msgs/JointState[] trajectory
    parameter_msg[] extra_data
    int64 velocity_scaling_percentage
    
    ================================================================================
    MSG: sensor_msgs/JointState
    # This is a message that holds data to describe the state of a set of torque controlled joints. 
    #
    # The state of each joint (revolute or prismatic) is defined by:
    #  * the position of the joint (rad or m),
    #  * the velocity of the joint (rad/s or m/s) and 
    #  * the effort that is applied in the joint (Nm or N).
    #
    # Each joint is uniquely identified by its name
    # The header specifies the time at which the joint states were recorded. All the joint states
    # in one message have to be recorded at the same time.
    #
    # This message consists of a multiple arrays, one for each part of the joint state. 
    # The goal is to make each of the fields optional. When e.g. your joints have no
    # effort associated with them, you can leave the effort array empty. 
    #
    # All arrays in this message should have the same size, or be empty.
    # This is the only way to uniquely associate the joint name with the correct
    # states.
    
    
    Header header
    
    string[] name
    float64[] position
    float64[] velocity
    float64[] effort
    
    ================================================================================
    MSG: std_msgs/Header
    # Standard metadata for higher-level stamped data types.
    # This is generally used to communicate timestamped data 
    # in a particular coordinate frame.
    # 
    # sequence ID: consecutively increasing ID 
    uint32 seq
    #Two-integer timestamp that is expressed as:
    # * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
    # * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
    # time-handling sugar is provided by the client library
    time stamp
    #Frame this data is associated with
    string frame_id
    
    ================================================================================
    MSG: admittance_controller/parameter_msg
    string parameter_name
    float32 parameter_value
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new joint_trajectory(null);
    if (msg.trajectory !== undefined) {
      resolved.trajectory = new Array(msg.trajectory.length);
      for (let i = 0; i < resolved.trajectory.length; ++i) {
        resolved.trajectory[i] = sensor_msgs.msg.JointState.Resolve(msg.trajectory[i]);
      }
    }
    else {
      resolved.trajectory = []
    }

    if (msg.extra_data !== undefined) {
      resolved.extra_data = new Array(msg.extra_data.length);
      for (let i = 0; i < resolved.extra_data.length; ++i) {
        resolved.extra_data[i] = parameter_msg.Resolve(msg.extra_data[i]);
      }
    }
    else {
      resolved.extra_data = []
    }

    if (msg.velocity_scaling_percentage !== undefined) {
      resolved.velocity_scaling_percentage = msg.velocity_scaling_percentage;
    }
    else {
      resolved.velocity_scaling_percentage = 0
    }

    return resolved;
    }
};

module.exports = joint_trajectory;
