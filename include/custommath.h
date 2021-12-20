#ifndef __AIDENMATH__
#define __AIDENMATH__
//dont question why i made this
#include <climits>
#include <math.h>

const float radToDeg = (180/M_PI);
const float degToRad = (M_PI/180);

//sign values 
template <class T>
T sign(T val) {
  return val > 0 ? (T)1 : (T)-1;
}

template <class T>
T MAX(T INPUT, T INPUT2, T INPUT3 = INT_MIN, T INPUT4 = INT_MIN) {
  T _temp = INPUT > INPUT2 ? INPUT : INPUT2; 
  T _temp2 = INPUT3 > INPUT4 ? INPUT3 : INPUT4;
  return _temp > _temp2 ? _temp : _temp2;
}

template <class T>
T MIN(T INPUT, T INPUT2, T INPUT3 = INT_MAX, T INPUT4 = INT_MAX) {
  T _temp = INPUT < INPUT2 ? INPUT : INPUT2; 
  T _temp2 = INPUT3 < INPUT4 ? INPUT3 : INPUT4;
  return _temp < _temp2 ? _temp : _temp2;
}

template <class T>
float distanceFormula(T x1, T y1, T x2, T y2) {
  return sqrt(pow((x2-x1), 2) + pow((y2-y1), 2));
}

/* dsin function returns sine of INPUT but input and output are in degrees, same goes for all other functions */
template <class T>
float dsin(T INPUT) { return (sin(INPUT*degToRad)); }

/* dcos function */
template <class T>
float dcos(T INPUT) { return (cos(INPUT*degToRad)); }

/* dtan function */
template <class T> 
float dtan(T INPUT) { return (tan(INPUT*degToRad)); }

/* atan2 function */
template <class T>
float datan2(T INPUT, T INPUT2) { return (atan2((float)INPUT, (float)INPUT2)*radToDeg); }

/* dacos function */
template <class T> 
float dacos(T INPUT) { return acos(INPUT)*radToDeg; }

/* dasin function */
template <class T>
float dasin(T INPUT) { return asin(INPUT)*radToDeg; }

/* atan function */
template <class T>
float datan(T INPUT) { return atan(INPUT)*radToDeg; }

#endif //__AIDENMATH__
