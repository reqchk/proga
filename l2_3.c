#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct list {
    int data;
    struct list* next;
};

struct list* new_node(int data){
    struct list* node = malloc(sizeof(struct list));
    if (!node) return NULL;
    node->data=data;
    node->next=NULL;
    return node;
}

void print_list(struct list* list){
    if (list == NULL) return;

    struct list* current = list;
    
    // Печатаем, пока не вернемся к началу
    do {
        printf("%d ", current->data);
        current = current->next;
    } while (current != list);
    printf("\n");
}


// Функция копирования списка
struct list* copy_list(struct list* list) {
    if (list == NULL) return NULL;  
    
    // Создаем копию первого узла
    struct list* copy = new_node(list->data);      
    struct list* new_current = copy; // указатель на текущий узел копии
    struct list* old_current = list->next; // указатель на следующий узел оригинала
    
    // Копируем остальные узлы, пока не вернемся к началу оригинала
    while (old_current != list) {                    
        new_current->next = new_node(old_current->data); // создаем копию узла
        new_current = new_current->next; // двигаемся по копии
        old_current = old_current->next; // двигаемся по оригиналу
    }
    
    // Замыкаем новый список
    new_current->next = copy;

    return copy;
}


// Функция объединения 
struct list* concatenate(struct list* list1, struct list* list2) {
    if (list1 == NULL) return copy_list(list2); // Если первый список пуст, возвращаем копию второго
    if (list2 == NULL) return copy_list(list1); // Если второй список пуст, возвращаем копию первого
    
    // Копируем первый список
    struct list* result = copy_list(list1);
    
    // Находим конец первого списка
    struct list* tail1 = result;
    while (tail1->next != result) {
        tail1 = tail1->next;
    }
    
    // Копируем второй список 
    struct list* list2_copy = copy_list(list2);

    // Находим конец второго списка
    struct list* tail2 = list2_copy;
    while (tail2->next!=list2_copy){
        tail2 = tail2->next;
    }

    // Связываем конец первого с началом второго
    tail1->next = list2_copy;
    // Связываем конец второго с началом первого (замыкаем цикл)
    tail2->next=result;
    
    return result;
}

// Функция пересечения
struct list* intersection(struct list* list1, struct list* list2){
    if (list1 == NULL || list2 == NULL) return NULL; 

    struct list * result = NULL;
    struct list * tail = NULL; // указатель на последний элемент результата

    struct list* current1 = list1;
    do{
        struct list* current2 = list2;
        do{
            if (current2->data == current1->data){
                if (result == NULL) { // если результат пуст
                    result = new_node(current2->data); // создаем первый узел
                    tail = result;
                    tail->next = result; 
                } else { // если в результате уже есть элементы
                    tail->next = new_node(current2->data); // добавляем новый узел в конец
                    tail = tail->next;                         
                    tail->next = result;
                }                    
            }
            current2 = current2->next;
        }while(current2!=list2);

        current1 = current1->next;
    }while(current1!=list1);

    return result;
}

// Функция разности
struct list* diff(struct list* list1, struct list* list2){
    if (list1 == NULL || list2 == NULL) return NULL;

    struct list* result = NULL;
    struct list* tail = NULL;

    struct list* current1 = list1;
    do{
        struct list* current2 = list2;
        int found = 0; // найден ли элемент во втором списке
        do{
            if (current1->data == current2->data) { // если нашли совпадение
                found = 1;
                break; // выходим из цикла
            }
            current2 = current2->next;
        }while(current2!=list2);

        // Если элемент не найден во втором списке 
        if (found == 0){
            // добавляем в результат
            if (result == NULL){
                result = new_node(current1->data);
                tail = result;
                tail->next = result;
            }else{
                tail->next=new_node(current1->data);
                tail=tail->next;
                tail->next=result;
            }
        }

        current1 = current1->next;
    }while(current1!=list1);
    
    return result;
}

int main(){
    setlocale(LC_ALL,"RU");

    struct list* list1 = new_node(2);
    list1->next=new_node(4);
    list1->next->next=new_node(8);
    list1->next->next->next=list1;
    printf("Первый список: "); print_list(list1);

    struct list* list2 = new_node(32);
    list2->next=new_node(8);
    list2->next->next=new_node(12);
    list2->next->next->next=list2;
    printf("Второй список: "); print_list(list2);

    struct list* list_concat = concatenate(list1,list2);
    printf("Объединение: "); print_list(list_concat);

    struct list* list_inter = intersection(list1,list2);
    printf("Пересечение: "); print_list(list_inter);

    struct list* list_diff = diff(list1,list2);
    printf("Разность: "); print_list(list_diff);

    return 0;
}
