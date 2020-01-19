#!/bin/bash

lcov --capture --directory . --output-file coverage.info
lcov --remove coverage.info '/usr/*' --output-file coverage.info
lcov --list coverage.info
bash <(curl -s https://codecov.io/bash) -f coverage.info -t 2b661e82-2ce9-44b3-93c0-7246b15b8921 || echo "Codecov did not collect coverage reports"