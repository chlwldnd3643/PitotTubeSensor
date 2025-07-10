#include <math.h>
#include "airspeed_utils.h"

float getDifferentialPressure(int raw_pressure, float full_scale_psi) {
    float diff_psi = ((raw_pressure - 8192.0) / 8192.0) * full_scale_psi;
    return diff_psi * 6894.76;
}

float calculateAirSpeed(float delta_p, float rho) {
    if (delta_p < 0) delta_p = 0;
    return sqrt(2 * delta_p / rho) * 3.6;  // km/h
}
