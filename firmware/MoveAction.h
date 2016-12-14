/*
 * MoveAction.h
 *
 *  Created on: 2016/11/11
 *      Author: kerikun11
 */

#ifndef MOVEACTION_H_
#define MOVEACTION_H_

#include "mbed.h"
#include "config.h"

#define MOVE_ACTION_PERIOD			1000
#define WALL_ATTACH_ENABLED			false
#define WALL_AVOID_ENABLED			false

#define LOOK_AHEAD_UNIT				20
#define TRAJECTORY_PROP_GAIN		50
#define TRAJECTORY_INTEGRAL_GAIN	0

class Trajectory {
public:
	Trajectory(bool mirror = false) :
			mirror(mirror) {
		reset();
	}
	virtual ~Trajectory() {
	}
	void reset() {
		last_index = 0;
	}
	Position getNextDir(const Position &cur, const float velocity) {
		int look_ahead = LOOK_AHEAD_UNIT;
//		int look_ahead = LOOK_AHEAD_UNIT * 20 * (1 + 5 * velocity / v_const);
		Position dir = (getNextPoint(cur, look_ahead) - cur).rotate(-cur.theta);
		dir.theta = atan(dir.y / (dir.x + interval));
		dir *= velocity / LOOK_AHEAD_UNIT;
		return dir;
	}
	float getPortion() const {
		return (float) last_index / getSize();
	}
	void shift(Position &cur) {
		Position moved = getPosition(getSize() - 1);
		cur = (cur - moved).rotate(-moved.theta);
		cur.theta += moved.theta;
	}
protected:
	bool mirror;
	int last_index;
	const float interval = 1.0f;
	const float v_const = 1000.0f;
	virtual int size() const {
		return 180;
	}
	virtual Position position(int index) const {
		return Position(index * interval, 0, 0);
	}
	int getSize() const {
		return size();
	}
	Position getPosition(const int index) {
		if (mirror) {
			return position(index).mirror_x();
		} else {
			return position(index);
		}
	}
	Position getNextPoint(const Position& pos, int look_ahead) {
		for (int i = last_index; i < 180 * 32; i++) {
			Position target = getPosition(i);
			Position dir = (target - pos).rotate(-target.theta);
			if (dir.x > 0) {
				last_index = i;
				return getPosition(last_index + 1 + look_ahead);
			}
		}
		return Position(0, 0, 0);
	}
}
;

class Curve90: public Trajectory {
public:
	Curve90(bool mirror = false) :
			Trajectory(mirror) {
	}
private:
	virtual int size() const {
		return 152;
	}
	virtual Position position(int index) const {
		static const float data[][3] = { { 0, 0, 0 }, { 1, 0, 0 }, { 2, 0, 0 }, { 3, 0, 0 }, { 4, 0,
				0 }, { 5, 0, 0 }, { 6, 0, 0 }, { 7, 0, 0 }, { 8, 0, 0 }, { 9.8969, 0, 0 }, { 10.897,
				0, 0 }, { 11.897, 0, 0 }, { 12.897, 0.00060392, 0.00060392 }, { 13.897, 0.0024157,
				0.0018118 }, { 14.897, 0.0060392, 0.0036235 }, { 15.897, 0.012078, 0.0060392 }, {
				16.897, 0.021137, 0.0090588 }, { 17.897, 0.033819, 0.012682 }, { 18.897, 0.050728,
				0.01691 }, { 19.896, 0.072467, 0.021741 }, { 20.896, 0.09964, 0.027176 }, { 21.895,
				0.13285, 0.033216 }, { 22.895, 0.1727, 0.039859 }, { 23.894, 0.21979, 0.047106 }, {
				24.892, 0.27472, 0.054957 }, { 25.89, 0.33808, 0.063412 }, { 26.887, 0.41049,
				0.07247 }, { 27.884, 0.49253, 0.082133 }, { 28.88, 0.5848, 0.0924 }, { 29.874,
				0.68789, 0.10327 }, { 30.868, 0.80238, 0.11474 }, { 31.86, 0.92886, 0.12682 }, {
				32.85, 1.0679, 0.13951 }, { 33.838, 1.2201, 0.15279 }, { 34.825, 1.386, 0.16668 }, {
				35.808, 1.5662, 0.18118 }, { 36.789, 1.7612, 0.19627 }, { 37.767, 1.971, 0.21137 },
				{ 38.741, 2.1956, 0.22647 }, { 39.712, 2.4348, 0.24157 },
				{ 40.679, 2.6887, 0.25667 }, { 41.643, 2.9571, 0.27176 }, { 42.602, 3.24, 0.28686 },
				{ 43.557, 3.5374, 0.30196 }, { 44.507, 3.8492, 0.31706 },
				{ 45.452, 4.1753, 0.33216 }, { 46.392, 4.5156, 0.34725 },
				{ 47.328, 4.8701, 0.36235 }, { 48.257, 5.2386, 0.37745 },
				{ 49.181, 5.6212, 0.39255 }, { 50.099, 6.0176, 0.40765 },
				{ 51.011, 6.4279, 0.42274 }, { 51.917, 6.8519, 0.43784 },
				{ 52.816, 7.2895, 0.45294 }, { 53.708, 7.7406, 0.46804 },
				{ 54.594, 8.2052, 0.48314 }, { 55.472, 8.683, 0.49823 },
				{ 56.343, 9.1741, 0.51333 }, { 57.207, 9.6783, 0.52843 },
				{ 58.063, 10.195, 0.54353 }, { 58.911, 10.725, 0.55863 },
				{ 59.751, 11.268, 0.57372 }, { 60.582, 11.824, 0.58882 },
				{ 61.406, 12.392, 0.60392 }, { 62.22, 12.972, 0.61902 },
				{ 63.026, 13.564, 0.63412 }, { 63.822, 14.169, 0.64921 },
				{ 64.609, 14.785, 0.66431 }, { 65.387, 15.414, 0.67941 },
				{ 66.156, 16.054, 0.69451 }, { 66.914, 16.705, 0.70961 },
				{ 67.663, 17.368, 0.7247 }, { 68.402, 18.042, 0.7398 }, { 69.13, 18.727, 0.7549 }, {
						69.848, 19.424, 0.77 }, { 70.555, 20.13, 0.7851 },
				{ 71.252, 20.848, 0.80019 }, { 71.938, 21.576, 0.81529 },
				{ 72.612, 22.314, 0.83039 }, { 73.275, 23.062, 0.84549 },
				{ 73.927, 23.821, 0.86059 }, { 74.568, 24.589, 0.87568 },
				{ 75.197, 25.366, 0.89078 }, { 75.814, 26.153, 0.90588 },
				{ 76.419, 26.949, 0.92098 }, { 77.012, 27.755, 0.93608 },
				{ 77.592, 28.569, 0.95117 }, { 78.161, 29.391, 0.96627 },
				{ 78.717, 30.223, 0.98137 }, { 79.26, 31.062, 0.99647 }, { 79.791, 31.91, 1.0116 },
				{ 80.308, 32.765, 1.0267 }, { 80.813, 33.629, 1.0418 }, { 81.304, 34.5, 1.0569 }, {
						81.783, 35.378, 1.072 }, { 82.248, 36.263, 1.0871 },
				{ 82.7, 37.155, 1.1022 }, { 83.138, 38.054, 1.1173 }, { 83.562, 38.959, 1.1324 }, {
						83.973, 39.871, 1.1474 }, { 84.37, 40.789, 1.1625 }, { 84.753, 41.713,
						1.1776 }, { 85.122, 42.642, 1.1927 }, { 85.477, 43.577, 1.2078 }, { 85.818,
						44.517, 1.2229 }, { 86.145, 45.462, 1.238 }, { 86.457, 46.412, 1.2531 }, {
						86.755, 47.367, 1.2682 }, { 87.039, 48.326, 1.2833 }, { 87.308, 49.289,
						1.2984 }, { 87.562, 50.256, 1.3135 }, { 87.802, 51.227, 1.3286 }, { 88.027,
						52.201, 1.3437 }, { 88.238, 53.179, 1.3588 }, { 88.433, 54.159, 1.3739 }, {
						88.614, 55.143, 1.389 }, { 88.78, 56.129, 1.4041 },
				{ 88.932, 57.117, 1.418 }, { 89.071, 58.108, 1.4313 }, { 89.198, 59.1, 1.444 }, {
						89.312, 60.093, 1.4561 }, { 89.415, 61.088, 1.4675 }, { 89.507, 62.083,
						1.4784 }, { 89.59, 63.08, 1.4887 }, { 89.662, 64.077, 1.4983 }, { 89.725,
						65.075, 1.5074 }, { 89.78, 66.074, 1.5158 }, { 89.827, 67.073, 1.5237 }, {
						89.867, 68.072, 1.5309 }, { 89.9, 69.072, 1.5376 },
				{ 89.928, 70.071, 1.5436 }, { 89.949, 71.071, 1.5491 }, { 89.966, 72.071, 1.5539 },
				{ 89.979, 73.071, 1.5581 }, { 89.988, 74.071, 1.5617 }, { 89.994, 75.071, 1.5648 },
				{ 89.998, 76.071, 1.5672 }, { 89.999, 77.071, 1.569 }, { 90, 78.071, 1.5702 }, { 90,
						79.071, 1.5708 }, { 90, 80.071, 1.5708 }, { 90, 80.071, 1.5708 }, { 90,
						81.071, 1.5708 }, { 90, 82.071, 1.5708 }, { 90, 83.071, 1.5708 }, { 90,
						84.071, 1.5708 }, { 90, 85.071, 1.5708 }, { 90, 86.071, 1.5708 }, { 90,
						87.071, 1.5708 }, { 90, 88.071, 1.5708 }, { 90, 89.071, 1.5708 }, { 90, 90,
						1.5708 }, };
		if (index < 0) {
			return Position(0, 0 + interval * index, 0);
		} else if (index > getSize() - 1) {
			Position end(data[getSize() - 1][0], data[getSize() - 1][1], data[getSize() - 1][2]);
			return end
					+ Position((index - getSize() + 1) * interval * cos(end.theta),
							(index - getSize() + 1) * interval * sin(end.theta), 0);
		} else {
			return Position(data[index][0], data[index][1], data[index][2]);
		}
	}
};

class Curve45: public Trajectory {
public:
	Curve45(bool mirror = false) :
			Trajectory(mirror) {
	}
private:
	virtual int size() const {
		return 300;
	}
	virtual Position position(int index) const {
		static const float data[][3] = { { 0, 0, 0 }, { 1, 0, 0 }, { 2, 0, 0 }, { 3, 0, 0 }, { 4, 0,
				0 }, { 5, 0, 0 }, { 6, 0, 0 }, { 7, 0, 0 }, { 8, 0, 0 }, { 9, 0, 0 }, { 10, 0, 0 },
				{ 11, 0, 0 }, { 12, 0, 0 }, { 13, 0, 0 }, { 14, 0, 0 }, { 15, 0, 0 }, { 16, 0, 0 },
				{ 17, 0, 0 }, { 18, 0, 0 }, { 19, 0, 0 }, { 20, 0, 0 }, { 21, 0, 0 }, { 22, 0, 0 },
				{ 23, 0, 0 }, { 24, 0, 0 }, { 25, 0, 0 }, { 26, 0, 0 }, { 27, 0, 0 }, { 28, 0, 0 },
				{ 29, 0, 0 }, { 30, 0, 0 }, { 31, 0, 0 }, { 32, 0, 0 }, { 33, 0, 0 }, { 34, 0, 0 },
				{ 35, 0, 0 }, { 36, 0, 0 }, { 37, 0, 0 }, { 38, 0, 0 }, { 39, 0, 0 }, { 40, 0, 0 },
				{ 41, 0, 0 }, { 42, 0, 0 }, { 43, 0, 0 }, { 44, 0, 0 }, { 45, 0, 0 }, { 46, 0, 0 },
				{ 47, 0, 0 }, { 48, 0, 0 }, { 49, 0, 0 }, { 50, 0, 0 }, { 51, 0, 0 }, { 52, 0, 0 },
				{ 53, 0, 0 }, { 54, 0, 0 }, { 55, 0, 0 }, { 56, 0, 0 }, { 57, 0, 0 }, { 58, 0, 0 },
				{ 59, 0, 0 }, { 60, 0, 0 }, { 61, 0, 0 }, { 62, 0, 0 }, { 63, 0, 0 }, { 64, 0, 0 },
				{ 65, 0, 0 }, { 66, 0, 0 }, { 67, 0, 0 }, { 68, 0, 0 }, { 69, 0, 0 }, { 70, 0, 0 },
				{ 71, 0, 0 }, { 72, 0, 0 }, { 73, 0, 0 }, { 74, 0, 0 }, { 75, 0, 0 }, { 76, 0, 0 },
				{ 77, 0, 0 }, { 78, 0, 0 }, { 79, 0, 0 }, { 80.69, 0, 0 }, { 81.69, 0, 0 }, { 82.69,
						0, 0 }, { 83.69, 9.6963e-05, 9.6963e-05 },
				{ 84.69, 0.00038785, 0.00029089 }, { 85.69, 0.00096963, 0.00058178 }, { 86.69,
						0.0019393, 0.00096963 }, { 87.69, 0.0033937, 0.0014544 }, { 88.69,
						0.0054299, 0.0020362 }, { 89.69, 0.0081449, 0.002715 }, { 90.69, 0.011636,
						0.0034907 }, { 91.69, 0.015999, 0.0043633 }, { 92.69, 0.021332, 0.005333 },
				{ 93.69, 0.027731, 0.0063995 }, { 94.69, 0.035294, 0.0075631 }, { 95.69, 0.044118,
						0.0088236 }, { 96.69, 0.054299, 0.010181 }, { 97.69, 0.065934, 0.011636 }, {
						98.69, 0.07912, 0.013187 }, { 99.69, 0.093955, 0.014835 }, { 100.69,
						0.11054, 0.016581 }, { 101.69, 0.12896, 0.018423 }, { 102.69, 0.14932,
						0.020362 }, { 103.69, 0.17171, 0.022398 }, { 104.69, 0.19624, 0.024532 }, {
						105.69, 0.223, 0.026762 }, { 106.69, 0.25209, 0.029089 }, { 107.69, 0.28359,
						0.031513 }, { 108.69, 0.31762, 0.034034 }, { 109.69, 0.35427, 0.036652 }, {
						110.69, 0.39362, 0.039367 }, { 111.68, 0.43579, 0.042179 }, { 112.68,
						0.48086, 0.045088 }, { 113.68, 0.52894, 0.048094 }, { 114.68, 0.58011,
						0.051196 }, { 115.68, 0.63448, 0.054396 }, { 116.68, 0.69214, 0.057693 }, {
						117.68, 0.75319, 0.061087 }, { 118.67, 0.81772, 0.064577 }, { 119.67,
						0.88583, 0.068165 }, { 120.67, 0.95762, 0.071849 }, { 121.67, 1.0332,
						0.075631 }, { 122.66, 1.1126, 0.079509 }, { 123.66, 1.196, 0.083485 }, {
						124.66, 1.2834, 0.087557 }, { 125.65, 1.375, 0.091727 }, { 126.65, 1.4709,
						0.095993 }, { 127.64, 1.5711, 0.10036 }, { 128.64, 1.6757, 0.10482 }, {
						129.63, 1.7849, 0.10937 }, { 130.62, 1.8986, 0.11403 }, { 131.62, 2.0171,
						0.11878 }, { 132.61, 2.1404, 0.12363 }, { 133.6, 2.2687, 0.12857 }, {
						134.59, 2.4019, 0.13361 }, { 135.58, 2.5402, 0.13875 }, { 136.57, 2.6837,
						0.14399 }, { 137.56, 2.8325, 0.14932 }, { 138.55, 2.9866, 0.15475 }, {
						139.54, 3.1462, 0.16028 }, { 140.52, 3.3113, 0.1659 }, { 141.51, 3.4821,
						0.17162 }, { 142.49, 3.6586, 0.17744 }, { 143.48, 3.841, 0.18336 }, {
						144.46, 4.0292, 0.18937 }, { 145.44, 4.2234, 0.19548 }, { 146.42, 4.4237,
						0.20168 }, { 147.4, 4.6303, 0.20805 }, { 148.37, 4.8431, 0.21441 }, {
						149.35, 5.062, 0.22078 }, { 150.32, 5.2872, 0.22714 }, { 151.3, 5.5186,
						0.23351 }, { 152.27, 5.7562, 0.23987 }, { 153.24, 6, 0.24623 }, { 154.21,
						6.2499, 0.2526 }, { 155.17, 6.506, 0.25896 }, { 156.14, 6.7682, 0.26533 }, {
						157.1, 7.0366, 0.27169 }, { 158.06, 7.311, 0.27806 }, { 159.02, 7.5916,
						0.28442 }, { 159.98, 7.8783, 0.29079 }, { 160.94, 8.1711, 0.29715 }, {
						161.89, 8.47, 0.30352 }, { 162.84, 8.775, 0.30988 }, { 163.79, 9.086,
						0.31624 }, { 164.74, 9.403, 0.32261 }, { 165.69, 9.7261, 0.32897 }, {
						166.63, 10.055, 0.33534 }, { 167.57, 10.39, 0.3417 }, { 168.51, 10.731,
						0.34807 }, { 169.45, 11.078, 0.35443 }, { 170.39, 11.431, 0.3608 }, {
						171.32, 11.79, 0.36716 }, { 172.25, 12.155, 0.37353 }, { 173.18, 12.526,
						0.37989 }, { 174.11, 12.903, 0.38626 }, { 175.03, 13.285, 0.39262 }, {
						175.95, 13.674, 0.39898 }, { 176.87, 14.068, 0.40535 }, { 177.79, 14.468,
						0.41171 }, { 178.7, 14.874, 0.41808 }, { 179.61, 15.286, 0.42444 }, {
						180.52, 15.704, 0.43081 }, { 181.43, 16.127, 0.43717 }, { 182.33, 16.556,
						0.44354 }, { 183.23, 16.991, 0.4499 }, { 184.13, 17.432, 0.45627 }, {
						185.02, 17.878, 0.46263 }, { 185.92, 18.33, 0.46899 }, { 186.81, 18.788,
						0.47536 }, { 187.69, 19.251, 0.48172 }, { 188.58, 19.72, 0.48809 }, {
						189.46, 20.195, 0.49445 }, { 190.33, 20.675, 0.50082 }, { 191.21, 21.16,
						0.50718 }, { 192.08, 21.652, 0.51355 }, { 192.95, 22.149, 0.51991 }, {
						193.81, 22.651, 0.52628 }, { 194.67, 23.159, 0.53264 }, { 195.53, 23.672,
						0.539 }, { 196.38, 24.191, 0.54537 }, { 197.24, 24.715, 0.55173 }, { 198.08,
						25.244, 0.5581 }, { 198.93, 25.779, 0.56446 }, { 199.77, 26.32, 0.57083 }, {
						200.61, 26.865, 0.57719 }, { 201.44, 27.416, 0.58356 }, { 202.27, 27.973,
						0.58992 }, { 203.1, 28.534, 0.59603 }, { 203.93, 29.1, 0.60204 }, { 204.75,
						29.672, 0.60796 }, { 205.56, 30.248, 0.61377 }, { 206.38, 30.828, 0.61949 },
				{ 207.19, 31.413, 0.62512 }, { 208, 32.003, 0.63065 }, { 208.8, 32.597, 0.63608 }, {
						209.6, 33.195, 0.64141 }, { 210.4, 33.798, 0.64664 }, { 211.2, 34.404,
						0.65178 }, { 211.99, 35.015, 0.65683 }, { 212.78, 35.63, 0.66177 }, {
						213.56, 36.248, 0.66662 }, { 214.35, 36.87, 0.67137 }, { 215.13, 37.496,
						0.67602 }, { 215.9, 38.125, 0.68058 }, { 216.68, 38.758, 0.68504 }, {
						217.45, 39.394, 0.68941 }, { 218.22, 40.033, 0.69367 }, { 218.98, 40.676,
						0.69784 }, { 219.75, 41.321, 0.70191 }, { 220.51, 41.97, 0.70589 }, {
						221.27, 42.622, 0.70977 }, { 222.02, 43.276, 0.71355 }, { 222.78, 43.934,
						0.71723 }, { 223.53, 44.594, 0.72082 }, { 224.28, 45.256, 0.72431 }, {
						225.02, 45.921, 0.72771 }, { 225.77, 46.589, 0.731 }, { 226.51, 47.259,
						0.7342 }, { 227.25, 47.931, 0.7373 }, { 227.99, 48.606, 0.74031 }, { 228.73,
						49.282, 0.74322 }, { 229.46, 49.961, 0.74603 }, { 230.19, 50.642, 0.74875 },
				{ 230.92, 51.324, 0.75136 }, { 231.65, 52.009, 0.75389 },
				{ 232.38, 52.695, 0.75631 }, { 233.11, 53.383, 0.75864 },
				{ 233.83, 54.073, 0.76087 }, { 234.55, 54.764, 0.763 }, { 235.27, 55.456, 0.76504 },
				{ 235.99, 56.15, 0.76698 }, { 236.71, 56.846, 0.76882 },
				{ 237.43, 57.542, 0.77056 }, { 238.15, 58.24, 0.77221 },
				{ 238.86, 58.939, 0.77376 }, { 239.58, 59.639, 0.77522 },
				{ 240.29, 60.339, 0.77657 }, { 241, 61.041, 0.77784 }, { 241.71, 61.744, 0.779 }, {
						242.42, 62.447, 0.78007 }, { 243.13, 63.151, 0.78103 }, { 243.84, 63.856,
						0.78191 }, { 244.55, 64.561, 0.78268 }, { 245.26, 65.266, 0.78336 }, {
						245.97, 65.973, 0.78394 }, { 246.68, 66.679, 0.78443 }, { 247.39, 67.386,
						0.78482 }, { 248.09, 68.093, 0.78511 }, { 248.8, 68.8, 0.7853 }, { 249.51,
						69.507, 0.7854 }, { 250.21, 70.214, 0.7854 }, { 250.21, 70.214, 0.7854 }, {
						250.92, 70.921, 0.7854 }, { 251.63, 71.628, 0.7854 }, { 252.34, 72.335,
						0.7854 }, { 253.04, 73.042, 0.7854 }, { 253.75, 73.749, 0.7854 }, { 254.46,
						74.456, 0.7854 }, { 255.16, 75.164, 0.7854 }, { 255.87, 75.871, 0.7854 }, {
						256.58, 76.578, 0.7854 }, { 257.28, 77.285, 0.7854 }, { 257.99, 77.992,
						0.7854 }, { 258.7, 78.699, 0.7854 }, { 259.41, 79.406, 0.7854 }, { 260.11,
						80.113, 0.7854 }, { 260.82, 80.82, 0.7854 }, { 261.53, 81.528, 0.7854 }, {
						262.23, 82.235, 0.7854 }, { 262.94, 82.942, 0.7854 }, { 263.65, 83.649,
						0.7854 }, { 264.36, 84.356, 0.7854 }, { 265.06, 85.063, 0.7854 }, { 265.77,
						85.77, 0.7854 }, { 266.48, 86.477, 0.7854 }, { 267.18, 87.184, 0.7854 }, {
						267.89, 87.892, 0.7854 }, { 268.6, 88.599, 0.7854 }, { 270, 90, 0.7854 }, };
		if (index < 0) {
			return Position(0, 0 + interval * index, 0);
		} else if (index > getSize() - 1) {
			Position end(data[getSize() - 1][0], data[getSize() - 1][1], data[getSize() - 1][2]);
			return end
					+ Position((index - getSize() + 1) * interval * cos(end.theta),
							(index - getSize() + 1) * interval * sin(end.theta), 0);
		} else {
			return Position(data[index][0], data[index][1], data[index][2]);
		}
	}
};

class Curve135: public Trajectory {
public:
	Curve135(bool mirror = false) :
			Trajectory(mirror) {
	}
private:
	virtual int size() const {
		return 284;
	}
	virtual Position position(int index) const {
		static const float data[][3] = { { 0, 0, 0 }, { 1.5056, 0, 0 }, { 2.5056, 0, 0 }, { 3.5056,
				0, 0 }, { 4.5056, 0.0002404, 0.0002404 }, { 5.5056, 0.00096161, 0.00072121 }, {
				6.5056, 0.002404, 0.0014424 }, { 7.5056, 0.0048081, 0.002404 }, { 8.5056, 0.0084141,
				0.0036061 }, { 9.5055, 0.013463, 0.0050485 }, { 10.506, 0.020194, 0.0067313 }, {
				11.505, 0.028848, 0.0086545 }, { 12.505, 0.039666, 0.010818 }, { 13.505, 0.052888,
				0.013222 }, { 14.505, 0.068754, 0.015867 }, { 15.505, 0.087504, 0.018751 }, {
				16.505, 0.10938, 0.021877 }, { 17.504, 0.13462, 0.025242 }, { 18.504, 0.16346,
				0.028848 }, { 19.504, 0.19615, 0.032695 }, { 20.503, 0.23293, 0.036782 }, { 21.502,
				0.27402, 0.041109 }, { 22.501, 0.31968, 0.045677 }, { 23.5, 0.37015, 0.050485 }, {
				24.498, 0.42565, 0.055533 }, { 25.496, 0.48644, 0.060822 }, { 26.494, 0.55274,
				0.066351 }, { 27.492, 0.6248, 0.072121 }, { 28.488, 0.70285, 0.078131 }, { 29.485,
				0.78713, 0.084382 }, { 30.481, 0.87788, 0.090873 }, { 31.476, 0.97533, 0.097604 }, {
				32.471, 1.0797, 0.10458 }, { 33.464, 1.1913, 0.11179 }, { 34.457, 1.3102, 0.11924 },
				{ 35.449, 1.4368, 0.12693 }, { 36.44, 1.5713, 0.13487 }, { 37.43, 1.7138, 0.14304 },
				{ 38.418, 1.8647, 0.15145 }, { 39.406, 2.0241, 0.16011 }, { 40.391, 2.1923, 0.169 },
				{ 41.376, 2.3695, 0.17814 }, { 42.358, 2.5559, 0.18751 },
				{ 43.339, 2.7518, 0.19713 }, { 44.317, 2.9573, 0.20699 },
				{ 45.294, 3.1727, 0.21708 }, { 46.268, 3.3982, 0.22742 }, { 47.24, 3.6339, 0.238 },
				{ 48.209, 3.8802, 0.24882 }, { 49.176, 4.1371, 0.25988 },
				{ 50.139, 4.405, 0.27118 }, { 51.099, 4.684, 0.28271 }, { 52.056, 4.9742, 0.29449 },
				{ 53.01, 5.276, 0.30651 }, { 53.959, 5.5894, 0.31878 }, { 54.905, 5.9146, 0.33128 },
				{ 55.846, 6.2519, 0.34402 }, { 56.783, 6.6014, 0.357 }, { 57.715, 6.9632, 0.37022 },
				{ 58.643, 7.3375, 0.38368 }, { 59.565, 7.7245, 0.39739 },
				{ 60.481, 8.1244, 0.41133 }, { 61.392, 8.5371, 0.42551 },
				{ 62.297, 8.963, 0.43994 }, { 63.195, 9.4021, 0.4546 }, { 64.087, 9.8546, 0.46951 },
				{ 64.972, 10.32, 0.48465 }, { 65.85, 10.8, 0.50004 }, { 66.72, 11.293, 0.51567 }, {
						67.582, 11.8, 0.53153 }, { 68.435, 12.321, 0.54764 }, { 69.281, 12.855,
						0.56399 }, { 70.117, 13.404, 0.58057 }, { 70.944, 13.966, 0.5974 }, {
						71.761, 14.543, 0.61447 }, { 72.568, 15.133, 0.63178 }, { 73.364, 15.738,
						0.64933 }, { 74.15, 16.357, 0.66712 }, { 74.924, 16.989, 0.68515 }, {
						75.687, 17.636, 0.70342 }, { 76.437, 18.297, 0.72193 }, { 77.175, 18.972,
						0.74068 }, { 77.9, 19.661, 0.7597 }, { 78.612, 20.363, 0.77871 }, { 79.31,
						21.079, 0.79772 }, { 79.995, 21.808, 0.81673 }, { 80.666, 22.549, 0.83574 },
				{ 81.322, 23.304, 0.85476 }, { 81.964, 24.071, 0.87377 },
				{ 82.591, 24.849, 0.89278 }, { 83.204, 25.64, 0.91179 },
				{ 83.801, 26.442, 0.93081 }, { 84.383, 27.255, 0.94982 },
				{ 84.949, 28.08, 0.96883 }, { 85.499, 28.914, 0.98784 }, { 86.034, 29.76, 1.0069 },
				{ 86.552, 30.615, 1.0259 }, { 87.054, 31.48, 1.0449 }, { 87.54, 32.354, 1.0639 }, {
						88.008, 33.237, 1.0829 }, { 88.46, 34.129, 1.1019 },
				{ 88.895, 35.03, 1.1209 }, { 89.313, 35.938, 1.1399 }, { 89.713, 36.855, 1.159 }, {
						90.096, 37.779, 1.178 }, { 90.461, 38.71, 1.197 },
				{ 90.808, 39.647, 1.216 }, { 91.138, 40.591, 1.235 }, { 91.449, 41.542, 1.254 }, {
						91.743, 42.498, 1.273 }, { 92.018, 43.459, 1.292 },
				{ 92.275, 44.426, 1.3111 }, { 92.513, 45.397, 1.3301 }, { 92.733, 46.372, 1.3491 },
				{ 92.935, 47.352, 1.3681 }, { 93.117, 48.335, 1.3871 }, { 93.281, 49.321, 1.4061 },
				{ 93.426, 50.311, 1.4251 }, { 93.553, 51.303, 1.4441 }, { 93.66, 52.297, 1.4632 }, {
						93.749, 53.293, 1.4822 }, { 93.818, 54.291, 1.5012 }, { 93.869, 55.289,
						1.5202 }, { 93.9, 56.289, 1.5392 }, { 93.913, 57.289, 1.5582 }, { 93.906,
						58.289, 1.5772 }, { 93.881, 59.288, 1.5962 }, { 93.837, 60.287, 1.6153 }, {
						93.773, 61.285, 1.6343 }, { 93.691, 62.282, 1.6528 }, { 93.591, 63.277,
						1.671 }, { 93.473, 64.27, 1.6891 }, { 93.338, 65.261, 1.7069 }, { 93.184,
						66.249, 1.7244 }, { 93.014, 67.234, 1.7417 }, { 92.828, 68.217, 1.7588 }, {
						92.624, 69.196, 1.7756 }, { 92.405, 70.172, 1.7922 }, { 92.169, 71.143,
						1.8086 }, { 91.918, 72.111, 1.8247 }, { 91.651, 73.075, 1.8405 }, { 91.37,
						74.035, 1.8562 }, { 91.074, 74.99, 1.8715 }, { 90.763, 75.94, 1.8867 }, {
						90.438, 76.886, 1.9016 }, { 90.1, 77.827, 1.9163 },
				{ 89.747, 78.763, 1.9307 }, { 89.382, 79.694, 1.9449 }, { 89.004, 80.62, 1.9588 }, {
						88.613, 81.54, 1.9725 }, { 88.209, 82.455, 1.986 },
				{ 87.794, 83.365, 1.9992 }, { 87.367, 84.269, 2.0122 }, { 86.928, 85.167, 2.0249 },
				{ 86.478, 86.061, 2.0374 }, { 86.017, 86.948, 2.0497 }, { 85.546, 87.83, 2.0617 }, {
						85.064, 88.706, 2.0735 }, { 84.572, 89.577, 2.085 }, { 84.071, 90.442,
						2.0963 }, { 83.559, 91.301, 2.1074 }, { 83.039, 92.155, 2.1182 }, { 82.509,
						93.004, 2.1288 }, { 81.971, 93.846, 2.1391 }, { 81.425, 94.684, 2.1492 }, {
						80.87, 95.516, 2.1591 }, { 80.307, 96.342, 2.1687 }, { 79.736, 97.163,
						2.1781 }, { 79.158, 97.979, 2.1872 }, { 78.573, 98.79, 2.1961 }, { 77.98,
						99.596, 2.2047 }, { 77.381, 100.4, 2.2132 }, { 76.776, 101.19, 2.2213 }, {
						76.164, 101.98, 2.2293 }, { 75.546, 102.77, 2.237 }, { 74.922, 103.55,
						2.2444 }, { 74.293, 104.33, 2.2516 }, { 73.658, 105.1, 2.2586 }, { 73.018,
						105.87, 2.2653 }, { 72.373, 106.63, 2.2718 }, { 71.723, 107.39, 2.2781 }, {
						71.069, 108.15, 2.2841 }, { 70.41, 108.9, 2.2898 },
				{ 69.747, 109.65, 2.2954 }, { 69.08, 110.4, 2.3007 }, { 68.41, 111.14, 2.3057 }, {
						67.736, 111.88, 2.3105 }, { 67.058, 112.61, 2.3151 }, { 66.378, 113.34,
						2.3194 }, { 65.694, 114.07, 2.3235 }, { 65.008, 114.8, 2.3273 }, { 64.319,
						115.53, 2.331 }, { 63.627, 116.25, 2.3343 }, { 62.933, 116.97, 2.3374 }, {
						62.238, 117.69, 2.3403 }, { 61.54, 118.4, 2.343 },
				{ 60.841, 119.12, 2.3454 }, { 60.14, 119.83, 2.3475 }, { 59.437, 120.54, 2.3495 }, {
						58.734, 121.25, 2.3511 }, { 58.029, 121.96, 2.3526 }, { 57.324, 122.67,
						2.3538 }, { 56.618, 123.38, 2.3548 }, { 55.911, 124.09, 2.3555 }, { 55.204,
						124.8, 2.356 }, { 54.497, 125.5, 2.3562 }, { 53.79, 126.21, 2.3562 }, {
						53.79, 126.21, 2.3562 }, { 53.083, 126.92, 2.3562 }, { 52.376, 127.62,
						2.3562 }, { 51.669, 128.33, 2.3562 }, { 50.961, 129.04, 2.3562 }, { 50.254,
						129.75, 2.3562 }, { 49.547, 130.45, 2.3562 }, { 48.84, 131.16, 2.3562 }, {
						48.133, 131.87, 2.3562 }, { 47.426, 132.57, 2.3562 }, { 46.719, 133.28,
						2.3562 }, { 46.012, 133.99, 2.3562 }, { 45.305, 134.7, 2.3562 }, { 44.598,
						135.4, 2.3562 }, { 43.89, 136.11, 2.3562 }, { 43.183, 136.82, 2.3562 }, {
						42.476, 137.52, 2.3562 }, { 41.769, 138.23, 2.3562 }, { 41.062, 138.94,
						2.3562 }, { 40.355, 139.65, 2.3562 }, { 39.648, 140.35, 2.3562 }, { 38.941,
						141.06, 2.3562 }, { 38.234, 141.77, 2.3562 }, { 37.526, 142.47, 2.3562 }, {
						36.819, 143.18, 2.3562 }, { 36.112, 143.89, 2.3562 }, { 35.405, 144.59,
						2.3562 }, { 34.698, 145.3, 2.3562 }, { 33.991, 146.01, 2.3562 }, { 33.284,
						146.72, 2.3562 }, { 32.577, 147.42, 2.3562 }, { 31.87, 148.13, 2.3562 }, {
						31.163, 148.84, 2.3562 }, { 30.455, 149.54, 2.3562 }, { 29.748, 150.25,
						2.3562 }, { 29.041, 150.96, 2.3562 }, { 28.334, 151.67, 2.3562 }, { 27.627,
						152.37, 2.3562 }, { 26.92, 153.08, 2.3562 }, { 26.213, 153.79, 2.3562 }, {
						25.506, 154.49, 2.3562 }, { 24.799, 155.2, 2.3562 }, { 24.091, 155.91,
						2.3562 }, { 23.384, 156.62, 2.3562 }, { 22.677, 157.32, 2.3562 }, { 21.97,
						158.03, 2.3562 }, { 21.263, 158.74, 2.3562 }, { 20.556, 159.44, 2.3562 }, {
						19.849, 160.15, 2.3562 }, { 19.142, 160.86, 2.3562 }, { 18.435, 161.57,
						2.3562 }, { 17.727, 162.27, 2.3562 }, { 17.02, 162.98, 2.3562 }, { 16.313,
						163.69, 2.3562 }, { 15.606, 164.39, 2.3562 }, { 14.899, 165.1, 2.3562 }, {
						14.192, 165.81, 2.3562 }, { 13.485, 166.52, 2.3562 }, { 12.778, 167.22,
						2.3562 }, { 12.071, 167.93, 2.3562 }, { 11.364, 168.64, 2.3562 }, { 10.656,
						169.34, 2.3562 }, { 9.9493, 170.05, 2.3562 }, { 9.2422, 170.76, 2.3562 }, {
						8.5351, 171.46, 2.3562 }, { 7.828, 172.17, 2.3562 }, { 7.1209, 172.88,
						2.3562 }, { 6.4138, 173.59, 2.3562 }, { 5.7067, 174.29, 2.3562 }, { 4.9995,
						175, 2.3562 }, { 4.2924, 175.71, 2.3562 }, { 3.5853, 176.41, 2.3562 }, {
						2.8782, 177.12, 2.3562 }, { 2.1711, 177.83, 2.3562 }, { 1.464, 178.54,
						2.3562 }, { 0.75691, 179.24, 2.3562 }, { 0, 180, 2.3562 }, };
		if (index < 0) {
			return Position(0, 0 + interval * index, 0);
		} else if (index > getSize() - 1) {
			Position end(data[getSize() - 1][0], data[getSize() - 1][1], data[getSize() - 1][2]);
			return end
					+ Position((index - getSize() + 1) * interval * cos(end.theta),
							(index - getSize() + 1) * interval * sin(end.theta), 0);
		} else {
			return Position(data[index][0], data[index][1], data[index][2]);
		}
	}
};

class MoveAction {
public:
	MoveAction(Buzzer *bz, Encoders *enc, MPU6500 *mpu, Reflector *rfl, WallDetector *wd,
			SpeedController *sc) :
			bz(bz), enc(enc), mpu(mpu), rfl(rfl), wd(wd), sc(sc),
					thread(PRIORITY_MOVE_ACTION, STACK_SIZE_MOVE_ACTION) {
		_actions = 0;
		set_params(600);
		ticker.attach_us(this, &MoveAction::isr, MOVE_ACTION_PERIOD);
	}
	enum ACTION {
		START_STEP,
		START_INIT,
		GO_STRAIGHT,
		TURN_LEFT_90,
		TURN_RIGHT_90,
		RETURN,
		STOP,
		FAST_START_STEP,
		FAST_GO_STRAIGHT,
		FAST_GO_DIAGONAL,
		FAST_TURN_LEFT_45,
		FAST_TURN_LEFT_90,
		FAST_TURN_LEFT_135,
		FAST_TURN_RIGHT_45,
		FAST_TURN_RIGHT_90,
		FAST_TURN_RIGHT_135,
		FAST_STOP,
	};
	struct Operation {
		enum ACTION action;
		int num;
	};
	const char* action_string(enum ACTION action) {
		static const char name[][32] = { "start_step", "start_init", "go_straight", "turn_left_90",
				"turn_right_90", "return", "stop", "fast_start_step", "fast_go_straight",
				"fast_go_diagonal", "fast_turn_left_45", "fast_turn_left_90", "fast_turn_left_135",
				"fast_turn_right_45", "fast_turn_right_90", "fast_turn_right_135", "fast_stop" };
		return name[action];
	}
	void enable() {
		rfl->enable();
		sc->enable();
		thread.start(this, &MoveAction::task);
		printf("0x%08X: Move Action\n", (unsigned int) thread.gettid());
	}
	void disable() {
		thread.terminate();
		sc->disable();
		rfl->disable();
		while (1) {
			osEvent evt = mail.get(1);
			if (evt.status != osEventMail) {
				break;
			}
		}
		_actions = 0;
	}
	void set_action(enum ACTION action, int num = 1) {
		_actions += num;
		struct Operation *operation = mail.alloc();
		operation->action = action;
		operation->num = num;
		mail.put(operation);
	}
	void set_params(float fast_speed) {
		this->fast_speed = fast_speed;
	}
	void set_params_relative(float add) {
		this->fast_speed += add;
	}
	int actions() const {
		return _actions;
	}
private:
	Buzzer *bz;
	Encoders *enc;
	MPU6500 *mpu;
	Reflector *rfl;
	WallDetector *wd;
	SpeedController *sc;
	Thread thread;
	Ticker ticker;
	Mail<struct Operation, 128> mail;
	Timer timer;
	int _actions;
	float fast_speed;

	void isr() {
		thread.signal_set(0x01);
	}
	void wall_avoid() {
#if WALL_AVOID_ENABLED
		void wall_attach() {
			if (wd->wall().side[0]) {
				sc->position.y -= wd->wall_difference().side[0] * 0.00001 * sc->actual().trans;
			}
			if (wd->wall().side[1]) {
				sc->position.y += wd->wall_difference().side[1] * 0.00001 * sc->actual().trans;
			}
		}
#endif
	}
	void wall_attach() {
#if WALL_ATTACH_ENABLED
		if (wd->wall().flont[0] && wd->wall().flont[1]) {
			while (1) {
				float trans = wd->wall_difference().flont[0] + wd->wall_difference().flont[1];
				float rot = wd->wall_difference().flont[1] - wd->wall_difference().flont[0];
				const float trans_saturation = 0.4f;
				const float rot_saturation = 0.4f;
				if (trans > trans_saturation) trans = trans_saturation;
				if (trans < -trans_saturation) trans = -trans_saturation;
				if (rot > rot_saturation) rot = rot_saturation;
				if (rot < -rot_saturation) rot = -rot_saturation;
				sc->set_target(trans * 500, rot * 5);
				if (fabs(trans) < 0.1f && fabs(rot) < 0.1f) break;
				Thread::wait(1);
			}
			sc->set_target(0, 0);
			sc->position.x = 0;
			printf("Attach:\t(%06.1f, %06.1f, %06.3f)\n", sc->position.x, sc->position.y,
					sc->position.theta);
		}
#endif
	}
	void turn(float target_angle, float speed) {
		const float accel = 32 * M_PI;
		timer.reset();
		timer.start();
		while (1) {
			Thread::signal_wait(0x01);
			if (fabs(sc->actual().rot) > speed) break;
			if (target_angle > 0) {
				sc->set_target(0, timer.read() * accel);
			} else {
				sc->set_target(0, -timer.read() * accel);
			}
		}
		while (1) {
			Thread::signal_wait(0x01);
			if (fabs(sc->actual().rot) < 0.5) break;
			float extra = target_angle - sc->position.theta;
			float target_speed = sqrt(2 * accel * fabs(extra));
			target_speed = (target_speed > speed) ? speed : target_speed;
			if (extra > 0) {
				sc->set_target(0, target_speed);
			} else {
				sc->set_target(0, -target_speed);
			}
		}
		sc->position.rotate(-target_angle);
	}
	void straight_x(const float distance, const float v0, const float v1, const float v2,
			const float accel = 9000) {
		Trajectory st;
		timer.reset();
		timer.start();
		int cnt = 0;
		float integral = 0;
		while (1) {
			if (sc->position.x > distance) break;
			Thread::signal_wait(0x01);
			float velocity;
			if (sc->position.x > distance / 2) {
				velocity = sqrt(2 * accel * fabs(distance - sc->position.x) + v2 * v2);
				if (velocity > v1) velocity = v1;
			} else if (sc->actual().trans < v1) {
				velocity = v0 + timer.read() * accel;
			} else {
				velocity = v1;
			}
			Position dir = st.getNextDir(sc->position, velocity);
			integral += dir.theta * TRAJECTORY_INTEGRAL_GAIN * MOVE_ACTION_PERIOD / 1000000;
			sc->set_target(dir.x, (dir.theta + integral) * TRAJECTORY_PROP_GAIN);
			if (cnt % 10 == 0) {
//				printf("%.3f\t%.3f\t%.4f\n", dir.x, dir.y, dir.theta);
			}
			cnt++;
			wall_avoid();
		}
		sc->set_target(v2, 0);
		printf("End:\t(%06.1f, %06.1f, %06.3f)\n", sc->position.x, sc->position.y,
				sc->position.theta);
		sc->position -= Position(distance, 0, 0);
	}
	template<class C> void trace(C tr, const float velocity) {
		int cnt = 0;
		float integral = 0;
		while (1) {
			if (tr.getPortion() > 0.99) break;
			Thread::signal_wait(0x01);
			Position dir = tr.getNextDir(sc->position, velocity);
			integral += dir.theta * TRAJECTORY_INTEGRAL_GAIN * MOVE_ACTION_PERIOD / 1000000;
			sc->set_target(dir.x, (dir.theta + integral) * TRAJECTORY_PROP_GAIN);
			if (cnt % 10 == 0) {
				//				printf("%.3f\t%.3f\t%.4f\n", dir.x, dir.y, dir.theta);
			}
			cnt++;
		}
		sc->set_target(velocity, 0);
		tr.shift(sc->position);
	}
	void task() {
		while (1) {
			osEvent evt = mail.get();
			if (evt.status != osEventMail) {
				printf("Mail Error!\n");
				continue;
			}
			struct Operation *operation = (struct Operation*) evt.value.p;
			printf("Action:\t%s\tNumber:\t%d\n", action_string(operation->action), operation->num);
			printf("Start:\t(%06.1f, %06.1f, %06.3f)\n", sc->position.x, sc->position.y,
					sc->position.theta);
			const float velocity = 600;
			const float omega = 4.0f * M_PI;
			switch (operation->action) {
				case START_STEP:
					sc->position.reset();
					straight_x(180 - 24 - 6, 0, velocity, velocity);
					break;
				case START_INIT:
					straight_x(90, velocity, velocity, 0);
					if (mpu->angleZ() > 0) {
						wall_attach();
						turn(-M_PI / 2, omega);
						wall_attach();
						turn(-M_PI / 2, omega);
					} else {
						wall_attach();
						turn(M_PI / 2, omega);
						wall_attach();
						turn(M_PI / 2, omega);
					}
					sc->set_target(-10, 0);
					Thread::wait(100);
					sc->set_target(-200, 0);
					Thread::wait(1000);
					sc->position.reset();
					sc->set_target(0, 0);
					break;
				case GO_STRAIGHT:
					straight_x(180, velocity, 1000, velocity);
					break;
				case TURN_LEFT_90: {
					Curve90 tr(false);
					trace(tr, velocity);
				}
					break;
				case TURN_RIGHT_90: {
					Curve90 tr(true);
					trace(tr, velocity);
				}
					break;
				case RETURN:
					straight_x(90, velocity, velocity, 0);
					if (mpu->angleZ() > 0) {
						wall_attach();
						turn(-M_PI / 2, omega);
						wall_attach();
						turn(-M_PI / 2, omega);
					} else {
						wall_attach();
						turn(M_PI / 2, omega);
						wall_attach();
						turn(M_PI / 2, omega);
					}
					straight_x(90, 0, velocity, velocity);
					break;
				case STOP:
					straight_x(90, velocity, velocity, 0);
					wall_attach();
					sc->set_target(0, 0);
					break;
				case FAST_START_STEP:
					straight_x(180 - 24 - 6, 0, velocity, velocity);
					break;
				case FAST_GO_STRAIGHT:
					straight_x(180, velocity, velocity, velocity);
					break;
				case FAST_GO_DIAGONAL:
					straight_x(90 * 1.41421356, velocity, velocity, velocity);
					break;
				case FAST_TURN_LEFT_45: {
					Curve45 tr(false);
					trace(tr, velocity);
				}
					break;
				case FAST_TURN_LEFT_90: {
					Curve90 tr(false);
					trace(tr, velocity);
				}
					break;
				case FAST_TURN_LEFT_135: {
					Curve135 tr(false);
					trace(tr, velocity);
				}
					break;
				case FAST_TURN_RIGHT_45: {
					Curve45 tr(true);
					trace(tr, velocity);
				}
					break;
				case FAST_TURN_RIGHT_90: {
					Curve90 tr(true);
					trace(tr, velocity);
				}
					break;
				case FAST_TURN_RIGHT_135: {
					Curve135 tr(true);
					trace(tr, velocity);
				}
					break;
				case FAST_STOP:
					straight_x(90, velocity, velocity, 0);
					wall_attach();
					sc->set_target(0, 0);
					break;
			}
			_actions -= operation->num;
			mail.free(operation);
			printf("Error:\t(%06.1f, %06.1f, %06.3f)\n", sc->position.x, sc->position.y,
					sc->position.theta);
			Thread::wait(5);
		}
	}
};

#endif /* MOVEACTION_H_ */
