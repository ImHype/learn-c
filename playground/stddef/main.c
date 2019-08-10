#include <stddef.h>
#include <stdio.h>
#include <assert.h>

enum course_t {
    ENGLISH,
    CHINISH,
};

typedef enum course_t course_tt;

#define BASE_DATA \
    char * name; \
    int age;

typedef struct {
    BASE_DATA;
    course_tt course;
} teacher_t;


typedef struct {
    BASE_DATA
} student_t;


typedef struct {
    char * name;
    teacher_t * teacher;
    student_t* student_list[10];
} class_t;

#define container_of(ptr, type, member) \
  ((type *) ((char *) (ptr) - offsetof(type, member)))

int main(int argc, char const *argv[])
{

    int pos = offsetof(teacher_t, name);
    assert(pos == 0);

    class_t class;
    teacher_t teacher;
    student_t student;
    course_tt course = ENGLISH;

    teacher.name = "teacher";
    teacher.age = 31;
    teacher.course = course;

    student.name = "student";
    student.age = 11;

    class.teacher = &teacher;
    class.student_list[0] = &student;

    teacher_t * teacher_cpy = container_of(&teacher.name, teacher_t, name);

    assert(teacher_cpy == &teacher);

    assert(offsetof(class_t, teacher) == sizeof(char *));

    assert(offsetof(class_t, student_list) == sizeof(char *) * 2);

    class.name = "class one";

    class_t * class_cpy = container_of(&class.name, class_t, name);
    class_t * class_cpy2 = container_of(&class.teacher, class_t, teacher);
    class_t * class_cpy3 = container_of(&class.student_list, class_t, student_list);

    assert(class_cpy == &class);
    assert(class_cpy2 == &class);
    assert(class_cpy3 == &class);
    assert(class_cpy2->student_list[0]->name == student.name);

    printf("All cases success\n");

    return 0;
}
