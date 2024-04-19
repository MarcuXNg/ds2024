```
➜  lab_3 git:(main) ✗ mpicc file_transfer.c -o file_transfer
➜  lab_3 git:(main) ✗ mpirun -np 2 ./file_transfer
[Client] File sent successfully
[Server] Data received and written to 'received_file.txt' successfully
```
