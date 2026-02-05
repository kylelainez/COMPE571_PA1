# only works when run from root dir
#!/usr/bin/env bash
set -e 

ROOT_DIR="$(pwd)" # TODO: Figure out how to avoid pwd and use the CMAKE var for source dir of CMakeLists.txt

cd "${ROOT_DIR}/build"

# Build 
cmake ..
make

# Find newest executable file
EXEC=$(find . -maxdepth 1 -type f -executable -printf "%T@ %p\n" \
        | sort -n | tail -1 | awk '{print $2}')

if [ -z "$EXEC" ]; then
    echo "No executable found"
    exit 1
fi

echo "Running: $EXEC"
"${EXEC}"
