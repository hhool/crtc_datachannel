# `README.md`

## `Description`

- crtc_datachannel base webrtc 94

## `Tools`

- [`cmake-3.22.2`](https://cmake.org/files/v3.22/)
  - windows [cmake-3.22.2-windows-x86_64.zip](https://cmake.org/files/v3.22/cmake-3.22.2-windows-x86_64.zip)
  - mac [cmake-3.22.2-macos-universal.dmg](https://cmake.org/files/v3.22/cmake-3.22.2-macos-universal.dmg)
  - linux [cmake-3.22.2-linux-x86_64.tar.gz](https://cmake.org/files/v3.22/cmake-3.22.2-linux-x86_64.tar.gz)

## `Deploy`

- `windows`

```cmd
cmake -S . -B out\default -G "Visual Studio 15 2017" -A WIN32 
```

- `mac_x64`

```bash
export LD_LIBRARY_PATH=deps/crtc_dc/mac_x64_debug
cmake -S . -B out/default -G Xcode
cmake --build out/default --config Debug -v
./out/default/tests/Debug/crtc_dc_test
```
