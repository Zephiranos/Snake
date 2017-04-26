#pragma once
///
// Snake class header
///
#include <deque>

class Snake
{
public:
	Snake(int x, int y, int speed);

	void update();
	void grow();
	void moveHorizontal(int h);
	void moveVertical(int v);
	bool collideApple(int x, int y) const { return _body.front().first == x && _body.front().second == y; }
	bool collideSelfNWorld(int w, int h);
	const std::deque<std::pair<int, int> > getBody() const { return _body; }

private:
	int _dx, _dy;
	int growCounter;
	int _speed;
	int _updateCounter;
	std::deque<std::pair<int, int> > _body;
};