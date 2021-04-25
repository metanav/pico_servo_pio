#include "hardware/clocks.h"
#include "hardware/pio.h"
#include "pico/stdlib.h"
#include "pico_servo.pio.h"

#define MIN_DC 650
#define MAX_DC 2250
const uint SERVO_PIN = 16;

// Write `period` to the input shift register
void pio_pwm_set_period(PIO pio, uint sm, uint32_t period) {
    pio_sm_set_enabled(pio, sm, false);
    pio_sm_put_blocking(pio, sm, period);
    pio_sm_exec(pio, sm, pio_encode_pull(false, false));
    pio_sm_exec(pio, sm, pio_encode_out(pio_isr, 32));
    pio_sm_set_enabled(pio, sm, true);
}

// Write `level` to TX FIFO. State machine will copy this into X.
void pio_pwm_set_level(PIO pio, uint sm, uint32_t level) {
    pio_sm_put_blocking(pio, sm, level);
}

int main() {
    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &pico_servo_pio_program);

    float freq = 50.0f; // servo except 50Hz
    uint clk_div = 64;  // make the clock slower

    pico_servo_pio_program_init(pio, sm, offset, clk_div, SERVO_PIN);

    uint cycles = clock_get_hz(clk_sys) / (freq * clk_div);
    uint32_t period = (cycles -3) / 3;  
    pio_pwm_set_period(pio, sm, period);

    uint level;
    int ms = (MAX_DC - MIN_DC) / 2;
    bool clockwise = false;

  while (true) {
    level = (ms / 20000.f) * period;
    pio_pwm_set_level(pio, sm, level);

    if (ms <= MIN_DC || ms >= MAX_DC) {
        clockwise = !clockwise;
    }

    if (clockwise) {
        ms -= 100;
    } else {
        ms += 100;
    }

    sleep_ms(500);
  }
}
