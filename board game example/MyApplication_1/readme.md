# STM32H573I-DK TBS

The default IDE is set to STM32CubeIDE, to change IDE open the STM32H573I-DK.ioc with CubeMX and select from the supported IDEs (EWARM, MDK-ARM and STM32CubeIDE). Supports flashing of the STM32H573I-DK board directly from TouchGFX Designer using GCC and STM32CubeProgrammer. Flashing the board requires STM32CubeProgrammer which can be downloaded from the ST webpage.

This TBS is configured for 240 x 240 pixels 16 bpp screen resolution.

Performance testing can be done using the GPIO pins designated with the following signals in Arduino connector on the underside of the board:

- VSYNC_FREQ  - Pin D4 (PG4)
- RENDER_TIME - Pin D7 (PG5)
- FRAME_RATE  - Pin D8 (PG8)
- MCU_ACTIVE  - Pin D2 (PG15)

The USER button (B1, which is connected to PC13 on the MCU) is implemented in the TBS and is mapped to the ASCII value '5'.
To use it in TouchGFX Designer choose hardware button 53.