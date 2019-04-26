#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4996) 

typedef struct WordInfo // 단어 정보를 저장할 구조체
{
	char word[50]; // 단어
	char wclass[10]; // 품사
	char meaning[1000]; // 뜻
}WordInfo;



typedef struct TreeNode {
	WordInfo *key;
	struct TreeNode *p;
	struct TreeNode *left, *right;
}TreeNode;



WordInfo wInfo[200000];
int size = 0; // 단어 개수

/*
TreeNode delete_node(TreeNode **root, TreeNode *key )
{
	TreeNode *parent, *child, *suc, *suc_p, *t;

	// key를 갖는 노드 t를 탐색한다. parent는 t의 부모노드다.
	parent = NULL; // 시초가 되는 root의 부모는 없다.
	t = *root;

	// key를 갖는 노드 t를 탐색한다.
	while (t != NULL && t->key != key)
	{
		parent = t; // 부모를 t값과 동일하게 준 후 t를 통해 탐색한다.
					// t는 왼쪽이나 key값에 따라 왼쪽이나 오른쪽으로 내려간다.
		t = (key < parent->key) ? parent->left : parent->right;
		printf("Deleted successfully");
	}

	// 탐색이 끝난 시점에서 만약 키 값이 트리에 없었다면 t는 NULL일 것이다.
	if (!t)
	{
		printf("key is not in the tree");
		return; // 원하는 값이 없으므로 return 한다.
	}
	// 위에서 탐색을 못했을 경우를 다뤘기 때문에 이 아래부터는 탐색이
	// 성공적으로 이루어졌다는 가정 하에 경우의 수를 따진다.

	// 첫 번째: 단말노드였을 경우
	if (t->left == NULL && t->right == NULL)
	{
		if (parent) // 부모 노드가 NULL이 아닐 때, 즉 존재할 때
		{
			if (parent->left == t)
				parent->left = NULL;
			else
				parent->right = NULL;
		}
		else // 부모 노드가 NULL 이라면, 삭제하려는 노드가 루트 노드다.
			*root = NULL;
	}
	// 두 번째: 하나의 서브트리만 가지는 경우
	else if ((t->left == NULL) || (t->right == NULL))
	{
		child = (t->left != NULL) ? t->left : t->right;
		if (parent)
		{
			if (parent->left == t)
				parent->left = child;
			else
				parent->right = child;
		}
		else // 부모 노드가 NULL이라면 삭제되는 노드가 루트노드다.
			*root = child;
	}
	// 세 번째: 두개의 서브트리를 모두 가지는 경우
	else
	{
		// 오른쪽 서브트리에서 가장 작은 값을 찾는다.
		suc_p = t;
		suc = t->right;
		while (suc->left != NULL)
		{
			suc_p = suc;
			suc = suc->left;
		}
		// 후속자의 부모와 자식을 연결
		if (suc_p->left == suc)
			suc_p->left = suc->right;
		else
			suc_p->right = suc->right;
	}
}*/


// key를 이진 탐색 트리 root에 삽입한다.
// key가 이미  안에 있으면 삽입되지 않는다.
void insert_node(TreeNode **root, WordInfo *key)
{
	// t는 탐색을 위한 포인터다.
	TreeNode *p, *t; // p는 부모노드를 가리키는 포인터, t는 현재노드 포인터
	TreeNode *n; // n은 새로운 노드

	t = *root; // 처음 시작시 현재 노드는 root 그 자체다.
	p = NULL; // root의 부모노드는 없다. root 자체가 시초

			  // 탐색을 먼저 수행한다.
	while (t)
	{
		if (key == t->key)	return;
		p = t; // 부모 노드를 현재 노드로 설정한다. 새로운 루트노드.
			   // 서브트리의 새로운 루트노드가 등장하는 것과 같은 원리다.

		if (strcmp(p->key->word, key->word)>0) // 부모의 키 값과 비교
			t = p->left; // 현재 노드는 부모의 왼쪽 서브트리가 된다.
		else
			t = p->right; // 현재 노드는 부모의 오른쪽 서브트리가 된다.
	}
	// key가 트리 안에 없으므로 삽입이 가능하다.

	// 새로 삽입될 노드를 생성한다.
	n = (TreeNode *)malloc(sizeof(TreeNode));
	if (!n)	return; // 동적할당 실패했을 경우 return

					// 데이터를 복사한다.
	if (p) // 부모 노드가 존재할 경우
	{
		if (strcmp(p->key->word, key->word)>0)
			p->left = n;
		else
			p->right = n;
	}
	else // 부모 노드가 없으니 새로 생긴 노드가 루트노드가 된다.
		*root = n;
}


int readLine(FILE *fp, char str[], int limit)
{ // 한 줄 읽기
	int ch, i = 0;
	while ((ch = fgetc(fp)) != '\n' && ch != EOF)
	{
		if (i<limit - 1)
			str[i++] = ch;
	}
	str[i] = '\0';
	return i;
}

TreeNode *search(TreeNode *x, char word[])
{
	if (x == NULL || strcmp(word, x->key->word) == 0) return x;
	if (strcmp(word, x->key->word) < 0) return search(x->left, word);
	else return search(x->right, word);

}
TreeNode *sw(TreeNode *h, char gsword[])
{
if(h== NULL)
 return NULL;
int cmp = strcmp(gsword,h->key->word);

if(cmp == -1)
sw(h->left,gsword);
else if(cmp == 1)
sw(h->right, gsword);
else
return h;
}

void searchword(TreeNode *h)
{
if(h == NULL)
{
 printf("저장된 단어가 없음.\n");
return;
}
char sword[30];

printf("검색할 단어 입력:");
gets(sword);

TreeNode *gn;
gn = sw(h,sword);

if(gn == NULL)
 printf("찾는 단어 없음.\n");
else
printf("찾은 단어의 뜻:%s\n",gn->key->meaning);
}

int main()
{
	
	char filename[50];
	FILE *fp = fopen("shuffled_dict.txt", "r");
    TreeNode *root = NULL,*tmp;
    WordInfo *ee;

	while (!feof(fp))
	{
		char buffer[1500] = { 0, };
		fflush(stdin);
		TreeNode *root = NULL;

		readLine(fp, buffer, sizeof(buffer));
		if (strcmp(buffer, "\0") != 0)
		{
			int len = strlen(buffer);
			int s = 0, e = 0;
			int isClassEnded = 0;

			for (int i = 0; i < len; i++)
			{
				if (!isClassEnded)
				{
					if (buffer[i] == '(')
					{
						strncpy(wInfo[size].word, buffer, e - 1);
						s = e;
					}
					else if (buffer[i] == ')')
					{
						strncpy(wInfo[size].wclass, buffer + s, e - s + 1);
						s = e;
						isClassEnded = 1;
					}
					e++;
				}
			}
			strcpy(wInfo[size].meaning, buffer + s + 2);
			size++;
		}
		insert_node(&root, wInfo);
	}
	
	char command[10];
	int isread = 0;


	while (1)
	{
		printf("$ ");
		scanf("%s", command);
     
	

			if (strcmp(command, "size") == 0) // 사이즈 출력
			{
				printf("%d\n", size);
			}
		
			else if (strcmp(command, "add") == 0) {

				WordInfo *word1 = (WordInfo *)malloc(sizeof(WordInfo));
				gets(word1->word);
				printf("word: ");
				gets(word1->word);
				
				printf("class: ");
				gets(word1->wclass);
				
				printf("meaning: ");
				gets(word1->meaning);
				insert_node(&root, word1);
			}
			
		    
			
		}

		free(fp);
	}
	
    
	

