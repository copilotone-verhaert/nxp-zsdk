/*
 * Copyright (c) 2025 NXP
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef NXP_VENDOR_TYPES_H_
#define NXP_VENDOR_TYPES_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief CCA Mode Configuration
 */
typedef struct otCCAModeConfig {
	uint8_t mCcaMode;
	/*< CCA Mode: 1=CCA1, 2=CCA2, 3=CCA1 AND CCA2, 4=CCA1 OR CCA2, 0xFF=No CCA*/
	uint8_t mCca1Threshold;		/*< Energy threshold for CCA Mode 1*/
	uint8_t mCca2CorrThreshold;	/*< Correlation threshold for CCA Mode 2*/
	uint8_t mCca2MinNumOfCorrTh;/*< Minimum number of correlation threshold (0-6)*/
} otCCAModeConfig;

#ifdef __cplusplus
}
#endif

#endif /* NXP_VENDOR_TYPES_H_*/
