# !Phubber
!Phubber is a wearable device that help reduce the phubbing, as well as the spreading of cervical diseases. 

The cervical diseases of the public have became more and more severe since the beginning of 21th century. !Phubber (anti-phubber, 'anti-' for 'reverse' and 'phubber' for the people who are always staring at phone and snubbing the others) is invented to remedy this issue. The angle of the bending neck is measured by a gyroscope on a side of the user's head as a wearable device. Then, a calculation would be done base on the length of time and the degree the head is lowered by a micro controller. If it gets over a given limit (lowering their head greatly for a long time), a vibrating motor would be triggered to alarm the users to raise up the head instead of staring at the smartphone. 

Author: Hao Yejia 郝烨嘉 haoyejia@outlook.com



Current progress:

- [x] Choosing and finding the components
- [x] Connecting the wires and test each components separately
- [x] Get the data from Gyroscope and display it on PC
- [x] Figure out the algorithm
- [x] Finish the prototype and run the alpha test
- [ ] Miniaturization, to become a qualified wearable device


## File reference

**\Codes**	Mainly the codes of the project, including the test codes and products

**\Data**	For storing the data, including the data directly from gyroscope for further analyses

**\Diagrams**	The illustration of logic flow of the anti-phubber

**\Examples**	The example codes collected, including the gyroscope and other similar projects

\Images	Store the images on Github so that there’s link that can be inserted in Markdown files (you can just ignore this folder)

**\Information Collection**	The collected information, including the data sheets, tutorials, use guide, etc.

\Lists	Shopping lists as back-up storage. (you can also ignore that, as all the components are written in README)

**\Tools**	The develop tools, including the libraries, driver, develop software, etc.

**\Journal.md**	The diary for this project. You can see my mistakes or the difficulties I’ve met. 



In this branch, the final codes is in **\Codes\antiPhubber** . You can find the release version of this project (including the source code, the IDE, the libraries, and the compiled .HEX file ) in another branch (coming soon)


## Version 0.x

### Components list

- **DFrobot Arduino Beetle (and its expansion board)**

  The reason of choosing this is that this board is open-source and small enough for a wearable device. Since this board is based on Arduino, the programming and transplant would be easier than other micro controller. Further more, this component is cheap enough.

  Though the number of port is not much (3 Analog, 3 Digital, a pair of I2C and a pair of UART), it’s enough for this project.

- **1027 Vibration motor**

  The motor is small enough to be as a wearable components, while having strong vibration force that  can effectively alert the user

- **Dfrobot BMI160 IMU module**

  The advantage of this module is its built-in PH2.0 port that is useful for building and repairing. Also, this module is open-source and smaller than MPU series.

- **A microswitch**

- **A switch**


### Connection diagram

![](<https://github.com/HaoYejia/Anti-Phubber/blob/master/Images/Connection%20Diagram%20v0.1.jpg>)

