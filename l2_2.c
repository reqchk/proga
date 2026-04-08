#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct list {
    int data;
    struct list* next;
    struct list* prev;
};

struct list* new_node(int data){
    struct list* node = malloc(sizeof(struct list));
    node->data = data;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void print_list_forward(struct list* list){
    if (list==NULL) return;
    printf("Вывод вперед: ");
    while (list!=NULL){
        printf("%d ", list->data);
        list = list->next;
    }
    printf("\n");
}

void print_list_back(struct list* list){
    if (list==NULL) return;
    while (list->next!=NULL){
        list = list->next;
    }
    printf("Вывод назад: ");
    while (list!=NULL){
        printf("%d ", list->data);
        list = list->prev;
    }
    printf("\n");
}

// Функция копирования списка
struct list* copy_list(struct list* list) {
    if (list == NULL) return NULL;
    
    // Копируем первый узел
    struct list* copy = new_node(list->data);
    struct list* new_current = copy;
    struct list* old_current = list->next;
    
    // Копируем остальные узлы и устанавливаем связи
    while (old_current != NULL) {
        new_current->next = new_node(old_current->data); // создаем копию узла
        new_current->next->prev = new_current;
        new_current = new_current->next; // двигаемся по копии
        old_current = old_current->next; // двигаемся по оригиналу
    }
    
    return copy;
}

// Функция объединения двух двусвязных списков
struct list* concatenate(struct list* list1, struct list* list2) {
    if (list1 == NULL) return copy_list(list2); // Если первый список пуст, возвращаем копию второго
    if (list2 == NULL) return copy_list(list1); // Если второй список пуст, возвращаем копию первого
    
    // Копируем первый список
    struct list* result = copy_list(list1);
    
    // Находим конец первого списка
    struct list* tail = result;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    
    // Копируем второй список
    struct list* list2_copy = copy_list(list2);
    
    // Связываем конец первого с началом второго
    tail->next = list2_copy;
    list2_copy->prev = tail;
    
    return result;
}


// Функция пересечения
struct list* intersection(struct list* list1, struct list* list2){
    if (list1 == NULL || list2 == NULL) return NULL;

    struct list * result = NULL;
    struct list * tail = NULL; // указатель на последний элемент результата

    struct list* current1 = list1;
    while(current1!=NULL){
        struct list* current2 = list2;
        while(current2!=NULL){
            if(current2->data == current1->data){
                if (result == NULL) { // если результат пуст
                        result = new_node(current2->data); // создаем первый узел
                        tail = result;  
                    } else { // если в результате уже есть элементы
                        tail->next = new_node(current2->data); // добавляем новый узел в конец   
                        tail->next->prev=tail;
                        tail = tail->next;
                    }
            }
            current2=current2->next;
        }
        current1=current1->next;
    }
    return result;
}


// Функция разности
struct list* diff(struct list* list1, struct list* list2){
    if (list1 == NULL || list2 == NULL) return NULL;

    struct list* result = NULL;
    struct list* tail = NULL;  // указатель на последний элемент результата

    struct list* current1 = list1;
    while (current1!=NULL){
        struct list* current2 = list2;
        int found = 0; // найден ли элемент во втором списке
        while (current2!=NULL){
            if (current1->data == current2->data) { // если нашли совпадение
                found = 1;
                break; // выходим из цикла
            }
            current2 = current2->next;
        }

        // Если элемент не найден во втором списке 
        if (found == 0){
            // добавляем в результат
            if (result == NULL) {
                        result = new_node(current1->data);
                        tail = result;  
                    } else {
                        tail->next = new_node(current1->data);  
                        tail->next->prev=tail;
                        tail = tail->next;
                    }
        }
        current1 = current1->next;
    }
    return result;
}

int main(){
    setlocale(LC_ALL,"RU");

    struct list* list1 = new_node(1);
    list1->next=new_node(6);
    list1->next->prev=list1;
    list1->next->next=new_node(5);
    list1->next->next->prev=list1->next;
    printf("Первый список: \n"); print_list_forward(list1); print_list_back(list1); printf("\n");

    struct list* list2 = new_node(6);
    list2->next=new_node(8);
    list2->next->prev=list2;
    list2->next->next=new_node(11);
    list2->next->next->prev=list2->next;
    printf("Второй список: \n"); print_list_forward(list2); print_list_back(list2); printf("\n");

    struct list* list_concat = concatenate(list1, list2);
    printf("Объединение: \n"); print_list_forward(list_concat); print_list_back(list_concat); printf("\n");
    
    struct list* list_inter = intersection(list1, list2);
    printf("Пересечение: \n"); print_list_forward(list_inter); print_list_back(list_inter); printf("\n");

    struct list* list_diff = diff(list1, list2);
    printf("Разность: \n"); print_list_forward(list_diff); print_list_back(list_diff); printf("\n");

    return 0;
}
