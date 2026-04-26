Requirements to run the code: 
Visual studio 2026 with C++ installed
vcpkg with curl

For the curl library:

1. Install vcpkg
git clone https://github.com/Microsoft/vcpkg
cd vcpkg
bootstrap-vcpkg.bat

2. Integrate with Visual Studio
vcpkg integrate install

3. Install curl
vcpkg install curl:x64-windows

(or x86-windows if you’re using 32-bit)

4. Then in C++
#include <curl/curl.h>
