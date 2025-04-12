set -euo pipefail

make
for i in `seq $1`; do
  echo "check samples/in${i}.txt"
  timeout 3s ./main.o < samples/in${i}.txt \
    > sample/out.txt \
    2> sample/debug.txt
  diff sample/out.txt samples/out${i}.txt
done

echo "sequence execute succeeded"
