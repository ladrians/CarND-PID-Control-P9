#include "PID.h"
#include <iostream>

using namespace std;

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
	this->Kp = Kp;
	this->Ki = Ki;
	this->Kd = Kd;

	p_error = 0;
	i_error = 0;
	d_error = 0;
}

void PID::UpdateError(double cte) {
	d_error = cte - p_error; // how much we change since the last time
	p_error = cte;
	i_error += cte; // cummulative
}

double PID::TotalError() {
	return Kp * p_error + Ki * i_error + Kd * d_error;
}

double PID::Value() {
	double value = -Kp * p_error - Ki * i_error - Kd * d_error;
    value = max(min(value, 1.0),-1.0);
	return value;
}

void PID::Twiddle()
{
	// algorithm structure taken from https://martin-thoma.com/twiddle/
	int steps = 200;
	int current_step = 0;
	float err = 1000.0;
	float best_error = 1e10;

	if (current_step <= steps)
	{
		double p[3] = {0, 0, 0};
		double dp[3] = {1, 1, 1};

		for (int i = 0; i < 3; ++i)
		{
			p[i] += dp[i];
			err = TotalError();
			if (err < best_error)
			{
				best_error = err;
				dp[i] *= 1.1; 
			}
			else // No improvement
			{
				p[i] -= 2 * dp[i]; // Go into the other direction
				err = TotalError();
				if (err < best_error) // Improvement
				{
					best_error = err;
					dp[i] *= 1.05;
				}
				else // No improvement
				{
					p[i] += dp[i];
					dp[i] *= 0.95;
				}
			}
		}
		this->Kp = p[0];
		this->Ki = p[1];
		this->Kd = p[2];
		current_step += 1;
	}
}
