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
// ������������������
//      ģ��ܽ�            ��Ƭ���ܽ�
//      A                   ENCODER_QUADDEC_A �궨������� Ĭ�� B4
//      B                   ENCODER_QUADDEC_B �궨������� Ĭ�� B5
//      GND                 ���İ��Դ�� GND
//      3V3                 ���İ� 3V3 ��Դ
// ���뷽�����������
//      ģ��ܽ�            ��Ƭ���ܽ�
//      LSB                 ENCODER_DIR_PULSE �궨������� Ĭ�� B6
//      DIR                 ENCODER_DIR_DIR �궨������� Ĭ�� B7
//      GND                 ���İ��Դ�� GND
//      3V3                 ���İ� 3V3 ��Դ



// *************************** ���̲���˵�� ***************************
// 1.���İ���¼��ɱ����̣�����ʹ�ú��İ���������������� USB-TTL ģ�飬�����Ӻñ��������ڶϵ�������������
// 2.���������������� USB-TTL ģ�����ӵ��ԣ�����ϵ�
// 3.������ʹ�ô������ִ򿪶�Ӧ�Ĵ��ڣ����ڲ�����Ϊ zf_common_debug.h �ļ��� DEBUG_UART_BAUDRATE �궨�� Ĭ�� 115200�����İ尴�¸�λ����
// 4.�����ڴ��������Ͽ������´�����Ϣ��
//      ENCODER_QUADDEC counter     x .
//      ENCODER_DIR counter         x .
// 5.ת���������ͻῴ����ֵ�仯
// �������������˵�����ز��� ����ձ��ļ����·� ���̳�������˵�� �����Ų�

// **************************** �������� ****************************

#define PIT0                             (PIT_CH0 )                             // ʹ�õ������жϱ��

#define ENCODER_DIR1                     (TC_CH58_ENCODER)                      // �������������Ӧʹ�õı������ӿ�       
#define ENCODER_DIR_PULSE1               (TC_CH58_ENCODER_CH1_P17_3)            // PULSE ��Ӧ������                      
#define ENCODER_DIR_DIR1                 (TC_CH58_ENCODER_CH2_P17_4)            // DIR ��Ӧ������                        
                                                                                
#define ENCODER_DIR2                     (TC_CH27_ENCODER)                      // �������������Ӧʹ�õı������ӿ�   
#define ENCODER_DIR_PULSE2               (TC_CH27_ENCODER_CH1_P19_2)            // PULSE ��Ӧ������                  
#define ENCODER_DIR_DIR2                 (TC_CH27_ENCODER_CH2_P19_3)            // DIR ��Ӧ������                    
                                                                                
#define ENCODER_DIR3                     (TC_CH07_ENCODER)                      // �������������Ӧʹ�õı������ӿ�  
#define ENCODER_DIR_PULSE3               (TC_CH07_ENCODER_CH1_P07_6)            // PULSE ��Ӧ������                 
#define ENCODER_DIR_DIR3                 (TC_CH07_ENCODER_CH2_P07_7)            // DIR ��Ӧ������                   
                                                                                
#define ENCODER_DIR4                     (TC_CH20_ENCODER)                      // �������������Ӧʹ�õı������ӿ�
#define ENCODER_DIR_PULSE4               (TC_CH20_ENCODER_CH1_P08_1)            // PULSE ��Ӧ������
#define ENCODER_DIR_DIR4                 (TC_CH20_ENCODER_CH2_P08_2)            // DIR ��Ӧ������

int16 encoder_data_dir[4] = {0};

uint8 pit_state = 0;

int main(void)
{
    clock_init(SYSTEM_CLOCK_250M); 	// ʱ�����ü�ϵͳ��ʼ��<��ر���>
    debug_init();			// ��ʼ��Ĭ�ϵ��Դ���
    // �˴���д�û����� ���������ʼ�������


    encoder_dir_init(ENCODER_DIR1, ENCODER_DIR_PULSE1, ENCODER_DIR_DIR1);       // ��ʼ��������ģ�������� ����������������ģʽ
    encoder_dir_init(ENCODER_DIR2, ENCODER_DIR_PULSE2, ENCODER_DIR_DIR2);       // ��ʼ��������ģ�������� ����������������ģʽ
    encoder_dir_init(ENCODER_DIR3, ENCODER_DIR_PULSE3, ENCODER_DIR_DIR3);       // ��ʼ��������ģ�������� ����������������ģʽ
    encoder_dir_init(ENCODER_DIR4, ENCODER_DIR_PULSE4, ENCODER_DIR_DIR4);       // ��ʼ��������ģ�������� ����������������ģʽ

    pit_ms_init(PIT0, 500);                                                     // ��ʼ�� PIT0 Ϊ�����ж� 100ms ��
    
    
    // �˴���д�û����� ���������ʼ�������
    while(true)
    {
        // �˴���д��Ҫѭ��ִ�еĴ���
        if(pit_state)
        {
            pit_state = 0;
            encoder_data_dir[0] = encoder_get_count(ENCODER_DIR1);
            encoder_clear_count(ENCODER_DIR1);
            encoder_data_dir[1] = encoder_get_count(ENCODER_DIR2);
            encoder_clear_count(ENCODER_DIR2);
            encoder_data_dir[2] = encoder_get_count(ENCODER_DIR3);
            encoder_clear_count(ENCODER_DIR3);
            encoder_data_dir[3] = encoder_get_count(ENCODER_DIR4);
            encoder_clear_count(ENCODER_DIR4);
            
            printf("ENCODER_DIR_1 counter \t\t%d .\r\n", encoder_data_dir[0]);      // ���������������Ϣ
            printf("ENCODER_DIR_2 counter \t\t%d .\r\n", encoder_data_dir[1]);      // ���������������Ϣ
            printf("ENCODER_DIR_3 counter \t\t%d .\r\n", encoder_data_dir[2]);      // ���������������Ϣ
            printf("ENCODER_DIR_4 counter \t\t%d .\r\n", encoder_data_dir[3]);      // ���������������Ϣ
        }

        
        // �˴���д��Ҫѭ��ִ�еĴ���
    }
}

// **************************** �������� ****************************

// *************************** ���̳�������˵�� ***************************
// ��������ʱ�밴�������������б���
// ����1������û������
//      �鿴�������ִ򿪵��Ƿ�����ȷ�Ĵ��ڣ����򿪵� COM ���Ƿ��Ӧ���ǵ������������� USB-TTL ģ��� COM ��
//      �����ʹ����ɿƼ� CMSIS-DAP �������������ӣ���ô������������Ƿ��ɶ��������İ崮�������Ƿ��Ѿ����ӣ��������߲鿴���İ�ԭ��ͼ�����ҵ�
//      �����ʹ�� USB-TTL ģ�����ӣ���ô��������Ƿ������Ƿ��ɶ���ģ�� TX �Ƿ����ӵĺ��İ�� RX��ģ�� RX �Ƿ����ӵĺ��İ�� TX
// ����2��������������
//      �鿴�����������õĲ������Ƿ����������һ�£������� zf_common_debug.h �ļ��� DEBUG_UART_BAUDRATE �궨��Ϊ debug uart ʹ�õĴ��ڲ�����
// ����3����ֵһֱ������һ��ת
//      ��Ҫ�ѷ����������������������ģʽ�Ľӿ���
// ����4����ֵ�������ת���仯
//      ���ʹ��������ԣ��������Ҫ�õ�ع���
//      ���������Ƿ��������ģ����Ƿ��ɶ����������Ƿ������ˣ��Ƿ�Ӵ���
