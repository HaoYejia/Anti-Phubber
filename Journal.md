# Preparation

## Gyroscope

- MPU6050
- BMI160

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