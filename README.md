# Drive servo with Raspberry Pi Pico using PIO 

The program was tested with a micro Servo 9g A0090. It should work with similar servos.  All the standard servos should response with the values between 1000ms and 2000ms. In my case I was able to achieve min and max angles using the configuration below, please change itby experimenting with yours.

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
