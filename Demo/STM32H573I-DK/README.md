### How to use (workflow tested for Windows only):
1. clone repository following [Mongoose guide](https://mongoose.ws/tutorials/stm32/all-make-baremetal-builtin/);
2. enable Internet sharing in Control Panel for your current connection;
3. compile dashboard Web UI;
4. compile STM32H573I-DK OTA capabilities;
5. write the generated .elf file to your board in STM32CubeProgrammer (you may perform a full chip erase first);
6. add the current folder containing esputil to PATH variables and run the following command to establish connection: (replace ## with your own portal which you can find in device manager);
```
 .\esputil -p /COM## monitor;
```
7. once the connection is ready, open the provided temporary IP in your browser.
