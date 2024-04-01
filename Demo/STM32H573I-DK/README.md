###How to use (workflow tested for Windows only):
1. clone repository following [Mongoose guide](https://mongoose.ws/tutorials/stm32/all-make-baremetal-builtin/);
2. enable Internet sharing in Control Panel for your current connection;
3. compile dashboard Web UI;
4. compile STM32H573I-DK OTA capabilities;
5. run the following command: .\esputil -p /COM## monitor (replace ## with your own portal which you may find in device manager);
6. once the connection is ready, open the provided temporary IP in your browser.
