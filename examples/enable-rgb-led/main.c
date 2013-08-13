#include <stdio.h>
#include <bbb.h>

//sudo bbb --enable-gpio-pin P8_27 --gpio-pin P8_27 --set-direction 1 --set-value 1 # LED 1 RED
//sudo bbb --enable-gpio-pin P8_28 --gpio-pin P8_28 --set-direction 1 --set-value 1 # LED 1 GREEN
//sudo bbb --enable-gpio-pin P8_29 --gpio-pin P8_29 --set-direction 1 --set-value 1 # LED 1 BLUE

int main() {
	int pin_27 = getIndexByStr("P8_27");
	int pin_28 = getIndexByStr("P8_28");
	int pin_29 = getIndexByStr("P8_29");

	int gpio_27 = getGpio(pin_27);
	int gpio_28 = getGpio(pin_28);
	int gpio_29 = getGpio(pin_29);

	if (enableGpio(gpio_27) < 0) {
		LOG("Unable to enable gpio(%d)\n", gpio_27);
	}

	if (enableGpio(gpio_28) < 0) {
		LOG("Unable to enable gpio(%d)\n", gpio_28);
	}

	if (enableGpio(gpio_29) < 0) {
		LOG("Unable to enable gpio(%d)\n", gpio_29);
	}

	if (setGpioDirection(gpio_27, 1) < 0) {
		LOG("Unable to set gpio(%d) direction(out)\n", gpio_27);
	}

	if (setGpioDirection(gpio_28, 1) < 0) {
		LOG("Unable to set gpio(%d) direction(out)\n", gpio_28);
	}

        if (setGpioDirection(gpio_29, 1) < 0) {
		LOG("Unable to set gpio(%d) direction(out)\n", gpio_29);
	}

	if (setGpioValue(gpio_27, 1) < 0) {
		LOG("Unable to set gpio(%d) value(HIGH)\n", gpio_27);
	}

	if (setGpioValue(gpio_28, 1) < 0) {
		LOG("Unable to set gpio(%d) value(HIGH)\n", gpio_28);
	}

	if (setGpioValue(gpio_29, 1) < 0) {
		LOG("Unable to set gpio(%d) value(HIGH)\n", gpio_29);
	}

	return 0;
}
