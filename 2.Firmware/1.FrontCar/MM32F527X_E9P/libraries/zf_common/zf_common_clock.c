/*********************************************************************************************************************
* MM32F527X-E9P Opensourec Library 即（MM32F527X-E9P 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
* 
* 本文件是 MM32F527X-E9P 开源库的一部分
* 
* MM32F527X-E9P 开源库 是免费软件
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
* 文件名称          zf_common_clock
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          MDK 5.37
* 适用平台          MM32F527X_E9P
* 店铺链接          https://seekfree.taobao.com/
* 
* 修改记录
* 日期              作者                备注
* 2022-08-10        Teternal            first version
********************************************************************************************************************/

#include "zf_common_function.h"
#include "zf_common_interrupt.h"

#include "zf_common_clock.h"

uint32 system_clock = SYSTEM_CLOCK_96M;                                         // 系统时钟信息
uint32 bus_clock = SYSTEM_CLOCK_96M;                                            // 总线时钟信息

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     核心时钟恢复初始设置
// 参数说明     void
// 返回参数     void
// 使用示例     clock_reset();
// 备注信息     本函数在文件内部调用 用户不用关注 也不可修改
//-------------------------------------------------------------------------------------------------------------------
static void clock_reset (void)
{
    RCC->CR |= RCC_CR_HSION_MASK;                                               // 启用 HSI
    while(RCC_CR_HSIRDY_MASK != (RCC->CR & RCC_CR_HSIRDY_MASK))                 // 等待 HSI 稳定
    {
        __NOP();
    }
    RCC->CFGR = RCC_CFGR_SW(0u);                                                // 复位其他时钟源并切换到 HSI
    while(RCC_CFGR_SWS(0u) != (RCC->CFGR & RCC_CFGR_SWS_MASK))                  // 等待 SYSCLK 切换到 HSI
    {
        __NOP();
    }

    RCC->CR = RCC_CR_HSION_MASK;                                                // 重置所有其他时钟源 启用 HSI
    RCC->CR |= RCC_CR_HSELPFSEL_MASK | RCC_CR_HSEDR(1);                         // 启用 HSE LPF 滤波后输出

    RCC->CIR = RCC->CIR;                                                        // 清除挂起位
    RCC->CIR = 0u;                                                              // 禁用所有中断并清除挂起位
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     核心时钟设置
// 参数说明     clock       时钟频率 推荐使用 zf_common_clock.h 中 system_clock_enum 定义的选项
// 返回参数     void
// 使用示例     clock_set_freq(clock);
// 备注信息     本函数在文件内部调用 用户不用关注 也不可修改
//-------------------------------------------------------------------------------------------------------------------
static void clock_set_freq (uint32 clock)
{
    volatile uint32 hse_status = 0;
    volatile uint32 temp_value = 0;
    volatile uint32 register_value = 0;
    system_clock = clock;                                                       // 记录核心时钟频率

    // ============================ PWR CORE POWER INIT  ============================
    RCC->APB1ENR |= RCC_APB1ENR_PWRDBG(1);                                      // 使能 PWR/DBG 时钟
    if(clock > SYSTEM_CLOCK_96M)
    {
        PWR->CR1 = (PWR->CR1 & ~PWR_CR1_VOS_MASK) | PWR_CR1_VOS(3u);            // 1.7V
    }
    else if(clock > SYSTEM_CLOCK_72M)
    {
        PWR->CR1 = (PWR->CR1 & ~PWR_CR1_VOS_MASK) | PWR_CR1_VOS(2u);            // 1.65V
    }
    else
    {
        PWR->CR1 = (PWR->CR1 & ~PWR_CR1_VOS_MASK) | PWR_CR1_VOS(1u);            // 1.6V
    }
    // ============================ PWR CORE POWER INIT  ============================

    // ================================== HSE INIT ==================================
    RCC->CR |= RCC_CR_HSEON(1);                                                 // 设置 HSEON[16] = 1 使能高速外部晶体振荡器
    do{
        hse_status = RCC_CR_HSERDY_MASK & (RCC->CR & RCC_CR_HSERDY_MASK);       // 获取高速外部晶体振荡器状态
        temp_value ++;                                                          // 超时计数
    }while((!hse_status) && (XTAL_STARTUP_TIMEOUT != temp_value));              // 高速外部晶体振荡器已稳定或者超时退出

    if (!(RCC->CR & RCC_CR_HSERDY_MASK))                                        // 外部晶振不稳定或缺失 时钟设置失败
    {
        while(1);
    }
    // ================================== HSE INIT ==================================

    // ============================ USB 48MHz PLL2 INIT  ============================
    register_value = RCC->PLL2CFGR;
    register_value &= ~(RCC_PLL2CFGR_PLL2SRC(1) | RCC_PLL2CFGR_PLL2XTPRE(1));   // 清空 [1:0] = 00 HSI 时钟用作 PLL2 输入时钟 HSE 不分频
    register_value |= (RCC_PLL2CFGR_PLL2SRC(1) | RCC_PLL2CFGR_PLL2XTPRE(0));    // 设置 [1:0] = 01 HSE 时钟用作 PLL2 输入时钟 HSE 不分频
    if(8000000 > BOARD_XTAL_FREQ)
    {
        register_value &= ~(RCC_PLL2CFGR_PLL2ICTRL_MASK);
        register_value |= RCC_PLL2CFGR_PLL2ICTRL(1);                            // 低于 8MHz 晶振输入 电荷泵电流控制信号推荐 2'b01
    }
    else
    {
        register_value &= ~(RCC_PLL2CFGR_PLL2ICTRL_MASK);
        register_value |= RCC_PLL2CFGR_PLL2ICTRL(3);                            // 高于 8MHz 晶振输入 电荷泵电流控制信号推荐 2'b11
    }
    register_value |= RCC_PLL2CFGR_PLL2LDS(7);                                  // 推荐设置 3'b111 PLL2 锁定检测器低精度
    temp_value = func_get_greatest_common_divisor(48000000, SYSTEM_CLOCK_XTAL); // 获取 USB 48<MHz 与晶振频率的最大公约数
    register_value &= ~(RCC_PLL2CFGR_PLL2DIV(7) | RCC_PLL2CFGR_PLL2MUL(255));   // 清空 PLL2DIV[10:8] PLL 分频系数 PLL2MUL[22:16] PLL 倍频系数
    register_value |= ((uint32)(SYSTEM_CLOCK_XTAL / temp_value - 1) << 8);      // 计算并写入 PLL2 分频系数
    register_value |= ((uint32)(48000000 / temp_value - 1) << 16);              // 计算并写入 PLL2 倍频系数
    RCC->PLL2CFGR = register_value;

    RCC->CR |= RCC_CR_PLL2ON(1);                                                // 使能 PLL2 倍频
    temp_value = 0;
    do{
        hse_status = RCC->CR & RCC_CR_PLL2RDY_MASK;
        temp_value ++;                                                          // 超时计数
    }while((!hse_status) && (XTAL_STARTUP_TIMEOUT != temp_value));              // 等待 PLL2 稳定或者超时退出
    if(XTAL_STARTUP_TIMEOUT == temp_value)
    {
        while(1);                                                               // PLL2 不稳定 时钟设置失败
    }
    // ============================ USB 48MHz PLL2 INIT  ============================

    // ============================== SYSTEM PLL1 INIT ==============================
    register_value = RCC->PLL1CFGR;
    register_value &= ~(RCC_PLL1CFGR_PLL1SRC(1) | RCC_PLL1CFGR_PLL1XTPRE(1));   // 清空 [1:0] = 00 HSI 时钟用作 PLL1 输入时钟 HSE 不分频
    register_value |= (RCC_PLL1CFGR_PLL1SRC(1) | RCC_PLL1CFGR_PLL1XTPRE(0));    // 设置 [1:0] = 01 HSE 时钟用作 PLL1 输入时钟 HSE 不分频
    if(8000000 > BOARD_XTAL_FREQ)
    {
        register_value &= ~(RCC_PLL1CFGR_PLL1ICTRL_MASK);
        register_value |= RCC_PLL1CFGR_PLL1ICTRL(1);                            // 低于 8MHz 晶振输入 电荷泵电流控制信号推荐 2'b01
    }
    else
    {
        register_value &= ~(RCC_PLL1CFGR_PLL1ICTRL_MASK);
        register_value |= RCC_PLL1CFGR_PLL1ICTRL(3);                            // 高于 8MHz 晶振输入 电荷泵电流控制信号推荐 2'b11
    }
    register_value |= RCC_PLL1CFGR_PLL1LDS(7);                                  // 推荐设置 3'b111 PLL1 锁定检测器低精度
    temp_value = func_get_greatest_common_divisor(clock, SYSTEM_CLOCK_XTAL);    // 获取目标时钟与晶振频率的最大公约数
    register_value &= ~(RCC_PLL1CFGR_PLL1DIV(7) | RCC_PLL1CFGR_PLL1MUL(255));   // 清空 PLL2DIV[10:8] PLL 分频系数 PLL2MUL[22:16] PLL 倍频系数
    register_value |= ((uint32)(SYSTEM_CLOCK_XTAL / temp_value - 1) << 8);      // 计算并写入 PLL 分频系数
    register_value |= ((uint32)(clock / temp_value - 1) << 16);                 // 计算并写入 PLL 倍频系数
    RCC->PLL1CFGR = register_value;

    RCC->CR |= RCC_CR_PLL1ON(1);                                                // 使能 PLL1 倍频
    temp_value = 0;
    do{
        hse_status = RCC->CR & RCC_CR_PLL1RDY_MASK;
        temp_value ++;                                                          // 超时计数
    }while((!hse_status) && (XTAL_STARTUP_TIMEOUT != temp_value));              // 等待 PLL1 稳定或者超时退出
    if(XTAL_STARTUP_TIMEOUT == temp_value)
    {
        while(1);                                                               // PLL1 不稳定 时钟设置失败
    }
    register_value = RCC->CFGR;
    if(clock > SYSTEM_CLOCK_120M)                                               // 如果时钟频率超过 120Mhz 就需要分频
    {
        register_value &= ~(RCC_CFGR_HPRE_MASK);
        register_value |= RCC_CFGR_HPRE(8);                                     // AHB 2 分频 AHB_CLK = SYSTEM_CLK / 2
        bus_clock = system_clock / 2;                                           // 记录总线时钟频率
    }
    else
    {
        register_value &= ~(RCC_CFGR_HPRE_MASK);
        register_value |= RCC_CFGR_HPRE(0);                                     // AHB 不分频 AHB_CLK = SYSTEM_CLK
        bus_clock = system_clock;                                               // 记录总线时钟频率
    }
    register_value &= ~(RCC_CFGR_PPRE1_MASK);                                   // APB1 不分频 APB1_CLK = AHB_CKL
    register_value &= ~(RCC_CFGR_PPRE2_MASK);                                   // APB2 不分频 APB2_CLK = AHB_CKL
    RCC->CFGR = register_value;
    // ============================== SYSTEM PLL1 INIT ==============================

    // =============================== FLASH ACR INIT ===============================
    FLASH->ACR &= ~(FLASH_ACR_LATENCY_MASK);                                    // 清空 Flash 时延
    FLASH->ACR |= FLASH_ACR_PRFTBE(clock <= 24000000);                          // 启用预取缓冲区
    FLASH->ACR |= (((clock - 1) / 24000000) & 0x00000007);                      // 计算并设置 Latency 时延
    // =============================== FLASH ACR INIT ===============================

    // =============================== ADC CLOCK INIT ===============================
    // 计算 ADC1 预分频 ADC 时钟频率最高 48MHZ 同时时钟分频要求为偶数
    temp_value = ((0 == (bus_clock % 48000000)) ? (bus_clock / 48000000) : (bus_clock / 48000000 + 1));
    temp_value = ((temp_value % 2 == 1) ? (temp_value + 1) : (temp_value));
    temp_value = ((2 < temp_value) ? (temp_value - 2) : (0));
    RCC->ADC1CFGR |= RCC_ADC1CFGR_PRE(temp_value);

    // 计算 ADC2 校准时钟预分频 ADC 校准时钟频率最高 1.5MHZ 同时时钟分频要求为偶数
    temp_value = ((0 == (bus_clock % 1500000)) ? (bus_clock / 1500000) : (bus_clock / 1500000 + 1));
    temp_value = ((temp_value % 2 == 1) ? (temp_value + 1) : (temp_value));
    temp_value = ((2 < temp_value) ? (temp_value - 2) : (0));
    RCC->ADC2CFGR |= RCC_ADC2CFGR_PRECAL(temp_value);
    // =============================== ADC CLOCK INIT ===============================

// 手册里虽然写了要分频到 1MHz 但 SDK 没分频 并且真的分频后会出现输出异常归零
//    // =============================== DAC CLOCK INIT ===============================
//    // 计算 DAC 预分频 DAC 时钟频率最高 1MHZ  PCLK1/(2*(n+1)) 分频后作为 DAC 时钟
//    temp_value = ((0 == (bus_clock % 1000000)) ? (bus_clock / 1000000) : (bus_clock / 1000000 + 1));
//    temp_value = temp_value / 2 - 1;
//    RCC->DACCFGR |= RCC_DACCFGR_PRE(temp_value);
//    // =============================== DAC CLOCK INIT ===============================

    // ============================= SYSTEM CLOCK INIT  =============================
    register_value = RCC->CFGR;
    register_value &= ~(RCC_CFGR_SW_MASK);                                      // 清空 SW[1:0] = 00 选择 HSI 用作系统时钟
    register_value |= RCC_CFGR_SW(2);                                           // 设置 SW[1:0] = 01 选择 PLL 输出用作系统时钟
    RCC->CFGR = register_value;
    temp_value = 0;
    do
    {
        hse_status = (RCC_CFGR_SWS(2) == (RCC->CFGR & RCC_CFGR_SWS_MASK));
        temp_value ++;                                                          // 超时计数
    }while((!hse_status) && (XTAL_STARTUP_TIMEOUT != temp_value));              // 等待 PLL1 输出用作系统时钟
    if(XTAL_STARTUP_TIMEOUT == temp_value)
    {
        while(1);                                                               // 系统时钟设置失败
    }
    // ============================= SYSTEM CLOCK INIT  =============================
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     核心时钟初始化
// 参数说明     clock       时钟频率 推荐使用 zf_common_clock.h 中 system_clock_enum 定义的选项
// 返回参数     void
// 使用示例     clock_init(SYSTEM_CLOCK_120M);                                  // 初始化核心时钟为 120MHz
// 备注信息     本函数用于将核心时钟设置到指定频率
//              当时钟 <=120MHz 时总线频率与核心频率一致
//              当时钟  >120MHz 时总线频率为核心频率的二分频
//-------------------------------------------------------------------------------------------------------------------
void clock_init (uint32 clock)
{
    clock_reset();
    clock_set_freq(clock);
    interrupt_init();
}
