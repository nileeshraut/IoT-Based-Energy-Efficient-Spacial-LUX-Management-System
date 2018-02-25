# IoT-Based-Energy-Efficient-Spacial-LUX-Management-System
The light bulb is switched on/off by analysing environmental conditions and also keeps tracking the power consumed by the light bulb  , life of bulb remaining and all this data is uploaded onto the cloud using IoT.

# Description:
  Street lights in remote areas need to be switched by manual switches and thus needs human interactions. But what if they are switched by sensing environmental light intensity , so that proper switching is done on right time , no human interaction needed for remote locations.
  Also this project keeps track of  power consumed by bulb, reports for how much duration the light bulb is ON so that remaining life of bulb can be calculated.
  Their is also provision for reporting if the light bulb accidentally gets damaged or fused or not working so that it can gets replaced in no time or soon as possible.
  
# Working:

  We use Microcontroller 8051 to handle the operations of sensing environment and switching light bulb.
  
1. LDR is used to sense the environment. We use MCP3204 12-bit Analog to digital Converter for reading data from LDR and provide it in digital form to microcontroller. 
  Whenever it is "dark" , the bulb is switched on and rest of tyhe circuit is activated for calculating various terms.

2. Also BH1750 LUX sensor is used to check light bulb is working or not. Whenever it is "dark" , the circuit gets activated and from this time BH1750 starts tracking the bulb status.

3. DS1307 RTC is used to measure the real time working hours of the bulb , so that we can calculate the remaining life of the bulb.

4. The data from RTC , BH1750 and MCP3204 needs to be uploaded on Cloud for further analysis , so with the help of UART Communication , it is transferred to Raspberry Pi where it is uploaded to the PubNub server.

5. The "C+PUBNUB" libraries and dependencies  are installed on RaspberryPi OS.

6. Thus we can observe each and every action taken by 8051 at anyplace over the Internet.

# Devices Used
1. Microcontroller 8051
2. LDR
3. BH1750 LUX Sensor
4. MCP3204 ADC 
5. DS1307 RTC
6. RaspberryPi Board
