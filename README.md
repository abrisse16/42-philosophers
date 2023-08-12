<div align=center>

# <b>Philosophers</b>

### 42 common core / circle #3
<i>Eat, Sleep, Spaghetti, repeat.
<br>This project is about learning how threads work by precisely timing a group of philosophers on when to pick up forks and eat spaghetti without dying from hunger.</i>

##

### Final grade
[![abrisse's 42 Philosophers Score](https://badge42.vercel.app/api/v2/cl1rqvecz002109l7rv0oprry/project/2850599)](https://github.com/JaeSeoKim/badge42)

### Subject
English version [here](https://cdn.intra.42.fr/pdf/pdf/96841/en.subject.pdf)
<br>
French version [here](https://cdn.intra.42.fr/pdf/pdf/96842/fr.subject.pdf)

</div>

---

## The project

In this project, we learned the basics of threading a process, gaining hands-on experience with creating threads and understanding the role of mutexes.

Drawing from the classic computer science paradigm, the "[Dining Philosopher’s Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)", this endeavor served as a vivid illustration of concurrency and race conditions, emphasizing the essential nature of grasping synchronization challenges and the techniques to resolve them.


### The Dining Philosopher's Problem

In this problem, a pre-determined number of philosophers come together to dine at a shared table. Each philosopher has their own designated place, with only one fork set beside each of their plates. These philosophers follow a routine cycle of eating, thinking, and sleeping. To eat their dish, which is a type of spaghetti, each philosopher requires two forks. However, acquiring these forks is the crux of the challenge. A philosopoher can only begin to eat when they successfully pick up both their left and right forks, which are only available when their neighboring philosophers are thinking and not eating. Once their meal is complete, they place down both forks and resume thinking.

<b>A philosopher routine</b>
- 🍴 Grab their left and right forks, if they are available.
- 🍝 Eat their spaghetti during `x` milliseconds.
- 🍴 Release their left and right forks.
- 🌙 Sleep during `x` milliseconds.
- 🧠 Think until their next meal or until they die.

<br>

The intricacy of this problem arises form ensuring that all philosophers can alternate between thinking and eating without any of them starving to death, especially given the constraint that a philosopher cannot predict when their peers might want to eat or think. The real dilemma here isn't just the act of eating but the coordination and synchronization required to keep all philosophers alive and content.

## Usage

Clone this repository :

```sh
git clone https://github.com/abrisse16/42-philosophers.git path/to/repository
````

In your local repository, run `make`

To run `philosophers`, use the following command :

```sh
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
````

> - number_of_philosophers : The number of philosophers and also the number of forks.
> - time_to_die (in milliseconds) : If a philosopher didn't start eating time_to_die milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
> - time_to_eat (in milliseconds) : The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
> - time_to_sleep (in milliseconds) : The time a philosopher will spend sleeping.
> - number_of_times_each_philosopher_must_eat (optional argument) : If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a philosopher dies.

---
<div align=center>
	<a href="mailto:abrisse@student.42.fr">abrisse@student.42.fr</a>
</div>