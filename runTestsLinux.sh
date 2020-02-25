mkdir -p Build &&
cd Build &&
cmake .. -DOPENZIA_COVERAGE=TRUE -DOPENZIA_TESTS=TRUE -DOPENZIA_WERROR=TRUE &&
cmake --build . &&
./openZiaTests &&
cd .. &&
gcovr --exclude Tests