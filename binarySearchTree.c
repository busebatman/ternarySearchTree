#include <stdio.h>

struct tst{
	int data;
	struct tst* left;
	struct tst* right;
	struct tst* middle;
};
typedef struct tst node;

node * getNode(int data) {
	node * _node = (node *)malloc(sizeof(struct tst));
	_node->data = data;
	_node->left = NULL;
	_node->middle = NULL;
	_node->right = NULL;
	return _node;
}

void insert(node ** tree, int key) {
    if (!(*tree)) {
    	*tree = getNode(key);
        return;
    }
    if (key < ((*tree)->data)) {
        insert(&(*tree)->left, key);
    }
    else if (key > ((*tree)->data) && key <= (((*tree)->data) * ((*tree)->data))) {
        insert(&(*tree)->middle, key);
    }
    else {
        insert(&(*tree)->right, key);
    }
}

node * find(node * tree, int key) {
	node * res = NULL;
    if (!tree) {
    	printf("NOT FOUND!\n");
        return res;
    }
    else if (tree->left && key == tree->left->data) {
    	res = tree->left;
    	printf("FOUND : %d\n", res->data);
        return res;
    }
    else if (tree->middle && key == tree->middle->data) {
    	res = tree->middle;
    	printf("FOUND : %d\n", res->data);
        return res;
    }
    else if (tree->right && key == tree->right->data) {
    	res = tree->right;
    	printf("FOUND : %d\n", res->data);
        return res;
    }
    else if(tree && key == tree->data){
    	printf("FOUND : %d\n", tree->data);
    	return tree;
	}

    if (key < (tree->data)) {
    	return find(tree->left, key);
    }
    else if (key > (tree->data) && key <= ((tree->data) * (tree->data))) {
        return find(tree->middle, key);
    }
    else {
        return find(tree->right, key);
    }
}

node * findAndDetach(node * tree, int key) {
	node * res = NULL;
    if (!tree) {
        return res;
    }
    else if (tree->left && key == tree->left->data) {
    	res = tree->left;
    	tree->left = NULL;
        return res;
    }
    else if (tree->middle && key == tree->middle->data) {
    	res = tree->middle;
    	tree->middle = NULL;
        return res;
    }
    else if (tree->right && key == tree->right->data) {
    	res = tree->right;
    	tree->right = NULL;
        return res;
    }

    if (key < (tree->data)) {
    	return findAndDetach(tree->left, key);
    }
    else if (key > (tree->data) && key <= ((tree->data) * (tree->data))) {
        return findAndDetach(tree->middle, key);
    }
    else {
        return findAndDetach(tree->right, key);
    }
}

void insertTree(node ** tree, node * newTree) {
	if (newTree) {
		insert(tree, newTree->data);
		insertTree(tree, newTree->left);
		insertTree(tree, newTree->middle);
		insertTree(tree, newTree->right);
		free(newTree);
	}
}

void removeFromTree(node ** tree, int key) {
	//if delete root
	if ((*tree)->data == key) {
		node * root = NULL;
		node * detached = (*tree);
		insertTree(&root, detached->left);
		insertTree(&root, detached->middle);
		insertTree(&root, detached->right);
		*tree = root;
	}
	else {
		node * detached = findAndDetach(*tree, key);
		if (!detached) {
			printf("NOT FOUND!\n");
			return;
		}
		insertTree(tree, detached->left);
		insertTree(tree, detached->middle);
		insertTree(tree, detached->right);
	}
}

void printNLMR(node * tree){
    if (tree) {
        printf("%d\n", (tree)->data);
        printNLMR((tree)->left);
        printNLMR((tree)->middle);
        printNLMR((tree)->right);
    }
}

void printLNMR(node * tree){
    if (tree) {
        printLNMR((tree)->left);
        printf("%d\n", (tree)->data);
        printLNMR((tree)->middle);
        printLNMR((tree)->right);
    }
}

int main() {
	node * root = NULL;
	FILE *inpf;
	inpf = fopen("input.txt", "r");
	while(!feof(inpf)) {
		int key;
		fscanf(inpf, "%d", &key);
		insert(&root, key);
	}
	fclose(inpf);
	
	printf("Press:\n1 to print LNMR\n2 to print NLMR\n3 to find an element\n4 to remove an element\n\n0 to exit:");
	int option, num;
	do{
	scanf("%d", &option);
		switch(option) {
		case 1: printLNMR(root); break;
		case 2: printNLMR(root); break;
		case 3: printf("Enter the value to find: "); scanf("%d", &num); find(root, num); break;
		case 4: printf("Enter the value to remove: "); scanf("%d", &num); removeFromTree(&root, num); break;
		case 0: return;
		default : printf("Invalid option\n" ); break;
		}
	}
	while(option!=0);
	return 1;
}
