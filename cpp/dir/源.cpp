#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<vector>

class node
{
public:
	node();
	node(char key, int value, int N, bool color);
	~node();
	bool isRed();


	char key;
	int value;
	node *left, *right;
	int N;
	bool color;
};

node::node()
{

}

node::node(char key, int value, int N, bool color)
{
	this->key = key;
	this->value = value;
	this->N = N;
	this->color = color;
}

node::~node()
{

}

bool node::isRed()
{
	return this->color == true;
}

int size(node* n)
{
	//todo
	return 0;
}

node rotateleft(node &h)
{
	node* x = h.right;
	h.right = x->left;
	x->left = &h;
	x->color = h.color;
	h.color = true;
	x->N = h.N;
	h.N = 1 + h.left->N + h.right->N;
	return *x;
}

node rotateright(node &h)
{
	node* x = h.left;
	h.left = x->right;
	x->right = &h;
	x->color = true;
	x->N = h.N;
	h.N = 1 + h.left->N + h.right->N;
	return *x;
}

void flipcolors(node &h)
{
	h.color = true;
	h.left->color = false;
	h.right->color = false;
}

class redblackt
{
public:
	redblackt();
	~redblackt();

	node* put(node *n, char key, int value);
	void put(char key, int value);

	node root;

private:

};

redblackt::redblackt()
{
}

redblackt::~redblackt()
{
}

void redblackt::put(char key, int value)
{
	root = *(put(&root, key, value));
	root.color = false;
}

node* redblackt::put(node *h,char key,int value)
{
	//node temp;
	if (h == NULL)
		return new node(key, value, 1, true);
	if (key < h->key)
		h->left = put(h->left, key, value);
	else if (key > h->key)
		h->right = put(h->right, key, value);
	else
		h->value = value;
	if (h->right->isRed() && !h->left->isRed())
		*h = rotateleft(*h);
	if (h->left->isRed() && h->left->left->isRed())
		*h = rotateright(*h);
	if (h->left->isRed() && h->right->isRed())
		flipcolors(*h);
	h->N = h->left->N + h->right->N + 1;//need2change use the size()function
	return h;
}




int main(int argc, char* argv)
{


	return 0;
}