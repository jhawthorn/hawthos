#include <stdio.h>

#include <hawthos.h>

#include "keyboard.h"

#define KEYBOARD_DATA    0x60
#define KEYBOARD_STATUS  0x64
#define KEYBOARD_COMMAND 0x64

uint8_t kbd_read_data() {
	return io_inb(KEYBOARD_DATA);
}

uint8_t kbd_read_status() {
	return io_inb(KEYBOARD_STATUS);
}

void kbd_send_cmd(uint8_t cmd) {
	io_outb(KEYBOARD_COMMAND, cmd);
}

void kbd_send_data(uint8_t data) {
	io_outb(KEYBOARD_DATA, data);
}

#define KEYBOARD_STATUS_OUTBUF 0x01
#define KEYBOARD_STATUS_INBUF  0x02

void kbd_wait_inbuf() {
	while(kbd_read_status() & KEYBOARD_STATUS_INBUF) {
		yield();
	}
}

void kbd_wait_outbuf() {
	while(!(kbd_read_status() & KEYBOARD_STATUS_OUTBUF)) {
		yield();
	}
}


void kbd_cmd0(uint8_t cmd) {
	kbd_wait_inbuf();
	kbd_send_cmd(cmd);
}

void kbd_cmd1(uint8_t cmd, uint8_t data) {
	kbd_wait_inbuf();
	kbd_send_cmd(cmd);
	kbd_wait_inbuf();
	kbd_send_data(data);
}

uint8_t kbd_read() {
	kbd_wait_outbuf();
	return kbd_read_data();
}

void kbd_dummy_read() {
	kbd_read_data();
}

#define CMD_DISABLE_KEY 0xAD
#define CMD_ENABLE_KEY  0xAE

#define CMD_DISABLE_AUX 0xA7
#define CMD_ENABLE_AUX  0xA8

#define CMD_READ_CCB    0x20
#define CMD_WRITE_CCB   0x60

#define CMD_SELF_TEST   0xAA

void restart_system() {
	kbd_cmd0(0xFe);
}

void shutdown_system() {
	io_outw(0xB004, 0x2000); /* Shutdown Bochs, old qemu */
	io_outw(0x604,  0x2000);  /* Shutdown newer qemu */
	io_outw(0x4004, 0x3400); /* Shutdown VirtualBox */

	restart_system();     /* No luck? Just reboot */
}

int main() {
	uint8_t ccb;

	kbd_dummy_read();

	kbd_cmd0(CMD_READ_CCB);
	ccb = kbd_read();

	kbd_cmd0(CMD_DISABLE_KEY);
	kbd_cmd0(CMD_DISABLE_AUX);

	kbd_cmd0(CMD_SELF_TEST);
	if (kbd_read() != 0x55) {
		printf("Keyboard self test failed\n");
		return 1;
	}
	yield();

	kbd_cmd1(CMD_WRITE_CCB, ccb);

	/* enable keyboard */
	kbd_cmd0(CMD_ENABLE_KEY);

	kbd_cmd0(CMD_READ_CCB);
	ccb = kbd_read();

	for(;;) {
		uint8_t scancode = kbd_read();
		char ascii = convert_scancode(scancode);
		if (ascii) {
			/* TESTING: shutdown if escape is pressed */
			if (ascii == 27) {
				shutdown_system();
			}

			putchar(ascii);
		}
	}

	return 0;
}
