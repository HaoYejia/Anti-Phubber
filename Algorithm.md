# Algorithm

The Algorithm is still unsure, but here’s some possible routes:

- To use the rate of angle directly from the gyro scope. To do this so, it’s required to accumulate the data as the gyroscope only output the rate of change of angle in each axis. However, the uncertainty of the final angle would boost greatly since it plays dozens of adding every half a minutes.
- A more accurate algorithm that improve the previous one is to change the way of Integral. The previous algorithm is actually the integral of function of angular acceleration to time by using the blocks-drawing method. Therefore, It can use a more accurate way to integral in order to get higher accuracy. However, the microcontroller might not have enough ability to do this integral.
- Another method is to detect the angle of gravitational acceleration as a vector to determine the rotational relationship between the initial head-straight frame and the final head-lowering frame, therefore determine the angle of lowering head. However, the algorithm involves difficult linear algebra, which requires a lot of time and help. 

## What data I can get

### Direct one

- The linear acceleration on each axis
- The change in each angle on each axis

### Implicit one

Notice the implicit one usually is hard to extract and required a lot of efforts as the only material I’ve got is the data manual. For further information, check the data manual of BMI160.

## Goal of this algorithm

Minimum goal (the goal of producing a prototype): Correctly calculate the angle of lowering the head and ignore the problem of errors or shifts (such as zero shift). Also, the algorithm should be **universal** as the location of wearing often changes a lot. In other words, I should figure out a way to **make sure this device can work smoothly with different wearing location.** 

