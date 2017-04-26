///////////////////////
// Snake implementation
///////////////////////
#include "Snake.h"
#include <cmath>

Snake::Snake(int x, int y, int speed) :
	_dx(0),
	_dy(0),
	_speed(speed),
	_updateCounter(0),
	growCounter(0)
{
	_body.push_back(std::make_pair(x, y));
}

void Snake::update()
{
	if (_updateCounter < _speed)
		++_updateCounter;
	else
	{
		_updateCounter = 0;
		_body.push_front(std::make_pair(_body.front().first + _dx, _body.front().second + _dy));
		if (!growCounter)
			_body.pop_back();
		else
			--growCounter;
	}
}

void Snake::grow()
{
	growCounter = 3;
}

void Snake::moveHorizontal(int h)
{
	h = (h > 0) - (h < 0);
	if (_body.size() > 1 )
		if (_body[1].first == (_body.front().first + h)) 
			return;

	_dx = h;
	_dy = 0;
}

void Snake::moveVertical(int v)
{
	v= (v > 0) - (v < 0);
	if (_body.size() > 1 )
		if(_body[1].second == (_body.front().second + v)) 
			return;

	_dx = 0;
	_dy = v;

}

bool Snake::collideSelfNWorld(int w, int h)
{
	int x = _body.front().first;
	int y = _body.front().second;

	//wall
	if (x < 0 || x >= w || y < 0 || y >= h) return true;
	//self
	std::deque<std::pair<int, int> >::const_iterator it = _body.begin();
	++it;
	for (; it != _body.end(); ++it)
		if (x == it->first && y == it->second) return true;

	return false;
}