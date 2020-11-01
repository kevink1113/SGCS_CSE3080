#include <stdio.h>
#include <stdlib.h>

#define last_node 0
#define not_last 1

typedef struct node *Nptr;

typedef struct node {
    int num; ///들어갈 수
    int define; //끝인지 여부
    Nptr before, after; //전, 후 포인터
} node;

Nptr make_list() {
    Nptr NEW = (Nptr) malloc(sizeof(node));
    NEW->define = last_node;
    NEW->after = NEW;
    NEW->before = NEW;
    return NEW;
}

//n을 원형 리스트에 삽입
void insert(Nptr HEAD, int n) {
    Nptr NEW = (Nptr) malloc(sizeof(node));
    NEW->num = n;
    NEW->define = not_last;
    if (HEAD->after != HEAD) {
        NEW->before = HEAD;
        NEW->after = HEAD->after;
        HEAD->after->before = NEW;
        HEAD->after = NEW;
    } else {
        NEW->before = HEAD;
        NEW->after = HEAD;
        HEAD->before = NEW;
        HEAD->after = NEW;
    }
}

//원소 삭
void minus(Nptr node) {
    if (node->define == last_node) return;
    node->before->after = node->after;
    node->after->before = node->before;
    free(node);
}

void Plus(Nptr fin, Nptr start) {
    do {
        start = start->before;
        insert(fin, start->num);
    } while (start->before->define != last_node);
}

Nptr create_list(char *filename) {
    FILE *fp = fopen(filename, "r");
    Nptr list = make_list();
    int n;
    while (fscanf(fp, "%d", &n) != EOF)
        insert(list, n);

    fclose(fp);
    return list;
}

void FREE(Nptr node) {
    while (node->after->define != last_node)
        minus(node->after);

    free(node);
}

void res_list_prt(Nptr node) {
    do {
        node = node->before;
        printf("%d ", node->num);
    } while (node->before->define != last_node);
    printf("\n");
}

int main() {
    Nptr txtA = create_list("A.txt");
    Nptr txtB = create_list("B.txt");
    Nptr txtC = create_list("C.txt");

    //합치기
    Plus(txtA, txtB);
    res_list_prt(txtA); //합쳐진 원형 리스트

    //A, B를 합친 A에서 C 빼기
    txtA = txtA->before;
    do {
        int confirm = 0;
        do {
            txtC = txtC->before;
            if (txtC->num == txtA->num) confirm = 1;
        } while (txtC->before->define != last_node);
        txtA = txtA->before;
        if (confirm) minus(txtA->after);
    } while (txtA->define != last_node);

    res_list_prt(txtA); //삭제된 후의 원형 리스트

    FREE(txtA); FREE(txtB); FREE(txtC);

    return 0;
}