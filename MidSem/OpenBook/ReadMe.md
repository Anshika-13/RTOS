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

Following is the data from the csv file:
```
TimeStamp, Temperature, Humidity,  Gas1,  Gas2,  Gas3
41227, 90, 83, 1087, 2209, 2465
41708, 84, 61, 1900, 2970, 2664
42098, 70, 60, 1014, 2280, 2600
42446, 68, 78, 1403, 2928, 2244
43072, 59, 51, 1278, 1965, 2602
43630, 70, 65, 1390, 2203, 2747
43944, 61, 84, 1071, 1642, 2969
44289, 61, 66, 1913, 2992, 2474
44699, 89, 76, 1807, 2833, 2542
45256, 66, 79, 1908, 1849, 2500
45609, 97, 54, 1782, 1631, 2038
45918, 64, 73, 1202, 2451, 2957
46275, 72, 75, 1644, 2260, 2142
46665, 57, 72, 1462, 2251, 2277
47149, 60, 69, 1813, 1854, 2724
47492, 70, 79, 1825, 2709, 2035
47830, 78, 51, 1500, 2370, 2246
48222, 99, 64, 1490, 2390, 2935
48823, 90, 81, 1586, 1872, 2046
```
