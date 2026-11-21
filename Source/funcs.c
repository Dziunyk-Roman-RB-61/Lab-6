#include "funcs.h" 

double func(double x) 
{
    return x * x * x / 30.0 - 4.0 * x * x + 50.0; 
}

void print_output_data(double x1, double x2, unsigned int N, double delta, char* group, unsigned int brigade, char* name) // функція виведення таблиці на екран та запису в текстовий файл
{

    unsigned int i; // лічильник циклу та номер точки
    double x; // поточне значення аргументу (тип double, з плаваючою комою подвійної точності)
    FILE* output_data_file; // вказівник на потік виведення в текстовий файл

    if((output_data_file = fopen("Texts/output_data.txt", "w")) != 0) { // створення текстового файлу для запису та перевірка успішності відкриття
        printf("+-------+------------+------------+\n"); 
        printf("| No    |     x      |    f(x)    |\n"); 
        printf("+-------+------------+------------+\n"); 
        fprintf(output_data_file, "+-------+------------+------------+\n"); 
        fprintf(output_data_file, "| No    |     x      |    f(x)    |\n");
        fprintf(output_data_file, "+-------+------------+------------+\n"); 

        for(i = 0; i < N; i++) { // цикл по всіх точках від 0 до N - 1
            x = x1 + i * delta; // обчислення аргументу від початкового значення без накопичення похибки
            printf("| %5u | %10.4lf | %10.4lf |\n", i + 1, x, func(x)); 
            fprintf(output_data_file, "| %5u | %10.4lf | %10.4lf |\n", i + 1, x, func(x)); 
        }
        printf("+-------+------------+------------+\n");
        fprintf(output_data_file, "+-------+------------+------------+\n"); 
        fprintf(output_data_file, "\nGroup: %s\n", group); 
        fprintf(output_data_file, "Brigade: %u\n", brigade);
        fprintf(output_data_file, "Name: %s\n", name); 
        fclose(output_data_file); 
    } else { 
        printf("Error! File cannot be opened 2\n"); 
    }
} 

void write_bin_file(double x1, double x2, unsigned int N, double delta, char* group, unsigned int brigade) // функція запису даних у бінарний файл
{
    unsigned int i; // лічильник циклу
    double x, y; // аргумент та значення функції
    FILE* bin_data_file; // вказівник на потік запису в бінарний файл

    if((bin_data_file = fopen("Texts/bin_data.bin", "wb")) != 0) { 
        fwrite(&N, sizeof(unsigned int), 1, bin_data_file); 
        fwrite(&brigade, sizeof(unsigned int), 1, bin_data_file); 
        fwrite(group, sizeof(char), GROUP_SIZE, bin_data_file); 

        for(i = 0; i < N; i++) { // цикл по всіх точках
            x = x1 + i * delta; // обчислення аргументу
            y = func(x); // обчислення значення функції
            fwrite(&x, sizeof(double), 1, bin_data_file); // запис аргументу у файл
            fwrite(&y, sizeof(double), 1, bin_data_file); // запис значення функції одразу після аргументу
        } 

        fclose(bin_data_file);
    } else {
        printf("Error! File cannot be opened 3\n"); 
    }
} 

void print_bin_data(void) // функція читання бінарного файлу та виведення даних на екран
{
    unsigned int i, count, brigade; 
    char group[GROUP_SIZE]; 
    double* data; 
    FILE* bin_data_file; 

    if((bin_data_file = fopen("Texts/bin_data.bin", "rb")) != 0) { 
        fread(&count, sizeof(unsigned int), 1, bin_data_file); 
        fread(&brigade, sizeof(unsigned int), 1, bin_data_file); 
        fread(group, sizeof(char), GROUP_SIZE, bin_data_file); 

        data = (double*)malloc(2 * count * sizeof(double)); // виділення пам'яті під 2N значень типу double
        if(data == NULL) { 
            printf("Error! Memory cannot be allocated\n");
            fclose(bin_data_file); 
            return; 
        }

        fread(data, sizeof(double), 2 * count, bin_data_file); // зчитування всіх пар значень у масив одним викликом
        fclose(bin_data_file); 

        printf("\nBinary file: group %s, brigade %u, points %u\n", group, brigade, count);
        printf("+-------+------------+------------+\n"); 
        printf("| No    |     x      |    f(x)    |\n"); 
        printf("+-------+------------+------------+\n");
        for(i = 0; i < count; i++) { // цикл по всіх зчитаних точках
            printf("| %5u | %10.4lf | %10.4lf |\n", i + 1, data[2 * i], data[2 * i + 1]); 
        }
        printf("+-------+------------+------------+\n"); 

        free(data); // звільнення динамічної пам'яті
    } else {
        printf("Error! File cannot be opened 4\n");
    }
} 