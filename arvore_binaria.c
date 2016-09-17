#include <stdio.h>
#include <stdlib.h>


struct Binarytree
{
    /* Essa é a estrutura que armazena o valor do nó, e os ponteiros dos lados direito e esquerdo */
    int value;
    struct Binarytree *left;
    struct Binarytree *right;
};

typedef struct Binarytree Binarytree;

int is_empty(Binarytree *bt)
{
    return(bt == NULL);
}


Binarytree* create_empty_binary_tree()
{
    /* O proprio nome já diz */
    return NULL;
}

BinaryTree* create_binary_tree(int value, BinaryTree *left, BinaryTree *right)
{
    BinaryTree *bt = (BinaryTree*)malloc(sizeof(BinaryTree));
    bt -> value = value;
    bt -> left = left;
    bt -> right = right;
    return bt;
}

/* Ver figuras no slide para entender melhor */
void print_in_order(Binarytree *bt)
{
    if (!is_empty(bt)) 
    {
        print_in_order(bt->left);       
        printf("%d ", bt->value);
        print_in_order(bt->right);
    }

}

void print_pre_order(Binarytree *bt)
{
    if (!is_empty(bt)) 
    {
        printf("%d ", bt->value);
        print_pre_order(bt->left);
        print_pre_order(bt->right);
    }
}

void print_post_order(Binarytree *bt)
{
    if (!is_empty(bt)) 
    {
        print_post_order(bt->left);
        print_post_order(bt->right);
        printf("%d", bt->value);
    }
}
 
/* Essa parte já é de Arvore de Busca Binária */


Binarytree* find_min(Binarytree *bt)
{
    /*Funçao para encontrar menor elemento na arvore de busca binaria */
    if(bt==NULL)
    {
        /* Não tem elemento nenhum na arvore */
        return NULL;
    }
    if(bt->left) /* Se a arvore não estiver vazia, vai descendo para esquerda para encontrar o menor valor */
    {
        return find_min(bt -> left); 
    }   
    else return bt;
    /*Só retorna o nó quando acabarem todas as chamadas recursivas */
}

Binarytree* find_max(Binarytree *bt)
{
    if(bt == NULL)
    {
        /* Não tem elemento nenhum na arvore */
        return NULL;
    }
    if(bt -> right) /* Vai para a direita do nó até achar o maior */
    {
        find_max(bt -> right);
    }
    else return bt;
}


Binarytree* search(Binarytree *bt, int value)
{
    /* Se o nó do momento não tiver mais filhos, ou se o nó armazena o valor procurado, retorna o nó */
    if ((bt == NULL) || (bt->value == value)) 
    {
        return bt;
    } 
    /* Se o valor procurado for menor que o nó do momento, então agora vai procurar a sua esquerda */
    else if (bt->value > value) 
    {
        return search(bt->left, value);
    } 
    /* Se o valor procurado for maior que o nó do momento, então agora vai procurar a sua direita */
    else 
    {
        return search(bt->right, value);
    }
}

Binarytree* add(Binarytree *bt, int value)
{
    /* Verifica da mesma forma que a busca, procurando o lugar certo onde o novo bt deve ser "encaixado"*/
    if (bt == NULL) 
    {
        /* Se a arvore estiver vazia, vai criar o novo nó raiz */
        bt = create_binary_tree(value, NULL, NULL);
        
    } 
    /* Se a arvore não estiver vazia, vai procurar o lugar certo */
    else if (bt->value > value)
    {
        bt->left = add(bt->left, value);
    } 
    else 
    {
        bt->right = add(bt->right, value);
    }
    return bt;
}

Binarytree* remove_node(Binarytree *bt, int value)
{
    Binarytree *temp;
    if(bt == NULL)
    {
        /* O nome já diz tudo*/
        return;
    }
    /* Nessa parte a função vai buscar onde esta o valor */
    else if(value < bt -> value)
    {
        bt -> left = remove_node(bt -> left, value);
    }
    else if(value > bt -> value)
    {
        bt -> right = remove_node(bt -> right, value);
    }

    else
    {
        /* Agora que encontramos onde esta o elemento, vamos remover e colocar no lugar o menor elemento a sua direita ou
        o maior elemento a sua esquerda */
        if(bt->right && bt->left)
        {
            /* Vamos substituir o elemento retirado pelo menor elemento a sua direita */
            temp = find_min(bt->right); /* Esse temporario é o nó que vai armazenar o nó que contem o menor valor a direita 
            do removido */
            bt -> value = temp -> value; 
            /* Enquanto o substituimos com outro nó, temos que remover o nó antigo */
            bt -> right = remove_node(bt->right,temp->value);
        }
        else
        {
            /* Se o no tiver 0 ou 1 filho, podemos conectar o pai diretamente com este filho */
            temp = bt;
            if(bt->left == NULL)
            {
                bt = bt -> right;
            }
            else if(bt->right == NULL)
            {
                bt = bt -> left;
            }
            free(temp); /* O temporario não é mais necessário */ 
        }
    }
    return bt;
}
