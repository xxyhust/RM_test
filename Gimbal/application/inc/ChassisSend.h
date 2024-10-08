#ifndef _CHASSIS_SEND_H
#define _CHASSIS_SEND_H

#include <string.h>
#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "remote_control.h"
#include "ins_task.h"
#include "Gimbal.h"
#include "ChassisSolver.h"
#include "pc_serial.h"

#pragma pack(push, 1)

typedef struct ChassisSendPack1
{
  uint16_t robot_state : 1;
  uint16_t control_type : 2;
  uint16_t control_mode_action : 4;
  uint16_t gimbal_mode : 3;
  uint16_t shoot_mode : 3;
  uint16_t _ : 2; // 无用占位
  uint16_t is_pc_on : 1;
  uint8_t autoaim_id; // 自瞄ID

  uint8_t extra_leg_mode;
  uint8_t cover_state : 1;
  uint8_t reserved : 7;

  int8_t robot_speed_x; // * 10 描述 x方向为云台正方向
  int8_t robot_speed_y; // * 10描述
  int8_t robot_speed_w;
} ChassisSendPack1;

typedef struct ChassisSendPack2 // 云台yaw和pitch角度
{
  int16_t yaw_motor_angle; // yaw轴电机角度
  int16_t gimbal_pitch;    // 云台pitch角度
  int16_t gimbal_yaw_speed;
  int16_t super_power;
} ChassisSendPack2;

#pragma pack(pop)

extern ChassisSendPack1 chassis_send_pack1;//底盘数据包1（发送
extern ChassisSendPack2 chassis_send_pack2;//底盘数据包2（发送）

void Pack_InfantryMode(void);//打包发送数据包1，包含各种模式和状态
void Pack_Yaw(void);//打包发送数据包2，主要包含云台yaw和pitch角度

#endif // !_CHASSIS_SEND_H
