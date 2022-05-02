#include "rbtree.h"
#include <stdlib.h>
#include <stdio.h>

// remove after debugging
#include <assert.h>

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

void postorder_del(rbtree *t, node_t *root)
{
    if (root == t->nil)
    {
        return;
    }
    postorder_del(t, root->left);
    postorder_del(t, root->right);
    free(root);
}

void delete_rbtree(rbtree *t)
{
    // TODO: reclaim the tree nodes's memory
    if (t == NULL)
    {
        return;
    }
    postorder_del(t, t->root);
    free(t->nil);
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
    node_t *uncle = t->nil;
    while (z->parent->color == RBTREE_RED)
    {
        if (z->parent == z->parent->parent->left)
        {
            uncle = z->parent->parent->right;
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
            uncle = z->parent->parent->left;
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
        if (key < x->key)
        {
            x = x->left;
        }
        else // key 값이 같거나 클 때
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
    // key의 위치를 찾아 내려가기 위한 ptr 변수 x 선언
    node_t *x = t->root;

    // x가 가리키는 노드가 nil 노드가 될 때 까지 탐색
    while (x != t->nil)
    {
        // 찾으려는 key값 보다 x->key가 크면
        if (x->key > key)
        {
            // 작은 값을 찾아 left child로 이동
            x = x->left;
        }
        // 찾으려는 key값 보다 x->key가 크면
        else if (x->key < key)
        {
            // 큰 값을 찾아 right child로 이동
            x = x->right;
        }
        else
        { // 키를 찾았으면 리턴
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
    while (x->left != t->nil)
    {
        x = x->left;
    }
    return x;
}

node_t *rbtree_max(const rbtree *t)
{
    // TODO: implement find
    node_t *x = t->root;
    while (x->right != t->nil)
    {
        x = x->right;
    }
    return x;
}

node_t *subtree_min(const rbtree *t, const node_t *z)
{
    node_t *ptr = z;
    while (ptr->left != t->nil)
    {
        ptr = ptr->left;
    }
    return ptr;
}

void rb_transplant(rbtree *t, node_t *u, node_t *v)
{
    if (u->parent == t->nil)
    {
        t->root = v;
    }
    else if (u == u->parent->left)
    {
        u->parent->left = v;
    }
    else
    {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

void rb_erase_fixup(rbtree *t, node_t *x)
{
    node_t *uncle = t->nil;
    while (x != t->root && x->color == RBTREE_BLACK)
    {
        if (x == x->parent->left)
        {
            uncle = x->parent->right;
            if (uncle->color == RBTREE_RED)
            {
                uncle->color = RBTREE_BLACK;
                x->parent->color = RBTREE_RED;
                left_rotate(t, x->parent);
                uncle = x->parent->right;
            }
            if (uncle->left->color == RBTREE_BLACK && uncle->right->color == RBTREE_BLACK)
            {
                uncle->color = RBTREE_RED;
                x = x->parent;
            }
            else
            {
                if (uncle->right->color == RBTREE_BLACK)
                {
                    uncle->left->color = RBTREE_BLACK;
                    uncle->color = RBTREE_RED;
                    right_rotate(t, uncle);
                    uncle = x->parent->right;
                }
                uncle->color = x->parent->color;
                x->parent->color = RBTREE_BLACK;
                uncle->right->color = RBTREE_BLACK;
                left_rotate(t, x->parent);
                x = t->root;
            }
        }
        else
        {
            uncle = x->parent->left;
            if (uncle->color == RBTREE_RED)
            {
                uncle->color = RBTREE_BLACK;
                x->parent->color = RBTREE_RED;
                right_rotate(t, x->parent);
                uncle = x->parent->left;
            }
            if (uncle->right->color == RBTREE_BLACK && uncle->left->color == RBTREE_BLACK)
            {
                uncle->color = RBTREE_RED;
                x = x->parent;
            }
            else
            {
                if (uncle->left->color == RBTREE_BLACK)
                {
                    uncle->right->color = RBTREE_BLACK;
                    uncle->color = RBTREE_RED;
                    left_rotate(t, uncle);
                    uncle = x->parent->left;
                }
                uncle->color = x->parent->color;
                x->parent->color = RBTREE_BLACK;
                uncle->left->color = RBTREE_BLACK;
                right_rotate(t, x->parent);
                x = t->root;
            }
        }
    }
    x->color = RBTREE_BLACK;
}

int rbtree_erase(rbtree *t, node_t *z)
{
    // TODO: implement erase
    if (z == NULL)
    {
        return 0;
    }

    node_t *x = NULL;
    node_t *y = z;
    color_t y_origin = y->color;

    if (z->left == t->nil)
    {
        x = z->right;
        rb_transplant(t, z, z->right);
    }
    else if (z->right == t->nil)
    {
        x = z->left;
        rb_transplant(t, z, z->left);
    }
    else
    {
        y = subtree_min(t, z->right);
        y_origin = y->color;
        x = y->right;
        if (y->parent == z)
        {
            x->parent = y;
        }
        else
        {
            rb_transplant(t, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        rb_transplant(t, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if (y_origin == RBTREE_BLACK)
    {
        rb_erase_fixup(t, x);
    }
    free(z);
    return 0;
}

int inorder(node_t *root, key_t *res, const rbtree *t, int i)
{
    if (root == t->nil)
    {
        return i;
    }

    i = inorder(root->left, res, t, i);
    res[i] = root->key;
    i = inorder(root->right, res, t, i + 1);
    return i;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n)
{
    inorder(t->root, arr, t, 0);
    return 0;
}