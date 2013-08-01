#ifndef _BBB_H
#define _BBB_H

// 	BeagleBone Black Config

#define BBB_SLOTS "/sys/devices/bone_capemgr.*/slots"
#define BBB_HELPER "/sys/devices/ocp.*/helper.*"
#define BBB_OCP2 "/sys/devices/ocp.*"
#define BBB_GPIOP "/sys/class/gpio"				
#define BBB_I2CDEVICES "/sys/bus/i2c/devices"

//	EOC

#ifndef Hz
#define Hz 1000000000
#endif

#ifndef kHz
#define kHz 1000000
#endif

#ifndef MHz
#define MHz 1000
#endif

#ifndef LOG
#define LOG(...) printf(__VA_ARGS__);
#endif

#define BBB_GPIO0(x) x
#define BBB_GPIO1(x) x + 32
#define BBB_GPIO2(x) x + 64
#define BBB_GPIO3(x) x + 96

#define BBB_PWM0
#define BBB_PWM1
#define BBB_PWM2
#define BBB_PWM3
#define BBB_PWM4
#define BBB_PWM5
#define BBB_PWM6
#define BBB_PWM7
#define BBB_PWM8

#define BBB_SERIAL0
#define BBB_SERIAL1
#define BBB_SERIAL2
#define BBB_SERIAL4

static char *bbb_pin_type_str[] = {
	"none", "gpio", "analog", "serial", "pwm", "timer", "i2c", "spi",
};

static int bbb_pin_type_str_size = sizeof(bbb_pin_type_str) / sizeof(char *);

typedef enum {
	BBB_NONE = 0, 
	BBB_GPIO, 
	BBB_ANALOG, 
	BBB_SERIAL, 
	BBB_PWM, 
	BBB_TIMER, 
	BBB_I2C, 
	BBB_SPI, 
} bbb_pin_type;

typedef struct _bbb_pinout_gpio {
	int header;
	int pin;
	int gpio;
	bbb_pin_type type1;
	bbb_pin_type type2;
	bbb_pin_type type3;
	char *sig;
	char *name;
} bbb_pinout_gpio;

static bbb_pinout_gpio pinout_table[] = {
	{ 8, 1, BBB_NONE, BBB_NONE,  BBB_NONE, BBB_NONE, "GND", "GND", }, 
	{ 8, 2, BBB_NONE, BBB_NONE,  BBB_NONE, BBB_NONE, "GND", "GND", }, 
	{ 8, 3, BBB_GPIO1(6), BBB_GPIO, BBB_GPIO, BBB_GPIO, "GPIO1_6", "gpmc_ad6" }, 
	{ 8, 4, BBB_GPIO1(7), BBB_GPIO, BBB_GPIO, BBB_GPIO, "GPIO1_7", "gpmc_ad7" }, 
	{ 8, 5, BBB_GPIO1(2), BBB_GPIO, BBB_GPIO, BBB_GPIO, "GPIO1_2", "gpmc_ad2" }, 
	{ 8, 6, BBB_GPIO1(3), BBB_GPIO, BBB_GPIO, BBB_GPIO, "GPIO1_3", "gpmc_ad3" }, 
	{ 8, 7, BBB_GPIO2(2), BBB_TIMER, BBB_GPIO, BBB_GPIO, "TIMER4", "gpmc_advn_ale" }, 
	{ 8, 8, BBB_GPIO2(3), BBB_TIMER, BBB_GPIO, BBB_GPIO, "TIMER7", "gpmc_oen_ren" }, 
	{ 8, 9, BBB_GPIO2(5), BBB_TIMER, BBB_GPIO, BBB_GPIO, "TIMER5", "gpmc_be0n_cle" }, 
	{ 8, 10, BBB_GPIO2(4), BBB_TIMER, BBB_GPIO, BBB_GPIO, "TIMER6", "gpmc_wen" }, 
	{ 8, 11, BBB_GPIO1(13), BBB_GPIO, BBB_GPIO, BBB_GPIO, "GPIO1_13", "gpmc_ad13" }, 
	{ 8, 12, BBB_GPIO1(12), BBB_GPIO, BBB_GPIO, BBB_GPIO, "GPIO1_12", "GPMC_AD12" }, 
	{ 8, 13, BBB_GPIO0(23), BBB_PWM, BBB_GPIO, BBB_GPIO, "EHRPWM2B", "gpmc_ad9" }, 
	{ 8, 14, BBB_GPIO0(26), BBB_PWM, BBB_GPIO, BBB_GPIO, "GPIO0_26", "gpmc_ad10" }, 
	{ 8, 15, BBB_GPIO1(15), BBB_GPIO, BBB_GPIO, BBB_GPIO, "GPIO1_15", "gpmc_ad15" }, 
	{ 8, 16, BBB_GPIO1(14), BBB_GPIO, BBB_GPIO, BBB_GPIO, "GPIO1_14", "gpmc_ad14" }, 
	{ 8, 17, BBB_GPIO0(27), BBB_PWM, BBB_GPIO, BBB_GPIO, "GPIO0_27", "gpmc_ad11" }, 
	{ 8, 18, BBB_GPIO2(1), BBB_GPIO, BBB_GPIO, BBB_GPIO, "GPIO2_1", "gpmc_clk_mux0" }, 
	{ 8, 19, BBB_GPIO0(22), BBB_PWM, BBB_GPIO, BBB_GPIO, "EHRPWM2A", "gpmc_ad8" }, 
	{ 8, 20, BBB_GPIO1(31), BBB_GPIO, BBB_GPIO, BBB_GPIO, "GPIO1_31", "gpmc_csn2" }, 
	{ 8, 21, BBB_GPIO1(30), BBB_GPIO, BBB_GPIO, BBB_GPIO, "GPIO1_30", "gpmc_csn1" }, 
	{ 8, 22, BBB_GPIO1(5), BBB_GPIO, BBB_GPIO, BBB_GPIO, "GPIO1_5", "gpmc_ad5" }, 
	{ 8, 23, BBB_GPIO1(4), BBB_GPIO, BBB_GPIO, BBB_GPIO, "GPIO1_4", "gpmc_ad4" }, 
	{ 8, 24, BBB_GPIO1(1), BBB_GPIO, BBB_GPIO, BBB_GPIO, "GPIO1_1", "gpmc_ad1" }, 
	{ 8, 25, BBB_GPIO1(0), BBB_GPIO, BBB_GPIO, BBB_GPIO, "GPIO1_0", "gpmc_ad0" }, 
	{ 8, 26, BBB_GPIO1(29), BBB_GPIO, BBB_GPIO, BBB_GPIO, "GPIO1_29", "gpmc_csn0" }, 
	{ 8, 27, BBB_GPIO2(22), BBB_GPIO, BBB_GPIO, BBB_GPIO, "GPIO2_22", "lcd_vsync" }, 
	{ 8, 28, BBB_GPIO2(24), BBB_GPIO, BBB_GPIO, BBB_GPIO, "GPIO2_24", "lcd_pclk" }, 
	{ 8, 29, BBB_GPIO2(23), BBB_GPIO, BBB_GPIO, BBB_GPIO, "GPIO2_23", "lcd_hsync" }, 
	{ 8, 30, BBB_GPIO2(25), BBB_GPIO, BBB_GPIO, BBB_GPIO, "GPIO2_25", "lcd_ac_bias_en" }, 
	{ 8, 31, BBB_GPIO0(10), BBB_GPIO, BBB_GPIO, BBB_GPIO, "UART5_CTSN", "lcd_data14" }, 
	{ 8, 32, BBB_GPIO0(11), BBB_GPIO, BBB_GPIO, BBB_GPIO, "UART5_RTSN", "lcd_data15" }, 
	{ 8, 33, BBB_GPIO0(9), BBB_GPIO, BBB_GPIO, BBB_GPIO, "UART4_RTSN", "lcd_data13" }, 
	{ 8, 34, BBB_GPIO2(17), BBB_PWM, BBB_SERIAL, BBB_GPIO, "UART3_RTSN", "lcd_data11" }, 
	{ 8, 35, BBB_GPIO0(8), BBB_GPIO, BBB_GPIO, BBB_GPIO, "UART4_CTSN", "lcd_data12" }, 
	{ 8, 36, BBB_GPIO2(16), BBB_PWM, BBB_SERIAL, BBB_GPIO, "UART3_CTSN", "lcd_data10" }, 
	{ 8, 37, BBB_GPIO2(14), BBB_PWM, BBB_SERIAL, BBB_GPIO, "UART5_TXD", "lcd_data8" }, 
	{ 8, 38, BBB_GPIO2(15), BBB_PWM, BBB_SERIAL, BBB_GPIO, "UART5_RXD", "lcd_data9" }, 
	{ 8, 39, BBB_GPIO2(12), BBB_GPIO, BBB_GPIO, BBB_GPIO, "GPIO2_12", "lcd_data6" }, 
	{ 8, 40, BBB_GPIO2(13), BBB_GPIO, BBB_GPIO, BBB_GPIO, "GPIO2_13", "lcd_data7" }, 
	{ 8, 41, BBB_GPIO2(10), BBB_GPIO, BBB_GPIO, BBB_GPIO, "GPIO2_10", "lcd_data4" }, 
	{ 8, 42, BBB_GPIO2(11), BBB_GPIO, BBB_GPIO, BBB_GPIO, "GPIO2_11", "lcd_data5" }, 
	{ 8, 43, BBB_GPIO2(8), BBB_PWM, BBB_GPIO, BBB_GPIO, "GPIO2_8", "lcd_data2" }, 
	{ 8, 44, BBB_GPIO2(9), BBB_PWM, BBB_GPIO, BBB_GPIO, "GPIO2_9", "lcd_data3" }, 
	{ 8, 45, BBB_GPIO2(6), BBB_PWM, BBB_GPIO, BBB_GPIO, "GPIO2_6", "lcd_data0" }, 
	{ 8, 46, BBB_GPIO2(7), BBB_PWM, BBB_GPIO, BBB_GPIO, "GPIO2_7", "lcd_data1" }, 
	{ 9, 1, BBB_NONE, BBB_NONE, BBB_NONE, BBB_NONE, "GND", "GND" }, 
	{ 9, 2, BBB_NONE, BBB_NONE, BBB_NONE, BBB_NONE, "GND", "GND" }, 
	{ 9, 3, BBB_NONE, BBB_NONE, BBB_NONE, BBB_NONE, "3.3V", "3.3V" }, 
	{ 9, 4, BBB_NONE, BBB_NONE, BBB_NONE, BBB_NONE, "3.3V", "3.3V" }, 
	{ 9, 5, BBB_NONE, BBB_NONE, BBB_NONE, BBB_NONE, "5V", "RAW_5V" }, 
	{ 9, 6, BBB_NONE, BBB_NONE, BBB_NONE, BBB_NONE, "5V", "RAW_5V" }, 
	{ 9, 7, BBB_NONE, BBB_NONE, BBB_NONE, BBB_NONE, "5V", "SYS_5V" }, 
	{ 9, 8, BBB_NONE, BBB_NONE, BBB_NONE, BBB_NONE, "5V", "SYS_5V" }, 	
	{ 9, 9, BBB_NONE, BBB_NONE, BBB_NONE, BBB_NONE, "PWR_BUT", "PWR_BUT" }, 
	{ 9, 10, BBB_NONE, BBB_NONE, BBB_NONE, BBB_NONE, "RESET", "RESET" }, 
	{ 9, 11, BBB_GPIO0(30), BBB_SERIAL, BBB_GPIO, BBB_GPIO, "UART4_RXD", "gpmc_wait0" }, 
	{ 9, 12, BBB_GPIO1(28), BBB_GPIO, BBB_GPIO, BBB_GPIO, "GPIO1_28", "gpmc_be1n" }, 
	{ 9, 13, BBB_GPIO0(31), BBB_SERIAL, BBB_GPIO, BBB_GPIO, "UART4_TXD", "gpmc_wpn" }, 
	{ 9, 14, BBB_GPIO1(18), BBB_GPIO, BBB_GPIO, BBB_PWM, "EHRPWM1A", "gpmc_a2" }, 
	{ 9, 15, BBB_GPIO1(16), BBB_GPIO, BBB_GPIO, BBB_PWM, "GPIO1_16", "gpmc_a0" }, 
	{ 9, 16, BBB_GPIO1(19), BBB_GPIO, BBB_GPIO, BBB_PWM, "EHRPWM1B", "gpmc_a3" }, 
	{ 9, 17, BBB_GPIO0(5), BBB_PWM, BBB_I2C, BBB_SPI, "I2C1_SCL", "spi0_cs0" }, 
	{ 9, 18, BBB_GPIO0(4), BBB_PWM, BBB_I2C, BBB_SPI, "I2C1_SDA", "spi0_d1" }, 
	{ 9, 19, BBB_GPIO0(13), BBB_TIMER, BBB_I2C, BBB_SERIAL, "I2C2_SCL", "uart1_rtsn" }, 
	{ 9, 20, BBB_GPIO0(12), BBB_TIMER, BBB_I2C, BBB_SERIAL, "I2C2_SDA", "uart1_ctsn" }, 
	{ 9, 21, BBB_GPIO0(3), BBB_PWM, BBB_SERIAL, BBB_SPI, "UART2_TXD", "spi0_d0" }, 
	{ 9, 22, BBB_GPIO0(2), BBB_PWM, BBB_SERIAL, BBB_SPI, "UART2_RXD", "spi0_sclk" }, 
	{ 9, 23, BBB_GPIO1(17), BBB_PWM, BBB_GPIO, BBB_GPIO, "GPIO1_17", "gpmc_a1" }, 
	{ 9, 24, BBB_GPIO0(15), BBB_SERIAL, BBB_GPIO, BBB_GPIO, "UART1_TXD", "uart1_txd" },
	{ 9, 25, BBB_GPIO3(21), BBB_GPIO, BBB_GPIO, BBB_GPIO, "GPIO3_21", "mcasp0_ahclkx" },
	{ 9, 26, BBB_GPIO0(14), BBB_SERIAL, BBB_GPIO, BBB_GPIO, "UART1_RXD", "uart1_rxd" }, 
	{ 9, 27, BBB_GPIO3(19), BBB_GPIO, BBB_GPIO, BBB_GPIO, "GPIO3_19", "mcasp0_fsr" }, 
	{ 9, 28, BBB_GPIO3(17), BBB_PWM, BBB_SPI, BBB_GPIO, "SPI1_CS0", "mcasp0_ahclkr" }, 
	{ 9, 29, BBB_GPIO3(15), BBB_PWM, BBB_SPI, BBB_GPIO, "SPI1_D0", "mcasp0_fsx" }, 
	{ 9, 30, BBB_GPIO3(16), BBB_PWM, BBB_SPI, BBB_GPIO, "SPI1_D1", "mcasp0_axr0" }, 
	{ 9, 31, BBB_GPIO3(14), BBB_PWM, BBB_SPI, BBB_GPIO, "SPI1_SCLK", "mcasp0_aclkx" }, 
	{ 9, 32, BBB_NONE, BBB_NONE, BBB_NONE, BBB_NONE, "VADC", "VADC" }, 
	{ 9, 33, BBB_NONE, BBB_ANALOG, BBB_NONE, BBB_NONE, "AIN4", "AIN4" }, 
	{ 9, 34, BBB_NONE, BBB_NONE, BBB_NONE, BBB_NONE, "AGND", "AGND" }, 
	{ 9, 35, BBB_NONE, BBB_ANALOG, BBB_NONE, BBB_NONE, "AIN6", "AIN6" }, 
	{ 9, 36, BBB_NONE, BBB_ANALOG, BBB_NONE, BBB_NONE, "AIN5", "AIN5" }, 
	{ 9, 37, BBB_NONE, BBB_ANALOG, BBB_NONE, BBB_NONE, "AIN2", "AIN2" }, 
	{ 9, 38, BBB_NONE, BBB_ANALOG, BBB_NONE, BBB_NONE, "AIN3", "AIN3" }, 
	{ 9, 39, BBB_NONE, BBB_ANALOG, BBB_NONE, BBB_NONE, "AIN0", "AIN0" }, 
	{ 9, 40, BBB_NONE, BBB_ANALOG, BBB_NONE, BBB_NONE, "AIN1", "AIN1" }, 
	{ 9, 41, BBB_GPIO0(20), BBB_TIMER, BBB_GPIO, BBB_GPIO, "CLKOUT2", "timer7_mux1" }, 
	{ 9, 41, BBB_GPIO3(20), BBB_GPIO, BBB_GPIO, BBB_GPIO, "GPIO3_20", "eQEP0_index" }, 
	{ 9, 42, BBB_GPIO0(7), BBB_PWM, BBB_SERIAL, BBB_SPI, "eCAP0_in_PWM0_out", "uart3_txd" }, 
	{ 9, 42, BBB_GPIO3(18), BBB_GPIO, BBB_GPIO, BBB_GPIO, "eQEP0A_in", "Mcasp0_aclkr" },
};

static int bbb_table_size = sizeof(pinout_table) / sizeof(bbb_pinout_gpio);

//	Get Index

int getIndexByStr(char *str);							// P8_3       => 2
int getIndexByPin(int header, int pin);						// 8, 3       => 2
int getIndexByGpio(int gpio);							// 38         => 2
int getIndexBySignalName(char *signalname);					// "GPIO1_6"  => 2
int getIndexByName(char *name);							// "gpmc_ad6" => 2

//	Index to values

int getHeader(int index);							// 2 => 8
int getPin(int index);								// 2 => 3
int getGpio(int index);								// 2 => 38
bbb_pin_type getType1(int index);						// 2 => BBB_GPIO = 1 
bbb_pin_type getType2(int index);						// 2 => BBB_GPIO = 1
bbb_pin_type getType3(int index);						// 2 => BBB_GPIO = 1
char *getSignalName(int index);							// 2 => "GPIO1_6"
char *getName(int index);							// 2 => "gpmc_ad6"

// 	Index to String Values

char *getPinStrByIndex(int index);						// 2 => "P8_3"
char *getGpioStrByIndex(int index);						// 2 => "38"
char *getTypeStrByIndex(int index);						// 2 => "gpio gpio gpio"
char *getSignalNameByIndex(int index);						// 2 => "GPIO1_6"
char *getNameByIndex(int index);						// 2 => "gpmc_ad6"

//	Types

char *pinType2str(bbb_pin_type type);						// 2 => analog
bbb_pin_type str2pinType(char *str);						// "analog" => 2

//	ADC

int enableADC();								// Enables Analog to Digital control
int getADC(int id);  								// id = "AIN[ID]"

//	I2C

int enableI2Cdevice(int bus, unsigned char address, char *module);		// Enables I2C Device on bus number by address
int disableI2Cdevice(int bus, unsigned char address);				// Disable I2C Device on bus number by address

//	GPIO

int enableGpio(int gpio);							// Enables GPIO enableGpio(getGpio(getIndexByStr("P9_12")));
int disableGpio(int gpio);							// Disables GPIO

int setGpioDirection(int gpio, int direction);					// 0 == IN && 1 == OUT
int getGpioDirection(int gpio);							// 0 == IN && 1 == OUT

int setGpioValue(int gpio, int value);						// 0 == LOW && 1 == HIGH
int getGpioValue(int gpio);							// 0 == LOW && 1 == HIGH

//	PWM

int enablePwm(int header, int pin);						// "P8_13" = 8, 13

int setPwmPeriod(int header, int pin, int time);				// 20000000 = 0.02 seconds == 50Hz
int setPwmDuty(int header, int pin, int time);					// 10000000 = 0.01 seconds == 50Hz / 2 == 50% duty
int setPwmHz(int header, int pin, char *hz);					// 50Hz, 100kHz, 1MHz, 25 = 25Hz
int setPwmPercent(int header, int pin, int duty);				// 0 - 100%
int setPwmPolarity(int header, int pin, int polarity);				// 0 || 1

int getPwmPeriod(int header, int pin);						// 20000000 
int getPwmDuty(int header, int pin);						// 10000000
char *getPwmHz(int header, int pin);						// 50Hz
int getPwmPercent(int header, int pin);						// 50%
int getPwmPolarity(int header, int pin);					// 0 || 1

//	Debug

void showByIndex(int index);							// Print values from pinout_table by index 
void showPin(char *str);							// showByIndex(getIndexByStr("P8_13"));
void showAll();									// Print table
void showByType(bbb_pin_type type);						// showByType(str2pinType("pwm"));
void showByTypeOnly(bbb_pin_type type);						// showByTypeOnly(str2pinType("pwm"));

#endif
