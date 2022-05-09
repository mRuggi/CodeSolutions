N46005027 MATTEO RUGGIERO

Per il testing si consiglia di far partire i task nell'ordine replica - plant - controller
E di eseguire reference, diag e diagWCET a piacimento durante l'esecuzione

Non ho settato l'affinity via codice quindi è consigliato:

```console
mruggi@mruggi:~$ sudo taskset -c 0 ./replica
mruggi@mruggi:~$ sudo taskset -c 0 ./plant
mruggi@mruggi:~$ sudo taskset -c 0 ./controller
mruggi@mruggi:~$ sudo taskset -c 0 ./reference 90 
mruggi@mruggi:~$ sudo taskset -c 0 ./diag
mruggi@mruggi:~$ sudo taskset -c 0 ./diagWCET
```
[Link della repository](https://github.com/mRuggi/CodeSolutions/tree/main/RTOSHW/HW1/HW1-SOL)