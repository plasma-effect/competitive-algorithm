set -euo pipefail
TIMEOUT=${1:-2}

make main.o user_case.o
./user_case.o > sample/in.txt
time cat sample/in.txt | ./main.o \
  > sample/out.txt \
  2> sample/debug.txt
