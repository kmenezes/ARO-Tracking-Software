# ARO-Tracking-Software
GPS Satellite tracking software using the Algonquin Radio Observatory (ARO) developed in C.

![ARO](http://kmenezes.github.io/ARO-Tracking-Software/docs/ARO.JPG)

## Getting Started
* You must have a C compiler IDE on your machine/computer.

## Prerequisites
This software package takes 3 inputs:
1. The **North American Aerospace Defense Command [Two-Line-Element](https://www.celestrak.com/columns/v04n03/)** of the 32 GPS-operational satellites from [Celestrak](https://www.celestrak.com/NORAD/elements/). The format is below:

![](http://kmenezes.github.io/ARO-Tracking-Software/docs/TLE.jpg)

2. **Tracking Schedule.** The start/stop date and time as well as the time step in a text file. As seen below:

Tracking start date/time: 2017-05-03-14:00:00
Tracking stop date/time: 2017-05-03-14:30:00
Output time step (sec): 60.00

3. **Station File**. File that contains parameters of your station. Here since we are using the ARO they are as follows:
  * Latitude 45 degrees 57' 19.812" N
  * Longitude 281 degrees 55' 37.055" E
  * Elevation 260.42m
  * Diameter = 46m solid and mesh parts (36.6m solid part)
  * Focal ratio = 0.4(0.5 solid)
  * Focal length = 18.3 m prime
  * Surface accuracy 0.32 cm (solid), 0.64 cm (mesh)
  * Beamwidth = 3 arcmin (10 GHz)
  * AZ speed max = 3 deg/min
  * EL speed max = 3 deg/min,
  * EL_min limit > 9 degrees, EL_max < 89 degrees

For specific format see actual file [here](https://github.com/kmenezes/ARO-Tracking-Software/blob/master/station_file.dat).

## Run-Time Environment
1. Imports TLE
  * User can view or edit parameters of the TLE or continue
2. Imports Station File
  * User can view or edit the parameters of the Station or continue
3. Imports Tracking Schedule
4. Displays the satellites within view for the Tracking Schedule
  * Also saved to a file [AOSLOS.txt](https://github.com/kmenezes/ARO-Tracking-Software/blob/master/AOSLOS.txt)
5. User selects the satellite they want to track
6. Displays the Time, Azimuth, Elevation, Azimuth rate-of-change, Elevation rate-of-change, Range rate-of-change, Range, Doppler, and Signal Level.
7. The software spits out files:
  * Tracking Data file which contains the correct formatting for the ARO dish.
  * Ephemeris file '.e' for debugging in [STK](www.agi.com)

## Post Run-Time
The TrackingData.txt file is uploaded to the ARO dish via ftp site.

## Accuracies
|            | Time                | Azimuth degrees  | Elevation degrees | Az-Rate  | El-Rate  | Range (km)  | Doppler Shift (kHz) | Signal Level (dBm) |
|------------|---------------------|----------|-----------|----------|----------|-------------|---------------------|--------------------|
| Software   | 2017-05-03 14:29    | 305.477  | 25.375    | 0.001022 | 0.006557 | 23486.77744 | 3.227356            | -139.215           |
| [STK](www.agi.com)       | 2017-05-03 14:28:59 | 305.4773 | 25.37563  | 0.001022 | 0.006557 | 23486.70615 | 3.227376            | -140.804369        |
| Difference | 1 second            | 0.000262 | 0.000631  | 0        | 0        | -0.071284   | 2E-05               | -1.589369          |
![Proof of Accuracies](http://kmenezes.github.io/ARO-Tracking-Software/docs/spacehardware.PNG)

### Outcomes
The outcomes of developing this software was:
* Demonstrating an example of a complete software project using C.
* Improve my programming, debugging skills using C.
* Apply theoretical knowledge of orbital mechanics, RF signal transmission to a practical problem.
* Introduce the large dish antenna measurement technique by using a celestial source.

## Authors
- [Keith Menezes](http://keithmenezes.ca)
- James Brook

### Development Documentation
Version 5 - Check the updates April 2nd 2017
[ENG-4350-P5-JK.pdf](http://kmenezes.github.io/ARO-Tracking-Software/docs/ENG-4350-P5-JK.pdf)

Version 4 - Check the updates March 26th 2017
[ENG-4350-P4-JK.pdf](http://kmenezes.github.io/ARO-Tracking-Software/docs/ENG-4350-P4-JK.pdf)

Version 3 - Check the updates below March 19th, 2017
[ENG-4350-P3-James-Keith.pdf](http://kmenezes.github.io/ARO-Tracking-Software/docs/ENG-4350-P3-James-Keith.pdf)

### License
