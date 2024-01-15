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
// 核心板正常供电即可 无需额外连接


// *************************** 例程测试说明 ***************************
// 1.核心板烧录完成本例程，完成上电
// 2.使用万用表检测 PWM_CHx 对应的通道，会看到电压变化
// 2.使用示波器检测 PWM_CHx 对应的通道，会看到脉宽变化
// 如果发现现象与说明严重不符 请参照本文件最下方 例程常见问题说明 进行排查

// **************************** 代码区域 ****************************

#define CHANNEL_NUMBER          (4)

#define PWM_CH1                 (TCPWM_CH24_P9_0)
#define PWM_CH2                 (TCPWM_CH25_P9_1)
#define PWM_CH3                 (TCPWM_CH30_P10_2)
#define PWM_CH4                 (TCPWM_CH31_P10_3)

int16 duty = 0;
int16 duty_temp = 0;
uint8 channel_index = 0;
pwm_channel_enum channel_list[CHANNEL_NUMBER] = {PWM_CH1, PWM_CH2, PWM_CH3, PWM_CH4};


int main(void)
{
    clock_init(SYSTEM_CLOCK_250M); 	// 时钟配置及系统初始化<务必保留>
    debug_init();			// 初始化默认调试串口
    // 此处编写用户代码 例如外设初始化代码等

    pwm_init(PWM_CH1, 17000, 0);                                                // 初始化 PWM 通道 频率 17KHz 初始占空比 0%
    pwm_init(PWM_CH2, 17000, 0);                                                // 初始化 PWM 通道 频率 17KHz 初始占空比 0%
    pwm_init(PWM_CH3, 17000, 0);                                                // 初始化 PWM 通道 频率 17KHz 初始占空比 0%
    pwm_init(PWM_CH4, 17000, 0);                                                // 初始化 PWM 通道 频率 17KHz 初始占空比 0%
    
    
    // 此处编写用户代码 例如外设初始化代码等
    while(true)
    {
        // 此处编写需要循环执行的代码
      
        for(duty = 0; duty <= PWM_DUTY_MAX / 2; duty ++)                        // 输出占空比递增到 50%
        {
			// 呼吸流水灯
            for(channel_index = 0; channel_index < CHANNEL_NUMBER; channel_index++) 
            {
                duty_temp = (duty + channel_index * PWM_DUTY_MAX / 8) % (PWM_DUTY_MAX / 2) + (PWM_DUTY_MAX / 2); 
                pwm_set_duty(channel_list[channel_index], duty_temp);           // 更新对应通道占空比
            }
            system_delay_us(200);
        }
        
        // 此处编写需要循环执行的代码
    }
}

// **************************** 代码区域 ****************************

// *************************** 例程常见问题说明 ***************************
// 遇到问题时请按照以下问题检查列表检查
// 问题1：串口没有数据
//      查看串口助手打开的是否是正确的串口，检查打开的 COM 口是否对应的是调试下载器或者 USB-TTL 模块的 COM 口
//      如果是使用逐飞科技 CMSIS-DAP 调试下载器连接，那么检查下载器线是否松动，检查核心板串口跳线是否已经焊接，串口跳线查看核心板原理图即可找到
//      如果是使用 USB-TTL 模块连接，那么检查连线是否正常是否松动，模块 TX 是否连接的核心板的 RX，模块 RX 是否连接的核心板的 TX
// 问题2：串口数据乱码
//      查看串口助手设置的波特率是否与程序设置一致，程序中 zf_common_debug.h 文件中 DEBUG_UART_BAUDRATE 宏定义为 debug uart 使用的串口波特率
// 问题3：显示数值与接入电压相差过大
//      检查信号引脚是否接对，信号线是否松动
//      使用万用表测量实际引脚上电压是多少 然后按照 voltage/3V3*256 计算
