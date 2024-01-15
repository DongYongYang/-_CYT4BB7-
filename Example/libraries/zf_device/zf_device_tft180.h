/*********************************************************************************************************************
* CYT4BB Opensourec Library ���� CYT4BB ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
* Copyright (c) 2022 SEEKFREE ��ɿƼ�
*
* ���ļ��� CYT4BB ��Դ���һ����
*
* CYT4BB ��Դ�� ���������
* �����Ը���������������ᷢ���� GPL��GNU General Public License���� GNUͨ�ù�������֤��������
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
* ����Դ��ʹ�� GPL3.0 ��Դ����֤Э�� ������������Ϊ���İ汾
* ��������Ӣ�İ��� libraries/doc �ļ����µ� GPL3_permission_statement.txt �ļ���
* ����֤������ libraries �ļ����� �����ļ����µ� LICENSE �ļ�
* ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
*
* �ļ�����          zf_device_tft180
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          IAR 9.40.1
* ����ƽ̨          CYT4BB
* ��������          https://seekfree.taobao.com/
*
* �޸ļ�¼
* ����              ����                ��ע
* 2024-01-12       pudding           first version
********************************************************************************************************************/
/*********************************************************************************************************************
* ���߶��壺
*                  ------------------------------------
*                  ģ��ܽ�              ��Ƭ���ܽ�
*                  SCL                 �鿴 zf_device_tft180.h �� TFT180_SCL_PIN �궨��
*                  SDA                 �鿴 zf_device_tft180.h �� TFT180_SDA_PIN �궨��
*                  RES                 �鿴 zf_device_tft180.h �� TFT180_RES_PIN �궨��
*                  DC                  �鿴 zf_device_tft180.h �� TFT180_DC_PIN �궨��
*                  CS                  �鿴 zf_device_tft180.h �� TFT180_CS_PIN �궨��
*                  BL                  �鿴 zf_device_tft180.h �� TFT180_BL_PIN �궨��
*                  VCC                 3.3V��Դ
*                  GND                 ��Դ��
*                  ���ֱ���160*128
*                  ------------------------------------
********************************************************************************************************************/

#ifndef _zf_device_tft180_h_
#define _zf_device_tft180_h_

#include "zf_common_typedef.h"

//=================================================���� TFT180 ��������================================================
#define TFT180_USE_SOFT_SPI             (0)                                     // Ĭ��ʹ��Ӳ�� SPI ��ʽ���� ����ʹ��Ӳ�� SPI ��ʽ����
#if TFT180_USE_SOFT_SPI                                                         // ������ ��ɫ�����Ĳ�����ȷ�� ��ɫ�ҵľ���û���õ�
//====================================================���� SPI ����====================================================
#define TFT180_SOFT_SPI_DELAY           (0 )                                    // ���� SPI ��ʱ����ʱ���� ��ֵԽС SPI ͨ������Խ��
#define TFT180_SCL_PIN                  (P12_2)                                 // ���� SPI SCK ����
#define TFT180_SDA_PIN                  (P12_1)                                 // ���� SPI MOSI ����
//====================================================���� SPI ����====================================================
#else
//====================================================Ӳ�� SPI ����====================================================
#define TFT180_SPI_SPEED                (30*1000*1000	)                       // Ӳ�� SPI ����
#define TFT180_SPI                      (SPI_1			)                       // Ӳ�� SPI ��
#define TFT180_SCL_PIN                  (SPI1_CLK_P12_2	)                       // Ӳ�� SPI SCK ����
#define TFT180_SDA_PIN                  (SPI1_MOSI_P12_1)                       // Ӳ�� SPI MOSI ����
#define TFT180_SDA_PIN_IN               (SPI_MISO_NULL	)                       // ����SPI_MISO����  TFTû��MISO���ţ�����������Ȼ��Ҫ���壬��spi�ĳ�ʼ��ʱ��Ҫʹ��
//====================================================Ӳ�� SPI ����====================================================
#endif

#define TFT180_RES_PIN                  (P22_4)                                 // Һ����λ���Ŷ���
#define TFT180_DC_PIN                   (P22_3)                                 // Һ������λ���Ŷ���
#define TFT180_CS_PIN                   (P12_3)                                 // CS Ƭѡ����
#define TFT180_BL_PIN                   (P12_0)                                 // Һ���������Ŷ���

#define TFT180_DEFAULT_DISPLAY_DIR      (TFT180_PORTAIT)                        // Ĭ�ϵ���ʾ����
#define TFT180_DEFAULT_PENCOLOR         (RGB565_RED)                            // Ĭ�ϵĻ�����ɫ
#define TFT180_DEFAULT_BGCOLOR          (RGB565_WHITE)                          // Ĭ�ϵı�����ɫ
#define TFT180_DEFAULT_DISPLAY_FONT     (TFT180_8X16_FONT)                      // Ĭ�ϵ�����ģʽ

#define TFT180_DC(x)                    ((x) ? (gpio_high(TFT180_DC_PIN))  : (gpio_low(TFT180_DC_PIN)))
#define TFT180_RST(x)                   ((x) ? (gpio_high(TFT180_RES_PIN)) : (gpio_low(TFT180_RES_PIN)))
#define TFT180_CS(x)                    ((x) ? (gpio_high(TFT180_CS_PIN))  : (gpio_low(TFT180_CS_PIN)))
#define TFT180_BLK(x)                   ((x) ? (gpio_high(TFT180_BL_PIN))  : (gpio_low(TFT180_BL_PIN)))
//=================================================���� TFT180 ��������================================================


//=================================================���� TFT180 �����ṹ��===============================================
typedef enum
{
    TFT180_PORTAIT                      = 0,                                    // ����ģʽ
    TFT180_PORTAIT_180                  = 1,                                    // ����ģʽ  ��ת180
    TFT180_CROSSWISE                    = 2,                                    // ����ģʽ
    TFT180_CROSSWISE_180                = 3,                                    // ����ģʽ  ��ת180
}tft180_dir_enum;

typedef enum
{
    TFT180_6X8_FONT                     = 0,                                    // 6x8      ����
    TFT180_8X16_FONT                    = 1,                                    // 8x16     ����
    TFT180_16X16_FONT                   = 2,                                    // 16x16    ���� Ŀǰ��֧��
}tft180_font_size_enum;

extern  uint16  tft180_width_max ;
extern  uint16  tft180_height_max;

//=================================================���� TFT180 �����ṹ��===============================================

//=================================================���� TFT180 ��������================================================
void    tft180_clear                    (void);                                                                               // TFT180 ��������
void    tft180_full                     (const uint16 color);                                                                 // TFT180 ��Ļ��亯��
void    tft180_set_dir                  (tft180_dir_enum dir);                                                                // TFT180 ������ʾ����
void    tft180_set_font                 (tft180_font_size_enum font);                                                         // TFT180 ������ʾ����
void    tft180_set_color                (const uint16 pen, const  uint16 bgcolor);                                            // TFT180 ������ʾ��ɫ
void    tft180_draw_point               (uint16 x, uint16 y, const uint16 color);                                             // TFT180 ���㺯��
void    tft180_draw_line                (uint16 x_start, uint16 y_start, uint16 x_end, uint16 y_end, const uint16 color);     // TFT180 ���ߺ���

void    tft180_show_char                (uint16 x, uint16 y, const char dat);                                                 // TFT180 ��ʾ�ַ�
void    tft180_show_string              (uint16 x, uint16 y, const char dat[]);                                               // TFT180 ��ʾ�ַ���
void    tft180_show_int                 (uint16 x,uint16 y, const int32 dat, uint8 num);                                      // TFT180 ��ʾ32λ�з��� (ȥ������������Ч��0)
void    tft180_show_uint                (uint16 x,uint16 y, const uint32 dat, uint8 num);                                     // TFT180 ��ʾ32λ�޷��� (ȥ������������Ч��0)
void    tft180_show_float               (uint16 x, uint16 y, const double dat, uint8 num, uint8 pointnum);

void    tft180_show_binary_image        (uint16 x, uint16 y, const uint8 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height);                    // TFT180 ��ʾ��ֵͼ�� ����ÿ�˸������һ���ֽ�����
void    tft180_show_gray_image          (uint16 x, uint16 y, const uint8 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height, uint8 threshold);   // TFT180 ��ʾ 8bit �Ҷ�ͼ�� ����ֵ����ֵ
void    tft180_show_rgb565_image        (uint16 x, uint16 y, const uint16 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height, uint8 color_mode); // TFT180 ��ʾ RGB565 ��ɫͼ��

void    tft180_show_wave                (uint16 x, uint16 y, const uint16 *wave, uint16 width, uint16 value_max, uint16 dis_width, uint16 dis_value_max);              // TFT180 ��ʾ����
void    tft180_show_chinese             (uint16 x, uint16 y, uint8 size, const uint8 *chinese_buffer, uint8 number, const uint16 color);                               // TFT180 ������ʾ
                                                                                                                              // 1.8��TFT��Ļ��ʼ��
void    tft180_init                     (void);
//=================================================���� TFT180 ��������================================================


//=================================================���� TFT180 ��չ����================================================
//-------------------------------------------------------------------------------------------------------------------
// �������     TFT180 ��ʾС���ͼ��
// ����˵��     p               ͼ������ָ��
// ����˵��     width           ͼ��ʵ�ʿ���
// ����˵��     height          ͼ��ʵ�ʸ߶�
// ���ز���     void
// ʹ��ʾ��     tft180_displayimage7725(ov7725_image_binary[0], OV7725_W, OV7725_H);
// ��ע��Ϣ     ��չ��һ����ʾ������Ĭ�������ţ�����Ļ������ʼ�㿪ʼ��ʾ
//-------------------------------------------------------------------------------------------------------------------
#define tft180_displayimage7725(p, width, height)       (tft180_show_binary_image(0, 0, (p), OV7725_W, OV7725_H, (width), (height)))
//-------------------------------------------------------------------------------------------------------------------
// �������     TFT180 ��ʾ�����ͼ��
// ����˵��     p               ͼ������ָ��
// ����˵��     width           ͼ��ʵ�ʿ���
// ����˵��     height          ͼ��ʵ�ʸ߶�
// ���ز���     void
// ʹ��ʾ��     tft180_displayimage03x(mt9v03x_image[0], MT9V03X_W, MT9V03X_H);
// ��ע��Ϣ     ��չ��һ����ʾ������Ĭ�������ţ�����Ļ������ʼ�㿪ʼ��ʾ
//-------------------------------------------------------------------------------------------------------------------
#define tft180_displayimage03x(p, width, height)        (tft180_show_gray_image(0, 0, (p), MT9V03X_W, MT9V03X_H, (width), (height), 0))
//-------------------------------------------------------------------------------------------------------------------
// �������     TFT180 ��ʾ��ͫͼ��
// ����˵��     p               ͼ������ָ��
// ����˵��     width           ͼ��ʵ�ʿ���
// ����˵��     height          ͼ��ʵ�ʸ߶�
// ���ز���     void
// ʹ��ʾ��     tft180_displayimage8660(scc8660_image[0], SCC8660_W, SCC8660_H);
// ��ע��Ϣ     ��չ��һ����ʾ������Ĭ�������ţ�����Ļ������ʼ�㿪ʼ��ʾ
//-------------------------------------------------------------------------------------------------------------------
#define tft180_displayimage8660(p, width, height)       (tft180_show_rgb565_image(0, 0, (p), SCC8660_W, SCC8660_H, (width), (height), 1))
//=================================================���� TFT180 ��չ����================================================


#endif