#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4996) 

typedef struct WordInfo // �ܾ� ������ ������ ����ü
{
	char word[50]; // �ܾ�
	char wclass[10]; // ǰ��
	char meaning[1000]; // ��
}WordInfo;



typedef struct TreeNode {
	WordInfo *key;
	struct TreeNode *p;
	struct TreeNode *left, *right;
}TreeNode;



WordInfo wInfo[200000];
int size = 0; // �ܾ� ����

/*
TreeNode delete_node(TreeNode **root, TreeNode *key )
{
	TreeNode *parent, *child, *suc, *suc_p, *t;

	// key�� ���� ��� t�� Ž���Ѵ�. parent�� t�� �θ����.
	parent = NULL; // ���ʰ� �Ǵ� root�� �θ�� ����.
	t = *root;

	// key�� ���� ��� t�� Ž���Ѵ�.
	while (t != NULL && t->key != key)
	{
		parent = t; // �θ� t���� �����ϰ� �� �� t�� ���� Ž���Ѵ�.
					// t�� �����̳� key���� ���� �����̳� ���������� ��������.
		t = (key < parent->key) ? parent->left : parent->right;
		printf("Deleted successfully");
	}

	// Ž���� ���� �������� ���� Ű ���� Ʈ���� �����ٸ� t�� NULL�� ���̴�.
	if (!t)
	{
		printf("key is not in the tree");
		return; // ���ϴ� ���� �����Ƿ� return �Ѵ�.
	}
	// ������ Ž���� ������ ��츦 �ٷ�� ������ �� �Ʒ����ʹ� Ž����
	// ���������� �̷�����ٴ� ���� �Ͽ� ����� ���� ������.

	// ù ��°: �ܸ���忴�� ���
	if (t->left == NULL && t->right == NULL)
	{
		if (parent) // �θ� ��尡 NULL�� �ƴ� ��, �� ������ ��
		{
			if (parent->left == t)
				parent->left = NULL;
			else
				parent->right = NULL;
		}
		else // �θ� ��尡 NULL �̶��, �����Ϸ��� ��尡 ��Ʈ ����.
			*root = NULL;
	}
	// �� ��°: �ϳ��� ����Ʈ���� ������ ���
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
		else // �θ� ��尡 NULL�̶�� �����Ǵ� ��尡 ��Ʈ����.
			*root = child;
	}
	// �� ��°: �ΰ��� ����Ʈ���� ��� ������ ���
	else
	{
		// ������ ����Ʈ������ ���� ���� ���� ã�´�.
		suc_p = t;
		suc = t->right;
		while (suc->left != NULL)
		{
			suc_p = suc;
			suc = suc->left;
		}
		// �ļ����� �θ�� �ڽ��� ����
		if (suc_p->left == suc)
			suc_p->left = suc->right;
		else
			suc_p->right = suc->right;
	}
}*/


// key�� ���� Ž�� Ʈ�� root�� �����Ѵ�.
// key�� �̹�  �ȿ� ������ ���Ե��� �ʴ´�.
void insert_node(TreeNode **root, WordInfo *key)
{
	// t�� Ž���� ���� �����ʹ�.
	TreeNode *p, *t; // p�� �θ��带 ����Ű�� ������, t�� ������ ������
	TreeNode *n; // n�� ���ο� ���

	t = *root; // ó�� ���۽� ���� ���� root �� ��ü��.
	p = NULL; // root�� �θ���� ����. root ��ü�� ����

			  // Ž���� ���� �����Ѵ�.
	while (t)
	{
		if (key == t->key)	return;
		p = t; // �θ� ��带 ���� ���� �����Ѵ�. ���ο� ��Ʈ���.
			   // ����Ʈ���� ���ο� ��Ʈ��尡 �����ϴ� �Ͱ� ���� ������.

		if (strcmp(p->key->word, key->word)>0) // �θ��� Ű ���� ��
			t = p->left; // ���� ���� �θ��� ���� ����Ʈ���� �ȴ�.
		else
			t = p->right; // ���� ���� �θ��� ������ ����Ʈ���� �ȴ�.
	}
	// key�� Ʈ�� �ȿ� �����Ƿ� ������ �����ϴ�.

	// ���� ���Ե� ��带 �����Ѵ�.
	n = (TreeNode *)malloc(sizeof(TreeNode));
	if (!n)	return; // �����Ҵ� �������� ��� return

					// �����͸� �����Ѵ�.
	if (p) // �θ� ��尡 ������ ���
	{
		if (strcmp(p->key->word, key->word)>0)
			p->left = n;
		else
			p->right = n;
	}
	else // �θ� ��尡 ������ ���� ���� ��尡 ��Ʈ��尡 �ȴ�.
		*root = n;
}


int readLine(FILE *fp, char str[], int limit)
{ // �� �� �б�
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
 printf("����� �ܾ ����.\n");
return;
}
char sword[30];

printf("�˻��� �ܾ� �Է�:");
gets(sword);

TreeNode *gn;
gn = sw(h,sword);

if(gn == NULL)
 printf("ã�� �ܾ� ����.\n");
else
printf("ã�� �ܾ��� ��:%s\n",gn->key->meaning);
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
     
	

			if (strcmp(command, "size") == 0) // ������ ���
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
	
    
	

