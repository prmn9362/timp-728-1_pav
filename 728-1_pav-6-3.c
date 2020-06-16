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

void print(uzel *n)
{
    if(n != NULL){
    if(n->roditel != NULL){
        printf("%d ", n->roditel->data);
    }else{
        printf("_ ");
    }
    if(n->leviy != NULL){
        printf("%d ", n->leviy->data);
    }else{
        printf("_ ");
    }
    if(n->praviy != NULL){
        printf("%d \n\n", n->praviy->data);
    }else{
        printf("_ \n\n");
    }
    }else{
        printf("- \n\n");
    }
}
void print_NULL(int level)
{
    int z=1;
    for (int i=0; i < level-1; i++){
        z = z*2;
    }
    for (int i = 0; i < z; i++){
        printf("_ ");
    }
}

bool print_lvl(uzel* n, int lvl)
{
    bool nlev = false;
    if (lvl == 0)
    {
        printf("%d ", n->data);
        if (!nlev && (n->praviy != NULL || n->leviy !=NULL))
        {
            nlev = true;
        }
    }else{
        if (lvl > 0){
            if (n->leviy != NULL){
                nlev += print_lvl(n->leviy, lvl -1);
            }else{
                print_NULL(lvl);
            }
            if (n->praviy != NULL){
                nlev += print_lvl(n->praviy, lvl -1);
            }else{
                print_NULL(lvl);
            }
        }
    }
    return nlev;
};

void print_tree(uzel* n)
{
    bool next_level = true;
    int level = 0;
    if (n == NULL)
    {
        printf("-\n\n");
        return;
    }
    while (next_level)
    {
        next_level = print_lvl(n, level);
        printf("\n");
        level++;
    }
    printf("\n");
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
    uzel* n_left = n -> praviy;
    n -> praviy = n_left -> leviy;
    n_left -> leviy = n;
    return n_left;
}

uzel *rotate_right(uzel *n){
    uzel* n_right = n -> leviy;
    n -> leviy = n_right -> praviy;
    n_right -> praviy = n;
    return n_right;
}

void back(uzel *root)
{
    if (root)
    {
        back(root -> leviy);
        back(root -> praviy);
        printf("%d ", root -> data);
    }
}

int main()
{
    int a, count=1;
    tree *temp = malloc(sizeof(tree));
    init(temp);
    uzel *root1 = temp->golova;
    uzel *root2 = (uzel *)malloc(sizeof(uzel));
    scanf("%d", &a);
    root1 = add_Uzel(a);
    
    //Ввод элементов
    for(int i=0; i<6; i++)
    {
        scanf("%d", &a);
        if(find(root1, a) == NULL)
        {
            insert(root1, add_Uzel(a));
            count++;
        }
    }
    back(root1);
    
    return 0;
}