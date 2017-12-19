# bitonicv1

Each seq to sort have a length of n = 2k

Repartition of sorting note:

the max sequence is send to node: 2rank + 1
the min sequence is send to node: 2rank + 2

For the recursive level (that we will use to find the seq size)

r = 0 -> (1, 2)
r = 1 -> (3, 4)
r = 2 -> (5, 6)
r = 3 -> (7, 8)

level = rank + (rank % 2)
k = n / level

## Improvements that we can make

the master node is useless during the sorting

# bitonicv2

# Interesting links

Recv from unknown and resend:

https://stackoverflow.com/questions/4348900/mpi-recv-from-an-unknown-source
