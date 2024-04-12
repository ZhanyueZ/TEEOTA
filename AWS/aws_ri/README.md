---
title:	STM32H573I-DK *aws_ri*
header-includes: <link rel="icon" type="image/x-icon" href="../../../_htmresc/favicon.png" />
---

This application example is a port of the [FreeRTOS STM32U5 IoT Reference Integration](https://www.freertos.org/STM32U5)
to the STM32H573 Discovery kit.

The application is composed of:

 - A command line interpreter, used for:
   - provisioning the device: Device cloud credentials (name, keys and certificate), endpoint name and root CA certificate, code signing key, and Wi-Fi network credentials;
   - monitoring the runtime resources consumption (RTOS tasks and dynamic memory).

 - An MQTT client, connecting to AWS IoT Core over TLS with mutual authentication based on X.509 certificates

 - AWS agents, supporting the following AWS IoT Core services:
   - Shadows
   - Device Defender
   - OTA update
   - Raw telemetry data reporting (network packets statistics)

# Keywords

* FreeRTOS
* AWS
* OTA
* Wi-Fi

# Directory contents

~~~
aws_ri
+-- .extSettings                              STM32CubeMX extended configuration file
+-- Inc
¦   +-- core_pkcs11_config.h                  Mapping of the PKI objects between the CLI and PKCS#11
¦   +-- kvstore_config_plat.h
¦   +-- main.h
¦   +-- mbedtls_config_ntz.h                  MbedTLS configuration, optimized for read-only footprint, and throughput
¦   +-- stm32h5xx_hal_conf.h
¦   +-- stm32h5xx_it.h
¦   +-- tls_transport_config.h                Mapping of the PKI objects between the MbedTLS port and PKCS#11
+-- README.md
+-- README.html
+-- STM32CubeIDE
¦   +-- Application
¦   ¦   +-- User
¦   ¦       +-- Core
¦   ¦       ¦   +-- syscalls.c
¦   ¦       ¦   +-- sysmem.c
¦   ¦       +-- Startup
¦   ¦           +-- startup_stm32h573iikxq.s
¦   +-- .cproject
¦   +-- .project

¦   +-- STM32H573I-DK_aws_ri.launch
¦   +-- STM32H573IIKXQ_FLASH.ld
+-- Src
¦   +-- app_main.c                            Application entry point
¦   +-- crypto
¦   ¦   +-- core_pkcs11_pal_littlefs.c        CorePKCS11 storage port to the littlefs filesystem
¦   ¦   +-- core_pkcs11_pal_utils.c
¦   ¦   +-- core_pkcs11_pal_utils.h
¦   ¦   +-- rng_alt_stm32.c                   Entropy generator mapped on the STM32 hardware RNG IP
¦   +-- fs                                    LittleFS filesystem platform port
¦   ¦   +-- lfs_config.h
¦   ¦   +-- lfs_port.h
¦   ¦   +-- lfs_port_ospi.c
¦   ¦   +-- lfs_port_prv.c
¦   ¦   +-- lfs_port_prv.h
¦   ¦   +-- ospi_nor_mx25lmxxx45g.c           Custom external flash driver
¦   ¦   +-- ospi_nor_mx25lmxxx45g.h
¦   +-- main.c                                Platform init
¦   +-- ota_pal                               OTA platform port to the STM32 bank swap mechanism
¦   ¦   +-- ota_firmware_version.c
¦   ¦   +-- ota_pal.h
¦   ¦   +-- ota_pal_stm32_ntz.c
¦   +-- stm32h5xx_hal_msp.c
¦   +-- stm32h5xx_it.c
¦   +-- system_stm32h5xx.c
+-- STM32H573I-DK_aws_ri.ioc                 STM32CubeMX project configuration file
~~~

Project-common files (common to all project variants and all targets):  
The '-' marks denote the sub-directories or files which are not used in the present project.

~~~
../Common/                                    Source files common to the ports of the FreeRTOS Reference Integration for
                                              STM32 (different targets, different connectivities, different boot and
                                              OTA firmware update mechanisms).
+-- app
¦   +-- auto_provisioning.c             -
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
¦   +-- PkiObjectPkcs11.c                  Port to PKCS#11
¦   +-- PkiObjectPsa.c                  -  Port PSA Crypto, PSA ITS and optionally PSA PS
¦   +-- PkiObject_prv.h
¦   +-- ReadMe.html
¦   +-- ReadMe.md
¦   +-- mbedtls_pk_pkcs11.c                MbedTLS integration of the PKCS#11 backend
¦   +-- mbedtls_pk_psa.c                -  MbedTLS integration of the PSA backend
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
¦   +-- kvstore_nv_littlefs.c              LittleFs backend
¦   +-- kvstore_nv_psa_its.c            -  PSA ITS backend
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
  - ST tools allowing programming and debugging (STM32CubeIDE),
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


### Other tools

- *python3*, to 
  - Use the provisioning helper scripts  
    Must be seconded by the modules listed in *\<env_dir\>tools/requirements.txt*, to be installed by  
     `$ python3 -m pip install -r <env_dir>/tools/requirements.txt`.
- *openssl*, to
  - Generate the code signing material required for launching OTA firmware update
- (optional) *bash*, *awk*, to
  - Run the example scripts (for OTA, and easy copy/paste of command lines) embedded in the present
    readme.

## Target preparation

By default there is no specific target preparation for this application.

If you have enabled TrustZone on your target (for instance by installing the Secure Manager), you must refer to
the documentation of your TrustZone application example to perform a full chip regression before programming
the present application example.

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
 1. Load the binary into the target and launch the debugger (right-click on the project in the STM32CubeIDE
    Project Explorer pane, and select **Debug As/STM32 C/C++ Application**), or drag-and-drop the *STM32CubeIDE/Debug/<app_name>.bin*
    file to the USB mass storage mounted on the Windows virtual drive named *DIS_H573II*

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

 1. Set your desired thing name (that is the MQTT device identifier)
     
     ```
> conf set thing_name my_thing_name
thing_name="my_thing_name"
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

 1. Generate an ECDSA key pair

    The resulting public key will be printed to the console.
    
    ```
    > pki generate key
    SUCCESS: Key pair generated and stored in
    Private Key Label: tls_key_priv
    Public Key Label: tls_key_pub
    -----BEGIN PUBLIC KEY-----
    XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX=
    -----END PUBLIC KEY-----
    ```

 1. Generate a self-signed certificate from your key pair and thing name
     
     ```
> pki generate cert
-----BEGIN CERTIFICATE-----
XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
(...)
XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX==
-----END CERTIFICATE-----
    ```
    
    Copy/paste and save the resulting certificate to a new file (e.g. *device_cert_filename.pem*).

## Registration of the device with AWS IoT Core

 1. Create the *thing*
     
     ```bash
aws iot create-thing \
      --thing-name my_thing_name
     ```

 1. Register the certificate

     Follow the instructions at the AWS IoT Core Developer Guide to
    [register a client certificate](https://docs.aws.amazon.com/iot/latest/developerguide/manual-cert-registration.html#manual-cert-registration-noca-cli).
    ```bash
aws iot register-certificate-without-ca \
      --status ACTIVE \
      --certificate-pem file://device_cert_filename.pem
    ```
    
    Note down the certificate ARN. It is needed in the next steps for attaching a policy to it, and for attaching it to
    your *thing*. It is referred to as *\<cert_arn\>* below.

 1.  Attach the certificate to the *thing*
     
     ```bash
aws iot attach-thing-principal \
      --principal <cert_arn> \
      --thing-name my_thing_name
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

> Alternatively to the manual device provisioning steps detailed in the two previous sections, it is possible to call
> the following script after having disconnected your terminal emulator from the serial interface:
> ```bash
> $ python3 ./tools/provision.py -i
> ```
> Note: In the present application example, the Wi-Fi SSID and credentials do not have to be set.
> See the [script documentation](../../STM32CubeProjectsList.html#provisioning-script) section in the ProjectList
> document for details.

Now that the device is registered and granted with AWS IoT Core permissions, it is allowed to connect to the IoT Core endpoint.

## Observation of MQTT messages on the AWS IoT Core Console

 1. If not already done, connect the device Ethernet port to your local network

 1. Reset the device

     ```
     > reset
     Resetting device.
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
  This forms an application-level file integrity and authentication check.

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

2. Create a service role which grants permission for OTA service to access the firmware image:  
[https://docs.aws.amazon.com/freertos/latest/userguide/create-service-role.html](https://docs.aws.amazon.com/freertos/latest/userguide/create-service-role.html)

3. Create an OTA update policy:  
[https://docs.aws.amazon.com/freertos/latest/userguide/create-ota-user-policy.html](https://docs.aws.amazon.com/freertos/latest/userguide/create-ota-user-policy.html)

4. Add a policy for AWS IoT to access the code signing profile:  
[https://docs.aws.amazon.com/freertos/latest/userguide/code-sign-policy.html](https://docs.aws.amazon.com/freertos/latest/userguide/code-sign-policy.html)

### Create a code signed firmware update job

1. Bump up the version of the new firmware image of the application to be updated.
   a. Open the file *\<project\>/Src/ota_pal/ota_firmware_version.c* and increment for instance the *APP_VERSION_MINOR* definition.
   a. Re-build the application.

   [Warning]{.mark}: If the image self-test procedure embedded in the application does not detect a higher version number after installation,
   the self-test procedure fails, the update is reverted, and the OTA job is reported as rejected.

1. Upload the new image file to the S3 bucket created in the previous section.
   
   The application image file generated by the post-build command is created as *\<project\>/STM32CubeIDE/Debug/STM32H573I-DK_aws_ri.bin*.

   In the following commands, *\<image_binary_path\>* is *\<project\>/STM32CubeIDE/Debug/STM32H573I-DK_aws_ri.bin*, and
   *\<image_binary_name\>* is *STM32H573I-DK_aws_ri.bin*.

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
   
   The image to update must be specified in the *files[].fileName* field of the *ota-update-job-config.json* file:
   *"STM32H573I-DK_aws.bin"*, for the OTA Agent to identify the image properly. Otherwise no image is downloaded.
   
   More precisely, it must match the name used in *otaPal_CreateFileForRx()*, in the OTA Platform Abstraction Layer provided by
   the user application.
       
   The *files[].fileLocation.s3Location.key* field should then be set to *STM32H573I-DK_aws_ri.bin*.

   ```json
   {
     "otaUpdateId": "<ota_update_unique_identifier>",
     "targets": [
         "arn:aws:iot:<region>:<account_id>:thing/<thing_name>"
     ],
     "targetSelection": "SNAPSHOT",
     "files": [{
         "fileName": "STM32H573I-DK_aws.bin",
         "fileVersion": "1",
         "fileLocation": {
             "s3Location": {
                 "bucket": "<s3_bucket_for_image>",
                 "key": "<image_binary_name>",
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
   fileName="STM32H573I-DK_aws.bin"
   otaBucketName="<s3_bucket_for_image>"
   fileKey="<image_binary_name>"
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
<INF>    88331 [MQTTAgent ] Received OTA job message, size: 614. (ota_update_task.c:921)
<INF>    88331 [OTAAgent  ] Extracted parameter: [key: value]=[execution.jobId: AFR_OTA-H5DK_2023-08-23_0952] (ota.c:1678)
<INF>    88333 [OTAAgent  ] Extracted parameter: [key: value]=[execution.jobDocument.afr_ota.streamname: AFR_OTA-456f10ca-4c96-4bd2-855a-f4bb3ddd9b8c] (ota.c:1678)
<INF>    88333 [OTAAgent  ] Extracted parameter: [key: value]=[execution.jobDocument.afr_ota.protocols: ["MQTT"]] (ota.c:1678)
<INF>    88334 [OTAAgent  ] Extracted parameter: [key: value]=[filepath: STM32H573I-DK_aws.bin] (ota.c:1678)
<INF>    88334 [OTAAgent  ] Extracted parameter: [key: value]=[filesize: 492536] (ota.c:1719)
<INF>    88334 [OTAAgent  ] Extracted parameter: [key: value]=[fileid: 0] (ota.c:1719)
<INF>    88334 [OTAAgent  ] Extracted parameter: [key: value]=[certfile: ota_signer_pub] (ota.c:1678)
<INF>    88335 [OTAAgent  ] Extracted parameter [ sig-sha256-ecdsa: MEUCIQCaJlhKjSymG3hDadcZCc5QcPAE... ] (ota.c:1609)
<INF>    88335 [OTAAgent  ] Job document was accepted. Attempting to begin the update. (ota.c:2258)
   ```

1. Once the full image has been downloaded, the OTA library verifies the image signature and requests the image installation by PSA Firmware Update.
   ```
<INF>    27899 [OTAAgent  ] Received final block of the update. (ota.c:2718)
<INF>    28293 [OTAAgent  ] Received entire update and validated the signature. (ota.c:2742)
...
<SYS>        0 [None      ] Reset Source: 0x14000000 : SFTRSTF: software system reset with pin reset. (app_main.c:266)
<INF>        0 [None      ] HW Init Complete (app_main.c:285)
   ```

1. New image boots up and performs a self-test, here it checks the version is higher than previous. If so it sets the new image as valid.
   ```
<INF>    15487 [OTAAgent] In self test mode. (ota.c:2102)
<INF>    15487 [OTAAgent] New image has a higher version number than the current image: New image version=1.1.0, Previous image version=1.0.0 (ota.c:1932)
   ```

1. Checking the job status, should show the job as succeeded:
   ```bash
   aws iot describe-job-execution --job-id=<Job ID created above> \
         --thing-name=<thing name>
   ```

# Design notes

## FreeRTOS heap configuration
The *heap_4* implementation of FreeRTOS dynamic memory allocator is selected and uses a single memory region.

Its size is specified by the FreeRTOS `configTOTAL_HEAP_SIZE` definition.

## MbedTLS configuration
The MbedTLS configuration file *\<project\>/Inc/mbedtls_config_ntz.h* is tuned to reduce the read-only memory footprint.
 - With exceptions:
 
   - For runtime performance reasons: MBEDTLS_AES_ROM_TABLES, MBEDTLS_ECP_NIST_OPTIM
   - For debuggability: MBEDTLS_ERROR_C

In particular the support of RSA-based cipher suites is disabled. Therefore, the root CA certificate provisioned for
authenticating the endpoint must be based on an ECDSA key. That is the *Amazon Root CA 3* CA which is specified in the
provisioning section above.

In case there is a TLS error during the handshake, ensure that the proper certificate was provisionned. Its common name
is displayed on the console as follows:
```
<INF>      916 [MQTTAgent ] CA Certificate:  CN=Amazon Root CA 3, SN:0x066C9FD5749736663F3B0B9AD9E89E7603F24A (mbedtls_transport.c:335)
```

## Firmware update implemented by flash bank swapping

- The application reads the bank size from a region of the STM32H5 system flash which does not support cached accesses.
  The application init therefore configures the MPU so that this region is mapped as non-cacheable device memory.

- The flash programmation operations are placed in critical sections so that the programming task is not descheduled
  by the RTOS before the operation is completed (task switches while programming have been reported to cause unstabilities).

- The swap of the flash banks is selected by the *SWAP_BANK* option byte.  
  After OTA update has run an odd number of times, the MCU boots from the second bank.
  
---
[Troubleshooting]{.mark}
In that state, if application download and debug fails to start and the STM32CubeIDE debugger fails to attach
to MCU after programming, 

   - The option byte can be reset manually to allow flash and debug again: `$ STM32CubeProgrammer.exe mode=UR -ob SWAP_BANK=0`
   - The external flash must also be erased so that the file system does not keep track of an erroneous OTA state.  
     The external loader to be selected in STM32CubeProgrammer is *MX25LM51245G_STM32H573I-DK-RevB*.  
     Please refer to the STM32CubeProgrammer documentation for usage details.

### Provisions for running FreeRTOS qualification tests

- The *FreeRTOS-Libraries-Integration-Tests* module is included in the project, together with the needed application
and configurarion files.
- The test task is built and replaces the reference integration applicative tasks only if one test case is selected
in the configuration file *<env_dir>/Projects/Common/config/test_execution_config.h*.
- The qualification testing status is documented in the release notes.

## IDE project settings

- Build settings
  - Only the *Debug* target is provided
  - Enabled .bin in MCU Post build outputs: `-O binary`
  - Selected debug-compatible compiler optimization: `-Og -g3`
  - Selected target-specific compiler optimization: *assume loading data from flash is slower than fetching
    instructions* `-mslow-flash-data`
  - No float support in printf
  
- Debug launcher settings

  - Enable FreeRTOS awareness for Cortex-M33 NTZ (the FreeRTOS kernel fully runs in the non-secure partition)

