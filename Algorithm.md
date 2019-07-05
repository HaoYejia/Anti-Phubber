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

---



## Difficulties when using a 2*2 matrix to represent the rotation on a plain

Assume a 
$$
\begin{bmatrix}
a & b \\
c & d
\end{bmatrix}



\begin{bmatrix}
x \\
y
\end{bmatrix}

= 

\begin{bmatrix}
m \\
n
\end{bmatrix}
$$
where 
$$
\begin{bmatrix}
a & b \\
c & d
\end{bmatrix}
$$
is the rotation matrix in 2 dimension (can be used to represent the rotate motion of a vector on a plain).


$$
\begin{bmatrix}
x \\
y
\end{bmatrix}
$$
and
$$
\begin{bmatrix}
m \\
n
\end{bmatrix}
$$
are the initial and final vectors of the linear transformation respectively.



### Experiment

Assume the transform is:
$$
\begin{bmatrix}
3 & 2 \\
-2 & 1
\end{bmatrix}


\begin{bmatrix}
5 \\
7
\end{bmatrix}
$$
By using Matlab, 

```matlab
>> trans = [3,2;-2,1]

trans =

     3     2
    -2     1

>> init = [5;7]

init =

     5
     7

>> trans*init

ans =

    29
    -3
```

The final vector, as it shown, is 
$$
\begin{bmatrix}
-29 \\
3
\end{bmatrix}
$$
However, when I try to **calculate the rotation matrix, Its turns out that this matrix is not unique**:

```matlab
>> final / init

ans =

         0    4.1429
         0   -0.4286

>> ans * init

ans =

   29.0000
   -3.0000

```

Notice the result of the calculation is 
$$
\begin{bmatrix}
0 & 4.1429 \\
0 & -0.4286
\end{bmatrix}
$$
clearly it’s different from the original rotation matrix, while out put the same result when I was trying to use this matrix to transform the initial vector. Therefore, it can be deduced that the rotation matrix calculated in this method is never unique.

### Deduction

The calculation of the transformation matrix can be represent as the following:
$$
\begin{bmatrix}
a & b \\
c & d
\end{bmatrix}



\begin{bmatrix}
5 \\
7
\end{bmatrix}

= 

\begin{bmatrix}
29 \\
-3
\end{bmatrix}
$$

$$
\begin{bmatrix}
5a+7b=29 \\
5c+7d=-3
\end{bmatrix}
$$

There’s four variables but only two equation, and the obviously that there’s **no unique solution**.

