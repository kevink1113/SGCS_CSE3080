#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct node {
    struct node *left;
    struct node *right;
    struct node *parent;
    int num;
} NODE;

NODE *CreateBTree(NODE *parent, int leaf_node_num);

NODE *SearchBFS(NODE *root, int num);

int log_2(double x);

void BFS_Search(struct node *root, int level, int num, NODE **search);

void MerklePath(NODE *cur, int tochar);

int main(void) {
    int leaf_node_num = 0;
    char exam = 0;
    int realExam;
    int depth;
    int max_num = 0;
    scanf("%d %c", &leaf_node_num, &exam);

    if (exam < 'A' || 'Z' < exam) {
        printf("Input Error!\n");
        return 0;
    }
    if (!(0 < leaf_node_num && leaf_node_num <= 26)) {
        printf("Input Error!\n");
        return 0;
    }
    if ((int) exam - 64 > leaf_node_num) {
        printf("Input Error!\n");
        return 0;
    }
    depth = log_2(leaf_node_num);

    for (int i = 0; i < depth; i++)
        max_num += (int) pow(2, i);
    max_num += leaf_node_num;

    realExam = (int) exam;
    realExam -= 65;
    realExam += max_num;
    realExam -= leaf_node_num;
    realExam++;

    NODE root[max_num + 2];
    CreateBTree(root, max_num);

    int tochar = max_num - leaf_node_num;

    root[0].num = depth * 100 + tochar;
    root[1].parent = NULL;

    SearchBFS(&root[1], realExam);

    return 0;
}

int log_2(double x) {
    double res = log(x) / log(2.0);
    int i;
    for (i = 0;; i++) {
        if (i >= res) break;
    }
    return i;
}

NODE *CreateBTree(NODE *parent, int max_num) {
    parent[1].num = 1;
    for (int i = 0; i <= max_num; i++) {
        int left = 0, right = 0;

        if (2 * i <= max_num) {
            parent[i].left = &parent[i * 2];
            parent[i * 2].parent = &parent[i];
            parent[i * 2].num = i * 2;
            left = 1;
        } else parent[i].left = NULL;

        if (2 * i + 1 <= max_num) {
            parent[i].right = &parent[i * 2 + 1];
            parent[i * 2 + 1].parent = &parent[i];
            parent[i * 2 + 1].num = i * 2 + 1;
            right = 1;
        } else parent[i].right = NULL;

        if (left == 1 && right == 0) { // 왼쪽은 자식이 있지만, 오른쪽은 자식이 없는 경우: 복제
            parent[i].right = &parent[i * 2 + 1];
            parent[i * 2 + 1].parent = &parent[i];
            parent[i * 2 + 1].num = i * 2;
        }

    }
    return parent;
}

void BFS_Search(NODE *root, int level, int num, NODE **search) {
    if (root == NULL)
        return;
    if (level == 1) {
        //printf("%d |", root->num); //-----> 주석을 해제하면 BFS로 탐색하는 것을 볼 수 있음!
        if (root->num == num) {
            (*search) = root;
        }
    } else if (level > 1) {
        BFS_Search(root->left, level - 1, num, search);
        BFS_Search(root->right, level - 1, num, search);
    }
}

NODE *SearchBFS(NODE *root, int num) {
    int depth = ((root - 1)->num) / 100; //깊이 입력
    int tochar = ((root - 1)->num) % 100;

    NODE *search = NULL;

    for (int i = 0; i <= depth + 1; i++)
        BFS_Search(root, i, num, &search);

    MerklePath(search, tochar);

    return 0;
}

void MerklePath(NODE *cur, int tochar) {
    NODE *par;
    par = cur->parent;

    while (cur->parent != NULL) {
        if ((cur->num) % 2 == 0) {
            cur = par->right;
            if (cur->num > tochar) printf("%c ", cur->num - tochar + 65 - 1);
            else printf("%d ", cur->num);

            cur = par;
            par = par->parent;
        } else {
            cur = par->left;

            if (cur->num > tochar) printf("%c ", cur->num - tochar + 65 - 1);
            else printf("%d ", cur->num);

            cur = par;
            par = par->parent;
        }
    }
    printf("\n");
}

