set -euo pipefail

make
for i in `seq $1`; do
  echo "check samples/in${i}.txt"
  cat samples/in${i}.txt | ./main.o \
    > sample/out.txt \
    2> sample/debug.txt
  diff sample/out.txt samples/out${i}.txt
done

echo "sequence execute succeeded"
