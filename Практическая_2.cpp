#include <iostream>

struct node 
{
	int key;
	unsigned char height;
	node* left;
	node* right;
	node(int k) { key = k; left = right = 0; height = 1; }
};

void out_print(node &p, int level)
{
	if (&p != NULL) {
		out_print(*p.left, level + 1);
		for (int i = 0; i < level; i++)
			std::cout << "   ";
		std::cout << p.key << std::endl;
		out_print(*p.right, level + 1);
	}
}


unsigned char height(node* p)
{
	return p ? p->height : 0;
}

int bfactor(node* p)
{
	return height(p->right) - height(p->left);
}

void fixheight(node* p)
{
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	p->height = (hl > hr ? hl : hr) + 1;
}

node* rotateright(node* p)
{
	node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

node* rotateleft(node* q) 
{
	node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

node* balance(node* p) 
{
	fixheight(p);
	if (bfactor(p) == 2)
	{
		if (bfactor(p->right) < 0)
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if (bfactor(p) == -2)
	{
		if (bfactor(p->left) > 0)
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; 
}

node* insert(node* p, int k) 
{
	if (!p) return new node(k);
	if (k < p->key)
		p->left = insert(p->left, k);
	else
		p->right = insert(p->right, k);
	return balance(p);
}


node* findmin(node* p)  
{
	return p->left ? findmin(p->left) : p;
}

node* removemin(node* p)
{
	if (p->left == 0)
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}

node* remove(node* p, int k) 
{
	if (!p) return 0;
	if (k < p->key)
		p->left = remove(p->left, k);
	else if (k > p->key)
		p->right = remove(p->right, k);
	else 
	{
		node* q = p->left;
		node* r = p->right;
		delete p;
		if (!r) return q;
		node* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
	return balance(p);
}

int main()
{
	std::cout << "Hello! Do you want to AVL Tree? 1/0 : ";
	bool choose;
	std::cin >> choose;
	if (!choose)
		return 0;
	std::cout << "Number of a key : ";
	int num;
	std::cin >> num;
	node* dot = new node(num);

	choose = 1;
	
	while (choose)
	{
		std::cout << "What do u want to do ? \n----- 1. Add Point\n----- 2. Delete Point\n";
		char perfomance;
		std::cin >> perfomance;
		if (perfomance == '1')
		{
			std::cout << "Number of a key : ";
			int k;
			std::cin >> k;
			dot = insert(dot, k);
			std::cout << std::endl << std::endl;
			out_print(*dot,1);
			std::cout << std::endl << std::endl << "Will continue ? 1/0 : ";
			std::cin >> perfomance;
		}
	}
}
