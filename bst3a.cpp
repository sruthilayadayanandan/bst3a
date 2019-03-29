//including library
#include<iostream>
using namespace std;

//defining the node class
class node
{
	public:

	int data;
	node *parent;
	node *left;
	node *right;

	//Constructor that makes pointers to null
	node(int val)
	{
		data = val;
		left = NULL;
 		right = NULL;
 		parent = NULL;
	}
};
//defining class bst3
class bst3
{
	public:
	node* root;	
	int count;
	//Constructor that makes root to null
	bst3()
	{
		root = NULL;
	}

//Insert function
void insert(int value)
{
	//root case
	if(root==NULL)
	{
		root = new node(value);
		count++;
		return;
	}
	//calling the insert helper function
	inserthelper(root, value);
	{count++;}
}
//inserthelper function
void inserthelper(node *current, int value)
{
	//scrolling and checking
	if(current->data > value)
	{
		//insert if prior to null
		if(current->left==NULL)
		{
			current->left = new node(value);
			current->left->parent = current;
			return;
		}
		//else 
		else{inserthelper(current->left, value);}
	}
	else
	{
		//Insert if prior to null
		if(current->right==NULL)
		{
			current->right = new node(value);
			current->right->parent = current;
			return;
		}
		//else 
		else 
		{inserthelper(current->right, value);}
	}
}
	
//defining the display function
void display()
{
	displayhelper(root);
	cout<<"\b "<<endl;
}

//the displayhelper
void displayhelper(node* current)
{
	//Base condition
	if(current == NULL)
	{return;}

	//display the left part
	displayhelper(current->left);

	//display the current node
	cout << current->data << ",";

	//display the right part
	displayhelper(current->right);
}

//Defining the search function
node* search(int val)
{
	return searchhelper(val, root);
}
//searchhelper
node* searchhelper(int val,node* current)
	{
	//conditio for empty tree or values found or the end of tree
	if(current == NULL || current->data == val)
	{return current;}

	else if(current->data > val)
	{return searchhelper(val, current->left);}
		
	else{
	return searchhelper(val, current->right);}
}

//Function to find the minimum
node* fmin(int val)
{
	node* current = search(val);

	if(root==NULL||current==NULL)
	{return NULL;}
	return fmin2(val,current);
}

//fmin2 function
node* fmin2(int val, node* current)
{
	if(current->left==NULL)
	{return current;}
	else
	{fmin2(val, current->left);}
}

//count fnction
int Count()
{
	return count;
}

//Delete function
void Delete(int val)
{
	node* current = search(val);
	//If node is absent
	if(current==NULL)
	{
		cout << "The value is not present int the bst"<<endl;
	}

	else
	{
		count--;
		//If there is ony one node in branch
		if((current->left && current->right==NULL)||(current->left==NULL && current->right))
		{
			//a node is on gthe left side
			if(current->left && current->right==NULL)
			{
				node* temp = current->left;
				//if current is root
				if(current==root)
				{root=temp;}

				else
				{
					//determining which side the node exists
					if((current->data)<(current->parent->data))
					{current->parent->left=temp;}

					else
					{current->parent->right=temp;}
				}
				temp->parent=current->parent;
			}
			
			//the node is on the right side
			else
			{
				node* temp = current->right;
				//if current is root
				if(current==root)
				{root=temp;}
				else
				{
					//finding currents point
					if((current->data)<(current->parent->data))
					{current->parent->left=temp;}
		
					else{current->parent->right=temp;}
				}
				temp->parent=current->parent;
				} 
		delete current;
		return;
	}
	//If there is two nodes on either side
	if(current->left && current->right){
		//iniorder succesion
		node* temp = fmin(current->right->data);
		current->data = temp->data;
//moving pointers

			if(temp->right){
				temp->parent->left=temp->right;
				temp->right->parent=temp->parent;
			}
			else{
				temp->parent->left=NULL;
			}
		delete temp;
		return;
	}

	//If there is no node on other side
	if(current->left==NULL && current->right==NULL){
		//if current is root
		if(current==root)
		{root=NULL;}
		//moving pointers
		if((current->data)<(current->parent->data)){
			current->parent->left=NULL;
		}
		else{current->parent->right=NULL;}
		delete current;
		}
	}
}

//The function to print all values in between the range
void printrange(int low,int high){ 
	printrange2(root,low,high);
}

void printrange2(node* current,int low,int high){
	//Base condition
	if(current == NULL)
	{return;}
	
	//display left
	printrange2(current->left,low,high);
	
	//display current if it is the entered range
	if((current->data)>=low && (current->data)<=high){
		cout << current->data << ",";
	}
	//display right
	printrange2(current->right,low,high);
}

//counting numberrr of nodes with values in the range
int rcount(int low,int high){ 
	return rcounthelp(root,low,high);
}

int rcounthelp(node* current,int low,int high){
	//Base case
	if(!current){return 0;}

	if(current->data == high && current->data == low){
		return 1;
	}

	//include he node in range and look on its succeding nodes
	if((current->data)<=high && (current->data)>=low)
	{
		return 1 + rcounthelp(current->left,low,high) + rcounthelp(current->right,low,high);
	}

	//If current node is smaller than low, go for right
	else if((current->data)<low){
		return rcounthelp(current->right,low,high);
	}
	//else move to left
	else{
		return rcounthelp(current->left,low,high);
	}
}

//The function for height of the tree
int height(){
	return height2(root);
}

int height2(node* current){
	//Base case
	if(!current){return 0;}

	//Create two parameters for l and r
	int lh = height2(current->left);
	int rh = height2(current->right);

	//compare the levels from left and right subtree and use larger one
	if(lh>rh){
		return (lh+1);
	}
	
	else {
		return (rh+1);
	}
}

};

//calling the main function
int main(){

	bst3 b1;

	//Inserting in tree and checking with display
	b1.insert(33);
	b1.insert(5);
	b1.insert(98);
	b1.insert(17);
	b1.insert(4);
	b1.insert(9);
	b1.insert(1);
	b1.insert(67);
	b1.insert(28);
	b1.display();

	node* find = b1.search(28);
	if (find!=NULL){
		cout << find->data << endl;
	}
	else{
		cout << "There is no such number" << endl;
	} 

	node* parent = b1.fmin(5);
	cout << parent-> data << endl;
	
	int r = b1.Count();
	cout << "No of nodes = " << right << endl;
	b1.display();

	b1.Delete(9);
	b1.display();
	
	cout << "enter the range"<<endl;
	int x,y;
	cin >> x >> y;
	cout << "numbers in the given range are"<<endl;
	
	b1.printrange(x,y);
	cout << endl <<"total numbers in the range = " << b1.rcount(x,y) <<endl;

	cout << "The height of tree is " << b1.height() << endl;

return 0;
}
