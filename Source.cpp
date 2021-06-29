#include<stdio.h>
#include<conio.h>
#include<stdlib.h> 
#define bool int 

struct tNode		// A binary tree tNode has data, pointer to left child and a pointer to right child 
{
	int data;
	struct tNode* left;
	struct tNode* right;
};

struct sNode		// Structure of a stack node. Linked List implementation is used for stack. A stack node contains a pointer to 
{					// tree node and a pointer to next stack node 
	struct tNode *t;
	struct sNode *next;
};

sNode* push(struct sNode *top_ref, struct tNode *t);				// Stack related functions 
struct tNode* pop(struct sNode* top_ref);
bool isEmpty(struct sNode *top);

/* Iterative function for inorder tree traversal */
void inOrder(struct tNode *root)
{
	/* set current to root of binary tree */
	struct tNode *current = root;
	struct sNode *s = NULL; /* Initialize stack s */
	bool done = 0;

	while (!done)
	{
		/* Reach the left most tNode of the current tNode */
		if (current != NULL)
		{
			/* place pointer to a tree node on the stack before traversing
			the node's left subtree */
			push(s, current);
			current = current->left;
		}

		/* backtrack from the empty subtree and visit the tNode
		at the top of the stack; however, if the stack is empty,
		you are done */
		else
		{
			if (!isEmpty(s))
			{
				current = pop(s);
				printf("%d ", current->data);

				/* we have visited the node and its left subtree.
				Now, it's right subtree's turn */
				current = current->right;
			}
			else
				done = 1;
		}
	} /* end of while */
}

sNode* push(struct sNode* top_ref, struct tNode *new_node)		// Function to push an item to sNode
{
	/* allocate tNode */
	struct sNode *new_tNode =
		(struct sNode*) malloc(sizeof(struct sNode));

	if (new_tNode == NULL)
	{
		printf("Stack Overflow \n");
		getchar();
		exit(0);
	}

	new_tNode->t = new_node;		// put in the data 

	new_tNode->next = top_ref;		// link the old list off the new tNode 

	top_ref = new_tNode;			// move the head to point to the new tNode 
}

bool isEmpty(struct sNode *top)		// The function returns true if stack is empty, otherwise false 
{
	return (top == NULL) ? 1 : 0;
}

struct tNode *pop(struct sNode *top_ref)		// Function to pop an item from stack
{
	struct tNode *result;
	struct sNode *top;

	/*If sNode is empty then error */
	if (isEmpty(top_ref))
	{
		printf("Stack Underflow \n");
		getchar();
		exit(0);
	}
	else
	{
		top = top_ref;
		result = top->t;
		top_ref = top_ref->next;
		free(top);
		return result;
	}
}

struct tNode* newtNode(int data)		// Helper function that allocates a new tNode with the given data and NULL left and right pointers.
{
	struct tNode* tNode = (struct tNode*)malloc(sizeof(struct tNode));
	tNode->data = data;
	tNode->left = NULL;
	tNode->right = NULL;

	return(tNode);
}

int main()
{

	/* Constructed binary tree is
	     1
    	/ \
	   2   3
	  / \
     4	 5
	 */
	struct tNode *root = newtNode(1);
	root->left = newtNode(2);
	root->right = newtNode(3);
	root->left->left = newtNode(4);
	root->left->right = newtNode(5);

	inOrder(root);

	_getch();
}
