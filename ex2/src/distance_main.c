#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include "distance.h" 

#define MAX_LENGTH 100
#define MAX_SUGGESTIONS 5

void load_dictionary(const char *file_path, char ***word_list, int *list_size) 
{
    FILE *file = fopen(file_path, "r");
    if (!file) 
    {
        perror("Errore nell'apertura del dizionario");
        exit(EXIT_FAILURE);
    }

    char temp_word[MAX_LENGTH];
    int current_size = 0;
    int capacity = 10;
    *word_list = (char **)malloc(capacity * sizeof(char *));

    while (fgets(temp_word, MAX_LENGTH, file)) 
    {
        temp_word[strcspn(temp_word, "\n")] = '\0';
        if (current_size >= capacity) 
        {
            capacity *= 2;
            *word_list = (char **)realloc(*word_list, capacity * sizeof(char *));
        }
        (*word_list)[current_size] = strdup(temp_word);
        current_size++;
    }
    fclose(file);
    *list_size = current_size;
}

void load_text(const char *file_path, char ***text_lines, int *line_count) 
{
    FILE *file = fopen(file_path, "r");
    if (!file) 
    {
        perror("Errore nell'apertura del file di testo");
        exit(EXIT_FAILURE);
    }

    char temp_word[MAX_LENGTH];
    int current_size = 0;
    int capacity = 10;
    *text_lines = (char **)malloc(capacity * sizeof(char *));

    while (fscanf(file, "%s", temp_word) == 1) 
    {
        if (current_size >= capacity) 
        {
            capacity *= 2;
            *text_lines = (char **)realloc(*text_lines, capacity * sizeof(char *));
        }
        (*text_lines)[current_size] = strdup(temp_word);
        current_size++;
    }
    fclose(file);
    *line_count = current_size;
}

void remove_trailing_punctuation(char *word) 
{
    int length = strlen(word);
    while (length > 0 && ispunct(word[length - 1])) 
    {
        word[length - 1] = '\0';
        length--;
    }
}

void convert_to_lowercase(char *word) 
{
    for (int i = 0; word[i]; i++) 
    {
        word[i] = tolower(word[i]);
    }
}

void find_similar_words(const char *input_word, char **dictionary, int dict_size, char **suggestions, int *suggestion_count) 
{
    *suggestion_count = 0;

    for (int i = 0; i < dict_size; i++) 
    {
        char dict_entry[MAX_LENGTH];
        strncpy(dict_entry, dictionary[i], MAX_LENGTH);
        dict_entry[MAX_LENGTH - 1] = '\0';
        convert_to_lowercase(dict_entry);

        int distance = edit_distance_dyn(input_word, dict_entry);
        if (distance >= 1 && distance <= 2)
         {  
            if (*suggestion_count < MAX_SUGGESTIONS) 
            {
                suggestions[*suggestion_count] = dictionary[i];
                (*suggestion_count)++;
            }
        }
    }
}

int main(void) 
{
    char **dict_words;
    int dict_size;
    load_dictionary("dictionary.txt", &dict_words, &dict_size);

    char **input_words;
    int text_size;
    load_text("correctme.txt", &input_words, &text_size);

    for (int i = 0; i < text_size; i++) 
    {
        char *current_word = input_words[i];
        char cleaned_word[MAX_LENGTH];
        strncpy(cleaned_word, current_word, MAX_LENGTH);
        cleaned_word[MAX_LENGTH - 1] = '\0';

        remove_trailing_punctuation(cleaned_word);
        convert_to_lowercase(cleaned_word);

        char *suggestions[MAX_SUGGESTIONS];
        int suggestion_count;

        int is_correct_word = 0;
        for (int j = 0; j < dict_size; j++) 
        {
            char dict_word[MAX_LENGTH];
            strncpy(dict_word, dict_words[j], MAX_LENGTH);
            dict_word[MAX_LENGTH - 1] = '\0';
            convert_to_lowercase(dict_word);

            if (strcmp(cleaned_word, dict_word) == 0) 
            {
                is_correct_word = 1;
                break;
            }
        }

        find_similar_words(cleaned_word, dict_words, dict_size, suggestions, &suggestion_count);

        if (is_correct_word)
        {
            printf("Parola: %s è corretta\n", current_word);
        } 
        else {
            printf("Parola: %s\n", current_word);
        }

        printf("Suggerimenti:\n");
        for (int j = 0; j < suggestion_count; j++) 
        {
            printf(" - %s\n", suggestions[j]);
        }
        if (suggestion_count == 0) 
        {
            printf(" - Nessun suggerimento trovato\n");
        }
    }

    for (int i = 0; i < dict_size; i++) 
    {
        free(dict_words[i]);
    }
    free(dict_words);

    for (int i = 0; i < text_size; i++) 
    {
        free(input_words[i]);
    }
    free(input_words);

    return 0;
}
