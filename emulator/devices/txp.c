
#include "../bcm2835_emul.h"
#include "../vcregs.h"

#include <assert.h>
#include <string.h>

extern void print_log (const char *fmt, ...);

void
txp_init (struct bcm2835_emul *emul) {
  memset (&emul->txp, 0, sizeof (emul->txp));
}

uint32_t
txp_load (struct bcm2835_emul *emul, uint32_t address) {
  print_log ("TXP Address load: %08x\n", address);
  return 0;
  (void) emul;
}

void
txp_store (struct bcm2835_emul *emul, uint32_t address, uint32_t value) {
  print_log ("TXP Address store: 0x%08x 0x%08x\n", address, value);
  (void) emul;
}
