/*********************************************************************************************************************
* CYT4BB Opensourec Library 即（ CYT4BB 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
*
* 本文件是 CYT4BB 开源库的一部分
*
* CYT4BB 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
*
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
*
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
*
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
*
* 文件名称          main_cm7_0
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          IAR 9.40.1
* 适用平台          CYT4BB
* 店铺链接          https://seekfree.taobao.com/
*
* 修改记录
* 日期              作者                备注
* 2024-1-4       pudding            first version
********************************************************************************************************************/

#include "zf_common_headfile.h"

// 打开新的工程或者工程移动了位置务必执行以下操作
// 第一步 关闭上面所有打开的文件
// 第二步 project->clean  等待下方进度条走完

// *************************** 例程硬件连接说明 ***************************
// 使用逐飞科技 CMSIS-DAP 调试下载器连接
//      直接将下载器正确连接在核心板的调试下载接口即可
// 使用 USB-TTL 模块连接
//      模块管脚            单片机管脚
//      USB-TTL-RX          查看 zf_common_debug.h 文件中 DEBUG_UART_TX_PIN 宏定义的引脚 默认 P14_0
//      USB-TTL-TX          查看 zf_common_debug.h 文件中 DEBUG_UART_RX_PIN 宏定义的引脚 默认 P14_1
//      USB-TTL-GND         核心板电源地 GND
//      USB-TTL-3V3         核心板 3V3 电源

// *************************** 例程测试说明 ***************************
// 1.核心板烧录完成本例程，单独使用核心板与调试下载器或者 USB-TTL 模块，在断电情况下完成连接
// 
// 2.将调试下载器或者 USB-TTL 模块连接电脑，完成上电
// 
// 3.电脑上使用串口助手打开对应的串口，串口波特率为 zf_common_debug.h 文件中 DEBUG_UART_BAUDRATE 宏定义 默认 115200，核心板按下复位按键
// 
// 4.可以在串口助手上看到如下串口信息：
//  m0_data:0,1,2,3,4,
//  m7_1_data:0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,
//  m0_data:0,1,2,3,4,
//  m7_1_data:0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,
//  m0_data:0,1,2,3,4,
//  m7_1_data:0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,
//  m0_data:0,1,2,3,4,
//  m7_1_data:0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,
//  m0_data:1,2,3,4,5,
//  m7_1_data:0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,
// 
// 如果发现现象与说明严重不符 请参照本文件最下方 例程常见问题说明 进行排查

// **************************** 代码区域 ****************************
#define M0_FLASH_SECTION_INDEX       (0)                                        // 存储 M0数据地址及长度 用的扇区
#define M0_FLASH_PAGE_INDEX          (0)                                        // 存储 M0数据地址及长度 用的页码 

#define M7_1_FLASH_SECTION_INDEX     (0)                                        // 存储 M7_1数据地址及长度 用的扇区
#define M7_1_FLASH_PAGE_INDEX        (1)                                        // 存储 M7_1数据长度及长度 用的页码 

volatile uint32 *m0_data;                                                      // 定义一个数据指针 用于通过地址直接访问M0数据 
uint32 m0_data_length;                                                          // 定义M0数据的长度 

volatile float *m7_1_data;                                                     // 定义一个数据指针 用于通过地址直接访问M7_1数据 
uint32 m7_1_data_length;                                                        // 定义M7_1数据的长度 

int main(void)
{
    clock_init(SYSTEM_CLOCK_250M); 	// 时钟配置及系统初始化<务必保留>
    debug_info_init();                  // 调试串口信息初始化
    // 此处编写用户代码 例如外设初始化代码等

    system_delay_ms(500);                                                       // 等待M0和M7_1将地址保存到flash  也可以使用查询flash数据的方式(此处不演示)
    
    flash_init();                                                               // flash初始化(访问flash之前需要初始化一次)
    
    flash_read_page_to_buffer(M0_FLASH_SECTION_INDEX, M0_FLASH_PAGE_INDEX, 2);  // 读取M0数据地址所在页的数据               
    m0_data = (volatile uint32 *)flash_union_buffer[0].uint32_type;             // 保存地址和长度 使用指针直接访问
    m0_data_length = flash_union_buffer[1].uint32_type;
    
    flash_read_page_to_buffer(M7_1_FLASH_SECTION_INDEX, M7_1_FLASH_PAGE_INDEX, 2);  // 读取M7_1数据地址所在页的数据                  
    m7_1_data = (volatile float *)flash_union_buffer[0].uint32_type;            // 保存地址和长度 使用指针直接访问
    m7_1_data_length = flash_union_buffer[1].uint32_type;
    
    // 此处编写用户代码 例如外设初始化代码等
    while(true)
    {
        // 此处编写需要循环执行的代码

        system_delay_ms(100);                                                   // 主循环延时
        
        SCB_CleanInvalidateDCache();                                            // M7_0有Dcashe 读取数据之前需要更新DCache的数据
        
        printf("m0_data:");                                                     // 直接将数据打印到串口
        for(int i = 0; i < m0_data_length; i ++)
        {
            
            printf("%d,", m0_data[i]);
        }
        printf("\r\n");
        
        printf("m7_1_data:");        
        for(int i = 0; i < m7_1_data_length; i ++)
        {
            printf("%.1f,", m7_1_data[i]);
        }
        printf("\r\n");
        
        // 此处编写需要循环执行的代码
    }
}

// **************************** 代码区域 ****************************

// 遇到问题时请按照以下问题检查列表检查
// 问题1：串口没有数据
//      查看串口助手打开的是否是正确的串口，检查打开的 COM 口是否对应的是调试下载器或者 USB-TTL 模块的 COM 口
//      如果是使用逐飞科技 CMSIS-DAP 调试下载器连接，那么检查下载器线是否松动，检查核心板串口跳线是否已经焊接，串口跳线查看核心板原理图即可找到
//      如果是使用 USB-TTL 模块连接，那么检查连线是否正常是否松动，模块 TX 是否连接的核心板的 RX，模块 RX 是否连接的核心板的 TX
// 问题2：串口数据乱码
//      查看串口助手设置的波特率是否与程序设置一致，程序中 zf_common_debug.h 文件中 DEBUG_UART_BAUDRATE 宏定义为 debug uart 使用的串口波特率