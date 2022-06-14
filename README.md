# Latency measurement system for HDMI display using ZYBO(FPGA)

Usage and details here (Japanese) → https://fumimaker.net/entry/2022/06/14/205526

## About

This system can measure the delay of an HDMI display: it outputs an HDMI signal, measures the delay time until the display emits light and returns as light. I need a phototransistor, a resistor, and a breadboard.

![2022-06-13 23.57.15](https://raw.githubusercontent.com/fumimaker/Public_Images/main/Images/20220614_1655132423_2022-06-13%2023.57.15.jpg)

## Environments

- Vivado 2019.2
- Vitis 2019.2
- Vivado HLS 2019.2
- Digilent ZYBO Z7-20



## Build FPGA system

1. download or clone this repo

`git clone https://github.com/fumimaker/display_latency.git`

2. download or clone digilent vivado-library

`git clone https://github.com/Digilent/vivado-library.git`

3. Copy rgb2dvi from vivado-library under ip_repo in this repository
4. Create project on the Vivado

`source ./display_latency.tcl`

![image-20220611225603997](https://raw.githubusercontent.com/fumimaker/Public_Images/main/Images/20220611_1654955764_image-20220611225603997.png)

```
[BD 41-49] Could not find abstraction definition for the interface: TMDS 
[BD 41-51] Could not find bus definition for the interface: TMDS 
```

These errors are not problem.

5. Generate bitstream on vivado
6. Export hardware on vivado
7. Open Vitis and create helloworld project.
8. Import a source code src/vitis/main.c on vitis (or overwrite helloworld.c)

![image-20220611231134200](https://raw.githubusercontent.com/fumimaker/Public_Images/main/Images/20220611_1654956694_image-20220611231134200.png)

## Build sensor system

I used a readily available NJL7502L phototransistor and implemented the following circuit on a breadboard.

![image-20220614005603738](https://raw.githubusercontent.com/fumimaker/Public_Images/main/Images/20220614_1655135764_image-20220614005603738.png)

The phototransistor was difficult to mount on the display, so I made a fixture with a 3D printer. [here](https://www.thingiverse.com/thing:5410079) is fixture. Be careful not to let any light other than that of the display enter the sensor, as this will cause an error. In the fixture, the sensor is pushed in to prevent ambient light from entering.

![2022-06-14 00.28.47](https://raw.githubusercontent.com/fumimaker/Public_Images/main/Images/20220614_1655134168_2022-06-14%2000.28.47.jpg)

## Measure

Make a sensor circuit and connect it to ZYBO on **JE[2] port.** (If you don't like it, you can change it to another place. (If you don't like it, you can change it to another place.) Connect ZYBO and the monitor with an HDMI cable. Place the sensor on the display. Make sure there is no gap between the sensor and the display.

![2022-06-14 20.07.55](https://raw.githubusercontent.com/fumimaker/Public_Images/main/Images/20220614_1655205310.jpg)

Open serial terminal(115200bps at 8N1)，and wirte to ZYBO at vitis(Launch on hardware). If you can see “Hello world, type something to start”, you are in serial communication successfully. 

![image-20220613191827213](https://raw.githubusercontent.com/fumimaker/Public_Images/main/Images/20220613_1655115507_image-20220613191827213.png)

Type something, and press enter to start measurement. (display flashing) You can see the latency[ms] on serial monitor.

![image-20220613234942839](https://raw.githubusercontent.com/fumimaker/Public_Images/main/Images/20220613_1655131783_image-20220613234942839.png)

Note: If the slide switch is set to "H", the instrument enters the test mode and measurement cannot be performed. Like this ↓. This mode can use as sensor adjustment.

![2022-06-14 00.20.49](https://github.com/fumimaker/Public_Images/blob/main/Images/20220614_1655134818_2022-06-14%2000.20.49.jpg)

## Author

[@fumi_maker](https://twitter.com/fumi_maker) Bug fixes and comments are welcome!

## Lisence 

This project is MIT Lisence.

