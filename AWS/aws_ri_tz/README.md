---
title:	STM32H573I-DK *aws_ri_tz*
header-includes: <link rel="icon" type="image/x-icon" href="../../../_htmresc/favicon.png" />
---

This application example is a port of the [FreeRTOS STM32U5 IoT Reference Integration](https://www.freertos.org/STM32U5)
to the STM32H573 Discovery kit, using ST *Secure Manager* as the TrustZone *Secure Processing Environment* and secure bootloader, 
with its pre-provisioned device unique identity.

In this project, the *Secure Manager* is configured to run the user application in the *Non-Secure Processing
Environment*,
leveraging the ARM PSA APIs (PSA Crypto, PSA Internal Storage, PSA Firmware Update) implemented in the Secure Processing Environment
for TLS authentication, secure firmware update, and secure storage of user data.

> The *Secure Manager* encrypted image (package reference: [X-CUBE-SEC-M-H5]{.mark}) must be downloaded from the
> [STM32TRUSTEE-SM](https://www.st.com/en/embedded-software/stm32trustee-sm.html) web page and installed on the target 
> prior to programming this application example.
>
> Please refer to the [Secure Manager](https://wiki.st.com/stm32mcu/wiki/Security:Secure_Manager) documentation and
[How to start with Secure Manager on SM32H5](https://wiki.st.com/stm32mcu/wiki/Category:How_to_start_with_Secure_Manager_on_STM32H5) for more information.
>
> [Important]{.mark} **The *Secure Manager* binary and its future updates is subject to export control and shall be handled
> accordingly by the user, including in case it is transferred to the device by an over-the-air firmware update
> procedure.**


The application is composed of:

 - A command line interpreter, used for:
   - provisioning the device: Endpoint name and root CA certificate, code signing key, and Wi-Fi network credentials;
   - monitoring the runtime resources consumption (RTOS tasks and dynamic memory).

 - An MQTT client, connecting to AWS IoT Core over TLS with mutual authentication based on a unique X.509 certificate
   provisioned at ST manufacturing.

 - AWS agents, supporting the following AWS IoT Core services:
   - Shadows
   - Device Defender
   - OTA update
   - Raw telemetry data reporting (consisting of network packets statistics)

# Keywords

* FreeRTOS
* AWS
* OTA
* Wi-Fi
* ARM TrustZone for Cortex-M
* ARM Platform Security Architecture (PSA)
* Secure Manager
* Device Unique Authentication

# Directory contents

Files specific to the present project:

~~~
aws_ri_tz
+-- .extSettings                              STM32CubeMX extended configuration file
+-- Binary
¦   +-- appli_enc_sign.bin                    Signed binary image ready to be installed by the STuROT firmware update
+-- Images
¦   +-- SM_Code_Image.xml
¦   +-- SM_Code_Image_bin.xml
+-- Inc
¦   +-- kvstore_config_plat.h
¦   +-- main.h
¦   +-- mbedtls_config_psa.h                  MbedTLS configuration, optimized for read-only footprint
¦   +-- stm32h5xx_hal_conf.h
¦   +-- stm32h5xx_it.h
¦   +-- tls_transport_config.h                Mapping of the PKI objects between the MbedTLS port and PSA
+-- README.md
+-- README.html
+-- STM32CubeIDE
¦   +-- Application
¦   ¦   +-- Startup
¦   ¦   ¦   +-- startup_stm32h573iikxq.s
¦   ¦   +-- User
¦   ¦       +-- syscalls.c
¦   ¦       +-- sysmem.c
¦   +-- .cproject
¦   +-- .project
¦   +-- STM32H573I-DK_aws_ri_tz.launch
¦   +-- STM32H573IIKXQ_FLASH.ld               Linker file, patched by the project pre-build command to match the STuROT memory mapping
¦   +-- postbuild.sh                          STM32CubeIDE project post-build command, which generates a signed binary image file to be installed by the STuROT firmware update
+-- Src
¦   +-- app_main.c                            Application entry point
¦   +-- main.c
¦   +-- mbedtls_entropy_alt_psa.c             MbedTLS entropy generator relying on the PSA random generation API
¦   +-- stm32h5xx_hal_msp.c
¦   +-- stm32h5xx_it.c
¦   +-- system_stm32h5xx.c
¦   +-- tfm_ns_interface_freertos.c           PSA API dispatch interface, implementing thread protection and optional API logging
+-- download.bat                              Application installation through the STuROT secure update mechanism
+-- download.sh
+-- env.sh
+-- prebuild.sh                               STM32CubeIDE project pre-build command, which updates the linker file according to the STuROT memory mapping
+-- STM32H573I-DK_aws_ri_tz.ioc               STM32CubeMX project configuration file
~~~

Project-common files (common to all project variants and all targets):  
The '-' marks denote the sub-directories or files which are not used in the present project.

~~~
../Common/                                    Source files common to the ports of the FreeRTOS Reference Integration for
                                              STM32 (different targets, different connectivities, different boot and
                                              OTA firmware update mechanisms).
+-- app
¦   +-- auto_provisioning.c                   Reconstruct the device user certificate and store it in a PSA ITS object
¦   +-- defender                              AWS Device Defender task
¦   ¦   +-- defender_task.c
¦   ¦   +-- metrics_collector.h
¦   ¦   +-- metrics_collector_lwip.c
¦   +-- emu_sensor_publish.c                  Emulated sensor telemetry task, reporting network packet statistics
¦   +-- env_sensor_publish.c            -
¦   +-- motion_sensors_publish.c        -
¦   +-- mqtt                                  AWS IoT Core MQTT task
¦   ¦   +-- freertos_command_pool.c
¦   ¦   +-- freertos_command_pool.h
¦   ¦   +-- mqtt_agent_task.c
¦   ¦   +-- mqtt_agent_task.h
¦   ¦   +-- subscription_manager.h
¦   +-- ota                                   AWS IoT Core OTA Firmware Update task
¦   ¦   +-- ota_update_task.c
¦   +-- pub_sub_test_task.c
¦   +-- qualification_app_main.c
¦   +-- shadow_device_task.c                  AWS IoT Core Shadow task
+-- boards
¦   +-- stm32u5_iot_board.c             -
+-- cli                                       Embedded command line interface supporting terminal logging, and network
                                              and PKI configuration.
¦   +-- ReadMe.html
¦   +-- ReadMe.md
¦   +-- cli.h
¦   +-- cli_conf.c
¦   +-- cli_main.c
¦   +-- cli_pki.c
¦   +-- cli_prv.h
¦   +-- cli_rngtest.c
¦   +-- cli_uart_drv.c
¦   +-- cli_utils.c
¦   +-- logging.c
¦   +-- logging.h
¦   +-- logging_levels.h
+-- config                                    Middleware configuration files
¦   +-- FreeRTOSConfig.h
¦   +-- b_u585i_iot02a_conf.h           -
¦   +-- core_http_config.h
¦   +-- core_mqtt_agent_config.h
¦   +-- core_mqtt_config.h
¦   +-- defender_config.h
¦   +-- hw_defs.h
¦   +-- kvstore_config.h
¦   +-- lwipopts.h
¦   +-- mqtt_metrics.h
¦   +-- ota_config.h
¦   +-- shadow_config.h
¦   +-- test_execution_config.h
¦   +-- test_param_config.h
¦   +-- tls_transport_lwip.h
¦   +-- unity_config.h
+-- crypto                                   Cryptography application module supporting the embedded CLI PKI commands
                                             and the device authentication by MbedTLS.
¦   +-- PkiObject.c
¦   +-- PkiObjectPkcs11.c               -  Port to PKCS#11
¦   +-- PkiObjectPsa.c                     Port PSA Crypto, PSA ITS and optionally PSA PS
¦   +-- PkiObject_prv.h
¦   +-- ReadMe.html
¦   +-- ReadMe.md
¦   +-- mbedtls_pk_pkcs11.c             -  MbedTLS integration of the PKCS#11 backend
¦   +-- mbedtls_pk_psa.c                   MbedTLS integration of the PSA backend
¦   +-- psa_util.c
¦   +-- psa_util.h
+-- include
¦   +-- PkiObject.h
¦   +-- cmsis_os.h                      -
¦   +-- mbedtls_error_utils.h
¦   +-- mbedtls_freertos_port.h
¦   +-- mbedtls_transport.h
¦   +-- sys_evt.h
+-- kvstore                                 Permanent storage application module for the network configuration
¦   +-- ReadMe.html
¦   +-- ReadMe.md
¦   +-- kvstore.c
¦   +-- kvstore.h
¦   +-- kvstore_cache.c                    Store cache in RAM
¦   +-- kvstore_nv_littlefs.c           -  LittleFs backend
¦   +-- kvstore_nv_psa_its.c               PSA ITS backend
¦   +-- kvstore_prv.h
+-- net                                     TCP/IP socket porting application module
¦   +-- eth                             -   LwIP/Ethernet backend
¦   ¦   +-- eth_dataplane.c            -
¦   ¦   +-- eth_lwip.c                 -
¦   ¦   +-- eth_lwip.h                 -
¦   ¦   +-- eth_netconn.c              -
¦   ¦   +-- eth_netconn.h              -
¦   ¦   +-- eth_prv.h                  -
¦   +-- lwip_port                           LwIP port
¦   ¦   +-- include
¦   ¦   ¦   +-- arch
¦   ¦   ¦   ¦   +-- cc.h
¦   ¦   ¦   ¦   +-- perf.h
¦   ¦   ¦   ¦   +-- sys_arch.h
¦   ¦   ¦   +-- lwipopts_freertos.h
¦   ¦   +-- src
¦   ¦       +-- sys_arch.c
¦   +-- mbedtls_transport.c                 MbedTLS port to the net and crypto port
¦   +-- mxchip                              LwIP/Mx-Chip EMW3080 Wi-Fi backend over SPI
¦       +-- mx_dataplane.c               
¦       +-- mx_ipc.c                     
¦       +-- mx_ipc.h                     
¦       +-- mx_lwip.c                    
¦       +-- mx_lwip.h                    
¦       +-- mx_netconn.c                 
¦       +-- mx_netconn.h                 
¦       +-- mx_prv.h                     
+-- sys
    +-- interrupt_handlers.c
    +-- mbedtls_freertos_port.c
    +-- newlibc_stubs.c
~~~

# Hardware and Software environment
## Hardware and test environment

This example runs on STM32H573I-DK devices.

![](../../../Documentation/STM32H573I-DK_EMW3080.png)

  : Figure: Target connectivity overview

Equipment to be connected to the device. Refer to picture above to locate the connectors.

1. Wi-Fi module  
  For the user application to connect to Internet.  
  Plug the provided EMW3080 daugtherboard in the STMOD+ connector of the discovery kit.
 
1. USB-C STLINK port  
  For supplying power to the target, programming and debugging over USB, and as a serial terminal console
  and command-line interface.  
  Connect to a USB port of the user computer installed with:
  - ST tools allowing programming and debugging (STM32CubeIDE, STM32CubeProgrammer),
  - A terminal emulator.
  
## Cloud account and resources

The user must have registered an AWS account with the appropriate rights.

Follow your organization's policy regarding configuring your access to AWS with temporary or long term IAM credentials.
If not such policy exists, refer to the instructions on the [Set up your AWS account](https://docs.aws.amazon.com/iot/latest/developerguide/setting-up.html) for details on your options.

## Development environment

The tool versions compatible with this expansion package are documented in the [Release Notes](../../../Release_Notes.html).

The open-source tools should preferably be installed by a package manager (such as [scoop](https://scoop.sh) for Windows) to easily manage
the installed versions and benefit from homogeneous execution paths. It is advised to double-check your *PATH* environment
variable and ensure that:

  - Different versions of the tools are not active at the same time;
  - C:\WINDOWS\system32 is placed before /usr/bin when running .bat files

### AWS tools

- The AWS CLI tool is used for most interactions between the user and AWS:

  1. Download AWS CLI for your platform from the [official website](https://aws.amazon.com/cli) or using your preferred package manager.

  1. Refer to the following guides for configuring AWS CLI depending on how your AWS account is set up:
      - [Configuring the AWS CLI to use AWS IAM Identity Center](https://docs.aws.amazon.com/cli/latest/userguide/cli-configure-sso.html)
      - [Quick configuration with aws configure](https://docs.aws.amazon.com/cli/latest/userguide/cli-configure-quickstart.html)

- AWS CLI must have access to Internet in order to be used for the provisioning, create OTA Update jobs, etc..  
  Depending on your environment, HTTP proxy settings may have to be defined.

### ST platform tools

- The following tools must be installed for building the application and programming the target.

  - [STM32CubeIDE](https://www.st.com/content/st_com/en/stm32cubeide.html)
  - [STM32CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html), which must be installed in the default location (`C:\Program Files\STMicroelectronics\STM32Cube\STM32CubeProgrammer`).

### Other tools

- *python3*, to 
  - Install or remove the Secure Manager from the target
  - Build the TrustZone-enabled applications (used by the pre-build and post-build scripts)
  - Use the provisioning helper scripts  
    Must be seconded by the modules listed in *\<env_dir\>tools/requirements.txt*, to be installed by  
     `$ python3 -m pip install -r <env_dir>/tools/requirements.txt`.
- *openssl*, to
  - Generate the code signing material required for launching OTA firmware update
- (optional) *bash*, *awk*, to
  - Run the example scripts (for device enrollment, OTA, and easy copy/paste of command lines) embedded in the present
    readme.

## Target preparation

- The Secure Manager must first be programmed on the target
  1. Connect the target STLINK USB port to your computer
  1. Download the X-CUBE-SEC-M-H5 package from [STM32TRUSTEE-SM](https://www.st.com/en/embedded-software/stm32trustee-sm.html)
     and unzip its contents over your local environment
  1. Call `<env_dir>/Projects/STM32H573I-DK/ROT_Provisioning/SM/provisioning_auto.bat` by double-clicking on the file in
     Windows Explorer.  
     On Linux, use `<env_dir>/Projects/STM32H573I-DK/ROT_Provisioning/SM/provisioning.sh`.
  
  Note: After usage, before installing a non-TrustZone application on the same target, you will have to
  Uninstall the Secure Manager by performing a full script regression:  
  Call `<env_dir>/Projects/STM32H573I-DK/ROT_Provisioning/DA/regression.bat` by double-clicking on the file in Windows
  Explorer.  
  On Linux, use `<env_dir>/Projects/STM32H573I-DK/ROT_Provisioning/DA/regression.sh`.
  
  See the Secure Manager documentation for more information.

# How to use it?

The required steps to run the application example follow. Here is the outline:

 - Firmware build and installation
 - Runtime device provisioning
 - Registration of the device with AWS IoT Core
 - Observation of MQTT messages on the AWS IoT Core Console
 - (optional) OTA Firmware Update

## Firmware build and installation
 1. When installing your development environment on MS Windows, substitute the expansion package installation path
    to a dedicated Windows drive letter. This avoids possible issues with long paths.

    For instance, create the `S:` virtual drive from the Windows command line:

    ```
    C:\Users\johndoe> subst S: C:\Users\johndoe\Downloads\STM32CubeExpansion_Cloud_AWS_H5_V<package_version>
    ```

 1. Open STM32CubeIDE. If prompted, create a fresh workspace for the version of the X-CUBE-AWS-H5 expansion package you
 installed (you may want to use `S:`, but the workspace location should not matter).
 1. Import the project from the `S:` subst drive in your STM32CubeIDE workspace (**File**/**Open Projects from Filesystem**/**Import source**/**Directory** menu)
 1. Build the project (right-click on the project in the STM32CubeIDE Project Explorer pane, and select **Build Project**)
 1. Connect the target STLINK USB port to your computer
 1. Load the binary into download slot of the target by clicking on the file `download.bat` in the IDE project explorer,
    or in Windows Explorer, or by launching `<project>/download.sh`.
 1. (optional) A debugger launch configuration is available (right-click on the project in the STM32CubeIDE 
    Project Explorer pane, and select **Debug As**/**Debug Configurations**/**STM32 C/C++
    Applications**/STM32H573I-DK_aws_eth_tz).

## Runtime device provisioning
 1. Open the target board's serial port with your favorite serial terminal emulator. Some common options are TeraTerm, putty, screen, minicom, and picocom.
     
     Use the settings below.
   
    Serial settings                  Terminal settings
    -----------------  --------  --  -------------------  ----------
    Baud rate          115200        New Line receive     Auto
    Data               8 bit         New line transmit    LF
    Parity             None
    Stop               1 bit
    Flow control       None

    : Table: Terminal settings

 1. Verify that the embedded CLI is functional by typing `help conf` in the terminal emulator. The following message should be displayed:

    ```
    > help conf
    conf:
        Get/ Set/ Commit runtime configuration values
        Usage:
        conf get
            Outputs the value of all runtime config options supported by the system.
    
        conf get <key>
            Outputs the current value of a given runtime config item.
    
        conf set <key> <value>
            Set the value of a given runtime config item. This change is staged
            in volatile memory until a commit operation occurs.
    
        conf commit
            Commit staged config changes to nonvolatile memory.
    ```

    The provisioning method detailed below relies on the device unique key and certificate which are provisionned
    by ST in the STM32H573 SoC at manufacturing time.

    [Variant]{.mark} In case the users prefer to stick to the same method as used in the Non-TrustZone application examples, they should:

      a. Define the USE_CUSTOM_TLS_KEY compilation switch in the STM32CubeIDE project (**Properties**/**C/C++ Build**/**Settings**/**Tools Settings**/**MCU GCC Compiler**/**Preprocessor**/**Define Symbols**)
      a. Follow the device runtime provisioning steps detailed in the [*aws_ri*](../aws_ri/Readme.html) readme file.
      
      The [*TLS with Device Unique Authentication* section](../../STM32CubeProjectsList.html#tls-dua) of the ProjectList document
      gives an overview of the possible device provisioning options.

    Otherwise, the thing name is automatically set to the value of the certificate subject *Common Name*.

    It can be checked by typing the following command in the terminal emulator:
    ```
    > conf get thing_name
    thing_name="stm32h5xx-user-xxxxxxxxxxxxxxxxxxxx"
    ```

    The device certificate may also be displayed:
    ```
    > pki export cert
    -----BEGIN CERTIFICATE-----
    xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    (...)
    xxxxxxxxxxxx
    -----END CERTIFICATE-----
    ```

 1. Set the AWS IoT Core MQTT endpoint for your AWS account and region:

    ```
    > conf set mqtt_endpoint xxxxxxxxxxxxxx-ats.iot.us-west-2.amazonaws.com
    mqtt_endpoint="xxxxxxxxxxxxxx-ats.iot.us-west-2.amazonaws.com"
    ```
    You can determine the endpoint for your AWS account
     - either with this AWS CLI command: `$ aws iot describe-endpoint --endpoint-type iot:Data-ATS`
    - or on the *Settings* page of the AWS IoT Core web console.

 1. Set the Wi-Fi SSID:
    ```
    > conf set wifi_ssid xxxxxxxxxxxxxxx
    wifi_ssid="xxxxxxxxxxxxxxx"
    ```
    Note: Your local Wi-Fi network must provide an open IPv4 access to Internet (no captive portal or proxy...).
 
 1. Set the Wi-Fi password:
     ```
    > conf set wifi_credential xxxxxxxxxxxxxxx
    wifi_credential="xxxxxxxxxxxxxxx"
    ```
 
 1. Commit the staged configuration changes to non-volatile memory.

    ```
    > conf commit
    Configuration saved to NVM.
    ```

 1. Import the certificate of the root CA of your endpoint

    Copy/paste the contents of the [Amazon Root CA 3 PEM file](https://www.amazontrust.com/repository/AmazonRootCA3.pem)
    on the terminal right after this command, and type *enter*:
    
    ```
    > pki import cert root_ca_cert
    -----BEGIN CERTIFICATE-----
    MIIBtjCCAVugAwIBAgITBmyf1XSXNmY/Owua2eiedgPySjAKBggqhkjOPQQDAjA5
    MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6b24g
    Um9vdCBDQSAzMB4XDTE1MDUyNjAwMDAwMFoXDTQwMDUyNjAwMDAwMFowOTELMAkG
    A1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJvb3Qg
    Q0EgMzBZMBMGByqGSM49AgEGCCqGSM49AwEHA0IABCmXp8ZBf8ANm+gBG1bG8lKl
    ui2yEujSLtf6ycXYqm0fc4E7O5hrOXwzpcVOho6AF2hiRVd9RFgdszflZwjrZt6j
    QjBAMA8GA1UdEwEB/wQFMAMBAf8wDgYDVR0PAQH/BAQDAgGGMB0GA1UdDgQWBBSr
    ttvXBp43rDCGB5Fwx5zEGbF4wDAKBggqhkjOPQQDAgNJADBGAiEA4IWSoxe3jfkr
    BqWTrBqYaGFy+uGh0PsceGCmQ5nFuMQCIQCcAu/xlJyzlvnrxir4tiz+OpAUFteM
    YyRIHN8wfdVoOw==
    -----END CERTIFICATE-----
    ```
    
    For verifying the import, type:
    
    ```
    > pki export cert root_ca_cert
    -----BEGIN CERTIFICATE-----
    MIIBtjCCAVugAwIBAgITBmyf1XSXNmY/Owua2eiedgPySjAKBggqhkjOPQQDAjA5
    MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6b24g
    Um9vdCBDQSAzMB4XDTE1MDUyNjAwMDAwMFoXDTQwMDUyNjAwMDAwMFowOTELMAkG
    A1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJvb3Qg
    Q0EgMzBZMBMGByqGSM49AgEGCCqGSM49AwEHA0IABCmXp8ZBf8ANm+gBG1bG8lKl
    ui2yEujSLtf6ycXYqm0fc4E7O5hrOXwzpcVOho6AF2hiRVd9RFgdszflZwjrZt6j
    QjBAMA8GA1UdEwEB/wQFMAMBAf8wDgYDVR0PAQH/BAQDAgGGMB0GA1UdDgQWBBSr
    ttvXBp43rDCGB5Fwx5zEGbF4wDAKBggqhkjOPQQDAgNJADBGAiEA4IWSoxe3jfkr
    BqWTrBqYaGFy+uGh0PsceGCmQ5nFuMQCIQCcAu/xlJyzlvnrxir4tiz+OpAUFteM
    YyRIHN8wfdVoOw==
    -----END CERTIFICATE-----
    ```

    Note:  Provisioning the *Amazon Root CA 3* (ECDSA-based) instead of the more usual *Amazon Root CA 1* (RSA-based) is mandatory.
    It allows to fully remove the RSA support from the TLS library and reduce the read-only memory footprint of the application.

> Alternatively to the manual device provisioning steps detailed in the present section, it is possible to call
> the following script after having disconnected your terminal emulator from the serial interface:
> ```bash
> $ python3 ./tools/provision.py --cert-issuer st
> ```
> See the [script documentation](../../STM32CubeProjectsList.html#provisioning-script) section in the ProjectList
> document for details.

## Registration of the device with AWS IoT Core

Despite the *register-certificate-without-ca* method used in [*aws_eth*](../aws_eth/Readme.html) application example
remains possible, one advantage of the STM32H573 device unique authentication is that the pre-provisioned device certificate
is signed by an ST root CA which can be registered at AWS IoT Core, so that the device certificate is validated
and automatically registered at first connection.

Follow the instructions at the AWS IoT Core Developer Guide to
[register a client certificate when the client connects to AWS IoT just-in-time registration (JITR)](https://docs.aws.amazon.com/iot/latest/developerguide/auto-register-device-cert.html):

 1. Register the ST Device Unique Authentication user root CA [certificate](../../../Utilities/Certificates/st_ca_01_dua_user_certificate.pem):

     ```bash
     aws iot register-ca-certificate --ca-certificate file://<env_dir>/Utilities/Certificates/st_ca_01_dua_user_certificate.pem \
           --certificate-mode SNI_ONLY \
           --set-as-active \
           --allow-auto-registration
     ```

     Note down the returned CA certificate ID. It is referred to as *\<ca_cert_id\>* below.

 1. Reset your device in order to force a new connection to AWS IoT Core
  
     By pushing the reset button, or by typing the following command in the terminal emulator:
     
     ```
> reset
Resetting device.
     ```
     
     At this stage, the device is able to connect over TLS, but the MQTT connection is rejected by the server because
     the certificate is not activated and the device is not registered yet.

 1. Retrieve the list of the certificates registered in just-in-time mode, which are in *PENDING_ACTIVATION* state
    
     ```bash
     aws iot list-certificates-by-ca --ca-certificate-id <ca_cert_id> \
           --query 'certificates[?status==`PENDING_ACTIVATION`].certificateId|join(`, `, @)'
     ```
    
     Note your device certificate ID. It is referred to as *\<cert_id\>* below.

 1. Retrieve the details of the device certificate

     - Get the certificate ARN. It is referred to as *\<cert_arn\>* below.
       ```bash
       aws iot describe-certificate --certificate-id <cert_id> \
             --query 'certificateDescription.certificateArn'
       ```
      
     - Get the certificate PEM payload and double-check that it corresponds to the one displayed by the embedded CLI in the previous steps.
       ```bash
       aws iot describe-certificate --certificate-id <cert_id> \
             --query 'certificateDescription.certificatePem'
       ```

 1. Activate the device certificate
    
     ```bash
     aws iot update-certificate --certificate-id <cert_id> \
           --new-status "ACTIVE"
     ```

 1. Create a policy if none exists

     ```bash
     aws iot create-policy \
           --policy-name="AllowAllDev" \
           --policy-document="{ \"Version\": \"2012-10-17\", \"Statement\": [{\"Effect\": \"Allow\", \"Action\": \"iot:*\", \"Resource\": \"*\"}]}"
     ```
     [Important]{.mark} This policy allows very broad access to AWS IoT MQTT APIs. Use a more restrictive policy for any production environments.

 1. Attach a security policy to the certificate

     ```bash
     aws iot attach-policy \
           --target <cert_arn> \
           --policy-name AllowAllDev
     ```

 1. Create the thing

     ```bash
     aws iot create-thing --thing-name <thing_name>
     ```
     [Important]{.mark} `<thing_name>` must be the exact name that the application example extracts from the device certificate.
     Any other value will be rejected by the server at MQTT connection time.

 1. Attach the certificate to the thing

     ```bash
     aws iot attach-thing-principal \
           --principal <cert_arn> \
           --thing-name <thing_name>
     ```

Now that the device is registered and granted with IoT Core permissions, it is allowed to connect to the IoT Core endpoint.

Those registration steps may be automated by an AWS Lambda rule triggered by the certificate registration event,
or by a local script, such as:

```bash {.numberLines}
#!/bin/bash
MY_POLICY="AllowAllDev"
CA_CERT_ID="xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" # DUA User root CA certificate ID

case "$1" in
  "provision")
    CERT_ID_LIST=$(aws iot list-certificates-by-ca --ca-certificate-id $CA_CERT_ID --query 'certificates[?status==`PENDING_ACTIVATION`].certificateId|join(`, `, @)' | tr -d ',"')
    for CERT_ID in $CERT_ID_LIST; do
      echo "Lookup $CERT_ID"
      CERT_ARN=$(aws iot describe-certificate --certificate-id $CERT_ID --query 'certificateDescription.certificateArn' | tr -d '"')
      CERT_PEM=$(aws iot describe-certificate --certificate-id $CERT_ID --query 'certificateDescription.certificatePem')
      THING_NAME=$(echo "${CERT_PEM//'\n'/$'\n'}" | tr -d '"' | openssl x509 -noout -subject -nameopt sep_multiline | awk -F= '/ *CN=/{ print $2 }')
      echo "Cert Arn: $CERT_ARN"
      echo "Thing name: $THING_NAME"
      aws iot update-certificate --certificate-id $CERT_ID --new-status "ACTIVE"
      aws iot attach-policy --policy-name "$MY_POLICY" --target "$CERT_ARN"
      aws iot create-thing --thing-name "$THING_NAME"
      aws iot attach-thing-principal --thing-name "$THING_NAME" --principal "$CERT_ARN"
    done
    ;;
  "clear")
      CERT_ID_LIST=$(aws iot list-certificates-by-ca --ca-certificate-id $CA_CERT_ID --query 'certificates[?status==`ACTIVE`].certificateId|join(`, `, @)' | tr -d ',"')
    for CERT_ID in $CERT_ID_LIST; do
      echo "Lookup $CERT_ID"
      CERT_ARN=$(aws iot describe-certificate --certificate-id $CERT_ID --query 'certificateDescription.certificateArn' | tr -d '"')
      CERT_PEM=$(aws iot describe-certificate --certificate-id $CERT_ID --query 'certificateDescription.certificatePem')
      THING_NAME=$(echo "${CERT_PEM//'\n'/$'\n'}" | tr -d '"' | openssl x509 -noout -subject -nameopt sep_multiline | awk -F= '/ *CN=/{ print $2 }')
      echo "Cert Arn: $CERT_ARN"
      echo "Thing name: $THING_NAME"
      aws iot detach-policy --policy-name "$MY_POLICY" --target "$CERT_ARN"
      aws iot update-certificate --certificate-id "$CERT_ID" --new-status "INACTIVE"
      aws iot detach-thing-principal --thing-name "$THING_NAME" --principal "$CERT_ARN"
      sleep 5 # Wait that the decommissioning is effective
      aws iot delete-thing --thing-name "$THING_NAME"
      aws iot delete-certificate --certificate-id "$CERT_ID"
    done
    ;;
  *)
    echo "Error: No valid command argument was specified: '$1'"
    echo "Syntax: $0 {provision|clear}"
    ;;
esac
```

## Observation of MQTT messages on the AWS IoT Core Console

1. Log in to [https://aws.amazon.com](https://aws.amazon.com) with your IAM User.
1. Navigate to the *Iot Core* service using the search box at the top of the page.
1. Select the AWS region where your endpoint is located using the select button at the top-right of the page.
1. Using the menu on the left side of the screen, select **Test**/**MQTT test client**
1. Set the topic filter to *#* and click the *Subscribe* button.

You will soon see telemetry data streaming from your device.

## OTA Firmware Update
Overview:

- The application example runs a FreeRTOS OTA agent as one of the RTOS tasks, which waits for OTA update jobs from the FreeRTOS OTA Service running in AWS.

- The update file is streamed over MQTT.

- After download, the application verifies its authenticity thanks to a code signing public key
  and to the signature embedded in the OTA update job document.
  This forms an application-level file integrity and authentication check, which is supplemented by the Secure Manager
  secure firmware update feature (which relies, by contrast, on the image header set at post-build time).

Before being able to create a FreeRTOS OTA Update job, you must create a code signing profile.

### Generate a code signing key

Setup and provision the code signing credentials so as to enable the FreeRTOS OTA Update Service to digitally sign the image file
and the device to verify the image file signature before installation.

1. In your working directory, use the following text to create a file named `cert_config.txt`. Replace *test_signer@amazon.com* with your email address:
   
   ```ini
   [ req ]
   prompt             = no
   distinguished_name = my_dn
   [ my_dn ]
   commonName = test_signer@amazon.com
   [ my_exts ]
   keyUsage         = digitalSignature
   extendedKeyUsage = codeSigning
   ```

1. Create an ECDSA code-signing private key:
   ```bash
   openssl genpkey -algorithm EC \
         -pkeyopt ec_paramgen_curve:P-256 \
         -pkeyopt ec_param_enc:named_curve \
         -outform PEM \
         -out ecdsasigner-priv-key.pem
   ```

1. Generate the corresponding public key from the private key:
   ```bash
   openssl ec -inform PEM \
         -in ecdsasigner-priv-key.pem \
         -pubout \
         -outform PEM \
         -out ecdsasigner-pub-key.pem
   ```

1. Create an ECDSA code-signing certificate to be uploaded to the AWS Certificate Manager service (ACM):
   ```bash
   openssl req -new -x509 \
         -config cert_config.txt \
         -extensions my_exts \
         -nodes \
         -days 365 \
         -key ecdsasigner-priv-key.pem \
         -out ecdsasigner.crt
   ```

1. Import the code-signing certificate and private key into ACM:
   ```bash
   aws acm import-certificate --certificate fileb://ecdsasigner.crt \
         --private-key fileb://ecdsasigner-priv-key.pem
   ```
   Note down the ARN of the code signing certificate. It will be referred to as *\<code_sign_cert_arn\>* when creating
   the code signing profile below.

1. If not already done, connect to the target device via a serial terminal.

   Copy/paste the contents of the *ecdsasigner-pub-key.pem* file on the terminal right after this command,
   and type *enter*:
   ```
   > pki import key ota_signer_pub
   -----BEGIN PUBLIC KEY-----
   xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
   xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
   -----END PUBLIC KEY-----
   ```

   Note: *ota_signer_pub* is the label used to refer to the code signing key during verification of the firmware update.

1. Create a signing profile in AWS to sign the firmware images.
   ```bash
   aws signer put-signing-profile --profile-name <your profile name> \
         --signing-material certificateArn=<code_sign_cert_arn> \
         --platform AmazonFreeRTOS-Default \
         --signing-parameters certname=ota_signer_pub
   ```
   
   
   Summary of the generated files:
   
   File name                     Contents
   ----------------              --------------------------------------
   ecdsasigner-priv-key.pem      Code signing private key
   ecdsasigner-pub-key.pem       Code signing public key
   cert_config.txt               Code signing certificate signature request parameters
   ecdsasigner.crt               Code signing certificate
   
   : Table: Code signing profile intermediate files

### Setup OTA S3 bucket, Service role and policies in AWS

1. Create an S3 bucket to store the new firmware image to be updated:  
[https://docs.aws.amazon.com/freertos/latest/userguide/dg-ota-bucket.html](https://docs.aws.amazon.com/freertos/latest/userguide/dg-ota-bucket.html)

   In the next steps, the name of this bucket is referred to as *<s3 bucket for image>*.

> [Important]{.mark} **In case of OTA update of the Secure Manager image**.  
> It is the user responsibility to satisty to the export control regulations.  
> Before uploading any Secure Manager image to AWS S3 or to any other entity, ensure that the files added to the bucket
> may not leak or bypass the export control.

2. Create a service role which grants permission for OTA service to access the firmware image:  
[https://docs.aws.amazon.com/freertos/latest/userguide/create-service-role.html](https://docs.aws.amazon.com/freertos/latest/userguide/create-service-role.html)

3. Create an OTA update policy:  
[https://docs.aws.amazon.com/freertos/latest/userguide/create-ota-user-policy.html](https://docs.aws.amazon.com/freertos/latest/userguide/create-ota-user-policy.html)

4. Add a policy for AWS IoT to access the code signing profile:  
[https://docs.aws.amazon.com/freertos/latest/userguide/code-sign-policy.html](https://docs.aws.amazon.com/freertos/latest/userguide/code-sign-policy.html)

### Create a code signed firmware update job

1. Bump up the version of the new firmware image of the application to be updated. 
   a. Open the file *\<project\>/Images/SM_Code_Image_bin.xml*
   a. Increment the *Version.Value* parameter:
      
      ```diff
           <Param>
             <Name>Version</Name>
      -      <Value>1.0.0</Value>
      +      <Value>1.1.0</Value>
             <Type>Data</Type>
             <Command>-v</Command>
             <Tooltip>Version of the data binary. Format is x.y.z</Tooltip>
      ```

   a. Re-build the application, so that the post-build script sets the new version in the image header.

   [Warning]{.mark}: If the image self-test procedure embedded in the application does not detect a higher version number after installation,
   the self-test procedure fails, the update is reverted, and the OTA job is reported as rejected.

1. Upload the new image file to the S3 bucket created in the previous section.
   
   The application image file generated by the post-build script is created as *\<project\>/Binaries/appli_enc_sign.bin*.

   In the following commands, *\<image binary path\>* is *\<project\>/Binaries/appli_enc_sign.bin*, and
   *\<image binary name\>* is *appli_enc_sign.bin*.

   ```bash
   aws s3 cp <image_binary_path> s3://<s3_bucket_for_image>/
   ```

1. Get the latest S3 file version of the binary image:
   ```bash
   aws s3api  list-object-versions --bucket <s3_bucket_for_image> \
         --prefix <image_binary_name> \
         --query 'Versions[?IsLatest==`true`]'
   ```

1. Create a new OTA Update job configuration json file (Example: *ota-update-job-config.json*) on your computer as below.
   
   Substitute the parameters with the output obtained from steps above.
        
   An OTA job may update either the non-secure image partition (which contains the user application), or the secure image
   partition (which contains the Secure Manager).
       
   The image to update must be specified in the *files[].fileName* field of the *ota-update-job-config.json* file:
   *"non_secure image"*, or *"secure image"* for the OTA Agent to identify the image properly. Otherwise no image is downloaded.
       
   The *files[].fileLocation.s3Location.key* field should then be set to *appli_enc_sign.bin* or *\<SecurityManager bin
   filename\>*, respectively.

   The example below specifies an OTA firmware update of the non-secure partition, within a TrustZone-enabled
   application:

   ```json
   {
     "otaUpdateId": "<ota_update_unique_identifier>",
     "targets": [
         "arn:aws:iot:<region>:<account_id>:thing/<thing_name>"
     ],
     "targetSelection": "SNAPSHOT",
     "files": [{
         "fileName": "non_secure image",
         "fileVersion": "1",
         "fileLocation": {
             "s3Location": {
                 "bucket": "<s3_bucket_for_image>",
                 "key": "appli_enc_sign.bin",
                 "version": "<latest_s3_file_version_of_binary_image>"
             }
         },
         "codeSigning": {
             "startSigningJobParameter": {
                 "signingProfileName": "<signing_profile_name>",
                 "destination": {
                     "s3Destination": {
                         "bucket": "<s3_bucket_for_image>"
                     }
                 }
             }
         }
     }],
     "roleArn": "arn:aws:iam::<account_id>:role/<OTA_service_role>"
   }
   ```

   [Important]{.mark} Please check the [X-CUBE-SEC-M-H5]{.mark} Release Notes for the availability of the *SecurityManager
   binary* file and the image dependency management.

1. Create a new OTA update job from the configuration file:
   ```bash
   aws iot create-ota-update --cli-input-json file://ota-update-job-config.json
   ```

   The command above must be launched from the folder containing the *ota-update-job-config.json* file.

   On success, the command returns the OTA Update identifier (referred to as *\<ota_update_identifier\>* in the next step) 
   and status of the job as *CREATE_PENDING*.

   At user convenience, and as an alternative to a local JSON file for creating an OTA update job with a unique update
   ID, a scripted command line may also be used, such as:
   
   ```bash {.numberLines}
   #!/bin/bash
   UPDATE_ID="H5DK_$(date +%F_%H%M)"
   TARGETS="arn:aws:iot:<region>:<account_id>:thing/<thing_name>"
   ROLE_ARN="arn:aws:iam::<account_id>:role/<OTA_service_role>"
   fileName="non_secure image"
   otaBucketName="<s3_bucket_for_image>"
   fileKey="appli_enc_sign.bin"
   fileVersion="<latest_s3_file_version_of_binary_image>"
   otaCodeSigningProfile="<signing_profile_name>"
   
   FILES="fileName=$fileName,\
          fileLocation={s3Location={bucket=$otaBucketName,key=$fileKey,version=$fileVersion}},\
          codeSigning={startSigningJobParameter={signingProfileName=\
            $otaCodeSigningProfile,\
            destination={s3Destination={bucket=$otaBucketName}}}}"
   
   aws iot create-ota-update --ota-update-id "$UPDATE_ID" \
         --targets "$TARGETS" \
         --target-selection "SNAPSHOT" \
         --files "$FILES" \
         --role-arn "$ROLE_ARN"
   ```

1. To get the corresponding job ID, execute the following command and look for *awsIotJobId* field in json document returned.
   ```bash
   aws iot get-ota-update --ota-update-id=<ota_update_identifier>
   ```
   Note down the job ID to check the status of the job later.

### Monitoring and Verification of firmware update

1. Once the OTA job is created, the job document is sent by AWS to the device, and your serial terminal emulator logs show
   that OTA job is accepted. The device subsequently starts downloading image.

   ```
<INF>   247960 [MQTTAgent ] Received OTA job message, size: 508. (ota_update_task.c:921)
<INF>   247961 [OTAAgent  ] Extracted parameter: [key: value]=[execution.jobId: AFR_OTA-H5DK_2023-08-03_1507] (ota.c:1678)
<INF>   247962 [OTAAgent  ] Extracted parameter: [key: value]=[execution.jobDocument.afr_ota.streamname: AFR_OTA-42402af7-43b0-4ab9-acd1-3de90c1f4fa1] (ota.c:1678)
<INF>   247962 [OTAAgent  ] Extracted parameter: [key: value]=[execution.jobDocument.afr_ota.protocols: ["MQTT"]] (ota.c:1678)
<INF>   247963 [OTAAgent  ] Extracted parameter: [key: value]=[filepath: non_secure image] (ota.c:1678)
<INF>   247963 [OTAAgent  ] Extracted parameter: [key: value]=[filesize: 398850] (ota.c:1719)
<INF>   247963 [OTAAgent  ] Extracted parameter: [key: value]=[fileid: 0] (ota.c:1719)
<INF>   247963 [OTAAgent  ] Extracted parameter: [key: value]=[certfile: ota_signer_pub] (ota.c:1678)
<INF>   247964 [OTAAgent  ] Extracted parameter [ sig-sha256-ecdsa: MEUCIQDj5LYF7goIjpeTIfLNEc0K6/+9... ] (ota.c:1609)
<INF>   247964 [OTAAgent  ] Job document was accepted. Attempting to begin the update. (ota.c:2258)
   ```

1. Once the full image has been downloaded, the OTA library verifies the image signature and requests the image installation by PSA Firmware Update.
   ```
<INF>   265821 [OTAAgent  ] Received final block of the update. (ota.c:2718)
<INF>   266349 [OTAAgent  ] Received entire update and validated the signature. (ota.c:2742)
   ```

1. New image boots up and performs a self-test, here it checks the version is higher than previous. If so it sets the new image as valid.
   ```
<INF>    10103 [OTAAgent  ] Beginning self-test. (ota.c:807)
<INF>    10104 [OTAAgent  ] Received OtaJobEventStartTest callback from OTA Agent. (ota_update_task.c:767)
<INF>    10363 [OTAAgent  ] PSA Image type 1 version validation succeeded, old version: 1.0.0 new version: 1.1.0 (ota_update_task.c:645)
   ```

1. Checking the job status, should show the job as succeeded:
   ```bash
   aws iot describe-job-execution --job-id=<Job ID created above> \
         --thing-name=<thing name>
   ```

# Design notes
## Shared resources between the non-secure partition and the secure partition
### Clocks
The clocks of the RNG IP are configured at application startup, so that the Secure Manager services may use the IP
without interfering with the settings of the non-secure user application.

### STLINK UART 
This UART is used concurrenlty

- by the embedded command line interface running in the non-secure partition
- by the Secure Manager logging utility running in the secure partition

The UART settings configured by the application are compatible with the usage by the secure partition.

## FreeRTOS heap configuration
The *heap_5* implementation of FreeRTOS dynamic memory allocator is selected to use non-contiguous memory regions in SRAM1 and SRAM3.

They are set in *app_main.c::prvInitializeHeap()*.

Note that the FreeRTOS `configTOTAL_HEAP_SIZE` definition specifies the overall size, while `SRAM3_NS_SIZE` specifies 
how much of the non-secure part of SRAM3 is to be used by the FreeRTOS heap.

## MbedTLS configuration
The MbedTLS configuration file *\<project\>/Inc/mbedtls_config_psa.h* is tuned to reduce the read-only memory footprint.

In particular the support of RSA-based cipher suites is disabled. Therefore, the root CA certificate provisioned for
authenticating the endpoint must be based on an ECDSA key. That is the *Amazon Root CA 3* CA which is specified in the
provisioning section above.

In case there is a TLS error during the handshake, ensure that the proper certificate was provisionned. Its common name
is displayed on the console as follows:
```
<INF>      916 [MQTTAgent ] CA Certificate:  CN=Amazon Root CA 3, SN:0x066C9FD5749736663F3B0B9AD9E89E7603F24A (mbedtls_transport.c:335)
```

## IDE project settings

- Included links to useful files in the Project Explorer pane
  - *download.bat*, for programming the target after build (only on MS Windows)
  - *prebuild.log*, *postbuild.log*, *download.log*, for quicker access and script troubleshooting

- Build settings
  - Only the *Debug* target is provided
  - Added Secure Manager integration pre-build and post-build commands
  - Enabled .bin in MCU Post build outputs: `-O binary`
  - Selected debug-compatible compiler optimization: `-Og -g3`
  - Selected target-specific compiler optimization: *assume loading data from flash is slower than fetching
    instructions* `-mslow-flash-data`
  - No float support in printf
  
- Debug launcher settings
  - No download and image verification.  
    It is handled by the download script.
  - Connect without reset  
    The debugger is not allowed to attach right after target reset, when the MCU is running in the secure partition
    in TZ-CLOSE mode. So the debugger must be attached at non-secure runtime.  
    In order to debug the application startup, the user must first start a debug session, then reset the board
    manually by pushing the reset button. The CPU then breaks on the application entry point, and the non-secure code
    can be debugged normally.  
    Note that it is not possible to step into the secure code: The debugger will immediately loose the connection to the MCU.
  - Enable FreeRTOS awareness for Cortex-M33 NTZ (the FreeRTOS kernel fully runs in the non-secure partition)
  - The following script is added to the **Startup** tab/**Run Commands** text area, in order to allow the IDE to directly
    program the user application in the non-secure partition.  
    Note however that this programming method bypasses the update of the image header. Since the latter contains the image
    version, this method is not compatible with OTA Update use cases. It is therefore not recommended, and not
    enabled by default.
    
    ```
    set breakpoint always-inserted on
    tbreak Reset_Handler
    monitor reset
    set breakpoint always-inserted off
    si
    ```    
