#ifndef LIST_H
#define LIST_H

struct list {
    struct list *prev;
    struct list *next;
};

void lst_init(struct list *lst);
int lst_empty(struct list *lst);
void lst_remove(struct list *e);
void* lst_pop(struct list *lst);
void lst_push(struct list *lst, void *p);
void lst_print(struct list *lst);
#endif // LIST_H