set -euo pipefail
TIMEOUT=${1:-2}

make main.o user_case.o -j4
timeout 3s ./user_case.o > sample/in.txt
time timeout 3s ./main.o < sample/in.txt \
  > sample/out.txt \
  2> sample/debug.txt
