#include "ruby.h"

#define RADIAN_PER_DEGREE 0.017453292519943
#define EARTH_RADIUS 6371

// Defining a space for information and references about the module to be stored internally
VALUE HaversineDistance = Qnil;

// Prototype for the initialization method - Ruby calls this, not you
void Init_haversine_distance();

VALUE method_km(VALUE self, VALUE lat1_v, VALUE lng1_v, VALUE lat2_v, VALUE lng2_v);
VALUE method_m(VALUE self, VALUE lat1_v, VALUE lng1_v, VALUE lat2_v, VALUE lng2_v, VALUE precision);

// The initialization method for this module
void Init_haversine_distance() {
  HaversineDistance = rb_define_module("HaversineDistance");
  rb_define_singleton_method(HaversineDistance, "km", method_km, 4);
  rb_define_singleton_method(HaversineDistance, "m", method_m, 5);
}

double compute_km(double lat1, double lng1, double lat2, double lng2) {
  double lat1_radians = lat1 * RADIAN_PER_DEGREE;
  double lat2_radians = lat2 * RADIAN_PER_DEGREE;
  double distance_lat = (lat2-lat1) * RADIAN_PER_DEGREE;
  double distance_lng = (lng2-lng1) * RADIAN_PER_DEGREE;
  double a = pow(sin(distance_lat/2.0), 2.0) + cos(lat1_radians) * cos(lat2_radians) * pow(sin(distance_lng/2.0), 2.0);
  double c = 2.0 * atan2(sqrt(a), sqrt(1.0-a));
  return EARTH_RADIUS * c;
}

double round_float(double f, int prec) {
  int mult = 10 * prec;
  return roundf( mult * f) / mult;
}

VALUE method_km(VALUE self, VALUE lat1_v, VALUE lng1_v, VALUE lat2_v, VALUE lng2_v) {
  double lat1 = NUM2DBL(lat1_v);
  double lng1 = NUM2DBL(lng1_v);
  double lat2 = NUM2DBL(lat2_v);
  double lng2 = NUM2DBL(lng2_v);
  return DBL2NUM(compute_km(lat1, lng1, lat2, lng2));
}

VALUE method_m(VALUE self, VALUE lat1_v, VALUE lng1_v, VALUE lat2_v, VALUE lng2_v, VALUE precision) {
  double lat1 = NUM2DBL(lat1_v);
  double lng1 = NUM2DBL(lng1_v);
  double lat2 = NUM2DBL(lat2_v);
  double lng2 = NUM2DBL(lng2_v);
  int prec = NUM2INT(precision);
  double res = compute_km(lat1, lng1, lat2, lng2) * 1000;

  return DBL2NUM(round_float(res, prec));
}
