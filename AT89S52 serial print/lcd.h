#ifndef _LCD_H
#define _LCD_H

#define clear_display 	0x01
#define return_home   	0x02
#define entry_mode    	0x04
#define display_control	0x08
#define display_shift   0x10
#define function_set    0x20
#define cgram_address   0x40

#define shift_enable	(entry_mode | (1 << 0))
#define shift_disable   (entry_mode &~(1 << 0))
#define cur_increment   (entry_mode | (1 << 1))
#define cur_decrement   (entry_mode &~(1 << 1))

#define display_on 	(display_control | (1 << 2))
#define display_off	(display_control &~(1 << 2))
#define cursor_on	(display_on | (1 << 1))
#define cursor_off	(display_on &~(1 << 1))
#define blink_on	(display_on | (1 << 0))
#define blink_off	(display_on &~(1 << 0))

#define entire_line		(display_shift &~(1 << 3))
#define current_line	(display_shift | (1 << 3))
#define shift_left		(display_sshit &~(1 << 2))
#define shift_right		(display_shift | (1 << 2))

#define eight_bit	(function_set | (1 << 4))
#define four_bit 	(function_set &~(1 << 4))
#define two_line	(function_set | (1 << 3))
#define one_line	(function_set &~(1 << 3))
#define char_set1	(function_set | (1 << 2))
#define char_set2	(function_set &~(1 << 2))

#define first_line	0x80
#define second_line 0xC0
#define third_line  0x94
#define fourth_line 0xD4

extern void lcd_initialize(void);
extern void lcd_command(unsigned char command);
extern void lcd_function(unsigned char command);

extern void lcd_write(unsigned char command, unsigned char data1);
extern void lcd_writeln(unsigned char command, const char *data1, unsigned char length);
extern void lcd_disp(unsigned char command, const char *data1);

//extern void lcd_decimal(unsigned char command, unsigned long data1, int length, int base);
//extern void lcd_float(unsigned char command, float data1, int postfix, int prefix); 

//extern void lcd_custom(unsigned char location, const char *data1);
//extern void lcd_char(unsigned char command, unsigned char location, const char *data1);
extern void lcd_allort(unsigned char data1);
extern void lcd_enable(void);
#endif	