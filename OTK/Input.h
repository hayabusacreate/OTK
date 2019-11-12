#ifndef _INPUT_H_
#define _INPUT_H_

class Input
{
public:
	Input();
	~Input();
	void Update();
	int GetKey();
private:
	int input;
	int key;
};


#endif // !_INPUT_H_
