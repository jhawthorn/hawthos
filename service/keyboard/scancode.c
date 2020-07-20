#include "keyboard.h"

#include "scancode.h"

char convert_scancode(uint8_t scancode) {
	return scancode_to_ascii[scancode];
}
