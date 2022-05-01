#include "rbtree.h"
#include <stdlib.h>

rbtree *new_rbtree(void)
{
    rbtree *p = (rbtree *)calloc(1, sizeof(rbtree)); // rbtree pointer 생성, 메모리는 rbtree 구조체 만큼 할당
    // TODO: initialize struct if needed
    node_t *nil_node = (node_t *)calloc(1, sizeof(node_t));
    nil_node->color = RBTREE_BLACK;
    p->nil = nil_node;
    p->root = p->nil;
    return p;
}

void delete_rbtree(rbtree *t)
{
    // TODO: reclaim the tree nodes's memory

    free(t);
}

void left_rotate(rbtree *t, node_t *x)
{
    node_t *y = x->right;
    x->right = y->left;
    if (y->left != t->nil)
    {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == t->nil)
    {
        t->root = y;
    }
    else if (x == x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void right_rotate(rbtree *t, node_t *y)
{
    node_t *x = y->left;
    y->left = x->right;
    if (x->right != t->nil)
    {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == t->nil)
    {
        t->root = x;
    }
    else if (y == y->parent->left)
    {
        y->parent->left = x;
    }
    else
    {
        y->parent->right = x;
    }
    x->right = y;
    y->parent = x;
}

void rbtree_insert_fixup(rbtree *t, node_t *z)
{
    while (z->parent->color == RBTREE_RED)
    {
        if (z->parent == z->parent->parent->left)
        {
            node_t *uncle = z->parent->parent->right;
            if (uncle->color == RBTREE_RED)
            {
                z->parent->color = RBTREE_BLACK;
                uncle->color = RBTREE_BLACK;
                z->parent->parent->color = RBTREE_RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->right)
                {
                    z = z->parent;
                    left_rotate(t, z);
                }
                z->parent->color = RBTREE_BLACK;
                z->parent->parent->color = RBTREE_RED;
                right_rotate(t, z->parent->parent);
            }
        }
        else
        {
            node_t *uncle = z->parent->parent->left;
            if (uncle->color == RBTREE_RED)
            {
                z->parent->color = RBTREE_BLACK;
                uncle->color = RBTREE_BLACK;
                z->parent->parent->color = RBTREE_RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->left)
                {
                    z = z->parent;
                    right_rotate(t, z);
                }
                z->parent->color = RBTREE_BLACK;
                z->parent->parent->color = RBTREE_RED;
                left_rotate(t, z->parent->parent);
            }
        }
    }
    t->root->color = RBTREE_BLACK;
}

node_t *rbtree_insert(rbtree *t, const key_t key)
{
    // TODO: implement insert
    node_t *y = t->nil;
    node_t *x = t->root;

    while (x != t->nil)
    {
        y = x;
        if (x->key == key)
        {
            return x;
        }
        else if (key < x->key)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }

    node_t *z = (node_t *)calloc(1, sizeof(node_t));
    z->key = key;
    z->parent = y;
    if (y == t->nil)
    {
        t->root = z;
    }
    else if (z->key < y->key)
    {
        y->left = z;
    }
    else
    {
        y->right = z;
    }

    z->left = t->nil;
    z->right = t->nil;
    z->color = RBTREE_RED;
    rbtree_insert_fixup(t, z);
    return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key)
{
    // TODO: implement find
    node_t *x = t->root;
    while (x != t->nil)
    {
        // 찾으려는 key값 보다 x->key가 크면
        if (x->key > key)
        {
            x = x->left;
        }
        else if (x->key < key)
        {
            x = x->right;
        }
        else if (x->key == key)
        { // 키를 찾았으면
            return x;
        }
    }
    // 찾는 키가 없으면
    return NULL;
}

node_t *rbtree_min(const rbtree *t)
{
    // TODO: implement find
    node_t *x = t->root;
    while (x != t->nil)
    {
        x = x->left;
    }
    return x;
}

node_t *rbtree_max(const rbtree *t)
{
    // TODO: implement find
    node_t *x = t->root;
    while (x != t->nil)
    {
        x = x->right;
    }
    return x;
}

int rbtree_erase(rbtree *t, node_t *p)
{
    // TODO: implement erase
    node_t *y = p;
    node_t *y_origin_color = y->color;

    if (p->left == t->nil)
    {
        node_t *x = p->right;
        rb_transplant(t, p, p->right);
    }
    else if (p->right == t->nil)
    {
        node_t *x = p->left;
        rb_transplant(t, p, p->left);
    }
    else
    {
        // 삭제 구현 중
    }
    return 0;
}

// int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
//   // TODO: implement to_array
//   return 0;
// }
