#ifndef TLS_TRANSPORT_CONFIG
#define TLS_TRANSPORT_CONFIG

#include "tls_transport_lwip.h"

#define configTLS_MAX_LABEL_LEN    32UL
#define TLS_KEY_PRV_LABEL          "tls_key_priv"
#define TLS_KEY_PUB_LABEL          "tls_key_pub"
#define TLS_CERT_LABEL             "tls_cert"
#define TLS_ROOT_CA_CERT_LABEL     "root_ca_cert"
#define OTA_SIGNING_KEY_LABEL      "ota_signer_pub"

#ifdef USE_CUSTOM_TLS_KEY
#define PSA_TLS_PRV_KEY_ID         0x10000000UL
#define PSA_TLS_PUB_KEY_ID         0x10000001UL
#define PSA_TLS_CERT_ID            0x1000000000000101ULL
#else /* USE_CUSTOM_TLS_KEY */
#include "psa/crypto_values.h"
#define PSA_TLS_PRV_KEY_ID         PSA_KEY_ID_ST_DUA_USER
#define PSA_TLS_PUB_KEY_ID         PSA_KEY_ID_ST_DUA_USER
#define PSA_TLS_CERT_ID            0x1000000000000102ULL
#endif /* USE_CUSTOM_TLS_KEY */

#define OTA_SIGNING_KEY_ID         0x10000002UL
#define PSA_TLS_ROOT_CA_CERT_ID    0x1000000000000201ULL

/*
 * Define MBEDTLS_TRANSPORT_PKCS11 to enable certificate and key storage via the PKCS#11 API.
 */
/*#define MBEDTLS_TRANSPORT_PKCS11 */

#define TRANSPORT_USE_CTR_DRBG

/*
 * Define MBEDTLS_TRANSPORT_PSA to enable certificate and key storage via the ARM PSA API.
 */
#define MBEDTLS_TRANSPORT_PSA

/*
 * Define MBEDTLS_TRANSPORT_PSA_HAS_PS to enable the PSA Protected Storage API in addition to the PSA Internal Trusted Storage API.
 */

/* #define MBEDTLS_TRANSPORT_PSA_HAS_PS */

#endif /* TLS_TRANSPORT_CONFIG */
