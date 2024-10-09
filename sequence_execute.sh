set -euo pipefail

for i in `seq $1`; do
  echo "check samples/in${i}.txt"
  ./execute.sh samples/in${i}.txt sample/out.txt sample/debug.txt
  diff sample/out.txt samples/out${i}.txt
done
