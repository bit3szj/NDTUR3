// Generated by gencpp from file admittance_controller/parameter_srvRequest.msg
// DO NOT EDIT!


#ifndef ADMITTANCE_CONTROLLER_MESSAGE_PARAMETER_SRVREQUEST_H
#define ADMITTANCE_CONTROLLER_MESSAGE_PARAMETER_SRVREQUEST_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace admittance_controller
{
template <class ContainerAllocator>
struct parameter_srvRequest_
{
  typedef parameter_srvRequest_<ContainerAllocator> Type;

  parameter_srvRequest_()
    : parameter_name()
    , parameter_value(0.0)  {
    }
  parameter_srvRequest_(const ContainerAllocator& _alloc)
    : parameter_name(_alloc)
    , parameter_value(0.0)  {
  (void)_alloc;
    }



   typedef std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> _parameter_name_type;
  _parameter_name_type parameter_name;

   typedef float _parameter_value_type;
  _parameter_value_type parameter_value;





  typedef boost::shared_ptr< ::admittance_controller::parameter_srvRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::admittance_controller::parameter_srvRequest_<ContainerAllocator> const> ConstPtr;

}; // struct parameter_srvRequest_

typedef ::admittance_controller::parameter_srvRequest_<std::allocator<void> > parameter_srvRequest;

typedef boost::shared_ptr< ::admittance_controller::parameter_srvRequest > parameter_srvRequestPtr;
typedef boost::shared_ptr< ::admittance_controller::parameter_srvRequest const> parameter_srvRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::admittance_controller::parameter_srvRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::admittance_controller::parameter_srvRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::admittance_controller::parameter_srvRequest_<ContainerAllocator1> & lhs, const ::admittance_controller::parameter_srvRequest_<ContainerAllocator2> & rhs)
{
  return lhs.parameter_name == rhs.parameter_name &&
    lhs.parameter_value == rhs.parameter_value;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::admittance_controller::parameter_srvRequest_<ContainerAllocator1> & lhs, const ::admittance_controller::parameter_srvRequest_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace admittance_controller

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::admittance_controller::parameter_srvRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::admittance_controller::parameter_srvRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::admittance_controller::parameter_srvRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::admittance_controller::parameter_srvRequest_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::admittance_controller::parameter_srvRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::admittance_controller::parameter_srvRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::admittance_controller::parameter_srvRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "2222a6ad43d45b6065719775535b8a26";
  }

  static const char* value(const ::admittance_controller::parameter_srvRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x2222a6ad43d45b60ULL;
  static const uint64_t static_value2 = 0x65719775535b8a26ULL;
};

template<class ContainerAllocator>
struct DataType< ::admittance_controller::parameter_srvRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "admittance_controller/parameter_srvRequest";
  }

  static const char* value(const ::admittance_controller::parameter_srvRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::admittance_controller::parameter_srvRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "string parameter_name\n"
"float32 parameter_value\n"
;
  }

  static const char* value(const ::admittance_controller::parameter_srvRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::admittance_controller::parameter_srvRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.parameter_name);
      stream.next(m.parameter_value);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct parameter_srvRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::admittance_controller::parameter_srvRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::admittance_controller::parameter_srvRequest_<ContainerAllocator>& v)
  {
    s << indent << "parameter_name: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>::stream(s, indent + "  ", v.parameter_name);
    s << indent << "parameter_value: ";
    Printer<float>::stream(s, indent + "  ", v.parameter_value);
  }
};

} // namespace message_operations
} // namespace ros

#endif // ADMITTANCE_CONTROLLER_MESSAGE_PARAMETER_SRVREQUEST_H
