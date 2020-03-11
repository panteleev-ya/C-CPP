#include<stdio.h>
#include<string.h>

typedef struct node {
    int freq;
    int value;
    struct node* left;
    struct node* right;
} node;

void write_to_arc(FILE*, char*);
void sort(node**);

int main(int argc, char** argv) {
	// FILE* arc;
	// if (strcmp(argv[3], "--extract") == 0) {
	//     arc = fopen(argv[1], "rb");
	// }
	// else if (strcmp(argv[3], "--list") == 0) {
	//     arc = fopen(argv[1], "rb");
	// }
	// else {
	//     // Создаем новый архив и последовательно записываем в него сжатые файлы
	//     arc = fopen(argv[1], "wb");
	//     fwrite(argc-3, sizeof(int), 1, arc); // записываем число сжатых файлов в архив
	//     for (int i=4; i<argc; i++) {
	//         FILE* next = fopen(argv[i], "rb");
	//         write_to_arc(arc, next); // записываем в архив сам файл
	//     }
	// }
	int freq[3] = { 3, 1, 2 };
	int value[3] = {30, 10, 20};
    node* mas[3];
	for (size_t i = 0; i < sizeof(mas) / sizeof(node); i++) {
		node* new_elem;
		new_elem->freq = freq[i];
		new_elem->value = value[i];
		mas[i] = new_elem;
		free(new_elem);
	}
    /*
	mas[0]->freq = 3;
    mas[0]->value = 30;
    mas[1]->freq = 1;
    mas[1]->value = 10;
    mas[2]->freq = 2;
    mas[2]->value = 20;
	*/
    sort(&mas[0]);
    return 0;
}

/*
void write_to_arc(FILE* arc, char* name) {
	FILE* file = fopen(name, "rb");
	// Записываем имя файла
	for (unsigned long i = 0; i < strlen(name); ++i) {
		char buffer = *(name + i); // i-ый симвой название читаем
		fwrite(&buffer, 1, 1, arc); // записываем
	}
	node* priority_queue[256]; // собираем данные о встречаемости байтов в приоритетную очередь
	int first = 0; // первый существующий элемент приоритетной очереди
	for (int i=0; i<256; i++) {
		priority_queue[i]->value = i; // создаем связь между встречаемостью и значением
		priority_queue[i]->freq = 0; // обнуляем изначальную встречаемость
	}
	int buffer;
	while(fread(&buffer, sizeof(int), 1, file)) {
		priority_queue[buffer]->freq++;
	} // собрали
	// sort(&priority_queue); // делаем массив и приоритетной очередью
	return;
}
*/

void sort(node** arr) {
    printf("%d\n", (*arr)->freq);
    (*arr)->freq++;
    printf("%d\n", (*arr)->freq);
    printf("%d\n", (*arr+1)->freq);
    (*arr+1)->freq++;
    printf("%d\n", (*arr+1)->freq);
    // for (int i=0; i<256; i++) {
    //     node* buffer;
    //     int min = i;
    //     for (int j=i+1; j<256; j++) {
    //         if (arr[j]->freq < arr[min]->freq) {
    //             min = j;
    //         }
    //     }
    //     buffer = arr[i];
    //     arr[i] = arr[min];
    //     arr[min] = buffer;
    //     free(buffer);
    // }
    return;
}