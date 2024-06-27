#!/bin/sh

# setup xmake for release or debug mode
xmake f -m debug

# build and run helix-tests
xmake build tests
xmake run tests
