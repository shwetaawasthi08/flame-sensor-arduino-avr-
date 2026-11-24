/*
 * Flame Sensor + Buzzer + 16x2 LCD (4-bit parallel)
 * Microchip Studio, ATmega328P (Arduino Uno), 16 MHz
 *
 *   Flame sensor DO -> D2  (PD2)
 *   Buzzer          -> D7  (PD7)
 *   LED (onboard)   -> D13 (PB5)
 *   LCD RS -> D8 (PB0)   LCD E  -> D9 (PB1)
 *   LCD D4 -> A0 (PC0)   LCD D5 -> A1 (PC1)
 *   LCD D6 -> A2 (PC2)   LCD D7 -> A3 (PC3)
 */
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define LCD_RS_HIGH()  (PORTB |=  (1 << PB0))
#define LCD_RS_LOW()   (PORTB &= ~(1 << PB0))
#define LCD_E_HIGH()   (PORTB |=  (1 << PB1))
#define LCD_E_LOW()    (PORTB &= ~(1 << PB1))

#define BUZZER_ON()   (PORTD |=  (1 << PD7))
#define BUZZER_OFF()  (PORTD &= ~(1 << PD7))
#define LED_ON()      (PORTB |=  (1 << PB5))
#define LED_OFF()     (PORTB &= ~(1 << PB5))

static void lcd_nibble(uint8_t n)
{
    PORTC = (PORTC & 0xF0) | (n & 0x0F);
    LCD_E_HIGH();
    _delay_us(1);
    LCD_E_LOW();
    _delay_us(50);
}

static void lcd_send(uint8_t byte, uint8_t rs)
{
    if (rs) LCD_RS_HIGH(); else LCD_RS_LOW();
    lcd_nibble(byte >> 4);
    lcd_nibble(byte & 0x0F);
}

static void lcd_cmd(uint8_t c)  { lcd_send(c, 0); }
static void lcd_data(uint8_t d) { lcd_send(d, 1); }

static void lcd_init(void)
{
    DDRC |= 0x0F;                          /* A0-A3 outputs (D4-D7) */
    DDRB |= (1 << PB0) | (1 << PB1);       /* RS, E outputs */
    LCD_RS_LOW();
    LCD_E_LOW();

    _delay_ms(50);
    lcd_nibble(0x03); _delay_ms(5);
    lcd_nibble(0x03); _delay_us(150);
    lcd_nibble(0x03); _delay_us(150);
    lcd_nibble(0x02);                      /* 4-bit mode */
    lcd_cmd(0x28);                         /* 2 lines, 5x8 */
    lcd_cmd(0x0C);                         /* display on, cursor off */
    lcd_cmd(0x06);                         /* entry mode */
    lcd_cmd(0x01); _delay_ms(2);           /* clear */
}

static void lcd_print_line(uint8_t row, const char *s)
{
    uint8_t i = 0;
    lcd_cmd(0x80 | (row ? 0x40 : 0x00));
    while (*s && i < 16) { lcd_data(*s++); i++; }
    while (i < 16)       { lcd_data(' '); i++; }
}

int main(void)
{
    uint8_t lastState = 0xFF;

    DDRD |= (1 << PD7);        /* buzzer */
    DDRB |= (1 << PB5);        /* LED */
    DDRD &= ~(1 << PD2);       /* flame DO input */
    PORTD |= (1 << PD2);       /* pull-up */
    BUZZER_OFF();

    lcd_init();
    lcd_print_line(0, "Flame Detector");
    lcd_print_line(1, "Starting...");
    _delay_ms(1500);

    while (1) {
        uint8_t fire = (PIND & (1 << PD2)) ? 0 : 1;   /* DO LOW = fire */

        if (fire) { BUZZER_ON();  LED_ON();  }
        else      { BUZZER_OFF(); LED_OFF(); }

        if (fire != lastState) {
            if (fire) {
                lcd_print_line(0, "FIRE DETECTED!!");
                lcd_print_line(1, "Move to safety!");
            } else {
                lcd_print_line(0, "System: SAFE");
                lcd_print_line(1, "No Fire Detected");
            }
            lastState = fire;
        }
        _delay_ms(100);
    }
}
