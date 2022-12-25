#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

struct t_node
{
	char *name;
	int ptd;
	struct t_node *next_dfile;
	struct t_node *next_file;
};

static struct t_node *create_tree(char *);
void print_tree(struct t_node *);
static struct t_node *create_tnode(char *);
int count;

DIR *dir = NULL;
struct t_node *tstart = NULL;


int main(int args, char **argv)
{
	tstart = create_tnode(".");

	if (args > 2)
	{
		printf("\n USAGE : ./a.out [PATH]");
		exit(0);
	}

	tstart->ptd = TRUE;
	char* a = getcwd(0, 0);
	(tstart->next_dfile) = create_tree(((args == 2) ? argv[1] : a));
	print_tree(tstart);

	// free(tstart);
	free(a);
	
	return 0;
}

static struct t_node *create_tree(char *root_name)
{
	dir = opendir(root_name);
	struct dirent *dr = {NULL};
	struct t_node *ptr_tstart = NULL, *temp = NULL, *temp1 = NULL;
	char *name = (char *)calloc(2000, sizeof(char));

	if (dir == NULL)
	{
		printf("\nFailed to open ..!!");
		printf(" : %s", root_name);
		return NULL;
	}

	while ((dr = readdir(dir)) != NULL)
	{
		if (strcmp((dr->d_name), ".") != 0 && strcmp((dr->d_name), "..") != 0)
			temp = create_tnode(dr->d_name);
		else
		{
			temp = NULL;
			continue;
		}

		if (temp1 != NULL)
		{
			temp1->next_file = temp;
		}
		else
		{
			(ptr_tstart) = temp;
		}

		if ((dr->d_type) == DT_DIR)
		{
			temp->ptd = TRUE;
			strcpy(name, root_name);
			(temp->next_dfile) = create_tree((strcat((strcat(name, "/")), dr->d_name)));
			strcpy(name, root_name);
		}
		else
		{
			(temp)->ptd = FALSE;
			(temp)->next_dfile = NULL;
		}

		temp1 = temp;
	}
	free(name);
	return (ptr_tstart);
}

static struct t_node *create_tnode(char *n)
{
	struct t_node *temp = (struct t_node *)malloc(sizeof(struct t_node));
	temp->name = n;
	temp->next_dfile = NULL;
	temp->next_file = NULL;
	return temp;
}

void print_tree(struct t_node *start)
{
	char *s = "- ", *s1 = "  ";
	struct t_node *temp = start;
	int i;

	if (start == NULL)
		return;

	for (i = 0; i < (count - 1); i++)
		printf("%s", s1);
	if (count > 0)
		printf("%s", s);

	printf("%s", temp->name);
	printf("\n");

	if (temp->ptd == TRUE)
	{
		count++;
		print_tree(temp->next_dfile);
		count--;
	}
	print_tree(temp->next_file);
}