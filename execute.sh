set -euo pipefail
TIMEOUT=${1:-2}

make
cat sample/in.txt | timeout ${TIMEOUT} ./main.o > sample/out.txt
