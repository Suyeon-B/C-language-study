#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void)
{
    // 트리의 root, nil 정보를 담을 포인터 변수 p
    rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
    // nil노드도 노드이므로, 노드 만큼의 사이즈로 메모리를 할당해준다.
    node_t *nil_node = (node_t *)calloc(1, sizeof(node_t));

    // 포인터 변수와 nil노드를 이어준다.
    p->nil = nil_node;
    // root, nil노드를 이어준다. (아직 삽입된 노드가 없을 때의 초기 ver.)
    p->root = p->nil;
    // nil노드는 항상 Black이므로, 색상을 지정해준다.
    p->nil->color = RBTREE_BLACK;
    return p;
}

void delete_rbtree(rbtree *t)
{
    // TODO: reclaim the tree nodes's memory
    free(t);
}

void left_rotate(rbtree *t, node_t *x)
{
    // 우선 x의 오른쪽 자식, y를 설정한다.
    node_t *y = x->right;
    x->right = y->left;
    // β(y의 왼쪽 자식)가 존재한다면
    if (y->left != t->nil)
    {
        // β의 부모 = y → x
        y->left->parent = x;
    }

    // left rotate 시 부모 자식 관계에 변화를 반영한다.
    // y의 부모 = x → x의 부모
    y->parent = x->parent;
    // 이 때 x->parent == t->root 이면,
    // 새로운 루트는 y가 된다.
    if (x->parent == t->nil)
    {
        t->root = y;
    }
    // x의 부모가 nil 이 아니고, x가 그 부모의 왼쪽 자식이었다면
    else if (x == x->parent->left)
    {
        x->parent->left = y;
    }
    // x가 그 부모의 오른쪽 자식이었다면
    else
    {
        x->parent->right = y;
    }

    // y의 왼쪽 자식 = β → x
    y->left = x;
    // x의 부모 = x의 부모 → y
    x->parent = y;
}

void right_rotate(rbtree *t, node_t *y)
{
    // 우선 y의 오른쪽 자식, x를 설정한다.
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

void right_rotate(rbtree *t, node_t *y)
{
    // 우선 y의 오른쪽 자식, x를 설정한다.
    node_t *x = y->right;
    y->right = x->left;
    // β(x의 왼쪽 자식)가 존재한다면
    if (x->left != t->nil)
    {
        // β의 부모 = x → y
        x->left->parent = y;
    }

    // left rotate 시 부모 자식 관계에 변화를 반영한다.
    // x의 부모 = y → y의 부모
    x->parent = y->parent;
    // 이 때 y->parent == t->root 이면,
    // 새로운 루트는 x가 된다.
    if (y->parent == t->nil)
    {
        t->root = x;
    }
    // y의 부모가 nil 이 아니고, y가 그 부모의 왼쪽 자식이었다면
    else if (y == y->parent->left)
    {
        y->parent->left = x;
    }
    // y가 그 부모의 오른쪽 자식이었다면
    else
    {
        y->parent->right = x;
    }

    // x의 왼쪽 자식 = β → y
    x->left = y;
    // x의 부모 = x의 부모 → y
    y->parent = x;
}

void rbtree_insert_fixup(rbtree *t, node_t *z)
{
    // 각 if, else문에서 사용할
    // 삼촌 노드 하나 미리 선언
    node_t *uncle = NULL;

    // 부모 노드가 red일 때가 문제이므로
    while (z->parent->color == RBTREE_RED)
    {
        // 부모가 할아버지의 왼쪽 자식일 때
        if (z->parent == z->parent->parent->left)
        {
            // 그럼 uncle은 오른쪽 자식임!
            uncle = z->parent->parent->right;
            // case 1 : parent red & uncle red
            if (uncle->color == RBTREE_RED)
            {
                // parent와 uncle 모두 black으로 바꾼다.
                z->parent->color = RBTREE_BLACK;
                uncle->color = RBTREE_BLACK;
                // grandparent를 red로 바꾼 뒤,
                // 포인터를 grandparent로 옮겨서
                // 그의 parent도 red인지 while문으로 다시 한 번 확인하게 한다.
                z->parent->parent->color = RBTREE_RED;
                z = z->parent->parent;
            }
            else
            {
                // case 2 : parent red & uncle black & 내가 right child
                if (z == z->parent->right)
                {
                    // 포인터 parent로 올리고, left-rotate
                    z = z->parent;
                    left_rotate(t, z);
                }
                // case 3 : parent red & uncle black & 내가 left child
                //  parent의 color는 black으로, grandparent를 red로 change
                z->parent->color = RBTREE_BLACK;
                z->parent->parent->color = RBTREE_RED;
                // 포인터를 grandparent로 옮겨서 right-rotate
                right_rotate(t, z->parent->parent);
            }
        }
        // 부모가 할아버지의 오른쪽 자식일 때
        // 위와 left, right만 반대이므로 주석 생략
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
    // 삽입할 key값을 가진 노드를 만들어준다.
    node_t *z = (node_t *)calloc(1, sizeof(node_t));
    z->key = key;

    // 자리를 찾아 내려갈 ptr 변수 x, y
    node_t *x = t->root;
    node_t *y = t->nil;
    // 새로운 노드가 들어갈 자리를 찾아준다.
    while (x != t->nil)
    {
        // while문이 매번 새로 돌 때 마다,
        // x가 가리키는 주소 값을 y도 가리키도록 바꿔준다.
        // 마지막에 x가 nil노드에 도달했을 때,
        // y가 직전 노드의 주소를 가지고 있도록 하기 위함이다!
        y = x;
        // 삽입할 값이 작다면 왼쪽으로 간다.
        if (x->key > key)
        {
            x = x->left;
        }
        // 삽입할 값이 크거나 같다면 오른쪽으로 간다.
        else
        {
            x = x->right;
        }
    }

    // 자리를 찾았으니 부모 자식 관계를 이어준다.
    // 만약 들어갈 자리가 nil노드라면, 삽입될 값이 최초의 루트노드이다.
    z->parent = y;
    if (y == t->nil)
    {
        t->root = z;
    }
    // nil노드가 아니라면 key값의 크기에 따라 left, right 자리를 정해준다.
    // right child일 경우
    else if (y->key <= key)
    {
        y->right = z;
    }
    // left child일 경우
    else
    {
        y->left = z;
    }

    // 빨간색으로 칠해주고, left, right child에 nil노드를 연결한다.
    z->color = RBTREE_RED;
    z->left = t->nil;
    z->right = t->nil;

    // 새로 삽입된 값에 의해
    // RB tree의 조건이 위배되었을 수 있으므로, 고쳐준다.
    rbtree_insert_fixup(t, z);

    return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key)
{
    // TODO: implement find
    return t->root;
}

node_t *rbtree_min(const rbtree *t)
{
    // RB Tree는 BST
    // 자신의 왼쪽 노드에 항상 작은 값이 있으므로,
    // root부터 nil직전까지 왼쪽 자식을 찾아가면 된다.
    node_t *find_min = t->root;
    while (find_min->left != t->nil)
    {
        find_min = find_min->left;
    }

    return find_min;
}

node_t *rbtree_max(const rbtree *t)
{
    // RB Tree는 BST
    // 자신의 오른쪽 노드에 항상 큰 값이 있으므로,
    // root부터 nil직전까지 오른쪽 자식을 찾아가면 된다.
    node_t *find_min = t->root;
    while (find_min->right != t->nil)
    {
        find_min = find_min->right;
    }

    return find_min;
}

int rbtree_erase(rbtree *t, node_t *p)
{
    // TODO: implement erase
    return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n)
{
    // TODO: implement to_array
    return 0;
}