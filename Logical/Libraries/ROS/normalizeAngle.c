
#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "ROS.h"
#ifdef __cplusplus
	};
#endif

#define M_PI 3.14159265358979323846

/* TODO: Add your comment here */
double normalizeAngle(double angle)
{

	if( angle > M_PI){
		angle -= 2.0 * M_PI;
	}
	if(angle < -M_PI){
		angle += 2.0 * M_PI;
	}
	
	return angle;
}
