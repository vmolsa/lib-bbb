#!/bin/sh

SUDO=sudo

GPLR1="P8_27"
GPLG1="P8_28"
GPLB1="P8_29"

GPLR2="P8_30"
GPLG2="P8_31"
GPLB2="P8_32"

GPLR3="P8_33"
GPLG3="P8_34"
GPLB3="P8_35"

GPLR4="P8_39"
GPLG4="P8_40"
GPLB4="P8_41"

$SUDO bbb --enable-gpio-pin $GPLR1 --gpio-pin $GPLR1 --set-direction 1 --set-value 1 # LED 1 RED
$SUDO bbb --enable-gpio-pin $GPLG1 --gpio-pin $GPLG1 --set-direction 1 --set-value 1 # LED 1 GREEN
$SUDO bbb --enable-gpio-pin $GPLB1 --gpio-pin $GPLB1 --set-direction 1 --set-value 1 # LED 1 BLUE
$SUDO bbb --enable-gpio-pin $GPLR2 --gpio-pin $GPLR2 --set-direction 1 --set-value 1 # LED 2 RED
$SUDO bbb --enable-gpio-pin $GPLG2 --gpio-pin $GPLG2 --set-direction 1 --set-value 1 # LED 2 GREEN
$SUDO bbb --enable-gpio-pin $GPLB2 --gpio-pin $GPLB2 --set-direction 1 --set-value 1 # LED 2 BLUE
$SUDO bbb --enable-gpio-pin $GPLR3 --gpio-pin $GPLR3 --set-direction 1 --set-value 1 # LED 3 RED
$SUDO bbb --enable-gpio-pin $GPLG3 --gpio-pin $GPLG3 --set-direction 1 --set-value 1 # LED 3 GREEN
$SUDO bbb --enable-gpio-pin $GPLB3 --gpio-pin $GPLB3 --set-direction 1 --set-value 1 # LED 3 BLUE
$SUDO bbb --enable-gpio-pin $GPLR4 --gpio-pin $GPLR4 --set-direction 1 --set-value 1 # LED 4 RED
$SUDO bbb --enable-gpio-pin $GPLG4 --gpio-pin $GPLG4 --set-direction 1 --set-value 1 # LED 4 GREEN
$SUDO bbb --enable-gpio-pin $GPLB4 --gpio-pin $GPLB4 --set-direction 1 --set-value 1 # LED 4 BLUE

