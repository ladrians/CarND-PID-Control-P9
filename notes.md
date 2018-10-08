# P9: PID Controller

The project includes the following files

* CMakeLists.txt
* src folder
* notes.txt (this file)
* video01.mp4

## Description

The project was addressed the following way:

* Review the [QA session](https://youtu.be/YamBuzDjrs8).
* Review the [Forum](https://discussions.udacity.com/c/nd013-controllers/project-pid-controller) messages.
* Slack #s-t2-p-pid channel was discarded.

## Considerations

The QA session was useful to get started and I followed the sample to tune the PID from command line and then added a 4th parameter to set the desired throttle.

The most useful information was from the forum [here](https://discussions.udacity.com/t/how-to-tune-parameters/303845) and references to the Ziegler-Nichols’ closed loop method.

Then it was suggested to use another PID for the throttle [here](https://discussions.udacity.com/t/how-to-tune-parameters/303845); I used a PD, it was good enough.

As suggested I started with the Kp (steering response) parameter, then Kd (reduce the oscillations) and finally Ki (converge on the long term).

Values selected are

Kp=0.1 Ki=0.0002 Kd=3.

I reviewed the Twiddle algorithm and ported the Python sample [here](https://martin-thoma.com/twiddle/) to C++ but could not integrate the code to the pipeline.

video01 details a sample.

## Test

Follow these steps for validation:

1. Compile the project as detailed `cmake .. && make`.
2. Run `./pid 0.1 0.0002 3. 55`, parameters are Proportional, Integral, Derivative, Throttle.
3. Run the simulator and Start

Notice that 55 is the higher throttle value I could find. Higher values will go wrong somewhere on the track.