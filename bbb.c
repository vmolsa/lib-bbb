/* Copyright (c) 2013, ville mölsä
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 *   Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * 
 *   Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.

 *   Neither the name of the {organization} nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include "bbb.h"

//	Get Index

int getIndexByStr(char *str) {
	int size = strlen(str);
	int header = 0; 
	int pin = 0;
	
	if (str[0] == 'P' && size >= 4) {
		if (str[1] == '8') {
			header = 8;
		} else {
			if (str[1] == '9') {
				header = 9;
			} else {
				return -1;
			}
		}
	} else {
		return -1;
	}

	if (str[2] == '_') {
		pin = atoi((str + 3));
	} else {
		return -1;
	}

	return getIndexByPin(header, pin);
}

int getIndexByPin(int header, int pin) {
	int i;

	for (i = 0; i < bbb_table_size; i++) {
		if (pinout_table[i].header == header && pinout_table[i].pin == pin) {
			return i;
		}
	}

	return -1;
}

int getIndexByGpio(int gpio) {
	int i;

	for (i = 0; i < bbb_table_size; i++) {
		if (pinout_table[i].gpio == gpio) {
			return i;
		}
	}

	return -1;
}

int getIndexBySignalName(char *signalname) {
	int i;

	for (i = 0; i < bbb_table_size; i++) {
		if (strcmp(pinout_table[i].sig, signalname) == 0) {
			return i;
		}
	}

	return -1;
}

int getIndexByName(char *name) {
	int i;

	for (i = 0; i < bbb_table_size; i++) {
		if (strcmp(pinout_table[i].name, name) == 0) {
			return i;
		}
	}

	return -1;
}

//	Index to values

int getPin(int index) {
	if (index >= 0 && index <= bbb_table_size) {
		return pinout_table[index].pin;
	}
	
	return -1;
}

int getGpio(int index) {
	if (index >= 0 && index <= bbb_table_size) {
		return pinout_table[index].gpio;
	}
	
	return 0;
}

bbb_pin_type getType1(int index) {
	if (index >= 0 && index <= bbb_table_size) {
		return pinout_table[index].type1;
	}
	
	return 0;
}

bbb_pin_type getType2(int index) {
	if (index >= 0 && index <= bbb_table_size) {
		return pinout_table[index].type2;
	}
	
	return 0;
}

bbb_pin_type getType3(int index) {
	if (index >= 0 && index <= bbb_table_size) {
		return pinout_table[index].type3;
	}
	
	return 0;
}

char *getSignalName(int index) {
	if (index >= 0 && index <= bbb_table_size) {
		return pinout_table[index].name;
	}

	return "undefined";
}

char *getName(int index) {
	if (index >= 0 && index <= bbb_table_size) {
		return pinout_table[index].name;
	}

	return "undefined";
}

// 	Index to String Values

char *getPinStrByIndex(int index) {
	static char pinstr[10];

	if (index >= 0 && index <= bbb_table_size) {
		memset(pinstr, 0, sizeof(pinstr));
		snprintf(pinstr, sizeof(pinstr), "P%d_%d", pinout_table[index].header, pinout_table[index].pin); 

		return pinstr;
	}

	return "undefined";
}

char *getGpioStrByIndex(int index) {
	static char gpiostr[10];

	if (index >= 0 && index <= bbb_table_size) {
		memset(gpiostr, 0, sizeof(gpiostr));
		snprintf(gpiostr, sizeof(gpiostr), "%d", pinout_table[index].gpio); 

		return gpiostr;
	}

	return "undefined";
}

char *getTypeStrByIndex(int index) {
	static char typestr[56];

	if (index >= 0 && index <= bbb_table_size) {
		memset(typestr, 0, sizeof(typestr));
		snprintf(typestr, sizeof(typestr), "%s %s %s", pinType2str(pinout_table[index].type1), pinType2str(pinout_table[index].type2), pinType2str(pinout_table[index].type3)); 

		return typestr;
	}

	return "undefined";
}

char *getSignalNameByIndex(int index) {
	if (index >= 0 && index <= bbb_table_size) {
		return pinout_table[index].sig;
	}

	return "undefined";
}

char *getNameByIndex(int index) {
	if (index >= 0 && index <= bbb_table_size) {
		return pinout_table[index].name;
	}

	return "undefined";
}

//	Types

char *pinType2str(bbb_pin_type type) {
	char *ret = "undefined";

	if (type >= BBB_NONE && type <= BBB_SPI) {
		ret = bbb_pin_type_str[type];
	}

	return ret;
}

bbb_pin_type str2pinType(char *str) {
	int i = 0;
	bbb_pin_type ret = BBB_NONE;

	for (i = 0; i < bbb_pin_type_str_size; i++) {
		if (strcmp(bbb_pin_type_str[i], str) == 0) {
			ret = i;
			break;
		}
	}

	return ret;
}

//	ADC

int enableADC() {
	int fd = -1;
	int ret = -1;
	char buffer[1024];
	char path[128];
	char *ptr = "cape-bone-iio";
	int size = strlen(ptr);

	if ((fd = open(BBB_SLOTS, O_RDWR | O_APPEND)) < 0) {
		return -1;
	}

	memset(buffer, 0, sizeof(buffer));

	if ((ret = read(fd, buffer, sizeof(buffer))) < 0) {
		return -1;
	}

	if (strncmp(buffer, ptr, size) != 0) {
		LOG("Enabling ADC\n");

		if (write(fd, ptr, size) != size) {
			return -1;
		}
	}

	return 0;
}

int getADC(int id) {
	int fd = -1;
	int ret = -1;
	char buffer[128];
	char path[128];
	struct stat st;

	memset(path, 0, sizeof(path));
	snprintf(path, sizeof(path), "%s/AIN%d", BBB_HELPER, id);

	if (stat(path, &st) == 0) {
		if ((fd = open(path, O_RDONLY)) < 0) {
			return -1;
		}

		memset(buffer, 0, sizeof(buffer));
		
		if ((ret = read(fd, buffer, sizeof(buffer))) < 0) {
			return -1;
		}

		ret = atoi(buffer);
	}

	return ret;
}

//	I2C

int enableI2Cdevice(int bus, unsigned char address, char *module) {
	int fd = -1;
	int ret = -1;
	char path[128];
	char ptr[128];

	struct stat st;

	if (address > 0 && module != NULL) {
		memset(path, 0, sizeof(path));
		snprintf(path, sizeof(path), "%s/%d-00%.2x", BBB_I2CDEVICES, bus, address);

		if (stat(path, &st) != 0 && errno == ENOENT) {
			memset(path, 0, sizeof(path));
			snprintf(path, sizeof(path), "/sys/bus/i2c/devices/i2c-%d/new_device", bus);

			if (stat(path, &st) != 0) {
				return -1;
			}

			if ((fd = open(path, O_WRONLY)) < 0) {
				return -1;
			}

			LOG("Enabling I2C device(%d), Address(0x%.2x), module(%s)\n", bus, address, module);

			memset(ptr, 0, sizeof(ptr));
			ret = snprintf(ptr, sizeof(ptr), "%s 0x%.2x", module, address);

			if ((ret = write(fd, ptr, ret)) < 0) {
				ret = -1;
			} else {
				ret = 0;
			}

			close(fd);
		}
	}

	return ret;
}

int disableI2Cdevice(int bus, unsigned char address) {
	int fd = -1;
	int ret = -1;
	char path[128];
	char ptr[128];
	struct stat st;

	if (address > 0) {
		memset(path, 0, sizeof(path));
		snprintf(path, sizeof(path), "%s/%d-00%.2x", BBB_I2CDEVICES, bus, address);

		if (stat(path, &st) == 0) {
			memset(path, 0, sizeof(path));
			snprintf(path, sizeof(path), "/sys/bus/i2c/devices/i2c-%d/delete_device", bus);

			if (stat(path, &st) != 0) {
				return -1;
			}

			if ((fd = open(path, O_WRONLY)) < 0) {
				return -1;
			}

			LOG("Disabling I2C device(%d), Address(0x%.2x)\n", bus, address);

			memset(ptr, 0, sizeof(ptr));
			ret = snprintf(ptr, sizeof(ptr), "0x%.2x", address);

			if ((ret = write(fd, ptr, ret)) < 0) {
				ret = -1;
			} else {
				ret = 0;
			}

			close(fd);
		}
	}

	return -1;
}

int enableGpio(int gpio) {
	int ret = -1;
	int fd = -1;
	char path[128];
	char ptr[128];
	struct stat st;
	
	if (gpio > 0) {
		memset(path, 0, sizeof(path));
		snprintf(path, sizeof(path), "%s/gpio%d", BBB_GPIOP, gpio);

		if (stat(path, &st) != 0) {
			memset(path, 0, sizeof(path));
			snprintf(path, sizeof(path), "%s/export", BBB_GPIOP);

			if ((fd = open(path, O_WRONLY)) < 0) {
				return -1;
			}

			LOG("Enabling GPIO(%d)\n", gpio);

			memset(ptr, 0, sizeof(ptr));
			ret = snprintf(ptr, sizeof(ptr), "%d", gpio);

			if (write(fd, ptr, ret) < 0) {
				ret = -1;
			} else {
				ret = 0;
			}

			close(fd);			
		}
	}

	return ret;
}

int disableGpio(int gpio) {
	int ret = -1;
	int fd = -1;
	char path[128];
	char ptr[128];
	struct stat st;
	
	if (gpio > 0) {
		memset(path, 0, sizeof(path));
		snprintf(path, sizeof(path), "%s/gpio%d", BBB_GPIOP, gpio);

		if (stat(path, &st) == 0) {
			memset(path, 0, sizeof(path));
			snprintf(path, sizeof(path), "%s/unexport", BBB_GPIOP);

			if ((fd = open(path, O_WRONLY)) < 0) {
				return -1;
			}

			LOG("Disabling GPIO(%d)\n", gpio);

			memset(ptr, 0, sizeof(ptr));
			ret = snprintf(ptr, sizeof(ptr), "%d", gpio);

			if (write(fd, ptr, ret) < 0) {
				ret = -1;
			} else {
				ret = 0;
			}

			close(fd);			
		}
	}

	return ret;
}

int setGpioDirection(int gpio, int direction) {
	int ret = -1;
	int fd = -1;
	char path[128];
	char *ptr = "IN";
	struct stat st;
	
	if (gpio > 0) {
		memset(path, 0, sizeof(path));
		snprintf(path, sizeof(path), "%s/gpio%d/direction", BBB_GPIOP, gpio);

		if (stat(path, &st) == 0) {
			if ((fd = open(path, O_WRONLY)) < 0) {
				return -1;
			}

			if (direction > 0) {
				ret = 3;
				ptr = "out";
			} else {	
				ret = 2;
				ptr = "in";
			}

			if (write(fd, ptr, ret) < 0) {
				ret = -1;
			} else {
				ret = 0;
			}

			close(fd);	
		}
	}

	return ret;
}

int getGpioDirection(int gpio) {
	int ret = -1;
	int fd = -1;
	char path[128];
	char ptr[128];
	struct stat st;

	if (gpio > 0) {
		memset(path, 0, sizeof(path));
		snprintf(path, sizeof(path), "%s/gpio%d/direction", BBB_GPIOP, gpio);

		if (stat(path, &st) == 0) {
			if ((fd = open(path, O_RDONLY)) < 0) {
				return -1;
			}

			memset(ptr, 0, sizeof(ptr));

			if ((ret = read(fd, ptr, sizeof(ptr))) <= 0) {
				close(fd);
				return -1;
			}

			if (ret >= 2 && strncmp(ptr, "in", 2) == 0) {
				ret = 0;				
			} else {
				if (ret >= 3 && strncmp(ptr, "out", 3) == 0) {
					ret = 1;
				} else {
					ret = -1;
				}
			}

			close(fd);	
		}
	}

	return ret;
}

int setGpioValue(int gpio, int value) {
	int ret = -1;
	int fd = -1;
	char path[128];
	char ptr[128];
	struct stat st;

	if (gpio > 0 && value >= 0) {
		memset(path, 0, sizeof(path));
		snprintf(path, sizeof(path), "%s/gpio%d/value", BBB_GPIOP, gpio);

		if (stat(path, &st) == 0) {
			if ((fd = open(path, O_WRONLY)) < 0) {
				return -1;
			}

			memset(ptr, 0, sizeof(ptr));
			ret = snprintf(ptr, sizeof(ptr), "%d", (value > 0) ? 1 : 0);

			if (write(fd, ptr, ret) < 0) {
				ret = -1;
			} else {
				ret = 0;
			}			

			close(fd);	
		}
	}

	return ret;
}

int getGpioValue(int gpio) {
	int ret = -1;
	int fd = -1;
	char path[128];
	char ptr[128];
	struct stat st;

	if (gpio > 0) {
		memset(path, 0, sizeof(path));
		snprintf(path, sizeof(path), "%s/gpio%d/value", BBB_GPIOP, gpio);

		if (stat(path, &st) == 0) {
			if ((fd = open(path, O_RDONLY)) < 0) {
				return -1;
			}

			memset(ptr, 0, sizeof(ptr));

			if ((ret = read(fd, ptr, sizeof(ptr))) <= 0) {
				close(fd);
				return -1;
			}

			ret = atoi(ptr);		

			close(fd);
		}
	}

	return ret;
}

//	Debug

void showByIndex(int index) {
	LOG("%s %s %s %s %s\n", getPinStrByIndex(index), getGpioStrByIndex(index), getTypeStrByIndex(index), getSignalNameByIndex(index), getNameByIndex(index));
}

void showPin(char *str) {
	showByIndex(getIndexByStr(str));
}

void showAll() {
	int i;

	for (i = 0; i < bbb_table_size; i++) {
		showByIndex(i);	
	}
}

void showByType(bbb_pin_type type) {
	int i;

	for (i = 0; i < bbb_table_size; i++) {
		if (pinout_table[i].type1 == type || pinout_table[i].type2 == type || pinout_table[i].type2 == type) {
			showByIndex(i);
		}
	}
}

void showByTypeOnly(bbb_pin_type type) {
	int i;

	for (i = 0; i < bbb_table_size; i++) {
		int found = 0;

		if (pinout_table[i].type1 == type || pinout_table[i].type2 == type || pinout_table[i].type2 == type) {
			found = 1;
		}

		if (type != BBB_ANALOG) {
			if (pinout_table[i].type1 == type || pinout_table[i].type1 == BBB_GPIO) {
				if (pinout_table[i].type2 == type || pinout_table[i].type2 == BBB_GPIO) {
					if (pinout_table[i].type3 == type || pinout_table[i].type3 == BBB_GPIO) {
						if (found) {
							showByIndex(i);
						}
					}
				}
			}
		}

		else {
			if (found) {
				showByIndex(i);
			}
		}
	}
}
