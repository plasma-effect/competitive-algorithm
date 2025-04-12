set -euo pipefail

make
time timeout 3s ./main.o < sample/in.txt \
  > sample/out.txt \
  2> sample/debug.txt
