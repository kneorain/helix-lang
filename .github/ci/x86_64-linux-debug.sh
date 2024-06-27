#!/bin/sh

# Load xmake environment
source ~/.xmake/profile

# setup xmake for release or debug mode
xmake f -m debug

# build and run helix-tests
xmake build tests
xmake run tests
