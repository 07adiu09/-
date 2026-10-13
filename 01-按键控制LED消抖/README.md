# 01 - 按键控制 LED 亮灭（软件消抖）

## 功能

按下按键一次，LED 的亮灭状态翻转一次。

## 硬件连接

| 器件 | 引脚 | 模式 | 说明 |
|---|---|---|---|
| LED | PB10 | 推挽输出 | 低电平点亮 |
| 按键 | PB11 | 上拉输入 | 按下时为低电平 |

## 实现思路

程序在 `while(1)` 中不断轮询按键状态，检测到有效按键后翻转 LED：

```c
Key_Init();
LED_Init();
GPIO_SetBits(GPIOB, GPIO_Pin_10);   // 上电先熄灭 LED

while (1)
{
    if (Key_GetFlag() == 1)         // 检测到有效按键
    {
        LED_Turn();                 // 翻转 LED 状态
    }
}
```

## 消抖处理

机械按键在按下和松开的瞬间会产生 5~10ms 的电平抖动。如果不处理，一次按下会被程序识别成多次，LED 会连续翻转，看起来像"失灵"。

这里采用的是**软件延时消抖**：

```c
uint8_t Key_GetFlag(void)
{
    uint8_t Flag = 0;
    if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0)      // 检测到按下
    {
        Delay_ms(10);                                         // 延时 10ms 躲过抖动
        while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0);  // 等待松手
        Delay_ms(10);                                         // 松手后再延时 10ms
        Flag = 1;
    }
    return Flag;
}
```

两次 `Delay_ms(10)` 分别过滤掉**按下抖动**和**松开抖动**，中间的 `while` 循环等待按键松开，保证一次按下只触发一次翻转。

## 文件说明

| 文件 | 作用 |
|---|---|
| `main.c` | 主程序，轮询按键并翻转 LED |
| `Key.c` / `Key.h` | 按键初始化与消抖检测 |
| `LED.c` / `LED.h` | LED 初始化与状态翻转 |
| `Delay.c` / `Delay.h` | 基于 SysTick 的微秒/毫秒级延时 |
