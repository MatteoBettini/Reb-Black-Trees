#include <stdio.h>
#include <stdlib.h>
#define COUNT 4

// RED BLACK TREE WITH STRINGS AS KEYS SORTED IN ALPHABETICAL ORDER
typedef struct node{
	char color;
	char *entity;
	struct node *left, *right, *parent;
}node_t;

node_t* nil;

node_t* rb_makeit_node(char *);
node_t* rb_left_rotate(node_t*,node_t*);
node_t* rb_right_rotate(node_t*,node_t*);
node_t* rb_insert(node_t*,node_t*);
node_t* rb_insert_fixup(node_t*,node_t*);
node_t* rb_delete(node_t*,node_t*);
node_t* rb_delete_fixup(node_t*,node_t*);
node_t* rb_successor(node_t*);
node_t* rb_predecessor(node_t*);
node_t* rb_search(node_t*,char*);
node_t* rb_search_and_destroy(node_t*,char*);
void rb_inorder_walk(node_t*);

int dic_order(char*,char*);
void rb_print2DUtil(node_t*, int);

int main(int argc, char * argv[]){
	
	node_t * root;
	char str[] = "0",str2[] = "1",str3[] ="2",str4[] = "3",str5[] = "4",str6[] ="5",str7[] = "6";
	char str8[] = "7",str9[] = "8",str10[] ="9",str11[] = "10",str12[] = "10",str13[] ="11",str14[] = "12";
	
	if(!(nil = (node_t*)malloc(sizeof(node_t))))
		return 0;
	nil->right = nil->left = NULL;
	nil->parent = nil;
	nil->entity = NULL;
	nil->color = 'B';
	root = nil;

	// EXAMPLE OF USE OF THE TREE

	root = rb_insert(root,rb_makeit_node(str));
	root = rb_insert(root,rb_makeit_node(str2));
	root = rb_insert(root,rb_makeit_node(str3));
	root = rb_insert(root,rb_makeit_node(str4));
	root = rb_insert(root,rb_makeit_node(str5));
	root = rb_insert(root,rb_makeit_node(str6));
	root = rb_insert(root,rb_makeit_node(str7));
	root = rb_insert(root,rb_makeit_node(str8));
	root = rb_insert(root,rb_makeit_node(str9));
	root = rb_insert(root,rb_makeit_node(str10));
	root = rb_insert(root,rb_makeit_node(str11));
	root = rb_insert(root,rb_makeit_node(str12));
	root = rb_insert(root,rb_makeit_node(str13));
	root = rb_insert(root,rb_makeit_node(str14));

	root = rb_search_and_destroy(root, str6);
	root = rb_search_and_destroy(root, str7);
	root = rb_search_and_destroy(root, str4);
	
	rb_print2DUtil(root, 0);
	
	
	return 0;
}

void rb_inorder_walk(node_t* root){
	if(root == nil)
		return;
	rb_inorder_walk(root->left);
	printf("%s\n",root->entity);
	rb_inorder_walk(root->right);
}
node_t* rb_search_and_destroy(node_t* root,char* str){
	
	node_t * temp = nil;
	
	temp = rb_search(root, str);
	if(temp != NULL)
        root = rb_delete(root, temp);

	return root;
}
node_t* rb_insert(node_t* root,node_t* z){
	node_t *y,*x;
	y = nil;
	x = root;
	while(x != nil){
		y = x;
		if(dic_order(z->entity,x->entity) == 1)
			x = x->left;
		else if(dic_order(z->entity,x->entity) == 2)
			return root;
		else
			x = x->right;
	}
	z->parent = y;
	if(y == nil)
		root = z;
	else if(dic_order(z->entity, y->entity) == 1)
		y->left = z;
	else if(dic_order(z->entity, y->entity) == 2)
		return root;
	else
		y->right = z;
	z->left = nil;
	z->right = nil;
	z->color = 'R';
	root = rb_insert_fixup(root,z);
	return root;
}
node_t* rb_insert_fixup(node_t* root,node_t* z){
	node_t *y,*x;
	if(z == root)
		root->color = 'B';
	else{
		x = z->parent;
		if(x->color == 'R'){
			if(x == x->parent->left){
				y = x->parent->right;
				if(y->color == 'R'){
					x->color = 'B';
					y->color = 'B';
					x->parent->color = 'R';
					root = rb_insert_fixup(root, x->parent);
				}
				else{
					if(z == x->right){
						z = x;
						root = rb_left_rotate(root, z);
						x = z->parent;
					}
					x->color = 'B';
					x->parent->color = 'R';
					root = rb_right_rotate(root, x->parent);
				}
			}
			else{
				y = x->parent->left;
				if(y->color == 'R'){
					x->color = 'B';
					y->color = 'B';
					x->parent->color = 'R';
					root = rb_insert_fixup(root, x->parent);
				}
				else{
					if(z == x->left){
						z = x;
						root = rb_right_rotate(root, z);
						x = z->parent;
					}
					x->color = 'B';
					x->parent->color = 'R';
					root = rb_left_rotate(root, x->parent);
				}
			}
		}
	}
	return root;
}
node_t* rb_delete(node_t *root,node_t* z){
	
	node_t *y,*x;
	int i;
	if(root != nil){
		if((z->left == nil)||(z->right == nil))
			y = z;
		else
			y = rb_successor(z);
		if(y->left != nil)
			x = y->left;
		else
			x = y->right;
		x->parent = y->parent;
		if(y->parent == nil)
			root = x;
		else if(y == y->parent->left)
			y->parent->left = x;
		else
			y->parent->right = x;
		if(y != z){
			for(i=0; y->entity[i] != '\0';i++)
				;
			if(!(z->entity = (char*)realloc(z->entity,sizeof(char)*(i+1))))
				return NULL;
			for(i=0; y->entity[i] != '\0';i++)
				z->entity[i] = y->entity[i];
			z->entity[i] = '\0';
		}
		if(y->color == 'B'){
			rb_delete_fixup(root, x);
		}
		free(y);
	}
	return root;
}
node_t* rb_delete_fixup(node_t* root,node_t* x){
	node_t* w;
	while(x != root && x->color == 'B'){
		if(x == x->parent->left){
			w = x->parent->right;
			if(w->color == 'R'){
				w->color = 'B';
				x->parent->color = 'R';
				root = rb_left_rotate(root,x->parent);
				w = x->parent->right;
			}
			
			if(w->left->color == 'B' && w->right->color == 'B'){
				w->color = 'R';
				x = x->parent;
			}
			else{
				if(w->right->color == 'B'){
					w->left->color = 'B';
					w->color = 'R';
					root = rb_right_rotate(root,w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = 'B';
				w->right->color = 'B';
				root = rb_left_rotate(root,x->parent);
				x = root;
			}
		}
		else{
			w = x->parent->left;
			if(w->color == 'R'){
				w->color = 'B';
				x->parent->color = 'R';
				root = rb_right_rotate(root,x->parent);
				w = x->parent->left;
			}
			
			if(w->left->color == 'B' && w->right->color == 'B'){
				w->color = 'R';
				x = x->parent;
			}
			else{
				if(w->left->color == 'B'){
					w->right->color = 'B';
					w->color = 'R';
					root = rb_left_rotate(root,w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = 'B';
				w->left->color = 'B';
				root = rb_right_rotate(root,x->parent);
				x = root;
			}
		}
	}
	x->color = 'B';
	return root;
}
node_t* rb_makeit_node(char * str){
	node_t * node;
	if(!(node = (node_t*)malloc(sizeof(node_t))))
		return NULL;
	int i;
	for(i=0; str[i] != '\0';i++)
		;
	if(!(node->entity = (char*)malloc(sizeof(char)*(i+1))))
		return NULL;
	for(i=0; str[i] != '\0';i++)
		node->entity[i] = str[i];
	node->entity[i] = '\0';
	node->parent = nil;
	
	return node;
}
node_t* rb_left_rotate(node_t * root,node_t * x){
	node_t * y;
	y = x->right;
	x->right = y->left;
	
	if(y->left != nil)
		y->left->parent = x;
	y->parent = x->parent;
	if(x->parent == nil)
		root = y;
	else if(x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->left = x;
	x->parent = y;
	return root;
}
node_t* rb_right_rotate(node_t * root,node_t * x){
	node_t * y;
	y = x->left;
	x->left = y->right;
	
	if(y->right != nil)
		y->right->parent = x;
	y->parent = x->parent;
	if(x->parent == nil)
		root = y;
	else if(x == x->parent->right)
		x->parent->right = y;
	else
		x->parent->left = y;
	y->right = x;
	x->parent = y;
	return root;
}
node_t* rb_search(node_t * root,char * str){
    if(root == nil)
        return NULL;
    if(dic_order(root->entity, str) == 2)
        return root;
    else if(dic_order(root->entity, str) == 1)
        return rb_search(root->right, str);
    return rb_search(root->left, str);
}
node_t* rb_successor(node_t * root){
	node_t * temp;
	temp = root->right;
	if(temp != nil){
		while(temp->left != nil)
			temp = temp->left;
		return temp;
	}
	else{
		temp = root->parent;
		while(temp != nil && root == temp->right){
			root = temp;
			temp = temp->parent;
		}
		return temp;
	}
	return temp;
}
node_t* rb_predecessor(node_t * root){
	node_t * temp;
	temp = root->left;
	if(temp != nil){
		while(temp->right != nil)
			temp = temp->right;
		return temp;
	}
	else{
		temp = root->parent;
		while(temp != nil && root == temp->left){
			root = temp;
			temp = temp->parent;
		}
		return temp;
	}
	return temp;
}
node_t* rb_max(node_t* root){
	if(root == nil)
		return nil;
	while(root->right != nil){
		root = root->right;
	}
	return root;
}
void rb_delete_tree(node_t* node){
	if(node == nil)
		return;
	rb_delete_tree(node->left);
	rb_delete_tree(node->right);
	free(node);
	return;
}

int dic_order(char* str1,char* str2){
    int i;
    for(i=0;str1[i] != '\0' && str2[i] != '\0';i++){
        if(str1[i] < str2[i])
            return 1;
        else if(str1[i] > str2[i])
            return 0;
    }
    if(str1[i] == '\0' && str2[i] != '\0')
        return 1;
    if(str2[i] == '\0' && str1[i] != '\0')
        return 0;
    return 2;
}
void rb_print2DUtil(node_t *root, int space)
{
    if (root == nil)
        return;
    space += COUNT;
    rb_print2DUtil(root->right, space);
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%s\n", root->entity);
    rb_print2DUtil(root->left, space);
}