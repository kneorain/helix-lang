# setup xmake for release or debug mode
xmake f -m {'debug' if "debug" in filename else 'release'}

# build and run helix-tests
xmake build tests
xmake run tests
