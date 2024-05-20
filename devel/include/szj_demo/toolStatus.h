// Generated by gencpp from file szj_demo/toolStatus.msg
// DO NOT EDIT!


#ifndef SZJ_DEMO_MESSAGE_TOOLSTATUS_H
#define SZJ_DEMO_MESSAGE_TOOLSTATUS_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace szj_demo
{
template <class ContainerAllocator>
struct toolStatus_
{
  typedef toolStatus_<ContainerAllocator> Type;

  toolStatus_()
    : linearX(0.0)
    , linearY(0.0)
    , linearZ(0.0)
    , angularX(0.0)
    , angularY(0.0)
    , angularZ(0.0)
    , velLinearX(0.0)
    , velLinearY(0.0)
    , velLinearZ(0.0)
    , velAngularX(0.0)
    , velAngularY(0.0)
    , velAngularZ(0.0)  {
    }
  toolStatus_(const ContainerAllocator& _alloc)
    : linearX(0.0)
    , linearY(0.0)
    , linearZ(0.0)
    , angularX(0.0)
    , angularY(0.0)
    , angularZ(0.0)
    , velLinearX(0.0)
    , velLinearY(0.0)
    , velLinearZ(0.0)
    , velAngularX(0.0)
    , velAngularY(0.0)
    , velAngularZ(0.0)  {
  (void)_alloc;
    }



   typedef double _linearX_type;
  _linearX_type linearX;

   typedef double _linearY_type;
  _linearY_type linearY;

   typedef double _linearZ_type;
  _linearZ_type linearZ;

   typedef double _angularX_type;
  _angularX_type angularX;

   typedef double _angularY_type;
  _angularY_type angularY;

   typedef double _angularZ_type;
  _angularZ_type angularZ;

   typedef double _velLinearX_type;
  _velLinearX_type velLinearX;

   typedef double _velLinearY_type;
  _velLinearY_type velLinearY;

   typedef double _velLinearZ_type;
  _velLinearZ_type velLinearZ;

   typedef double _velAngularX_type;
  _velAngularX_type velAngularX;

   typedef double _velAngularY_type;
  _velAngularY_type velAngularY;

   typedef double _velAngularZ_type;
  _velAngularZ_type velAngularZ;





  typedef boost::shared_ptr< ::szj_demo::toolStatus_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::szj_demo::toolStatus_<ContainerAllocator> const> ConstPtr;

}; // struct toolStatus_

typedef ::szj_demo::toolStatus_<std::allocator<void> > toolStatus;

typedef boost::shared_ptr< ::szj_demo::toolStatus > toolStatusPtr;
typedef boost::shared_ptr< ::szj_demo::toolStatus const> toolStatusConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::szj_demo::toolStatus_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::szj_demo::toolStatus_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::szj_demo::toolStatus_<ContainerAllocator1> & lhs, const ::szj_demo::toolStatus_<ContainerAllocator2> & rhs)
{
  return lhs.linearX == rhs.linearX &&
    lhs.linearY == rhs.linearY &&
    lhs.linearZ == rhs.linearZ &&
    lhs.angularX == rhs.angularX &&
    lhs.angularY == rhs.angularY &&
    lhs.angularZ == rhs.angularZ &&
    lhs.velLinearX == rhs.velLinearX &&
    lhs.velLinearY == rhs.velLinearY &&
    lhs.velLinearZ == rhs.velLinearZ &&
    lhs.velAngularX == rhs.velAngularX &&
    lhs.velAngularY == rhs.velAngularY &&
    lhs.velAngularZ == rhs.velAngularZ;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::szj_demo::toolStatus_<ContainerAllocator1> & lhs, const ::szj_demo::toolStatus_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace szj_demo

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::szj_demo::toolStatus_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::szj_demo::toolStatus_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::szj_demo::toolStatus_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::szj_demo::toolStatus_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::szj_demo::toolStatus_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::szj_demo::toolStatus_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::szj_demo::toolStatus_<ContainerAllocator> >
{
  static const char* value()
  {
    return "fc2d79cf8b7f949061e6ffc3b214e01e";
  }

  static const char* value(const ::szj_demo::toolStatus_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xfc2d79cf8b7f9490ULL;
  static const uint64_t static_value2 = 0x61e6ffc3b214e01eULL;
};

template<class ContainerAllocator>
struct DataType< ::szj_demo::toolStatus_<ContainerAllocator> >
{
  static const char* value()
  {
    return "szj_demo/toolStatus";
  }

  static const char* value(const ::szj_demo::toolStatus_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::szj_demo::toolStatus_<ContainerAllocator> >
{
  static const char* value()
  {
    return "float64 linearX\n"
"float64 linearY\n"
"float64 linearZ\n"
"float64 angularX\n"
"float64 angularY\n"
"float64 angularZ\n"
"float64 velLinearX\n"
"float64 velLinearY\n"
"float64 velLinearZ\n"
"float64 velAngularX\n"
"float64 velAngularY\n"
"float64 velAngularZ\n"
;
  }

  static const char* value(const ::szj_demo::toolStatus_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::szj_demo::toolStatus_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.linearX);
      stream.next(m.linearY);
      stream.next(m.linearZ);
      stream.next(m.angularX);
      stream.next(m.angularY);
      stream.next(m.angularZ);
      stream.next(m.velLinearX);
      stream.next(m.velLinearY);
      stream.next(m.velLinearZ);
      stream.next(m.velAngularX);
      stream.next(m.velAngularY);
      stream.next(m.velAngularZ);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct toolStatus_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::szj_demo::toolStatus_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::szj_demo::toolStatus_<ContainerAllocator>& v)
  {
    s << indent << "linearX: ";
    Printer<double>::stream(s, indent + "  ", v.linearX);
    s << indent << "linearY: ";
    Printer<double>::stream(s, indent + "  ", v.linearY);
    s << indent << "linearZ: ";
    Printer<double>::stream(s, indent + "  ", v.linearZ);
    s << indent << "angularX: ";
    Printer<double>::stream(s, indent + "  ", v.angularX);
    s << indent << "angularY: ";
    Printer<double>::stream(s, indent + "  ", v.angularY);
    s << indent << "angularZ: ";
    Printer<double>::stream(s, indent + "  ", v.angularZ);
    s << indent << "velLinearX: ";
    Printer<double>::stream(s, indent + "  ", v.velLinearX);
    s << indent << "velLinearY: ";
    Printer<double>::stream(s, indent + "  ", v.velLinearY);
    s << indent << "velLinearZ: ";
    Printer<double>::stream(s, indent + "  ", v.velLinearZ);
    s << indent << "velAngularX: ";
    Printer<double>::stream(s, indent + "  ", v.velAngularX);
    s << indent << "velAngularY: ";
    Printer<double>::stream(s, indent + "  ", v.velAngularY);
    s << indent << "velAngularZ: ";
    Printer<double>::stream(s, indent + "  ", v.velAngularZ);
  }
};

} // namespace message_operations
} // namespace ros

#endif // SZJ_DEMO_MESSAGE_TOOLSTATUS_H