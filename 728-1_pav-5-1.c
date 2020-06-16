#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
struct Derevo
{
	struct Derevo *Praviy;
	struct Derevo *Leviy;
	double Znach;
};
void init(struct Derevo **t)
{
	*t = (struct Derevo *)malloc(sizeof(struct Derevo));
	(*t)->Praviy = NULL;
	(*t)->Leviy = NULL;
	(*t)->Znach = 2147483648;
}
void clean(struct Derevo *t)
{
	if (t != NULL)
	{
		if (t->Praviy != NULL)
			clean(t->Praviy);
		if (t->Leviy != NULL)
			clean(t->Leviy);
		free(t);
	}
}
struct Derevo* find(struct Derevo *t, int value)
{
	if (t->Znach==value)
		return t;
	else
	{
		if (value < t->Znach)
		{
			if (t->Leviy != NULL)
				return(find(t->Leviy, value));
			else
				return NULL;
		}
		else
		{
			if (t->Praviy != NULL)
				return(find(t->Praviy, value));
			else
				return NULL;
		}
	}
}
int find_with_output(struct Derevo *t, int value)
{
	if (t-> Znach == value)
	{
		printf("_ ");
		if (t->Leviy != NULL)
			printf("%d ", (int)t->Leviy->Znach);
		else
			printf("_ ");
		if (t->Praviy != NULL)
			printf("%d", (int)t->Praviy->Znach);
		else
			printf("_");
	}
	else
	{
		if (value < t->Znach)
		{
			if (t->Leviy != NULL)
			{
				if (t->Leviy->Znach == value)
				{
					printf("%d ", (int)t->Znach);
					if ((t->Leviy->Leviy) != NULL)
						printf("%d ", (int)t->Leviy->Leviy->Znach);
					else
						printf("_ ");
					if ((t->Leviy->Praviy) != NULL)
						printf("%d", (int)t->Leviy->Praviy->Znach);
					else
						printf("_");
				}
				else
					return(find_with_output(t->Leviy, value));
			}
			else
				return 1;
		}
		else
		{
			if (t->Praviy != NULL)
			{
				if (t->Praviy->Znach == value)
				{
					printf("%d ", (int)t->Znach);
					if ((t->Praviy->Leviy) != NULL)
						printf("%d ", (int)t->Praviy->Leviy->Znach);
					else
						printf("_ ");
					if ((t->Praviy->Praviy) != NULL)
						printf("%d", (int)t->Praviy->Praviy->Znach);
					else
						printf("_");
				}
				else
					return(find_with_output(t->Praviy, value));
			}
			else
				return 1;
		}
	}
	return 0;
}
int insert(struct Derevo *t, int value)
{
	if (t->Znach == 2147483648)
	{
		t->Znach = value;
		return 0;
	}
	if (t->Znach == value)
		return 1;
	if (value > (t->Znach))
	{
		if ((t->Praviy)!=NULL)
			return(insert(t->Praviy, value));
		else
		{
			t->Praviy=(struct Derevo *)malloc(sizeof(struct Derevo));
			t->Praviy->Praviy = NULL;
			t->Praviy->Leviy = NULL;
			t->Praviy->Znach = value;
			return 0;
		}
	}
	else
	{
		if ((t->Leviy) != NULL)
			return(insert(t->Leviy, value));
		else
		{
			t->Leviy = (struct Derevo *)malloc(sizeof(struct Derevo));
			t->Leviy->Praviy = NULL;
			t->Leviy->Leviy = NULL;
			t->Leviy->Znach = value;
			return 0;
		}
	}
}
int deep(struct Derevo *t)
{
	int r=0, l=0;
	if ((t->Praviy) != NULL)
		r=deep(t->Praviy);
	if ((t->Leviy) != NULL)
		l = deep(t->Leviy);
	if (r > l)
		return (r+1);
	return (l+1);
}
int remove_node(struct Derevo **t, int value)
{
	if ((*t)->Znach == value)
	{
		if ((*t)->Praviy != NULL)
		{
			struct Derevo *Temp = (*t)->Praviy, *Temp2;
			if (Temp->Leviy != NULL)
			{
				while (Temp->Leviy->Leviy != NULL)
					Temp = Temp->Leviy;
				(*t)->Znach = Temp->Leviy->Znach;
				Temp2=Temp->Leviy;
				Temp->Leviy=Temp2->Praviy;
				free(Temp2);
			}
			else
			{
				struct Derevo *Temp;
				(*t)->Znach = (*t)->Praviy->Znach;
				Temp = (*t)->Praviy;
				(*t)->Praviy = (*t)->Praviy->Praviy;
				free(Temp);
			}
		}
		else
		{
			struct Derevo *Temp;
			Temp = (*t);
			(*t) = (*t)->Leviy;
			free(Temp);
			Temp = NULL;
		}
		return 0;
	}
	else
	{
		if (value < ((*t)->Znach))
		{
			if ((*t) -> Leviy != NULL)
				return(remove_node(&((*t)->Leviy), value));
			else
				return 1;
		}
		else
		{
			if (((*t)->Praviy) != NULL)
				return(remove_node(&((*t)->Praviy), value));
			else
				return 1;
		}
	}
}
int remove_min(struct Derevo *t)
{
	struct Derevo *Temp = t, *Temp2;
	if (Temp->Leviy != NULL)
	{
		while (Temp->Leviy->Leviy != NULL)
			Temp = Temp->Leviy;
		Temp2 = Temp->Leviy;
		Temp->Leviy = Temp2->Praviy;
		free(Temp2);
	}
	else
	{
		Temp = t->Praviy;
		free(t);
		t = Temp;
	}
	return 0;
}
int rotate_right(struct Derevo **t)
{
	if (*t == NULL)
		return 1;
	struct Derevo *A, *B, *C=(*t)->Praviy, *x=(*t)->Leviy, *y=(*t), *Temp = (struct Derevo *)malloc(sizeof(struct Derevo));
	if (x != NULL)
	{
		A = x -> Leviy;
		B = x -> Praviy;
	}
	else
		return 1;
	Temp->Praviy = y;
	Temp->Leviy = A;
	Temp->Praviy->Praviy = C;
	Temp->Praviy->Leviy = B;
	Temp->Znach= x->Znach;
	free(x);
	(*t) = Temp;
	return 0;
}
int rotate_left(struct Derevo **t)
{
	if (*t == NULL)
		return 1;
	struct Derevo *A = (*t)->Leviy, *B, *C, *x = (*t), *y = (*t)->Praviy, *Temp=(struct Derevo *)malloc(sizeof(struct Derevo));
	if (y != NULL)
	{
		B = y->Leviy;
		C = y->Praviy;
	}
	else
		return 1;
	Temp->Praviy = C;
	Temp->Leviy = x;
	Temp->Leviy->Praviy = B;
	Temp->Leviy->Leviy = A;
	Temp->Znach = y->Znach;
	free(y);
	(*t) = Temp;
	return 0;
}
int print_tree(struct Derevo *t)
{
	if (t == NULL)
	{
		printf("-\n");
		return 1;
	}
	struct Derevo *Temp=t;
	int Rank=0, i, j, k, sk;
	int *comb;
	Rank = deep(t);
	comb = (int*)malloc(sizeof(int));
	for (i = 0; i < Rank; i++)
	{
		if (i != 0)
		{
			comb = (int*)realloc(comb, i* sizeof(int));
			for (j = 0; j < i; j++)
				comb[j] = 0;
		}
		j = 1;
		sk = i;
		while (sk != 0)
		{
			j = j * 2;
			sk--;
		}
		while (j != 0)
		{
			k = 0;
			Temp = t;
			for (k = 0; k < i; k++)
			{
				if (comb[k] == 0)
				{
					if ((Temp -> Leviy) != NULL)
						Temp = Temp->Leviy;
					else
					{
						k = -1;
						break;
					}
				}
				else
				{
					if ((Temp->Praviy) != NULL)
						Temp = Temp->Praviy;
					else
					{
						k = -1;
						break;
					}
				}
			}
			if (i != 0)
			{
				sk=i-1;
				comb[sk]++;
				while (1)
				{
					if (comb[sk] == 2)
					{
						comb[sk] = 0;
						sk--;
						if (sk < 0)
							break;
						else
							comb[sk]++;
					}
					else
						break;
				}
			}
			if (k==-1)
				printf("_");
			else
				printf("%d", (int)Temp->Znach);
			j--;
			if (j != 0)
				printf(" ");
		}
		printf("\n");
	}
	return 1;
}
int all(struct Derevo *t)
{
	if (t == NULL)
		return 0;
	int r, l;
	l = all(t->Leviy);
	r = all(t->Praviy);
	return (l + r+1);
}
int main()
{
	struct Derevo *t;
	int i;
	double a;
	init(&t);//1 пункт
	for (i = 0; i < 4; i++)
	{
		scanf("%lf", &a);
		insert(t, a);
	}
	print_tree(t);//2 пункт
	printf("\n");
	for (i = 0; i < 3; i++)//3 пункт
	{
		scanf("%lf", &a);
		insert(t, a);
	}
	print_tree(t);//4 пункт
	printf("\n");
	for (i = 0; i < 2; i++)
	{
		scanf("%lf", &a);//5 и 6 пункт
		a = find_with_output(t, a);
		if (a == 1)
			printf("-");
		printf("\n\n");
	}
	scanf("%lf", &a);//7 пункт
	remove_node(&t, a);
	print_tree(t);//8 пункт
	printf("\n");
	while (1)//9 пункт
	{
		a=rotate_left(&t);
		if (a == 1)
			break;
	}
	print_tree(t);//10 пункт
	printf("\n");
	while (1)//11 пункт
	{
		a = rotate_right(&t);
		if (a == 1)
			break;
	}
	print_tree(t);//12 пункт
	printf("\n");
	printf("%d\n\n", all(t));//13 пункт
	clean(t);//14 пункт
	t = NULL;
	print_tree(t);//15 пункт
	return 0;
}