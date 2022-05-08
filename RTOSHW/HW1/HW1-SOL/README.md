N46005027 MATTEO RUGGIERO

Per il testing si consiglia di far partire i task nell'ordine replica - plant - controller
E di eseguire reference, diag e diagWCET a piacimento durante l'esecuzione

Non ho settato l'affinity via codice quindi è consigliato eseguire con taskset:

```console
mruggi@mruggi:~$ sudo taskset -c 0 ./replica
mruggi@mruggi:~$ sudo taskset -c 0 ./plant
mruggi@mruggi:~$ sudo taskset -c 0 ./controller
mruggi@mruggi:~$ sudo taskset -c 0 ./reference 90 
mruggi@mruggi:~$ sudo taskset -c 0 ./diag
mruggi@mruggi:~$ sudo taskset -c 0 ./diagWCET
```

Per la parte opzionale del calcolo dei WCET ho preferito memorizzare sempre quello correntemente calcolato perchè altrimenti i primi sono sempre i massimi (Ad esempio il primo WCET dell'acquire_filter che per partire attende la nascita del plant sarà sempre nell'ordine dei secondi o comunque pari a WCET del thread + attesa che si esegua il plant)