#!/bin/sh

SUDO=sudo

$SUDO bbb --enable-i2c-device 1 --address 0x53 --module adxl34x
$SUDO bbb --enable-i2c-device 1 --address 0x21 --module hmc6352
$SUDO bbb --enable-i2c-device 1 --address 0x68 --module l3g4200d
$SUDO bbb --enable-i2c-device 1 --address 0x77 --module bmp085
