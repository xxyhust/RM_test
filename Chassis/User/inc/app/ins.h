/**
 ******************************************************************************
 * @file    ins.h
 * @author  Wang Hongxi
 * @version V2.0.0
 * @date    2022/2/23
 * @brief
 ******************************************************************************
 * @attention
 * copied from https://github.com/WangHongxi2001/RoboMaster-C-Board-INS-Example
 ******************************************************************************
 */
/*
获取ins数据解算出IMU角度
*/
#ifndef _INS_H_
#define _INS_H_

#include "stdint.h"
#include "QuaternionEKF.h"
#include "icm20602.h"

#define X 0
#define Y 1
#define Z 2

#define INS_TASK_PERIOD 1
#define RAD_TO_ANGLE_COEF 57.295779513f
#define ANGLE_TO_RAD_COEF 0.0174532925f
#define PI_2 6.2831853072f

typedef struct
{
    float q[4]; // 四元数估计值

    float Gyro[3];          // 角速度
    float Accel[3];         // 加速度
    float MotionAccel_b[3]; // 机体坐标加速度
    float MotionAccel_n[3]; // 绝对系加速度

    float AccelLPF; // 加速度低通滤波系数

    // 加速度在绝对系的向量表示
    float xn[3];
    float yn[3];
    float zn[3];

    float atanxz;
    float atanyz;

    // 位姿
    float Roll;
    float Pitch;
    float Yaw;
    float YawTotalAngle;
} INS_t;

/**
 * @brief 用于修正安装误差的参数,demo中可无视
 *
 */
typedef struct
{
    uint8_t flag;

    float scale[3];

    float Yaw;
    float Pitch;
    float Roll;
} IMU_Param_t;

extern INS_t INS;

void INS_Init(void);
void INS_Task(IMU *IMUReceive, IMU_Data_t *icm_20602);

void QuaternionUpdate(float *q, float gx, float gy, float gz, float dt);
void QuaternionToEularAngle(float *q, float *Yaw, float *Pitch, float *Roll);
void EularAngleToQuaternion(float Yaw, float Pitch, float Roll, float *q);
void BodyFrameToEarthFrame(const float *vecBF, float *vecEF, float *q);
void EarthFrameToBodyFrame(const float *vecEF, float *vecBF, float *q);

#endif // !_INS_H_
