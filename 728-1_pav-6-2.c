#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct uzel
{
    int data;
    struct uzel *leviy;
    struct uzel *praviy;
    struct uzel *roditel;
} uzel;


typedef struct tree
{
    struct uzel *golova;
} tree;


void init(tree *t)
{
    t -> golova = NULL;
}


typedef struct Stack {
    size_t size;
    size_t max;
    uzel **data;
} Stack;

Stack* add_Stack() {
    Stack *tmp = (Stack*) malloc(sizeof(Stack));
    tmp -> max = 7;
    tmp -> size = 0;
    tmp -> data = (uzel**) malloc(tmp->max * sizeof(uzel*));
    return tmp;
}

void freee(Stack **s)
{
    free((*s) -> data);
    free(*s);
    *s = NULL;
}


uzel *find(uzel *n, int value)
{
    if(n == NULL)
    {
        return NULL;
    }
    if(value == n -> data)
    {
        return n;
    }
    if (value < n -> data)
    {
      return find(n -> leviy, value);
    }
    else
    {
      return find(n -> praviy, value);
    }
}

uzel *add_Uzel(int value)
{
    uzel *root =  (uzel *)malloc(sizeof(uzel));
    root -> data = value;
    root -> leviy = root -> praviy = root -> roditel = NULL;
    return root;
}


int insert(uzel *n, uzel *root)
{
   while (n != NULL)
   {
        if (root->data > n->data)
        {
            if (n->praviy == NULL)
            {
                root->roditel = n;
                n->praviy = root;
                return 0;
            }
            else
            {
                n = n->praviy;
            }
        }
        else
        {
            if (root->data < n->data)
            {
                if (n->leviy == NULL)
                {
                   root->roditel = n;
                   n->leviy = root;
                   return 0;
                }
                else
                {
                    n = n->leviy;
                }
            }
            else
            {
                if (root->data == n->data)
                {
                    return 1;
                }
            }
        }
        
   }
}


uzel *min(uzel* n)
{
    uzel *current = n;
    while (current && current->leviy != NULL)
        current = current->leviy;
    return current;
}

uzel *max(uzel *n)
{
    uzel *current = n;
    while (current && current->praviy != NULL)
        current = current->praviy;
    return current;
}

uzel* delete(uzel* root, int value)
{
    if(root == NULL)
    {
        return root;
    }
   
    if (value < root -> data)
    {
        root -> leviy = delete(root -> leviy, value);
    }
    else if (value > root -> data)
    {
        root -> praviy = delete(root -> praviy, value);
    }
    else
    {
        if (root -> leviy == NULL)
        {
            uzel *temp = root -> praviy;
            free(root);
            return temp;
        }
        else if (root -> praviy == NULL)
        {
            uzel *temp = root -> leviy;
            free(root);
            return temp;
        }
        uzel* temp = min(root -> praviy);
        root -> data = temp -> data;
        root -> praviy = delete(root -> praviy, temp -> data);
    }
    return root;
    
}



int remove_min(uzel *n)
{
    int min_n = min(n) -> data;
    delete(n, min_n);
    return min_n;
}

uzel *rotate_left(uzel *n){
    uzel* n_leviy = n -> praviy;
    n -> praviy = n_leviy -> leviy;
    n_leviy -> leviy = n;
    return n_leviy;
}

uzel *rotate_right(uzel *n){
    uzel* n_praviy = n -> leviy;
    n -> leviy = n_praviy -> praviy;
    n_praviy -> praviy = n;
    return n_praviy;
}





void push(Stack *s, uzel *temp)
{
    if (s -> size >= s -> max)
    {
        s -> max *= 2;
        s -> data = (uzel**) realloc(s -> data, s -> max * sizeof(uzel*));
    }
    s -> data[s -> size++] = temp;
}

uzel* pop(Stack *s)
{
    if (s -> size == 0)
    {
        exit(7);
    }
    s -> size--;
    return s -> data[s -> size];
}

uzel* peek(Stack *s)
{
    return s -> data[s -> size-1];
}


void print(uzel *root) {
    Stack *s = add_Stack();
    while (s -> size != 0 || root != NULL)
    {
        if (root != NULL)
        {
            printf("%d ", root -> data);
            if (root -> praviy != NULL)
            {
                push(s, root -> praviy);
            }
            root = root -> leviy;
        }
        else
        {
            root = pop(s);
        }
    }
    freee(&s);
}


int main()
{
    int a;
    tree *temp = malloc(sizeof(tree));
    init(temp);
    uzel *root1 = temp->golova;
    scanf("%d", &a);
    root1 = add_Uzel(a);
    for(int i=0; i<6; i++)
    {
        scanf("%d", &a);
        if(find(root1, a) == NULL)
        {
            insert(root1, add_Uzel(a));
        }
    }
    print(root1);
    return 0;
}