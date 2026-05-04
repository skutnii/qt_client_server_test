Requires CMake and Qt 6.

Debug build:
```shell
cmake -B _build/Debug -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=ON .
cmake --build _build/Debug
```
from the project root.

This produces two executables _build/Debug/test_server and _build/Debug/test_client.
For a release build just change Debug -> Release above.
