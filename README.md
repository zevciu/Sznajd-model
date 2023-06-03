# Sznajd-model

This is a project that i made for "Computational sociology" classes during my Master's studies at AGH University.
This project is an attempt to build a simple sociophysical model, called the Sznajd model, using the C++ programming language.

This model simulates consensus building through the exchange of opinions between members of a given community. A very important point of reference for this model is the social phenomenon called "social proof". According to this principle, a person in a situation in which
does not know which decision or view is right, makes decisions or adopts the views of the majority of the group.

In this social simulation, a simple two-dimensional regular network is considered, on which actors "yes" and actors "no" will be distributed randomly according to the given initial proportion, i.e. a given network cell will take the state 1 or (-1). The simulation process assumes that if there are two "spinsons" (spin+person) with the same views in a randomly selected place on the network, i.e. a pair assuming the state (1, 1) or (-1, -1), then adjacent cells in the next unit of time they will adopt their state, i.e. they will adopt the opinion of a compatible pair. Due to the fact that a simple 2D regular network is considered, the number of neighbors for a given pair will be exactly 6.


In the main.cpp file:

- run_exercise(1):
We follow the evolution of a small (10x10) system for 10 time steps. At the initial moment, the spatial distribution coefficient p0 of the "yes" actors is equal to 0.5, which means that the opinions "yes" and "no" are exactly 50% each.

- run_exercise(2):
We trace the time evolution p(t) of the yes actors for a 14x14 array and p0 = 0.5 to calculate the arithmetic mean of the time (t) for the system to stabilize. We run 20 such simulations.

- run_exercise(3):
We consider a 14x14 array. We simulate 10, 1000 and 100000 times for p0 = 0.5. Each time the actors will be distributed differently on the networks. We will do the same for p0 = 0.25 and p0 = 0.75.
The simulation time for p0 = 0.5 will be t = 2252 (determined according to the results from run_exercise(2))
The simulation time for p0 = 0.25 will be t = 1091 (determined on the basis of the average of 20
observation)
The simulation time for p0 = 0.75 will be t = 711 (determined on the basis of the average of 20
observation)
Finally, we average the results and estimate the uncertainty of these averages.
