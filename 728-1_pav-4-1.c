#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
	int value;		   
	struct node *posl;
	struct node *pred;
} node;

typedef struct list
{
	struct node *head; 
	struct node *tail; 
} list;

void init(list *l)
{
	l->head = NULL;
	l->tail = NULL;
}

void clean(list *l)
{
	if (l->head != NULL)
	{

		node *tmp = NULL;
		while (l->head->posl)
		{
			tmp = l->head;
			l->head = l->head->posl;
			free(tmp);
		}
		free(l->head);
		l->head = NULL;
		l->tail = NULL;
		tmp = NULL;
	}
	else
		printf("Error");
}

bool is_empty(list *l)
{
	if (l->head != NULL)
		return false;
	else
		return true;
}

node *find(list *l, int value)
{
	node *tmp = l->head;
	while ((tmp != NULL) && (tmp->value != value))
		tmp = tmp->posl;
	if (tmp == NULL)
	{
		printf("0 ");
		return NULL;
	}
	else
	{
		printf("1 ");
		tmp = NULL;
	}
}

int push_back(list *l, int value)
{
	if (l->head != NULL)
	{
		node *tmp = l->head;
		while (tmp->posl != NULL)
			tmp = tmp->posl;
		tmp->posl = malloc(sizeof(node));
		tmp->posl->value = value;
		tmp->posl->pred = tmp;
		tmp->posl->posl = NULL;
		l->tail = tmp->posl;
		tmp = NULL;
		return 0;
	}
	else
	{
		node *tmp = malloc(sizeof(node));
		tmp->value = value;
		tmp->posl = l->head;
		l->head = tmp;
		l->head->pred = NULL;
		l->tail = tmp;
		tmp = NULL;
		return 0;
	}
}

int push_front(list *l, int value)
{
	node *tmp = malloc(sizeof(node));
	tmp->value = value;
	tmp->posl = l->head;
	tmp->pred = NULL;
	l->head->pred = tmp;
	l->head = tmp;
	tmp = NULL;
	return 0;
}

int insert_after(list *l, node *n, int value)
{
	if (n != NULL)
	{
		node *tmp = malloc(sizeof(node));
		tmp->value = value;
		tmp->posl = n->posl;
		tmp->pred = n;
		if (n->posl != NULL)
			n->posl->pred = tmp;
		else
			l->tail = tmp;
		n->posl = tmp;
		tmp = NULL;
		return 0;
	}
	else
	{
		printf("Error");
		return 2;
	}
}

int insert_before(list *l, node *n, int value)
{
	if (n != NULL)
	{
		node *tmp = malloc(sizeof(node));
		tmp->value = value;
		tmp->posl = n;
		tmp->pred = n->pred;
		if (n->pred != NULL)
			n->pred->posl = tmp;
		else
			l->head = tmp;
		n->pred = tmp;
		tmp = NULL;
		return 0;
	}
	else
	{
		printf("Error");
		return 2;
	}
}


node *list_index(list *l, int j)
{
	node *tmp = l->head;
	int index = 0;
	while (index != j - 1 && tmp != NULL)
	{
		tmp = tmp->posl;
		++index;
	}
	return tmp;
}

int remove_first(list *l, int value)
{
	if (l->head == NULL)
		return 1;
	else
	{
		node *tmp = l->head;
		while (tmp->posl != NULL)
		{
			if (tmp->value == value)
			{
				if (tmp->pred == NULL)
				{
					l->head = tmp->posl;
					l->head->pred = NULL;
					free(tmp);
					tmp = NULL;
					return 0;
				}
				tmp->pred->posl = tmp->posl;
				tmp->posl->pred = tmp->pred;
				free(tmp);
				tmp = NULL;
				return 0;
			}
			tmp = tmp->posl;
		}
		if (tmp->value == value)
		{
			l->tail = tmp->pred;
			l->tail->posl = NULL;
			free(tmp);
			tmp = NULL;
			return 0;
		}
		return 1;
	}
}

int remove_last(list *l, int value)
{
	if (l->head == NULL)
		return 1;
	else
	{
		node *tmp = l->tail;
		while (tmp->pred != NULL)
		{
			if (tmp->value == value)
			{
				if (tmp->posl == NULL)
				{
					l->tail = tmp->pred;
					l->tail->posl = NULL;
					free(tmp);
					tmp = NULL;
					return 0;
				}
				tmp->posl->pred = tmp->pred;
				tmp->pred->posl = tmp->posl;
				free(tmp);
				tmp = NULL;
				return 0;
			}
			tmp = tmp->pred;
		}
		if (tmp->value == value)
		{
			l->head = tmp->posl;
			l->head->pred = NULL;
			free(tmp);
			tmp = NULL;
			return 0;
		}
		return 1;
	}
}

void print(list *l)
{
	node *tmp = l->head;
	while (tmp != NULL)
	{
		printf("%d ", tmp->value);
		tmp = tmp->posl;
	}
}

void print_invers(list *l)
{
	node *tmp = l->tail;
	while (tmp != NULL)
	{
		printf("%d ", tmp->value);
		tmp = tmp->pred;
	}
}

int main()
{
	int n;
	(void)scanf("%d", &n);

	list l;
	init(&l);

	int a;
	for (int i = 1; i <= n; ++i)
	{
		(void)scanf("%d", &a);
		push_back(&l, a);
	}

	print(&l);
	printf("\n");

	for (int k = 1; k <= 3; ++k)
	{
		(void)scanf("%d", &a);
		find(&l, a);
	}
	printf("\n");

	int m;
	(void)scanf("%d", &m);
	push_back(&l, m);

	print_invers(&l);
	printf("\n");

	int t;
	(void)scanf("%d", &t);
	push_front(&l, t);

	print(&l);
	printf("\n");

	int j, x;
	(void)scanf("%d", &j);
	(void)scanf("%d", &x);
	node *usel = list_index(&l, j);
	insert_after(&l, usel, x);

	print_invers(&l);
	printf("\n");

	int u, y;
	(void)scanf("%d", &u);
	(void)scanf("%d", &y);
	node *xsel = list_index(&l, u);
	insert_before(&l, xsel, y);


	print(&l);
	printf("\n");

	int z;
	(void)scanf("%d", &z);
	remove_first(&l, z);

	print_invers(&l);
	printf("\n");

	int r;
	(void)scanf("%d", &r);
	remove_last(&l, r);

	print(&l);
	printf("\n");

	clean(&l);

	bool b = is_empty(&l);

	return 0;
}