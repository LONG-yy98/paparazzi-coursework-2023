/*
 * Copyright (C) 2023 Ryan Y. Liu <yueqianliu@outlook.com>
 *
 * This file is part of paparazzi
 *
 * paparazzi is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * paparazzi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with paparazzi; see the file COPYING.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

/**
 * @file "modules/maze_runner/maze_runner.h"
 * @author Ryan Y. Liu <yueqianliu@outlook.com>
 * A module for AE4317 Autonomous Flight of Micro Air Vehicles at the TU Delft.
 * This module aims to provide a collision free navigation strategy for the Bebop in the Cyberzoo.
 * Cyberzoo == Maze, so bebop == maze runner :p
 */

#ifndef MAZE_RUNNER_H
#define MAZE_RUNNER_H

#include "firmwares/rotorcraft/navigation.h"
#include "firmwares/rotorcraft/guidance/guidance_h.h"
#include "generated/airframe.h"
#include "modules/core/abi.h"
#include "pthread.h"
#include "state.h"
#include "string.h"
#include "math.h"
#include <time.h>
#include <stdio.h>



#define MAZE_RUNNER_VERBOSE TRUE
#ifndef MAZE_RUNNER_VISUAL_DETECTION_ID
#define MAZE_RUNNER_VISUAL_DETECTION_ID ABI_BROADCAST
#endif

struct cv_info_t
{
    float lmag;
    float rmag;
    float leof;
    float reof;
    int fps;
};

struct dbg_msg_t
{
    float lmag;
    float rmag;
    float leof;
    float reof;
    float dmag;
    float deof;
    int16_t fps;
};

struct cmd_t
{
    float yaw_rate;
    float body_vel_x;
    float body_vel_y;
};


struct mav_state_t
{
    struct EnuCoor_f pos_enu;
    struct EnuCoor_f vel_enu;
    struct FloatEulers rpy_ned;
    struct FloatRates ang_vel_body;
};

extern void maze_runner_init(void);
extern void maze_runner_loop(void);

void cv_cb(uint8_t __attribute__((unused)) sender_id,
           float left_flow_mag,
           float right_flow_mag,
           float left_flow_eof,
           float right_flow_eof,
           int fps);

void ctrl_backend_init(void);
void ctrl_backend_run(struct cmd_t *cmd, struct EnuCoor_f *goal, struct mav_state_t *mav, struct cv_info_t *cv);

#endif
