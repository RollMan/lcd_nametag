## Development
### Run unittests that is platform-independent with clang on Windows without Docker
Do not use MinGW GCC because it does not support Asan which is required for sanitizers. https://stackoverflow.com/questions/55018627/cannot-find-lasan-using-address-sanitizer-in-mingw-in-windows-mingw/55019187#55019187

Instead, use clang:

```pwsh
$env:CC_LD="lld"
$env:CC="clang"
meson setup --wipe build/
meson test -C build/
```
