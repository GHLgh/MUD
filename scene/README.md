# SCENEs
It's a module that presents the infomation of the room where the player is at. The infomation includes the objects in the room and the actions player can perform.

1. When a scene object (room) is created, it loads the scene description, objects that initially in the scene and available actions from scene file.
  * TODO: Type of the room may be needed such that enemies won't be spawned in safe room.
  * TODO: State of the room may be needed to indicate if there is a combat.

2. A scene object will keep its influence from players until it is flushed (the idea is similar to cache with LRU). When it is flushed, its status won't be saved (refreshing).
