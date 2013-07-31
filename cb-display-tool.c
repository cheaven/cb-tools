#include <stdio.h>
#include <sys/ioctl.h>
#include <stdint.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <linux/types.h>
#include <video/sunxi_disp_ioctl.h>

static const char * dispdev = "/dev/disp";
__disp_vga_mode_t default_vga_mode = DISP_VGA_H1024_V768;
__disp_tv_mode_t default_tv_mode = DISP_TV_MOD_720P_50HZ;

int outport(int sel,int dispfh,__disp_output_type_t type,__disp_tv_mode_t mode)
{	
	unsigned long arg[4];

	printf("port=%d,mode=%d\n",type,mode);	

	if(type == DISP_OUTPUT_TYPE_LCD) {
		printf("LCD mode\n");
		arg[0] = sel;
		arg[1] = 0;
		arg[2] = 0;
		ioctl(dispfh,DISP_CMD_LCD_OFF,(unsigned long)arg);
		ioctl(dispfh,DISP_CMD_VGA_OFF,(unsigned long)arg);
		ioctl(dispfh,DISP_CMD_TV_OFF,(unsigned long)arg);
		ioctl(dispfh,DISP_CMD_HDMI_OFF,(unsigned long)arg);
		ioctl(dispfh,DISP_CMD_LCD_ON,(unsigned long)arg);
	}
	else if(type == DISP_OUTPUT_TYPE_TV) {
		printf("TV mode\n");
		arg[0] = sel;
		arg[1] = 0;
		arg[2] = 0;
		ioctl(dispfh,DISP_CMD_TV_OFF,(unsigned long)arg);
		ioctl(dispfh,DISP_CMD_LCD_OFF,(unsigned long)arg);
		ioctl(dispfh,DISP_CMD_HDMI_OFF,(unsigned long)arg);	
		ioctl(dispfh,DISP_CMD_VGA_OFF,(unsigned long)arg);
		arg[0] = sel;
		arg[1] = mode;
		arg[2] = 0;
		ioctl(dispfh,DISP_CMD_TV_SET_MODE,(unsigned long)arg);
		
		arg[0] = sel;
		arg[1] = 0;
		arg[2] = 0;
		ioctl(dispfh,DISP_CMD_TV_ON,(unsigned long)arg);
	}
	else if(type == DISP_OUTPUT_TYPE_HDMI) {
		printf("HDMI mode\n");
		arg[0] = sel;
		arg[1] = 0;
		arg[2] = 0;
		ioctl(dispfh,DISP_CMD_TV_OFF,(unsigned long)arg);
		ioctl(dispfh,DISP_CMD_LCD_OFF,(unsigned long)arg);
		ioctl(dispfh,DISP_CMD_HDMI_OFF,(unsigned long)arg);	
		ioctl(dispfh,DISP_CMD_VGA_OFF,(unsigned long)arg);
		arg[0] = sel;
		arg[1] = mode;
		arg[2] = 0;
		ioctl(dispfh,DISP_CMD_HDMI_SET_MODE,(unsigned long)arg);
		
		arg[0] = sel;
		arg[1] = 0;
		arg[2] = 0;
		ioctl(dispfh,DISP_CMD_HDMI_ON,(unsigned long)arg);
		
	}
	else if(type == DISP_OUTPUT_TYPE_VGA) {
		printf("VGA mode\n");
		arg[0] = sel;
		arg[1] = 0;
		arg[2] = 0;
		ioctl(dispfh,DISP_CMD_LCD_OFF,(unsigned long)arg);
		ioctl(dispfh,DISP_CMD_HDMI_OFF,(unsigned long)arg);	
		ioctl(dispfh,DISP_CMD_VGA_OFF,(unsigned long)arg);
		ioctl(dispfh,DISP_CMD_TV_OFF,(unsigned long)arg);
		arg[0] = sel;
		arg[1] = mode;
		arg[2] = 0;
		ioctl(dispfh,DISP_CMD_VGA_SET_MODE,(unsigned long)arg);
		
		
		arg[0] = sel;
		arg[1] = 0;
		arg[2] = 0;
		ioctl(dispfh,DISP_CMD_VGA_ON,(unsigned long)arg);
	}
	else {
		printf("No Output Port select!!");
		return -1;
	}
	return 0;
}


void print_tv_mode()
{
	printf("TV Mode:\n" \
		"\t0 - 480p\n"			\
	       "\t1 - 576i\n" \
	       "\t2 - 480p\n" \
	       "\t3 - 576p\n" \
	       "\t4 - 720p@50Hz\n" \
	       "\t5 - 720p@60Hz\n" \
	       "\t6 - 1080i@50Hz\n" \
	       "\t7 - 1080i@60Hz\n" \
	       "\t8 - 1080p@24Hz\n" \
	       "\t9 - 1080p@50Hz\n" \
	       "\t10- 1080p@60Hz\n\n");

}

#if 0
typedef enum {
	DISP_VGA_H1680_V1050 = 0,
	DISP_VGA_H1440_V900 = 1,
	DISP_VGA_H1360_V768 = 2,
	DISP_VGA_H1280_V1024 = 3,
	DISP_VGA_H1024_V768 = 4,
	DISP_VGA_H800_V600 = 5,
	DISP_VGA_H640_V480 = 6,
	DISP_VGA_H1440_V900_RB = 7, /* not support yet */
	DISP_VGA_H1680_V1050_RB = 8, /* not support yet */
	DISP_VGA_H1920_V1080_RB = 9,
	DISP_VGA_H1920_V1080 = 0xa,
	DISP_VGA_H1280_V720 = 0xb,
	DISP_VGA_MODE_NUM = 0xc,
} __disp_vga_mode_t;
#endif

void print_vga_mode()
{
	printf("VGA Mode:\n" \
	       "\t0 - 1680x1050\n"		\
	       "\t1 - 1440x900\n" \
	       "\t2 - 1360x768\n" \
	       "\t3 - 1280x1024\n" \
	       "\t4 - 1024x768\n" \
	       "\t5 - 800x600\n" \
	       "\t6 - 640x480\n" \
	       "\t7 - 1440x900-RB\n" \
	       "\t8 - 1680x1050-RB\n" \
	       "\t9 - 1920x1080-RB\n" \
	       "\t10- 1920x1080\n" \
	       "\t11- 1280x720\n" \
	       "\t12- Mode Num\n\n"
	       );
}


void print_help()
{
	printf("CB-DISPLAY-TOOL\n" \
	       "NAME\n" \
	       "\tcb-display-tool - simple tool to control cubieboard's display output mode\n"  \
	       "OPTIONS\n" \
	       "\t-o output  Output type, 4(HDMI), 8(VGA)\n" \
	       "\t-m mode    Mode type\n" \
	       "\n");

	print_tv_mode();
	print_vga_mode();
}

int main(int argc, char *argv[])
{
	int dispfd = -1, ret = -1, opt;
	unsigned int var[6];
	int output = 4, mode = 4;

	while(( opt = getopt(argc, argv, "o:m:h")) != -1) {
		switch (opt) {
		case 'o':
			output = atoi(optarg);
			break;
		case 'm':
			mode = atoi(optarg);
			break;
		default:
			print_help();
			return 0;
		}
	}

	if (output != 4 && output != 8) {
		printf("only support VGA and HDMI now!\n");
		return -1;
	}


	dispfd = open(dispdev, O_RDWR);
	if (dispfd < 0) {
		perror("open /dev/disp");
		return -1;
	}

	ret = outport(0, dispfd, output, mode);
	printf("ret = %d\n", ret);

	close(dispfd);

	return 0;
}


