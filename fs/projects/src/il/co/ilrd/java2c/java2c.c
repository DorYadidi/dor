#include <stdio.h>   /*printf*/
#include <stdlib.h> /*calloc*/
#include <string.h> /*strcpy*/

#define ARRAY_SIZE 5
typedef void (*v_func_t)(void *);
enum {TO_STRING, FINALIZE, SAY_HELLO, GET_NUM_MASTERS} func_t;
typedef enum {FALSE, TRUE} bool;
/**********************************metadata************************************/
typedef struct class_s class_t;
struct class_s
{
	char *name;
	size_t size;
	class_t *super;
	v_func_t (*v_table)[];
};
/************************************Object class******************************/
typedef struct object_s object_t;
struct object_s
{
	class_t *metadata;
};

void finalize(object_t *obj)
{
	free(obj);
	obj = NULL;
}

int hashCode(object_t *obj)
{
	int result = 0;
	char *string = obj->metadata->name;
	for (int i = 0; i < strlen(string); ++i)
	{
		result += string[i] * 31;
	}

	return (result);
}

char *toString(object_t *obj)
{
	char *to_string = calloc(strlen(obj->metadata->name) + 20, 1);
	sprintf(to_string, "il.co.ilrd.java2c %s @%x", obj->metadata->name, hashCode(obj));

	return (to_string);
}

v_func_t object_v_table[] = {(void (*)(void *))toString, (void (*)(void *))finalize};
class_t obj_metadata = {"Object", sizeof(object_t), NULL, &object_v_table};

/******************************Animal class************************************/

static int animal_counter = 0; /*static var from animal_t*/
static bool static_block_flag_animal = FALSE;

typedef struct animal_s animal_t;
struct animal_s
{
	object_t object;
	int num_legs;
	int num_masters;
	int ID;
};

void StaticBlockAnimal();
void AnimalCtor1(animal_t *animal);
void AnimalCtor2(animal_t *animal, int num_masters);
void sayHello(animal_t *animal);
void showCounter();
int getNumMasters(animal_t *animal);
void Animal_finalize(animal_t *animal);
char *Animal_toString(animal_t *animal);

void StaticBlockAnimal()
{
	if (FALSE == static_block_flag_animal)
	{
		printf("Static block Animal 1\n");
		printf("Static block Animal 2\n");
		static_block_flag_animal = TRUE;
	}
}

void AnimalCtor1(animal_t *animal)
{
	StaticBlockAnimal(); /*static block*/
	printf("Instance initialization block Animal\n"); /*non static block*/

	printf("Animal Ctor\n");
	animal->ID = ++animal_counter;
	animal->num_legs = 5;
	animal->num_masters = 1;
	((void (*)(void*))((*animal->object.metadata->v_table)[SAY_HELLO]))(animal);
	showCounter(animal);
	printf("%s\n", ((char * (*)(void*))((*animal->object.metadata->v_table)[TO_STRING]))(animal));
	printf("%s\n", toString((void *)animal));
}

void AnimalCtor2(animal_t *animal, int num_masters)
{
	StaticBlockAnimal(); /*static block*/
	printf("Instance initialization block Animal\n"); /*non static block*/
	printf("Animal Ctor int\n");
	animal->ID = ++animal_counter;
	animal->num_legs = 5;
	animal->num_masters = num_masters;
}

void sayHello(animal_t *animal)
{
	printf("Animal Hello!\n");
	printf("I have %d legs\n", animal->num_legs);
}

void showCounter()
{
	printf("%d\n", animal_counter);
}

int getNumMasters(animal_t *animal)
{
	return (animal->num_masters);
}

void Animal_finalize(animal_t *animal)
{
	printf("finalize Animal with ID: %d \n", animal->ID);
	finalize((void *)animal);
}

char *Animal_toString(animal_t *animal)
{
	char *to_string = calloc(strlen(animal->object.metadata->name) + 20, 1);
	sprintf(to_string, "Animal with ID: %d", animal->ID);

	return (to_string);
}

v_func_t animal_v_table[] = {(void (*)(void *))Animal_toString, (void (*)(void *))Animal_finalize,
	                        (void (*)(void *))sayHello, (void (*)(void *))getNumMasters};
class_t animal_metadata = {"Animal", sizeof(animal_t), &obj_metadata, &animal_v_table};

/**********************************Dog class************************************/

static bool static_block_flag_dog = FALSE;

typedef struct dog_s dog_t;
struct dog_s
{
	animal_t animal;
	int num_legs;
};

void StaticBlockDog();
void DogCtor1(dog_t *dog);
void sayHelloDog(dog_t *dog);
void Dog_finalize(dog_t *dog);
char *Dog_toString(dog_t *dog);

void StaticBlockDog()
{
	if (FALSE == static_block_flag_dog)
	{
		printf("Static block Dog\n");
		static_block_flag_dog = TRUE;
	}
}

void DogCtor1(dog_t *dog)
{
	StaticBlockAnimal(); /*static super*/
	StaticBlockDog(); /*static block*/
	AnimalCtor2(&dog->animal, 2); /*super*/

	printf("Instance initialization block Dog\n"); /*non static block*/
	dog->num_legs = 4;
	printf("Dog Ctor\n");
}

void sayHelloDog(dog_t *dog)
{
	printf("Dog Hello!\n");
	printf("I have %d legs\n", dog->num_legs);
}

void Dog_finalize(dog_t *dog)
{
	printf("finalize Dog with ID: %d \n", dog->animal.ID);
	finalize((void *)dog);
}

char *Dog_toString(dog_t *dog)
{
	char *to_string = calloc(strlen(dog->animal.object.metadata->name) + 20, 1);
	sprintf(to_string, "Dog with ID: %d", dog->animal.ID);

	return (to_string);
}

v_func_t dog_v_table[] = {(void (*)(void *))Dog_toString, (void (*)(void *))Dog_finalize,
	                      (void (*)(void *))sayHelloDog, (void (*)(void *))getNumMasters};
class_t dog_metadata = {"Dog", sizeof(dog_t), &animal_metadata, &dog_v_table};

/********************************Cat class*************************************/

static bool static_block_flag_cat = FALSE;

typedef struct cat_s cat_t;
struct cat_s
{
	animal_t animal;
	char *colors;
	int num_masters;
};

void StaticBlockCat();
void CatCtor1(cat_t *cat);
void CatCtor2(cat_t *cat, char *colors);
void Cat_finalize(cat_t *cat);
char *Cat_toString(cat_t *cat);

void StaticBlockCat()
{
	if (FALSE == static_block_flag_cat)
	{
		printf("Static block Cat\n");
		static_block_flag_cat = TRUE;
	}
}

void CatCtor1(cat_t *cat)
{
	CatCtor2(cat, "black");
	printf("Cat Ctor\n");
	cat->num_masters = 2;
}

void CatCtor2(cat_t *cat, char *colors)
{
	StaticBlockAnimal(); /*static super*/
	StaticBlockCat(); /*static block*/
	AnimalCtor1(&cat->animal); /*super*/

	cat->num_masters = 5;
	cat->colors = calloc(10, 1);
	strcpy(cat->colors, colors);
	printf("Cat Ctor with color: %s\n" , cat->colors);
}

void Cat_finalize(cat_t *cat)
{
	printf("finalize Cat with ID: %d \n", cat->animal.ID);
	finalize((void *)cat);
}

char *Cat_toString(cat_t *cat)
{
	char *to_string = calloc(strlen(cat->animal.object.metadata->name) + 20, 1);
	sprintf(to_string, "Cat with ID: %d", cat->animal.ID);

	return (to_string);
}

v_func_t cat_v_table[] = {(void (*)(void *))Cat_toString, (void (*)(void *))Cat_finalize,
	                  (void (*)(void *))sayHello, (void (*)(void *))getNumMasters};
class_t cat_metadata = {"Cat", sizeof(cat_t), &animal_metadata, &cat_v_table};

/********************LegendaryAnimal class**************************************/

static bool static_block_flag_la = FALSE;

typedef struct legendary_animal_s legendary_animal_t;
struct legendary_animal_s
{
	cat_t cat;
};

void StaticBlockLA();
void LegendaryAnimalCtor1(legendary_animal_t *legendary_animal);
void sayHelloLegendaryAnimal(legendary_animal_t *legendary_animal);
void LegendaryAnimal_finalize(legendary_animal_t *legendary_animal);
char *LegendaryAnimal_toString(legendary_animal_t *legendary_animal);

void StaticBlockLA()
{
	if (FALSE == static_block_flag_la)
	{
		printf("Static block Legendary Animal\n");
		static_block_flag_la = TRUE;
	}
}

void LegendaryAnimalCtor1(legendary_animal_t *legendary_animal)
{
	StaticBlockAnimal(); /*static super*/
	StaticBlockCat(); /*static super*/
	StaticBlockLA(); /*static block*/
	CatCtor1(&legendary_animal->cat); /*super*/
	printf("Legendary Ctor\n");
}

void sayHelloLegendaryAnimal(legendary_animal_t *legendary_animal)
{
	(void)legendary_animal;
	printf("Legendary Hello!\n");
}

void LegendaryAnimal_finalize(legendary_animal_t *legendary_animal)
{
	printf("finalize Cat with ID: %d \n", legendary_animal->cat.animal.ID);
	finalize((void *)legendary_animal);
}

char *LegendaryAnimal_toString(legendary_animal_t *legendary_animal)
{
	char *to_string = calloc(strlen(legendary_animal->cat.animal.object.metadata->name) + 20, 1);
	sprintf(to_string, "LegendaryAnimal with ID: %d", legendary_animal->cat.animal.ID);

	return (to_string);
}

v_func_t legendary_animal_v_table[] = {(void (*)(void *))LegendaryAnimal_toString,
  (void (*)(void *))LegendaryAnimal_finalize,
    (void (*)(void *))sayHelloLegendaryAnimal, (void (*)(void *))getNumMasters};

class_t la_metadata = {"LegendaryAnimal", sizeof(legendary_animal_t),
                                     &cat_metadata, &legendary_animal_v_table};

/************************ObjectAlloc*******************************************/

object_t *ObjectAlloc(class_t *metadata)
{
	object_t *obj = calloc(metadata->size, 1);
	obj->metadata = metadata;

	return (obj);
}

/*****************************Main*********************************************/

void foo(animal_t *animal)
{
	printf("%s\n", ((char * (*)(void*))((*animal->object.metadata->v_table)[TO_STRING]))(animal));
}

int main ()
{
	object_t *obj = ObjectAlloc(&obj_metadata);

	animal_t *animal = (animal_t *)ObjectAlloc(&animal_metadata);
	AnimalCtor1(animal);

	dog_t *dog = (dog_t *)ObjectAlloc(&dog_metadata);
	DogCtor1(dog);

	cat_t *cat = (cat_t *)ObjectAlloc(&cat_metadata);
	CatCtor1(cat);

	legendary_animal_t *la = (legendary_animal_t *)ObjectAlloc(&la_metadata);
	LegendaryAnimalCtor1(la);

	showCounter();

	printf("%d\n", animal->ID);
	printf("%d\n", dog->animal.ID);
	printf("%d\n", cat->animal.ID);
	printf("%d\n", la->cat.animal.ID);

	dog_t *dog2 = (dog_t *)ObjectAlloc(&dog_metadata);
	DogCtor1(dog2);

	cat_t *cat2 = (cat_t *)ObjectAlloc(&cat_metadata);
	CatCtor1(cat2);

	cat_t *cat3 = (cat_t *)ObjectAlloc(&cat_metadata);
	CatCtor2(cat3, "white");

	legendary_animal_t *la2 = (legendary_animal_t *)ObjectAlloc(&la_metadata);
	LegendaryAnimalCtor1(la2);

	animal_t *animal2 = (animal_t *)ObjectAlloc(&animal_metadata);
	AnimalCtor1(animal2);

	animal_t *array[] = {(animal_t *)dog2, (animal_t *)cat2, (animal_t *)cat3, (animal_t *)la2, animal2};

	for(int i = 0; i < ARRAY_SIZE; ++i)
	{
		((void (*)(void*))((*array[i]->object.metadata->v_table)[SAY_HELLO]))(array[i]);
		printf("%d\n", ((int (*)(void*))((*array[i]->object.metadata->v_table)[GET_NUM_MASTERS]))(array[i]));
	}

	for(int j = 0; j < ARRAY_SIZE; ++j)
	{
		foo(array[j]);
	}

	return (0);
}
