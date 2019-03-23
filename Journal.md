# Mar 10th, 2019-Voltage Fitness
It's REALLY necessary to check the input voltage of the components. To be honest, it's the most important step during the preperation. Though it's pretty easy to find the components that fits each other, but there's still ones that don't.

Tip 1: Confirm your voltage. Make sure that the battery voltage fits the components.

Tip 2: Adjust the voltage when unfitness do exist. For example, to change the battery or to change the output voltage of board. The Beetle used in this project has a output voltage level as same as the battery (it's really excited to find out that the voltage can be easily changed by changing a battery instead of other complicated methods lol). Or, to find other ways to increase or decrease the output voltage by additional components (resistance, arduino, micro potential transformer, etc...)

Methods to adjust the voltage:
- PWM
- Resistance
- Chip



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
- 

#### Beneath the board

- require lots more welds
- larger volume
- 

### To have additional wires

- wires may be blocked by RESET  port and the capacitance
- lots more welds



# Mar 23th-Common Ground problem

Common ground refers to that you have to connect the GND if there are multiple power sources for different components, especially when you are trying to let them communicate.

The sensor, especially the sensor for single chip, output and input signals with HIGH or LOW voltage. However,  the voltage level is relative to the level on GND. In other words, the GND must be connected in order to provide a common base line of the signal. 

It’s pretty similar with the fact that you cannot find out the voltage while you put one needle of multimeter on one circuit while putting the other needle on another. There is no potential difference between these points, therefore impossible to measure the voltage.