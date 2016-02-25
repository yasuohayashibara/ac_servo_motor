// Chiba Institute of Technology

#ifndef MBED_ACMOTOR_H
#define MBED_ACMOTOR_H

#include "mbed.h"

/** Class to control a motor on any pin, without using pwm pin
 *
 * Example:
 * @code
 * // ACMotor Control
 * #include "mbed.h"
 * #include "ACMotor.h"
 *
 * ACMotor motor(xp31, xp32, xp33);
 * ACMotor motor(xp34, xp35, xp36);
 *
 * int main(){
 * while(1) {
 *     for (int pos = 1000; pos < 2000; pos += 25) {
 *         Servo1.SetPosition(pos);
 *         wait_ms(20);
 *     }
 *     for (int pos = 2000; pos > 1000; pos -= 25) {
 *         Servo1.SetPosition(pos);
 *         wait_ms(20);
 *     }
 * }
 * @endcode
 */


class ACMotor
{
public:
    /** Create a new SoftwarePWM object on any mbed pin
      *
      * @param Pin Pin on mbed to connect PWM device to
     */
    ACMotor(
        PinName Pu_high, PinName Pu_low,
        PinName Pv_high, PinName Pv_low,
        PinName Pw_high, PinName Pw_low,
        PinName Phole1, PinName Phole2, PinName Phole3);

		void setMaxDutyRatio(float max_ratio);

    void period(double seconds);


void write(double value);

    float read();
    
#ifdef MBED_OPERATORS
    /** A operator shorthand for write()
     */
    ACMotor& operator= (float value) {
        write(value);
        return *this;
    }

    ACMotor& operator= (ACMotor& rhs) {
        write(rhs.read());
        return *this;
    }

    /** An operator shorthand for read()
     */
    operator float() {
        return read();
    }
#endif

private:
		PwmOut uh_;
		PwmOut vh_;
		PwmOut wh_;
		DigitalOut ul_;
		DigitalOut vl_;
		DigitalOut wl_;
    InterruptIn hole1_;
    InterruptIn hole2_;
    InterruptIn hole3_;

    double value;
    double period_sec;
		double max_ratio;
    bool enable;

    static int switching_table[6][3];
    void status_changed(void);
    void drive(int u, int v, int w);
};

#endif
