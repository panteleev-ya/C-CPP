#define _CRT_SECURE_NO_WARNINGS
#define MAX_FILES 100

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE* arc;
char* files[MAX_FILES]; // массив архивируемых файлов
unsigned long long file_sizes[MAX_FILES]; // массив размеров файлов
int last = 0; // количество заполненных строк таблицы
char zero = 0x00; // символ с кодом 0

int main(int argc, char** argv) {
	if (strcmp(argv[3], "--create") == 0) {
		arc = fopen(argv[2], "wb"); // создаем файл архива
		for (int i = 4; i < argc; i++) {
			char* nextfilename = argv[i];
			files[i - 4] = nextfilename; // записываем названия файлов в массив
		}
		// Пишем в архив число файлов и список их имен
		int count_of_files = 2; //argc - 4;
		fwrite(&count_of_files, sizeof(int), 1, arc);
		for (int i = 0; i < argc - 4; i++) {
			for (size_t j = 0; j < strlen(files[i]); j++) {
				fwrite(&files[i][j], sizeof(char), 1, arc); // посимвольная запись названия файла
			}
			fwrite("*", sizeof(char), 1, arc); // разделитель между названиями
		}
		for (int i = 0; i < argc - 4; i++) {
			fwrite(&file_sizes[i], sizeof(unsigned long long), 1, arc); // пишем размер файла
			unsigned char buffer;
			FILE* read_file = fopen(files[i], "rb");
			int tmp;
			while ((tmp = getc(read_file)) != EOF)
				putc(tmp, arc);
			fclose(read_file);
		}
	}
	else if (strcmp(argv[3], "--extract") == 0) {
		arc = fopen(argv[2], "rb"); // открываем готовый файл архива
		int count; // считываем количество файлов в архиве
		fread(&count, sizeof(int), 1, arc);
		for (int i = 0; i < count; i++) {
			int k = 1;
			char* buffer_name = calloc(1, 1);
			*buffer_name = '\0';
			char buffer_byte = 0x00;
			fread(&buffer_byte, 1, 1, arc);
			while (buffer_byte != '*') {
				realloc(buffer_name, k);
				*(buffer_name + k - 1) = buffer_byte;
				fread(&buffer_byte, 1, 1, arc);
				k++;
			}
			*(buffer_name + k - 1) = '\0';
			files[i] = buffer_name;
		} // посимвольно считываем названия файлов в массив
		// Считываем количество различных символов и таблицу соответствия
		fread(&last, sizeof(int), 1, arc);
		unsigned char read_char; // буфер
		for (int i = 0; i < count; i++) {
			FILE* f = fopen(files[i], "wb"); // создаем очередной файл
			fread(&file_sizes[i], sizeof(unsigned long long), 1, arc); // считываем длину файла
			for (unsigned long long j = 0; j < file_sizes[i]; j++) {
				fread(&read_char, sizeof(char), 1, arc);
				fwrite(&read_char, sizeof(char), 1, f);
			}
		}
	}
	else {
		arc = fopen(argv[2], "rb"); // открываем готовый файл архива
		int count; // считываем количество файлов в архиве
		fread(&count, sizeof(int), 1, arc);
		printf("There is %d files:\n", count);
		for (int i = 0; i < count; i++) {
			unsigned char read_char;
			printf(" %d) ", i + 1);
			while (fread(&read_char, sizeof(char), 1, arc) && read_char != '*') {
				printf("%c", read_char); // посимвольно считываем названия файлов
			}
			printf("\n");
		}
	}
	return 0;
}