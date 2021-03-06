
#include "../bcm2835_emul.h"
#include "../vcregs.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

void print_log (const char *fmt, ...);

void
gpio_init (struct bcm2835_emul *emul) {
  memset (&emul->gpio, 0, sizeof (emul->gpio));
}

uint32_t
gpio_load (struct bcm2835_emul *emul, uint32_t address) {
  if (address >= VC_GPIO_FSEL0 && address <= VC_GPIO_FSEL6) {
    return emul->gpio.fsel[(address - VC_GPIO_FSEL0) >> 2];
  } else if (address == VC_GPIO_PUD) {
    return emul->gpio.pud;
  }
  print_log("GPIO Address load: 0x%08x\n, address", address);
  return 0;
}

void
gpio_store (struct bcm2835_emul *emul, uint32_t address, uint32_t value) {
  int i;

  if (address >= VC_GPIO_FSEL0 && address <= VC_GPIO_FSEL6) {
    int reg_index = (address - VC_GPIO_FSEL0) >> 2;
    uint32_t old_value = emul->gpio.fsel[reg_index];

    emul->gpio.fsel[reg_index] = value;
    for (i = 0; i < 10; i++) {
      if ((value & 0x7) != (old_value & 0x7)) {
        print_log ("GPIO %d fsel %d\n", i + reg_index * 10, value & 0x7);
      }
      value >>= 3;
      old_value >>= 3;
    }
    return;
  } else if (address >= VC_GPIO_CLR0 && address <= VC_GPIO_CLR2) {
    int reg_index = (address - VC_GPIO_CLR0) >> 2;
    uint32_t old_value = emul->gpio.output_level[reg_index];

    emul->gpio.output_level[reg_index] &= ~value;
    for (i = 0; i < 32; i++) {
      if ((value & 0x1) == 1 && (old_value & 0x1) == 1) {
        print_log ("GPIO %d clear\n", i + reg_index * 32);
      }
      value >>= 1;
      old_value >>= 1;
    }
  } else if (address >= VC_GPIO_SET0 && address <= VC_GPIO_SET2) {
    int reg_index = (address - VC_GPIO_SET0) >> 2;
    uint32_t old_value = emul->gpio.output_level[reg_index];

    emul->gpio.output_level[reg_index] |= value;
    for (i = 0; i < 32; i++) {
      if ((value & 0x1) == 1 && (old_value & 0x1) == 0) {
        print_log ("GPIO %d set\n", i + reg_index * 32);
      }
      value >>= 1;
      old_value >>= 1;
    }
  } else if (address >= VC_GPIO_LEV0 && address <= VC_GPIO_LEV2) {
    /*
     * TODO 
     */
    print_log ("[%s:%u:%s] Address %x value %x\n", __FILE__, __LINE__,
               __FUNCTION__, address, value);
    assert (0 && "GPIO_LEVx not implemented!\n");
  } else if (address == VC_GPIO_PUD && address <= VC_GPIO_PUDCLK2) {
    if (address == VC_GPIO_PUD) {
      emul->gpio.pud = value;
    } else if (address == VC_GPIO_PUDCLK0) {
      emul->gpio.pudclk[0] = value;
    } else if (address == VC_GPIO_PUDCLK1) {
      emul->gpio.pudclk[1] = value;
    } else if (address == VC_GPIO_PUDCLK2) {
      emul->gpio.pudclk[2] = value;
    } else {
    /*
     * TODO 
     */
      print_log ("[%s:%u:%s] Address %x value %x\n", __FILE__, __LINE__,
                 __FUNCTION__, address, value);
    }
    //assert (0 && "GPIO_PUD & GPIO_PUD_CLKx not implemented!\n");
  } else {
    /*
     * TODO 
     */
    print_log ("[%s:%u:%s] Address %x value %x\n", __FILE__, __LINE__,
               __FUNCTION__, address, value);
  }
}
