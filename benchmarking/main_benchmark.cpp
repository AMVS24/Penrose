#include "freefall.h"
#include "orbital.h"
#include "Constants.h"

int main() {

    // ----------------------------------------------------------------
    // BENCHMARK 1: Radial free-fall
    // Drops a particle from r0 with E=1 and measures horizon crossing
    // time against the exact analytical result.
    // ----------------------------------------------------------------
    benchmark_freefall(10.0, dt);

    // ----------------------------------------------------------------
    // BENCHMARK 2: General orbit
    // Set r0, vr, vph and dt freely.
    // vt is computed automatically from the norm condition.
    //
    // Examples:
    //   Spiral infall:    r0=1.4, vr=0.0,  vph=0.05556, dt=0.0001
    //   Circular orbit:   r0=6.0, vr=0.0,  vph=0.05556, dt=0.01
    //   Radial plunge:    r0=10.0, vr=-0.5, vph=0.0,    dt=0.001
    // ----------------------------------------------------------------
    double r0        = 6.0;
    double vr        = 0.0;
    double vph       = 0.05556;
    double step_size = 0.01;
    int    max_steps = 5000000;

    benchmark_orbital(r0, vr, vph, step_size, max_steps);

    return 0;
}
