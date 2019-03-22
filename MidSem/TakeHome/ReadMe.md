## Sensor

### How To Run:

1. Execute the sensor simulator python file, given in the LMS, then execute the server, then execute the client, each in three different terminals, like,<br />
python simulator.py <br />
gcc Server.c -o Server <br />
./Server <br />
gcc Client.c -o Client <br />
./Client <br />

2. The output csv file will be saved in the same folder as the client.c file. <br />

### Performance Data

Following is a section of the data from the csv file:
```
TimeStamp, Temperature, Humidity,  Gas1,  Gas2,  Gas3
1553252443, 76, 75, 1903, 1671, 2964
1553252445, 62, 85, 1856, 1667, 2553
1553252447, 101, 81, 1552, 1751, 2345
1553252449, 65, 74, 1531, 2170, 2713
1553252451, 101, 72, 1099, 1710, 2458
1553252453, 80, 88, 1529, 1942, 2670
1553252455, 64, 89, 1313, 1556, 2521
1553252457, 71, 52, 1199, 1513, 2754
1553252459, 83, 69, 1714, 2599, 2122
1553252461, 95, 74, 1550, 2593, 2346
1553252463, 89, 87, 1565, 1925, 2992
```
We can observe the time stamp difference of 2 seconds here.
