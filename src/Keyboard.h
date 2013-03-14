/*
 * Keyboard.h
 *
 *  Created on: Mar 14, 2013
 *      Author: Tyler
 */

#ifndef KEYBOARD_H_
#define KEYBOARD_H_

namespace ts {

enum Key{
	a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, keyCount
};

class Keyboard {
public:

	void setKey(Key key, bool value);

private:
	Keyboard();
	Keyboard(const Keyboard &);
	Keyboard& operator=(Keyboard const& copy);

	Key keys[keyCount];

	virtual ~Keyboard();
};

} /* namespace ts */
#endif /* KEYBOARD_H_ */
