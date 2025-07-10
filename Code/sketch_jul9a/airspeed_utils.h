#ifndef AIRSPEED_UTILS_H
#define AIRSPEED_UTILS_H

float getDifferentialPressure(int raw_pressure, float full_scale_psi = 1.0);
float calculateAirSpeed(float delta_p, float rho = 1.225);

#endif
