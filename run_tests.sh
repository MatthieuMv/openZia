#!/bin/bash

mkdir -p Build &&
cd Build &&
cmake .. -DOPENZIA_TESTS=TRUE -DOPENZIA_COVERAGE=TRUE &&
cmake --build . &&
./openZiaTests