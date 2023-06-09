/*
 * Copyright (C) 2015 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     drivers_lsm303dlhc
 * @{
 *
 * @file
 * @brief       LSM303DLHC adaption to the RIOT actuator/sensor interface
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 *
 * @}
 */

#include <string.h>

#include "saul.h"
#include "lsm303dlhc.h"

static int read_acc(const void *dev, phydat_t *res)
{
    const lsm303dlhc_t *d = (const lsm303dlhc_t *)dev;
    lsm303dlhc_read_acc(d, (lsm303dlhc_3d_data_t *)res->val);

    /* normalize result */
    int fac = (1 << (d->params.acc_scale >> 4));
    for (int i = 0; i < 3; i++) {
        res->val[i] *= fac;
    }

    res->unit = UNIT_G_FORCE;
    res->scale = -3;
    return 3;
}

static int read_mag(const void *dev, phydat_t *res)
{
    const lsm303dlhc_t *d = (const lsm303dlhc_t *)dev;

    lsm303dlhc_read_mag(d, (lsm303dlhc_3d_data_t *)res->val);

    /* normalize results */
    int gain;
    switch (d->params.mag_gain) {
        case LSM303DLHC_MAG_GAIN_1100_980_GAUSS: gain = 1100; break;
        case LSM303DLHC_MAG_GAIN_855_760_GAUSS:  gain = 855;  break;
        case LSM303DLHC_MAG_GAIN_670_600_GAUSS:  gain = 670;  break;
        case LSM303DLHC_MAG_GAIN_450_400_GAUSS:  gain = 450;  break;
        case LSM303DLHC_MAG_GAIN_400_355_GAUSS:  gain = 400;  break;
        case LSM303DLHC_MAG_GAIN_330_295_GAUSS:  gain = 330;  break;
        case LSM303DLHC_MAG_GAIN_230_205_GAUSS:  gain = 230;  break;
        default: gain = 1000; break;
    }
    for (int i = 0; i < 3; i++) {
        int32_t tmp = res->val[i] * 1000;
        tmp /= gain;
        res->val[i] = (int16_t)tmp;
    }

    res->unit = UNIT_GAUSS;
    res->scale = -3;
    return 3;
}

const saul_driver_t lsm303dlhc_saul_acc_driver = {
    .read = read_acc,
    .write = saul_write_notsup,
    .type = SAUL_SENSE_ACCEL,
};

const saul_driver_t lsm303dlhc_saul_mag_driver = {
    .read = read_mag,
    .write = saul_write_notsup,
    .type = SAUL_SENSE_MAG,
};
