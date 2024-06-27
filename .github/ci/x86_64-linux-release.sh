#!/bin/sh

# setup xmake for release or debug mode
xmake f -m release

# build and run helix-tests
xmake build tests
xmake run tests
