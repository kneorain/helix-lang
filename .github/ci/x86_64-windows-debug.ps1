# Load xmake environment
. $env:USERPROFILE\.xmake\profile.ps1

# setup xmake for release or debug mode
xmake f -m debug

# build and run helix-tests
xmake build tests
xmake run tests
