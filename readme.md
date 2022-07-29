
# Teapot BWLR1B
 <p align="center"> <img src="https://raw.githubusercontent.com/teapotlaboratories/bwlr1b/master/docs/images/cr2450_aa_with_case.jpg" alt="drawing"  width="50%" height="50%"/></p>
 
Teapot BWLR1B is a wireless LoRa environmental sensor capable of sensing temperature, humidity, air pressure and air quality using the on-board BME680. 
By using an STM32WLE MCU, the device is capable of multi-year operation before changing the batteries

Teapot BWLR1B is part of  [Teapot open-hardware project](https://github.com/teapotlaboratories). 

## Specification

- [RAK3172](https://docs.rakwireless.com/Product-Categories/WisDuo/RAK3172-Module/Overview/): An STM32WLE5CC module
- 3.3V only power/pin. 
- 2uA Deep-Sleep
- BME680 for Environmental Sensing
- Switchable TX Power. 14 dBm(50mA) or 22 dBm(140mA) ( on 915MHz frequency )
- Supports LoRaWAN 1.0.3
- 1KM+ Range
- UART2 breakout for **Arduino** progamming
- SWD breakout for **Mbed OS/STM32Cube** programming
- SMA antenna connector
- **CR2450** battery holder *xor* **AA** battery holder
- Capacitor ( [optional to prolong CR2450 usage](https://www.rs-online.com/designspark/can-i-prolong-my-coin-cell-battery-life-with-a-capacitor) )


> Based-on [TI's White Paper](https://www.ti.com/lit/wp/swra349/swra349.pdf), using coin-cell to draw short high-power pulses (~40mA) is possible, but will reduce the effective capacity of the battery. The White Paper proposed a solution to increase the effective capacity
## Schematics

<p align="center"> <img src="https://raw.githubusercontent.com/teapotlaboratories/bwlr1b/master/hardware/schematic_1920x1356.png" alt="schematic"/></p>

## Boards 
 <p align="center"> <img src="https://github.com/teapotlaboratories/bwlr1b/raw/master/docs/images/3d_pcb.gif" alt="drawing"  width="50%" height="50%"/></p>

Built using KiCAD v6, the board is design to be as small as possible when operated using CR2450 coin-cell batteries

### Design
The device designed to be operable using **2x CR2450** coin cell batteries *xor* the standard **2x AA** batteries.
By using the RAK3172 module, it is possible to use the IPEX [variant](https://store.rakwireless.com/products/wisduo-lpwan-module-rak3172?variant=40014759297222) of the module and use a [PCB antenna](https://store.rakwireless.com/products/pcb-antenna-for-lora) connected to the IPEX port on the RAK3172 module.
| Top Board | Bottom Board with AA or CR2450 Battery |
|--|--|
| <p align="center"> <img src="https://github.com/teapotlaboratories/bwlr1b/raw/master/docs/images/top_pcb.jpg" alt="drawing"  width="77%" height="77%"/></p> | <p align="center"> <img src="https://github.com/teapotlaboratories/bwlr1b/raw/master/docs/images/bottom_pcb.jpg" alt="drawing"  width="100%" height="100%"/></p> |
  <p align="center"> <img src="https://raw.githubusercontent.com/teapotlaboratories/bwlr1b/master/hardware/pcb.png" alt="drawing"  width="50%" height="50%"/></p> 
  
### Case
 The cases are available for the CR2450 variant and the AA variant, 3D printable with any generic 3D printer with/without suppport (depends on the orientation). The STL files are available [here](https://github.com/teapotlaboratories/bwlr1b/tree/master/hardware/case)
 <p align="center"> <img src="https://github.com/teapotlaboratories/bwlr1b/raw/master/docs/images/open_case.jpg" alt="drawing"  width="50%" height="50%"/></p> 


 
### Bill Of Materials
Most of the components are generic and can be bought from any electornics/semi-conductor distributor. RAK3172 is the only component available in [RAKwireless store.](https://store.rakwireless.com/products/wisduo-lpwan-module-rak3172?variant=40014759493830). The bill of materials can be downloaded [here](https://raw.githubusercontent.com/teapotlaboratories/bwlr1b/master/hardware/bill_of_materials.csv)

> :warning: **Be sure to buy the RAK3172 variant without IPEX to use the SMA connector** 

|Id |Designator                      |Package                                       |Quantity|Designation|Supplier and ref|Notes                            |
|---|--------------------------------|----------------------------------------------|--------|-----------|----------------|---------------------------------|
|1  |BT2                             |BatteryHolder_Keystone_2462_2xAA              |1       |2x AA      |                |Mutual Exclusive with BT3 and BT1|
|2  |BT3,BT1                         |BatteryHolder_Keystone_3008_1x2450            |2       |CR2450     |                |Mutual Exclusive with BT2        |
|3  |C5,C12,C11,C3                   |C_1206_3216Metric_Pad1.33x1.80mm_HandSolder   |4       |100nF      |                |                                 |
|4  |C9,C8,C10,C2,C4,C13,C14,C6,C1,C7|CP_EIA-3528-15_AVX-H_Pad1.50x2.35mm_HandSolder|10      |330uF      |                |Optional                         |
|5  |J3                              |SMA_Amphenol_132289_EdgeMount                 |1       |915MHz SMA |                |                                 |
|6  |Q1                              |SOT-23                                        |1       |AO3407     |                |                                 |
|7  |R5                              |R_1206_3216Metric_Pad1.30x1.75mm_HandSolder   |1       |1K         |                |                                 |
|8  |R7,R2,R3,R6                     |R_1206_3216Metric_Pad1.30x1.75mm_HandSolder   |4       |10K        |                |                                 |
|9  |SW3                             |SW_SPST_Omron_B3FS-100xP                      |1       |RESET      |                |                                 |
|10 |SW4                             |SW_SPST_Omron_B3FS-100xP                      |1       |BOOT       |                |                                 |
|11 |U1                              |BME680-PSON80P300X300X100-8N                  |1       |BME680     |                |                                 |
|12 |U2                              |RAK3172 without IPEX                                       |1       |RAK3172    |RAKwireless     |                                 |


## Programming
Programming the device can be done over the **UART2** or **SWD**, available next to the SMA antenna port.
Out of the factory, the RAK3172 chip ships with an **AT firmware** that can be tested by connecting a USB-to-UART bridge to the **UART2** port.

The following are some very good tutorial to start developing with the device:

- [Communicating with the AT firmware](https://docs.rakwireless.com/Product-Categories/WisDuo/RAK3172-Module/Quickstart/#rak3172-as-a-lora-lorawan-modem-via-at-command)
 - [Programming with Arduino](https://docs.rakwireless.com/Product-Categories/WisDuo/RAK3172-Module/Quickstart/#rak3172-as-a-stand-alone-device-using-rui3)
 - [Programming with STM32Cube](https://docs.rakwireless.com/Product-Categories/WisDuo/RAK3172-Module/Low-Level-Development/#rak3172-on-stm32cubeide-with-stm32wl-sdk-v1-0-0)
 - [Programming with MbedOS](https://github.com/hallard/LoRa-E5-Tiny/blob/main/README.md#compile-and-flash-firmware)

For connecting to the **UART2** port, use any USB-to-UART bridge module. In testing, the [Sparkfun](https://www.sparkfun.com/products/14050) board is used for communication with AT firmware and programming over **Arduino**.
 <p align="center"> <img src="https://raw.githubusercontent.com/teapotlaboratories/bwlr1b/master/docs/images/sparkfun_ftdi.jpeg" width="30%" height="30%"><br>Sparkfun USB-to-UART Bridge</p>

> :warning: **Be sure to only use 3.3V module. Do not 5V module** 

For connecting to the **SWD** port, use ST-Link v2  in-circuit debugger and programmer from STM. In testing, ST-Link v2 clone will not work. The ST-Link v2 should atleast be reconizeable by the [STM32CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html).
A cheap and alternative way to get an authorized ST-Link is to buy a Nucleo board, cut the top part which contain the ST-Link and use it as an external programmer.
 <p align="center"> <img src="https://raw.githubusercontent.com/teapotlaboratories/bwlr1b/master/docs/images/nucleo_st-linkv2.jpeg" width="70%" height="70%"><br>ST-Link v2 from a Nucleo Development Board</p>
Here are some good tutorial to convert a Nucleo to and external ST-Link v2:

 - https://www.radioshuttle.de/en/turtle-en/nucleo-st-link-interface-en/
 - https://jeelabs.org/book/1547a/index.html

## Reference
The project won't be possible without the amazing work from people across the globe. The following are the reference to those awesome projects:

 - [LoRa e5 Tiny](https://github.com/hallard/LoRa-E5-Tiny)
 - [AERQ - Air Quality Monitoring](https://www.seeedstudio.com/blog/2022/04/27/monitoring-indoor-air-pollutants-the-silent-issue-for-smart-city-iot-using-seeed-lora-e5-and-fusion-pcba/)


## License
The product is open-source! However, some part of library used under **src**, might have it's own license.

![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)
