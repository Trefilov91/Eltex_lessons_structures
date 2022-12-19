#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define PHONEBOOK_SIZE 100 
#define NAME_SIZE  100
#define ADRES_SIZE 100
#define PHONE_NUMBER_SIZE  13

struct phonebook {
    char name[NAME_SIZE];
    char adres[ADRES_SIZE];
    char phone_number[PHONE_NUMBER_SIZE];
};

void print_main_menu(void);
char get_user_input_simbol(void);
int get_user_input_string(char *, int);
int add_abonent_to_phonebook(struct phonebook *);
int delete_abonent_from_phonebook(struct phonebook *);
int find_free_space_in_phonebook(struct phonebook *);
int print_all_names(struct phonebook *);
int print_all_adresses(struct phonebook *);
int is_phone_number(char *, int);
int find_abonent_by_name(struct phonebook *);
int find_abonent_by_adress(struct phonebook *);

int main()
{
    struct phonebook book1[PHONEBOOK_SIZE];
    char menu_user_input;

    memset(book1, '\0', sizeof(book1));

    while(1)
    {    
        print_main_menu();

        menu_user_input = get_user_input_simbol();
        
        switch(menu_user_input)
        {
            case '1':
                print_all_names(&book1[0]);
                break;

            case '2':
                print_all_adresses(&book1[0]);
                break;

            case '3':
                find_abonent_by_name(&book1[0]);
                break;

            case '4':
                find_abonent_by_adress(&book1[0]);
                break;

            case '5':
                add_abonent_to_phonebook(&book1[0]);
                break;

            case '6':
                delete_abonent_from_phonebook(&book1[0]);
                break;

            case '7':
                return 0;

            default:
                printf("\n Пожалуйста, выберете действие из списка\n\n");
                break;
        }
    }

    return 0;
}

int add_abonent_to_phonebook(struct phonebook *book)
{
    char step = 0;
    int free_index, ret;

    free_index = find_free_space_in_phonebook(book);
    if(free_index < 0){
        printf("\n Нет свободных позиций, удалите устаревшие записи\n");
        return -1;
    }

    while(1)
    {
        switch(step)
        {
            case 0:
                printf("\n Введите ФИО абонента:\n");
                ret = get_user_input_string(book[free_index].name, sizeof(book[free_index].name));
                if(ret){
                    step = 1;
                }
                else{
                    return ret;
                }
                break;

            case 1:
                printf("\n Введите адрес абонента:\n");
                ret = get_user_input_string(book[free_index].adres, sizeof(book[free_index].adres));
                if(ret){
                    step = 2;
                }
                else{
                    return ret;
                }
                break; 

            case 2:
                printf("\n Введите номер абонента:\n");
                ret = get_user_input_string(book[free_index].phone_number, sizeof(book[free_index].phone_number));
                if(ret){
                    if(!is_phone_number(book[free_index].phone_number, ret)){
                        break;
                    }
                }                
                return ret;               
        }
    }
}

void print_main_menu(void)
{
    printf("\n Выберете пунткт меню:\n\
            1. Список абонентов\n\
            2. Список адресов\n\
            3. Поиск по ФИО\n\
            4. Поиск по адресу\n\
            5. Довавить абонента\n\
            6. Удалить абонента\n\
            7. Выход\n");
}

char get_user_input_simbol(void)
{
    char ret = 0, current_simbol = 0;
    int valid_iterations = 2;

    while(1){    
        ret = current_simbol;
        current_simbol = fgetc(stdin);
        valid_iterations--;

        if(current_simbol == '\n'){
            if(!valid_iterations){
                return ret;
            }
            else{
                printf("\n Введите корректное значение\n");
                valid_iterations = 2;
            }
        }    
    }    
}

int get_user_input_string(char *str, int max_string_size)
{
    int str_lenght = 0, valid_itteraton = 1;

    while(fgets(str, max_string_size, stdin) != NULL){
        str_lenght = strlen(str);
        valid_itteraton--;
        if(str[str_lenght - 1] == '\n'){
            if(!valid_itteraton && str_lenght > 1){
                return str_lenght;
            }
            else{
                printf("\n Введите от 1 до %d символов\n", max_string_size-2);
                memset(str, 0, max_string_size);
                valid_itteraton = 1;
            }
        }
    }
    return 0;
}

int find_free_space_in_phonebook(struct phonebook *book)
{
    int i = 0;

    for(i = 0; i < PHONEBOOK_SIZE; i++){
        // printf("\n 0x%x \n", book[i].name[0]);
        if(book[i].name[0] == '\0'){
            return i;
        }
    }
    return -1;
}

int print_all_names(struct phonebook *book)
{
    for(int i = 0; i < PHONEBOOK_SIZE; i++){
        if(book[i].name[0] != '\0'){
            printf("%s", book[i].name);
        }
    }
}

int print_all_adresses(struct phonebook *book)
{
    for(int i = 0; i < PHONEBOOK_SIZE; i++){
        if(book[i].adres[0] != '\0'){
            printf("%s", book[i].adres);
        }
    }
}

int is_phone_number(char *str, int phone_number_size)
{
    int ret;
    for(char i = 0; i < phone_number_size - 1; i++){
        if(!isdigit(str[i])){
            printf("\n Введите числа от 0 до 9\n");
            memset(str, 0, phone_number_size);
            return 0;
        }
    }
    return 1;
}

int find_abonent_by_name(struct phonebook *book)
{
    int user_input_lenght, i;
    char user_input_str[NAME_SIZE];
    memset(user_input_str, 0, NAME_SIZE);

    printf("\n Введите ФИО абонента\n");
    user_input_lenght = get_user_input_string(user_input_str, NAME_SIZE);

    for(i = 0; i < PHONEBOOK_SIZE; i++){
        if(!strncmp(user_input_str, book[i].name, user_input_lenght-1)){
            printf("\n%s%s%s\n", book[i].name, book[i].adres, book[i].phone_number);
            return 1;
        }
    }
    printf("\n Абонент не найден\n");
    return 0;
}

int find_abonent_by_adress(struct phonebook *book)
{
    int user_input_lenght, i;
    char user_input_str[ADRES_SIZE];
    memset(user_input_str, 0, ADRES_SIZE);

    printf("\n Введите адрес абонента\n");
    user_input_lenght = get_user_input_string(user_input_str, ADRES_SIZE);

    for(i = 0; i < PHONEBOOK_SIZE; i++){
        if(!strncmp(user_input_str, book[i].adres, user_input_lenght-1)){
            printf("\n%s%s%s\n", book[i].name, book[i].adres, book[i].phone_number);
            return 1;
        }
    }
    printf("\n Абонент не найден\n");
    return 0;
}

int delete_abonent_from_phonebook(struct phonebook *book)
{
    int user_input_lenght, i;
    char user_input_str[NAME_SIZE];
    memset(user_input_str, 0, NAME_SIZE);

    printf("\n Введите ФИО абонента\n");
    user_input_lenght = get_user_input_string(user_input_str, NAME_SIZE);

    for(i = 0; i < PHONEBOOK_SIZE; i++){
        if(!strncmp(user_input_str, book[i].name, user_input_lenght-1)){
            printf("\n%s%s%s\n Абонент удален\n", book[i].name, book[i].adres, book[i].phone_number);
            memset(&book[i], 0, sizeof(book[i]));
            return 1;
        }
    }
    printf("\n Абонент не найден\n");
    return 0;
}
