
#include "../bcm2835_emul.h"
#include "../vcregs.h"

#include <assert.h>
#include <string.h>

extern void print_log (const char *fmt, ...);

void
pwm0_init (struct bcm2835_emul *emul) {
  memset (&emul->pwm0, 0, sizeof (emul->pwm0));
}

uint32_t
pwm0_load (struct bcm2835_emul *emul, uint32_t address) {
  print_log("PWM0 Address load: 0x%08x\n", address);
  return 0;
  (void) emul;
}

void
pwm0_store (struct bcm2835_emul *emul, uint32_t address, uint32_t value) {
  print_log("PWM0 Address store: 0x%08x 0x%08x\n", address, value);
  (void) emul;
}
