#ifndef __R2P_IMU_H__
#define __R2P_IMU_H__

#include "BaseMessage.hpp"

#define IMU_RAW_ID		4001
#define IMU_ATTITUDE_ID	4011

struct IMURaw: public BaseMessage {
	uint16_t gx;
	uint16_t gy;
	uint16_t gz;
	uint16_t ax;
	uint16_t ay;
	uint16_t az;
	uint16_t mx;
	uint16_t my;
	uint16_t mz;
}__attribute__((packed));

struct IMUAttitude: public BaseMessage {
	  float roll;
	  float pitch;
	  float yaw;
}__attribute__((packed));

#endif /* __R2P_IMU_H__ */
