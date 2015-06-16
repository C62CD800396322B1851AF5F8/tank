# tank
Tank game to learn SFML and C++

## Game concept
tanks are fighting in an arena. Their bullets can bounce on the external walls, but are stopped when hitting objects in the arena, be it a tank or an obstacle.

## Modeling
### List of objects
- Tank
- Bullet
- Obstacle
- Wall

The Tank, Bullet and Obstacle all a method returning the intersection if it touches -- they should inherit from the same parent class Thing.

### Utility objects
I might also need these:
- Thing
- Vector

### Physics
#### Tank
The tanks movements are constant speed for the first iteration (advance, rotate left or right, go back), but a second iteration could take into account the acceleration.

If a tank touches another tank, an Obstacle or a Wall, it cannot move in the direction, but it should “slide” on it — don’t know how to do it for the moment.
If a tank is touched by a Bullet, it disappears.

#### Bullet
A Bullet bounces on walls, calculating the normal vector towards the inside of the arena and the speed vector of the bullet — just like raytracing.
If a Bullet touches a Bullet, an Obstacle or a Tank, it disappears.

#### Obstacle
An Obstacle doesn’t move, for the moment.

## Possible problems
corner of the arena: the bullets are big enough to always touch a side of a wall, knowing its direction is adding (like vectors) towards the inside.

## Organisation
- [X] Code the Tank class and instantiate it to move it around a free space: advance, go backward, turn left, turn right and combine the turns and other moves.
- [X] Code the Bullet, and fire it from nowhere, then from the Tank and finally towards the tank to test if collision is detected correctly.
- [X] Code the Wall of the arena, fire a Bullet to check it bounces, then check if the Tank cannot pass through.
- [X] Code an Obstacle and check the detection with a Bullet works — the Bullet disappears but not the Obstacle.
- [X] Make the Obstacle impossible to go through for the tank.
- [ ] Add some sprites for the Tank, the Bullet and the Obstacle.

## Improvements
* Everything is on the stack, so I should learn how to use the heap in C++
* MVC is squished into marmalade, which I should be ashamed coming from the modeling community
* Replace Obstacles by a polygon (with collision detection)

