# Drive servo with Raspberry Pi Pico using PIO 

The program was tested with a micro Servo 9g A0090. It should work with similar servos. Change the values in the main.c to match with your servo.

```
#define MIN_DC 650
#define MAX_DC 2250
```

## Build the program

```
$ export PICO_SDK_PATH=/path/to/pico/pico-sdk
$ git clone https://github.com/metanav/pico_servo_pio.git
$ cd pico_servo_pio
$ mkdir build && cd build
$ cmake ..
$ make
```
