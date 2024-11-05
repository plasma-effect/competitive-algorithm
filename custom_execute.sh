set -euo pipefail
TIMEOUT=${1:-2}

make
python3 make_case.py > sample/in.txt
cat sample/in.txt | ./main.o \
  > sample/out.txt \
  2> sample/debug.txt
