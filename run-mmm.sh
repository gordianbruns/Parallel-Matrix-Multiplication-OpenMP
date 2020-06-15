# for each version


# serial, 1 thread, i = 100-1000, r = 10, p = hopper
echo hopper
echo serial
for items in 100 200 300 400 500 600 700 800 900 1000; do echo; echo $items; ./parallel-mmm -i $items -r 10 -p hopper -t 1; done

# strong scaling, 1-16 threads, i = 1,000, r = 10, p = hopper
echo
echo strong scaling
for threads in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16; do echo; echo $threads; ./parallel-mmm -i 1000 -r 10 -p hopper -t $threads; done

# weak scaling, 1-16 threads, i = thread * 100, r = 10, p = hopper
echo
echo weak scaling
for threads in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16; do echo; echo $threads; ./parallel-mmm -i `expr $threads \* 100` -r 10 -p hopper -t $threads; done

#serial, 1 thread, i = 100-1000, r = 10, p = pollock
echo
echo pollock
echo serial
for items in 100 200 300 400 500 600 700 800 900 1000; do echo; echo $items; ./parallel-mmm -i $items -r 10 -p pollock -t 1; done

# strong scaling, 1-16 threads, i = 1,000, r = 10, p = pollock
echo
echo strong scaling
for threads in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16; do echo; echo $threads; ./parallel-mmm -i 1000 -r 10 -p pollock -t $threads; done

# weak scaling, 1-16 threads, i = thread * 100, r = 10, p = pollock
echo
echo weak scaling
for threads in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16; do echo; echo $threads; ./parallel-mmm -i `expr $threads \* 100` -r 10 -p pollock -t $threads; done
