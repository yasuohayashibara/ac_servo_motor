#include "ACMotor.h"
#include "mbed.h"

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

#define HOLE_STATE1 	0x04	// 100  ( 0deg - 60deg)
#define HOLE_STATE2 	0x06	// 110  ( 60deg - 120deg)
#define HOLE_STATE3 	0x02	// 010  ( 120deg - 180deg)
#define HOLE_STATE4 	0x03	// 011  ( 180deg - 240deg)
#define HOLE_STATE5 	0x01	// 001  ( 240deg - 300deg)
#define HOLE_STATE6 	0x05	// 101  ( 300deg - 360deg)

int ACMotor::switching_table[6] [3] = {
		{ 0, -1, 1 },
		{ 1, -1, 0 },
		{ 1, 0, -1 },
		{ 0, 1, -1 },
		{ -1, 1, 0 },
		{ -1, 0, 1 },
};

/*
// !!! check and change !!!
int ACMotor::switching_table[2][7] = {
	{
		0x15,	//LLL 010101 (stop)
		0x09,	//-HL 001001 (hole: 001)
		0x18,	//LH- 011000 (hole: 011)
		0x12,	//L-H 010010 (hole: 010)
		0x06,	//-LH 000110 (hole: 110)
		0x24,	//HL- 100100 (hole: 100)
		0x21,	//H-L 100001 (hole: 101)
	},{
		0x15,	//LLL 010101 (stop)
		0x18,	//LH-011000 (hole: 001)
		0x12,	//L-H 010010 (hole: 011)
		0x06,	//-LH 000110 (hole: 010)
		0x24,	//HL- 100100 (hole: 110)
		0x21,	//H-L 100001 (hole: 100)
		0x21,	//-HL 001001 (hole: 101)
	}
};
*/

// L-H         -LH              HL-

ACMotor::ACMotor(
		PinName Pu_high, PinName Pu_low,
		PinName Pv_high, PinName Pv_low,
		PinName Pw_high, PinName Pw_low,
		PinName Phole1, PinName Phole2, PinName Phole3)
		: uh_(Pu_high), vh_(Pv_high), wh_(Pw_high), ul_(Pu_low), vl_(Pv_low), wl_(Pw_low),
			hole1_(Phole1), hole2_(Phole2), hole3_(Phole3)
    
{
//	hole1_.rise(ACMotor::status_changed);
	hole1_.fall(this, &ACMotor::status_changed);
	hole1_.rise(this, &ACMotor::status_changed);
	hole2_.fall(this, &ACMotor::status_changed);
	hole2_.rise(this, &ACMotor::status_changed);
	hole3_.fall(this, &ACMotor::status_changed);
	hole3_.rise(this, &ACMotor::status_changed);
	uh_.period(0.00005);		// 20kHz
	this->write(0);
}

void ACMotor::setMaxDutyRatio(float max_ratio)
{
	max_ratio = max(min(max_ratio, 1.0), 0.0);
	this->max_ratio = max_ratio;
}

void ACMotor::period(double seconds)
{
	period_sec = seconds;
	this->period(seconds);
}

void ACMotor::write(double value)
{
	value = max(min(value, 1.0), -1.0);
	this->value = value;
}

float ACMotor::read()
{
  return value;
}

void ACMotor::status_changed(void)
{
	int hole1 = hole1_.read();
	int hole2 = hole2_.read();
	int hole3 = hole3_.read();
	
	int hole_state = (hole1 << 2) + (hole2 << 1) + hole3;
	int state = 0;
	int dir = (value >= 0.0) ? 1 : -1;
	switch(hole_state){
		case HOLE_STATE1:
			state = 0; break;
		case HOLE_STATE2:
			state = 1; break;
		case HOLE_STATE3:
			state = 2; break;
		case HOLE_STATE4:
			state = 3; break;
		case HOLE_STATE5:
			state = 4; break;
		case HOLE_STATE6:
			state = 5; break;
	}
	int next_state = (state + dir) % 6;
	if (enable){
		drive(switching_table[next_state][0],
						switching_table[next_state][1],
						switching_table[next_state][2]);
	} else {
		drive(-1, -1, -1);
	}
}

/*!
 * @brief drive for three phase motor
* @param[in] u switch u line (1:High, 0: NC, -1: Low)
* @param[in] v switch v line (1:High, 0: NC, -1: Low)
* @param[in] w switch w line (1:High, 0: NC, -1: Low)
 */
void ACMotor::drive(int u, int v, int w)
{
	float val = value * max_ratio;
	
	uh_ = (u == 1) ? val : 0;
	ul_ = (u == -1) ? 1 : 0;
	vh_ = (v == 1) ? val : 0;
	vl_ = (v == -1) ? 1 : 0;
	wh_ = (w == 1) ? val : 0;
	wl_ = (w == -1) ? 1 : 0;
}
