#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <sys/wait.h>

#include "bbb.h"

int i2c_bus_detect(char *index) {
	pid_t pid;
	int status;
	int pipefd[2] = { -1, -1 };
	char *envp[] = { NULL };
	char *argv[] = { "i2cdetect", "-y", "-r", index, NULL };

	switch ((pid = fork())) {
		case -1:
			return -1;
		case 0:
			status = execvp(argv[0], argv);
			exit(status);
		default:
			if (waitpid(pid, &status, 0) < 0) {
				return -1;
			}

			if (WIFEXITED(status)) {
				return WEXITSTATUS(status);
			}

			break;
	}

	return -1;
}

static struct option long_options[] = {
	{ "show-all", 		no_argument, 0, 'a' },
	{ "show-pin",		required_argument, 0, 'p' },
	{ "show-by-type", 	required_argument, 0, 'b' },
	{ "show-by-type-only", 	required_argument, 0, 'o' },
	{ "show-types",		no_argument, 0, 't' },
	{ "help", 		no_argument, 0, 'h' },
	{ "enable-adc",		no_argument, 0, 'A' },
	{ "get-adc",		required_argument, 0, 'U' },
	{ "i2c-scan",		required_argument, 0, 'S' },
	{ "enable-i2c-device", 	required_argument, 0, 'i' },
	{ "disable-i2c-device", required_argument, 0, 'I' },
	{ "address",		required_argument, 0, 'd' },
	{ "module",		required_argument, 0, 'm' },
	{ "enable-gpio",	required_argument, 0, 'g' },
	{ "enable-gpio-pin",	required_argument, 0, 'G' },
	{ "disable-gpio",	required_argument, 0, 'j' },
	{ "disable-gpio-pin",	required_argument, 0, 'J' },
	{ "gpio",		required_argument, 0, 'q' },
	{ "gpio-pin",		required_argument, 0, 'Q' },
	{ "set-direction",	required_argument, 0, 'c' },
	{ "get-direction",	no_argument, 0, 'C' },
	{ "set-value",		required_argument, 0, 'v' },
	{ "get-value",		no_argument, 0, 'V' },
	{ "enable-pwm", 	required_argument, 0, '1' },
	{ "pwm", 		required_argument, 0, '2' },
	{ "set-period",		required_argument, 0, '9' },
	{ "set-period-hz", 	required_argument, 0, '3' },
	{ "set-duty", 		required_argument, 0, '4' },
	{ "set-polarity", 	required_argument, 0, '7' },
	{ "get-period", 	no_argument, 0, '5' },
	{ "get-duty", 		no_argument, 0, '6' },
	{ "get-polarity", 	no_argument, 0, '8' },
	{ "enable-serial", 	required_argument, 0, 'K' },
	{ 0, 0, 0, 0 }
};

static int long_options_count = sizeof(long_options) / sizeof(struct option);
static char *help =
"                                                                   \n"
"   BeagleBone Black                                                \n"
"   ----------------                                                \n"
"                                                                   \n"
"   --show-all                                                      \n"
"   --show-pin <P[HEADER]_[NUM]>                                    \n"
"   --show-by-type <type>                                           \n"
"   --show-by-type-only <type>                                      \n"
"   --show-types                                                    \n"
"                                                                   \n"
"   --enable-adc                                                    \n"
"   --get-adc <id>                                                  \n"
"                                                                   \n"
"   --i2c-scan <bus>                                                \n"
"   --enable-i2c-device <bus>                                       \n"
"      --address <address>                                          \n"
"      --module <module>                                            \n"
"                                                                   \n"
"   --disable-i2c-device <bus>                                      \n"
"      --address <address>                                          \n"
"                                                                   \n"
"   --enable-gpio <gpio>                                            \n"
"   --enable-gpio-pin <P[HEADER]_[NUM]>                             \n"
"   --disable-gpio <gpio>                                           \n"
"   --disable-gpio-pin <P[HEADER]_[NUM]>                            \n"
"                                                                   \n"
"   --gpio <gpio>                                                   \n"
"   --gpio-pin <P[HEADER]_[NUM]>                                    \n"
"      --set-direction <0 | 1>                                      \n"
"      --get-direction                                              \n"
"      --set-value <0 | 1>                                          \n"
"      --get-value                                                  \n"
"                                                                   \n"
"   --enable-pwm <P[HEADER]_[NUM]>                                  \n"
"   --pwm <P[HEADER]_[NUM]>                                         \n"
"      --set-period <time>                                          \n"
"      --set-period-hz <x[Hz][kHz][MHz]>                            \n"
"      --set-duty <[0-100]>                                         \n"
"      --set-polarity <0 | 1>                                       \n"
"      --get-period                                                 \n"
"      --get-duty                                                   \n"
"      --get-polarity                                               \n"
"                                                                   \n"
"   --enable-serial <[0-5]>                                         \n"
"                                                                   \n"
" Examples:                                                         \n"
"                                                                   \n"
" sudo bbb --enable-adc                                             \n"
" sudo bbb --get-adc 2                                              \n"
"                                                                   \n"
" sudo bbb --enable-i2c-device 1 --address 0x53 --module adxl34x    \n"
" sudo bbb --i2c-scan 1                                             \n"
" sudo bbb --disable-i2c-device 1 --address 0x53                    \n"
"                                                                   \n"
"      bbb --show-all                                               \n"
"      bbb --show-pin P8_13                                         \n"
"      bbb --show-by-type-only pwm                                  \n"
"                                                                   \n"
" sudo bbb --enable-gpio 60                                         \n"
" sudo bbb --gpio 60 --set-direction 1                              \n"
" sudo bbb --gpio 60 --get-direction                                \n"
" sudo bbb --gpio 60 --set-value 1                                  \n"
" sudo bbb --gpio 60 --get-value                                    \n"
" sudo bbb --disable-gpio 60                                        \n"
"                                                                   \n"
" sudo bbb --enable-pwm P8_13                                       \n"
" sudo bbb --pwm P8_13 --set-period 1000000000                      \n"
" sudo bbb --pwm P8_13 --set-period-hz 50Hz                         \n"
" sudo bbb --pwm P8_13 --set-duty 100                               \n"
" sudo bbb --pwm P8_13 --get-period --get-duty                      \n"
" sudo bbb --pwm P8_13 --set-polarity 0                             \n"
"\n";

int main(int argc, char **argv) {
	int c = 0, i = 0;

	int enableadc = -1;
	int enablei2c = -1;
	int disablei2c = -1;
	int gpio = -1;
	int direction = -1;
	int getdirection = -1;
	int setgpiovalue = -1;
	int getgpiovalue = -1;
	unsigned char address = 0;
	char *module = NULL;
	int pwm_header = -1;
	int pwm_pin = -1;
	int setpwmperiod = -1;
	char *setpwmperiodhz = NULL;
	int setpwmduty = -1;
	int getpwmperiod = -1;
	int getpwmduty = -1;
	int setpwmpolarity = -1;
	int getpwmpolarity = -1;

	int option_index = 0;

	if (argc == 1) {
		LOG("%s\n", help);
		return 0;
	}

	while ((c = getopt_long (argc, argv, "", long_options, &option_index)) != -1) {
		switch (c) {
			case 'a':
				bbb_showAll();
				break;
			case 'A':
				enableadc = 1;
				break;
			case 'U':
				LOG("%d\n", bbb_getADC(atoi(optarg)));
				break;
			case 'p':
				bbb_showPin(optarg);
				break;
			case 'b':
				bbb_showByType(bbb_str2pinType(optarg));
				break;
			case 'o':
				bbb_showByTypeOnly(bbb_str2pinType(optarg));
				break;
			case 'S':
				return i2c_bus_detect(optarg);
			case 't':
				for (i = 0; i < bbb_pin_type_str_size; i++) {
					LOG("   %s\n", bbb_pin_type_str[i]);
				}
				break;
			case 'i':
				enablei2c = atoi(optarg);
				break;
			case 'I':
				disablei2c = atoi(optarg);
				break;
			case 'd':
				address = (unsigned char) strtol(optarg, NULL, 0);
				break;
			case 'm':
				module = optarg;
				break;
			case 'g':
				bbb_enableGpio(atoi(optarg));
				break;
			case 'G':
				bbb_enableGpio(bbb_getGpio(bbb_getIndexByStr(optarg)));
				break;
			case 'j':
				bbb_disableGpio(atoi(optarg));
				break;
			case 'J':
				bbb_disableGpio(bbb_getGpio(bbb_getIndexByStr(optarg)));
				break;
			case 'q':
				gpio = atoi(optarg);
				break;
			case 'Q':
				gpio = bbb_getGpio(bbb_getIndexByStr(optarg));
				break;
			case 'c':
				direction = atoi(optarg);
				break;
			case 'C':
				getdirection = 1;
				break;
			case 'v':
				setgpiovalue = atoi(optarg);
				break;
			case 'V':
				getgpiovalue = 1;
				break;
			case '1':
				bbb_enablePwm(bbb_getHeader(bbb_getIndexByStr(optarg)), bbb_getPin(bbb_getIndexByStr(optarg)));
				break;
			case '2':
				pwm_header = bbb_getHeader(bbb_getIndexByStr(optarg));
				pwm_pin = bbb_getPin(bbb_getIndexByStr(optarg));
				break;
			case '3':
				setpwmperiodhz = optarg;
				break;
			case '4':
				setpwmduty = atoi(optarg);
				break;
			case '5':
				getpwmperiod = 1;
				break;
			case '6':
				getpwmduty = 1;
				break;
			case '7':
				setpwmpolarity = atoi(optarg);
				break;
			case '8':
				getpwmpolarity = 1;
				break;
			case '9':
				setpwmperiod = atoi(optarg);
				break;
			case 'K':
				bbb_enableSerial(atoi(optarg));
				break;
			case 'h':
			default:
				LOG("%s\n", help);
				break;
		}
	}

	if (enablei2c >= 0) {
		if (address > 0 && module != NULL) {
			bbb_enableI2Cdevice(enablei2c, address, module);
		}

		else {
			LOG("%s\n", help);
		}

		return 0;
	}

	if (disablei2c >= 0) {
		if (address > 0) {
			bbb_disableI2Cdevice(disablei2c, address);
		}

		else {
			LOG("%s\n", help);
			return -1;
		}
	}

	if (enableadc >= 0) {
		bbb_enableADC();
	}

	if (direction >= 0) {
		if (gpio > 0) {
			bbb_setGpioDirection(gpio, direction);
		} else {
			LOG("%s\n", help);
			return -1;
		}
	}

	if (getdirection >= 0) {
		if (gpio > 0) {
			LOG("%d\n", bbb_getGpioDirection(gpio));
		} else {
			LOG("%s\n", help);
			return -1;
		}
	}

	if (setgpiovalue >= 0) {
		if (gpio > 0) {
			bbb_setGpioValue(gpio, setgpiovalue);
		} else {
			LOG("%s\n", help);
			return -1;
		}
	}

	if (getgpiovalue >= 0) {
		if (gpio > 0) {
			LOG("%d\n", bbb_getGpioValue(gpio));
		} else {
			LOG("%s\n", help);
			return -1;
		}
	}

	if (setpwmperiod >= 0) {
		if (pwm_header > 0 && pwm_pin > 0) {
			bbb_setPwmPeriod(pwm_header, pwm_pin, setpwmperiod);
		} else {
			LOG("%s\n", help);
			return -1;
		}
	}

	if (setpwmperiodhz != NULL) {
		if (pwm_header > 0 && pwm_pin > 0) {
			bbb_setPwmHz(pwm_header, pwm_pin, setpwmperiodhz);
		} else {
			LOG("%s\n", help);
			return -1;
		}
	}

	if (setpwmduty >= 0) {
		if (pwm_header > 0 && pwm_pin > 0) {
			bbb_setPwmPercent(pwm_header, pwm_pin, setpwmduty);
		} else {
			LOG("%s\n", help);
			return -1;
		}
	}

	if (setpwmpolarity >= 0) {
		if (pwm_header > 0 && pwm_pin > 0) {
			bbb_setPwmPolarity(pwm_header, pwm_pin, setpwmpolarity);
		} else {
			LOG("%s\n", help);
			return -1;
		}
	}

	if (getpwmperiod >= 0) {
		if (pwm_header > 0 && pwm_pin > 0) {
			LOG("%s\n", bbb_getPwmHz(pwm_header, pwm_pin));
		} else {
			LOG("%s\n", help);
			return -1;
		}
	}

	if (getpwmduty >= 0) {
		if (pwm_header > 0 && pwm_pin > 0) {
			LOG("%d%%\n", bbb_getPwmPercent(pwm_header, pwm_pin));
		} else {
			LOG("%s\n", help);
			return -1;
		}
	}

	if (getpwmpolarity >= 0) {
		if (pwm_header > 0 && pwm_pin > 0) {
			LOG("%d\n", bbb_getPwmPolarity(pwm_header, pwm_pin));
		} else {
			LOG("%s\n", help);
			return -1;
		}
	}

	return 0;
}
