# !Phubber
The cervical diseases of the public have became more and more severe since the beginning of 21th century. !Phubber (anti-phubber, 'anti-' for 'reverse' and 'phubber' for the guys who stuck into the smartphone all the time) is invented to remedy this issue. The angle of the bending neck is measured by a gyroscope on a side of the user's head as a wearable. Then, a calculation would be done base on the length of time and the degree the head is lowered by a chip. If it gets over a given limit, a vibrating motor would be triggered to alarm the users to raise up the head instead of staring at the smartphone. 

Author: Hao Yejia 郝烨嘉 haoyejia@outlook.com


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

###Components list

- DFrobot Arduino Beetle (and its expansion board)
- 1027 Vibration motor
- Dfrobot BMI160 IMU module
- A microswitch
- A switch
- Pre-programmed UART screen (2.4’)

### Connection diagram



### Algorithm

The Algorithm is still unsure, but here’s some possible routes:

- To use the rate of angle directly from the gyro scope. To do this so, it’s required to accumulate the data as the gyroscope only output the rate of change of angle in each axis. However, the uncertainty of the final angle would boost greatly since it plays dozens of adding every half a minutes.
- A more accurate algorithm that improve the previous one is to change the way of Integral. The previous algorithm is actually the integral of function of angular acceleration to time by using the blocks-drawing method. Therefore, It can use a more accurate way to integral in order to get higher accuracy. However, the microcontroller might not have enough ability to do this integral.
- Another method is to detect the angle of gravitational acceleration as a vector to determine the rotational relationship between the initial head-straight frame and the final head-lowering frame, therefore determine the angle of lowering head. However, the algorithm involves difficult linear algebra, which requires a lot of time and help. 