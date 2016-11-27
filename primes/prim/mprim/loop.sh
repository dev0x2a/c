echo > results1.txt
for n in $(seq 2 1000); do 
  ./a.out $n >> results1.txt
done  
  
