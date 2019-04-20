# Preparation

## Gyroscope

- MPU6050

- BMI160

  ![](https://github.com/HaoYejia/Anti-Phubber/blob/master/Images/BMI160-RealPhoto.jpg?raw=true)

  

## Motor

## Control board

- arduino
  - Beetle
  - Uno
  - Nano



# Mar 10th, 2019-Voltage Fitness

It's REALLY necessary to check the input voltage of the components. To be honest, it's the most important step during the preperation. Though it's pretty easy to find the components that fits each other, but there's still ones that don't.

Tip 1: Confirm your voltage. Make sure that the battery voltage fits the components.

Tip 2: Adjust the voltage when unfitness do exist. For example, to change the battery or to change the output voltage of board. The Beetle used in this project has a output voltage level as same as the battery (it's really excited to find out that the voltage can be easily changed by changing a battery instead of other complicated methods lol). Or, to find other ways to increase or decrease the output voltage by additional components (resistance, arduino, micro potential transformer, etc...)

## Methods to adjust the voltage:
### PWM

- Can only adjust to a lower voltage
- Possible higher efficiency by using the high-frequency switch

### Resistance

- Waste energy
- Can only lower the voltage
- Need calculation
- The constant resistance one is difficult to determine or change, while the changeable one is either not suitable for large power or has problem on reliability

### Chip

- Possible lower efficiency by using the MOS
- 

### Transformer (变压器)

- Physical isolation of input and out put.
- Large volume
- Cheap

# Mar 22th, 2019-Wire connection

A problem comes out while I was trying to get data from gyro and screen: the port is on the backside of the board, which is be blocked by the extension board.

[image]

[image]

The BMI160 gyro requires SDA and SCL port while the screen requires RX and TX port. Unfortunately, all these port are on the back side and be blocked.

[photo of standard connection between two boards, showing that these ports can’t be reached]4

## Method to solve this problem

### To use beetle board only

- not-very-much additional welds
- smaller volume
- probably more difficult welds

### Change the connection between the two boards

#### Up-side-down

To up-side-down the beetle board in order to access the port.

- require another  two welds
- the positive and negative of the board would reverse
  - battery protection may fail
  - easy to misconnect the + and - ports

#### Beneath the board

- require lots more welds
- larger volume

### To have additional wires

- wires may be blocked by RESET  port and the capacitance
- lots more welds

## Final approach: pluggable connection without weld

- To weld the female end of solid tip jump wire to the beetle. Therefore, it’s pluggable without welding. 

  [image of this method]

- Also, I weld an additional wire since there is enough space as the board is elevated. 



# Mar 22th, 2019-A Failure: a copper foil falls off from the board

This happened when I was trying to disconnect the Beetle and the expansion board. To fully wipe off the Tin on the port, I used a copper wire to absorb it which require long-time heating. It cause the falling off of the D9 port and waste it.

A expanded research question: How to adjust the setting of tempreture or other parameters so that the foil will not fall off while the Tin can be wiped out enough to pull out the components?

# Mar 23th, 2019-Common Ground problem

Common ground refers to that you have to connect the GND if there are multiple power sources for different components, especially when you are trying to let them communicate.

The sensor, especially the sensor for single chip, output and input signals with HIGH or LOW voltage. However,  the voltage level is relative to the level on GND. In other words, the GND must be connected in order to provide a common base line of the signal. 

It’s pretty similar with the fact that you cannot find out the voltage while you put one needle of multimeter on one circuit while putting the other needle on another. There is no potential difference between these points, therefore impossible to measure the voltage.

#Mar 29th, 2019-Low Voltage problem

The battery I use is Li-on one that has a output voltage of 3.7V. After using for a while, the voltage drop to 3.5V but still lies in the voltage range of the board (3V to 6V). However, the extension board have another resistance that lower the voltage even more. The result of the output voltage (or the actual input voltage of the board) is around 2.9V, which produce the failure of the boot of the board.

The reason why this problem emerged recently is probably that the output voltage of the battery is 0.xV higher than now. Therefore, it’s just suitable for booting the board and support some low-power tasks. My test of the board is the “blink” program, blinking the built-in LED of the board. This LED is so low-power that cannot determine the voltage issue well. It’s not discovered until I use the voltmeter to measure the voltage.

Well, the best solution of this case is to add a voltage raising module that produce enough power. Or, this problem shouldn’t exist at the beginning. It’s probably better for me to have a brand-new set of components instead of using what I have. It’s necessary to investigate the parameter of the board I am going to buy, but it’s also important to do this so on the board I have now. 



# Apr 4th, 2019-Reverse Connection of Terminal Due to the Design of port

A problem occur when I was trying to connect the battery to the DC-DC component. The port (PH2.0) has positive terminal at left on the board, while the positive terminal is at right on the battery. In other words, if the battery is directly connected to the DC-DC module (the PH2.0 port is monodirectional, there is only onw way to plug in), the terminals of the power input would reverse.

[image]

That is exactly what I’ve done. What makes it worse is that the DC-DC module do not has a built-in reverse connection protection. Usually it could possibly cause the overheat of the chip and can highly possible ruins it. 

The best solution is to reverse the wires of the battery to fit the board, while introducing another problem of where to connect the line. The port on the board is the chip one, which has little room to remove the port or add additional wires. While the wire connected to the battery is too short to sustain enough length after welding multiple times.

Therefore, I weld the wire on the pins of a dual-in-line input components (beside the PH2.0 port). To do this so is easy to remove the wire in the future and reduce the risk of damaging the board by operating on the tiny PH2.0 port.

[image]



# Apr 5th, 2019-Mistakenly Reverse Connection of the Terminals of Components

This problem has mistakenly occurred many times by connect the power wire of components to the power source reversely. The result is usually overheat of the chip.

Therefore, a protection module is in great need among the following methods:

## Single diode with cross-line

## Single diode built in the wire

## Diode bridge

## MOS



# Apr 6th, 2019-A mile stone

THE DATA FROM GYROSCOPE IS FIIIIIIIIIIIINALLY EXTRACTED!!!!!



# Apr 20th, 2019-A problem of button state detecting

When I was trying to digital read the state of the button (on or off) in order to mark for the data collection, a problem occurs. When the button is switched off (confirm by a ohm meter that the resistance this time is infinity), the reading of the signal level is sometimes HIGH, which ought to always be LOW.

Vibration is eliminated as a causing since this only occur in pressing procedure (more specifically, it would only happens to a BUTTON instead of a SWITCH). What I am using is a switch. By testing, the input voltage is constant and could not be the reason. 

What’s more, this only occurs when the button is connected to S (signal) and +(positive terminal). The reading is constant at LOW when the switch is connected to S and -.

![](https://github.com/HaoYejia/Anti-Phubber/blob/master/Images/A%20problem%20of%20button%20state%20detecting1.png?raw=true)

As it shown, the left one always detected LOW at S as the switch is on or off. However, the right one sometimes occurs HIGH when the switch is switched off.

The solution (by the help of my dad) is following:

![](https://github.com/HaoYejia/Anti-Phubber/blob/master/Images/A%20problem%20of%20button%20state%20detecting2.png?raw=true)

The reason that this problem occurs is that the voltage level of the pin is a little bit high to trigger the HIGH signal (by measuring, the voltage vibrates between 300mV and 900mV, not quite low enough to stay at LOW constantly). By connecting like this, the illusory-high-voltage error can be solved.

In this case, the signal detected is always HIGH when the switch is off. The resistance this time used for letting the signal detectable and protect the circuit is called pull-up resister, while this procedure is called pull-up. 

Then, the signal detected is always LOW when the switch is on. By previous tests, this time the signal is constant at LOW. Therefore, the problem is avoid as it doesn’t even meet the conditions (connect S and + by switch) that problem occurs.