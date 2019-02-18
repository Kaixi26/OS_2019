#include <stdio.h>
#include "Person.h"

int main(){

    Person andre = new_person ("Andre", 20);

    printf ("Old age :%d\n", andre.age);
    person_change_age (&andre, 30);
    printf ("New age :%d\n", andre.age);

    Person new_andre = clone_person(&andre);

    person_change_age (&new_andre, 40);
    printf ("Age : %d\n", andre.age);
    printf ("Clone age : %d\n", new_andre.age);

    destroy_person (&andre);
    destroy_person (&new_andre);

    return 0;
}
