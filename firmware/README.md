# LCD Nametag
Schematic, PCB layout and AVR firmware to show JPG figures on an LCD driven by ST7789V. Useful to make digital sinage for nametags, etc.

## Compile Project to Generate the AVR binary in Intel HEX Format

```
docker build . -o build/
```

## Run Platform-Independent Unittests in the Build Environment

```
docker build . --target test
```
