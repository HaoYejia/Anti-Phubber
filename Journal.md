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

