#include "common_inc.h"

using Led_R = gpio::C0;
using Led_G = gpio::C1;
using Led_B = gpio::C2;
using Key   = gpio::C13;

void Main()
{
    delay::init();
    while (true) {
        if (!Key::read()) {
            delay::ms(20);
            while (!Key::read()) {
            }
            Led_R::toggle();
            Led_G::toggle();
            Led_B::toggle();
            delay::ms(20);
        }
    }
}
