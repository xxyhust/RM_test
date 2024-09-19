#ifndef _CHASSIS_SOLVER_H
#define _CHASSIS_SOLVER_H

#include "remote_control.h"
#include "debug.h"

#include "Offline_Task.h"
#include "ins_task.h"
#include "Gimbal.h"
#include "pc_serial.h"
#include "ToggleBullet.h"
#include "BombBay.h"

#define SPEED_MAX 2.0f      // 最大速度
#define SPEED_W_MAX 3.5f    // 最大角速度
#define MAX_LEG_SPEED 0.08f // 最大伸腿速度 m/s

#define MAX_SW_YAW_SPEED 180.0f  // 云台yaw轴灵敏度(拨杆) 度/s
#define MAX_SW_PITCH_SPEED 50.0f // 云台yaw轴灵敏度(拨杆) 度/s

typedef struct ChassisSolver
{
    float chassis_speed_x; // 云台方向速度
    float chassis_speed_y; // 垂直云台方向速度
    float chassis_speed_w; // 小陀螺状态的速度期望

    // yaw轴云台
    uint32_t last_cnt;
    float delta_t;
} ChassisSolver;

extern ChassisSolver chassis_solver;

void get_control_info(ChassisSolver *infantry);//根据控制模式选择不同的控制命令解析函数，//会解析出控制模式，云台yaaw和pitch的目标角度，以及底盘的各方向速度
void setAllModeOff(void);//下电模式

#endif // !_CHASSIS_SOLVER_H
