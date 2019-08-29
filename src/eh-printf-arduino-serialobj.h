/* SPDX-License-Identifier: LGPL-2.1-or-later */
/* eh-printf-arduino-serialobj.h: printf adapter for Arduino */
/* Copyright (C) 2012, 2017, 2019 Eric Herman <eric@freesa.org> */
/* https://github.com/ericherman/libeh-printf */

#ifndef EH_PRINTF_ARDUINO_SERIALOBJ_H
#define EH_PRINTF_ARDUINO_SERIALOBJ_H

#include <Arduino.h>
#include <HardwareSerial.h>

#if defined( _VARIANT_ARDUINO_DUE_X_ ) || defined( ARDUINO_SAM_DUE )
#if ARDUINO_DUE_USB_PROGRAMMING == 1
#define SERIAL_OBJ Serial
#else // default to the NATIVE port
#define SERIAL_OBJ SerialUSB
#endif
#endif

#ifndef SERIAL_OBJ
#define SERIAL_OBJ Serial
#endif

#endif /* EH_PRINTF_ARDUINO_SERIALOBJ_H */
