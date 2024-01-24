/*********************************************************************************************************************
* CYT4BB Opensourec Library ���� CYT4BB ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
* Copyright (c) 2022 SEEKFREE ��ɿƼ�
*
* ���ļ��� CYT4BB ��Դ���һ����
*
* CYT4BB ��Դ�� ��������
* �����Ը��������������ᷢ���� GPL��GNU General Public License���� GNUͨ�ù������֤��������
* �� GPL �ĵ�3�棨�� GPL3.0������ѡ��ģ��κκ����İ汾�����·�����/���޸���
*
* ����Դ��ķ�����ϣ�����ܷ������ã�����δ�������κεı�֤
* ����û�������������Ի��ʺ��ض���;�ı�֤
* ����ϸ����μ� GPL
*
* ��Ӧ�����յ�����Դ���ͬʱ�յ�һ�� GPL �ĸ���
* ���û�У������<https://www.gnu.org/licenses/>
*
* ����ע����
* ����Դ��ʹ�� GPL3.0 ��Դ���֤Э�� �����������Ϊ���İ汾
* �������Ӣ�İ��� libraries/doc �ļ����µ� GPL3_permission_statement.txt �ļ���
* ���֤������ libraries �ļ����� �����ļ����µ� LICENSE �ļ�
* ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
*
* �ļ�����          zf_driver_pwm
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          IAR 9.40.1
* ����ƽ̨          CYT4BB
* ��������          https://seekfree.taobao.com/
*
* �޸ļ�¼
* ����              ����                ��ע
* 2024-1-8       pudding            first version
********************************************************************************************************************/

#ifndef _zf_driver_pwm_h_
#define _zf_driver_pwm_h_

#include "zf_common_typedef.h"

#define PWM_DUTY_MAX     10000                 // PWM���ռ�ձ�  ���ռ�ձ�Խ��ռ�ձȵĲ���ֵԽС

// ��ö�ٶ��岻�����û��޸�
typedef enum // ö��PWM����
{
	TCPWM_CH0_P3_1   ,	TCPWM_CH0_P6_1	 ,
	TCPWM_CH1_P3_0   ,	TCPWM_CH1_P6_3	 ,
	TCPWM_CH2_P6_5   ,	
	TCPWM_CH3_P2_4	 , 	TCPWM_CH3_P6_7	 ,
	TCPWM_CH4_P2_3   , 	TCPWM_CH4_P4_0	 ,
	TCPWM_CH5_P2_2   , 	TCPWM_CH5_P4_1	 ,
	TCPWM_CH6_P2_1   , 
	TCPWM_CH7_P2_0   , 
	TCPWM_CH9_P5_0   , 
	TCPWM_CH10_P5_1  , 
	TCPWM_CH11_P5_2  , 	TCPWM_CH11_P1_1  ,		
	TCPWM_CH12_P5_3  , 	TCPWM_CH12_P1_0  ,		
	TCPWM_CH13_P5_4  , 	TCPWM_CH13_P0_3  ,			
	TCPWM_CH14_P0_2  , 
	TCPWM_CH15_P7_1  , 
	TCPWM_CH16_P7_3  , 
	TCPWM_CH17_P7_5  , 	TCPWM_CH17_P0_1	 , 	
	TCPWM_CH18_P7_7  , 	TCPWM_CH18_P0_0	 , 	
	TCPWM_CH19_P8_0  ,	
	TCPWM_CH20_P8_1  ,	
	TCPWM_CH21_P8_2  ,	
	TCPWM_CH22_P8_3  , 	TCPWM_CH22_P23_7 ,	
	TCPWM_CH24_P9_0  ,			
	TCPWM_CH25_P9_1  , 	TCPWM_CH25_P23_4 ,		
	TCPWM_CH26_P19_1 ,
	TCPWM_CH27_P19_2 ,
	TCPWM_CH28_P10_0 ,	TCPWM_CH28_P19_3 ,	TCPWM_CH28_P22_6 ,		
	TCPWM_CH29_P10_1 ,	TCPWM_CH29_P19_4 ,	TCPWM_CH29_P22_5 ,		
	TCPWM_CH30_P10_2 ,	TCPWM_CH30_P20_0 ,	TCPWM_CH30_P22_4 ,		
	TCPWM_CH31_P10_3 ,	TCPWM_CH31_P22_3 ,		
	TCPWM_CH32_P10_4 ,	TCPWM_CH32_P22_2 ,		
	TCPWM_CH33_P22_1 ,
	TCPWM_CH34_P21_5 ,
	TCPWM_CH36_P12_0 ,	TCPWM_CH36_P21_6 ,		
	TCPWM_CH37_P12_1 ,	TCPWM_CH37_P21_5 ,		
	TCPWM_CH38_P12_2 ,	
	TCPWM_CH39_P12_3 ,	TCPWM_CH39_P21_3 ,		
	TCPWM_CH40_P12_4 ,	TCPWM_CH40_P21_2 ,		
	TCPWM_CH41_P12_5 ,	TCPWM_CH41_P21_1 ,		
	TCPWM_CH42_P21_0 ,	
	TCPWM_CH44_P13_1 ,	
	TCPWM_CH45_P13_3 ,	
	TCPWM_CH46_P13_5 ,	
	TCPWM_CH47_P13_7 ,	TCPWM_CH47_P20_3 ,		
	TCPWM_CH48_P14_0 ,	TCPWM_CH48_P20_2 ,	 	
	TCPWM_CH49_P14_1 ,	TCPWM_CH49_P20_1 ,	 	
	TCPWM_CH50_P18_7 , 	
	TCPWM_CH51_P18_6 ,	
	TCPWM_CH52_P14_4 ,	TCPWM_CH52_P18_5 ,		
	TCPWM_CH53_P14_5 ,	TCPWM_CH53_P18_4 ,		
	TCPWM_CH54_P18_3 ,	
	TCPWM_CH55_P18_2 ,	
	TCPWM_CH56_P15_0 ,	
	TCPWM_CH57_P15_1 ,	TCPWM_CH57_P17_4 ,		
	TCPWM_CH58_P15_2 ,	TCPWM_CH58_P17_3 ,		
	TCPWM_CH59_P15_3 ,	TCPWM_CH59_P17_2 ,	TCPWM_CH59_P11_2 ,		
	TCPWM_CH60_P11_1 ,	TCPWM_CH60_P17_1 ,		
	TCPWM_CH61_P11_0 ,	TCPWM_CH61_P17_0 ,	
	
	TCPWM_CH_NUM	 ,
}pwm_channel_enum;


//====================================================PWM ��������====================================================
void pwm_all_channel_close      (void);
void pwm_set_duty               (pwm_channel_enum pwmch, uint32 duty);
void pwm_init                   (pwm_channel_enum pwmch, uint32 freq, uint32 duty);
//====================================================PWM ��������====================================================

#endif
