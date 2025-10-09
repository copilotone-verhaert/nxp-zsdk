.. _nxp_mbedtls_psa_crypto_opaque:
.. zephyr:code-sample:: nxp_mbedtls_psa_crypto_opaque
   :name: mbedtls_psa_crypto_opaque
   :relevant-api: psa-crypto-apis

   psa-crypto-driver example for psa-api usage

NXP Mbedtls Psa Crypto Test Sample
##################################

Overview
********

This example showcase the use of the PSA Crypto API,
demonstrating how it integrates with secure storage to manage both volatile and persistent keys (PSA ITS).

Key storage location is controlled via the CONFIG_TEST_KEY_LOCATION macro:
- Location 0 is reserved for local (transparent) keys.
- Other locations are vendor-specific and may refer to hardware-backed secure keystores.

Supported locations:
- RT1180 ELE S40x HW secure keystore - 0x800002 (PSA_CRYPTO_ELE_S4XX_LOCATION), keys visible only to HSM

The source code for this sample application can be found at:
:zephyr_file:`samples/crypto/nxp_mbedtls_psa_crypto_opaque`.
This sample is available for platforms that support psa-crypto-driver.

Requirements
************

- Micro USB cable
- Supported platform
- Personal Computer

Building, Flashing and Running
******************************

.. zephyr-app-commands::
   :zephyr-app: samples/boards/mimxrt1180_evk/nxp_mbedtls_psa_crypto
   :board: mimxrt1180_evk
   :goals: build flash
   :compact:


Flashing
********

.. code-block:: console

#You can find "zephyr.bin" and "zephyr.elf" under the "build/zephyr/" path.
    $ cd build/zephyr
    $ loadbin C:xxx\build\zephyr.bin, <addr>

Sample Output
=============

.. code-block:: console

*** PSA Crypto example ***

Key location is opaque 800002


VOLATILE KEYS



ECC keys

224 bit ECC_KEY_PAIR(SECP_R1)
with sign / verify algo ECDSA(SHA224)
	: PASSED

	  521 bit ECC_KEY_PAIR(SECP_R1)
with sign / verify algo ECDSA(SHA512)
	: PASSED

	  256 bit ECC_KEY_PAIR(SECP_R1)
with sign / verify algo ECDSA(SHA256)
	: PASSED

	  256 bit ECC_KEY_PAIR(BRAINPOOL_R1)
with sign / verify algo ECDSA(SHA256)
	: PASSED

	  384 bit ECC_KEY_PAIR(BRAINPOOL_R1)
with sign /
	verify algo ECDSA(SHA384)
	: PASSED

	  AES keys

	  128 bit AES key with encrypt
	  /
	  decrypt algo ECB_NO_PADDING : PASSED

					192 bit AES key with encrypt
					/
					decrypt algo CBC_NO_PADDING : PASSED

								      256 bit AES key with encrypt
								      /
								      decrypt algo CTR
	: PASSED

	  128 bit AES key with encrypt
	  /
	  decrypt algo CCM : PASSED

			     256 bit AES key with encrypt
			     /
			     decrypt algo GCM : PASSED

						192 bit AES key with sign
						/
						verify algo CMAC : PASSED

								   MAC keys

								   256 bit HMAC key with sign
								   /
								   verify algo HMAC(SHA - 256)
	: PASSED

	  RSA keys

	  2048 bit RSA key with sign
	  /
	  verify algo RSA_PKCS1V15(SHA256)
	: PASSED

	  2048 bit RSA key with sign
	  /
	  verify algo RSA_PSS(SHA512)
	: PASSED

	  PERSISTENT KEYS

	  ECC keys

	  224 bit ECC_KEY_PAIR(SECP_R1)
with sign / verify algo ECDSA(SHA224)
	: PASSED

	  521 bit ECC_KEY_PAIR(SECP_R1)
with sign / verify algo ECDSA(SHA512)
	: PASSED

	  256 bit ECC_KEY_PAIR(SECP_R1)
with sign / verify algo ECDSA(SHA256)
	: FAILED

	  256 bit ECC_KEY_PAIR(BRAINPOOL_R1)
with sign / verify algo ECDSA(SHA256)
	: PASSED

	  384 bit ECC_KEY_PAIR(BRAINPOOL_R1)
with sign /
	verify algo ECDSA(SHA384)
	: PASSED

	  AES keys

	  128 bit AES key with encrypt
	  /
	  decrypt algo ECB_NO_PADDING : PASSED

					192 bit AES key with encrypt
					/
					decrypt algo CBC_NO_PADDING : PASSED

								      256 bit AES key with encrypt
								      /
								      decrypt algo CTR
	: PASSED

	  128 bit AES key with encrypt
	  /
	  decrypt algo CCM : PASSED

			     256 bit AES key with encrypt
			     /
			     decrypt algo GCM : PASSED

						192 bit AES key with sign
						/
						verify algo CMAC : PASSED

								   MAC keys

								   256 bit HMAC key with sign
								   /
								   verify algo HMAC(SHA - 256)
	: PASSED

	  RSA keys

	  2048 bit RSA key with sign
	  /
	  verify algo RSA_PKCS1V15(SHA256)
	: PASSED

	  2048 bit RSA key with sign
	  /
	  verify algo RSA_PSS(SHA512)
	: PASSED

	  End of example