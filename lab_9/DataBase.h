//
// Created by mikhail on 18.04.2020.
//
#ifndef LAB_9_DATABASE_H
#define LAB_9_DATABASE_H

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int const str_max_size = 32;

typedef struct entry_ {
    void **data;
    void *comp_field;
} entry;

void entry_init(entry *one)
{
    one->data = NULL;
    one->comp_field = NULL;
}

typedef struct table_ {
    int arg_amt;
    char **arg_types;
    char **titles;
    int size;
    int capacity;
    entry *list;
} table;

void table_init(table *db)
{
    db->arg_amt = 0;
    db->arg_types = NULL;
    db->titles = NULL;
    db->size = 0;
    db->capacity = 0;
    db->list = NULL;
}

void clear_input();
void destroy_table(table *);
void destroy_entry(table *, entry *);
entry copy_entry(table *, entry *);
void print_table(table *);
table get_new_table();
int is_str(table *, int);
int is_int(table *, int);
char *make_str_copy(char *);
void add_column(table *, char *, char *, void *);
void add_new_column(table *);
void add_entry(table *, entry *);
entry make_new_entry(table *);
void add_new_entry(table *);
int open_table(table *, char *);
entry get(table *, int);
int equal(table *, entry *, entry *);
int int_comparison(const void *, const void *);
int str_comparison(const void *, const void *);
void sort_by_field(table *, int);
void save_table(table *, char *);
int find_entry(table *, entry *);
void delete_entry(table *, int);
table get_entries_by_field(table *, void *, int);
table get_entries(table *);
void substitute_entry(table *, int, entry *);
int get_int_width(int);
int get_str_width(char *);
int get_width(table *, int, int);

//reads out all characters from standard input
void clear_input()
{
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

//two functions for freeing memory from entries and databases
void destroy_table(table *db)
{
    for(int i = 0; i < db->size; i++)
    {
        destroy_entry(db, &db->list[i]);
    }
    if(db->list != NULL)
        free(db->list);

    for(int i = 0; i < db->arg_amt; i++)
    {
        free(db->titles[i]);
        free(db->arg_types[i]);
    }
    if(db->arg_types != NULL)
    {
        free(db->titles);
        free(db->arg_types);
    }
}

//sends entry with given number to a better world
void delete_entry(table *db, int start)
{
    //why did the entry cross the road?
     if(start < db->size)
     {
         destroy_entry(db, &db->list[start]);
         db->size--;
     }

     for(int i = start; i < db->size; i++)
     {
         db->list[i] = db->list[i+1];
     }
}

//poryadok eto otstoy
void destroy_entry(table *db, entry *slated)
{
    for(int i = 0; i < db->arg_amt; i++)
    {
        // free(slated->data[i]);
    }
    if(slated->comp_field != NULL)
        free(slated->comp_field);
    if(slated->comp_field != NULL)
        free(slated->data);
}

entry copy_entry(table *db, entry *one)
{
    entry result;
    result.data = (void **)calloc(db->arg_amt, sizeof(void *));
    for(int j = 0; j < db->arg_amt; j++)
    {
        if(is_str(db, j))
        {
            result.data[j] = make_str_copy((char *)(one->data[j]));
        }
        if(is_int(db, j))
        {
            result.data[j] = (void *)calloc(1, sizeof(int));
            ((int *)result.data[j])[0] = ((int *)(*one).data[j])[0];
        }
    }
    return result;
}


table get_new_table()
{
    table ret;
    ret.arg_amt = 0;
    ret.size = 0;
    ret.capacity = 0;

    return ret;
}

//functions for checking type of field under given number in arg_types array
int is_str(table *db, int field)
{
    return strcmp(db->arg_types[field], "str") == 0;
}

int is_int(table *db, int field)
{
    return strcmp(db->arg_types[field], "int") == 0;
}

char *make_str_copy(char *origin)
{
    char *result = (char *)calloc(str_max_size, sizeof(char));
    for(int i = 0; i < strlen(origin) + 1; i++)
    {
        result[i] = origin[i];
    }

    return result;
}

//to make new columns in a table (for construction of a new table)
void add_column(table *db, char *title, char *type, void* value)
{
    db->arg_amt++;
    if(db ->arg_amt == 1)
    {
        db->titles = (char **)calloc(db->arg_amt, sizeof(char **));
        db->arg_types = (char **)calloc(db->arg_amt, sizeof(char **));
    }
    else
    {
        db->titles = (char **)realloc(db->titles, db->arg_amt*sizeof(char **));
        db->arg_types = (char **)realloc(db->arg_types, db->arg_amt*sizeof(char **));
    }
    db->titles[db->arg_amt - 1] = make_str_copy(title);
    db->arg_types[db->arg_amt - 1] = make_str_copy(type);

    // assigning default value to existing entries
    for(int i = 0; i < db->size; i++)
    {
        if(db->arg_amt == 1)
            db->list[i].data = (void**)calloc(db->arg_amt, sizeof(void **));
        else
            db->list[i].data = (void**)realloc(db->list[i].data, db->arg_amt*sizeof(void **));
        if(is_str(db, db->arg_amt - 1))
        {
            db->list[i].data[db->arg_amt - 1] = make_str_copy((char *)value);
        }
        if(is_int(db, db->arg_amt - 1))
        {
            db->list[i].data[db->arg_amt - 1] = malloc(sizeof(int));
            ((int *)db->list[i].data[db->arg_amt - 1])[0] = *(int *)value;
        }
    }
}

//interface for making new columns
void add_new_column(table *db)
{
    char *title, *type;
    title = (char *)calloc(str_max_size, sizeof(char *));
    void *value;
    printf("Enter title for a new column: ");
    scanf("\n%[^\n]s", title);
    const char *typelist[] = {"int", "str"};
    printf("Enter number of corresponding type\n");
    for (int i = 0; i < 2; i++)
    {
        printf("%s - %d\n", typelist[i], i);
    }
    int typen;
    while(1)
    {

        scanf("%d", &typen);
        if(typen >= 0 && typen < 2)
            break;
        printf("Incorrect number, please try again: ");
        clear_input();
    }
    type = (char *)typelist[typen];
    printf("Enter default value for this field: ");
    if(typen == 0)
    {
        value = malloc(sizeof(int));
        scanf("%d", (int *)value);
    }
    if(typen == 1)
    {
        value = calloc(str_max_size, sizeof(char));
        scanf("%s", (char *)value);
    }
    add_column(db, title, type, value);
    printf("New column has been successfully added to database\n");
    free(title);
    // free(type); // it points on element of static array
    free(value);
}

//maximum safe method to add an existing entry
void add_entry(table *db, entry *new_entry)
{
    if(db->size == 0)
    {
        db->capacity = 10;
        db->list = (entry *)calloc((db->capacity), sizeof(entry));
    }
    db->size++;
    if(db->size > db->capacity)
    {
        db->capacity*=2;
        db->list = (entry *)realloc(db->list, db->capacity*sizeof(entry));
    }
    db->list[db->size-1] = copy_entry(db, new_entry);
}

//Interface for creating one entry according to existing database fields
entry make_new_entry(table *db)
{
    entry new_entry;
    new_entry.data = (void **)calloc(db->arg_amt, sizeof(void *));
    for(int i = 0; i < db->arg_amt; i++)
    {
        printf("Type %s (%s value) for a new entry: ", db->titles[i], db->arg_types[i]);
        if(is_str(db, i))
        {
            new_entry.data[i] = calloc(str_max_size, sizeof(char));
            scanf("%s", (char *)(new_entry.data[i]));
        }
        if(is_int(db, i))
        {
            new_entry.data[i] = malloc(sizeof(int));
            scanf("%d", (int *)new_entry.data[i]);
        }
    }
    return new_entry;
}

void add_new_entry(table *db)
{
    entry new_entry = make_new_entry(db);
    add_entry(db, &new_entry);
    destroy_entry(db, &new_entry);
}

int open_table(table *db, char *filename)
{
    FILE *file = fopen(filename, "r");
    if(file == NULL)
        return 1;
    fscanf(file, "%d ", &(db->arg_amt));
    fscanf(file, "%d\n", &(db->size));
    db->arg_types = (char **)calloc(db->arg_amt, sizeof(char *));
    db->titles = (char **)calloc(db->arg_amt, sizeof(char *));
    for(int i = 0; i < db->arg_amt; i++)
    {
        db->arg_types[i] = (char *)calloc(str_max_size, sizeof(char));
        db->titles[i] = (char *)calloc(str_max_size, sizeof(char));
        fscanf(file, "%s %[^\n]s\n", db->arg_types[i], db->titles[i]);
    }
    db->capacity = db->size;
    db->list = (entry *)calloc(db->capacity, sizeof(entry));
    for(int i = 0; i < db->size; i++)
    {
        db->list[i].data = (void **)calloc(db->arg_amt, sizeof(void *));
        for(int j = 0; j < db->arg_amt; j++)
        {
            if(is_str(db, j))
            {
                // I wonder if this trick would work
                // But maybe it is even unnecessary
                // "One week later"
                // I mastered pointers like a hell and I know that this shit works
                db->list[i].data[j] = calloc(str_max_size, sizeof(char));
                fscanf(file, "%s ", (char *) (db->list[i].data[j]));
            }
            if(is_int(db, j))
            {
                //this too
                db->list[i].data[j] = malloc(sizeof(int));
                fscanf(file, "%d ", (int *)(db->list[i].data[j]));
            }
        }
    }
    fclose(file);
    return 0;
}

// the most useless function here
entry get(table *db, int number)
{
    assert(db->size > number);
    assert(number >= 0);
    return (copy_entry(db, &db->list[number]));
}

// compares two entries and if they are equal returns true otherwise false
int equal(table *db, entry *first, entry *second)
{
    int ans = 1;
    for(int i = 0; i < db->arg_amt; i++)
    {
        if(is_str(db, i))
            ans &= (strcmp((char *)(first->data[i]), (char *)(second->data[i])) == 0);
        if(is_int(db, i))
            ans &= (*(int *)(first->data[i]) == *(int *)(second->data[i]));
    }
    return ans;
}

// integer comparator for qsort
int int_comparison(const void *elem1, const void *elem2)
{
    entry f = *((entry *)elem1);
    entry s = *((entry *)elem2);
    return (*(int *)f.comp_field - *(int *)s.comp_field);
}

// char * comparator for qsort
int str_comparison(const void *elem1, const void *elem2)
{
    entry f = *((entry *)elem1);
    entry s = *((entry *)elem2);
    return strcmp((char *)f.comp_field, (char *)s.comp_field);
}

//sorts by field under given number in table->titles
void sort_by_field(table *db, int field)
{
    for(int i = 0; i < db->size; i++)
    {
        //comparison field is the field used by qsort comparators above
        db->list[i].comp_field = (void *)(db->list[i].data[field]);
    }
    if(is_str(db, field))
    {
        qsort(db->list, db->size, sizeof(entry), str_comparison);
        return;
    }
    if(is_int(db, field))
    {
        qsort(db->list, db->size, sizeof(entry), int_comparison);
        return;
    }
    //It must end before
    assert(0);
}

void save_table(table *db, char *filename)
{
    //first line is amount of arguments and number of entries
    FILE *file = fopen(filename, "w");
    fprintf(file, "%d ", db->arg_amt);
    fprintf(file, "%d\n", db->size);

    //next lines contain type and title for each argument field
    for(int i = 0; i < db->arg_amt; i++)
    {
        fprintf(file, "%s %s\n", db->arg_types[i], db->titles[i]);
    }

    //next lines contain values for each field in each entry separated by whitespaces
    for(int i = 0; i < db->size; i++)
    {
        fprintf(file, "\n");
        for(int j = 0; j < db->arg_amt; j++)
        {
            if(is_str(db, j))
            {
                fprintf(file, "%s ", (char *)db->list[i].data[j]);
            }
            if(is_int(db, j))
            {
                fprintf(file, "%d ", *(int *)db->list[i].data[j]);
            }
        }
    }
    fclose(file);
}

//returns position of first occurrence of equal entry
// and returns database size if there is no equal entries in given database
int find_entry(table *db, entry *one)
{
    int number = db->size;
    for(int i = 0; i < db->size; i++)
    {
        if(equal(db, one, &(db->list[i])))
        {
            number = i;
            break;
        }
    }
    return number;
}

// returns database containing entries with desired value in chosen field only
table get_entries_by_field(table *db, void* field, int type)
{
    table result = get_new_table();
    result.arg_amt = db->arg_amt;
    result.arg_types = (char **)calloc(db->arg_amt, sizeof(char *));
    result.titles = (char **)calloc(db->arg_amt, sizeof(char *));
    for(int i = 0; i < db->arg_amt; i++)
    {
        result.arg_types[i] = make_str_copy(db->arg_types[i]);
        result.titles[i] = make_str_copy(db->titles[i]);
    }

    for(int i = 0; i < db->size; i ++)
    {
        if(is_str(db, type))
        {
            if(strcmp((char *)(db->list[i].data[type]), (char *)field) == 0)
            {
                add_entry(&result, &db->list[i]);
            }
        }
        if(is_int(db, type))
        {
            if(*(int *)(db->list[i].data[type]) == *(int *)(field))
            {
                add_entry(&result, &db->list[i]);
            }
        }
    }

    return result;
}

//interface for searching entries with desired values
table get_entries(table *db)
{
    int type;
    void *value;
    printf("Enter number of corresponding column\n");
    for(int i = 0; i < db->arg_amt; i++)
    {
        printf("%s - %d\n", db->titles[i], i);
    }
    scanf("%d", &type);
    while(type < 0 || type >= db->arg_amt)
    {
        printf("Invalid option '%d'. Please, try again: ", type);
        clear_input();
        scanf("%d", &type);
    }

    printf("Enter value of field (%s value): ", db->arg_types[type]);
    clear_input();
    if(is_str(db, type))
    {
        value = calloc(str_max_size, sizeof(char));
        scanf("%s", (char *)value);
    }
    if(is_int(db, type))
    {
        value = malloc(sizeof(int));
        scanf("%d", (int *)value);
    }
    table result = get_entries_by_field(db, value, type);
    free(value);
    return result;
}

//trying to find a given entry in database and rewrite it
void substitute_entry(table *db, int pos, entry *after)
{
    //pos--; //find_entry(db, before);
    destroy_entry(db, &db->list[pos]);
    if(pos < db->size)
        db->list[pos] = copy_entry(db, after);
}

//determines minimum width for integer fields to print database as spreadsheet
int get_int_width(int field)
{
    int res = 0;
    if(field < 0)
    {
        field *= -1;
        res++;
    }

    while(field > 0)
    {
        res++;
        field /= 10;
    }
    if(res == 0)
        res++;
    return res;
}

//returns hom much bytes after this byte belongs to the same character (if it is first byte)
// may and will throw errors if used on middle bytes of utf8 characters
int utf8_added_length(char *s) {
    //this function must not be here but I just can't leave it alone in other header
    int value = *s;
    value = ((unsigned int)value) % 256;
    if (value < 128)
        return 0; // regular ASCII byte
    assert(value > 128+64); // continuation byte, invalid code point
    if (value < 128+64+32)
        return 1; // code-point encoded on 2 bytes
    if (value < 128+64+32+16)
        return 2; // code-point encoded on 3 bytes
    if (value < 128+64+32+16+8)
        return 3; // code-point encoded on 4 bytes
        assert(0); // NO INVALID POINTERS IN MY CODE!!!
}

//returns quantity of utf8 characters in string
int get_str_width(char * field)
{
    int russians = 0;
    for(int i = 0; i < strlen(field); i++)
    {
        int to_add = utf8_added_length(&field[i]);
        russians += to_add;
        i += to_add;
    }

    return ((int)strlen(field) - russians);
}

//function beautifully displays database on the screen
void print_table(table *db)
{
    int number_width = (1<db->size?get_int_width(db->size):1);
    int *widths = NULL;
    widths = (int *)calloc(db->arg_amt, sizeof(int));

    // for(int i = 0; i < db->arg_amt; i++)
    // {
    //     printf("%s, ", db->arg_types[i]);
    // }
    printf("\n");
    //counting all widths for fields in table format
    for(int i = 0; i < db->arg_amt; i++) // for each argument
    {
        widths[i] = get_str_width(db->titles[i]);
        for(int j = 0; j < db->size; j++) // in each entry
        {
            if(is_str(db, i))
            {
                if(db->list[j].data[i] == NULL)
                {
                    printf("Alert!");
                }
                int width = get_str_width((char *)(db->list[j].data[i]));
                if(widths[i] < width)
                    widths[i] = width;
            }
            if(is_int(db, i))
            {
                int width = get_int_width(*(int *)db->list[j].data[i]);
                if(widths[i] < width)
                    widths[i] = width;
            }
        }
    }

    //printing titles in table format to terminal
    printf("||%*s|", number_width, "№");
    for(int i = 0; i < db->arg_amt; i++)
    {
            printf("|%*s%s|", widths[i] - get_str_width(db->titles[i]),
                    "", (char *)db->titles[i]);
    }
    printf("|\n");

    //printing entries by values in table format
    for(int i = 0; i < db->size; i++)//for each entry
    {
        printf("||%*d|", number_width, i + 1);
        for(int j = 0; j < db->arg_amt; j++)//for each argument in entry
        {
            if(is_str(db, j))
            {
                printf("|%*s%s|", widths[j] - get_str_width((char *)db->list[i].data[j]),
                        "", (char *)db->list[i].data[j]);
            }
            if(is_int(db, j))
            {
                printf("|%*d|", widths[j], *((int *)(db->list[i].data[j])));
            }
        }
        printf("|\n");
    }
    if(db->size == 0)
        printf("No entries\n");
}
//I hope you are ok after reading so much shitty code
//take care

#endif //LAB_9_DATABASE_H
