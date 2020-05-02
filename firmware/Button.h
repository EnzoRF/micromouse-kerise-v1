/*
 * Button.h
 *
 *  Created on: 2016/10/26
 *      Author: kerikun11
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#define PRESS_LEVEL 2
#define LONG_PRESS_LEVEL1  40
#define LONG_PRESS_LEVEL2  200
#define LONG_PRESS_LEVEL3  1000

class Button {
public:
	/** Constructor.
	 @param button_pin �{�^�������t����s��
	 @param pressed_state ���_�������_������ݒ�D
	 @param pin_mode �v���A�b�v�Ȃ�
	 */
	Button(PinName button_pin, int pressed_state = 0, PinMode pin_mode = PullUp) :
			pin(button_pin, pin_mode), pressedState(pressed_state) {
		flags = 0x00;
	}

	~Button() {
		ticker.detach();
	}

	/** �{�^���̏�ԃt���O.
	 ��Ԃ�ǂݎ������t���O���N���A���邱�ƁD
	 */
	union {
		volatile uint8_t flags; /**< �t���O�ɂ܂Ƃ߂ăA�N�Z�X */
		struct {
			volatile uint8_t pressed :1; /**< �{�^���������ꂽ */
			volatile uint8_t long_pressed_1 :1; /**< �{�^�������������ꂽ */
			volatile uint8_t long_pressed_2 :1; /**< �{�^���������ƒ��������ꂽ */
			volatile uint8_t long_pressed_3 :1; /**< �{�^���������Ƃ����ƒ��������ꂽ */
			volatile uint8_t pressing :1; /**< �{�^����������Ă��� */
			volatile uint8_t long_pressing_1 :1; /**< �{�^��������������Ă��� */
			volatile uint8_t long_pressing_2 :1; /**< �{�^���������ƒ���������Ă��� */
			volatile uint8_t long_pressing_3 :1; /**< �{�^���������Ƃ����ƒ���������Ă��� */
		};
	};

	/** �{�^���������֐�.
	 �^�C�}�[���荞�݂��A�^�b�`����D�n�߂ɕK�����s���邱�ƁD
	 */
	void init() {
		ticker.attach_us(this, &Button::timerIsr, 10000);
	}
private:
	DigitalIn pin;
	int pressedState;
	Ticker ticker;
	volatile int counter;

	void timerIsr() {
		if (pin == pressedState) {
			if (counter < LONG_PRESS_LEVEL3 + 1)
				counter++;
			if (counter == LONG_PRESS_LEVEL3)
				long_pressing_3 = 1;
			if (counter == LONG_PRESS_LEVEL2)
				long_pressing_2 = 1;
			if (counter == LONG_PRESS_LEVEL1)
				long_pressing_1 = 1;
			if (counter == PRESS_LEVEL)
				pressing = 1;
		} else {
			if (counter >= LONG_PRESS_LEVEL3)
				long_pressed_3 = 1;
			else if (counter >= LONG_PRESS_LEVEL2)
				long_pressed_2 = 1;
			else if (counter >= LONG_PRESS_LEVEL1)
				long_pressed_1 = 1;
			else if (counter >= PRESS_LEVEL)
				pressed = 1;
			counter = 0;
			flags &= 0x0F;
		}
	}
};

#endif /* BUTTON_H_ */
