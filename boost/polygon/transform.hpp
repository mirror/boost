/*
    Copyright 2008 Intel Corporation

    Use, modification and distribution are subject to the Boost Software License,
    Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
*/

#ifndef BOOST_POLYGON_TRANSFORM_HPP
#define BOOST_POLYGON_TRANSFORM_HPP

#include "isotropy.hpp"

namespace boost {
namespace polygon{
// Transformation of Coordinate Systems
// Enum meaning:
// Select which direction_2d to change the positive direction of each
// axis in the old coordinate system to map it to the new coordiante system.
// The first direction_2d listed for each enum is the direction to map the
// positive horizontal direction to.
// The second direction_2d listed for each enum is the direction to map the
// positive vertical direction to.
// The zero position bit (LSB) indicates whether the horizontal axis flips
// when transformed.
// The 1st postion bit indicates whether the vertical axis flips when
// transformed.
// The 2nd position bit indicates whether the horizontal and vertical axis
// swap positions when transformed.
// Enum Values:
//   000 EAST NORTH
//   001 WEST NORTH
//   010 EAST SOUTH
//   011 WEST SOUTH
//   100 NORTH EAST
//   101 SOUTH EAST
//   110 NORTH WEST
//   111 SOUTH WEST
class axis_transformation {
 public:
  // Enum Names and values
  // NULL_TRANSFORM = 0, BEGIN_TRANSFORM = 0,
  // ENU = 0, EAST_NORTH_UP = 0, EN = 0, EAST_NORTH = 0,
  // WNU = 1, WEST_NORTH_UP = 1, WN = 1, WEST_NORTH = 1, FLIP_X = 1,
  // ESU = 2, EAST_SOUTH_UP = 2, ES = 2, EAST_SOUTH = 2, FLIP_Y = 2,
  // WSU = 3, WEST_SOUTH_UP = 3, WS = 3, WEST_SOUTH = 3,
  // NEU = 4, NORTH_EAST_UP = 4, NE = 4, NORTH_EAST = 4, SWAP_XY = 4,
  // SEU = 5, SOUTH_EAST_UP = 5, SE = 5, SOUTH_EAST = 5,
  // NWU = 6, NORTH_WEST_UP = 6, NW = 6, NORTH_WEST = 6,
  // SWU = 7, SOUTH_WEST_UP = 7, SW = 7, SOUTH_WEST = 7,
  // END_2D_TRANSFORM = 7,
  // END = 8, EAST_NORTH_DOWN = 8,
  // WND = 9, WEST_NORTH_DOWN = 9,
  // ESD = 10, EAST_SOUTH_DOWN = 10,
  // WSD = 11, WEST_SOUTH_DOWN = 11,
  // NED = 12, NORTH_EAST_DOWN = 12,
  // SED = 13, SOUTH_EAST_DOWN = 13,
  // NWD = 14, NORTH_WEST_DOWN = 14,
  // SWD = 15, SOUTH_WEST_DOWN = 15,
  // UNE = 16, UP_NORTH_EAST = 16,
  // DNE = 17, DOWN_NORTH_EAST = 17,
  // USE = 18, UP_SOUTH_EAST = 18,
  // DSE = 19, DOWN_SOUTH_EAST = 19,
  // NUE = 20, NORTH_UP_EAST = 20,
  // SUE = 21, SOUTH_UP_EAST = 21,
  // NDE = 22, NORTH_DOWN_EAST = 22,
  // SDE = 23, SOUTH_DOWN_EAST = 23,
  // UNW = 24, UP_NORTH_WEST = 24,
  // DNW = 25, DOWN_NORTH_WEST = 25,
  // USW = 26, UP_SOUTH_WEST = 26,
  // DSW = 27, DOWN_SOUTH_WEST = 27,
  // NUW = 28, NORTH_UP_WEST = 28,
  // SUW = 29, SOUTH_UP_WEST = 29,
  // NDW = 30, NORTH_DOWN_WEST = 30,
  // SDW = 31, SOUTH_DOWN_WEST = 31,
  // EUN = 32, EAST_UP_NORTH = 32,
  // WUN = 33, WEST_UP_NORTH = 33,
  // EDN = 34, EAST_DOWN_NORTH = 34,
  // WDN = 35, WEST_DOWN_NORTH = 35,
  // UEN = 36, UP_EAST_NORTH = 36,
  // DEN = 37, DOWN_EAST_NORTH = 37,
  // UWN = 38, UP_WEST_NORTH = 38,
  // DWN = 39, DOWN_WEST_NORTH = 39,
  // EUS = 40, EAST_UP_SOUTH = 40,
  // WUS = 41, WEST_UP_SOUTH = 41,
  // EDS = 42, EAST_DOWN_SOUTH = 42,
  // WDS = 43, WEST_DOWN_SOUTH = 43,
  // UES = 44, UP_EAST_SOUTH = 44,
  // DES = 45, DOWN_EAST_SOUTH = 45,
  // UWS = 46, UP_WEST_SOUTH = 46,
  // DWS = 47, DOWN_WEST_SOUTH = 47, END_TRANSFORM = 47
  enum ATR {
    NULL_TRANSFORM = 0, BEGIN_TRANSFORM = 0,
    ENU = 0, EAST_NORTH_UP = 0, EN = 0, EAST_NORTH = 0,
    WNU = 1, WEST_NORTH_UP = 1, WN = 1, WEST_NORTH = 1, FLIP_X       = 1,
    ESU = 2, EAST_SOUTH_UP = 2, ES = 2, EAST_SOUTH = 2, FLIP_Y       = 2,
    WSU = 3, WEST_SOUTH_UP = 3, WS = 3, WEST_SOUTH = 3, FLIP_XY      = 3,
    NEU = 4, NORTH_EAST_UP = 4, NE = 4, NORTH_EAST = 4, SWAP_XY      = 4,
    SEU = 5, SOUTH_EAST_UP = 5, SE = 5, SOUTH_EAST = 5, ROTATE_LEFT  = 5,
    NWU = 6, NORTH_WEST_UP = 6, NW = 6, NORTH_WEST = 6, ROTATE_RIGHT = 6,
    SWU = 7, SOUTH_WEST_UP = 7, SW = 7, SOUTH_WEST = 7, FLIP_SWAP_XY = 7, END_2D_TRANSFORM = 7,
    END = 8, EAST_NORTH_DOWN = 8, FLIP_Z = 8,
    WND = 9, WEST_NORTH_DOWN = 9,
    ESD = 10, EAST_SOUTH_DOWN = 10,
    WSD = 11, WEST_SOUTH_DOWN = 11,
    NED = 12, NORTH_EAST_DOWN = 12,
    SED = 13, SOUTH_EAST_DOWN = 13,
    NWD = 14, NORTH_WEST_DOWN = 14,
    SWD = 15, SOUTH_WEST_DOWN = 15,
    UNE = 16, UP_NORTH_EAST = 16,
    DNE = 17, DOWN_NORTH_EAST = 17,
    USE = 18, UP_SOUTH_EAST = 18,
    DSE = 19, DOWN_SOUTH_EAST = 19,
    NUE = 20, NORTH_UP_EAST = 20,
    SUE = 21, SOUTH_UP_EAST = 21,
    NDE = 22, NORTH_DOWN_EAST = 22,
    SDE = 23, SOUTH_DOWN_EAST = 23,
    UNW = 24, UP_NORTH_WEST = 24,
    DNW = 25, DOWN_NORTH_WEST = 25,
    USW = 26, UP_SOUTH_WEST = 26,
    DSW = 27, DOWN_SOUTH_WEST = 27,
    NUW = 28, NORTH_UP_WEST = 28,
    SUW = 29, SOUTH_UP_WEST = 29,
    NDW = 30, NORTH_DOWN_WEST = 30,
    SDW = 31, SOUTH_DOWN_WEST = 31,
    EUN = 32, EAST_UP_NORTH = 32,
    WUN = 33, WEST_UP_NORTH = 33,
    EDN = 34, EAST_DOWN_NORTH = 34,
    WDN = 35, WEST_DOWN_NORTH = 35,
    UEN = 36, UP_EAST_NORTH = 36,
    DEN = 37, DOWN_EAST_NORTH = 37,
    UWN = 38, UP_WEST_NORTH = 38,
    DWN = 39, DOWN_WEST_NORTH = 39,
    EUS = 40, EAST_UP_SOUTH = 40,
    WUS = 41, WEST_UP_SOUTH = 41,
    EDS = 42, EAST_DOWN_SOUTH = 42,
    WDS = 43, WEST_DOWN_SOUTH = 43,
    UES = 44, UP_EAST_SOUTH = 44,
    DES = 45, DOWN_EAST_SOUTH = 45,
    UWS = 46, UP_WEST_SOUTH = 46,
    DWS = 47, DOWN_WEST_SOUTH = 47, END_TRANSFORM = 47
  };

  // Individual axis enum values indicate which axis an implicit individual
  // axis will be mapped to.
  // The value of the enum paired with an axis provides the information
  // about what the axis will transform to.
  // Three individual axis values, one for each axis, are equivalent to one
  // ATR enum value, but easier to work with because they are independent.
  // Converting to and from the individual axis values from the ATR value
  // is a convenient way to implement tranformation related functionality.
  // Enum meanings:
  // PX: map to positive x axis
  // NX: map to negative x axis
  // PY: map to positive y axis
  // NY: map to negative y axis
  // PZ: map to positive z axis
  // NZ: map to negative z axis
  enum INDIVIDUAL_AXIS {
    PX = 0,
    NX = 1,
    PY = 2,
    NY = 3,
    PZ = 4,
    NZ = 5
  };

  inline axis_transformation() : atr_(NULL_TRANSFORM) {}
  inline axis_transformation(ATR atr) : atr_(atr) {}
  inline axis_transformation(const axis_transformation& atr) : atr_(atr.atr_) {}
  explicit axis_transformation(const orientation_3d& orient);
  explicit axis_transformation(const direction_3d& dir);
  explicit axis_transformation(const orientation_2d& orient);
  explicit axis_transformation(const direction_2d& dir);

  // assignment operator
  axis_transformation& operator=(const axis_transformation& a);

  // assignment operator
  axis_transformation& operator=(const ATR& atr);

  // equivalence operator
  bool operator==(const axis_transformation& a) const;

  // inequivalence operator
  bool operator!=(const axis_transformation& a) const;

  // ordering
  bool operator<(const axis_transformation& a) const;

  // concatenation operator
  axis_transformation operator+(const axis_transformation& a) const;

  // concatenate this with that
  axis_transformation& operator+=(const axis_transformation& a);

  // populate_axis_array writes the three INDIVIDUAL_AXIS values that the
  // ATR enum value of 'this' represent into axis_array
  void populate_axis_array(INDIVIDUAL_AXIS axis_array[]) const;

  // it is recommended that the directions stored in an array
  // in the caller code for easier isotropic access by orientation value
  inline void get_directions(direction_2d& horizontal_dir,
                             direction_2d& vertical_dir) const {
    bool bit2 = (atr_ & 4) != 0;
    bool bit1 = (atr_ & 2) != 0;
    bool bit0 = (atr_ & 1) != 0;
    vertical_dir = direction_2d((direction_2d_enum)(((int)(!bit2) << 1) + !bit1));
    horizontal_dir = direction_2d((direction_2d_enum)(((int)(bit2) << 1) + !bit0));
  }

  // it is recommended that the directions stored in an array
  // in the caller code for easier isotropic access by orientation value
  inline void get_directions(direction_3d& horizontal_dir,
                             direction_3d& vertical_dir,
                             direction_3d& proximal_dir) const {
    bool bit5 = (atr_ & 32) != 0;
    bool bit4 = (atr_ & 16) != 0;
    bool bit3 = (atr_ & 8) != 0;
    bool bit2 = (atr_ & 4) != 0;
    bool bit1 = (atr_ & 2) != 0;
    bool bit0 = (atr_ & 1) != 0;
    proximal_dir = direction_3d((direction_2d_enum)((((int)(!bit4 & !bit5)) << 2) +
                                                    ((int)(bit5) << 1) +
                                                    !bit3));
    vertical_dir = direction_3d((direction_2d_enum)((((int)((bit4 & bit2) | (bit5 & !bit2))) << 2)+
                                                    ((int)(!bit5 & !bit2) << 1) +
                                                    !bit1));
    horizontal_dir = direction_3d((direction_2d_enum)((((int)((bit5 & bit2) |
                                                              (bit4 & !bit2))) << 2) +
                                                      ((int)(bit2 & !bit5) << 1) +
                                                      !bit0));
  }

  // combine_axis_arrays concatenates this_array and that_array overwriting
  // the result into this_array
  static void combine_axis_arrays (INDIVIDUAL_AXIS this_array[],
                                   const INDIVIDUAL_AXIS that_array[]);

  // write_back_axis_array converts an array of three INDIVIDUAL_AXIS values
  // to the ATR enum value and sets 'this' to that value
  void write_back_axis_array(const INDIVIDUAL_AXIS this_array[]);

  // behavior is deterministic but undefined in the case where illegal
  // combinations of directions are passed in.
  axis_transformation& set_directions(const direction_2d& horizontal_dir,
                                 const direction_2d& vertical_dir);
  // behavior is deterministic but undefined in the case where illegal
  // combinations of directions are passed in.
  axis_transformation& set_directions(const direction_3d& horizontal_dir,
                                 const direction_3d& vertical_dir,
                                 const direction_3d& proximal_dir);

  // transform the two coordinates by reference using the 2D portion of this
  template <typename coordinate_type>
  void transform(coordinate_type& x, coordinate_type& y) const;

  // transform the three coordinates by reference
  template <typename coordinate_type>
  void transform(coordinate_type& x, coordinate_type& y, coordinate_type& z) const;

  // invert the 2D portion of this
  axis_transformation& invert_2d();

  // get the inverse of the 2D portion of this
  axis_transformation inverse_2d() const;

  // invert this axis_transformation
  axis_transformation& invert();

  // get the inverse axis_transformation of this
  axis_transformation inverse() const;

  //friend std::ostream& operator<< (std::ostream& o, const axis_transformation& r);
  //friend std::istream& operator>> (std::istream& i, axis_transformation& r);

private:
  ATR atr_;
};


// Scaling object to be used to store the scale factor for each axis

// For use by the transformation object, in that context the scale factor
// is the amount that each axis scales by when transformed.
// If the horizontal value of the Scale is 10 that means the horizontal
// axis of the input is multiplied by 10 when the transformation is applied.
template <typename scale_factor_type>
class anisotropic_scale_factor {
public:
  inline anisotropic_scale_factor()
#ifndef BOOST_POLYGON_MSVC
    : scale_()
#endif
  {
    scale_[0] = 1;
    scale_[1] = 1;
    scale_[2] = 1;
  }
  inline anisotropic_scale_factor(scale_factor_type xscale, scale_factor_type yscale)
#ifndef BOOST_POLYGON_MSVC
    : scale_()
#endif
  {
    scale_[0] = xscale;
    scale_[1] = yscale;
    scale_[2] = 1;
  }
  inline anisotropic_scale_factor(scale_factor_type xscale, scale_factor_type yscale, scale_factor_type zscale)
#ifndef BOOST_POLYGON_MSVC
    : scale_()
#endif
  {
    scale_[0] = xscale;
    scale_[1] = yscale;
    scale_[2] = zscale;
  }

  // get a component of the anisotropic_scale_factor by orientation
  scale_factor_type get(orientation_3d orient) const;
  scale_factor_type get(orientation_2d orient) const { return get(orientation_3d(orient)); }

  // set a component of the anisotropic_scale_factor by orientation
  void set(orientation_3d orient, scale_factor_type value);
  void set(orientation_2d orient, scale_factor_type value) { set(orientation_3d(orient), value); }

  scale_factor_type x() const;
  scale_factor_type y() const;
  scale_factor_type z() const;
  void x(scale_factor_type value);
  void y(scale_factor_type value);
  void z(scale_factor_type value);

  // concatination operator (convolve scale factors)
  anisotropic_scale_factor operator+(const anisotropic_scale_factor& s) const;

  // concatinate this with that
  const anisotropic_scale_factor& operator+=(const anisotropic_scale_factor& s);

  // transform this scale with an axis_transform
  anisotropic_scale_factor& transform(axis_transformation atr);

  // scale the two coordinates
  template <typename coordinate_type>
  void scale(coordinate_type& x, coordinate_type& y) const;

  // scale the three coordinates
  template <typename coordinate_type>
  void scale(coordinate_type& x, coordinate_type& y, coordinate_type& z) const;

  // invert this scale factor to give the reverse scale factor
  anisotropic_scale_factor& invert();

private:
  scale_factor_type scale_[3];
};

// Transformation object, stores and provides services for transformations.
// Consits of axis transformation, scale factor and translation.
// The tranlation is the position of the origin of the new coordinate system of
// in the old system. Coordinates are scaled before they are transformed.
template <typename coordinate_type>
class transformation {
 public:
  transformation() : atr_(), p_(0, 0) {}
  transformation(axis_transformation atr) : atr_(atr), p_(0, 0) {}
  transformation(axis_transformation::ATR atr) : atr_(atr), p_(0, 0) {}
  transformation(const transformation& tr) : atr_(tr.atr_), p_(tr.p_) {}

  template <typename point_type>
  transformation(const point_type& p) : atr_(), p_(0, 0) {
    set_translation(p);
  }

  template <typename point_type>
  transformation(axis_transformation atr,
                 const point_type& p) : atr_(atr), p_(0, 0) {
    set_translation(p);
  }

  template <typename point_type>
  transformation(axis_transformation atr,
                 const point_type& referencePt,
                 const point_type& destinationPt) : atr_(), p_(0, 0) {
    transformation<coordinate_type> tmp(referencePt);
    transformation<coordinate_type> rotRef(atr);
    transformation<coordinate_type> tmpInverse = tmp.inverse();
    point_type decon(referencePt);
    deconvolve(decon, destinationPt);
    transformation<coordinate_type> displacement(decon);
    tmp += rotRef;
    tmp += tmpInverse;
    tmp += displacement;
    (*this) = tmp;
  }

  // equivalence operator
  bool operator==(const transformation& tr) const {
    return (atr_ == tr.atr_) && (p_ == tr.p_);
  }

  // inequivalence operator
  bool operator!=(const transformation& tr) const {
    return !(*this == tr);
  }

  // ordering
  bool operator<(const transformation& tr) const {
    return (atr_ < tr.atr_) || ((atr_ == tr.atr_) && (p_ < tr.p_));
  }

  // concatenation operator
  transformation operator+(const transformation& tr) const {
    transformation<coordinate_type> retval(*this);
    return retval+=tr;
  }

  // concatenate this with that
  const transformation& operator+=(const transformation& tr) {
    coordinate_type x, y;
    transformation<coordinate_type> inv = inverse();
    inv.transform(x, y);
    p_.set(HORIZONTAL, p_.get(HORIZONTAL) + x);
    p_.set(VERTICAL, p_.get(VERTICAL) + y);
    //concatenate axis transforms
    atr_ += tr.atr_;
    return *this;
  }

  // get the axis_transformation portion of this
  axis_transformation get_axis_transformation() const {
    return atr_;
  }

  // set the axis_transformation portion of this
  void set_axis_transformation(const axis_transformation& atr) {
    atr_ = atr;
  }

  // get the translation portion of this as a point3d
  template <typename point_type>
  void get_translation(point_type& p) const {
    assign(p, p_);
  }

  // set the translation portion of this with a point3d
  template <typename point_type>
  void set_translation(const point_type& p) {
    assign(p_, p);
  }

  // apply the 2D portion of this transformation to the two coordinates given
  void transform(coordinate_type& x, coordinate_type& y) const {
    y -= p_.get(VERTICAL);
    x -= p_.get(HORIZONTAL);
    atr_.transform(x, y);
  }

  // invert this transformation
  transformation& invert() {
    coordinate_type x = p_.get(HORIZONTAL), y = p_.get(VERTICAL);
    atr_.transform(x, y);
    x *= -1;
    y *= -1;
    p_ = point_data<coordinate_type>(x, y);
    atr_.invert();
    return *this;
  }

  // get the inverse of this transformation
  transformation inverse() const {
    transformation<coordinate_type> ret_val(*this);
    return ret_val.invert();
  }

  void get_directions(direction_2d& horizontal_dir,
                      direction_2d& vertical_dir) const {
    return atr_.get_directions(horizontal_dir, vertical_dir);
  }

 private:
  axis_transformation atr_;
  point_data<coordinate_type> p_;
};
}  // polygon
}  // boost

#include "detail/transform_detail.hpp"
#endif
