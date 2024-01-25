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
* �ļ�����          main_cm7_0
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          IAR 9.40.1
* ����ƽ̨          CYT4BB
* ��������          https://seekfree.taobao.com/
*
* �޸ļ�¼
* ����              ����                ��ע
* 2024-1-4       pudding            first version
********************************************************************************************************************/

#include "zf_common_headfile.h"
#include "arm_math.h"

// ���µĹ��̻��߹����ƶ���λ�����ִ�����²���
// ��һ�� �ر��������д򿪵��ļ�
// �ڶ��� project->clean  �ȴ��·�����������

// *************************** ����Ӳ������˵�� ***************************
// ʹ����ɿƼ� CMSIS-DAP ��������������
//      ֱ�ӽ���������ȷ�����ں��İ�ĵ������ؽӿڼ���
// ʹ�� USB-TTL ģ������
//      ģ��ܽ�            ��Ƭ���ܽ�
//      USB-TTL-RX          �鿴 zf_common_debug.h �ļ��� DEBUG_UART_TX_PIN �궨������� Ĭ�� P14_0
//      USB-TTL-TX          �鿴 zf_common_debug.h �ļ��� DEBUG_UART_RX_PIN �궨������� Ĭ�� P14_1
//      USB-TTL-GND         ���İ��Դ�� GND
//      USB-TTL-3V3         ���İ� 3V3 ��Դ

// ***************************** ���̲���˵�� *****************************
// 1.���İ���¼��ɱ����̣�����ʹ�ú��İ���������������� USB-TTL ģ�飬�ڶϵ�������������
// 2.���������������� USB-TTL ģ�����ӵ��ԣ�����ϵ�
// 3.������ʹ��������ִ򿪶�Ӧ�Ĵ��ڣ����ڲ�����Ϊ DEBUG_UART_BAUDRATE �궨�� Ĭ�� 115200�����İ尴�¸�λ����
// 4.��������������Ͽ������´�����Ϣ��
//      fft count use time: 493 us
// 5.������������ֵ�ʾ�������濴��FFT������ɺ�Ľ������
// �������������˵�����ز��� ����ձ��ļ����·� ���̳�������˵�� �����Ų�

// **************************** �������� ****************************

#define FFT_SIZE 1024

float inputSignal[FFT_SIZE * 2];                // ���������ź� �����ź�Ϊ���� ���Գ���Ϊ FFT_SIZE * 2
float outputSignal[FFT_SIZE * 2];               // ��������ź� ����ź�Ϊ���� ���Գ���Ϊ FFT_SIZE * 2

uint32 fft_count_time_us = 0;

int main(void)
{
    clock_init(SYSTEM_CLOCK_250M); 	        // ʱ�����ü�ϵͳ��ʼ��<��ر���>
    debug_info_init();                          // ���Դ�����Ϣ��ʼ��
    // �˴���д�û����� ���������ʼ�������

    
    for(int i = 0; i < FFT_SIZE; i++){
        inputSignal[2*i] = i * 0.1024;          // �������������⸳ֵ��ʵ�������ź���ADC�ɼ�   ����������ʵ�����鲿Ϊ0
        inputSignal[2*i + 1] = 0;
    }    

    arm_cfft_instance_f32 arm_cfft_instance_f32_len_1024;                       // ����FFT����
          
    arm_cfft_init_f32(&arm_cfft_instance_f32_len_1024, FFT_SIZE);               // ��ʼ��FFT���� ������㳤��
    
    timer_init(TC_TIME2_CH0, TIMER_US);                                         // ��ʼ��һ����ʱ�� ���ڼ�¼FFT����ĺ�ʱ
      
    timer_start(TC_TIME2_CH0);                                                  // ������ʱ��
    
    arm_cfft_f32(&arm_cfft_instance_f32_len_1024 , inputSignal , 0 , 1);        // 32λ����FFT����
    
    arm_cmplx_mag_f32(inputSignal , outputSignal , FFT_SIZE);                   // ��FFT���ת��Ϊ������
    
    fft_count_time_us = timer_get(TC_TIME2_CH0);                                // ��ȡFFT����ʱ��
    
    timer_clear(TC_TIME2_CH0);                                                  // �����ʱ������ֵ
    
    timer_stop(TC_TIME2_CH0);                                                   // �رն�ʱ��
    
    seekfree_assistant_interface_init(SEEKFREE_ASSISTANT_DEBUG_UART);           // ��ʼ������������ ѡ��debug���������Ϣ
    
    seekfree_assistant_oscilloscope_data.channel_num  = 1;                      // ����ͨ������Ϊ1��

    for(int i = 0; i < FFT_SIZE; i++)
    {
        seekfree_assistant_oscilloscope_data.data[0] = outputSignal[i];         // ��ȡFFT�����ķ�����Ϣ
        
        seekfree_assistant_oscilloscope_send(&seekfree_assistant_oscilloscope_data);     // ���������Ϣ��ʾ����                                     
    }   
    
    printf("\r\n fft count use time: %d us\r\n", fft_count_time_us);            // ���FFT�����ʱ
    
    // �˴���д�û����� ���������ʼ�������
    
    while(true)
    {
        // �˴���д��Ҫѭ��ִ�еĴ���


        
        // �˴���д��Ҫѭ��ִ�еĴ���
    }
}

// **************************** �������� ****************************

// **************************** ���̳�������˵�� ****************************
// ��������ʱ�밴�������������б���
// ����1������û������
//      �鿴������ִ򿪵��Ƿ�����ȷ�Ĵ��ڣ����򿪵� COM ���Ƿ��Ӧ���ǵ������������� USB-TTL ģ��� COM ��
//      �����ʹ����ɿƼ� Ӣ����TriCore �������������ӣ���ô������������Ƿ��ɶ��������İ崮�������Ƿ��Ѿ����ӣ��������߲鿴���İ�ԭ��ͼ�����ҵ�
//      �����ʹ�� USB-TTL ģ�����ӣ���ô��������Ƿ������Ƿ��ɶ���ģ�� TX �Ƿ����ӵĺ��İ�� RX��ģ�� RX �Ƿ����ӵĺ��İ�� TX
// ����2��������������
//      �鿴����������õĲ������Ƿ����������һ�£������� zf_common_debug.h �ļ��� DEBUG_UART_BAUDRATE �궨��Ϊ debug uart ʹ�õĴ��ڲ�����
