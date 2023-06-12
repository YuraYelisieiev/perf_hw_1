## Strace

strace -c ./perf_hw_1

```bash
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 88.24    2,713142           3   2603376           write
  8.61    0,254367          36      7238      1209 read
  2.01    0,056183           9      6513           poll
  0.51    0,015178          26       585           close
  0.45    0,012736           2      9748           rt_sigaction
  0.09    0,002513         222        15           munmap
  0.07    0,001913           4       571        27 openat
  0.06    0,001787           3       549        14 stat
  0.06    0,001855           1      1212           fcntl
  0.03    0,000962           0      1080           fstat
  0.03    0,000831           0      1055           lseek
  0.03    0,000801         160         5         2 connect
  0,01    0,000280          70         4           getdents64
  0,00    0,000110           1        63           mmap
  ...
------ ----------- ----------- --------- --------- ----------------
100.00    3,072817               2538810      1242 total
```


The system call "write" is clearly dominating in terms of time consumption. This suggests that the writing process is not optimized to its best potential.

## Netstat

```bash
(Not all processes could be identified, non-owned process info
 will not be shown, you would have to be root to see it all.)
tcp        0      0 yuriiyelisieiev:61001   128.195.10.252:https   ESTABLISHED yuriiyelisieiev    94144      6174/./perf_hw_1   
tcp        0      0 localhost:45555         localhost:55055        ESTABLISHED yuriiyelisieiev    94128      6174/./perf_hw_1   
tcp        0      0 localhost:55055         localhost:45555        ESTABLISHED yuriiyelisieiev    94127      6174/./perf_hw_1   
tcp        0      0 yuriiyelisieiev:61002   128.195.10.252:https   ESTABLISHED yuriiyelisieiev    94137      6174/./perf_hw_1   
(Not all processes could be identified, non-owned process info
 will not be shown, you would have to be root to see it all.)
tcp        0      0 yuriiyelisieiev:61001   128.195.10.252:https   ESTABLISHED yuriiyelisieiev    94144      6174/./perf_hw_1   
tcp        0      0 localhost:45555         localhost:55055        ESTABLISHED yuriiyelisieiev    94128      6174/./perf_hw_1   
tcp        0      0 localhost:55055         localhost:45555        ESTABLISHED yuriiyelisieiev    94127      6174/./perf_hw_1   
tcp        0      0 yuriiyelisieiev:61002   128.195.10.252:https   ESTABLISHED yuriiyelisieiev    94137      6174/./perf_hw_1   
(Not all processes could be identified, non-owned process info
 will not be shown, you would have to be root to see it all.)
tcp        0      0 yuriiyelisieiev:61001   128.195.10.252:https   ESTABLISHED yuriiyelisieiev    94144      6174/./perf_hw_1   
tcp        0      0 localhost:45555         localhost:55055        ESTABLISHED yuriiyelisieiev    94128      6174/./perf_hw_1   
tcp        0      0 localhost:55055         localhost:45555        ESTABLISHED yuriiyelisieiev    94127      6174/./perf_hw_1   
tcp        0      0 yuriiyelisieiev:61002   128.195.10.252:https   ESTABLISHED yuriiyelisieiev    94137      6174/./perf_hw_1   
(Not all processes could be identified, non-owned process info
 will not be shown, you would have to be root to see it all.)
tcp        0      0 yuriiyelisieiev:61001   128.195.10.252:https   ESTABLISHED yuriiyelisieiev 
```

We can see that our binary is using network to download the file.

## iostat

```bash
 tps    kB_read/s    kB_wrtn/s    kB_dscd/s    kB_read    kB_wrtn    kB_dscd Device
128,35         1,8M        12,8M         0,0k       3,5M      25,7M       0,0k sda

  tps    kB_read/s    kB_wrtn/s    kB_dscd/s    kB_read    kB_wrtn    kB_dscd Device
53,00       170,0k        12,5M         0,0k     340,0k      25,0M       0,0k sda

  tps    kB_read/s    kB_wrtn/s    kB_dscd/s    kB_read    kB_wrtn    kB_dscd Device
210,80         2,5M        11,0M         0,0k       5,0M      22,0M       0,0k sda

  tps    kB_read/s    kB_wrtn/s    kB_dscd/s    kB_read    kB_wrtn    kB_dscd Device
140,23         2,3M        9,8M         0,0k       4,6M      19,6M       0,0k sda

  tps    kB_read/s    kB_wrtn/s    kB_dscd/s    kB_read    kB_wrtn    kB_dscd Device
58,00       155,0k        8,5M         0,0k     310,0k      17,0M       0,0k sda

  tps    kB_read/s    kB_wrtn/s    kB_dscd/s    kB_read    kB_wrtn    kB_dscd Device
220,90         2,0M        7,0M         0,0k       4,0M      14,0M       0,0k sda
```

The output shows disk I/O statistics during the run of the program for the device "sda" with information about the number of transactions per second (tps), kilobytes read and written per second (kB_read/s and kB_wrtn/s), cumulative kilobytes read and written (kB_read and kB_wrtn), and discarded kilobytes (kB_dscd).