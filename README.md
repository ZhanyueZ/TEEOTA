

# TEEOTA
a TEE based project to achieve something. For collaboration on our Capstone project.


## <b> How to use the AWS Cloud OTA ? </b> 
 - Make sure you already have the Secure Manager.
 - This part of code is mainly written by ST. We tested its feasibilities. We added more support for Arm PSA apis.
 - Follow the readme file under the AWS folder. You need create a AWS account.
 - We focused on ri_tz project.

## <b> How to run the http server ?</b>

 - Generate an binary file of our examples using the makefile. You can access this example in the demo folder.
 - Program the generated .elf file into board's flash. You  can use STM32 CubeProgrammer.
 - Change you local network's setting to make it accessible to other devices connected to the PC.
 - Find the virtual port that the board connected to.
 - Run `esputil -p /your port` to monitor the serial log
 - Once the setting is good, you can find a random http server is ready
 - Go to that server address, and you'll see the frontend management portal.
 - Customize the frontend by modifying the css and js file and using the makefile to `make`

## <b>How to use the chess game and costomize it?</b>

In order to make the program work, you must do the following:

 - WARNING: Before opening the project with any toolchain be sure your folder installation path is not too in-depth since the toolchain may report errors after building.

 - Open your preferred toolchain

 - MyApplication_1 is the folder that contains all the frontend designs and algorithm implementation.

 - Run the application in your IDE.
   
 - *Two demonstrative algorithm cores & debuggers, as well as their corresponding STM32H5 onbaord implemenmtations utilizing touchscreen (with TouchGFX API) for Connect-Four / Gomoku board game are provided*
 - You can customize the UI using TouchGFX designer. You can customize you algorithms in Screen1View.cpp and Screen2View.cpp 

### <b> How to scale the chess game to a upgradable one </b>
 - Change the linker script in the demo folder so that the flash address should be correctly handled with no overlap
 - Change the linker script of the chess game to make sure the generated chess game binary didn't overwrite the internal http server code. 
 - In the frontend server, you can upgrade the chess game binary

