/*****************************************************************************************
* This is implementation of CAN BUS ASCII protocol based on LAWICEL v1.3 serial protocol
*  of CAN232/CANUSB device (http://www.can232.com/docs/can232_v3.pdf)
*
* Made for Arduino with Seeduino/ElecFreaks CAN BUS Shield based on MCP2515
*
* Copyright (C) 2015 Anton Viktorov <latonita@yandex.ru>
*                                    https://github.com/latonita/arduino-canbus-monitor
*
* This library is free software. You may use/redistribute it under The MIT License terms. 
*
*****************************************************************************************/

#include <SPI.h>
#include "mcp_can.h"
#include "can-232.h"
#include "SoftwareSerial.h"

#define DEBUG_MODE

void setup() {
	  Serial.begin(LW232_DEFAULT_BAUD_RATE); // default COM baud rate is 115200. 

        // Can232::init  (RATE, CLOCK)
        // Rates: CAN_10KBPS, CAN_20KBPS, CAN_50KBPS, CAN_100KBPS, CAN_125KBPS, CAN_250KBPS, CAN_500KBPS, CAN_500KBPS, CAN_1000KBPS, CAN_83K3BPS
        //        Default is CAN_83K3BPS ;)))))))))
        // Clock: MCP_16MHz or MCP_8MHz. 
        //        Default is MCP_16MHz. Please note, not all CAN speeds supported. check big switch in mcp_can.cpp
        // defaults can be changed in mcp_can.h

//        Can232::init();             // rate and clock = LW232_DEFAULT_CAN_RATE and LW232_DEFAULT_CLOCK_FREQ
//        Can232::init(CAN_125KBPS);  // rate = 125, clock = LW232_DEFAULT_CLOCK_FREQ
    Can232::init(CAN_125KBPS, MCP_16MHz); // set default rate you need here and clock frequency of CAN shield. Typically it is 16MHz, but on some MCP2515 + TJA1050 it is 8Mhz

//    Can232::setOutputProtocol(OutputProtocol::PROTO_GVRET); // PROTO_LAWICEL (default) or PROTO_GVRET for SavvyCAN

    // optional custom packet filter to reduce number of messages comingh through to canhacker
    // Can232::setFilter(myCustomAddressFilter); 
}

INT8U myCustomAddressFilter(INT32U addr) {
    INT8U ret = LW232_FILTER_SKIP; //LW232_FILTER_PROCESS or LW232_FILTER_SKIP
    switch(addr) {
    //    case 0x01b: //VIN
    //    case 0x1C8:  //lights
    //    case 0x2C0: // pedals
        case 0x3d0: // sound vol, treb..
      ret = LW232_FILTER_PROCESS;
    //    case 0x000: // ?
    //    case 0x003: //shifter
    //    case 0x015: // dor open close affects this as well
    //    case 0x02c: // ???
    //        ret = 0;
    //        break;
    //    case 0x002:
    //    case 0x1a7: //fuel cons or some other
    //      ret = 1;
    //      break;
    //     default: 
    //       ret = 0;
    }

  return ret;
}

void loop() {
    Can232::loop();
}

void serialEvent() {
    Can232::serialEvent();
}

