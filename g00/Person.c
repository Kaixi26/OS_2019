#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Person.h"

Person new_person (char *name, int age){
    Person p;
    size_t len = strlen (name) + 1;
    p.name = calloc (len, sizeof(char));
    strcpy(p.name, name);
    p.age = age;
    return p;
}

Person clone_person (Person *p){
    return new_person (p->name, p->age);
}

void destroy_person (Person *p) {
    free (p->name);
}

int person_age (Person *p) {
    return p->age;
}

void person_change_age (Person *p, int age) {
    p->age = age;
}

void person_print (Person *p) {
    printf ("%s %d", p->name, p->age);
}
