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
* �ļ�����          main_cm0plus
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

#define FLASH_SECTION_INDEX       (0)                                           // �洢 M0���ݵ�ַ������ �õ�����
#define FLASH_PAGE_INDEX          (0)                                           // �洢 M0���ݵ�ַ������ �õ�ҳ��

 
#define DATA_LENGTH               (5)                                           // �������ݳ���

uint32 m0_data[DATA_LENGTH] = {0, 1, 2, 3, 4};                                  // ����M0��ʾ�������� ��������

int main(void)
{
    __enable_irq();
    SystemInit();                                                               // ϵͳ��ʼ�� ��ϵͳʱ�ӡ�ϵͳ��Դ��������
    debug_init();			                                        // ��ʼ��Ĭ�ϵ��Դ���

    // �˴���д�û���ʼ������ 
    
    flash_init();                                                               // flash��ʼ��(����flash֮ǰ��Ҫ��ʼ��һ��)
    
    flash_union_buffer[0].uint32_type = (uint32)&m0_data[0];                    // ȡ�����׵�ַ
    flash_union_buffer[1].uint32_type = DATA_LENGTH;                            // ȡ���鳤��
        
    flash_erase_page(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);                    // д��flash֮ǰ��Ҫ������ǰҳ ������ܵ������ݴ���
    flash_write_page_from_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX, 2);     // ����ַ�ͳ�����Ϣд��flash
    
    // �˴���д�û���ʼ������ 
    
    Cy_SysEnableApplCore(CORE_CM7_1, CY_CORTEX_M7_1_APPL_ADDR);                 // ����M7����1
    Cy_SysEnableApplCore(CORE_CM7_0, CY_CORTEX_M7_0_APPL_ADDR);                 // ����M7����0
    while(true)
    {
        // �˴���д��Ҫѭ��ִ�еĴ���
        
        system_delay_ms(1000);                                                  // ��ѭ����ʱ
        
        for(int i = 0; i < DATA_LENGTH; i ++)                                   // M0��ʾ�������� M0����û��cache ��������cache��ز���
        {
            m0_data[i] ++;
        }

        // �˴���д��Ҫѭ��ִ�еĴ���
    }
}

// **************************** �������� ****************************


