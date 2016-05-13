#include "scene.c"

struct _scene_t{
  char* description; // a pointer to the description of the scene
  object_t* objects; // a pointer to the linked list of objects in this scene
  char** actions; // a pointer to a list of actions can be perform in this scene
}scene_t;
