#include <stdio.h>
#include <string.h>
#include <locale.h>

char* w[] = {"nstu", "algoritm", "log", "test", "status",  NULL};

// проверка наличия символа в середине
int symbol_middle(char* word, char first_symbol){
    for (int i = 1; i<strlen(word)-1;i++){
        if (word[i] == first_symbol) return i;
    }
    return -1;
}

 // построение цепочки
void step(int k){
    if (w[k+1]==NULL) throw 1;
    for (int n=k+1;w[n]!=NULL;n++){
        if (k==-1){
            // Обмен найденного со следующим
            char *q = w[k+1]; 
            w[k+1] = w[n]; 
            w[n] = q;
            step(k+1);
            // Обратный обмен для восстановления массива
            q = w[k+1]; 
            w[k+1] = w[n]; 
            w[n] = q;
        }else{
            char first_symbol = w[n][0];
            if (symbol_middle(w[k],first_symbol)!=-1){
                // Если нашли подходящее слово то меняем его местами со следующим 
                char *q = w[k+1];
                w[k+1] = w[n];
                w[n] = q;
                step(k + 1);
                // Обратный обмен для восстановления массива
                q = w[k+1]; 
                w[k+1] = w[n]; 
                w[n] = q;
            }
        }
    }
}

int main(){
    setlocale(LC_ALL,"ru_RU.UTF-8");
    try {
        step(-1);
        printf("Цепочка из всех слов не найдена\n");
    }
    catch(int v){
        int s = 0;
        // Вывод слов «лесенкой» с подсчетом
        for (int i = 0; w[i] != NULL; i++){
            for (int j = 0; j < s; j++){
                putchar(' ');
            }
            puts(w[i]);
            if (w[i+1]!=NULL){
                char* current = w[i];
                char first_symbol = w[i+1][0];
                for (int j = 1; j < strlen(current)-1; j++){
                    if (current[j] == first_symbol){
                        s+=j;
                        break;
                    }
                } 
            }
        }
    }

    return 0;
}
