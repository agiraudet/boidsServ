# boidsServ
A C.W.Reynolds boid's implementation in C++ with realtime controls.

The end goal is to provide an indpendant process capable of taking inputs (both for controls and querry),
 and outputing various informations about the boids in return.
 
## Controls
Currently, only three keyboard inputs are used as realtime-controls:
* __[A]__ Create a new flock off boids. Number and position are randoms, with numbers between 50 ans 500.
* __[S]__ Delete the mmost recently created flock.
* __[Q]__ Exit the program.

## Dependecies
* [SLD2](https://www.libsdl.org/) is used for all video rendering, and input management.
* [CPTL](https://github.com/vit-vit/CTPL) is used for threadPooling (but is already included in the code as a header).

## Structure and how to use
The Sky class need to be instancied only once. It will manages all the flocks of boids.
Each Flock class holds N boids.
Currently, each Flock just ignore each other, but that will change in the future.
```
                  +-----+
                  | SKY |
                  +-----+
                     |
       +-------------+-------------+
       |             |             |
  +---------+   +---------+   +---------+
  | Flock 1 |   | Flock 2 |   | Flock 3 |
  +---------+   +---------+   +---------+
    |             |             |
    +-[Boid1]     +-[Boid1]     +-[Boid1]
    +-[Boid2]     +-[Boid2]     +-[Boid2]
    +-[Boid3]     +-[Boid3]     +-[Boid3]
    +-[Boid4]     +-[Boid4]     +-[Boid4]  
```

## TODO next
* Get a better visual for the boids.
* Create different type of boids with differents ruleset
* Allow Flocks to see each other (and thus interract)
* Create a proper control system (might be either via a GUI or a command prompt)
