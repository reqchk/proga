#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

struct tree{
    char* str;
    tree** children;
    int count_children; // Максимальная вместимость
    int real_children; // Текущее количество детей
};

tree* create_node(int n, const char* s){
    if (n <= 0) return NULL;
    tree* node = (tree*)malloc(sizeof(tree));
    if (!node) return NULL;
    // Выделяем память под строку
    node->str = (char*)malloc(strlen(s)+1);
    if (!node->str){
        free(node); return NULL;
    }
    strcpy(node->str, s); // Копируем строку
    node->children = (tree**)malloc(n*sizeof(tree*));
    if (!node->children){
        free(node->str); free(node); return NULL;
    }
    // Инициализируем все указатели на потомков как NULL
    for (int i = 0; i < n; i++) node->children[i] = NULL;

    node->count_children =  n;
    node->real_children = 0; // Пока нет детей

    return node;    
}

// Обход по уровням
struct tree* find_free(struct tree* root, int* idx) {
    if (!root) return NULL;
    struct tree* queue[1000]; 
    int head = 0, tail = 0;
    queue[tail++] = root;
    
    while (head < tail) {
        struct tree* current = queue[head++];
        
        // Если нашли свободное место
        if (current->real_children < current->count_children) {
            *idx = current->real_children;
            return current;
        }
        
        // Добавляем всех потомков в очередь
        for (int i = 0; i < current->real_children; i++)
            queue[tail++] = current->children[i];
    }
    return NULL;
}

void insert(struct tree* root, const char* s) {
    if (!root) return;
    int idx;
    // Находим узел со свободным местом (наиболее близкий к корню)
    struct tree* new_node = find_free(root, &idx);
    if (!new_node) return;
    // Создаем новый узел с вместимостью в 2 раза больше
    new_node->children[idx] = create_node(new_node->count_children * 2, s);
    new_node->real_children++;
}

void print_tree(struct tree* root, int level){
    if(!root) return;

    for(int i = 0; i < level; i++){
        printf("  ");
    }

    printf("- %s (вместимость: %d, заполнено: %d)\n", root->str, root->count_children, root->real_children);

    for (int i = 0; i < root->real_children; i++){
        if (root->children[i]){
            print_tree(root->children[i], level + 1);
        }
    }
}

void input_strings(struct tree* root) {
    if (!root) {
        printf("Ошибка: дерево не создано\n");
        return;
    }
    
    int count;
    char buffer[256];
    
    // Ввод количества строк
    printf("Сколько строк вы хотите добавить? ");
    scanf("%d", &count);
    
    if (count < 0) {
        printf("Ошибка: количество не может быть отрицательным\n");
        return;
    }
    getchar(); 
    
    for (int i = 0; i < count; i++) {
        printf("Введите строку %d: ", i + 1);
        if (fgets(buffer, sizeof(buffer), stdin)) {
            // Удаляем символ новой строки
            size_t len = strlen(buffer);
            if (len > 0 && buffer[len-1] == '\n') {
                buffer[len-1] = '\0';
            }
            
            if (strlen(buffer) > 0) {
                insert(root, buffer);
                printf("  Строка '%s' добавлена\n", buffer);
            }
            
        }
    }
}

int main(){
    setlocale(LC_ALL, "ru_RU.UTF-8");
    int n;
    char buffer[256];
    int count;
    
    // Ввод размера корневой вершины
    printf("Введите размерность списка в корневой вершине (N > 0): ");
    scanf("%d", &n);
    if (n <= 0) {
        printf("Ошибка: введено некорректное значение\n");
        return 1;
    }
    getchar();
    // Создание корневой вершины
    struct tree* root = create_node(n, "root");
    if (!root) {
        printf("Ошибка: не удалось создать корневой узел\n");
        return 1;
    }
    
    input_strings(root);
    
    // Вывод содержимого дерева
    printf("\nСодержимое дерева\n");
    print_tree(root, 0);

    return 0;
}