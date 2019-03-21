## Echo Engine

### How To Run:

1. Execute the server, then execute the client, like,<br />
gcc Server.c -o Server <br />
gcc ClientA.c -o ClientA <br />
./Server <br />
./ClientA <br />

2. To measure the performance data, edit the Client files and send a character 10 times to the server instead of asking the user for an input. Then, measure the time taken by the server to respond to each request and average it out. <br />
Then, execute the server, then execute one or more clients simultaneously, like, <br />
gcc Server.c -o Server <br />
gcc ClientA.c -o ClientA <br />
gcc ClientB.c -o ClientB <br />
./Server <br />
./ClientA & ./ClientB & <br />

### Performance Data

Following are the average values of time taken by server to respond over 10 requests:

Number of Clients | Client A (microseconds) | Client B (microseconds) | Client C (microseconds) | Client D (microseconds) | Client E (microseconds)
------------ | ------------- | ------------- | ------------- | ------------- | ------------- 
1 | 55 | . | . | . | . 
2 | 93 | 98 | . | . | . 
3 | 154 | 113 | 143 | . | . 
4 | 278 | 154 | 131 | 80 | . 
5 | 212 | 251 | 265 | 294 | 279

While these are the average values, I observed that some requests were served very fast (in around 50 to 60 us), and a few were serviced very slow (>270 us). I also observed that as the number of simultaneous clients increased, the average value also increased, from most requests being serviced in around 50-60us for one client, to around 200-280us for five clients.
