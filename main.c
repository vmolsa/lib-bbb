#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

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
" Examples:                                                         \n"
" sudo ./bbb --enable-adc                                           \n"
" sudo ./bbb --get-adc 2                                            \n"
" sudo ./bbb --enable-i2c-device 1 --address 0x53 --module adxl34x  \n"
" sudo ./bbb --i2c-scan 1                                           \n"
" sudo ./bbb --disable-i2c-device 1 --address 0x53                  \n"
" sudo ./bbb --show-by-type-only pwm                                \n"
" sudo ./bbb --enable-gpio 60                                       \n"
" sudo ./bbb --gpio 60 --set-direction 1                            \n"
" sudo ./bbb --gpio 60 --get-direction                              \n"
" sudo ./bbb --gpio 60 --set-value 1                                \n"
" sudo ./bbb --gpio 60 --get-value                                  \n"
" sudo ./bbb --disable-gpio 60                                      \n"
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
	
	int option_index = 0;

	if (argc == 1) {
		LOG("%s\n", help);
		return 0;
	}

	while ((c = getopt_long (argc, argv, "", long_options, &option_index)) != -1) {
		switch (c) {
			case 'a':
				showAll();
				break;
			case 'A':
				enableadc = 1;
				break;
			case 'U':
				LOG("%d\n", getADC(atoi(optarg)));
				break;
			case 'p':
				showPin(optarg);
				break;
			case 'b':
				showByType(str2pinType(optarg));
				break;
			case 'o':
				showByTypeOnly(str2pinType(optarg));
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
				enableGpio(atoi(optarg));
				break;
			case 'G':
				enableGpio(getGpio(getIndexByStr(optarg)));
				break;
			case 'j':
				disableGpio(atoi(optarg));
				break;
			case 'J':
				disableGpio(getGpio(getIndexByStr(optarg)));
				break;
			case 'q':
				gpio = atoi(optarg);
				break;
			case 'Q':
				gpio = getGpio(getIndexByStr(optarg));
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
			case 'h':
			default:
				LOG("%s\n", help);
				break;
		}
	}

	if (enablei2c >= 0) {
		if (address > 0 && module != NULL) {
			enableI2Cdevice(enablei2c, address, module);
		}

		else {
			LOG("%s\n", help);
		}

		return 0;
	}

	if (disablei2c >= 0) {
		if (address > 0) {
			disableI2Cdevice(disablei2c, address);
		}

		else {
			LOG("%s\n", help);
			return -1;
		}
	}

	if (enableadc >= 0) {
		enableADC();
	}

	if (direction >= 0) {
		if (gpio > 0) {
			setGpioDirection(gpio, direction);
		} else {
			LOG("%s\n", help);
			return -1;
		}
	}

	if (getdirection >= 0) {
		if (gpio > 0) {
			LOG("%d\n", getGpioDirection(gpio));
		} else {
			LOG("%s\n", help);
			return -1;
		}
	}

	if (setgpiovalue >= 0) {
		if (gpio > 0) {
			setGpioValue(gpio, setgpiovalue);
		} else {
			LOG("%s\n", help);
			return -1;
		}
	}

	if (getgpiovalue >= 0) {
		if (gpio > 0) {
			LOG("%d\n", getGpioValue(gpio)); 
		} else {
			LOG("%s\n", help);
			return -1;
		}
	}

	return 0;
}
