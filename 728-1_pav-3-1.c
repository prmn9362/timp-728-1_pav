#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    int value;         
    struct node *next; 
} node;

typedef struct list
{
    struct node *head; 
} list;

void init(list *l)
{
    l->head = NULL;
}

void clean(list *l)
{
    if (l->head != NULL)
    {
        node *tmp = NULL;
        while (l->head->next)
        {
            tmp = l->head;
            l->head = l->head->next;
            free(tmp);
        }
        free(l->head);
        tmp = NULL;
        l->head = NULL;
    }
    else
        printf("Error");
}

bool is_empty(list *l)
{
    if (l->head)
        return true;
    else
        return false;
}

node *find(list *l, int value)
{
    node *tmp = l->head;
    while ((tmp != NULL) && (tmp->value != value))
        tmp = tmp->next;
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
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = malloc(sizeof(node));
        tmp->next->value = value;
        tmp->next->next = NULL;
        tmp = NULL;
        return 0;
    }
    else
    {
        node *tmp = malloc(sizeof(node));
        tmp->value = value;
        tmp->next = l->head;
        l->head = tmp;
        tmp = NULL;
        return 0;
    }
}

int push_front(list *l, int value)
{
    node *tmp = malloc(sizeof(node));
    tmp->value = value;
    tmp->next = l->head;
    l->head = tmp;
    tmp = NULL;
    return 0;
}

int insert_after(node *n, int value)
{
    if (n!=NULL)
    {
    node *tmp = malloc(sizeof(node));
    tmp->value = value;
    tmp->next = n->next;
    n->next = tmp;
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
        tmp = tmp->next;
        ++index;
    }
    return tmp;
}

int remove_node(list *l, int value)
{
    if (l->head == NULL)
        return 1;
    else
    {
        node *tmp = l->head;
        node *txp = NULL;
        while (tmp != NULL)
        {
            if (tmp->value == value)
            {
                if (txp == NULL)
                {
                    l->head = tmp->next;
                    free(tmp);
                    tmp = NULL;
                    return 0;
                }
                txp->next = tmp->next;
                free(tmp);
                tmp = NULL;
                return 0;
            }
            txp = tmp;
            tmp = tmp->next;
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
        tmp = tmp->next;
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

    print(&l);
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
    insert_after(usel, x);

    print(&l);
    printf("\n");

    int z;
    (void)scanf("%d", &z);
    remove_node(&l, z);

    print(&l);
    printf("\n");

    clean(&l);

    bool b = is_empty(&l);

    return 0;
}