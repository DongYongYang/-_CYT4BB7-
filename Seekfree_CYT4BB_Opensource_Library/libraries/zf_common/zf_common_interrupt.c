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
* 文件名称          zf_common_interrupt
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

#include "cmsis_compiler.h"
#include "zf_common_interrupt.h"
#include "zf_driver_pwm.h"

static vuint32 interrupt_global_flag = 0;
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     全局中断使能
// 参数说明     void
// 返回参数     void
// 使用示例     interrupt_global_enable(1);
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
void interrupt_global_enable (uint32 primask)
{
    if(primask == 0)
    {
        __enable_irq();
    }
    interrupt_global_flag ++;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     全局中断屏蔽
// 参数说明     void
// 返回参数     void
// 使用示例     uint32 interrupt_num = interrupt_global_disable();
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
uint32 interrupt_global_disable (void)
{
    __disable_irq();
    if(interrupt_global_flag > 0) interrupt_global_flag --;
    return interrupt_global_flag; 
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     断言中断配置
// 参数说明     void
// 返回参数     void
// 使用示例     assert_interrupt_config();
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
void assert_interrupt_config (void)
{
    interrupt_global_disable();                 // 全局中断失能
    pwm_all_channel_close();                    // 关闭PWM所有通道输出
}
